#include "stdafx.h"
#include "FantasyRaceBanner.h"
#include "Badge.h"
#include "Deck.h"
#include <algorithm>
#include <iostream>
using std::cout;

Deck::Deck() {
    addRace(Amazons());
    addRace(Dwarves());
    addRace(Elves());
    addRace(Ghouls());
    addRace(Giants());
    addRace(Halflings());
    addRace(Humans());
    addRace(Orcs());
    addRace(Ratmen());
    addRace(Skeletons());
    addRace(Sorcerers());
    addRace(Tritons());
    addRace(Trolls());
    addRace(Wizards());
    
    addBadge(Alchemist());
    addBadge(Berserk());
    addBadge(Bivouacking());
    addBadge(Commando());
    addBadge(Diplomat());
    addBadge(DragonMaster());
    addBadge(Flying());
    addBadge(Forest());
    addBadge(Fortified());
    addBadge(Heroic());
    addBadge(Hill());
    addBadge(Merchant());
    addBadge(Mounted());
    addBadge(Pillaging());
    addBadge(Seafaring());
    addBadge(Spirit());
    addBadge(Stout());
    addBadge(Swamp());
    addBadge(Underworld());
    addBadge(Wealthy());
    
    std::random_shuffle(races.begin(), races.end());
	std::random_shuffle(badges.begin(), badges.end());
}

void Deck::addRace(FantasyRaceBanner race) {
    races.push_back(race);
}

void Deck::addBadge(Badge badge) {
    badges.push_back(badge);
}

void Deck::removeRace(int raceIndex) {
 	races.erase(races.begin() + raceIndex);   
}

void Deck::removeBadge(int badgeIndex) {
 	badges.erase(badges.begin() + badgeIndex);   
}

FantasyRaceBanner Deck::getRace(int raceIndex) {
	return races.at(raceIndex);
}

Badge Deck::getBadge(int badgeIndex) {
	return badges.at(badgeIndex);
}

void Deck::displayAvailableRaces() {
    for (int i = 0; i < 6; i++)
		cout << i + 1 << ". " << badges.at(i).getName() << " " << races.at(i).getName() << endl;
}