#pragma once

#include "stdafx.h"
#include <string>
using namespace std;

/**
* The badge is a propriety that defines special skills granted to a player
*/
class Badge {
private:
	/** The badge's name */
	const char* name;
	/** The badge's token value */
    int raceTokens;
	/* The badge's defense tokens (i.e. fortresses, encampments) */
	int defense;
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
	/**
	* Returns defenses
	* @return The badges's number of defense tokens available
	*/
	int getDefense();
	/**
	* Sets defenses to a given value
	* @param The badge's new number of defense tokens available
	*/
	void setDefense(int);
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

/**
* Skill: You may use the Reinforcement die before each of your conquests
*/
class Berserk : public Badge {
private:

public:
	Berserk();
};

/**
* Skill: Deploy the 5 Encampment tokens in any of your Region(s), during your Troop Redeployment phase. 
*/
class Bivouacking : public Badge {
private:

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

/**
* Skill: You may conquer any Region of the map except Seas and Lakes.
*/
class Flying : public Badge {
private:

public:
	Flying();
};

/**
* Skill: Collect 1 bonus Victory coin for each Forest Region you occupy at turn's end.
*/
class Forest : public Badge {
private:

public:
	Forest();
};

/**
* Skill: Once per turn, as long as your Fortified Race is active, you may place 1 Fortress in a Region you occupy.
*/
class Fortified : public Badge {
private:

public:
	Fortified();
};

class Heroic : public Badge {
private:
    int heroes = 2;
public:
	Heroic();
};

/**
* Skill: Collect 1 bonus Victory coin for each Hill Region you occupy at turn's end.
*/
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

/**
* Skill: You may conquer any Hill or Farmland Region with 1 less Race token than normal.
*/
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

/**
* Skill: As long as your Seafaring race is active, you may conquer the Seas and the Lake.
*/
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

/**
* Skill: You may go In Decline at the end of a regular turn of conquests, after scoring.
*/
class Stout : public Badge {
private:

public:
	Stout();
};

/**
* Skill: Collect 1 bonus Victory coin for each Swamp Region you occupy at turn's end.
*/
class Swamp : public Badge {
private:

public:
	Swamp();
};

/**
* Skill: You may conquer any Region with a Cavern with 1 less Race token than normal.
*/
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