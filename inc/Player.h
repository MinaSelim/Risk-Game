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
	void addCountryOwnerShip(CountryNode * node, int numOfArmies);

	void printListOfAllCountriesEnemies();
	void printListOfCountryAdjacentEnemies(CountryNode & country);
	vector<CountryNode*> getAdjacentEnemies(CountryNode & country);
	bool isEnemy(CountryNode & country);

	CountryNode * chooseAttackingCountry(CountryNode & attackingCountry);
	CountryNode * chooseCountryToBeAttacked(CountryNode & chosenAttackingCountry, CountryNode & chosenCountryToAttack);
	int inListOfEnemyCountries(CountryNode * attackingCountry, CountryNode * chosenCountryToBeAttacked, bool modifyChosenCountryToBeAttacked);

	void rollingSequence(CountryNode * attackingCountry, CountryNode * defendingCountry);

	void transferDefeatedCountry(CountryNode * attackingCountry, CountryNode * defendingCountry);
	void attackSequence(CountryNode * attackingCountry, CountryNode * countryToBeAttacked);

	
	

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
