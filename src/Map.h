#pragma once
#define MAP_H

#include "stdafx.h"
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
	std::string owner;
	//number of tokens
	int tokens;

	//default constructor
	region() {};

	//contructor
	region(string n) : name(n) {}
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

	//adds a new link between 2 regions
	void addLink(const size_t, const size_t);

	//Returns vector with results of recursiveDepthFirstTraversal
	std::vector<size_t> dft(const size_t);

	// Checks if all regions are linked
	bool linked();

	bool empty();
};