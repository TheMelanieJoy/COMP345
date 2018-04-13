#pragma once
#define OBSERVER_H

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Subject;

//base observer template, used to observe and output some type of information
class Observer {

	//subject observed by the observer
	Subject* item;

public:

	//Constructor with provided subject
	Observer(Subject *i) {
		item = i;
	}
	//Base constructor
	Observer() {};

	//Called by this observer's subject, usually prints the subject's status
	virtual void update() = 0;
};


//base subject, holds all the relevant information for the observer
class Subject {
private:
	//Observer currently observing this subject
	Observer* observer;

public:
	//changes the current observer to the provided observer
	void addObserver(Observer* const& observer);
	//tells the observer that something has changed
	void notify();
};

//subject for which turn it is
class TurnSubject : public Subject {
public:
	//current turn
	int turn;

	//called whenever the turn changes
	void TurnChanged(int t) {
		turn = t;
	}
};

//First implementation of observer
//Looks at the current turn
class BaseObserver : public Observer {
	//This observer's subject
	TurnSubject* tItem;

public:
	//Constructor, selects our subject and adds itself as the subject's observer
	BaseObserver(TurnSubject *t) {
		tItem = t;
		t->addObserver(this);
	}

	//Logs the turn from the subject when called
	void update() {
		cout << endl << "It is turn " << tItem->turn << endl;
	}
};

//Subject holding the current phase of play
class PhaseSubject : public Subject {
public:
	//who's turn it is
	string player;
	//current game phase
	int phase;
	//message to display
	string str;

	//called whenever the game phase or turn changes
	void PhaseChanged(string plr, int pha, string s) {
		player = plr;
		phase = pha;
		str = s;

		notify();
	}

};

//Observer looking at the current phase of play
class PhaseObserver : public Observer {
	//Observed subject
	PhaseSubject *pItem;
public:
	//Constructor, sets our subject, and adds this observer as the subjects observer
	PhaseObserver(PhaseSubject *i) {
		pItem = i;
		i->addObserver(this);
	}
	//Logs current phase information
	void update() override {
		cout << endl;
		
		//each number corresponds to a phase
		switch (pItem->phase) {
		case 0:
			cout << "Race Selection Phase: ";
			break;
		case 1:
			cout << "Abandonment Phase: ";
			break;
		case 2:
			cout << "Attack Phase: ";
			break;
		case 3:
			cout << "Redeployment Phase: ";
			break;
		case 4:
			cout << "Scoring Phase: ";
			break;
		case 5:
			cout << "Decline Phase: ";
			break;

		}
		
		//logs the current player and any additionnal message
		cout << pItem->player << " " << pItem->str << endl << endl;

	}
};

//Wrapper that enables the decorator design pattern.
//Adds its utilities to the observer(s) it contains
class ObserverWrapper : public Observer {
private:
	//The observer the wrapper is building upon
	Observer * wrappee;
public:
	//Constructor, sets the wrappee
	ObserverWrapper(Observer *inner) {
		wrappee = inner;
	}
	//Destructor, deletes this, and every wrappee contained within it
	~ObserverWrapper() {
		delete wrappee;
	}
	//whenever this is updated, so are all the wrappees
	void update() {
		wrappee->update();
	}

};

//A subject for the domination view
class DominionSubject : public Subject {
public:
	//list of all players
	vector<string> players;
	//list of which percentage of the map they own
	vector<int> percents;

	//called whenever the map changes. updates the current players and percentages
	void MapChanged(vector<string> plr, vector<int> scores) {
		players.clear();
		percents.clear();
		for each (string player in plr)
		{
			players.push_back(player);
		}
		for each (int score in scores)
		{
			percents.push_back(score);
		}
	}

};

//A subject for the card view
class HandSubject : public Subject {
public:
	//list of all players
	vector<string> players;
	//list of which race the players are currently using
	vector<string> cards;

	//called whenever a player changes races. Updates all players
	//and their hands
	void HandChanged(vector<string> plr, vector<string> hand) {
		players.clear();
		cards.clear();
		for each (string player in plr)
		{
			players.push_back(player);
		}
		for each (string card in hand)
		{
			cards.push_back(card);
		}

	}

};

//A subject for the points view
class PointsSubject : public Subject {
public:
	//A list of all players
	vector<string> players;
	//A list of how much points they have
	vector<int> points;

	//Called whenever a player gains or loses points.
	//Updates all players and the ammount of points they have.
	void PointsChanged(vector<string> plr, vector<int> vicPoints) {
		players.clear();
		points.clear();
		for each (string player in plr)
		{
			players.push_back(player);
		}
		for each (int point in vicPoints)
		{
			points.push_back(point);
		}

	}

};

//The observer for the domination view
class DominionObserver : public ObserverWrapper {
	//The corresponding subject
	DominionSubject *sItem;
public:
	//Constructor, selects our subject and adds itself as the subject's observer
	//Also adds itself to another observer
	DominionObserver(DominionSubject *i, Observer *inner) : ObserverWrapper(inner) {
		sItem = i;
		i->addObserver(this);
	}
	
	//Logs dominion information from the subject
	void update() override {
		ObserverWrapper::update();
		cout << endl;

		for (unsigned int i = 0; i < sItem->percents.size() && i < sItem->players.size(); i++) {
			cout << sItem->players[i] << " owns " << sItem->percents[i] << "% of the map!" << endl;
		}

	}
};

//The observer for the card view
class HandObserver : public ObserverWrapper {
	//The corresponding subject
	HandSubject *sItem;
public:
	//Constructor, selects our subject and adds itself as the subject's observer
	//Also adds itself to another observer
	HandObserver(HandSubject *i, Observer *inner) : ObserverWrapper(inner) {
		sItem = i;
		i->addObserver(this);
	}
	
	//Logs card information from the subject
	void update() override {
		ObserverWrapper::update();

		cout << endl;

		for (unsigned int i = 0; i < sItem->cards.size() && i < sItem->players.size(); i++) {
			if (sItem->cards[i] == "")
				cout << sItem->players[i] << " doesn't have a current race" << endl;
			else
				cout << sItem->players[i] << " has the " << sItem->cards[i] << endl;
		}

	}
};

//The observer for the points view
class PointsObserver : public ObserverWrapper {
	//The corresponding subject
	PointsSubject *sItem;
public:
	//Constructor, selects our subject and adds itself as the subject's observer
	//Also adds itself to another observer
	PointsObserver(PointsSubject *i, Observer *inner) : ObserverWrapper(inner) {
		sItem = i;
		i->addObserver(this);
	}
	
	//Logs points information from the subject
	void update() override {
		ObserverWrapper::update();

		cout << endl;

		for (unsigned int i = 0; i < sItem->points.size() && i < sItem->players.size(); i++) {
			cout << sItem->players[i] << " has " << sItem->points[i] << " points. " << endl;
		}

	}
};
