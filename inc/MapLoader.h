#pragma once

#include "Map.h"

namespace MapLoader {
	Map * loadMap(std::string fileName);
}

namespace {
	void seekFileStreamToLine(std::ifstream & inputStream, std::string lineContent);
	CountryInformation * createCountryInformation(char * countryInfo);
	ContinentInformation * createContinentInformation(char * continentInfo);
	void createBordersInformation(char * bordersInfo, std::vector<CountryInformation*>  countries);
	void pushNeighbouringCountry(std::vector<CountryInformation*> countries, int id, std::vector<int> neighbouringIds);
}