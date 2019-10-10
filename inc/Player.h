#pragma once

#include <vector>
#include "Map.h"

using namespace std;

class Player {
	
private:
	string * playerName;
	vector<CountryNode> * countries;
	//std:: vector<Cards> cards;
	
public:
	Player();
	Player(string playerName, vector<CountryNode> countries);
	~Player();
	void reinforce();
	void attack();
	void fortify();
};