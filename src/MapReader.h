#define MAP_READER

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Map.h"

class MapReader {
public:
	std::string path = "";

	MapReader(std::string p) : path(p) {};

	Map makeMap();
};