#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <sys/types.h>
#include <dirent.h>
#include "MainApp.h"
#include "User.h"
#include "RentalPost.h"
#include "Transaction.h"
#include "Interaction.h"
#include "Payment.h"
#include "Finance.h"

using namespace std;

void MainApp::wait() {
	cout << "\n\n\n(press any key to continue)";
	string dummy;
	getline(cin, dummy);
}

void MainApp::clear() {
	system("cls");
}

void MainApp::exit() {
	MainApp::isExit = true;
	cout << "\nBye Bye!\n";
}

void MainApp::printBanner() {
	string banner =
	"                                                          \n"
	"\x1b[1;36m"
	" #     #                                                  \n"
	" #     # #    # #####  #####  ###### #      #        ##   \n"
	" #     # ##  ## #    # #    # #      #      #       #  #  \n"
	" #     # # ## # #####  #    # #####  #      #      #    # \n"
	" #     # #    # #    # #####  #      #      #      ###### \n"
	" #     # #    # #    # #   #  #      #      #      #    # \n"
	"  #####  #    # #####  #    # ###### ###### ###### #    # \n"
	"                                                          \n"
	"\x1b[1;31m"
	" ######                                                   \n"
	" #     # ###### #    # #####   ##   #                     \n"
	" #     # #      ##   #   #    #  #  #                     \n"
	" ######  #####  # #  #   #   #    # #                     \n"
	" #   #   #      #  # #   #   ###### #                     \n"
	" #    #  #      #   ##   #   #    # #                     \n"
	" #     # ###### #    #   #   #    # ######                \n"
	"                                                          \n"
	"\x1b[1;37m"
	"----------------------------------------------------------\n"
	"\x1b[0m"
	;
	cout << banner << "\n";
}

void MainApp::printMenu() {
	string menu =
	"Welcome to \x1b[1;3mUMBRELLA RENTAL!\x1b[23m \n"
	"\x1b[0m"
	"                            \n"
	"Command:                    \n"
	"1: Sign Up                  \n"
	"2: Login                    \n"
	"3: Get Posts Location       \n"
	"4: About Us                 \n"
	"5: Help                     \n"
	"6: Exit                     \n"
	"                            \n";
	cout << menu << "\n";
}

void MainApp::printMenuLogin() {
	string role = "";
	if (MainApp::nowUser->getRole() == 'A') {role = "Admin ";}
	string menu =
	"Welcome to \x1b[1;3mUMBRELLA RENTAL!\x1b[23m \n"
	"\x1b[0m"
	"Hi, \x1b[5m" + role + MainApp::nowUser->username + "\x1b[0m \n"
	"                              \n"
	"Command:                      \n"
	"\x1b[1m1 : Rental\x1b[0m                    \n"
	"\x1b[1m2 : Retrieve\x1b[0m                  \n"
	"3 : Add Post (admin only)     \n"
	"4 : Check Ongoing Transaction \n"
	"5 : Get Transactions History  \n"
	"6 : Get Interactions History  \n"
	"7 : Get User Balance          \n"
	"\x1b[1m8 : Get Posts Location\x1b[0m        \n"
	"9 : Get Post Interactions     \n"
	"10: Get Payments History      \n"
	"11: Change Password           \n"
	"12: Get Password              \n"
	"13: I am admin                \n"
	"\x1b[1m14: Deposit\x1b[0m                   \n"
	"15: What's my ID?             \n"
	"16: About Us                  \n"
	"17: Help                      \n"
	"18: Log Out                   \n"
	"19: Exit                      \n"
	;
	cout << menu << "\n";
}

void MainApp::aboutUs() {
	string output =
	"We are TIF 2024 (\"B\"ebek.inc)                          \n"
	"- Atila                                                  \n"
	"- The ho                                                 \n"
	"- Debert                                                 \n"
	"                                                         \n"
	"Together with us we will give you the best!              \n";
	cout << output << "\n";
}

void MainApp::help() {
	string output =
	"Imagine you want to rental an umbrella in an UmbrellaPost \n"
	"you should:                                               \n"
	"                                                          \n"
	"1. Login (sign up first if you don't have account yet)    \n"
	"1. Deposit your money                                     \n"
	"3. Scan the QR code or use the \"Get Posts Location\"     \n"
	"   to get post ID                                         \n"
	"4. Rental                                                 \n"
	"                                                          \n"
	"As simple as that, you can also check your history!       \n"
	"----------------------------------------------------------\n"
	"                                                          \n"
	"Dont't forget to retrieve the umbrella as hourly late fine\n"
	"is implied                                                \n"
	;
	cout << output << "\n";
}

bool MainApp::check(string dbpath, int id) {
	DIR *nowdir;
	struct dirent *file;
	string path = "database/"+dbpath;
	nowdir = opendir(path.c_str());
	if (nowdir) {
		while ((file = readdir(nowdir)) != NULL) {
			if (file->d_name == to_string(id)) {
				closedir(nowdir);
				return false;
			}
		}
		closedir(nowdir);
	}
	return true;
}

unsigned int MainApp::now() {
	return chrono::system_clock::now().time_since_epoch().count();
}

int MainApp::genID(string dbpath) {
	int id; 
	do {
		id = MainApp::rng() % MAX_ID;
	} while (!MainApp::check(dbpath, id));

	return id;
}

void MainApp::login() {
	string username, password;

	cout << "Please input username and password (NO WHITESPACE):\n";
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	cin.ignore();
	cout << "\n";

	DIR *nowdir;
	struct dirent *file;
	nowdir = opendir("database/users");
	if (nowdir) {
		while ((file = readdir(nowdir)) != NULL) {
			string uID = file->d_name;
			ifstream userFile("database/users/"+uID);
			string nowUsername;
			userFile >> nowUsername;

			if (nowUsername != username) {
				userFile.close();
				continue ;
			}

			string nowPassword;
			userFile >> nowPassword;
			if (nowPassword == password) {
				// True
				MainApp::nowUser->populate(stoi(file->d_name));

				cout << "Logged in as " << username << "\n";
			} else {
				cout << "Incorrect Password!\n";
			}

			userFile.close();
			closedir(nowdir);
			return ;
		}
		closedir(nowdir);
		cout << "User Not Found!\n";
	}
	return ;
}

void MainApp::signup() {
	string username, email, region, password;
	cout << "Please input the required data (NO WHITESPACE):\nUsername: ";

	cin >> username;
	while (!User::checkUsername(username)) {
		cout << "Sorry, username has already taken!\n\nUsername: ";
		cin >> username;
	}

	cout << "Password: ";
	cin >> password;
	cout << "Email: ";
	cin >> email;
	cout << "Region: ";
	cin >> region;
	cout << "\n\nAre you sure you want to create user with this info, users can't be deleted (y/N)?\n"
			"----------------------------------------------------------------------------------\n"
			"Username: " << username << "\n"
			"Password: " << password << "\n"
			"Email: " << email << "\n"
			"Region: " << region << "\n";

	cin.ignore();
	cout << "\n";
	string validation;
	getline(cin, validation);
	cout << "\n";

	if (validation == "y") {
		// Create User
		User user(username, password, email, region);
	} else {
		cout << "Cancelled Register!\n";
	}
}

void MainApp::notLoggedInUI() {
	MainApp::printBanner();
	MainApp::printMenu();

	string input;
	getline(cin, input);

	cout << "\n";
	if (input == "1") {
		MainApp::signup();
	} else if (input == "2") {
		MainApp::login();
	} else if (input == "3") {
		MainApp::getPostsLocation();
	} else if (input == "4") {
		MainApp::aboutUs();
	} else if (input == "5") {
		MainApp::help();
	} else if (input == "6") {
		MainApp::exit();
	} else {
		cout << "Invalid Command\n";
	}
}

void MainApp::loggedInUI() {
	MainApp::printBanner();
	MainApp::printMenuLogin();

	string input;
	getline(cin, input);

	cout << "\n";
	if (input == "1") {
		MainApp::rental();
	}
	else if (input == "2") {
		MainApp::retrieve();
	}
	else if (input == "3") {
		MainApp::addPost();
	} 
	else if (input == "4") {
		MainApp::checkOngoingTransaction();
	}
	else if (input == "5") {
		MainApp::getTransactionsHistory();
	}
	else if (input == "6") {
		MainApp::getInteractionsHistory();
	}
	else if (input == "7") {
		MainApp::getUserBalance();
	}
	else if (input == "8") {
		MainApp::getPostsLocation();
	}
	else if (input == "9") {
		MainApp::getPostInteractions();
	}
	else if (input == "10") {
		MainApp::getPaymentsHistory();
	}
	else if (input == "11") {
		MainApp::changePassword();
	}
	else if (input == "12") {
		MainApp::getPassword();
	}
	else if (input == "13") {
		MainApp::iAmAdmin();
	}
	else if (input == "14") {
		MainApp::deposit();
	}
	else if (input == "15") {
		MainApp::whatsMyID();
	}
	else if (input == "16") {
		MainApp::aboutUs();
	}
	else if (input == "17") {
		MainApp::help();
	}
	else if (input == "18") {
		MainApp::logOut();
	}
	else if (input == "19") {
		MainApp::exit();
	}
	else {
		cout << "Invalid Command!\n";
	}
}

string MainApp::formatStatus(STATUS status) {
	switch (status) {
		case RENTAL:
			return "Rental";
		case RETRIEVED:
			return "Retrieved";
	}
	return "";
}

void MainApp::rental() {
	if (MainApp::nowUser->checkOngoingTransaction()) {
		cout << "Please finish your ongoing transaction first!\n";
		return ;
	}
	int pID;
	string _pID;
	cout << "Input Post ID (NUMBERS ONLY): ";
	cin >> _pID;
	pID = stoi(_pID);
	cin.ignore();
	cout << "\n";
	if (MainApp::check("posts", pID)) {
		cout << "There are no post with that ID!\n";
		return ;
	}
	MainApp::nowUser->rental(pID);
}

void MainApp::retrieve() {
	if (!MainApp::nowUser->checkOngoingTransaction()) {
		cout << "There are no ongoing transaction!\n";
		return ;
	}
	int pID; string _pID;
	cout << "Input Post ID where you retrieve it\n"
		 << "Post ID (NUMBERS ONLY): ";
	cin >> _pID;
	pID = stoi(_pID);
	cin.ignore();
	cout << "\n";

	if (MainApp::check("posts", pID)) {
		cout << "There are no post with that ID!\n";
		return ;
	}

	MainApp::nowUser->retrieve(pID);
	cout << "------------------------------\n"
		 << "Sucessfully retrieve umbrella!\n";
}

void MainApp::getPostsLocation() {
	cout << "NO | ID : Post Name : <lat, long>\n"
		 << "---------------------------------\n";

	DIR *nowdir;
	struct dirent *file;
	nowdir = opendir("database/posts");
	if (nowdir) {
		int counter = 1;
		while ((file = readdir(nowdir)) != NULL) {
			if(strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
				continue ;
			}
			RentalPost rentalPost;
			rentalPost.populate(stoi(file->d_name));
			cout << counter <<  "  | "
				 << rentalPost.getPostID() << " : "
			 	 << rentalPost.postName << " : "
			 	 << "<" << rentalPost.coordinate.first << ", "
			 	 << rentalPost.coordinate.second << ">\n";
			counter++;
		}
		closedir(nowdir);
	}
	cout << "\n";
}

void MainApp::addPost() {
	if (MainApp::nowUser->getRole() != ADMIN) {
		cout << "This section is admin only!\n";
		return ;
	}

	pair<float,float> coordinate;
	pair<string,string> _coordinate;
	string postName;
	cout << "Please input the required data: \n";
	cout << "Post Name (can have whitespace): ";
	getline(cin, postName);
	cout << "Coordinate (FLOAT ONLY):\n";
	cout << "Lattitude: ";
	cin >> _coordinate.first;
	cout << "Longitude: ";
	cin >> _coordinate.second;
	coordinate.first = stof(_coordinate.first);
	coordinate.second = stof(_coordinate.second);
	cin.ignore();
	cout << "\n";

	RentalPost rentalPost(postName, coordinate);
}

void MainApp::checkOngoingTransaction() {
	int tID = MainApp::nowUser->checkOngoingTransaction();
	if(tID) {
		Transaction transaction;
		transaction.populate(tID);

		cout << "ONGOING TRANSACTION\n"
			 << "-------------------\n"
			 << transaction.getPrintable(false);
	} else {
		cout << "There are no ongoing transaction, you are free!\n";
	}
}

void MainApp::getTransactionsHistory() {
	vector<int> transactions = MainApp::nowUser->getTransactions();
	if (transactions.empty()) {
		cout << "There are no transactions yet!\n";
		return ;
	}
	for(int i = 0; i < transactions.size(); i++) {
		Transaction transaction;
		transaction.populate(transactions[i]);
		cout << "TRANSACTION #" << (i+1) << "\n"
			 << "-----------------\n"
		     << transaction.getPrintable(false) << "\n\n";
	}
}

void MainApp::getInteractionsHistory() {
	vector<int> interactions = MainApp::nowUser->getInteractions();
	if (interactions.empty()) {
		cout << "There are no interactions yet!\n";
		return ;
	}
	for(int i = 0; i < interactions.size(); i++) {
		Interaction interaction;
		interaction.populate(interactions[i]);
		cout << "INTERACTION #" << (i+1) << "\n"
			 << "-----------------\n"
		     << interaction.getPrintable(false) << "\n\n";
	}
}

void MainApp::getUserBalance() {
	cout << "Rp" << MainApp::nowUser->getBalance() << "\n";
}

void MainApp::getPostInteractions() {
	cout << "Input Post ID (NUMBERS ONLY): ";
	string _pID;
	int pID;
	cin >> _pID;
	pID = stoi(_pID);
	cin.ignore();
	cout << "\n";

	if(MainApp::check("posts", pID)) {
		cout << "There are no post with that ID!\n";
		return ;
	}

	RentalPost rentalPost;
	rentalPost.populate(pID);

	vector<int> interactions = rentalPost.getInteractions();
	for (int i = 0; i < interactions.size(); ++i) {
		Interaction interaction;
		interaction.populate(interactions[i]);
		cout << "INTERACTION #" << (i+1) << "\n"
			 << "-----------------\n"
		     << interaction.getPrintable(false) << "\n\n";
	}
}

void MainApp::getPaymentsHistory() {
	vector<int> payments = MainApp::nowUser->getPayments();
	for (int i = 0; i < payments.size(); ++i) {
		Payment payment;
		payment.populate(payments[i]);
		cout << "PAYMENT #" << (i+1) << "\n"
		 << "-----------------\n"
	     << payment.getPrintable(false) << "\n\n";
	}
}

void MainApp::changePassword() {
	string oldPass, newPass;
	cout << "Input now password (NO WHITESPACE): ";
	cin >> oldPass;
	if (oldPass != MainApp::nowUser->getPassword()) {
		cin.ignore();
		cout << "Password doesn't match!\n";
		return ;
	}
	cout << "Input new password: ";
	cin >> newPass;
	cin.ignore();
	cout << "\n";

	MainApp::nowUser->setPassword(newPass);
	MainApp::nowUser->save();
	cout << "Password Successfully changed!\n";
}

void MainApp::getPassword() {
	cout << "Here's your password (how can you even forgot lol):\n" <<
	MainApp::nowUser->getPassword() << "\n";
}

void MainApp::iAmAdmin() {
	if (MainApp::nowUser->getRole() == ADMIN) {
		cout << "You are already an admin!\n";
		return ;
	}
	cout << "Prove you are admin by answering this question!\n"
		 << "Who is your proffesor first name?\n";
	string answer;
	getline(cin, answer);
	cout << "\n";
	if (answer == "warsun") {
		cout << "Title case please!\n";
		return ;
	}
	if(answer == "Warsun") {
		MainApp::nowUser->setRole(ADMIN);
		MainApp::nowUser->save();
		cout << "You are now an admin!\n";
		return ;
	}
	cout << "You are not admin!\n";
}

void MainApp::deposit() {
	cout << "Choose the amount to deposit (NUMBERS ONLY): ";
	int amount; string _amount;
	cin >> _amount;
	amount = stoi(_amount);
	cin.ignore();
	cout << "\n";
	if(Finance::deposit(MainApp::nowUser, amount)){
		cout << "Rp" << amount << " has successfully deposited!\n";
	} else {
		cout << "Failed to deposit Rp" << amount << "!\n";
	}
}

void MainApp::whatsMyID() {
	cout << 
	"-----------------------------\n"
	"ID: " << MainApp::nowUser->getUserID() << "\n" <<
	"Role: " << User::formatRole(MainApp::nowUser->getRole()) << "\n" <<
	"Username: " << MainApp::nowUser->username << "\n" <<
	"Email: " << MainApp::nowUser->email << "\n" <<
	"Region: " << MainApp::nowUser->region << "\n";
}

void MainApp::logOut() {
	cout << "Are you sure you want to log out? (y/N)\n";
	string validation;
	getline(cin, validation);
	cout << "\n";

	if (validation == "y") {
		cout << "Logging Out\n";
		delete MainApp::nowUser;
		MainApp::nowUser = new User();
		return ;
	}
	cout << "Cancelled logging out!\n";
}