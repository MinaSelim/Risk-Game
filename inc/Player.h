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
	Map * map;
	int * numberOfArmies;

public:
	Player();
	Player(string playerName, Map * map);
	Player(string playerName, vector<CountryNode*>* listOfCountries, Map * map);
	~Player();
	int getNumberOfArmyAtCountry(const string& countryName);
	void setNumberOfArmyAtCountry(CountryNode & country, int armies);
	void addCountryOwnerShip(CountryNode * node, int numOfArmies);

	void printListOfAllCountriesEnemies();
	void printListOfCountryAdjacentEnemies(CountryNode & country);
	//vector<CountryNode*> getAdjacentEnemies(CountryNode & country);
	bool isEnemy(string country);

	string chooseAttackingCountry();
	string chooseCountryToBeAttacked(string chosenAttackingCountry);
	//int inListOfEnemyCountries(CountryNode * attackingCountry, string chosenCountryToBeAttacked);
	bool isEnemyNeighbor(CountryNode & country, string enemyNeighbor);

	void rollingSequence(CountryNode * attackingCountry, CountryNode * defendingCountry);

	void transferDefeatedCountry(CountryNode * attackingCountry, CountryNode * defendingCountry);
	void attackSequence(CountryNode * attackingCountry, CountryNode * countryToBeAttacked);

	
	

	void reinforce();
	void attack();
	void fortify();

	string choosingCountry();
	string choosingNeighboringCountry(CountryNode * chosenCountry, bool & repeat);
	void armyManipulationFortify(CountryNode * chosenNeighborCountry, CountryNode * chosenCountry);
	bool inListOfCountries(string countryName);
	bool hasANeighbor(CountryNode & country);

	void printListOfCountries();
	void printListOfCountryNeighbors(CountryNode & country);
	void printListOfPlayersCountryNeighbors(CountryNode& country);

	int getArmiesAccordingToContinents();
	void placeArmiesOnCountries();

	inline DicesRoller* getDice()  { return dice; };
	inline HandOfCards* getHandOfCards() { return hand; };
	inline string getPlayerName() { return *playerName; };
	inline void setNumberOfArmies(int value) { *numberOfArmies = value; };
	inline int getNumberOfArmies() { return *numberOfArmies; };
	inline void setMap(Map * mapToSet) { map = mapToSet; };
};
