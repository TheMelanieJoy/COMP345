#pragma once
#define MAP_H

#include "stdafx.h"

#ifndef PLAYER_H
#define PLAYER_H
#include "Player.h"

#endif // !PLAYER_H


#include <vector>

using namespace std;

//link between two regions, aka edge
struct mapLink
{
	//the linked regions
	size_t region1, region2;

	//constructor
	mapLink(size_t r1, size_t r2) : region1(r1), region2(r2) {}
};

//region, aka vertex
struct region
{
	//name of the region
	std::string name;

	//owner of the region
	Player *owner = nullptr;
	//number of tokens
	int tokens;

	//default constructor
	region() : owner(nullptr) {};

	//is it a mountain
	bool mountain;


	bool decline = false;

	//contructor
	region(string n) : name(n), mountain(false), tokens(0), owner(nullptr) {}
	region(string n, bool m, bool l) : name(n), mountain(m), owner(nullptr)
	{
		if (l) {
			tokens = 1;
			decline = true;
		}
		else
			tokens = 0;
	}
};

class Map {
private:
	//used to see if map is a connected graph
	void recursiveDepthFirstTraversal(std::vector<size_t> &, std::vector<bool> &, size_t);
public:
	//vector of all the regions
	std::vector<region> regions;
	//vector of all the links
	std::vector<mapLink> links;

	//constructor
	Map(const size_t, const size_t);

	//simply adds a new region of the chosen name
	void addRegion(string);


	//simply adds a new region of the chosen name
	void addRegion(string, char type);

	//adds a new link between 2 regions
	void addLink(const size_t, const size_t);

	//Returns vector with results of recursiveDepthFirstTraversal
	std::vector<size_t> dft(const size_t);

	// Checks if all regions are linked
	bool linked();

	bool empty();

	void decline(Player*);
};