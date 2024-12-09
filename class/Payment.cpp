#include "Payment.h"
#include "MainApp.h"
#include <string>
#include <fstream>

using namespace std;

Payment::Payment() {}

Payment::Payment(int uID, int amount, FLOW flow, string metadata) {
	this->paymentID = MainApp::genID("payments");
	this->userID = uID;
	this->amount = amount;
	this->flow = flow;
	this->date = Date(0);
	this->metadata = metadata;

	this->save();
}

int Payment::getPaymentID() {return this->paymentID;}

void Payment::save() {
	ofstream paymentFile("database/payments/"+to_string(this->paymentID));
	paymentFile <<
	DELIM << this->userID <<
	DELIM << this->amount <<
	DELIM << this->flow <<
	DELIM << this->date.getSave() <<
	LINE_DELIM << this->metadata;
	paymentFile.close();
}

void Payment::populate(int tID) {
	this->paymentID = tID;
	ifstream paymentFile("database/payments/"+to_string(this->paymentID));
	int flow;
	string date;
	paymentFile >>
	this->userID >>
	this->amount >>
	flow >> date;

	this->date = Date(date);

	this->flow = (FLOW)flow;
	// Dummy
	getline(paymentFile, this->metadata);
	
	getline(paymentFile, this->metadata);
	paymentFile.close();
}

string Payment::formatFlow(FLOW flow) {
	switch(flow) {
		case IN:
			return "IN";
		case OUT:
			return "OUT";
	}
	return "";
}

string Payment::getPrintable(bool isLong) {
	string output = 
	"Payment ID: " + to_string(this->paymentID) + "\n" +
	"User ID: " + to_string(this->userID) + "\n" +
	"Amount: " + to_string(this->amount) + "\n" +
	"Flow: " + Payment::formatFlow(this->flow) + "\n" +
	"Date: " + (this->date.getPrintable(isLong)) + "\n" +
	"Metadata: " + this->metadata + "\n";
	return output;
}