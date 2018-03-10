#include "stdafx.h"
#include "Player.h"
#include "Dice.h"
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

bool Player::conquers(Map m, size_t region) {
	//Add region to function's parameter?
	int neededTokens = m.regions.at(region).tokens + 2;		//tokens() refers to the total tokens present on map (e.g. enemies, lost tribes, mountains)

	if(raceTokens >= neededTokens) {		
		//Return 1 token to old conquerer
		m.regions.at(region).owner = getName();		//Yay victory
		raceTokens -= neededTokens;
		return true;
	}
	else {
		int totalTokens = raceTokens + roll();
		if(totalTokens >= neededTokens) {
			//Return 1 token to old conquerer
			m.regions.at(region).owner = getName();		//Yay victory
			raceTokens = 0;
			return true;
		}
		else {
			return false;
		}
	}
}

void Player::scores(Map m) {
	for(const auto region : m.regions) {		//Maybe add vector in this function's parameter?
		if(region.owner.compare(getName()))
			victoryCoins += 1;
	}
}

void Player::declines_race(Deck* deck) {
	//Returns old declined race and badge to the bottom of the deck
	if (declinedRace != NULL) {
		deck->addRace(declinedRace);
		deck->addBadge(declinedBadge);
	}
	declinedRace = race;
	race = NULL;
}