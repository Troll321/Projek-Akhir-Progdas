#include <iostream>
#include <fstream>
#include "Transaction.h"
#include "MainApp.h"
#include "Date.h"
#include "Payment.h"

using namespace std;

Transaction::Transaction() {}

Transaction::Transaction(int uID) {
	this->userID = uID;
	this->transactionID = MainApp::genID("transactions");
	this->startDate = Date(0);
	this->expireDate = this->startDate;
	this->expireDate.increment(MINUTE, RENTAL_LIMIT);
	this->status = RENTAL;
	this->save();
}

int Transaction::getUserID() {return this->userID;}

int Transaction::getTransactionID() {return this->transactionID;}

Date Transaction::getExpireDate() {return this->expireDate;}

Date Transaction::getStartDate() {return this->startDate;}

Date Transaction::getRetrieveDate() {return this->retrieveDate;}

STATUS Transaction::getStatus() {return this->status;}

bool Transaction::retrieve(User* user) {
	this->status = RETRIEVED;
	this->retrieveDate = Date(0);

	// Calculate late fine
	if (this->expireDate < this->retrieveDate) {
		int fine = (this->retrieveDate-this->expireDate)/FINE_RATE*FINE_PRICE;
		Payment payment(user->getUserID(), fine, OUT, "Late fine for #"+to_string(this->transactionID));
		user->addPayment(payment.getPaymentID());
		user->updateBalance(fine, OUT);
		return true;
	}
	return false;
}

void Transaction::save() {
	ofstream transactionFile("database/transactions/"+to_string(this->transactionID));
	transactionFile <<
	DELIM << this->userID <<
	DELIM << this->status <<
	DELIM << this->startDate.getSave() <<
	DELIM << this->expireDate.getSave() <<
	DELIM << this->retrieveDate.getSave();
	transactionFile.close();
}

void Transaction::populate(int tID) {
	int status;
	this->transactionID = tID;
	ifstream transactionFile("database/transactions/"+to_string(this->transactionID));

	string startDate, expireDate, retrieveDate;

	transactionFile >>
	this->userID >>
	status >>
	startDate >>
	expireDate >>
	retrieveDate;
	this->startDate = Date(startDate);
	this->expireDate = Date(expireDate);
	this->retrieveDate = Date(retrieveDate);
	this->status = (STATUS)status;
	transactionFile.close();
}

string Transaction::getPrintable(bool isLong) {
	string output =
	"Transaction ID: " + to_string(this->transactionID) + "\n" +
	"User ID: " + to_string(this->userID) + "\n" + 
	"Status: " + MainApp::formatStatus(this->status) + "\n"
	"Start Date: " + this->startDate.getPrintable(isLong) + "\n" +
	"Expire Date: " + this->expireDate.getPrintable(isLong) + "\n";
	if (this->status == RENTAL) {
		output += "Retrieve Date: -\n";
	} else {
		output += "Retrieve Date: " + this->retrieveDate.getPrintable(isLong) + "\n";
	}
	return output;
}