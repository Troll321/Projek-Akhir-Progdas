#ifndef TRANSACTION_CLASS
#define TRANSACTION_CLASS

#define RENTAL_LIMIT 1
#define FINE_RATE 1
#define FINE_PRICE 1000
#define RENTAL_PRICE 5000

#include "MainApp.h"
#include "Date.h"

class Transaction {
private:
	int transactionID = 0;
	int userID = 0;
	Date expireDate, startDate, retrieveDate;
	STATUS status;

public:
	Transaction();

	Transaction(int uID);

	int getUserID();

	int getTransactionID();

	Date getExpireDate();

	Date getStartDate();

	Date getRetrieveDate();

	STATUS getStatus();

	bool retrieve(User* user);

	string getPrintable(bool isLong);

	void save();

	void populate(int tID);
};

#endif