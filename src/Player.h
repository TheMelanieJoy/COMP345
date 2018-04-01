#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#endif

#include "stdafx.h"
class Map;



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
	int getVictoryCoins();
	FantasyRaceBanner* getRace();
	Badge* getBadge();
	int currentTokens();
    void add_coins(int);
	void picks_race(FantasyRaceBanner*, Badge*);
	bool conquers(Map*, size_t, Dice*);
	int scores(Map*);
	void declines_race(Map*, Deck*);
	void addTokens(int);
	void setTokens(int);
};