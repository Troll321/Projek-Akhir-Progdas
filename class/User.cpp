#include "User.h"
#include "MainApp.h"
#include "Finance.h"
#include "Payment.h"
#include "Transaction.h"
#include "Interaction.h"
#include "RentalPost.h"
#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <sys/types.h>

using namespace std;

ROLE User::getRole() {return this->role;}
void User::setRole(ROLE role) {this->role = role;}

bool User::checkUsername(string inputUsername) {
	DIR *nowdir;
	struct dirent *file;
	nowdir = opendir("database/users");
	if (nowdir) {
		while ((file = readdir(nowdir)) != NULL) {
			string uID = file->d_name;
			ifstream userFile("database/users/"+uID);
			string nowUsername;
			userFile >> nowUsername;	
			userFile.close();

			if (nowUsername == inputUsername) {
				closedir(nowdir);
				return false;
			}
		}
		closedir(nowdir);
	}
	return true;
}

User::User(){}

vector<int> User::getTransactions() {return this->transactions;}
vector<int> User::getInteractions() {return this->interactions;}
vector<int> User::getPayments() {return this->payments;}

void User::addPayment(int payID) {
	this->payments.push_back(payID);
}

int User::getUserID() {return this->userID;}

int User::getBalance() {return this->balance;}

string User::getPassword() {return this->password;}

void User::save() {
	// Add user to the Users DB
	ofstream userFile("database/users/"+to_string(this->userID));
	userFile <<
	DELIM << this->username <<
	DELIM << this->password <<
	DELIM << this->email <<
	DELIM << this->region <<
	DELIM << this->role <<
	DELIM << this->balance <<
	DELIM << this->transactions.size();
	for (int i = 0; i < this->transactions.size(); ++i) {
		userFile << DELIM << transactions[i];
	}
	userFile << DELIM << this->interactions.size();
	for (int i = 0; i < this->interactions.size(); ++i) {
		userFile << DELIM << interactions[i];
	}
	userFile << DELIM << this->payments.size();
	for (int i = 0; i < this->payments.size(); ++i) {
		userFile << DELIM << payments[i];
	}
	userFile.close();
}

void User::populate(int uID) {
	this->userID = uID;
	ifstream userFile("database/users/"+to_string(uID));
	unsigned int transactionsSize, interactionsSize, paymentsSize;
	int role;
	userFile >>
	this->username >>
	this->password >>
	this->email >>
	this->region >>
	role >>
	this->balance >>
	transactionsSize;

	this->role = (ROLE)role;

	this->transactions.resize(transactionsSize);
	for (int i = 0; i < this->transactions.size(); ++i) {
		userFile >> (this->transactions)[i];
	}
	userFile >> interactionsSize;
	this->interactions.resize(interactionsSize);
	for (int i = 0; i < this->interactions.size(); ++i) {
		userFile >> (this->interactions)[i];
	}
	userFile >> paymentsSize;
	this->payments.resize(paymentsSize);
	for (int i = 0; i < this->payments.size(); ++i) {
		userFile >> (this->payments)[i];
	}
	userFile.close();
}

// Not Dummy
User::User(string username, string password, string email, string region) {
	this->interactions.clear();
	this->transactions.clear();
	this->username = username;
	this->password = password;
	this->email = email;
	this->region = region;
	this->userID = MainApp::genID("users");

	this->save();
	
	cout << "User Successfully Created!\n";
}

void User::rental(int pID) {
	cout << "Please make a payment!\n";
	if(Finance::makePayment(MainApp::nowUser, RENTAL_PRICE)) {
		// Create Transaction
		Transaction transaction(this->userID);
		this->transactions.push_back(transaction.getTransactionID());

		// Create Interaction
		Interaction interaction(RENTAL, pID, this->userID, transaction.getTransactionID());
		this->interactions.push_back(interaction.getInteractionID());

		// Update Rental Post
		RentalPost rentalPost;
		rentalPost.populate(pID);
		rentalPost.addInteraction(interaction.getInteractionID());
		rentalPost.save();

		this->save();

		cout << "Rental success, you can grab umbrella number "
			 << (MainApp::rng() % 100 + 1)
			 << " at the post!\n\n"
			 << "Please return it " << RENTAL_LIMIT << " minutes after usage (failing results in late fine)\n"
			 << "Have a nice day :V\n";
	} else {
		cout << "Rental cancelled!\n";
	}
}

void User::retrieve(int pID) {
	Transaction transaction;
	transaction.populate(this->transactions.back());
	if(transaction.retrieve(this)) {
		cout << "You have a late fine!\nCheck payment history!\n";
	}

	transaction.save();

	Interaction interaction(RETRIEVED, pID, this->userID, transaction.getTransactionID());
	this->interactions.push_back(interaction.getInteractionID());

	RentalPost rentalPost;
	rentalPost.populate(pID);
	rentalPost.addInteraction(interaction.getInteractionID());
	rentalPost.save();

	this->save();
}

int User::checkOngoingTransaction() {
	if (this->transactions.empty()) {
		return 0;
	}
	int tID = this->transactions.back();
	Transaction transaction;
	transaction.populate(tID);

	if (transaction.getStatus() == RENTAL) {
		return tID;
	} else {
		return 0;
	}
}

void User::setPassword(string newPassword) {this->password = newPassword;}

void User::updateBalance(int amount, FLOW flow) {
	if (flow == IN) {
		this->balance += amount;
	}
	if (flow == OUT) {
		this->balance -= amount;
	}
}