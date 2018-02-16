#pragma once
#define FANTASYRACEBANNER_H

#include <string>
using namespace std;

class Badge {
private:
	string name;
    int raceTokens;
public:
	Badge(string, int);
	string getName();
};

class Alchemist : Badge {
private:

public:
	Badge();
};

class Berserk : Badge {
private:

public:
	Berserk();
};

class Bivouacking : Badge {
private:
    int encampments = 5;
public:
	Bivouacking();
};

class DragonMaster : Badge {
private:
    int dragon = 1;
public:
	DragonMaser();
};

class Fortified : Badge {
private:
    int fortresses = 6;
public:
	Fortified();
};

class Heroic : Badge {
private:
    int heroes = 2;
public:
	Heroic();
};