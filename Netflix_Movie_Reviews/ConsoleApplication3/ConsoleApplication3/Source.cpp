// 
// Netflix Movie Reviews
// Ashour Dankha
// U. of Illinois, Chicago
// CS 341, Fall 2016
// HW #02
//
// Description: A simple C++ program that utilizes the vector container alongside basic C++ library algorithms (stable_sort, sort, find_if)
//				The goal of the program is to read in a large dataset / files that contains information about reviews on movies on Netflix.
//				The main educational goal is to grow familar with some of the C++ standard library and concepts of writing code in an efficient manner to produce an outcome.
//				The outcome for this program is to print the top 10 movies based on average rating and the top 10 users based on total reviews written.
//


// Includes
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Movie.h"
#include "Review.h"
#include "TotalReview.h"
#include <ctime>

// Namespaces
using std::string;
using std::ifstream;
using std::vector;
using std::stringstream;
using std::getline;
using std::stoi;
using std::sort;
using std::cout;
using std::endl;



/* Function that reads the movies from the file being passed in
	Restrictions for reading in file:
		.csv file (comma delimiter)
		movieid, moviename, pubyear
		int, string, int respectively
*/
int read_movies(vector<Movie>& movies, string filename, int& totalMovies) {

	/* Reading movies.csv file. Parsing each line. Storing line into vector.*/
	ifstream file1(filename);

	/* Holds the line (for parsing purposes), MovieID, MovieName, and PublishYear*/
	string line1, mid, mvName, pubYr;


	// Check to see if file can be opened.
	if (!file1.good()) {
		cout << "Could not open file. Terminating program." << endl;
		return -1;
	}

	getline(file1, line1);    // Skip header of .csv file

    // Main while loop that reads and parses file and stores into vector Movie class. It also sorts!
	while (getline(file1, line1))
	{
		stringstream ss(line1); // Grab the line, store in ss
								// Parse the line using the comma delimiters

	    /* Parse the values from file using the comma delimiter*/
		getline(ss, mid, ',');
		getline(ss, mvName, ',');
		getline(ss, pubYr, ',');

		// Create an instance of the Movie class and use the constructor to store the contents of the line
		Movie M(stoi(mid), mvName, stoi(pubYr));

		// Store into vector
		movies.push_back(M);
		totalMovies++;

	}
	/* End of movies.csv file (reading, parsing, and storing). Return true */
	return 0;
}

/* Sorts the movies based on MID */
void sort_movies(vector<Movie>& movies) 
{
	// Sorting the Movie vector by MID (Movie ID) in ascending order:
	sort(movies.begin(),
		movies.end(),
		[](Movie& m1, Movie& m2)
	{
		if (m1.MID > m2.MID)
			return false;
		else
			return true;
	}
	);
}


/* Function that reads the reviews from the file being passed in
	Restrictions for reading in file:
	.csv file (comma delimiter)
	movieid, userid, rating, revdate
	int, int, int, string respectively
*/
int read_reviews(vector<Review>& reviews, string fname, int& totalReviews)
{

	ifstream  file2(fname);
	int i = 0;

	/* Holds line (for parsing), UserID, Rating, and ReviewDate of the Reviews*/
	string line, mid, uid, rating, revdate;

	if (!file2.good()) {
		cout << "Could not open file. Terminating program." << endl;
		return -1;
	}

	getline(file2, line); // Skip the header in the .csv file

	while (getline(file2, line))
	{
		stringstream ss(line);

		//Parse the line:
		getline(ss, mid, ',');
		getline(ss, uid, ',');
		getline(ss, rating, ',');
		getline(ss, revdate, ',');

		// Create an instance holding the first line read in from the file.
		Review R(stoi(mid), stoi(uid), stoi(rating), revdate);

		// Insert @ end in the vector reviews:
		reviews.push_back(R);
		totalReviews++;
	}

	return 0;
}



/* Self explanatory. Sorts the review vector based on MID or UID*/
void sort_reviews(vector<Review>& reviews, int flag)
{
	// Sorting the Review vector by MID (Movie ID) in ascending order:
	if (flag == 1)
	{
		sort(reviews.begin(),
			reviews.end(),
			[](Review& r1, Review& r2)
		{
			if (r1.MID > r2.MID)
				return false;
			else if (r1.MID == r2.MID)
				return false;
			else
				return true;
		}
		);
	}
	else
	{
		sort(reviews.begin(),
			reviews.end(),
			[](Review& r1, Review& r2)
		{
			if (r1.UID < r2.UID)
				return false;
			else
				return true;
		}
		);
	}
}


// Sort helper used for when the Ratings average are the same. We sort by movie name.
bool sort_helper(const vector<Movie>& movies, int mid1, int mid2)
{

	string firstName;
	string secondName;
	/* Finds the first Movie to be compared with secondary sort method*/
	auto iter = std::find_if(
		movies.begin(),
		movies.end(),
		[&](const Movie& m)
	{
		if (m.MID == mid1)
			return true;
		else
			return false;
	}
	);

	// Assign firstName to be that MovieName
	if (iter != movies.end() && iter->MID == mid1)
			firstName.assign(iter->MovieName);

	/* Finds the second Movie to be compared with secondary sort method*/
		iter = std::find_if(
		movies.begin(),
		movies.end(),
		[&](const Movie& m)
	{
		if (m.MID == mid2)
			return true;
		else
			return false;
	}
	);

	// Assign secondName to be that MovieName
	if (iter != movies.end() && iter->MID == mid2)		
			secondName.assign(iter->MovieName);

	// If firstName is less than secondName, we want it to be in ascending order, so return true.
	if (firstName.compare(secondName) < 0)
		return true;		
	else
		return false;
}



/*

Important function for all the multiple components of the program.

1. Loops in the review vector to find all the matching movie IDs (it's sorted, so once there is an unmatch, we have a new set).
2. During the loop, it adds to the total count, to the average rating, and to the specific count for the ratings 1 to 5.
3. Sorts the totals vector by the average rating (while holding the movie ID!). If there is equality in the ratings, we search for names and sort that way.
4. Once all the components are stored in the totals vector, we search for the movies in the movie vector by ID and store those values there.
*/
void avg_total(vector<TotalReview>& totals, const vector<Review>&  reviews, vector<Movie>& movies)
{
	int count = 0;
	double rating = 0;
	int mid = reviews.front().MID;
	int rangeRatings[6]; 	// Used to hold the specific count of ratings 1 to 5. (Note: index 1 = rating 1 count


	for (int i = 0; i < 6; i++)
	{
		rangeRatings[i] = 0;
	}


	// For loop that helps us find all the MovieIDs so that we can...
	// Count the total Reviews
	// Count the average of the reviews
	// Count the number of specific rating values (1 to 5)
	// Once we have all this information, we pushed it onto our totals vector.
	for (const Review& r : reviews)
	{
		if (mid != r.MID)
		{
			rating = rating / count;
			TotalReview TR(mid, count, rating, rangeRatings);
			totals.push_back(TR);

			mid = r.MID;
			count = 0;
			rating = 0;

			for (int i = 0; i < 6; i++)
			{
				rangeRatings[i] = 0;
			}

		}
		rangeRatings[r.Rating]++;
		count++;
		rating = rating + r.Rating;
	}

	rating = rating / count;
	TotalReview TR(mid, count, rating, rangeRatings);
	totals.push_back(TR);

	// We do a stable sort here so that when the TotalRatings are a match, we sort by the Movie Name.
	stable_sort(
		totals.begin(),
		totals.end(),
		[&](const TotalReview& tr1, const TotalReview& tr2)
	{
		if (tr1.TotalRating > tr2.TotalRating)
			return true;
		else if (tr1.TotalRating == tr2.TotalRating)
			return sort_helper(movies, tr1.MID, tr2.MID);
		else
			return false;
	}
	);

	// Important aspect of storing the information of the Movie class inside the actual Movie class.
	// Here we are storing the Average Rating, Total Review Count, and the specific numbers for the ratings 1 to 5 in the Movie class
	// We want to be able to have the Movie class stand-alone at the end of the program. i.e. Holds all the information that it's related to.
	// This for-loop iterates through the totals class which holds all the linking pieces and finds the corresponding movie and stores it in the movie class instances.
	for (size_t i = 0; i < totals.size(); ++i)
	{
		auto iter = std::find_if(
			movies.begin(),
			movies.end(),
			[&](Movie& m)
		{
			if (m.MID == totals[i].MID)
				return true;
			else
				return false;
		}
		);
		if (iter != movies.end())
		{
			iter->setRating(totals[i].TotalRating);
			iter->setCount(totals[i].TotalCount);
			iter->setRatingArray(totals[i].ratingArray);
		}
	}


} // End of avg_total(..)




void print_top10_movies(const vector<TotalReview>& totals, const vector<Movie>& movies)
{

	for (int i = 0; i < 10; ++i)
	{

		cout << i + 1 << ".\t" << totals[i].MID << ":\t" << totals[i].TotalCount << ":\t";
		auto iter = std::find_if(
			movies.begin(),
			movies.end(),
			[&](const Movie& m)
		{
			if (m.MID == totals[i].MID)
				return true;
			else
				return false;
		}
		);
		if (iter != movies.end())
		{
			cout << iter->TotalRating << "\t" << "'" << iter->MovieName << "'" << endl;
		}
	}
}



/* Self-explanatory here. Essentially counts the total reviews a user inputs and then sorts to easily grab the top 10*/
void user_review_total(vector<TotalReview>& userTotals, const vector<Review>&  reviews)
{
	int count = 0;
	int uid = reviews.front().UID;

	for (const Review& r : reviews)
	{
		if (uid != r.UID)
		{
			TotalReview TR(uid, count);
			userTotals.push_back(TR);
			uid = r.UID;
			count = 0;
		}
		count++;
	}

	TotalReview tr(uid, count);
	userTotals.push_back(tr);

	// now sort:
	stable_sort(
		userTotals.begin(),
		userTotals.end(),
		[&](const TotalReview& tr1, const TotalReview& tr2)
	{
		if (tr1.TotalUserCount > tr2.TotalUserCount)
			return true;
		else if (tr1.TotalUserCount == tr2.TotalUserCount)
			return tr1.UID < tr2.UID;
		else
			return false;
	}
	);
}// void end of user_review_total(..)



int main()
{

	clock_t begin = clock();
	
	cout << "** Netflix Movie Review Analysis **" << endl << endl;


	/* Reading movies.csv file.
	Parsing each line.
	Storing line into vector.
	Returns -1 if failed, 0 if success
	*/
	vector<Movie> movies;		// Create a vector for the codes
	int totalMovies = 0;		// Holds total number of codes
	string fname = "movies.csv";
	cout << ">> Reading Movies... ";

	//Read
	if(read_movies(movies, fname, totalMovies) == -1)		// Function that returns -1 if failed to read, otherwise it reads and stores into vector
		return -1;
	cout << "Done!" << endl;
	//Sort
	cout << ">> Sorting Movies... ";
	sort_movies(movies);		// Sorts the movie vector
	cout << "Done!" << endl;


	/* Reading reviews.csv file. 
	Parsing each line. 
	Storing line into vector.
	*/
	vector<Review> reviews;
	int totalReviews = 0;									// Holds total number of reviews
	fname = "reviews-2.csv";
	cout << ">> Reading Reviews... ";

	//Read
	if (read_reviews(reviews, fname, totalReviews) == -1)	// Function that returns -1 if failed to read, otherwise it reads and stores into vector
		return -1;
	cout << "Done!" << endl;
	cout << ">> Sorting Reviews... ";
	
	//Sort
	sort_reviews(reviews, 1);								// Sorts the review vector
	cout << "Done!" << endl << endl;

	/* Prints for Total Movies and Reviews */
	cout << ">> Total Movies: " << totalMovies << " <<" << endl;
	cout << ">> Total Reviews: " << totalReviews << " <<" << endl << endl << endl;


	/*****************************/
	/*		Top-10 Movies		 */
	/*****************************/

	vector<TotalReview> totals;			// Vector to hold/ tally the totals of movie ratings and the average
	avg_total(totals, reviews, movies);	// Function that handles the finding of average rating, total count, and searching and sorting of the top 10 movies 
	cout << "** Top-10 Movies **" << endl;
	cout << "Rank:	ID:	Reviews:Average: MovieName" << endl;
	print_top10_movies(totals, movies);	// Function that prints the top-10 movies
	cout << endl;


	/*****************************/
	/*		Top-10 Users		 */
	/*****************************/

	// Sorting the Review vector by UID) in descending order:
	sort_reviews(reviews, -1);
	vector<TotalReview> userTotals;
	user_review_total(userTotals, reviews);
	
	cout << "** Top-10 Users **" << endl;
	cout << "Rank:	ID:	Reviews:" << endl;

	for (int i = 0; i < 10; ++i)
		cout << i + 1 << ".\t" << userTotals[i].UID << ": " << userTotals[i].TotalUserCount << endl;



	/* Time variable to see how long the execution was for parsing in all the data.*/
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << endl << "TOTAL TIME ELAPSED: " << elapsed_secs << endl;


	/******************************/
	/*		Interactive Loop	  */
	/******************************/
	string userInput;
	do
	{
		cout << endl << "Please enter a movie ID [1..." << movies.size() << "], 0 to stop: ";
		std::cin >> userInput;
		cout << endl;

		if (stoi(userInput) < 0 || stoi(userInput) > 250)
			cout << "** Invalid movie id, please try again..." << endl;
		else if (stoi(userInput) == 0)
		{
			cout << "DONE." << endl;
		}
		else
		{
			cout << "Movie:\t" << "'" << movies[stoi(userInput) - 1].MovieName << "'"<< endl;
			cout << "Year:\t" << movies[stoi(userInput) - 1].PubYear << endl;
			cout << "Avg rating:  " << movies[stoi(userInput) - 1].TotalRating << endl;
			cout << "Num reviews:  " << movies[stoi(userInput) - 1].TotalCount << endl;
			
			for (int i = 0; i < 5; i++) 
			{
				cout << "Num " << i+1 << "'s:\t" << movies[stoi(userInput) - 1].ratingArray[i + 1] << endl;
			}

		}
	} while (userInput.compare("0") != 0);

}