#pragma once
#include<vector>


struct ContinentInformation {
	std::string * continentName;
	int * continentId;
	ContinentInformation(std::string name, int id);
	~ContinentInformation();
};

struct CountryInformation {
	int * countryId;
	int *xCoordinate;
	int *yCoordinate;
	int *continentId;
	//std::string continentName;
	std::string *countryName;
	std::vector<int> neighbouringCountriesIds;
	CountryInformation(int id, int x, int y, int contId, std::string countName, std::vector<int> neigboursIds);
	virtual ~CountryInformation();
};

struct CountryNode {
	CountryInformation * countryInformation;
	std::vector<CountryNode*> neighbouringCountries;
	bool * visited;
	CountryNode(CountryInformation * info);
	~CountryNode();
};


class Map {

private:
	std::vector<CountryNode*> *countriesGraph;

public:
	Map(std::vector<CountryInformation*> countries);
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