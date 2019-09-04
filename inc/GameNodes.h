#pragma once
#include <string>
#include <vector>

struct CountryInformation {
	int xCoordinate;
	int yCoordinate;
	std::string continentName;
	std::string locationName;
	std::vector<std::string> neighbouringCountriesAsStrings;
};

struct CountryNode {
	CountryInformation countryInformation;
	std::vector<CountryNode*> neighbouringCountries;
};