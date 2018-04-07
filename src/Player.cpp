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

	if (badge->getName().compare("Wealthy") == 0)
		setBonusCoins(bonusVictoryCoins + 7);
}

int Player::abandons(Map* map, vector<size_t>* regions) {
	return strategy->abandons(map, regions);
}

int Player::expands(Map* map, vector<size_t>* regions) {
	return strategy->expands(map, regions);
}

bool Player::conquers(Map* m, size_t region, Dice* dice) {
	int neededTokens = m->regions.at(region).tokens + 2;

	// Commando requires 1 less token to conquer
	if (getBadge()->getName().compare("Commando") == 0)
		if (neededTokens > 1)
			neededTokens--;

	if (m->regions.at(region).mountain)
		neededTokens++;

	int roll = 0;
	bool rolled = false;
	if(raceTokens < neededTokens) {
		if (m->regions.at(region).tokens == 0)
			return false;
		 roll = dice->roll();		
		 rolled = true;
	}

	int totalTokens = raceTokens + roll;
	if (totalTokens >= neededTokens) {
		// Return all but 1 token to old conquerer EXCEPT if the old conquerer is an elf, in which case, return all their tokens
		if (m->regions.at(region).owner) {
			// Orcs and Pillaging earn 1 bonus coin for every non-empty region conquered that turn
			// Skeletons don't earn bonus coins, but utilize the method for their own skill
			if (getRace()->getName().compare("Orcs") == 0 ||
				getRace()->getName().compare("Skeletons") == 0 ||
				getBadge()->getName().compare("Pillaging") == 0) {

				setBonusCoins(bonusVictoryCoins + 1);
			}
			if (m->regions.at(region).owner->getRace() != NULL && m->regions.at(region).owner->getRace()->getName().compare("Elves") == 0)
				m->regions.at(region).owner->addTokens(m->regions.at(region).tokens);
			else
				m->regions.at(region).owner->addTokens(m->regions.at(region).tokens - 1);
		}

		m->regions.at(region).owner = this;
		m->regions.at(region).decline = false;

		if (!rolled) {
			m->regions.at(region).tokens = neededTokens;
			raceTokens -= neededTokens;
		}
		else {
			m->regions.at(region).tokens = raceTokens;
			setTokens(0);
		}
		return true;
	}
	else {
		return false;
	}
}

std::tuple<int, int> Player::redeploys(Map* map, vector<size_t>* regions) {
	return strategy->redeploys(map, regions);
}

int Player::scores(Map * m) {
	int points = 0;

	for(const auto region : m->regions) {
		if (region.owner == this) {
			points += 1;
			// Merchant gains extra coin for each region owned
			if (getBadge() != NULL && getBadge()->getName().compare("Merchant") == 0)
				setBonusCoins(bonusVictoryCoins + 1);
		}
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
	declinedBadge = badge;
	race = NULL;
	badge = NULL;
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

int Player::getBonusCoins() {
	return bonusVictoryCoins;
}

void Player::setBonusCoins(int coins) {
	bonusVictoryCoins = coins;
}

void Player::set_strategy(Strategy *strategy) {
	this->strategy = strategy;
}

int Player::select_action(int currentTurn) {
	return strategy->select_action(currentTurn);
}