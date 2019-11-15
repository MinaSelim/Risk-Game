#include "MapLoader.h"
#include "Utility.h"
#include "ErrorCodes.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>


//#define Logging
Map * MapLoader::loadMap(std::string fileName)
{
	if (!Utility::fileExist(fileName))
	{
		throw FILE_DOES_NOT_EXIST;
	}
	
	std::ifstream mapFile(fileName);
	seekFileStreamToLine(mapFile, "[continents]");
	std::vector<ContinentInformation*> continents;
	std::vector<CountryInformation*> countries;
	std::vector<CountryInformation*> countriesWithNeighbours;

	std::streamsize  count = 400;
	char nextLine[400];

	int continentId = 0;

	while (!mapFile.eof())
	{
		mapFile.getline(nextLine, count);

#ifdef Logging
		std::cout << nextLine << std::endl;
#endif

		while (std::string("[countries]").compare(nextLine)) {
			continentId++;
			if (std::string("").compare(nextLine)) {
				continents.push_back(createContinentInformation(nextLine, continentId));
			}
			mapFile.getline(nextLine, count);
		}

		mapFile.getline(nextLine, count);

		while (std::string("[borders]").compare(nextLine)) {
			if (std::string("").compare(nextLine)) {
				countries.push_back(createCountryInformation(nextLine));
			}
			mapFile.getline(nextLine, count);
		}

		mapFile.getline(nextLine, count);

		while (!mapFile.eof()) {
			if (std::string("").compare(nextLine)) {
				createBordersInformation(nextLine, countries);
				mapFile.getline(nextLine, count);
			}
		}
	}

	Map * map = new Map(countries, continents);
	return map;
}


namespace
{
	void seekFileStreamToLine(std::ifstream & inputStream, std::string lineContent) //seeks to a certain line in the file
	{
		std::streamsize  count = 400;
		char nextLine[400];

		while (!inputStream.eof())
		{
			inputStream.getline(nextLine, count);

			if (!lineContent.compare(nextLine))
			{
				return;
			}
		}
	}

	CountryInformation * createCountryInformation(char * countryInfo)
	{
		char * token = nullptr;
		char * context = nullptr;
		char delim[] = " ";

		token = strtok_s(countryInfo, delim, &context);
		int countryId = Utility::convertCStringToNumber(token);

		token = strtok_s(nullptr, delim, &context);
		std::string countryName = token;

		token = strtok_s(nullptr, delim, &context);
		int continentId = Utility::convertCStringToNumber(token);

		token = strtok_s(nullptr, delim, &context);
		int xCoordinate = Utility::convertCStringToNumber(token);

		token = strtok_s(nullptr, delim, &context);
		int yCoordinate = Utility::convertCStringToNumber(token);

		std::vector<int> neighboursId;

		token = strtok_s(nullptr, delim, &context);
		CountryInformation * info = new CountryInformation(countryId, xCoordinate, yCoordinate, continentId, countryName, neighboursId);

		while (token != nullptr)
		{
			token = strtok_s(nullptr, delim, &context);

		}

		return info;
	}



	ContinentInformation * createContinentInformation(char * continentInfo, int id)
	{
		char * token = nullptr;
		char * context = nullptr;
		char delim[] = " ";

		token = strtok_s(continentInfo, delim, &context);
		std::string continentName = token;

		token = strtok_s(nullptr, delim, &context);
		int controlValue = Utility::convertCStringToNumber(token);

	ContinentInformation * info = new ContinentInformation(continentName, controlValue, id);

		while (token != nullptr)
		{
			token = strtok_s(nullptr, delim, &context);
		}

		return info;
	}

	// This function attaches borders ids to the countryInfo
	void createBordersInformation(char * bordersInformation, std::vector<CountryInformation*>  countries)
	{
		char * token = nullptr;
		char * context = nullptr;
		char delim[] = " ";
		int countryId;
		std::vector<int> neighbouringIds;

		token = strtok_s(bordersInformation, delim, &context);
		countryId = Utility::convertCStringToNumber(token);

		token = strtok_s(nullptr, delim, &context);

		while (token != nullptr)
		{
			neighbouringIds.push_back(Utility::convertCStringToNumber(token));
			token = strtok_s(nullptr, delim, &context);
		}
		pushNeighbouringCountry(countries, countryId, neighbouringIds);


		return;
	}

	void pushNeighbouringCountry(std::vector<CountryInformation*>  countries, int id, std::vector<int> neighbouringIds) {
		for (unsigned int i = 0; i < countries.size(); i++) {
			if (*countries[i]->countryId == id) {
				countries[i]->neighbouringCountriesIds = neighbouringIds;
				break;
			}
		}
	}


}



void ConquestMapReader::conquestCreateListOfNeighbors(char * token,int & countryId, map<string, int>& countryIds, CountryInformation & country)
{
	if (countryIds.count(token) > 0) {
		auto pos = countryIds.find(token);
		int  tempCountryId = pos->second;
		country.neighbouringCountriesIds.push_back(tempCountryId);
	}
	else 
	{
		string countryName = token;
		countryIds.insert({ countryName, countryId });
		country.neighbouringCountriesIds.push_back(countryId);
		countryId++;
	}
}

CountryInformation * ConquestMapReader::conquestCreateCountryInformation(char * countryInfo, std::vector<ContinentInformation*>& continents, int &countryId, map<string,int> & countryIds)
{
	char * token = nullptr;
	char * context = nullptr;
	char delim[] = ",";
	int continentId=0;
	CountryInformation * info;

	token = strtok_s(countryInfo, delim, &context);
	std::string countryName = token;

	token = strtok_s(nullptr, delim, &context);
	int xCoordinate = Utility::convertCStringToNumber(token);

	token = strtok_s(nullptr, delim, &context);
	int yCoordinate = Utility::convertCStringToNumber(token);

	token = strtok_s(nullptr, delim, &context);
	std::string continentName = token;
	for (unsigned int i = 0; i < continents.size(); i++) {
		if (continents.at(i)->continentName->compare(continentName)==0) {
			continentId = *continents.at(i)->continentId;
		}
	}
	token = strtok_s(nullptr, delim, &context);

	std::vector<int> neighbours;

	if (countryIds.count(countryName) > 0) 
	{
		auto pos = countryIds.find(countryName);
		info = new CountryInformation(pos->second, xCoordinate, yCoordinate, continentId, countryName, neighbours);
	}
	else 
	{
		info = new CountryInformation(countryId, xCoordinate, yCoordinate, continentId, countryName, neighbours);
		countryIds.insert({ countryName, countryId });
		countryId++;
	}
	while (token != nullptr)
	{	
		conquestCreateListOfNeighbors(token, countryId, countryIds, *info);
		token = strtok_s(nullptr, delim, &context);
	}
	return info;
}



Map * ConquestMapReader::conquestLoadMap(std::string fileName)
{
	if (!Utility::fileExist(fileName))
	{
		throw FILE_DOES_NOT_EXIST;
	}
	std::ifstream mapFile(fileName);
	seekFileStreamToLine(mapFile, "[Continents]");
	std::vector<CountryInformation*> countries;
	std::vector<ContinentInformation*> continents;
	map<string, int> countryIds;
	int countryId   = 1;
	int continentId = 0;

	std::streamsize  count = 400;
	char nextLine[400];

	while (!mapFile.eof())
	{
		mapFile.getline(nextLine, count);
		while (std::string("[Territories]").compare(nextLine)) {
			continentId++;
			if (std::string("").compare(nextLine)) {
				continents.push_back(conquestCreateContinentInformation(nextLine, continentId));
			}
			mapFile.getline(nextLine, count);
		}

		mapFile.getline(nextLine, count);


		while (!mapFile.eof()) {
			if (std::string("").compare(nextLine)) {
				countries.push_back(conquestCreateCountryInformation(nextLine, continents, countryId, countryIds));
			}
			mapFile.getline(nextLine, count);
		}
	}
	Map * map = new Map(countries, continents);
	return map;
}
ContinentInformation * ConquestMapReader::conquestCreateContinentInformation(char * continentInfo, int id)
{
	char * token = nullptr;
	char * context = nullptr;
	char delim[] = "=";

	token = strtok_s(continentInfo, delim, &context);
	std::string continentName = token;

	token = strtok_s(nullptr, delim, &context);
	int controlValue = Utility::convertCStringToNumber(token);

	ContinentInformation * info = new ContinentInformation(continentName, controlValue, id);

	while (token != nullptr)
	{
		token = strtok_s(nullptr, delim, &context);
	}
	return info;
}

MapLoaderAdapter::MapLoaderAdapter()
{
}

MapLoaderAdapter::MapLoaderAdapter(ConquestMapReader * mapReader) : MapLoader()
{
	conquestMapReader = mapReader;
}

Map * MapLoaderAdapter::loadMap(std::string fileName)
{
	conquestMapReader->conquestLoadMap(fileName);
}


