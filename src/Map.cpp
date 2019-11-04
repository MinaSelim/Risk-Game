#include "Map.h"
#include "ErrorCodes.h"
#include "Utility.h"
#include "Player.h"
#include <new>

CountryInformation::CountryInformation(int id, int x, int y, int contId, std::string countName, std::vector<int> neigboursIds) :
	countryId(new int(id)), xCoordinate(new int(x)), yCoordinate(new int(y)),
	continentId(new int(contId)), countryName(new std::string(countName)), neighbouringCountriesIds(neigboursIds)
{
}

CountryInformation::CountryInformation(CountryInformation & info) :
	countryId(new int(*info.countryId)), xCoordinate(new int(*info.xCoordinate)), yCoordinate(new int(*info.yCoordinate)),
	continentId(new int(*info.continentId)), countryName(new std::string(*info.countryName))
{
	for (unsigned int i = 0; i < info.neighbouringCountriesIds.size(); i++)
	{
		neighbouringCountriesIds.push_back(info.neighbouringCountriesIds[i]);
	}
}


string CountryInformation::getCountryName()
{
	return *this->countryName;
}

CountryInformation::~CountryInformation()
{
	Utility::safeDelete(countryId);
	Utility::safeDelete(xCoordinate);
	Utility::safeDelete(yCoordinate);
	Utility::safeDelete(continentId);
	Utility::safeDelete(countryName);

}


ContinentInformation::ContinentInformation(std::string name, int cv, int id) :
	continentName(new std::string(name)), controlValue(new int(cv)), continentId(new int(id))
{
}

ContinentInformation::~ContinentInformation()
{
	Utility::safeDelete(continentName);
	Utility::safeDelete(controlValue);
}




CountryNode::CountryNode(CountryInformation * info) :
	countryInformation(info), visited(new bool(false)), neighbouringCountries(0), playerInfo(new PlayerNode())
{
}

CountryNode::CountryNode(const CountryNode & node):
	countryInformation(new CountryInformation(*node.countryInformation)), visited(new bool(*node.visited)), neighbouringCountries(0), playerInfo(new PlayerNode())
{
}

CountryNode::~CountryNode()
{
	Utility::safeDelete(countryInformation);
	Utility::safeDelete(visited);
}

Map::Map(std::vector<CountryInformation*> countries, std::vector<ContinentInformation*> continents)
{
	countriesGraph = new std::vector<CountryNode*>();
	for (unsigned int i = 0; i < countries.size(); i++)
	{
		CountryNode * node = new CountryNode(countries[i]);
		countriesGraph->push_back(node);
	}

	continentsInfo = continents;
	attachEdgesToNodes();
	validateMap();

}

Map::Map(Map & map)
{
	countriesGraph = new std::vector<CountryNode*>();
	for (unsigned int i = 0; i < map.countriesGraph->size(); i++)
	{
		CountryNode * node = new CountryNode(*(*map.countriesGraph)[i]);
		countriesGraph->push_back(node);
	}

	attachEdgesToNodes();
	validateMap();
}


void Map::validateMap()
{
	resetVisitedNodes();

	visitAllUnvisitedEdgesOfNode((*countriesGraph)[0]);

	for (unsigned int i = 0; i < countriesGraph->size(); i++) // If a node is unvisited, It means that the map is invalid
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
	std::vector<int> continentsIds = getContinentIds();

	// This for loop goes through each continents, and tries to visit all the nodes inside that continent
	for (unsigned int i = 0; i < continentsIds.size(); i++) 
	{
		CountryNode * node = getNodeInContinent(continentsIds[i]);
		visitAllUnvisitedEdgesOfNodeInContinent(node, continentsIds[i]);

		for (unsigned int j = 0; j < countriesGraph->size(); j++) // Checks if all the nodes in the continent have been visited
		{
			if (*(*countriesGraph)[j]->visited == false && *(*countriesGraph)[j]->countryInformation->continentId == continentsIds[i])
			{
				throw INTERCONNECTED_CONTINENT_ERROR;
			}
		}

		resetVisitedNodes(); // reset the nodes for the next test
	}

}

vector<int> Map::getContinentIds() 
{
	vector<int> continentsIds;
	for (unsigned int i = 0; i < countriesGraph->size(); i++)
	{
		auto continentId = *(*countriesGraph)[i]->countryInformation->continentId;
		if (!Utility::vectorContains(continentsIds, continentId))
		{
			continentsIds.push_back({ continentId });
		}
	}
	return continentsIds;
}

bool Map::checkUserContinents(int continentId, string playerName)
{
	for (unsigned int i = 0; i < countriesGraph->size(); i++) {
		if (*(*countriesGraph)[i]->countryInformation->continentId == continentId &&
			(*countriesGraph)[i]->playerInfo->getPlayer()->getPlayerName().compare(playerName)) {
			return false;
		}
	}
	return true;
}

//simple graph travelling algorithm (limited by continent)
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

// attaches all the edges to the nodes
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
	for (unsigned int i = 0; i < countriesGraph->size(); i++) 
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



CountryNode * Map::getNodeFromGraphByName(string countryName)
{
	for (unsigned int i = 0; i < countriesGraph->size(); i++)
	{
		if ((*countriesGraph)[i]->countryInformation->countryName->compare(countryName) == 0)
		{
			return (*countriesGraph)[i];
		}
	}
	return nullptr;
}

int Map::getNumberOfCountriesInMap()
{
	int numberOfCountries = 0;
	for (unsigned int i = 0; i < this->countriesGraph->size(); i++) {
		numberOfCountries += 1;
	}
	return numberOfCountries;
}

CountryNode * Map::getFirstNode()
{
	return (*countriesGraph)[0];
}

vector<CountryNode*> Map::getCountriesGraph()
{
	std::vector<CountryNode*> vect;
	for (unsigned int i = 0; i < countriesGraph->size(); i++)
	{
		vect.push_back((*countriesGraph)[i]);
	}

	return vect;
}

int Map::getContinentControlValue(int continentId)
{
	for (unsigned i = 0; i < continentsInfo.size(); i++) {
		if (*continentsInfo[i]->continentId == continentId) {
			return *continentsInfo[i]->controlValue;
		}
	}

	//TODO: throw proper error code
	throw -1;
}


Map::~Map()
{
	int * i = new int(0);
	auto maxsSize = countriesGraph->size();
	unsigned int test = 0;
	while (test < maxsSize)
	{
		delete (*countriesGraph)[test];
		*i = *i + 1;
		test = *i;
	}

	delete countriesGraph;
	delete i;

}

PlayerNode::PlayerNode(): player(nullptr), numOfArmies(new int(0))
{
}


PlayerNode::PlayerNode(Player * player, int armies): player(player), numOfArmies(new int(armies))
{
}

PlayerNode::~PlayerNode()
{
	delete numOfArmies;
	numOfArmies = nullptr;
}

Player * PlayerNode::getPlayer()
{
	return player;
}

void PlayerNode::assignPlayer(Player * playerToSet)
{

	player = playerToSet;
}
