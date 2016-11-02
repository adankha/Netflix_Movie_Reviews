#pragma once
#include <iostream>
#include <string>

using namespace std;

class Movie {

public:

	int MID;
	string MovieName;
	int PubYear;
	int TotalCount;
	double TotalRating;
	int ratingArray[6];

	//constructor prototype
	Movie(int mid, string mn, int py);


	/* Getters */
	int getMID();
	int getPubYear();
	string getMovieName();
	int getCount();
	double getRating();

	/* Setters */
	void setRating(double num);
	void setCount(int num);
	void setRatingArray(int arr[]);


};//end Movie class