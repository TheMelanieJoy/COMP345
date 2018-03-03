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
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
using namespace std;

vector<Player> players;
int numberOfTurns;
Deck deck = Deck();

void setup() {
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
		players.push_back(player);
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
	MapReader mr = MapReader("C:/Users/Gecky/source/repos/COMP345/COMP345/Debug/example.map");

	Map m = mr.makeMap();

	m.linked();

	std::cout << "Printing map \n";
	auto dftResult = m.dft(0);
	for (const auto v : dftResult) std::cout << " " << v;
	std::cout << "\n";*/
}

void first_turn(Player player) {

	//Picks a Race and Special Power combo
    deck.displayAvailableRaces();

	cout << player.getName() << ", select a race (Enter its assigned number): ";
	int selectedRace = 0;
	while (!(cin >> selectedRace)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter a number from 1 to 6: ";
	}
    
	player.picks_race(deck.getRace(selectedRace - 1), deck.getBadge(selectedRace - 1));
	deck.removeRace(selectedRace - 1);
	deck.removeBadge(selectedRace - 1);

	cout << player.getName() << " selects " << player.getBadge()->getName() << " " << player.getRace()->getName() << endl;

	//Conquers some Regions

	//Scores some Victory coins

}

void following_turns(Player player) {
    cout << player.getName() << ", it is now your turn. What will you do?" << endl
        << "1. Decline my race." << endl
        << "2. Conquer." << endl;
    int selectedMove;
    while (!(cin >> selectedMove)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter a valid number.";
	}
    
    //Player declines race and ends turn
    if(selectedMove == 1) {
        
    }
}

int main()
{
	setup();

	//Each player plays the first turn of the game
	int currentTurn = 1;
	cout << "It is now Turn " << currentTurn << endl;
	for (auto &player : players)
		first_turn(player);
	currentTurn++;

	//Each player plays the following turns until the game is over
	while (currentTurn <= numberOfTurns) {
		cout << "It is now Turn " << currentTurn << endl;
		for (auto &player : players)
			following_turns(player);
		currentTurn++;
	}

	//Game ends

    return 0;
}

