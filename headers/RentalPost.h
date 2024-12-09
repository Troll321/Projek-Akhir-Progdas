#ifndef RENTALPOST_CLASS
#define RENTALPOST_CLASS

#include <string>
#include <vector>
using namespace std;

class RentalPost {
private:
	int postID = 0;
	vector<int> interactions;

public:
	// {lattitude, longitude}
	pair<float,float> coordinate;
	string postName;

	RentalPost();

	RentalPost(string postName, pair<float,float> coordinate);

	vector<int> getInteractions();

	void addInteraction(int iID);

	int getPostID();

	void save();

	void populate(int pID);
};

#endif