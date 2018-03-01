// SmallWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Dice.h"
#include "FantasyRaceBanner.h"
#include "Badge.h"
#include "Player.h"
#include "MapReader.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
using namespace std;

vector<FantasyRaceBanner>races = { Amazons(),Dwarves(),Elves(),Ghouls(),Giants(),Halflings(),Humans(),Orcs(),Ratmen(),Skeletons(),Sorcerers(),Tritons(),Trolls(),Wizards() };
vector<Badge>badges = { Alchemist(),Berserk(),Bivouacking(),Commando(),Diplomat(),DragonMaster(),Flying(),Forest(),Fortified(),Heroic(),Hill(),Merchant(),Mounted(),Pillaging(),Seafaring(),Spirit(),Stout(),Swamp(),Underworld(),Wealthy() };
vector<Player> players;
int numberOfTurns = 10;
int currentTurn = 1;

void setup() {

	cout << "Setting up game for 2 players..." << endl;
	int numberOfPlayers = 2;
	for (int i = 0; i < numberOfPlayers; i++) {
		string name = "Player " + to_string(i);
		Player player = Player(name);
		players.push_back(player);
	}

	//Shuffles race banners and badges' index
	srand(time(NULL));


	std::random_shuffle(races.begin(), races.end());
	std::random_shuffle(badges.begin(), badges.end());

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
	std::cout << "\n";
}

void first_turn(Player player) {

	//Picks a Race and Special Power combo
	for (int i = 0; i < 6; i++)
		cout << i + 1 << ". " << badges[i].getName() << " " << races[i].getName() << endl;

	cout << player.getName() << ", Please select a race (Enter its assigned number): ";
	int selectedRace = 0;
	while (!(cin >> selectedRace)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter a number from 1 to 6: ";
	}
	player.picks_race(races.at(selectedRace - 1), badges.at(selectedRace - 1));
	races.erase(races.begin() + selectedRace - 1);
	badges.erase(badges.begin() + selectedRace - 1);

	cout << player.getName() << " selects " << player.getBadge()->getName() << " " << player.getRace()->getName() << endl;

	//Conquers some Regions

	//Scores some Victory coins

	currentTurn++;
}

void following_turns(Player player) {

}

int main()
{
	setup();

	//Each player plays the first turn of the game
	for (auto &player : players)
		first_turn(player);

	//Each player plays the following turns until the game is over
	while (currentTurn < numberOfTurns) {
		for (auto &player : players)
			following_turns(player);
	}

    cout << "Testing reinforcements dice" << std::endl;
    cout << "Rolling die 1..." << std::endl;
    int dice1 = roll();

    return 0;
}

