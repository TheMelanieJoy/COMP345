#include "stdafx.h"
#include "Badge.h"
#include <string>
using namespace std;

Badge::Badge() {
	name = "";
	raceTokens = 0;
}

Badge::Badge(const char* name, int raceTokens) {
	this->name = name;
    this->raceTokens = raceTokens;
}

string Badge::getName() {
	return name;
}

int Badge::getRaceTokens() {
	return raceTokens;
}

Alchemist::Alchemist() : Badge("Alchemist", 4) {
}

Berserk::Berserk() : Badge("Berserk", 4) {
}

Bivouacking::Bivouacking() : Badge("Bivouacking", 5) {
}

Commando::Commando() : Badge("Commando", 4) {
}

Diplomat::Diplomat() : Badge("Diplomat", 5) {
}

DragonMaster::DragonMaster() : Badge("Dragon Master", 5) {
}

Flying::Flying() : Badge("Flying", 5) {
}

Forest::Forest() : Badge("Forest", 4) {
}

Fortified::Fortified() : Badge("Fortified", 3) {
}

Heroic::Heroic() : Badge("Heroic", 5) {
}

Hill::Hill() : Badge("Hill", 4) {
}

Merchant::Merchant() : Badge("Merchant", 2) {
}

Mounted::Mounted() : Badge("Mounted", 5) {
}

Pillaging::Pillaging() : Badge("Pillaging", 5) {
}

Seafaring::Seafaring() : Badge("Seafaring", 5) {
}

Spirit::Spirit() : Badge("Spirit", 5) {
}

Stout::Stout() : Badge("Stout", 4) {
}

Swamp::Swamp() : Badge("Swamp", 4) {
}

Underworld::Underworld() : Badge("Underworld", 5) {
}

Wealthy::Wealthy() : Badge("Wealthy", 4) {
}