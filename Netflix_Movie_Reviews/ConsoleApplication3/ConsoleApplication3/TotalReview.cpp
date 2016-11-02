#include "TotalReview.h"

/*
Class TotalReview has a few very important features.
1. It is the class that helps determine the top 10 movies as well as the top 10 users
2. This class can be seen as a "linking" table for a database.
3. The class also has an int array that holds the total ratings per int value from 1 to 5.
*/


TotalReview::TotalReview(int mid_or_uid, int total)
{
	MID = mid_or_uid;
	UID = mid_or_uid;
	TotalUserCount = total;

}


TotalReview::TotalReview(int mid, int total, double rating, int ratingarray[])
{
	MID = mid;
	TotalCount = total;
	TotalRating = rating;
	for (int i = 0; i < 6; i++)
	{
		ratingArray[i] = ratingarray[i];
	}
}


