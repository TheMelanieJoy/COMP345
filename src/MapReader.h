#pragma once
#define MAP_READER_H

#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class MapReader {
public:
	std::string path = "";

	MapReader(std::string p) : path(p) {};

	Map makeMap();
};