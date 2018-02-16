#include "FantasyRaceBanner.h"

#include <string>
using namespace std;

Badge::Badge(string name, raceTokens) {
	this->name = name;
    this->raceTokens;
}

string Badge::getName() {
	return name;
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