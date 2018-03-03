#pragma once
#define DECK_H

#include "stdafx.h"
#include "FantasyRaceBanner.h"
#include "Badge.h"
#include <vector>

class Deck {
private:
    vector<FantasyRaceBanner> races;
    vector<Badge> badges;
public:
	Deck();
	void addRace(FantasyRaceBanner);
    void addBadge(Badge);
    void removeRace(int);
    void removeBadge(int);
	FantasyRaceBanner getRace(int);
	Badge getBadge(int);
    void displayAvailableRaces();
};