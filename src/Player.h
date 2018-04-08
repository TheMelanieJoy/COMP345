#pragma once

#include "stdafx.h"
#include "Strategy.h"
#include "Map.h"
#include "Dice.h"
#include <tuple>
class Map;
class Strategy;

class Player {
private:
	/* The player's name */
	string name;
	/* The number of victory coins in their possession */
    int victoryCoins;
	/* Bonus victory coins earned during a turn due to race and badge skills */
	int bonusVictoryCoins;
	/* The player's selected race */
	FantasyRaceBanner* race;
	/* The player's previous race */
	FantasyRaceBanner* declinedRace;
	/* The player's selected badge */
	Badge* badge;
	/* The player's previous badge */
    Badge* declinedBadge;
	/* The number of race tokens in their possession (not on the map) */
	int raceTokens;
	/* The player's automated playstyle */
	Strategy* strategy;

public:
	/**
	* Constructor
	* @param string - The player's name
	*/
	Player(string);

	/**
	* Destructor
	*/
	~Player();

	/**
	* Returns the player's name
	* @return The player's name
	*/
	string getName();
	/**
	* Returns the player's current race
	* @return The player's current race
	*/
	FantasyRaceBanner* getRace();
	/**
	* Returns the player's current badge
	* @return The player's current badge
	*/
	Badge* getBadge();
	/**
	* Returns the number of victory coins owned
	* @return The number of victory coins owned
	*/
	int getVictoryCoins();
	/**
	* Returns the number of bonus coins earned from skills
	* @return The number of bonus victory coins earned
	*/
	int getBonusCoins();
	/**
	* Returns the number of race tokens in the player's possesion
	* @return The quantity of race tokens
	*/
	int getTokens();

	/**
	* Sets victoryCoins to a new quantity
	* @param int - The player's new number of victory coins
	*/
	void setVictoryCoins(int);
	/**
	* Sets bonusVictoryCoins to a new quantity
	* @return The new number of bonus victory coins earned
	*/
	void setBonusCoins(int);
	/**
	* Sets raceTokens to a new quantity
	* @param int - The player's new number of tokens
	*/
	void setTokens(int);
	/**
	* Sets strategy
	* @param Strategy* - A pointer to a strategy
	*/
	void setStrategy(Strategy*);

	/**
	* Prompts the user to select an action to perform during their turn
	* @return 1 - Declining their race
	*	2 - Expanding their territory
	*/
	int select_action(int);
	/**
	* Puts the player's race into decline
	* @param Map* - The game map
	* @param Deck* - The stack of races and badges to put any previously decline race and badge into
	*/
	void declines_race(Map*, Deck*);
	/**
	* Sets race and badge
	* @param FanatasyRaceBanner* - The selected race
	* @param Badge* - The selected badge
	*/
	void picks_race(FantasyRaceBanner*, Badge*);
	/**
	* Allows the user to abandon any currently owned region on the map
	* @param Map* - The game map
	* @param vector<size_t>* - Contains all the regions the player owns
	* @return The index of the selected region
	*	Returns -1 if the player chooses not to abandon a region
	*/
	int abandons(Map*, vector<size_t>*);
	/**
	* Allows the user to select a region to conquer
	* @param Map* - The game map
	* @param vector<size_t>* - Contains all the regions that can be conquered
	* @return The index of the selected region
	*	Returns -1 if the player chooses not to conquer a region
	*/
	int expands(Map*, vector<size_t>*);
	/**
	* Processes the attempt to conquer a region
	* @param Map* - The game map
	* @param size_t - The index of the region to conquer
	* @param Dice* - The reinforcement die
	* @return True if the region has been conquered
	*	False otherwise
	*/
	bool conquers(Map*, size_t, Dice*);
	/**
	* Allows the user to redeploy raceTokens onto the map
	* @param Map* - The game map
	* @param vector<size_t>* - Contains all the regions that can be conquered
	* @return A pair of integers representing the index of the selected region and the number of race tokens to redeploy respectively
	*/
	std::tuple<int, int> redeploys(Map*, vector<size_t>*);
	/**
	* Awards victory coins for the number of regions owned and skill effects
	* @param Map* - The game map
	* @return The number of victory coins earned
	*/
	int scores(Map*);
};