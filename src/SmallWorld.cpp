// SmallWorld.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Dice.h"
#include "Deck.h"
#include "FantasyRaceBanner.h"
#include "Badge.h"
#include "Player.h"
#include "MapReader.h"
#include "Map.h"
#include "tinydir.h"
#include "Strategy.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <limits>
#include "SmallWorld.h"

using std::cout;
using std::cin;

#undef max

// Constants
const int twoThreePlayersTurns = 3;
const int fourPlayersTurns = 9;
const int fivePlayersTurns = 8;

// Global variables
vector<Player*> players;
int numberOfTurns;
Deck deck;
Dice dice;
Map m = Map(0,0);
int currentTurn;

PhaseSubject* phaseSubject = new PhaseSubject;
PhaseObserver* phaseObserver;
DominionSubject* dominionSubject = new DominionSubject;
DominionObserver* dominionObserver;

//function that selects the maps directory and lists all the maps
string dir() {
	tinydir_dir dir;

	//holds map list
	std::vector<string> maps;

	//attempt to open map folder, go to bail if unable
	if (tinydir_open(&dir, "./maps") == -1)
	{
		perror("Error opening file");
		goto bail;
	}

	int item = 0;



	maps.reserve(10);
	//goes through every file in dir
	while (dir.has_next)
	{
		tinydir_file file;
		if (tinydir_readfile(&dir, &file) == -1)
		{
			perror("Error getting file");
			goto bail;
		}

		//only lists it if it isn't a folder
		if (!file.is_dir)
		{
			item++;
			printf("%i", item);
			printf(") ");
			printf("%s", file.name);
			printf("\n");
			maps.push_back(file.path);
		}

		if (tinydir_next(&dir) == -1)
		{
			perror("Error getting next file");
			goto bail;
		}
	}

	//now we need you to select a map
	cout << endl << "Select a map (Enter its assigned number): ";
	int selectedMap = 0;
	while (!(cin >> selectedMap) || (selectedMap < 1 || selectedMap > maps.size())) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter a number from 1 to " << item << "." << endl;
	}

	cout << maps[selectedMap - 1] << endl;
	return maps[selectedMap - 1];

bail:
	tinydir_close(&dir);
	return "";

}


void updateDominion() {

	vector<string> playerNames;
	vector<int> percent;
	int size = m.regions.size();

	for each(Player *p in players) 
		playerNames.push_back(p->getName());
	

	for (int i = 0; i < playerNames.size(); i++) {

		int score = 0;

		for each (region r in m.regions) 
			if (r.owner && r.owner->getName() == playerNames[i]) 
				score++;
			

		score *= 100;
		score /= size;
		percent.push_back(score);
	}

	dominionSubject->MapChanged(playerNames, percent);
}

void setup() {

	phaseObserver = new PhaseObserver(phaseSubject);
	dominionObserver = new DominionObserver(dominionSubject);
	bool mapReady = false;

	//keeps asking for a map until you succeed
	while (!mapReady) {
		cout << "Maps:" << endl << endl;
		string mapPath = dir();

		MapReader mr = MapReader(mapPath);

		m = mr.makeMap();

		if (!m.linked())
			cout << "Map isn't valid" << endl;

		else if (m.empty())
			cout << "Map is empty" << endl;

		else
			mapReady = true;
	}


	//Requests the number of players
	cout << "Select the number of players in the game (2-5 players): ";
	int numberOfPlayers = 0;
	//Number must be between 2 and 5 inclusive
	while (!(cin >> numberOfPlayers) || (numberOfPlayers < 2 || numberOfPlayers > 5)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter a valid number of players: ";
	}

	//Sets the number of turns for the game based on the number of players
	switch (numberOfPlayers) {
		case 4:
			numberOfTurns = fourPlayersTurns;
			break;
		case 5:
			numberOfTurns = fivePlayersTurns;
			break;
		default:
			numberOfTurns = twoThreePlayersTurns;
	}

	//Gets names for all players
	for (int i = 0; i < numberOfPlayers; i++) {
		string name = "Player " + to_string(i);
		cout << "Player " << to_string(i + 1) << ", please enter your name: ";
		cin >> name;
		Player player = Player(name);
		players.push_back(new Player(name));
		players.at(i)->set_strategy(new Random(players.at(i)));
	}

	currentTurn = 1;
}

void pickingRace(Player* player) {
	deck.displayAvailableRaces();

	//Players select a random race
	srand(time(NULL));
	int selectedRace = rand() % 6;

	player->picks_race(deck.getRace(selectedRace), deck.getBadge(selectedRace));
	deck.removeRace(selectedRace);
	deck.removeBadge(selectedRace);

	phaseSubject->PhaseChanged(player->getName(), 0, "selects " + player->getBadge()->getName() + " " + player->getRace()->getName());
}

void conquering(Player* player) {
	vector<size_t> regions = vector<size_t>(0);
	for (int i = 0; i < m.regions.size(); i++) {
		//if (m.regions.at(i).decline)
		//	cout << "Region " << m.regions.at(i).name << " is in decline.\n";

		if (m.regions.at(i).owner && m.regions.at(i).owner == player && !m.regions.at(i).decline) {
			regions.push_back(i);
			if (m.regions.at(i).tokens > 1) {
				player->addTokens(m.regions.at(i).tokens - 1);
				m.regions.at(i).tokens = 1;
			}
		}
	}

	//Abandons
	if (currentTurn > 1) {
		if (regions.size() > 0) {
			int selectedRegion = 0;

			while (selectedRegion >= 0) {
				selectedRegion = player->abandons(&m, &regions);

				if (selectedRegion < 0)
					break;
				phaseSubject->PhaseChanged(player->getName(), 1, "abandons region " + regions.at(selectedRegion));
				updateDominion();

				regions = vector<size_t>(0);
				for (int i = 0; i < m.regions.size(); i++) {
					if (m.regions.at(i).owner && m.regions.at(i).owner == player && !m.regions.at(i).decline) {
						regions.push_back(i);
						if (m.regions.at(i).tokens > 1) {
							player->addTokens(m.regions.at(i).tokens - 1);
							m.regions.at(i).tokens = 1;
						}
					}
				}
			}
		}
	}

	//Conquers
	while (player->currentTokens() > 0) {
		int owned = 0;

		for (const auto region : m.regions)
			if (region.owner && region.owner == player)
				owned++;

		if (owned == m.regions.size()) {
			std::cout << "Cannot expand further: You have conquered all regions";
			break;
		}

		if (owned > 0) {
			regions = vector<size_t>(0);
			for (const auto link : m.links) {
				//we're only looking for the links that start with our region
				if (m.regions.at(link.region1).owner && m.regions.at(link.region1).owner == player) {
					if (!(std::find(regions.begin(), regions.end(), link.region2) != regions.end())) {
						if (!m.regions.at(link.region2).owner || m.regions.at(link.region2).owner != player) {
							regions.push_back(link.region2);
						}
					}
				}
			}
		}
		else {
			regions = vector<size_t>(0);
			for (int i = 0; i < m.regions.size(); i++) {
				regions.push_back(i);
			}
		}

		regions.shrink_to_fit();

		int selectedRegion = player->expands(&m, &regions);

		if (selectedRegion < 0)
			break;
		else {
			if (player->conquers(&m, selectedRegion, &dice)) {
				phaseSubject->PhaseChanged(player->getName(), 2, "captures a region.");
				updateDominion();
			}
			else {
				phaseSubject->PhaseChanged(player->getName(), 2, "fails to capture region.");
				break;
			}
		}
	}

	//Redeploy
	regions = vector<size_t>(0);
	for (int i = 0; i < m.regions.size(); i++) {
		if (m.regions.at(i).owner && m.regions.at(i).owner == player && !m.regions.at(i).decline) {
			regions.push_back(i);
			if (m.regions.at(i).tokens > 1) {
				player->addTokens(m.regions.at(i).tokens - 1);
				m.regions.at(i).tokens = 1;
			}
		}
	}

	if (regions.size() == 0)
		cout << "Cannot redeploy: You don't own any regions" << endl;
	else
		while (player->currentTokens() > 0) {
			int selectedRegion, numberOfTokens;
			std::tie(selectedRegion, numberOfTokens) = player->redeploys(&m, &regions);
			phaseSubject->PhaseChanged(player->getName(), 3, "adds " + std::to_string(numberOfTokens) + " tokens to " + m.regions.at(regions.at(selectedRegion)).name);
		}
}

void plays_turn(Player* player) {
	//Player selects new race if they declined in the previous one
	if (player->getRace() == NULL)
		pickingRace(player);

	int selectedMove = player->select_action(currentTurn);

	//Entering in decline
	if (selectedMove == 1) {
		//Player puts race in decline
		phaseSubject->PhaseChanged(player->getName(), 5, "declines the " + player->getBadge()->getName() + " " + player->getRace()->getName());
		player->declines_race(&m, &deck);

	}
	//Expanding through new conquests
	else if (selectedMove == 2) {
		conquering(player);

	}

	//Scores some Victory coins
	int points = player->scores(&m);
	phaseSubject->PhaseChanged(player->getName(), 4, " won " + points + (string)" coins. Now they have " + std::to_string(player->getVictoryCoins()) + " coins.\n");
}


int main()
{
	//string str = "Sent  armies to ";
	//subj->PhaseChanged("john", 0, str);
	
	// Init
	setup();

	//Game loop
	while (currentTurn <= numberOfTurns) {
		cout << "It is now Turn " << currentTurn << endl << endl;
		for (auto &player : players)
			plays_turn(player);
		currentTurn++;
	}

	//Game ends
	string winner = "";
	int winningScore = 0;
	for (auto player : players) {
		cout << player->getName() << " scored a total of " << player->getVictoryCoins() << " victory points." << endl;

		if (player->getVictoryCoins() > winningScore) {
			winner = player->getName();
			winningScore = player->getVictoryCoins();
		}
		else if (player->getVictoryCoins() == winningScore) {
			winner += " & " + player->getName();
		}
	}
	cout << winner << " wins with a score of " << winningScore << " victory points!" << endl << endl;
	dice.printRollPercentage();

	//Destroy all pointer values
	delete phaseSubject;
	delete phaseObserver;
	delete dominionSubject;
	delete dominionObserver;
	for (auto player : players)
		delete player;

    return 0;
}



