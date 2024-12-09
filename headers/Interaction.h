#ifndef INTERACTION_CLASS
#define INTERACTION_CLASS

#include <string>
#include "MainApp.h"
#include "Date.h"
using namespace std;

class Interaction {
private:
	STATUS type;
	int postID, userID, transactionID, interactionID;
	Date date;

public:
	Interaction();

	Interaction(STATUS type, int postID, int userID, int transactionID);

	int getUserID();

	int getPostID();

	int getTransactionID();

	int getInteractionID();

	STATUS getType();

	Date getDate();

	void updateTransactionState();

	void save();

	void populate(int tID);

	string getPrintable(bool isLong);
};

#endif