#pragma once

#include "Player.h"
#include "Map.h"
#include "Dice.h"
#include <tuple>
class Player;
class Map;

/**
* Strategy defines the algorithms used by players to make game choices based on their playstyle
*/
class Strategy {
protected:
	/**
	* The player that is using the strategy
	*/
	Player * player;
public:
	/**
	* Constructor
	* @param Player* - The player using the strategy
	*/
	Strategy(Player*);
	/**
	* An algorithm that prompts the player to either expand the territory or decline their race during following turns.
	* @param int - The current turn
	* @return 1 - Player chooses to decline
	*	2 - Player chooses to expand further
	*/
	virtual int select_action(int) = 0;
	/**
	* An algorithm that makes the player abandon a territory or not.
	* @param Map* - The game map
	* @param vector<size_t>* - The index of all regions owned by the player
	* @return The index of the region to abandon
	*	-1 if not abandoning
	*/
	virtual int abandons(Map*, vector<size_t>*) = 0;
	/**
	* An algorithm that decides whether the player should conquer a territory or not
	* @param Map* - The game map
	* @param vector<size_t>* - The index of all regions that may be conquered
	* @return The index of the region to conquer
	*	-1 if not conquering
	*/
	virtual int expands(Map*, vector<size_t>*) = 0;
	/**
	* An algorithm that decides which regions to redeploy tokens to.
	* @param Map* - The game map
	* @param vector<size_t>* - The index of all regions owned by the player
	* @return The region to redeploy to and the number of tokens to redeploy respectively
	*/
	virtual std::tuple<int, int> redeploys(Map*, vector<size_t>*) = 0;
};

class Aggressive : public Strategy {
public:
	Aggressive(Player*);
	int select_action(int) override;
	int abandons(Map*, vector<size_t>*) override;
	int expands(Map*, vector<size_t>*) override;
	std::tuple<int, int> redeploys(Map*, vector<size_t>*) override;
};

class Defensive : public Strategy {
public:
	Defensive(Player*);
	int select_action(int) override;
	int abandons(Map*, vector<size_t>*) override;
	int expands(Map*, vector<size_t>*) override;
	std::tuple<int, int> redeploys(Map*, vector<size_t>*) override;
};

class Moderate : public Strategy {
public:
	Moderate(Player*);
	int select_action(int) override;
	int abandons(Map*, vector<size_t>*) override;
	int expands(Map*, vector<size_t>*) override;
	std::tuple<int, int> redeploys(Map*, vector<size_t>*) override;
};

class Random : public Strategy {
public:
	Random(Player*);
	int select_action(int) override;
	int abandons(Map*, vector<size_t>*) override;
	int expands(Map*, vector<size_t>*) override;
	std::tuple<int, int> redeploys(Map*, vector<size_t>*) override;
};