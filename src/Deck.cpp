#include "stdafx.h"
#include "FantasyRaceBanner.h"
#include "Badge.h"
#include "Deck.h"
#include <algorithm>
#include <ctime>
#include <iostream>
using std::cout;

Deck::Deck() {
    addRace(new Amazons());
    addRace(new Dwarves());
    addRace(new Elves());
    addRace(new Ghouls());
    addRace(new Giants());
    addRace(new Halflings());
    addRace(new Humans());
    addRace(new Orcs());
    addRace(new Ratmen());
    addRace(new Skeletons());
    addRace(new Sorcerers());
    addRace(new Tritons());
    addRace(new Trolls());
    addRace(new Wizards());
    
    addBadge(new Alchemist());
    addBadge(new Berserk());
    addBadge(new Bivouacking());
    addBadge(new Commando());
    addBadge(new Diplomat());
    addBadge(new DragonMaster());
    addBadge(new Flying());
    addBadge(new Forest());
    addBadge(new Fortified());
    addBadge(new Heroic());
    addBadge(new Hill());
    addBadge(new Merchant());
    addBadge(new Mounted());
    addBadge(new Pillaging());
    addBadge(new Seafaring());
    addBadge(new Spirit());
    addBadge(new Stout());
    addBadge(new Swamp());
    addBadge(new Underworld());
    addBadge(new Wealthy());

	srand(time(NULL));
    std::random_shuffle(races.begin(), races.end());
	std::random_shuffle(badges.begin(), badges.end());
}

Deck::~Deck() {
	for (auto race : races)
		delete race;

	for (auto badge : badges)
		delete badge;
}

void Deck::addRace(FantasyRaceBanner* race) {
    races.push_back(race);
}

void Deck::addBadge(Badge* badge) {
    badges.push_back(badge);
}

void Deck::removeRace(int raceIndex) {
 	races.erase(races.begin() + raceIndex);   
}

void Deck::removeBadge(int badgeIndex) {
 	badges.erase(badges.begin() + badgeIndex);   
}

FantasyRaceBanner* Deck::getRace(int raceIndex) {
	return races.at(raceIndex);
}

Badge* Deck::getBadge(int badgeIndex) {
	return badges.at(badgeIndex);
}