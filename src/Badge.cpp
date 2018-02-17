#include "stdafx.h"
#include "Badge.h"
#include <string>
using namespace std;

Badge::Badge(string name, int raceTokens) {
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

DragonMaster::DragonMaster() : Badge("Dragon Master", 5) {
    
}

Fortified::Fortified() : Badge("Fortified", 3) {
    
}

Heroic::Heroic() : Badge("Heroic", 5) {
    
}