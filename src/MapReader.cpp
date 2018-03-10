#include "stdafx.h"
#include "MapReader.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

Map MapReader::makeMap() {

	std::cout << "Building map" << std::endl;

	if (path == "") {
		std::cout << "No path provided, returning." << std::endl;
		return Map(0, 0);
	}

	// Vector to hold our words we read in.
	std::vector <std::string> words;
	// Temp string
	std::string str;
	// open the path
	std::ifstream fin(path);

	//read the file
	while (fin >> str)
	{
		words.push_back(str);
	}
	fin.close();

	//checking if regions is recorded
	if (words.at(0).substr(0, 9) != "[Regions=") {
		std::cout << "Illegal map." << endl;
		return Map(0, 0);
	}

	//getting the number of regions which is at position 9 and above
	int pos = 9;
	char c = words.at(0)[pos];

	string s = "";

	while (c != ']') {
		s += c;
		pos++;
		c = words.at(0)[pos];
	}

	//parsing the int
	std::stringstream parseInt(s);

	int regions = 0;
	parseInt >> regions;

	Map m = Map(regions, regions*regions);

	//reading all regions

	//which word is being read
	int word = 1;

	//position of the char
	pos = 0;

	//getting the char
	c = words.at(word)[pos];

	//output
	s = "";

	//go through the map getting all region names until we reach the links
	while (c != '[') {

		if (c == '=') {
			m.addRegion(s);
			word++;
			pos = 0;
			s = "";
			c = words.at(word)[pos];
		}

		else {
			s += c;

			pos++;

			if (pos >= words.size())
				break;

			c = words.at(word)[pos];
		}
	}

	//links

	//checking if links is recorded
	if (words.at(word).substr(0, 7) != "[Links=") {
		std::cout << "Illegal map." << endl;
		return Map(0, 0);
	}


	word++;
	pos = 2;

	//index of first link
	string s1 = "";
	//index of second link
	string s2 = "";
	c = words.at(word)[pos];

	//whether first or second link is being looked at
	bool firstLink = true;

	//going through the rest of the map recording all the links
	while (word < words.size()) {
		c = words.at(word)[pos];

		if (!isdigit(c)) {
			if (c != ',') {
				std::cout << "Illegal map." << endl;
				return Map(0, 0);
			}
			else {
				pos++;
				if (firstLink)
					firstLink = false;
			}
		}

		else {
			if (firstLink)
				s1 += c;
			else
				s2 += c;
			pos++;
			if (pos >= words.at(word).size()) {
				pos = 2;
				word++;
				firstLink = true;

				std::stringstream parseS1(s1);
				std::stringstream parseS2(s2);

				int link1 = 0;
				int link2 = 0;
				parseS1 >> link1;
				parseS2 >> link2;

				m.addLink(link1, link2);

				s1 = "";
				s2 = "";
			}

		}
	}


	return m;
}