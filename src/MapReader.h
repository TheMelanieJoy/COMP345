#pragma once

#include "stdafx.h"
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