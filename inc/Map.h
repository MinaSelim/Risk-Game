#pragma once
#include<vector>
#include "GameNodes.h"

class Map {

private:
	std::vector<CountryNode> countriesGraph;

public:
	Map(std::vector<CountryInformation> countries);

private:
	void validateMap();
	void visitAllUnvisitedEdgesOfNode(CountryNode * node);
	void attachEdgesToNodes();
	void resetVisitedNodes();
	CountryNode* getNodeFromGraphByString(std::string countryName);

};