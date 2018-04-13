#include <iostream>
#include <exception>

using namespace std;

/**
* An exception thrown if an input is invalid or out of bounds
*/
class IllegalInputException : public exception {
public:
	IllegalInputException() {}
	~IllegalInputException() {}
	const char* what() const throw() {
		return "IllegalInputException: Input cannot be accepted\n";
	}
};