#include "stdafx.h"
#include <iostream>
#include <string>
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
	//vector of all the regions
	std::vector<region> regions;
	//vector of all the links
	std::vector<mapLink> links;

public:

	//constructor
	Map(const size_t regionCount, const size_t linkCount) {
		//tells the vectors how big we expect them to be
		regions.reserve(regionCount);
		links.reserve(linkCount);
	}

	//simply adds a new region of the chosen name
	void addRegion(string name) {
		regions.push_back(region(name));
	}

	//adds a new link between 2 regions
	void addLink(const size_t region1Index, const size_t region2Index) {
		//if the link index is bigger than the ammount of regions, something has gone wrong
		if (regions.size() <= region1Index || regions.size() <= region2Index) {
			std::cout << "Error: link index higher than ammount of regions \n";
			return;
		}
		//if the link is to itself, it is unneeded
		if (region1Index == region2Index) {
			std::cout << "Error: link refers to the same region twice \n";
			return;
		}

		//we add 2 links since every region can be visited both ways
		//simpler than asking rest of code to try to go either way on a link
		links.push_back(mapLink(region1Index, region2Index));
		links.push_back(mapLink(region2Index, region1Index));
	}

private:
	//used to see if map is a connected graph
	void recursiveDepthFirstTraversal(std::vector<size_t> & result, std::vector<bool> & visited, size_t v) {
		//if we already visited this region, return
		if (visited[v]) return;

		//otherwise add the region to the final vector
		result.push_back(v);

		//and note that it has been visited in the visited array
		visited[v] = true;

		//we go through our vector of links
		for (const auto link : links) {
			//we're only looking for the links that start with our region
			if (link.region1 != v) continue;
			//if we find one, we continue the recursive traversal
			recursiveDepthFirstTraversal(result, visited, link.region2);
		}
	}

public:

	//Returns vector with results of recursiveDepthFirstTraversal
	std::vector<size_t> dft(const size_t region) {
		
		//if the index is bigger than the ammount of regions, then it doesnt exist
		if (regions.size() <= region) {
			std::cout << "Error: requested region doesn't exist \n";
			return std::vector<size_t>();
		}

		//make the vector holding the visited
		std::vector<bool> visited(regions.size());
		//make the vector holding the results
		std::vector<size_t> result;
		//we expect the result to be at most as big as our regions
		result.reserve(regions.size());

		//call the dft
		recursiveDepthFirstTraversal(result, visited, region);
		return result;
	}

	// Checks if all regions are linked
	bool linked() {
		//do a depth first traversal of the regions starting at 0
		auto dftResult = dft(0);

		//if the result is as big as the vector of regions, then all regions must be linked
		if (dftResult.size() == regions.size()) {
			std::cout << "All regions are linked \n";
			return true;
		}

		std::cout << "Error: not all regions are linked \n";
		return false;
	}
};