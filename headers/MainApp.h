#ifndef MAINAPP_CLASS
#define MAINAPP_CLASS

#define MAX_ID 100000
#define MAX_DATE_LEN 80
#define DELIM ' '
#define LINE_DELIM '\n'

#include <vector>
#include <string>
#include <random>
#include <chrono>
#include "User.h"

enum STATUS {
	RENTAL = 0,
	RETRIEVED
};

using namespace std;

class MainApp {
public:
	static User* nowUser;
	static mt19937 rng;
	static bool isExit;
	static unsigned int now();
	static int genID(string dbpath);
	static bool check(string dbpath, int id);
	static void printBanner();
	static void printMenu();
	static void printMenuLogin();
	static void clear();
	static void wait();
	static string formatDate(unsigned int epoch);
	static string formatStatus(STATUS status);

	static void notLoggedInUI();
	static void loggedInUI();
	static void signup();
	static void login();
	static void rental();
	static void retrieve();
	static void addPost();
	static void getTransactionsHistory();
	static void getInteractionsHistory();
	static void getUserBalance();
	static void getPostsLocation();
	static void getPostInteractions();
	static void getPaymentsHistory();
	static void checkOngoingTransaction();
	static void changePassword();
	static void getPassword();
	static void iAmAdmin();
	static void deposit();
	static void whatsMyID();
	static void aboutUs();
	static void help();
	static void logOut();
	static void exit();
};

#endif