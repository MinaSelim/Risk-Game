#pragma once
#include <vector>
#include <string>
#include  <new>

using namespace std;
class Player;

struct ContinentInformation {
	string * continentName;
	int * controlValue;
	int * continentId;
	ContinentInformation(string name, int controlValue, int id);
	ContinentInformation(const ContinentInformation & ci);
	~ContinentInformation();
};

struct CountryInformation {
	int * countryId;
	int *xCoordinate;
	int *yCoordinate;
	int *continentId;
	string *countryName;
	vector<int> neighbouringCountriesIds;
	CountryInformation(int id, int x, int y, int contId, string countName, vector<int> neigboursIds);
	CountryInformation(CountryInformation & info);
	string getCountryName();
	virtual ~CountryInformation();
};


class PlayerNode {
private:
	Player * player;
	int * numOfArmies;
	
public:
	PlayerNode();
	PlayerNode(Player * player, int armies);
	~PlayerNode();
	int getNumberOfArmies() { return *numOfArmies; };
	Player * getPlayer();
	void assignPlayer(Player * player);
	void setNumberOfArmies(int number) { *numOfArmies = number; };
};

struct CountryNode {
	CountryInformation * countryInformation;
	vector<CountryNode*> neighbouringCountries;
	PlayerNode * playerInfo;
	bool * visited;
	CountryNode(CountryInformation * info);
	CountryNode(const CountryNode & node);
	~CountryNode();
};

class Map {

private:
	vector<CountryNode*> *countriesGraph;
	vector<ContinentInformation*> continentsInfo;

public:
	Map(vector<CountryInformation*> countries, vector<ContinentInformation*> continents);
	Map(const Map & map);
	CountryNode * getNodeFromGraphByName(string countryName);
	int getNumberOfCountriesInMap();
	CountryNode* getFirstNode();
	vector<CountryNode*> getCountriesGraph();
	virtual ~Map();
	std::vector<int> getContinentIds();
	bool checkUserContinents(int continentId, string playerName);
	CountryNode* getNodeFromGraphById(int countryId);
	int getContinentControlValue(int continentId);
	//const Map& operator=(const Map& m);

private:
	void validateMap();
	void validateContinents();
	void visitAllUnvisitedEdgesOfNodeInContinent(CountryNode * node, int continent);
	void visitAllUnvisitedEdgesOfNode(CountryNode * node);
	void attachEdgesToNodes();
	void resetVisitedNodes();
	CountryNode* getNodeInContinent(int continentId);
};


