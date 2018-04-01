#pragma once
#define OBSERVER_H

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Subject;

class Observer {

	Subject* item;

public:

	Observer(Subject *i) {
		item = i;
		//i->addObserver(this);
	}
	Observer() {};

	virtual void update() = 0;
};



class Subject {
private:
	Observer* observer;

public:
	void addObserver(Observer* const& observer);
	void notify();
};

class TurnSubject : public Subject {
public:
	int turn;

	void TurnChanged(int t) {
		turn = t;
		//notify();
	}
};

class BaseObserver : public Observer {
	TurnSubject* tItem;

public:
	BaseObserver(TurnSubject *t) {
		tItem = t;
		t->addObserver(this);
	}

	void update() {
		cout << endl << "It is turn " << tItem->turn;
	}
};

class PhaseSubject : public Subject {
public:
	string player;
	int phase;
	string str;


	void PhaseChanged(string plr, int pha, string s) {
		player = plr;
		phase = pha;
		str = s;

		notify();
	}

};


class PhaseObserver : public Observer {
	PhaseSubject *pItem;
public:
	PhaseObserver(PhaseSubject *i) {
		pItem = i;
		i->addObserver(this);
	}
	void update() override {
		cout << endl;

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

		cout << pItem->player << " " << pItem->str << endl << endl;

	}
};

class ObserverWrapper : public Observer {
public:
	ObserverWrapper(Observer *inner) {
		wrappee = inner;
	}
	~ObserverWrapper() {
		delete wrappee;
	}
	/*virtual*/
	void update() {
		wrappee->update();
	}
private:
	Observer * wrappee;

};


class DominionSubject : public Subject {
public:
	vector<string> players;
	vector<int> percents;


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

		//notify();
	}

};

class HandSubject : public Subject {
public:
	vector<string> players;
	vector<string> cards;


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

		//notify();
	}

};

class PointsSubject : public Subject {
public:
	vector<string> players;
	vector<int> points;


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

		//notify();
	}

};


class DominionObserver : public ObserverWrapper {
	DominionSubject *sItem;
public:
	DominionObserver(DominionSubject *i, Observer *inner) : ObserverWrapper(inner) {
		sItem = i;
		i->addObserver(this);
	}
	void update() override {
		ObserverWrapper::update();
		cout << endl;

		for (unsigned int i = 0; i < sItem->percents.size() && i < sItem->players.size(); i++) {
			cout << sItem->players[i] << " owns " << sItem->percents[i] << "% of the map!" << endl;
		}

	}
};


class HandObserver : public ObserverWrapper {
	HandSubject *sItem;
public:
	HandObserver(HandSubject *i, Observer *inner) : ObserverWrapper(inner) {
		sItem = i;
		i->addObserver(this);
	}
	void update() override {
		ObserverWrapper::update();

		cout << endl;

		for (unsigned int i = 0; i < sItem->cards.size() && i < sItem->players.size(); i++) {
			cout << sItem->players[i] << " has the " << sItem->cards[i] << endl;
		}

	}
};

class PointsObserver : public ObserverWrapper {
	PointsSubject *sItem;
public:
	PointsObserver(PointsSubject *i, Observer *inner) : ObserverWrapper(inner) {
		sItem = i;
		i->addObserver(this);
	}
	void update() override {
		ObserverWrapper::update();

		cout << endl;

		for (unsigned int i = 0; i < sItem->points.size() && i < sItem->players.size(); i++) {
			cout << sItem->players[i] << " has " << sItem->points[i] << " points. " << endl;
		}

	}
};