#include "stdafx.h"
#include "Player.h"
#include "Dice.h"
#include "Map.h"
#include <string>
using namespace std;

Player::Player(string name) {
	this->name = name;
	victoryCoins = 5;
	race = NULL;
	declinedRace = NULL;
	badge = NULL;
	declinedBadge = NULL;
}

string Player::getName() {
	return name;
}

int Player::getVictoryCoins() {
	return victoryCoins;
}

FantasyRaceBanner* Player::getRace() {
	return race;
}

Badge* Player::getBadge() {
	return badge;
}

void Player::add_coins(int coins) {
    victoryCoins += coins;
}

void Player::picks_race(FantasyRaceBanner* race, Badge* badge) {
	this->race = race;
	this->badge = badge;
	raceTokens = race->getRaceTokens() + badge->getRaceTokens();
}

int Player::abandons(Map* map, vector<size_t>* regions) {
	return strategy->abandons(map, regions);
}

int Player::expands(Map* map, vector<size_t>* regions) {
	return strategy->expands(map, regions);
}

bool Player::conquers(Map* m, size_t region, Dice* dice) {
	int neededTokens = m->regions.at(region).tokens + 2;

	if (m->regions.at(region).mountain)
		neededTokens++;

	if(raceTokens >= neededTokens) {
		cout << "More than enough tokens \n";
		//Return 1 token to old conquerer
		if (m->regions.at(region).owner)
			m->regions.at(region).owner->addTokens(m->regions.at(region).tokens - 1);

		m->regions.at(region).owner = this;
		m->regions.at(region).tokens = neededTokens;
		m->regions.at(region).decline = false;
		raceTokens -= neededTokens;
		return true;
	}
	else {
		cout << "Not enough tokens \n";

		if (m->regions.at(region).tokens == 0) {
			cout << "Can't use reinforcement dice on an empty region. \n";
			return false;
		}

		int roll = dice->roll();

		int totalTokens = raceTokens + roll;

		if(totalTokens >= neededTokens) {
			//Return 1 token to old conquerer
			if (m->regions.at(region).owner)
				m->regions.at(region).owner->addTokens(m->regions.at(region).tokens - 1);

			m->regions.at(region).owner = this;
			m->regions.at(region).tokens = raceTokens;
			m->regions.at(region).decline = false;
			raceTokens = 0;
			return true;
		}
		else {
			return false;
		}
	}
}

std::tuple<int, int> Player::redeploys(Map* map, vector<size_t>* regions) {
	return strategy->redeploys(map, regions);
}

int Player::scores(Map * m) {
	int points = 0;

	for(const auto region : m->regions) {
		if(region.owner == this)
			points += 1;
	}

	victoryCoins += points;

	return points;
}

void Player::declines_race(Map* m, Deck* deck) {
	//Returns old declined race and badge to the bottom of the deck
	if (declinedRace != NULL) {
		deck->addRace(declinedRace);
		deck->addBadge(declinedBadge);
	}
	declinedRace = race;
	race = NULL;
	m->decline(this);
}

void Player::addTokens(int tokens)
{
	raceTokens += tokens;
}

void Player::setTokens(int tokens)
{
	if(tokens >= 0)
		raceTokens = tokens;
}

int Player::currentTokens()
{
	return raceTokens;
}

void Player::set_strategy(Strategy *strategy) {
	this->strategy = strategy;
}

int Player::select_action(int currentTurn) {
	return strategy->select_action(currentTurn);
}