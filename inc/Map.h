#pragma once
#include <vector>
#include <string>

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

struct CountryNode {
	CountryInformation * countryInformation;
	vector<CountryNode*> neighbouringCountries;
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