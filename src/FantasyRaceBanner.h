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
	/* The race's defense tokens (i.e. holes-in-the-ground, troll lairs) */
	int defense;
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
	/**
	* Returns defenses
	* @return The race's number of defense tokens available
	*/
	int getDefense();
	/**
	* Sets defenses to a given value
	* @param The race's new number of defense tokens available
	*/
	void setDefense(int);
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

/**
* Skill: Each Mine Region your Dwarves occupy is worth 1 bonus Victory coin, at the end of your turn.
*/
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
/**
* Skill: Your Giants may conquer a Mountain Region at a cost of 1 less Giant token than normal.
*/
class Giants : public FantasyRaceBanner {
private:

public:
	Giants();
};

/**
* Skill: Place a Hole-in-the-Ground in each of the first 2 Regions you conquer, to make them immune to enemy conquests.
*/
class Halflings : public FantasyRaceBanner {
private:

public:
	Halflings();
};

/**
* Skill: Each Farmland Region your Humans occupy is worth 1 bonus Victory coin, at the end of your turn.
*/
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

/**
* Skill: During redeployment, earn 1 new race token for every 2 non-empty Regions you conquered this turn.
*/
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

/**
* Skill: Place a Troll's Lair in each Region your Trolls occupy.
*/
class Trolls : public FantasyRaceBanner {
private:

public:
	Trolls();
};

/**
* Skill: Each Magic Region your Wizards occupy is worth 1 bonus Victory coin, at the end of your turn.
*/
class Wizards : public FantasyRaceBanner {
private:
	
public:
	Wizards();
};