#include "Strategy.h"
#include <ctime>

Strategy::Strategy(Player * player) {
	this->player = player;
}

Aggressive::Aggressive(Player * player) : Strategy(player) {}

/* Aggressive player only declines if there are no tokens to redeploy.
	Returns 1 if declining or 2 if expanding. */
int Aggressive::select_action(int currentTurn) {
	if (player->getTokens() == 0)
		return 1;
	else
		return 2;
}

/* Aggressive player only abandons if they have 1 or 2 tokens left to use for conquering */
int Aggressive::abandons(Map* map, vector<size_t>* regions) {
	if (player->getTokens() > 2)
		return -1;
	else {
		//Player abandons a random region for simplicity's sake
		srand(time(NULL));
		int selectedRegion = rand() % regions->size();

		map->regions.at(regions->at(selectedRegion)).tokens = 0;
		map->regions.at(regions->at(selectedRegion)).owner = nullptr;

		return selectedRegion;
	}
}

/* Aggressive player conquers the least reinforced region.
They stop conquering once they run out of race tokens */
int Aggressive::expands(Map* map, vector<size_t>* regions) {
	int weakestRegion = 0;
	int weakestRegionTokens = map->regions.at(0).tokens;
	for (int i = 1; i < regions->size() - 1; i++) {
		int temp = map->regions.at(i).tokens;
		if (temp < weakestRegionTokens) {
			weakestRegion = i;
			weakestRegionTokens = temp;
		}
	}
	return weakestRegion;
}

/* Aggressive player puts all of their redeployable tokens into one region */
std::tuple<int, int> Aggressive::redeploys(Map* map, vector<size_t>* regions) {
	int selectedRegion = 0;
	int numberOfTokens = player->getTokens();

	player->setTokens(player->getTokens() - numberOfTokens);
	map->regions.at(regions->at(selectedRegion)).tokens += numberOfTokens;
	return std::make_tuple(selectedRegion, numberOfTokens);
}

Defensive::Defensive(Player * player) : Strategy(player) {}

/* Defensive player only declines if less than 25% of initial tokens remaining for deployment.
	Returns 1 if declining or 2 if expanding. */
int Defensive::select_action(int currentTurn) {
	int initialTokenQuantity = player->getRace()->getRaceTokens() + player->getBadge()->getRaceTokens();
	if (player->getTokens() < (float)(initialTokenQuantity * 25 / 100))
		return 1;
	else
		return 2;
}

/* Defensive player never abandons one of their regions */
int Defensive::abandons(Map* map, vector<size_t>* regions) {
	return -1;
}

/* Defensive player conquers the most reinforced region.
	They stop conquering when they have less than 50% of their initial number of tokens. */
int Defensive::expands(Map* map, vector<size_t>* regions) {
	int initialTokenQuantity = player->getRace()->getRaceTokens() + player->getBadge()->getRaceTokens();

	if (player->getTokens() < (float)(initialTokenQuantity * 50 / 100))
		return -1;
	else {
		int strongestRegion = 0;
		int strongestRegionTokens = map->regions.at(0).tokens;
		for (int i = 1; i < regions->size() - 1; i++) {
			int temp = map->regions.at(i).tokens;
			if (temp < strongestRegionTokens) {
				strongestRegion = i;
				strongestRegionTokens = temp;
			}
		}
		return strongestRegion;
	}
}

/* Defensive player distributes tokens among its regions as evenly as possible */
std::tuple<int, int> Defensive::redeploys(Map* map, vector<size_t>* regions) {
	int numberOfTokens = 1;
	bool redeployDone = false;
	int selectedRegion = 0;
	int i = 2;

	while (!redeployDone) {
		if (map->regions.at(regions->at(selectedRegion)).tokens < i)
			redeployDone = true;
		else if (selectedRegion == regions->size() - 1) {
			i++;
			selectedRegion = 0;
		}
		else
			selectedRegion++;
	}

	player->setTokens(player->getTokens() - numberOfTokens);
	map->regions.at(regions->at(selectedRegion)).tokens += numberOfTokens;
	return std::make_tuple(selectedRegion, numberOfTokens);
}

Moderate::Moderate(Player * player) : Strategy(player) {}

/* Moderate player declines every 3 turns.
	Returns 1 if declining or 2 if expanding. */
int Moderate::select_action(int currentTurn) {
	if (player->getRace()->getName().compare("Ghouls") || (currentTurn - 1) % 3 == 0)
		return 1;
	else
		return 2;
}

/* Moderate player randomly opts to abandon a region if they no longer have a region for use during conquer
	i.e. If they have no more tokens, they may or may not abandon a region. */
int Moderate::abandons(Map* map, vector<size_t>* regions) {
	srand(time(NULL));
	if (player->getTokens() > 0 || rand() % 2 == 0)
		return -1;
	else {
		//Player abandons a random region for simplicity's sake
		srand(time(NULL));
		int selectedRegion = rand() % regions->size();

		map->regions.at(regions->at(selectedRegion)).tokens = 0;
		map->regions.at(regions->at(selectedRegion)).owner = nullptr;

		return selectedRegion;
	}
}

/* Moderate player conquers the least reinforced region.
	They stop conquering when they have less than 50% of their initial number of tokens. */
int Moderate::expands(Map* map, vector<size_t>* regions) {
	int initialTokenQuantity = player->getRace()->getRaceTokens() + player->getBadge()->getRaceTokens();

	if (player->getTokens() < (float)(initialTokenQuantity * 50 / 100))
		return -1;
	else {
		int weakestRegion = 0;
		int weakestRegionTokens = map->regions.at(0).tokens;
		for (int i = 1; i < regions->size() - 1; i++) {
			int temp = map->regions.at(i).tokens;
			if (temp < weakestRegionTokens) {
				weakestRegion = i;
				weakestRegionTokens = temp;
			}
		}
		return weakestRegion;
	}
}

/* Moderate player redeploys half of their remaining tokens to a region continuously until they no longer have any */
std::tuple<int, int> Moderate::redeploys(Map* map, vector<size_t>* regions) {
	int numberOfTokens = ceil((float)player->getTokens() / 2);
	bool redeployDone = false;
	int selectedRegion = 0;
	int i = 2;

	while (!redeployDone) {
		if (map->regions.at(regions->at(selectedRegion)).tokens < i)
			redeployDone = true;
		else if (selectedRegion == regions->size() - 1) {
			i++;
			selectedRegion = 0;
		}
		else
			selectedRegion++;
	}
	player->setTokens(player->getTokens() - numberOfTokens);
	map->regions.at(regions->at(selectedRegion)).tokens += numberOfTokens;
	return std::make_tuple(selectedRegion, numberOfTokens);
}

Random::Random(Player * player) : Strategy(player) {}

/* Random player declines or expands randomly.
	Returns 1 if declining or 2 if expanding. */
int Random::select_action(int currentTurn) {
	srand(time(NULL));
	return rand() % 2 + 1;
}

/* Random player randomly abandons regions */
int Random::abandons(Map* map, vector<size_t>* regions) {
	srand(time(NULL));
	if (rand() % 2 == 0)
		return -1;
	else {
		srand(time(NULL));
		int selectedRegion = rand() % regions->size();

		map->regions.at(regions->at(selectedRegion)).tokens = 0;
		map->regions.at(regions->at(selectedRegion)).owner = nullptr;

		return selectedRegion;
	}
}

/* Random player selects whether to conquer or not randomly.
	If they choose to conquer, they select a random region. */
int Random::expands(Map* map, vector<size_t>* regions) {
	srand(time(NULL));
	if (rand() % 2 == 0)
		return -1;
	else {
		srand(time(NULL));
		return rand() % regions->size();
	}
}

/* Random player deploys a random amount of tokens to a random property */
std::tuple<int, int> Random::redeploys(Map* map, vector<size_t>* regions) {
	srand(time(NULL));
	int selectedRegion = rand() % regions->size();
	srand(time(NULL));
	int numberOfTokens = (rand() % player->getTokens()) + 1;
	if (numberOfTokens == 0) numberOfTokens = 1;

	player->setTokens(player->getTokens() - numberOfTokens);
	map->regions.at(regions->at(selectedRegion)).tokens += numberOfTokens;
	return std::make_tuple(selectedRegion, numberOfTokens);
}