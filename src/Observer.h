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
	std::vector<Observer*> observers;

public:
	void addObserver(Observer* const& observer);
	void notify();
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

		notify();
	}

};


class DominionObserver : public Observer {
	DominionSubject *sItem;
public:
	DominionObserver(DominionSubject *i) {
		sItem = i;
		i->addObserver(this);
	}
	void update() override {
		cout << endl;

		for (unsigned int i = 0; i < sItem->percents.size() && i < sItem->players.size(); i++) {
			cout << endl << sItem->players[i] << " owns " << sItem->percents[i] << "% of the map!" << endl;
		}

		cout << endl;
	}
};