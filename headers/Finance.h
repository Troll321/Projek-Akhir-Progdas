#ifndef FINANCE_CLASS
#define FINANCE_CLASS

#include "User.h"

class Finance {
public:
	static bool makePayment(User* user, int nominal);
	static bool deposit(User* user, int nominal);
};

#endif