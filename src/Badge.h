#pragma once
#define BADGE_H

#include "stdafx.h"
#include <string>
using namespace std;

class Badge {
private:
	/** The badge's name */
	const char* name;
	/** The badge's token value */
    int raceTokens;
public:
	/** Default constructor */
	Badge();
	/**
	* Constructor
	* @param const char* - The badge's name
	* @param int - The badge's token value
	*/
	Badge(const char*, int);
	/**
	* Returns the badge's name
	* @return The badge's name
	*/
	string getName();
	/**
	* Returns the badge's token value 
	* @return The badge's token value
	*/
	int getRaceTokens();
};

/* Subclasses for each badge in the game */

/**
* Skill: Collect 2 bonus Victory coins at the end of each turn your race hasn't yet gone into Decline.
*/
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

/**
* Skill: You may conquer any Region with 1 less Race token than normal. A minimum of 1 token is still required.
*/
class Commando : public Badge {
private:

public:
	Commando();
};

class Diplomat : public Badge {
private:

public:
	Diplomat();
};

class DragonMaster : public Badge {
private:
    int dragon = 1;
public:
	DragonMaster();
};

class Flying : public Badge {
private:

public:
	Flying();
};

class Forest : public Badge {
private:

public:
	Forest();
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

class Hill : public Badge {
private:

public:
	Hill();
};

/**
* Skill: Collect 1 bonus Victory coin for any Region you occupy at turn's end.
*/
class Merchant : public Badge {
private:

public:
	Merchant();
};

class Mounted : public Badge {
private:

public:
	Mounted();
};

/**
* Skill: Each non-empty Region you conquer this turn is worth 1 bonus Victory coin at turn's end.
*/
class Pillaging : public Badge {
private:

public:
	Pillaging();
};

class Seafaring : public Badge {
private:

public:
	Seafaring();
};

class Spirit : public Badge {
private:

public:
	Spirit();
};

class Stout : public Badge {
private:

public:
	Stout();
};

class Swamp : public Badge {
private:

public:
	Swamp();
};

class Underworld : public Badge {
private:

public:
	Underworld();
};

/**
* Skill: Collect 7 bonus Victory coins, once only, at the end of your first turn.
*/
class Wealthy : public Badge {
private:

public:
	Wealthy();
};