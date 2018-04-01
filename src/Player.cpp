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

bool Player::conquers(Map* m, size_t region, Dice* dice) {
	//Add region to function's parameter?
	int neededTokens = m->regions.at(region).tokens + 2;		//tokens() refers to the total tokens present on map (e.g. enemies, lost tribes, mountains)

	if (m->regions.at(region).mountain)
		neededTokens++;

	if(raceTokens >= neededTokens) {
		cout << "More than enough tokens \n";
		//Return 1 token to old conquerer
		if (m->regions.at(region).owner)
			m->regions.at(region).owner->addTokens(m->regions.at(region).tokens - 1);

		m->regions.at(region).owner = this;		//Yay victory
		m->regions.at(region).tokens = neededTokens;
		m->regions.at(region).decline = false;
		cout << m->regions.at(region).owner << endl;
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

			m->regions.at(region).owner = this;		//Yay victory
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

int Player::scores(Map * m) {
	int points = 0;

	for(const auto region : m->regions) {		//Maybe add vector in this function's parameter?
		if(region.owner == this)
			points += 1;
	}

	victoryCoins += points;
	//cout << "Won " << points << " coins. Now you have " << victoryCoins << " coins.\n";

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
