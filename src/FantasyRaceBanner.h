#pragma once
#define FANTASYRACEBANNER_H

#include "stdafx.h"
#include <string>
using namespace std;

class FantasyRaceBanner {
private:
	const char* name;
    int raceTokens;
public:
	FantasyRaceBanner();
	FantasyRaceBanner(const char*, int);
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

class Giants : public FantasyRaceBanner {
private:

public:
	Giants();
};

class Halflings : public FantasyRaceBanner {
private:
    int holes_in_the_ground = 2;
public:
	Halflings();
};

class Humans : public FantasyRaceBanner {
private:

public:
	Humans();
};

class Orcs : public FantasyRaceBanner {
private:

public:
	Orcs();
};

class Ratmen : public FantasyRaceBanner {
private:

public:
	Ratmen();
};

class Skeletons : public FantasyRaceBanner {
private:

public:
	Skeletons();
};

class Sorcerers : public FantasyRaceBanner {
private:

public:
	Sorcerers();
};

class Tritons : public FantasyRaceBanner {
private:
	
public:
	Tritons();
};

class Trolls : public FantasyRaceBanner {
private:
    int trollLairs = 10;
public:
	Trolls();
};

class Wizards : public FantasyRaceBanner {
private:
	
public:
	Wizards();
};