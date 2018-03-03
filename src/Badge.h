#pragma once
#define BADGE_H

#include <string>
using namespace std;

class Badge {
private:
	const char* name;
    int raceTokens;
public:
	Badge();
	Badge(const char*, int);
	string getName();
	int getRaceTokens();
};

class Alchemist : public Badge {
private:

public:
	Alchemist();
};

class Berserk : public Badge {
private:

public:
	Berserk();
};

class Bivouacking : public Badge {
private:
    int encampments = 5;
public:
	Bivouacking();
};

class Commando : public Badge {
private:

public:
	Commando();
};

class Diplomat : public Badge {
private:

public:
	Diplomat();
};

class DragonMaster : public Badge {
private:
    int dragon = 1;
public:
	DragonMaster();
};

class Flying : public Badge {
private:

public:
	Flying();
};

class Forest : public Badge {
private:

public:
	Forest();
};

class Fortified : public Badge {
private:
    int fortresses = 6;
public:
	Fortified();
};

class Heroic : public Badge {
private:
    int heroes = 2;
public:
	Heroic();
};

class Hill : public Badge {
private:

public:
	Hill();
};

class Merchant : public Badge {
private:

public:
	Merchant();
};

class Mounted : public Badge {
private:

public:
	Mounted();
};

class Pillaging : public Badge {
private:

public:
	Pillaging();
};

class Seafaring : public Badge {
private:

public:
	Seafaring();
};

class Spirit : public Badge {
private:

public:
	Spirit();
};

class Stout : public Badge {
private:

public:
	Stout();
};

class Swamp : public Badge {
private:

public:
	Swamp();
};

class Underworld : public Badge {
private:

public:
	Underworld();
};

class Wealthy : public Badge {
private:

public:
	Wealthy();
};