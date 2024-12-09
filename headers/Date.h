#ifndef DATE_CLASS
#define DATE_CLASS

#define DATE_LEN 6
#define MAX_MONTH_LEN 10

#include <string>

using namespace std;

enum DATE_PART {
	DAY = 0,
	DATE,
	MONTH,
	YEAR,
	HOUR,
	MINUTE
};

class Date {
public:
	// 1 = Monday
	// 1 = January
	// int day, date, month, year, hour, minute;
	int date[DATE_LEN] = {0,0,0,0,0,0};

	static int MAX[DATE_LEN];
	static DATE_PART next[DATE_LEN];
	static DATE_PART bef[DATE_LEN];
	static string day(int day);
	static string month(int month);
	static string pad(int input, DATE_PART part);

	bool operator<(Date& b);

	int operator-(Date& b);

	Date();

	Date(bool now);

	Date(string saveString);

	void populate(string saveString);

	string getPrintable(bool isLong);

	string getSave();

	void increment(DATE_PART part, unsigned int amount);
};

#endif