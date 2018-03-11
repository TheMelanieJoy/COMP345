#pragma once
#define DICE_H

#include "stdafx.h"
#include <vector>

class Dice {
private:
	int zeroCounter;
	int oneCounter;
	int twoCounter;
	int threeCounter;
public:
	Dice();
	int roll();
	void printRollPercentage();
};