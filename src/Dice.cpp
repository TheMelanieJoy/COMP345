#include "stdafx.h"
#include "Dice.h"
#include <ctime>
#include <iostream>
using namespace std;

int roll() {
    srand(time(0));
    int dieValue = rand() % 6 + 1;
    //3 die faces are blank
    if(dieValue > 3)
	   dieValue = 0;

    cout << "You rolled a " << dieValue << "." << endl;
	return dieValue;
}