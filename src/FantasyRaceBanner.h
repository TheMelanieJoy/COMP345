#pragma once
#define FANTASYRACEBANNER_H

#include <string>
using namespace std;

class FantasyRaceBanner {
private:
	string name;
    int raceTokens;
public:
	FantasyRaceBanner(string, int);
	string getName();
};

class Amazons : FantasyRaceBanner {
private:

public:
	Amazons();
};

class Dwarves : FantasyRaceBanner {
private:

public:
	Dwarves();
};

class Elves : FantasyRaceBanner {
private:

public:
	Elves();
};

class Halflings : FantasyRaceBanner {
private:
    int holes_in_the_ground = 2;
public:
	Halflings();
};

class Trolls : FantasyRaceBanner {
private:
    int trollLairs = 10;
public:
	Trolls();
};