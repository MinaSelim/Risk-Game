#include "Map.h"
#include "ErrorCodes.h"



Map::Map(std::vector<CountryInformation> countries)
{
	for (unsigned int i = 0; i < countries.size(); i++)
	{
		CountryNode node{0};
		node.countryInformation = countries[i];
		countriesGraph.push_back(node);
	}

	attachEdgesToNodes();

	validateMap();
}


void Map::validateMap()
{
	resetVisitedNodes();

	visitAllUnvisitedEdgesOfNode(&countriesGraph[0]);

	for (unsigned int i = 0; i < countriesGraph.size(); i++)
	{
		if (countriesGraph[i].visited == false)
		{
			throw INVALID_MAP;
		}
	}

	
}

void Map::visitAllUnvisitedEdgesOfNode(CountryNode * node)
{
	node->visited = true;
	auto neighbours = node->neighbouringCountries;
	for (unsigned int i = 0; i < neighbours.size(); i++)
	{
		if (neighbours[i]->visited == false)
		{
			visitAllUnvisitedEdgesOfNode(neighbours[i]);
		}
	}


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

void Map::resetVisitedNodes()
{
	for (unsigned int i = 0; i < countriesGraph.size(); i++)
	{
		countriesGraph[i].visited = false;
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

