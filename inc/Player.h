#pragma once

#include <vector>
#include "Map.h"
#include "GameNodes.h"

class Player {
	
private:
	std:: string * playerName;
	std:: vector<CountryNode> * countries;
	//std:: vector<Cards> cards;
	
public:
	void reinforce();
	void attack();
	void fortify();
};