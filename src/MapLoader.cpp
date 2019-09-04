
#include "MapLoader.h"
#include "Utility.h"

#include <iostream>
#include <fstream>
#include <cstring>

//#define Logging

Map MapLoader::loadMap(std::string fileName)
{
	std::ifstream mapFile(fileName);
	seekFileStreamToLine(mapFile, "[Territories]");
	std::vector<CountryInformation> countries;

	std::streamsize  count = 400;
	char nextLine[400];

	while (!mapFile.eof())
	{
		mapFile.getline(nextLine, count);
		if (std::strlen(nextLine) != 0)
		{
			#ifdef Logging
				std::cout << nextLine << std::endl;
			#endif

			countries.push_back(createCountryInformation(nextLine));
		}
	}

	Map map(countries);

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

CountryInformation MapLoader::createCountryInformation(char * countryInfo)
{
	CountryInformation info{0};
	char * token = nullptr;
	char * context = nullptr;
	char delim [] = ",";

	token = strtok_s(countryInfo, delim, &context);
	info.locationName = token;

	token = strtok_s(nullptr, delim, &context);
	info.xCoordinate = Utility::convertCStringToNumber(token);

	token = strtok_s(nullptr, delim, &context);
	info.yCoordinate = Utility::convertCStringToNumber(token);

	token = strtok_s(nullptr, delim, &context);
	info.continentName = token;

	token = strtok_s(nullptr, delim, &context);

	while (token != nullptr)
	{
		info.neighbouringCountriesAsStrings.push_back(token);
		token = strtok_s(nullptr, delim, &context);
	}
	
	
	return info;
}

