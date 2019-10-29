#pragma once
#include <vector>
#include <string>
#include  <new>

using namespace std;

struct ContinentInformation {
	string * continentName;
	int * continentId;
	ContinentInformation(string name, int id);
	~ContinentInformation();
};

struct CountryInformation {
	int * countryId;
	int *xCoordinate;
	int *yCoordinate;
	int *continentId;
	//string continentName;
	string *countryName;
	vector<int> neighbouringCountriesIds;
	CountryInformation(int id, int x, int y, int contId, string countName, vector<int> neigboursIds);
	string getCountryName();
	virtual ~CountryInformation();
};

class PlayerNode {
private:
	string * playerName;
	int * numOfArmies;
public:
	PlayerNode();
	PlayerNode(string name, int armies);
	~PlayerNode();
	inline int getNumberOfArmies() { return *numOfArmies; };
	inline string getPlayerName() { return *playerName; };
	inline void setNumberOfArmies(int number) { *numOfArmies = number; };
	inline void setPlayerName(string name) { *playerName = name; };
};

struct CountryNode {
	CountryInformation * countryInformation;
	vector<CountryNode*> neighbouringCountries;
	PlayerNode * playerInfo;
	bool * visited;
	CountryNode(CountryInformation * info);
	~CountryNode();
};


class Map {

private:
	vector<CountryNode*> *countriesGraph;

public:
	Map(vector<CountryInformation*> countries);
	int getNumberOfCountriesInMap();
	CountryNode* getFirstNode();
	virtual ~Map();
private:
	void validateMap();
	void validateContinents();
	void visitAllUnvisitedEdgesOfNodeInContinent(CountryNode * node, int continent);
	void visitAllUnvisitedEdgesOfNode(CountryNode * node);
	void attachEdgesToNodes();
	void resetVisitedNodes();
	CountryNode* getNodeInContinent(int continentId);
	CountryNode* getNodeFromGraphById(int countryId);
};


