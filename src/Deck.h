#pragma once

#include "stdafx.h"
#include "FantasyRaceBanner.h"
#include <vector>

/*
* Contains the stacks of race banners and badges that the user may take from
*/
class Deck {
private:
	/* Contains all races that can be drawn by a player */
    vector<FantasyRaceBanner*> races;
	/* Contains all badges that can be drawn by a player */
	vector<Badge*> badges;
public:
	/** Default constructor*/
	Deck();
	/** Destructor */
	~Deck();
	/**
	* Adds a race to the deck
	* @param FantasyRaceBanner* - A pointer to a race to be added to the deck
	*/
	void addRace(FantasyRaceBanner*);
	/**
	* Adds a badge to the deck
	* @param Badge* - A pointer to a badge to be added to the deck
	*/
    void addBadge(Badge*);
	/**
	* Removes a race from the deck
	* @param int - The index of the race to remove
	*/
    void removeRace(int);
	/**
	* Removes a badge from the deck
	* @param int - The index of the badge to remove
	*/
    void removeBadge(int);
	/**
	* Returns a pointer to the race object, given its index
	* @param int - The index of the returned badge 
	* @return A pointer to the selected race object
	*/
	FantasyRaceBanner* getRace(int);
	/**
	* Returns a pointer to the badge object, given its index
	* @param int - The index of the returned badge
	* @return A pointer to the selected badge object
	*/
	Badge* getBadge(int);
};