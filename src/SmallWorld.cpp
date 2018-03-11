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
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <limits>

using namespace std;

#undef max

vector<Player*> players;
int numberOfTurns;
Deck* deck = new Deck();
Dice* dice = new Dice();

string dir() {
	tinydir_dir dir;

	std::vector<string> maps;

	if (tinydir_open(&dir, "./maps") == -1)
	{
		perror("Error opening file");
		goto bail;
	}

	int item = 0;



	maps.reserve(10);

	while (dir.has_next)
	{
		tinydir_file file;
		if (tinydir_readfile(&dir, &file) == -1)
		{
			perror("Error getting file");
			goto bail;
		}

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


void setup() {

	bool mapReady = false;


	while (!mapReady) {
		cout << "Maps:" << endl << endl;
		string mapPath = dir();

		MapReader mr = MapReader(mapPath);

		Map m = mr.makeMap();

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
			numberOfTurns = 9;
			break;
		case 5:
			numberOfTurns = 8;
			break;
		default:
			numberOfTurns = 10;
	}

	//Gets names for all players
	for (int i = 0; i < numberOfPlayers; i++) {
		string name = "Player " + to_string(i);
		cout << "Player " << to_string(i + 1) << ", please enter your name: ";
		cin >> name;
		Player player = Player(name);
		players.push_back(new Player(name));
	}

	//Shuffles race banners and badges' index
	srand(time(NULL));

	/**
	std::cout << "Manually adding map \n";
	//making a new map
	Map g = Map(10, 20);

	//fill up all regions
	g.addRegion("R0");
	g.addRegion("R1");
	g.addRegion("R2");
	g.addRegion("R3");
	g.addRegion("R4");

	// fill up all links
	g.addLink(0, 1);
	g.addLink(0, 2);
	g.addLink(0, 3);
	g.addLink(0, 4);

	std::cout << "Testing illegal links \n";
	// trying to add illegal links
	g.addLink(1, 1);
	g.addLink(5, 4);

	g.linked();

	std::cout << "\n";

	std::cout << "Reading map from file \n";

	m.linked();

	std::cout << "Printing map \n";
	auto dftResult = m.dft(0);
	for (const auto v : dftResult) std::cout << " " << v;
	std::cout << "\n";*/
}

void first_turn(Player* player) {

	//Picks a Race and Special Power combo
    deck->displayAvailableRaces();

	cout << player->getName() << ", select a race (Enter its assigned number): ";
	int selectedRace = 0;
	while (!(cin >> selectedRace) || (selectedRace < 1 || selectedRace > 6)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter a number from 1 to 6: ";
	}
    
	player->picks_race(deck->getRace(selectedRace - 1), deck->getBadge(selectedRace - 1));
	deck->removeRace(selectedRace - 1);
	deck->removeBadge(selectedRace - 1);

	cout << player->getName() << " selects " << player->getBadge()->getName() << " " << player->getRace()->getName() << endl << endl;

	//Conquers some Regions

	//Scores some Victory coins

}

void following_turns(Player* player) {
	//Player selects new race if they declined in the previous one
	if (player->getRace() == NULL) {
		deck->displayAvailableRaces();

		cout << player->getName() << ", select a race (Enter its assigned number): ";
		int selectedRace = 0;
		while (!(cin >> selectedRace) || (selectedRace < 1 || selectedRace > 6)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a number from 1 to 6: ";
		}

		player->picks_race(deck->getRace(selectedRace - 1), deck->getBadge(selectedRace - 1));
		deck->removeRace(selectedRace - 1);
		deck->removeBadge(selectedRace - 1);

		cout << player->getName() << " selects " << player->getBadge()->getName() << " " << player->getRace()->getName() << endl << endl;
	}

    cout << player->getName() << ", it is now your turn. What will you do?" << endl
        << "1. Decline my race." << endl
        << "2. Conquer." << endl;
    int selectedMove;
	while (!(cin >> selectedMove) || (selectedMove < 1 || selectedMove > 2)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter a valid number: ";
	}
    
    //Entering in decline
    if(selectedMove == 1) {
		//Player puts race in decline
		cout << "The " << player->getBadge()->getName() << " " << player->getRace()->getName() << " is now declined." << endl << endl;
		player->declines_race(deck);

		//Player scores victory points
		//TODO add player.scores(...)
    }
	//Expanding through new conquests
	else if(selectedMove == 2) {
		//TODO add player.conquers(...)
		//Available conquest moves:
		// - Ready your troops
		// - Conquer
		// - Abandoning a region

		//TODO add player.scores(...)
	}
}


int main()
{
	setup();

	//Each player plays the first turn of the game
	int currentTurn = 1;
	cout << "\nIt is now Turn " << currentTurn << endl << endl;
	for (auto &player : players)
		first_turn(player);
	currentTurn++;

	//Each player plays the following turns until the game is over
	while (currentTurn <= numberOfTurns) {
		cout << "It is now Turn " << currentTurn << endl << endl;
		for (auto &player : players)
			following_turns(player);
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
	dice->printRollPercentage();

	//Destroy all pointer values
	delete deck;
	delete dice;
	for (auto player : players)
		delete player;

    return 0;
}



