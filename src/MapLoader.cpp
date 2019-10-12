#include "MapLoader.h"
#include "Utility.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

//#define Logging
Map * MapLoader::loadMap(std::string fileName)
{
	std::ifstream mapFile(fileName);
	seekFileStreamToLine(mapFile, "[continents]");
	std::vector<ContinentInformation*> continents;
	std::vector<CountryInformation*> countries;
	std::vector<CountryInformation*> countriesWithNeighbours;

	std::streamsize  count = 400;
	char nextLine[400];

	while (!mapFile.eof())
	{
		mapFile.getline(nextLine, count);

#ifdef Logging
		std::cout << nextLine << std::endl;
#endif
		mapFile.getline(nextLine, count);

		while (std::string("[countries]").compare(nextLine)) {
			if (std::string("").compare(nextLine)) {
				continents.push_back(createContinentInformation(nextLine));
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

	Map * map = new Map(countries);
	return map;
}

void MapLoader::seekFileStreamToLine(std::ifstream & inputStream, std::string lineContent)
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

CountryInformation * MapLoader::createCountryInformation(char * countryInfo)
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

ContinentInformation * MapLoader::createContinentInformation(char * continentInfo)
{
	char * token = nullptr;
	char * context = nullptr;
	char delim[] = " ";

	token = strtok_s(continentInfo, delim, &context);
	std::string continentName = token;

	token = strtok_s(nullptr, delim, &context);
	int continentId = Utility::convertCStringToNumber(token);

	ContinentInformation * info = new ContinentInformation(continentName, continentId);

	while (token != nullptr)
	{
		token = strtok_s(nullptr, delim, &context);
	}

	return info;
}

void MapLoader::createBordersInformation(char * bordersInformation, std::vector<CountryInformation*>  countries)
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

void MapLoader::pushNeighbouringCountry(std::vector<CountryInformation*>  countries, int id, std::vector<int> neighbouringIds) {
	for (unsigned int i = 0; i < countries.size(); i++) {
		if (*countries[i]->countryId == id) {
			countries[i]->neighbouringCountriesIds = neighbouringIds;
			break;
		}
	}
}

