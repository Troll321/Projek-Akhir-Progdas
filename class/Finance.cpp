#include <iostream>
#include "Finance.h"
#include "User.h"
#include "Payment.h"
#include "Date.h"

using namespace std;

bool Finance::makePayment(User* user, int nominal) {
	cout << "----------------------------------------------------------------\n";
	cout << "Are you sure you want to pay Rp" << nominal << "? (y/N)\n";
	cout << "----------------------------------------------------------------\n";
	string input;
	getline(cin, input);
	cout << "\n";

	if (input == "y") {
		// Create payment
		if (user->getBalance() < nominal) {
			cout << "Sorry your balance is below the nominal!\n"
				 << "Balance: Rp" << user->getBalance() << "\n";
			return false;
		}
		Payment payment(user->getUserID(), nominal, OUT, "Rental");
		user->addPayment(payment.getPaymentID());
		user->updateBalance(nominal, OUT);
		user->save();

		cout << "Payment success!\n";
		return true;
	}

	cout << "Payment failed!\n";
	return false;
}

bool Finance::deposit(User* user, int nominal) {
	cout << "----------------------------------------------------------------------\n";
	cout << "Are you sure you want to deposit Rp" << nominal << "? (y/N)\n";
	cout << "----------------------------------------------------------------------\n";

	string input;
	getline(cin, input);
	cout << "\n";

	if (input == "y") {
		// Create payment
		Payment payment(user->getUserID(), nominal, IN, "Deposit");
		user->addPayment(payment.getPaymentID());
		user->updateBalance(nominal, IN);
		user->save();

		cout << "Deposit success!\n";
		return true;
	}

	cout << "Deposit failed!\n";
	return false;
}