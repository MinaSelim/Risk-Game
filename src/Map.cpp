#include "Map.h"
#include "ErrorCodes.h"
#include <new>



Map::Map(std::vector<CountryInformation*> countries)
{
	for (unsigned int i = 0; i < countries.size(); i++)
	{
		CountryNode * node = new CountryNode(countries[i]);
		countriesGraph.push_back(node);
	}

	attachEdgesToNodes();

	validateMap();

}


void Map::validateMap()
{
	resetVisitedNodes();

	visitAllUnvisitedEdgesOfNode(countriesGraph[0]);

	for (unsigned int i = 0; i < countriesGraph.size(); i++)
	{
		if (*countriesGraph[i]->visited == false)
		{
			throw INVALID_MAP;
		}
	}

}

void Map::visitAllUnvisitedEdgesOfNode(CountryNode * node)
{
	*node->visited = true;
	auto neighbours = node->neighbouringCountries;
	for (unsigned int i = 0; i < neighbours.size(); i++)
	{
		if (*neighbours[i]->visited == false)
		{
			visitAllUnvisitedEdgesOfNode(neighbours[i]);
		}
	}


}

void Map::attachEdgesToNodes()
{
	for (unsigned int i = 0; i < countriesGraph.size(); i++)
	{
		auto neigbouringCountriesAsIds = countriesGraph[i]->countryInformation->neighbouringCountriesIds;
		for (unsigned int j = 0; j < neigbouringCountriesAsIds.size(); j++)
		{
			CountryNode * node = getNodeFromGraphById(neigbouringCountriesAsIds[j]);
			countriesGraph[i]->neighbouringCountries.push_back(node);
		}
	}
}

void Map::resetVisitedNodes()
{
	for (unsigned int i = 0; i < countriesGraph.size(); i++)
	{
		*countriesGraph[i]->visited = false;
	}
}

CountryNode * Map::getNodeFromGraphById(int countryId)
{
	for (unsigned int i = 0; i < countriesGraph.size(); i++)
	{
		if (*countriesGraph[i]->countryInformation->countryId == countryId)
		{
			return countriesGraph[i];
		}
	}

	throw 1;
}

Map::~Map()
{
	int * i = new int(0);
	auto maxsSize = countriesGraph.size();
	int test = 0;
	while (test < maxsSize)
	{
		delete countriesGraph[test];
		*i = *i + 1;
		test = *i;
	}

	delete i;

}