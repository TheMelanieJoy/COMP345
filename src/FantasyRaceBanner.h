#pragma once

#include "stdafx.h"
#include <string>
using namespace std;

class FantasyRaceBanner {
private:
	/* The race's name */
	const char* name;
	/* The race's token value */
    int raceTokens;
public:
	/**
	* Default constructor
	*/
	FantasyRaceBanner();
	/**
	* Constructor
	* @param const char* - The race's name
	* @param int - The race's token value
	*/
	FantasyRaceBanner(const char*, int);
	/**
	* Returns name
	* @return The race's name
	*/
	string getName();
	/**
	* Returns raceTokens
	* @return The race's token value
	*/
	int getRaceTokens();
};

/* Subclasses for each race banner in the game */

/**
* Skill: Four of your Amazon tokens may only be used for conquest
*/
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

/**
* Skill: When the enemy conquers one of your Regions, keep all your Elf tokens in hand for redeployment at the end of the current player's turn
*/
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

/** 
* Skill: Each not empty Region your Orcs conquered this turn is worth 1 bonus Victory coin, at the end of your turn.
*/
class Orcs : public FantasyRaceBanner {
private:

public:
	Orcs();
};

/**
* Skill: No Race benefit; their sheer number of tokens is enough!
*/
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