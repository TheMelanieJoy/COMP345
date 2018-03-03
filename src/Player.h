#pragma once
#define PLAYER_H

#include "FantasyRaceBanner.h"
#include "Badge.h"
#include "Map.h"
#include "Deck.h"

class Player {
private:
	string name;
    int victoryCoins;
	FantasyRaceBanner* race;
	FantasyRaceBanner* declinedRace;
	Badge* badge;
    Badge* declinedBadge;
	int raceTokens;

public:
	Player(string);
	string getName();
	FantasyRaceBanner* getRace();
	Badge* getBadge();
    void add_coins(int);
	void picks_race(FantasyRaceBanner, Badge);
	bool conquers(Map, size_t);
	void scores(Map);
	void declines_race(Deck*);
};