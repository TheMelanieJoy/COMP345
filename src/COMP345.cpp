// COMP345.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Map.cpp"


int main()
{
	//making a new map
	Map g = Map(10, 20);

	//fill up all regions
	g.addRegion("R0");
	g.addRegion("R1");
	g.addRegion("R2");
	g.addRegion("R3");
	g.addRegion("R4");

	// fill up all links
	g.addLink(0, 1);
	g.addLink(0, 2);
	g.addLink(0, 3);
	g.addLink(0, 4);

	// trying to add illegal links
	g.addLink(1, 1);
	g.addLink(5, 4);

	g.linked();

	std::cout << "\n";
}