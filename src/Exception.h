#include <iostream>
#include <exception>

using namespace std;

class IllegalInputException : public exception {
public:
	IllegalInputException() {}
	~IllegalInputException() {}
	const char* what() const throw() {
		return "IllegalInputException: Input cannot be accepted\n";
	}
};