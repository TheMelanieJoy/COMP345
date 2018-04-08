// SmallWorld.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Tournament.h"
#include "Exception.h"
#include <iostream>

using std::cout;
using std::cin;

#undef max

/* Runs the application. Prompts user to select which type of tournament to run. */
int main()
{
	std::cout << "Which tournament would you like to run?" << endl
		<< "1. 2-player game" << endl
		<< "2. 3-player game" << endl
		<< "3. 4-player game" << endl
		<< "4. 5-player game" << endl;

	//Input must be between 1 and 4 inclusive
	int choice = 0;
	while (choice < 1 || choice > 4)
		try {
			if (!(cin >> choice) || (choice < 1 || choice > 4)) {
				throw IllegalInputException();
			}
		}
		catch (IllegalInputException e) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cerr << e.what();
			cout << "Enter a valid choice: ";
	}

	Tournament t(choice + 1);
	t.run();
	return 0;
}