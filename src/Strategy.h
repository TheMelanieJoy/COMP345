#pragma once

#include "Player.h"
#include "Map.h"
#include "Dice.h"
#include <tuple>
class Player;
class Map;

class Strategy {
protected:
	Player * player;
public:
	Strategy(Player*);
	virtual int select_action(int) = 0;
	virtual int abandons(Map*, vector<size_t>*) = 0;
	virtual int expands(Map*, vector<size_t>*) = 0;
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