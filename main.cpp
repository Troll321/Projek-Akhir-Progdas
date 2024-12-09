#include <iostream>
#include <random>
#include <chrono>
#include "Interaction.h"
#include "MainApp.h"
#include "Payment.h"
#include "RentalPost.h"
#include "Transaction.h"
#include "User.h"

#include "Date.h"
using namespace std;

mt19937 MainApp::rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

User* MainApp::nowUser = new User();
bool MainApp::isExit = false;

int main() {
	MainApp::clear();

	while(!MainApp::isExit) {
		if (MainApp::nowUser->getUserID() == -1) {
			MainApp::notLoggedInUI();
		} else {
			MainApp::loggedInUI();
		}
		MainApp::wait();
		MainApp::clear();
	}
	return 0;
}