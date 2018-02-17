#include "stdafx.h"
#include "Player.h"
#include "Dice.h"
#include <string>
using namespace std;

Player::Player(string name) {
	this->name = name;
	victoryCoins = 5;
	badge = NULL;
	declinedBadge = NULL;
	race = NULL;
	declinedRace = NULL;
}

string Player::getName() {
	return name;
}

void Player::add_coins(int coins) {
    victoryCoins += coins;
}

void Player::picks_race(FantasyRaceBanner race, Badge badge) {
	this->race = &race;
	this->badge = &badge;
	raceTokens = race.getRaceTokens() + badge.getRaceTokens();
}

bool Player::conquers() {
	/*
	//Add region to function's parameter?
	int neededTokens = region.tokens() + 2;		//tokens() refers to the total tokens present on map (e.g. enemies, lost tribes, mountains)
	if(raceTokens >= neededTokens) {		
		//Return 1 token to old conquerer
		region.setConquerer(player.getName());		//Yay victory
		raceTokens -= neededTokens;
		return true;
	}
	else {
		int totalTokens = player.raceTokens() + roll();
		if(totalTokens >= neededTokens) {
			//Return 1 token to old conquerer
			region.setConquerer(player.getName());		//Yay victory
			raceTokens = 0;
			return true;
		}
		else {
			return false;
		}
	}
	*/

	return true;		//Placeholder return value
}

void Player::scores() {
    /*
	for(Region region : vector<Regions> map {		//Maybe add vector in this function's parameter?
		if(region.getConquerer().compare(player.getName())
			victoryCoins += 1;
	}
	*/
}