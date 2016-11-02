#include "Review.h"

Review::Review(int mid, int uid, int rating, string rd)
{
	MID = mid;
	UID = uid;
	Rating = rating;
	ReviewDate = rd;
}

/* Getters */
int Review::getMID() { return MID; }
int Review::getUID() { return UID; }
int Review::getRating() { return Rating; }
string Review::getRevDate() { return ReviewDate; }




