#pragma once

#include <vector>
#include "Map.h"
#include "GameNodes.h"
#include "Cards.h"
#include "Dice.h"

using namespace std;

class Player {
	
private:
	string * playerName;
	vector<CountryNode*> * countries;
	HandOfCards * hand;
	DicesRoller * dice;
	int * numberOfArmies;

public:
	Player();
	Player(string playerName, vector<CountryNode*> countries);
	~Player();
	void reinforce();
	void attack();
	void fortify();
	DicesRoller getDice();
	HandOfCards* getCard();
};