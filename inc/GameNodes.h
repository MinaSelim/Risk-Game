#pragma once
#include <string>
#include <vector>

struct CountryInformation {
	int * countryId;
	int *xCoordinate;
	int *yCoordinate;
	int *continentId;
	//std::string continentName;
	std::string *countryName;
	std::vector<int> neighbouringCountriesIds;
	CountryInformation(int id, int x, int y, int contId, std::string countName, std::vector<int> neigboursIds);
	virtual ~CountryInformation();
};

struct CountryNode {
	CountryInformation * countryInformation;
	std::vector<CountryNode*> neighbouringCountries;
	bool * visited;
	CountryNode(CountryInformation * info);
	~CountryNode();
};

struct ContinentInformation {
	std::string * continentName;
	int * continentId;
	ContinentInformation(std::string name, int id);
	~ContinentInformation();
};