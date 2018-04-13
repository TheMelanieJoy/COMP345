#pragma once

#include "stdafx.h"
#include "Dice.h"
#include "Deck.h"
#include "Player.h"
#include "Map.h"
#include "tinydir.h"
#include <iostream>
#include <vector>

/**
* The tournament class prepares and executes a tournament (a full game of Small World) based on the number of players.
*/
class Tournament {
private:
	// Constants
	/* Number of turn in the game, given the number of players */
	const int twoThreePlayersTurns = 10;
	const int fourPlayersTurns = 9;
	const int fivePlayersTurns = 8;

	/* Contains all the players in the tournament */
	vector<Player*> players;
	/* The number of players in the tournament */
	int numberOfPlayers;
	/* The number of turns in the game */
	int numberOfTurns;
	/* The stack of races and badges */
	Deck deck;
	/* The reinforcement die */
	Dice dice;
	/* The game map */
	Map m = Map(0, 0);
	/* Tracks the current turn */
	int currentTurn;

	bool dom, hand, coins;

	PhaseSubject* phaseSubject = new PhaseSubject;
	PhaseObserver* phaseObserver;
	TurnSubject* turnSubject = new TurnSubject;
	DominionSubject* dominionSubject = new DominionSubject;
	HandSubject* handSubject = new HandSubject;
	PointsSubject* pointsSubject = new PointsSubject;
	Observer* baseObserver;

	/**
	* Handles IllegalInputExceptions for an input that is expected to be an integer
	* @return An integer
	*/
	int processInput();

public:
	/**
	* Constructor
	* @param int - The number of players in the tournament
	*/
	Tournament(int);
	void changeObserver();
	void updateObserver();
	/**
	* Sets up the game by intializing the players
	*/
	void setup();
	string dir();
	/**
	* Player selects a new race and badge
	* @param The current player
	*/
	void pickingRace(Player* player);
	/**
	* Player expands the territory by abandoning owned regions, conquering new ones, and redeploying units
	* @param Player* - The current player
	* @param vector<size_t>* - Contains indices of regions owned by player
	*/
	void expanding(Player*, vector<size_t>*);
	/**
	* Player completes a turn by picking a race, conquering, and scoring
	* @param Player* - The current player
	*/
	void plays_turn(Player*);
	/**
	* Runs the game
	*/
	void run();
};