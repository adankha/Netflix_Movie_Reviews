#include "Movie.h"


Movie::Movie(int mid, string mn, int py)
{
	MID = mid;
	MovieName = mn;
	PubYear = py;
	TotalCount = 0;
	TotalRating = 0;
	for (int i = 0; i < 6; i++)
	{
		ratingArray[i] = 0;
	}
}

// Getters /
int Movie::getMID() { return MID; }
int Movie::getPubYear() { return PubYear; }
string Movie::getMovieName() { return MovieName; }
int Movie::getCount() { return TotalCount; }
double Movie::getRating() { return TotalRating; }

//* Setters /
void Movie::setRating(double num) { TotalRating = num; }
void Movie::setCount(int num) { TotalCount = num; }
void Movie::setRatingArray(int arr[])
{
	for (int i = 0; i < 6; i++)
	{
		ratingArray[i] = arr[i];
	}
}



