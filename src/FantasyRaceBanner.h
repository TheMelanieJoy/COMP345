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
	int getRaceTokens();
};

class Amazons : public FantasyRaceBanner {
private:

public:
	Amazons();
};

class Dwarves : public FantasyRaceBanner {
private:

public:
	Dwarves();
};

class Elves : public FantasyRaceBanner {
private:

public:
	Elves();
};

class Ghouls : public FantasyRaceBanner {
private:

public:
	Ghouls();
};

class Halflings : public FantasyRaceBanner {
private:
    int holes_in_the_ground = 2;
public:
	Halflings();
};

class Trolls : public FantasyRaceBanner {
private:
    int trollLairs = 10;
public:
	Trolls();
};