#pragma once

#include "stdafx.h"
#include "Map.h"
#include <string>

class MapReader {
private:
	std::string path = "";
public:
	MapReader(std::string p) : path(p) {};
	Map makeMap();
};