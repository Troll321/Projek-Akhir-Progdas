#ifndef PAYMENT_CLASS
#define PAYMENT_CLASS

#include <string>
#include "Date.h"
using namespace std;

enum FLOW {
	IN = 0,
	OUT
};

class Payment {
private:
	int paymentID, userID, amount;
	FLOW flow;
	Date date;
	string metadata = "";

public:
	static string formatFlow(FLOW flow);

	Payment();

	Payment(int uID, int amount, FLOW flow, string metadata);

	int getPaymentID();

	string getPrintable(bool isLong);

	void save();

	void populate(int tID);
};

#endif