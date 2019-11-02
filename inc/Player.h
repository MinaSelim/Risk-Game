#pragma once

#include <vector>
#include "Map.h"
#include "Cards.h"
#include "Dice.h"
#include "Utility.h"

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
	Player(string playerName);
	Player(string playerName, vector<CountryNode*>* listOfCountries );
	~Player();
	int getNumberOfArmyAtCountry(const string& countryName);
	void setNumberOfArmyAtCountry(CountryNode & country, int armies);

	void printListOfAllCountriesEnemies();
	void printListOfCountryAdjacentEnemies(CountryNode & country);
	bool isEnemy(CountryNode & country);

	CountryNode * chooseAttackingCountry(CountryNode & attackingCountry);
	CountryNode * chooseCountryToAttack(CountryNode & chosenAttackingCountry, CountryNode & chosenCountryToAttack);
	

	void reinforce();
	void attack();
	void fortify();

	CountryNode * choosingCountry(CountryNode & chosenCountry);
	CountryNode * choosingNeighboringCountry(CountryNode * chosenNeighborCountry, CountryNode * chosenCountry, bool & repeat);
	void armyManipulationFortify(CountryNode * chosenNeighborCountry, CountryNode * chosenCountry);
	int inListOfCountries(CountryNode * chosenCoutnry, bool modifyChoosenCountry);
	bool hasANeighbor(CountryNode & country);

	void printListOfCountries();
	void printListOfCountryNeighbors(CountryNode & country);
	void printListOfPlayersCountryNeighbors(CountryNode& country);

	inline DicesRoller* getDice()  { return dice; };
	inline HandOfCards* getHandOfCards() { return hand; };
	inline string getPlayerName() { return *playerName; };
	inline void setNumberOfArmies(int value) { *numberOfArmies = value; };
	inline int getNumberOfArmies() { return *numberOfArmies; };
};
