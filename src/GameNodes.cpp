#include "GameNodes.h"
#include "utility.h"

CountryInformation::CountryInformation(int id, int x, int y, int contId, std::string countName, std::vector<int> neigboursIds) :
	countryId(new int(id)) , xCoordinate(new int(x)), yCoordinate (new int(y)),
	continentId(new int(contId)), countryName(new std::string(countName)), neighbouringCountriesIds(neigboursIds)
{
}

CountryInformation::~CountryInformation()
{
	Utility::safeDelete( countryId);
	Utility::safeDelete( xCoordinate);
	Utility::safeDelete( yCoordinate);
	Utility::safeDelete( continentId);
	Utility::safeDelete( countryName);

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

ContinentInformation::ContinentInformation(std::string name, int id) :
	continentName(new std::string(name)), continentId(new int(id))
{
}

ContinentInformation::~ContinentInformation()
{
	Utility::safeDelete(continentName);
	Utility::safeDelete(continentId);
}
