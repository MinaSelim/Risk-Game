#include "Map.h"



Map::Map(std::vector<CountryInformation> countries)
{
	for (unsigned int i = 0; i < countries.size(); i++)
	{
		CountryNode node;
		node.countryInformation = countries[i];
		countriesGraph.push_back(node);
	}

	attachEdgesToNodes();
}

void Map::attachEdgesToNodes()
{
	for (unsigned int i = 0; i < countriesGraph.size(); i++)
	{
		auto neigbouringCountriesAsStrings = countriesGraph[i].countryInformation.neighbouringCountriesAsStrings;
		for (unsigned int j = 0; j < neigbouringCountriesAsStrings.size(); j++)
		{
			CountryNode * node = getNodeFromGraphByString(neigbouringCountriesAsStrings[j]);
			countriesGraph[i].neighbouringCountries.push_back(node);
		}
	}
}

CountryNode * Map::getNodeFromGraphByString(std::string countryName)
{
	for (unsigned int i = 0; i < countriesGraph.size(); i++)
	{
		if (countriesGraph[i].countryInformation.locationName.compare(countryName) == 0)
		{
			return &countriesGraph[i];
		}
	}

	throw 1;
}

