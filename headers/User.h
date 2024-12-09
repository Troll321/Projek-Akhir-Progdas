#ifndef USER_CLASS
#define USER_CLASS

#include <string>
#include <vector>
#include "Payment.h"
using namespace std;

enum ROLE {
	CUSTOMER = 0,
	ADMIN = 1
};

class User {
private:
	int balance = 0;
	int userID = -1;
	ROLE role = CUSTOMER;
	string password;
	vector<int> transactions, interactions, payments;

public:
	string username, email, region;

	static bool checkUsername(string inputUsername);

	static string formatRole(ROLE role) {
		switch (role) {
		case CUSTOMER:
			return "CUSTOMER";
		case ADMIN:
			return "ADMIN";
		}
		return  "";
	}

	User();

	User(string username, string password, string email, string region);

	void populate(int uID);

	void addPayment(int payID);

	void save();

	int getUserID();

	ROLE getRole();

	void setRole(ROLE role);

	string getPassword();

	void updateBalance(int amount, FLOW flow);

	void setPassword(string newPassword);

	int checkOngoingTransaction();

	void retrieve(int pID);

	vector<int> getTransactions();

	vector<int> getInteractions();

	vector<int> getPayments();

	int getBalance();

	void deposit();

	void rental(int pID);
};

#endif