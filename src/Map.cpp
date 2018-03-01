#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include "Map.h"

using namespace std;

void Map::recursiveDepthFirstTraversal(std::vector<size_t> & result, std::vector<bool> & visited, size_t v) {
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

Map::Map(const size_t regionCount, const size_t linkCount) {
	//tells the vectors how big we expect them to be
	regions.reserve(regionCount);
	links.reserve(linkCount);
}

void Map::addRegion(string name) {
	regions.push_back(region(name));
}

void Map::addLink(const size_t region1Index, const size_t region2Index) {
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

std::vector<size_t> Map::dft(const size_t region) {
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

bool Map::linked() {
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