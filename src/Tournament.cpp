#include "Tournament.h"
#include "MapReader.h"
#include "Strategy.h"
#include "tinydir.h"
#include "Exception.h"
#include <string>
#include <limits>
#include <ctime>

#undef max;

Tournament::Tournament(int numberOfPlayers) {
	this->numberOfPlayers = numberOfPlayers;
	dom = hand = coins = false;
	phaseObserver = new PhaseObserver(phaseSubject);
	baseObserver = new BaseObserver(turnSubject);
	baseObserver = new BaseObserver(turnSubject);
	baseObserver = new BaseObserver(turnSubject);
	baseObserver = new BaseObserver(turnSubject);
	baseObserver = new BaseObserver(turnSubject);

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
}

int Tournament::processInput() {
	int choice = 0;
	while (choice < 1 || choice > 4)
		try {
			if (!(cin >> choice) || (choice < 1 || choice > 4)) {
				throw IllegalInputException();
			}
		}
		catch (IllegalInputException e) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cerr << e.what();
			cout << "Enter a valid choice: ";
		}
	return choice;
}

void Tournament::changeObserver() {
	bool done = false;

	while (!done) {
		system("CLS");

		cout << "Observer: ";
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


		cout << "Would you like to change observers?" << endl << "1. Toggle Domination view" <<
			endl << "2. Toggle Cards view" << endl << "3. Toggle Points view" << endl <<
			"4. Done" << endl;

		int choice = processInput();

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

void Tournament::updateObserver() {
	vector<string> playerNames;
	vector<int> percent;
	vector<string> hands;
	vector<int> points;
	int size = m.regions.size();

	for each(Player *p in players) {
		playerNames.push_back(p->getName());

		if (p->getBadge())
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
	else {
		turnSubject->notify();
	}

	cout << endl << flush;
	system("PAUSE");
}

void Tournament::setup() {
	bool mapReady = false;

	string mapDirectory = "./maps/" +  std::to_string(numberOfPlayers) + "players.map";
	
	

	MapReader mr = MapReader(mapDirectory);

	m = mr.makeMap();
	
	/*
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
	}*/

	//Gets names for all players
	for (int i = 0; i < numberOfPlayers; i++) {
		players.push_back(new Player("Player " + to_string(i + 1)));

		cout << players.at(i)->getName() << ", what strategy will you use?" << endl
			<< "1. Aggressive" << endl
			<< "2. Defensive" << endl
			<< "3. Moderate" << endl
			<< "4. Random" << endl;

		
		int strategyInput = processInput();

		switch (strategyInput) {
		case 1:
			players.at(i)->setStrategy(new Aggressive(players.at(i)));
			break;
		case 2:
			players.at(i)->setStrategy(new Defensive(players.at(i)));
			break;
		case 3:
			players.at(i)->setStrategy(new Moderate(players.at(i)));
			break;
		default:
			players.at(i)->setStrategy(new Random(players.at(i)));
			break;
		}
	}

	currentTurn = 1;
}

//function that selects the maps directory and lists all the maps
string Tournament::dir() {
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

void Tournament::pickingRace(Player* player) {
	//Players select a random race
	srand(time(NULL));
	int selectedRace = rand() % 6;

	player->picks_race(deck.getRace(selectedRace), deck.getBadge(selectedRace));
	deck.removeRace(selectedRace);
	deck.removeBadge(selectedRace);

	phaseSubject->PhaseChanged(player->getName(), 0, "selects " + player->getBadge()->getName() + " " + player->getRace()->getName());
}

void Tournament::expanding(Player* player, vector<size_t>* regions) {
	//Abandons
	// Does not occur in the first turn of the game
	if (currentTurn > 1) {
		if (regions->size() > 0) {
			int selectedRegion = 0;

			// Loops until the player no longer wishes to abandon or owns no regions
			while (regions->size() > 0 && selectedRegion >= 0) {
				selectedRegion = player->abandons(&m, regions);

				if (selectedRegion < 0)
					break;
				phaseSubject->PhaseChanged(player->getName(), 1, "abandons " + m.regions.at((regions->at(selectedRegion))).name + ".");

				// regions contains indices of regions owned by player
				regions->clear();
				for (int i = 0; i < m.regions.size(); i++) {
					if (m.regions.at(i).owner && m.regions.at(i).owner == player && !m.regions.at(i).decline) {
						regions->push_back(i);
						if (m.regions.at(i).tokens > 1) {
							player->setTokens(player->getTokens() + m.regions.at(i).tokens - 1);
							m.regions.at(i).tokens = 1;
						}
					}
				}
			}
		}
	}

	//Conquers
	// Amazons gain 4 extra conquer tokens during conquer
	if (player->getRace()->getName().compare("Amazons") == 0)
		player->setTokens(player->getTokens() + 4);
	// Loops until player no longer wishes to conquer, fails to conquer, or runs out of tokens
	while (player->getTokens() > 0) {
		int owned = 0;

		for (const auto region : m.regions)
			if (region.owner && region.owner == player)
				owned++;

		if (owned == m.regions.size()) {
			phaseSubject->PhaseChanged(player->getName(), 2, "cannot expand further: You have conquered all regions.");
			break;
		}
		if (owned > 0) {
			regions->clear();
			for (const auto link : m.links) {
				//we're only looking for the links that start with our region
				if (m.regions.at(link.region1).owner && m.regions.at(link.region1).owner == player) {
					if (!(std::find(regions->begin(), regions->end(), link.region2) != regions->end())) {
						if (!m.regions.at(link.region2).owner || m.regions.at(link.region2).owner != player) {
							regions->push_back(link.region2);
						}
					}
				}
			}
		}
		else {
			regions->clear();
			for (int i = 0; i < m.regions.size(); i++) {
				regions->push_back(i);
			}
		}

		regions->shrink_to_fit();

		int selectedRegion = player->expands(&m, regions);

		if (selectedRegion < 0)
			break;
		else if (player->conquers(&m, selectedRegion, &dice)) {
			phaseSubject->PhaseChanged(player->getName(), 2, "captures a region.");
		}
		else {
			phaseSubject->PhaseChanged(player->getName(), 2, "fails to capture region.");
			break;
		}
	}

	//Redeploy
	// regions contains indices of regions owned by player
	regions->clear();
	for (int i = 0; i < m.regions.size(); i++) {
		if (m.regions.at(i).owner && m.regions.at(i).owner == player && !m.regions.at(i).decline) {
			regions->push_back(i);
			if (m.regions.at(i).tokens > 1) {
				player->setTokens(player->getTokens() + m.regions.at(i).tokens - 1);
				m.regions.at(i).tokens = 1;
			}
		}
	}

	// Amazons lose their 4 extra conquer tokens
	if (player->getRace()->getName().compare("Amazons") == 0)
		player->setTokens(player->getTokens() - 4);

	/* Skeletons earn an extra token for every 2 non-empty regions conquered during a turn.
		To do so, the bonusVictoryCoins is utilized as a counter of the number non-empty regions conquered */
	if (player->getRace()->getName().compare("Skeletons") == 0) {
		player->setTokens(player->getTokens() + player->getBonusCoins() / 2);
		player->setBonusCoins(0);
	}

	if (regions->size() == 0)
		phaseSubject->PhaseChanged(player->getName(), 3, "cannot redeploy: You don't own any regions.");
	else {
		// Alchemist earn 2 bonus coins if they have tokens on the map during the turn
		if (player->getBadge()->getName().compare("Alchemist") == 0)
			player->setBonusCoins(player->getBonusCoins() + 2);
		// Loops until player no longer has any tokens
		while (player->getTokens() > 0) {
			int selectedRegion, numberOfTokens;
			std::tie(selectedRegion, numberOfTokens) = player->redeploys(&m, regions);
			phaseSubject->PhaseChanged(player->getName(), 3, "adds " + std::to_string(numberOfTokens) + " tokens to " + m.regions.at(regions->at(selectedRegion)).name);
		}
	}
}


void Tournament::plays_turn(Player* player) {
	changeObserver();

	player->setBonusCoins(0);
	bool newRace = false;

	//Player selects new race if they declined in the previous one
	if (player->getRace() == NULL) {
		pickingRace(player);
		newRace = true;
	}

	// regions contains indices of regions owned by player
	vector<size_t> regions = vector<size_t>(0);
	for (int i = 0; i < m.regions.size(); i++) {
		if (m.regions.at(i).owner && m.regions.at(i).owner == player && !m.regions.at(i).decline) {
			regions.push_back(i);
			if (m.regions.at(i).tokens > 1) {
				player->setTokens(player->getTokens() + m.regions.at(i).tokens - 1);
				m.regions.at(i).tokens = 1;
			}
		}
	}

	int selectedMove = 2;

	//Player will not decline when they have a new race or last turn
	if (!newRace && currentTurn != numberOfTurns) {
		selectedMove = player->select_action(currentTurn);
	}

	//Entering in decline
	if (selectedMove == 1) {
		//Player puts race in decline
		phaseSubject->PhaseChanged(player->getName(), 5, "declines the " + player->getBadge()->getName() + " " + player->getRace()->getName());
		player->declines_race(&m, &deck);
	}
	//Expanding through new conquests
	else if (selectedMove == 2)
		expanding(player, &regions);

	//Player scores victory points
	phaseSubject->PhaseChanged(player->getName(), 4, "scores " + std::to_string(player->scores(&m)) + " victory coins and " + std::to_string(player->getBonusCoins()) + " bonus victory coins.");

	// Stout can decline race after scoring
	if (player->getBadge() != NULL &&  player->getBadge()->getName().compare("Stout") == 0)
		if (player->select_action(currentTurn) == 1) {
			//Player puts race in decline
			phaseSubject->PhaseChanged(player->getName(), 5, "declines the " + player->getBadge()->getName() + " " + player->getRace()->getName());
			player->declines_race(&m, &deck);
		}

	updateObserver();
}


void Tournament::run() {
	//string str = "Sent  armies to ";
	//subj->PhaseChanged("john", 0, str);

	// Init
	setup();

	//Game loop
	while (currentTurn <= numberOfTurns) {
		for (auto &player : players)
			plays_turn(player);
		currentTurn++;
	}

	//Game ends
	string winner = "";
	int winningScore = 0;
	system("CLS");
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
	cout << "\n" << winner << " wins with a score of " << winningScore << " victory points!" << endl << endl;
	dice.printRollPercentage();

	//Destroy all pointer values
	delete phaseSubject;
	delete phaseObserver;
	delete dominionSubject;
	for (auto player : players)
		delete player;
}
