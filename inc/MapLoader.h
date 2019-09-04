#pragma once

#include "GameNodes.h"
#include "Map.h"

namespace MapLoader {

	Map loadMap(std::string fileName);
	void seekFileStreamToLine(std::ifstream & inputStream, std::string lineContent);
	CountryInformation createCountryInformation(char * countryInfo);

};