#include <string>
#include <ctime>
#include <chrono>
#include <iostream>
#include "Date.h"

using namespace std;

int Date::MAX[] = {6, 30, 11, 9999, 59, 59};
DATE_PART Date::next[] = {DATE, MONTH, YEAR, YEAR, DAY, MINUTE};
DATE_PART Date::bef[] = {DATE, HOUR, DATE, MONTH, MINUTE, MINUTE};

bool Date::operator< (Date& b) {
	DATE_PART part = YEAR;
	while(true) {
		if (this->date[part] < b.date[part]) {
			return true;
		} else if(this->date[part] > b.date[part]) {
			return false;
		} else {
			if (part == MINUTE) { return false; }
			part = Date::bef[part];
		}
	}
	return false;
}

int Date::operator- (Date& b) {
	int output = (this->date[YEAR]- b.date[YEAR])*8760*60
	+ (this->date[MONTH] - b.date[MONTH])*730*60
	+ (this->date[DATE] - b.date[DATE])*24*60
	+ (this->date[HOUR] - b.date[HOUR])*60
	+ (this->date[MINUTE] - b.date[MINUTE])
	;
	return output;
}

Date::Date() {}

Date::Date(bool now) {
	// Get Now Date
	time_t t = time(0);
	tm* tm = localtime(&t);
	this->date[DAY] = tm->tm_wday;
	this->date[DATE] = tm->tm_mday;
	this->date[MONTH] = tm->tm_mon;
	this->date[YEAR] = tm->tm_year + 1900;
	this->date[HOUR] = tm->tm_hour;
	this->date[MINUTE] = tm->tm_min;
}

void Date::increment(DATE_PART part, unsigned int amount) {
	if (part == DATE || part == DAY) {
		this->date[DATE] += amount;
		this->date[DAY] += amount;
		this->date[DAY] %= Date::MAX[part]+1;
		part = DATE;
	} else {
		this->date[part] += amount;
	}

	while(this->date[part] > Date::MAX[part]) {
		this->date[part] %= Date::MAX[part]+1;
		part = Date::next[part];
		amount = 1;

		if (part == DATE || part == DAY) {
			this->date[DATE] += amount;
			this->date[DAY] += amount;
			this->date[DAY] %= Date::MAX[part]+1;
			part = DATE;
		} else {
			this->date[part] += amount;
		}
	}
}

Date::Date(string saveString) {
	this->populate(saveString);
}

void Date::populate(string saveString) {
	for (int i = 0; i < DATE_LEN; ++i) {
		int itr = 2;
		if (i == YEAR) {itr = 4;}

		string now = "";
		while(itr--) {
			now += saveString.back();
			saveString.pop_back();
		}
		(this->date)[i] = stoi(now);
	}
}

string Date::day(int day) {
	switch (day) {
		case 0:
			return "Monday";
		case 1:
			return "Tuesday";
		case 2:
			return "Wednesday";
		case 3:
			return "Thursday";
		case 4:
			return "Friday";
		case 5:
			return "Saturday";
		case 6:
			return "Sunday";
	}
	return "";
}

string Date::month(int month) {
	switch(month) {
	case 0:
		return "January";
	case 1:
		return "February";
	case 2:
		return "March";
	case 3:
		return "April";
	case 4:
		return "May";
	case 5:
		return "June";
	case 6:
		return "July";
	case 7:
		return "August";
	case 8:
		return "September";
	case 9:
		return "October";
	case 10:
		return "November";
	case 11:
		return "Desember";
	}
	return "";
}

string Date::pad(int input, DATE_PART part) {
	string out = to_string(input);
	int len = 2;
	if (part == YEAR) {len = 4;}
	while(out.size() < len) {out = "0"+out;}
	return out;
}

string Date::getPrintable(bool isLong) {
	string output = "";
	int len = 3;
	if (isLong) {len = MAX_MONTH_LEN;}
	output += Date::day(this->date[DAY]).substr(0,len) + ", ";
	output += to_string(this->date[DATE]) + " ";
	output += Date::month(this->date[MONTH]).substr(0,len) + " ";
	output += to_string(this->date[YEAR]) + " ";
	output += Date::pad(this->date[HOUR], HOUR) + ":";
	output += Date::pad(this->date[MINUTE], MINUTE);

	return output;
}

string Date::getSave() {
	string output = "";
	for (int i = DATE_LEN-1; i >= 0; --i) {
		string now = Date::pad(this->date[i], (DATE_PART)i);
		for (int j = (int)now.size()-1; j >= 0; --j) {
			output.push_back(now[j]);
		}
	}
	return output;
}