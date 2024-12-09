#include <iostream>
#include <fstream>
#include "RentalPost.h"
#include "MainApp.h"

using namespace std;

RentalPost::RentalPost() {}

RentalPost::RentalPost(string postName, pair<float,float> coordinate) {
	this->coordinate = coordinate;
	this->postName = postName;
	this->postID = MainApp::genID("posts");
	this->interactions.clear();

	this->save();
	cout << "Post Succesfully Created!\n";
}

vector<int> RentalPost::getInteractions() {return this->interactions;}

void RentalPost::addInteraction(int iID) {
	this->interactions.push_back(iID);
}

int RentalPost::getPostID() {return this->postID;}

void RentalPost::save() {
	ofstream rentalFile("database/posts/"+to_string(this->postID));

	rentalFile <<
	this->postName <<
	LINE_DELIM << this->coordinate.first <<
	DELIM << this->coordinate.second <<
	DELIM << this->interactions.size();
	for (int i = 0; i < this->interactions.size(); ++i) {
		rentalFile << DELIM << (this->interactions)[i];
	}
	rentalFile.close();
}

void RentalPost::populate(int pID) {
	this->postID = pID;
	ifstream rentalFile("database/posts/"+to_string(this->postID));
	unsigned int interactionsSize;

	getline(rentalFile, this->postName);
	rentalFile >> 
	(this->coordinate).first >>
	(this->coordinate).second >>
	interactionsSize;
	this->interactions.resize(interactionsSize);
	for (int i = 0; i < this->interactions.size(); ++i) {
		rentalFile >> (this->interactions)[i];
	}
	rentalFile.close();
}