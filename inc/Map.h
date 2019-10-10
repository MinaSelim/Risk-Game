#pragma once
#include<vector>
#include "GameNodes.h"

class Map {

private:
	std::vector<CountryNode*> countriesGraph;

public:
	Map(std::vector<CountryInformation*> countries);
	virtual ~Map();
private:
	void validateMap();
	void visitAllUnvisitedEdgesOfNode(CountryNode * node);
	void attachEdgesToNodes();
	void resetVisitedNodes();
	CountryNode* getNodeFromGraphById(int countryId);

};