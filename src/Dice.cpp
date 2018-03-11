#include "stdafx.h"
#include "Dice.h"
#include <ctime>
#include <iostream>
using namespace std;

Dice::Dice() {
	zeroCounter = 0;
	oneCounter = 0;
	twoCounter = 0;
	threeCounter = 0;
}

int Dice::roll() {
    srand(time(NULL));
    int dieValue = rand() % 6 + 1;
    //3 die faces are blank
    if(dieValue > 3)
	   dieValue = 0;

	//Tracks percentage value of each die roll
	switch (dieValue) {
		case 1:
			oneCounter++;
			break;
		case 2:
			twoCounter++;
			break;
		case 3:
			threeCounter++;
			break;
		default:
			zeroCounter++;
	}

    cout << "You rolled a " << dieValue << "." << endl;

	return dieValue;
}

void Dice::printRollPercentage() {
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	int totalRolls = zeroCounter + oneCounter + twoCounter + threeCounter;
	cout << (float)zeroCounter / totalRolls * 100 << "% of total rolls were 0s." << endl
		<< (float)oneCounter / totalRolls * 100 << "% of total rolls were 1s." << endl
		<< (float)twoCounter / totalRolls * 100 << "% of total rolls were 2s." << endl
		<< (float)threeCounter / totalRolls * 100 << "% of total rolls were 3s." << endl;
}