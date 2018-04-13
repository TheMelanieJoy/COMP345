#pragma once

#include "stdafx.h"
#include "Map.h"
#include <string>

//used to convert a .map file into a map we can use
class MapReader {
private:
	//where the map is located on the pc
	std::string path = "";
public:
	//Constructor, sets the path
	MapReader(std::string p) : path(p) {};
	//Parses the .map file and returns an usable map
	Map makeMap();
};
