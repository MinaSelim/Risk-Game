#pragma once

#include <vector>
#include "Map.h"
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
	void printListOfCountries();
	void setNumberOfArmies(int value);
	int getNumberOfArmies();
	DicesRoller* getDice();
	HandOfCards* getHandOfCards();
	string getPlayerName();
};
