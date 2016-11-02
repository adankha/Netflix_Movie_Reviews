#pragma once
#include <iostream>
#include <string>
using namespace std;

/*
Class TotalReview has a few very important features.
1. It is the class that helps determine the top 10 movies as well as the top 10 users
2. This class can be seen as a "linking" table for a database.
3. The class also has an int array that holds the total ratings per int value from 1 to 5.
*/

class TotalReview
{

public:
	int MID;
	int UID;
	int TotalCount;
	double TotalRating;
	int TotalUserCount;
	int ratingArray[6];

	TotalReview(int uid, int total);
	TotalReview(int mid, int total, double rating, int ratingarray[]);
};


