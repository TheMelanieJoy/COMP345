#include "FantasyRaceBanner.h"

#include <string>
using namespace std;

FantasyRaceBanner::FantasyRaceBanner(string name, raceTokens) {
	this->name = name;
    this->raceTokens;
}

string FantasyRaceBanner::getName() {
	return name;
}

Amazons::Amazons() : FantasyRaceBanner("Amazons", 6) {
}

Dwarves::Dwarves() : FantasyRaceBanner("Dwarves", 3) {
}

Elves::Elves() : FantasyRaceBanner("Elves", 6) {
}