#pragma once

#include "stdafx.h"
#include "Dice.h"
#include "Deck.h"
#include "Player.h"
#include "Map.h"
#include "tinydir.h"
#include <iostream>
#include <vector>

class Tournament {
private:
	// Constants
	// Number of turn in the game, given the number of players
	const int twoThreePlayersTurns = 10;
	const int fourPlayersTurns = 9;
	const int fivePlayersTurns = 8;

	vector<Player*> players;
	int numberOfPlayers;
	int numberOfTurns;
	Deck deck;
	Dice dice;
	Map m = Map(0, 0);
	int currentTurn;

	bool dom, hand, coins;

	PhaseSubject* phaseSubject = new PhaseSubject;
	PhaseObserver* phaseObserver;
	TurnSubject* turnSubject = new TurnSubject;
	DominionSubject* dominionSubject = new DominionSubject;
	HandSubject* handSubject = new HandSubject;
	PointsSubject* pointsSubject = new PointsSubject;
	Observer* baseObserver;

public:
	Tournament(int);
	int processInput();
	void changeObserver();
	void updateObserver();
	void setup();
	string dir();
	void pickingRace(Player* player);
	void expanding(Player*, vector<size_t>*);
	void plays_turn(Player*);
	void run();
};