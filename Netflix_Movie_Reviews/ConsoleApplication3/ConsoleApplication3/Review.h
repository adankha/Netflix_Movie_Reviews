#pragma once
#include <iostream>
#include <string>

using namespace std;

class Review {

public:
	int MID;
	int UID;
	int Rating;
	string ReviewDate;

	Review(int mid, int uid, int rating, string rd);

	/* Getters */
	int getMID();
	int getUID();
	int getRating();
	string getRevDate();


};//end review header




