#include <fstream>
#include "Interaction.h"
#include "MainApp.h"
#include "Date.h"

using namespace std;

Interaction::Interaction() {}

int Interaction::getUserID() {return this->userID;}

int Interaction::getPostID() {return this->postID;}

int Interaction::getTransactionID() {return this->transactionID;}

int Interaction::getInteractionID() {return this->interactionID;}

STATUS Interaction::getType() {return this->type;}

Date Interaction::getDate() {return this->date;}

Interaction::Interaction(STATUS type, int postID, int userID, int transactionID) {
	this->type = type;
	this->postID = postID;
	this->userID = userID;
	this->transactionID = transactionID;
	this->interactionID = MainApp::genID("interactions");
	this->date = Date(0);
	this->save();

	if (type == RETRIEVED) {
		this->updateTransactionState();
	}
}

void Interaction::save() {
	ofstream interactionFile("database/interactions/"+to_string(this->interactionID));
	interactionFile <<
	DELIM << this->transactionID <<
	DELIM << this->postID <<
	DELIM << this->userID <<
	DELIM << this->type <<
	DELIM << this->date.getSave();
	interactionFile.close();
}

void Interaction::populate(int tID) {
	this->interactionID = tID;
	ifstream interactionFile("database/interactions/"+to_string(this->interactionID));

	string date;
	int type;

	interactionFile >>
	this->transactionID >>
	this->postID >>
	this->userID >>
	type >>
	date;
	this->type = (STATUS)type;
	this->date = Date(date);
	interactionFile.close();
}

string Interaction::getPrintable(bool isLong) {

	string output = 
	"Interaction ID: " + to_string(this->interactionID) + "\n"
		 + "Transaction ID: " + to_string(this->transactionID) + "\n"
		 + "Post ID: " + to_string(this->postID) + "\n"
		 + "User ID: " + to_string(this->userID) + "\n"
		 + "Type: " + MainApp::formatStatus(this->type) + "\n"
		 + "Date: " + this->date.getPrintable(isLong) + "\n";
		 ;
	return output; 
}

void Interaction::updateTransactionState() {

}

