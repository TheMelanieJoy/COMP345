#include "stdafx.h"
#include "FantasyRaceBanner.h"
#include <string>
using namespace std;

FantasyRaceBanner::FantasyRaceBanner() {
	name = "";
	raceTokens = 0;
	defense = 0;
}

FantasyRaceBanner::FantasyRaceBanner(const char* name, int raceTokens) {
	this->name = name;
    this->raceTokens = raceTokens;
	defense = 0;
}

string FantasyRaceBanner::getName() {
	return name;
}

int FantasyRaceBanner::getRaceTokens() {
	return raceTokens;
}

int FantasyRaceBanner::getDefense() {
	return defense;
}

void FantasyRaceBanner::setDefense(int defense) {
	this->defense = defense;
}

Amazons::Amazons() : FantasyRaceBanner("Amazons", 6) {
}

Dwarves::Dwarves() : FantasyRaceBanner("Dwarves", 3) {
}

Elves::Elves() : FantasyRaceBanner("Elves", 6) {
}

Ghouls::Ghouls() : FantasyRaceBanner("Ghouls", 5) {
}

Giants::Giants() : FantasyRaceBanner("Giants", 6) {
}

Halflings::Halflings() : FantasyRaceBanner("Halflings", 6) {
	setDefense(2);
}

Humans::Humans() : FantasyRaceBanner("Humans", 5) {
}

Orcs::Orcs() : FantasyRaceBanner("Orcs", 5) {
}

Ratmen::Ratmen() : FantasyRaceBanner("Ratmen", 8) {
}

Skeletons::Skeletons() : FantasyRaceBanner("Skeletons", 6) {
}

Sorcerers::Sorcerers() : FantasyRaceBanner("Sorcerers", 5) {
}

Tritons::Tritons() : FantasyRaceBanner("Tritons", 6) {
}

Trolls::Trolls() : FantasyRaceBanner("Trolls", 5) {
	setDefense(10);
}

Wizards::Wizards() : FantasyRaceBanner("Wizards", 5) {
}