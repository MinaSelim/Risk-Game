#include "Map.h"
#include "ErrorCodes.h"
#include "Utility.h"
#include <new>

CountryInformation::CountryInformation(int id, int x, int y, int contId, std::string countName, std::vector<int> neigboursIds) :
	countryId(new int(id)), xCoordinate(new int(x)), yCoordinate(new int(y)),
	continentId(new int(contId)), countryName(new std::string(countName)), neighbouringCountriesIds(neigboursIds)
{
}

CountryInformation::~CountryInformation()
{
	Utility::safeDelete(countryId);
	Utility::safeDelete(xCoordinate);
	Utility::safeDelete(yCoordinate);
	Utility::safeDelete(continentId);
	Utility::safeDelete(countryName);

}


ContinentInformation::ContinentInformation(std::string name, int id) :
	continentName(new std::string(name)), continentId(new int(id))
{
}

ContinentInformation::~ContinentInformation()
{
	Utility::safeDelete(continentName);
	Utility::safeDelete(continentId);
}


CountryNode::CountryNode(CountryInformation * info) :
	countryInformation(info), visited(new bool(false)), neighbouringCountries(0)
{
}

CountryNode::~CountryNode()
{
	Utility::safeDelete(countryInformation);
	Utility::safeDelete(visited);
}

Map::Map(std::vector<CountryInformation*> countries)
{
	countriesGraph = new std::vector<CountryNode*>();
	for (unsigned int i = 0; i < countries.size(); i++)
	{
		CountryNode * node = new CountryNode(countries[i]);
		countriesGraph->push_back(node);
	}

	attachEdgesToNodes();

	validateMap();

}


void Map::validateMap()
{
	resetVisitedNodes();

	visitAllUnvisitedEdgesOfNode((*countriesGraph)[0]);

	for (unsigned int i = 0; i < countriesGraph->size(); i++)
	{
		if (*(*countriesGraph)[i]->visited == false)
		{
			throw INVALID_MAP;
		}
	}

	resetVisitedNodes();
	validateContinents();

}

void Map::validateContinents()
{
	std::vector<int> continentsIds;
	for (int i = 0; i < countriesGraph->size(); i++)
	{
		auto continentId = *(*countriesGraph)[i]->countryInformation->continentId;
		if (!Utility::vectorContains(continentsIds, continentId))
		{
			continentsIds.push_back(continentId);
		}
	}

	for (int i = 0; i < continentsIds.size(); i++)
	{
		CountryNode * node = getNodeInContinent(continentsIds[i]);
		visitAllUnvisitedEdgesOfNodeInContinent(node, continentsIds[i]);

		for (unsigned int j = 0; j < countriesGraph->size(); j++)
		{
			if (*(*countriesGraph)[j]->visited == false && *(*countriesGraph)[j]->countryInformation->continentId == continentsIds[i])
			{
				throw INTERCONNECTED_CONTINENT_ERROR;
			}
		}

		resetVisitedNodes();
	}

}

void Map::visitAllUnvisitedEdgesOfNodeInContinent(CountryNode * node, int continent)
{
	*node->visited = true;
	auto neighbours = node->neighbouringCountries;
	for (unsigned int i = 0; i < neighbours.size(); i++)
	{
		if (*neighbours[i]->visited == false && *neighbours[i]->countryInformation->continentId == continent)
		{
			visitAllUnvisitedEdgesOfNodeInContinent(neighbours[i], continent);
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
	for (unsigned int i = 0; i < countriesGraph->size(); i++)
	{
		auto neigbouringCountriesAsIds = (*countriesGraph)[i]->countryInformation->neighbouringCountriesIds;
		for (unsigned int j = 0; j < neigbouringCountriesAsIds.size(); j++)
		{
			CountryNode * node = getNodeFromGraphById(neigbouringCountriesAsIds[j]);
			(*countriesGraph)[i]->neighbouringCountries.push_back(node);
		}
	}
}

void Map::resetVisitedNodes()
{
	for (unsigned int i = 0; i < countriesGraph->size(); i++)
	{
		*(*countriesGraph)[i]->visited = false;
	}
}

CountryNode * Map::getNodeInContinent(int continentId)
{
	for (auto i = 0; i < countriesGraph->size(); i++) 
	{
		if (*(*countriesGraph)[i]->countryInformation->continentId == continentId)
		{
			return (*countriesGraph)[i];
		}
	}

	return nullptr;
}

CountryNode * Map::getNodeFromGraphById(int countryId)
{
	for (unsigned int i = 0; i < countriesGraph->size(); i++)
	{
		if (*(*countriesGraph)[i]->countryInformation->countryId == countryId)
		{
			return (*countriesGraph)[i];
		}
	}

	throw 1;
}

Map::~Map()
{
	int * i = new int(0);
	auto maxsSize = countriesGraph->size();
	int test = 0;
	while (test < maxsSize)
	{
		delete (*countriesGraph)[test];
		*i = *i + 1;
		test = *i;
	}

	delete countriesGraph;
	delete i;

}