#include "stdafx.h"
#include "Player.h"
#include <string>

Player::Player(string name) {
	this->name = name;
	victoryCoins = 5;
	race = NULL;
	declinedRace = NULL;
	badge = NULL;
	declinedBadge = NULL;
}

Player::~Player() {
	delete race;
	delete declinedRace;
	delete badge;
	delete declinedBadge;
	delete strategy;
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


int Player::getVictoryCoins() {
	return victoryCoins;
}

int Player::getBonusCoins() {
	return bonusVictoryCoins;
}

int Player::getTokens() {
	return raceTokens;
}

void Player::setVictoryCoins(int coins) {
	victoryCoins = coins;
}

void Player::setBonusCoins(int coins) {
	bonusVictoryCoins = coins;
}

void Player::setTokens(int tokens) {
	if (tokens >= 0)
		raceTokens = tokens;
}

void Player::setStrategy(Strategy *strategy) {
	this->strategy = strategy;
}


int Player::select_action(int currentTurn) {
	return strategy->select_action(currentTurn);
}

void Player::declines_race(Map* m, Deck* deck) {
	// Returns old declined race and badge to the bottom of the deck
	if (declinedRace != NULL) {
		deck->addRace(declinedRace);
		deck->addBadge(declinedBadge);
	}
	// Declines race and badge
	declinedRace = race;
	declinedBadge = badge;
	// Player has no race or badge for the rest of the turn
	race = NULL;
	badge = NULL;
	// Puts all tokens on the map in decline
	m->decline(this);
}

void Player::picks_race(FantasyRaceBanner* race, Badge* badge) {
	// Sets a new race and badge
	this->race = race;
	this->badge = badge;
	raceTokens = race->getRaceTokens() + badge->getRaceTokens();

	// Wealthy earns a bonus 7 coins for their first turn
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

	// Defenses increase the number of needed tokens
	if (m->regions.at(region).type == m->regions.at(region).MOUNTAIN)
		neededTokens++;
	if (m->regions.at(region).encampment)
		neededTokens++;
	if (m->regions.at(region).fortress)
		neededTokens++;
	if (m->regions.at(region).lair)
		neededTokens++;

	// Commando requires 1 less token to conquer
	if (getBadge()->getName().compare("Commando") == 0)
		if (neededTokens > 1)
			neededTokens--;

	// Mounted requires 1 less token to conquer hills and farmlands
	if (getBadge() != NULL && getBadge()->getName().compare("Mounted") == 0)
		if (m->regions.at(region).type == m->regions.at(region).HILL ||
			m->regions.at(region).type == m->regions.at(region).FARMLAND)
			neededTokens--;

	// Underworld requires 1 less token to conquer caverns
	if (getBadge() != NULL && getBadge()->getName().compare("Underworld") == 0)
		if (m->regions.at(region).cavern)
			neededTokens--;

	// Giants requires 1 less token to conquer mountains
	if (getRace() != NULL && getRace()->getName().compare("Giants") == 0)
		if (m->regions.at(region).type == m->regions.at(region).MOUNTAIN)
			neededTokens--;

	if (neededTokens < 1)
		neededTokens = 1;

	int roll = 0;
	bool rolled = false;

	// Berserk can roll the die before a conquest
	if (getBadge()->getName().compare("Berserk") == 0)
		roll = dice->roll();
	else if(raceTokens < neededTokens) {
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
			if (getRace()->getName().compare("Orcs") == 0)
				setBonusCoins(bonusVictoryCoins + 1);
			if (getBadge()->getName().compare("Pillaging") == 0)
				setBonusCoins(bonusVictoryCoins + 1);

			// Skeletons don't earn bonus coins, but utilize the method for their own skill
			if (m->regions.at(region).owner->getRace() != NULL && m->regions.at(region).owner->getBadge() != NULL &&
				getRace()->getName().compare("Skeletons") == 0) {

				setBonusCoins(bonusVictoryCoins + 1);
			}
			// Elves get back all of their tokens when their region has been conquered by an enemy
			if (m->regions.at(region).owner->getRace() != NULL && m->regions.at(region).owner->getRace()->getName().compare("Elves") == 0)
				m->regions.at(region).owner->setTokens(m->regions.at(region).owner->raceTokens + m->regions.at(region).tokens);
			// Previous owner gets back all but one token from their captured region
			else
				m->regions.at(region).owner->setTokens(m->regions.at(region).owner->raceTokens + m->regions.at(region).tokens - 1);
		}

		m->regions.at(region).owner = this;
		m->regions.at(region).decline = false;

		
		if (!rolled) {
			// Berserk may require less tokens for conquer depending on die roll outcome
			if (m->regions.at(region).owner->getBadge() != NULL && getBadge()->getName().compare("Berserk") == 0) {
				neededTokens -= roll;
				if (neededTokens < 1)
					neededTokens = 1;
			}
			m->regions.at(region).tokens = neededTokens;
			raceTokens -= neededTokens;
		}
		else {
			m->regions.at(region).tokens = raceTokens;
			setTokens(0);
		}

		// Trolls place a lair on each occupied region
		if (race->getName().compare("Trolls") == 0) {
			if (!m->regions.at(region).lair && race->getDefense() > 0) {
				m->regions.at(region).lair = true;
				race->setDefense(race->getDefense() - 1);
			}
		}

		// Halflings place a hole-in-the-ground on their first 2 occupied regions
		if (race->getName().compare("Halflings") == 0) {
			if (!m->regions.at(region).hole && race->getDefense() > 0) {
				m->regions.at(region).hole = true;
				race->setDefense(race->getDefense() - 1);
			}
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
		// Player earns one victory coin for each region they own
		if (region.owner == this) {
			points += 1;
			// Merchant gains extra coin for each region occupied
			if (getBadge() != NULL && getBadge()->getName().compare("Merchant") == 0)
				setBonusCoins(bonusVictoryCoins + 1);

			// Hill earns an extra victory coin for each hill occupied
			if (getBadge() != NULL && getBadge()->getName().compare("Hill") == 0)
				if (region.type == region.HILL)
					setBonusCoins(bonusVictoryCoins + 1);

			// Humans earn an extra victory coin for each farmland occupied
			if (getRace() != NULL && getRace()->getName().compare("Humans") == 0)
				if (region.type == region.FARMLAND)
					setBonusCoins(bonusVictoryCoins + 1);

			// Forest earns an extra victory coin for each forest occupied
			if (getBadge() != NULL && getBadge()->getName().compare("Forest") == 0)
				if (region.type == region.FOREST)
					setBonusCoins(bonusVictoryCoins + 1);
			
			// Swamp earns an extra victory coin for each swamp occupied
			if (getBadge() != NULL && getBadge()->getName().compare("Swamp") == 0)
				if (region.type == region.SWAMP)
					setBonusCoins(bonusVictoryCoins + 1);

			// Wizards earn an extra victory coin for each magic region occupied
			if (getBadge() != NULL && getBadge()->getName().compare("Fortified") == 0)
				if (region.fortress)
					setBonusCoins(bonusVictoryCoins + 1);

			// Wizards earn an extra victory coin for each magic region occupied
			if (getRace() != NULL && getRace()->getName().compare("Wizards") == 0)
				if (region.magic)
					setBonusCoins(bonusVictoryCoins + 1);
		}
	}

	victoryCoins += points;
	victoryCoins += bonusVictoryCoins;

	return points;
}