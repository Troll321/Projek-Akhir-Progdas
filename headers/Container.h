#ifndef CONTAINER_CLASS
#define CONTAINER_CLASS

#include <string>
#include <vector>
using namespace std;

template <typename T>
class Container {
public:
	static string getPrintable(T input);

	vector<T> vec;
};

#endif