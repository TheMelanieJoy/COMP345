#include "stdafx.h"
#include "Badge.h"
#include <string>
using namespace std;

Badge::Badge() {
	name = "";
	raceTokens = 0;
}

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

Berserk::Berserk() : Badge(std::string("Berserk"), 4) {
}

Bivouacking::Bivouacking() : Badge(std::string("Bivouacking"), 5) {
}

DragonMaster::DragonMaster() : Badge(std::string("Dragon Master"), 5) {
    
}

Fortified::Fortified() : Badge(std::string("Fortified"), 3) {
    
}

Heroic::Heroic() : Badge(std::string("Heroic"), 5) {
    
}