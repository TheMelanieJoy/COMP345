#pragma once
#define PLAYER_H

#include "FantasyRaceBanner.h"
#include "Badge.h"
#ifndef MAP
#define MAP
#include "Map.cpp"
#endif


class Player {
private:
	string name;
    int victoryCoins;
    Badge badge;
    Badge declinedBadge;
    FantasyRaceBanner race;
    FantasyRaceBanner declinedRace;
	int raceTokens;

public:
	Player(string);
	string getName();
	FantasyRaceBanner getRace();
	Badge getBadge();
    void add_coins(int);
	void picks_race(FantasyRaceBanner, Badge);
	bool conquers(Map, size_t);
	void scores(Map);
};