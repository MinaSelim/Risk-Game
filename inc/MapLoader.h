#pragma once

#include "Map.h"
#include <map>

class MapLoader {
public:
	MapLoader() {};
	virtual ~MapLoader() {};
	virtual Map * loadMap(std::string fileName);
};


namespace {
	bool seekFileStreamToLine(std::ifstream & inputStream, std::string lineContent);
	CountryInformation * createCountryInformation(char * countryInfo);
	ContinentInformation * createContinentInformation(char * continentInfo, int continentId);
	void createBordersInformation(char * bordersInfo, std::vector<CountryInformation*>  countries);
	void pushNeighbouringCountry(std::vector<CountryInformation*> countries, int id, std::vector<int> neighbouringIds);
};

class ConquestMapReader {

public:
	~ConquestMapReader() {};
	void conquestCreateListOfNeighbors(char * token, int & countryId, map<string, int>& countryIds, CountryInformation& country);
	CountryInformation*  conquestCreateCountryInformation(char*countryInfo, std::vector<ContinentInformation*> & continents, int &countryId, map<string, int>&countryIds);
	Map * conquestLoadMap(std::string fileName);
	ContinentInformation * conquestCreateContinentInformation(char * continentInfo, int id);
};

class MapLoaderAdapter: public MapLoader {
private:
	ConquestMapReader * conquestMapReader;
public:
	MapLoaderAdapter();
	~MapLoaderAdapter();
	MapLoaderAdapter(ConquestMapReader * mapReader);
	Map * loadMap(std::string fileName);

};




