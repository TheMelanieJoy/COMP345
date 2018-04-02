#pragma once

#include "stdafx.h"
#include "Strategy.h"
#include "Map.h"
#include <tuple>
class Map;
class Strategy;

class Player {
private:
	string name;
    int victoryCoins;
	FantasyRaceBanner* race;
	FantasyRaceBanner* declinedRace;
	Badge* badge;
    Badge* declinedBadge;
	int raceTokens;
	Strategy* strategy;

public:
	Player(string);
	string getName();
	int getVictoryCoins();
	FantasyRaceBanner* getRace();
	Badge* getBadge();
	int currentTokens();
    void add_coins(int);
	void picks_race(FantasyRaceBanner*, Badge*);
	int abandons(Map*, vector<size_t>*);
	int expands(Map*, vector<size_t>*);
	bool conquers(Map*, size_t, Dice*);
	std::tuple<int, int> redeploys(Map*, vector<size_t>*);
	int scores(Map*);
	void declines_race(Map*, Deck*);
	void addTokens(int);
	void setTokens(int);
	void set_strategy(Strategy*);
	int select_action(int);
};