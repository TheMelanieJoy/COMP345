#pragma once
#define BADGE_H

#include <string>
using namespace std;

class Badge {
private:
	string name;
    int raceTokens;
public:
	Badge();
	Badge(string, int);
	string getName();
	int getRaceTokens();
};

class Alchemist : public Badge {
private:

public:
	Alchemist();
};

class Berserk : public Badge {
private:

public:
	Berserk();
};

class Bivouacking : public Badge {
private:
    int encampments = 5;
public:
	Bivouacking();
};

class DragonMaster : public Badge {
private:
    int dragon = 1;
public:
	DragonMaster();
};

class Fortified : public Badge {
private:
    int fortresses = 6;
public:
	Fortified();
};

class Heroic : public Badge {
private:
    int heroes = 2;
public:
	Heroic();
};