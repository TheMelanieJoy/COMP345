#pragma once
#define PLAYER_H

#include "FantasyRaceBanner.h"
#include "Badge.h"


class Player {
private:
	string name;
    int victoryCoins;
    Badge *badge;
    Badge *declinedBadge;
    FantasyRaceBanner *race;
    FantasyRaceBanner *declinedRace;
	int raceTokens;

public:
	Player(string);
	string getName();
    void add_coins(int);
	void picks_race(FantasyRaceBanner, Badge);
	bool conquers();
	void scores();
};