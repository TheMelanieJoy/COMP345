#include "stdafx.h"
#include "MapReader.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

Map MapReader::makeMap() {

	Map m = Map(0,0);

	try {

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


		m = Map(regions, regions*regions);

		//reading all regions

		//which word is being read
		int word = 1;

		//position of the char
		pos = 0;

		//getting the char
		c = words.at(word)[pos];

		//output
		s = "";

		bool named = false;
		bool details = false;
		bool tribal = false;
		bool coastal = false;
		bool magic = false;
		bool cavern = false;
		bool mine = false;

		int stage = 0;

		char type = '0';


		//go through the map getting all region names until we reach the links
		while (c != '[') {
			//part where we get the region name
			if (c == '=') {
				named = true;
				pos++;
				c = words.at(word)[pos];
			}

			else if (!named) {
				s += c;

				pos++;

				if (pos >= words.size())
					break;

				c = words.at(word)[pos];
			}
			//part where we check for special attributes in the region
			else if (details) {
				while (stage < 5) {
					if (words.at(word).size() <= pos) {
						std::cout << "Illegal map." << endl;
						return Map(0, 0);
					}
					stage++;
					pos++;
					c = words.at(word)[pos];
					if (c == '1') {
						switch (stage)
						{
						case 1: tribal = true;
							break;
						case 2: coastal = true;
							break;
						case 3: magic = true;
							break;
						case 4: cavern = true;
							break;
						case 5: mine = true;
							break;
						default:
							break;
						}
					}
				}

				m.addRegion(s, type, tribal, coastal, magic, cavern, mine);

				word++;
				pos = 0;
				s = "";
				c = words.at(word)[pos];
				details = false;
				named = false;
				stage = 0;


				tribal = false;
				coastal = false;
				magic = false;
				cavern = false;
				mine = false;
			}
			//Part where we get the type of the region
			else {
				if (c == ',') {
					details = true;
					pos++;
					c = words.at(word)[pos];
					type = c;
					//m.addRegion(s, c);

					//word++;
					//pos = 0;
					//s = "";
					//c = words.at(word)[pos];


				}
				else if (words.at(word).size() <= pos) {
					m.addRegion(s);
					word++;
					pos = 0;
					s = "";
					c = words.at(word)[pos];
				}
				else {
					s += c;
					pos++;
					c = words.at(word)[pos];
				}

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

		int linkStart = word;

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
					int i = 1;
					while (word - linkStart > 9 * i) {
						pos++;
						i *= 10;
					}
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
	}
	catch (const std::exception& e) {
		std::cout << "Illegal map." << endl;
		return Map(0, 0);
	}


	return m;
}
