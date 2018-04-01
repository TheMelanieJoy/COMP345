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
int currentTurn = 1;
Deck* deck = new Deck();
Dice* dice = new Dice();
Map m = Map(0,0);

bool dom, hand, coins;

PhaseSubject* phaseSubject = new PhaseSubject;
PhaseObserver* phaseObserver;
TurnSubject* turnSubject = new TurnSubject;
DominionSubject* dominionSubject = new DominionSubject;
HandSubject* handSubject = new HandSubject;
PointsSubject* pointsSubject = new PointsSubject;
Observer* baseObserver;

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


void changeObserver() {
	bool done = false;

	while (!done) {
		cout << endl << "Observer: ";
		if (dom)
			cout << "Domination is on, ";
		else
			cout << "Domination is off, ";
		if (hand)
			cout << "Cards is on, ";
		else
			cout << "Cards is off, ";
		if (coins)
			cout << "Points is on" << endl;
		else
			cout << "Points is off" << endl;


		cout << "Would you like to change observers?" << endl << "1. Toggle Dominion view" <<
			endl << "2. Toggle Cards view" << endl << "3. Toggle Points view" << endl <<
			"4. Done" << endl;

		int choice = 0;
		//Number must be between 2 and 5 inclusive
		while (!(cin >> choice) || (choice < 1 || choice > 4)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter a valid choice: ";
		}

		switch (choice) {
		case 1:
			dom = !dom;
			break;
		case 2:
			hand = !hand;
			break;
		case 3:
			coins = !coins;
			break;
		case 4:
			done = true;
			break;
		}
	}

	baseObserver = new BaseObserver(turnSubject);

	if (dom)
		baseObserver = new DominionObserver(dominionSubject, baseObserver);
	if (hand)
		baseObserver = new HandObserver(handSubject, baseObserver);
	if (coins)
		baseObserver = new PointsObserver(pointsSubject, baseObserver);


}

void updateObserver() {


	vector<string> playerNames;
	vector<int> percent;
	vector<string> hands;
	vector<int> points;
	int size = m.regions.size();

	for each(Player *p in players) {
		playerNames.push_back(p->getName());

		if(p->getBadge())
			hands.push_back(p->getBadge()->getName() + " " + p->getRace()->getName());

		points.push_back(p->getVictoryCoins());
	}
	

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
	handSubject->HandChanged(playerNames, hands);
	pointsSubject->PointsChanged(playerNames, points);
	turnSubject->TurnChanged(currentTurn);

	if (coins)
		pointsSubject->notify();
	else if (hand)
		handSubject->notify();
	else if (dom)
		dominionSubject->notify();
	else
		turnSubject->notify();
}

void setup() {

	dom = hand = coins = false;
	phaseObserver = new PhaseObserver(phaseSubject);
	baseObserver =  new BaseObserver(turnSubject);
	baseObserver = new BaseObserver(turnSubject);
	baseObserver = new BaseObserver(turnSubject);
	baseObserver = new BaseObserver(turnSubject);
	baseObserver = new BaseObserver(turnSubject);
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
	}

	//Shuffles race banners and badges' index
	srand(time(NULL));
}

void pickingRace(Player* player) {
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

	if (regions.size() > 0) {
		bool abandon = true;
		
		cout << "Would you like to abandon a region?\n1)Yes\n2)No\n";

		while (abandon) {
			int answer;
			
			while (!(cin >> answer) || (answer < 1 || answer > 2)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Please enter a valid answer: ";
			}

			if (answer == 2)
				abandon = false;
			else {
				cout << "Regions owned: \n";
				int regionCount = 1;
				for (auto region : regions) {
					cout << regionCount << ") " << m.regions.at(region).name << endl;
					regionCount++;
				}

				cout << "Which one?";

				int selectedRegion;
				while (!(cin >> selectedRegion) || (selectedRegion < 1 || selectedRegion > regionCount - 1)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Please enter a valid number: ";
				}

				m.regions.at(regions.at(selectedRegion - 1)).tokens = 0;
				m.regions.at(regions.at(selectedRegion - 1)).owner = nullptr;

				phaseSubject->PhaseChanged(player->getName(), 1, "abandons region " + regions.at(selectedRegion - 1));


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
				if (regions.size() > 1) {
					cout << "Would you like to abandon another region?\n1)Yes\n2)No\n";
				}
				else
					abandon = false;
			}
		}
	}

	while (player->currentTokens() > 0) {
		cout << "Remaining tokens: " << player->currentTokens() << endl;

		cout << "Select region to conquer: \n";

		int owned = 0;
		size_t currentRegion = 0;


		for (const auto region : m.regions) {
			if (region.owner && region.owner == player) {
				owned++;
			}
		}


		if (owned == m.regions.size()) {
			cout << "Wow, you own all the regions!\n";
			break;
		}


		currentRegion = 1;
		if (owned == 0) {
			for (const auto region : m.regions) {
				cout << currentRegion << ") " << region.name;
				if (region.owner) 
					cout << " owned by: " << region.owner->getName() << " current tokens: " << region.tokens;
				
				else if (region.decline && region.tokens > 0)
					cout << " owned by: " << "Lost tribe" << " current tokens: " << region.tokens;

				cout << endl;

				currentRegion++;
			}

			int selectedRegion;
			while (!(cin >> selectedRegion) || (selectedRegion < 1 || selectedRegion > currentRegion - 1)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Please enter a valid number: ";
			}
			if (player->conquers(&m, selectedRegion - 1, dice)) {
				phaseSubject->PhaseChanged(player->getName(), 2, "captures a region.");
			}
			else {
				phaseSubject->PhaseChanged(player->getName(), 2, "fails to capture region.");
				break;
			}
		}
		else {
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
			regions.shrink_to_fit();
			currentRegion = 1;
			for (const auto region : regions) {
				cout << currentRegion << ") " << m.regions.at(region).name;
				if (m.regions.at(region).owner)
					cout << " owned by: " << m.regions.at(region).owner->getName() << " current tokens: " << m.regions.at(region).tokens;
				else if (m.regions.at(region).decline && m.regions.at(region).tokens > 0)
					cout << " owned by: " << "Lost tribe" << " current tokens: " << m.regions.at(region).tokens;
				cout  << endl;

				currentRegion++;
			}

			int selectedRegion;
			while (!(cin >> selectedRegion) || (selectedRegion < 1 || selectedRegion > currentRegion - 1)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Please enter a valid number: ";
			}
			int capturedRegion = regions.at(selectedRegion - 1);

			if (player->conquers(&m, regions.at(selectedRegion - 1), dice)) {
				phaseSubject->PhaseChanged(player->getName(), 2, "captures a region.");
			}
			else {
				phaseSubject->PhaseChanged(player->getName(), 2, "fails to capture region.");
				break;
			}

		}



	}

	cout << "Done conquering. \n";
	cout << "Time to redeploy. \n";

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

	while (player->currentTokens() > 0) {
		if (regions.size() == 0) {
			cout << "You don't own any regions, can't redeploy.\n";
			break;
		}

		cout << "Current tokens : " << player->currentTokens() << endl;
		cout << "Regions owned: \n";
		int regionCount = 1;
		for (auto region : regions) {
			cout << regionCount << ") " << m.regions.at(region).name << ", " << m.regions.at(region).tokens << " tokens.\n";
			regionCount++;
		}
		cout << "Which region would you like to add to? ";
		int selectedRegion;
		while (!(cin >> selectedRegion) || (selectedRegion < 1 || selectedRegion > regionCount - 1)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a valid number: ";
		}
		cout << "How many tokens do you want to add? ";
		int numberOfTokens;
		while (!(cin >> numberOfTokens) || (numberOfTokens < 0 || numberOfTokens > player->currentTokens())) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a valid number: ";
		}
		phaseSubject->PhaseChanged(player->getName(), 3, "adds " + std::to_string(numberOfTokens) + " tokens to " + m.regions.at(regions.at(selectedRegion - 1)).name);
		player->setTokens(player->currentTokens() - numberOfTokens);
		m.regions.at(regions.at(selectedRegion - 1)).tokens += numberOfTokens;
	}
}

void first_turn(Player* player) {

	changeObserver();
	//Picks a Race and Special Power combo
	pickingRace(player);

	//Conquers some Regions
	conquering(player);

	//Scores some Victory coins
	int points = player->scores(&m);

	phaseSubject->PhaseChanged(player->getName(), 4, " won " + points + (string)" coins. Now they have " + std::to_string( player->getVictoryCoins() ) + " coins.\n");

	updateObserver();
}

void following_turns(Player* player) {

	changeObserver();

	//Player selects new race if they declined in the previous one
	if (player->getRace() == NULL) {
		pickingRace(player);
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
		phaseSubject->PhaseChanged(player->getName(), 5, "declines the " + player->getBadge()->getName() + " " + player->getRace()->getName());
		//cout << "The " << player->getBadge()->getName() << " " << player->getRace()->getName() << " is now declined." << endl << endl;
		player->declines_race(&m, deck);

    }
	//Expanding through new conquests
	else if(selectedMove == 2) {
		
		conquering(player);
		
	}

	//Player scores victory points
	player->scores(&m);

	updateObserver();
}


int main()
{

	//string str = "Sent  armies to ";
	//subj->PhaseChanged("john", 0, str);
	
	// Init
	setup();

	//Each player plays the first turn of the game
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



