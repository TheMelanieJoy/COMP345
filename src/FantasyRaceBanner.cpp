#include "stdafx.h"
#include "FantasyRaceBanner.h"
#include <string>
using namespace std;

FantasyRaceBanner::FantasyRaceBanner(string name, int raceTokens) {
	this->name = name;
    this->raceTokens = raceTokens;
}

string FantasyRaceBanner::getName() {
	return name;
}

int FantasyRaceBanner::getRaceTokens() {
	return raceTokens;
}


Amazons::Amazons() : FantasyRaceBanner("Amazons", 6) {
}

Dwarves::Dwarves() : FantasyRaceBanner("Dwarves", 3) {
}

Elves::Elves() : FantasyRaceBanner("Elves", 6) {
}

Ghouls::Ghouls() : FantasyRaceBanner("Ghouls", 5) {
}

Halflings::Halflings() : FantasyRaceBanner("Halflings", 6) {
}

Trolls::Trolls() : FantasyRaceBanner("Trolls", 5) {
}