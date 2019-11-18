#pragma once

#include <vector>
#include "Map.h"
#include "Cards.h"
#include "Dice.h"
#include "Utility.h"
#include "GameObservers.h"

using namespace std;

class Player {
	
private:
	string * playerName;
	vector<CountryNode*> * countries;
	HandOfCards * hand;
	DicesRoller * dice;
	Map * map;
	int * numberOfArmies;

	void armyManipulationFortify(CountryNode * chosenNeighborCountry, CountryNode * chosenCountry);
	void attackSequence(CountryNode * attackingCountry, CountryNode * countryToBeAttacked);
	string chooseAttackingCountry();
	string chooseCountryToBeAttacked(string chosenAttackingCountry);
	string choosingCountry();
	string choosingNeighboringCountry(CountryNode * chosenCountry, bool & repeat);
	int getNumberOfArmyAtCountry(const string& countryName);
	bool hasANeighbor(CountryNode & country);
	bool inListOfCountries(string countryName);
	bool isEnemy(string country);
	bool isEnemyNeighbor(CountryNode & country, string enemyNeighbor);
	void rollingSequence(CountryNode * attackingCountry, CountryNode * defendingCountry);
	void setNumberOfArmyAtCountry(CountryNode & country, int armies);
	void transferDefeatedCountry(CountryNode * attackingCountry, CountryNode * defendingCountry);

public:
	Player();
	Player(string playerName, Map * map);
	Player(string playerName, vector<CountryNode*>* listOfCountries, Map * map);
	~Player();
	
	void addCountryOwnerShip(CountryNode * node, int numOfArmies);
	int  getArmiesAccordingToContinents(); 

	void reinforce();
	void attack();
	void fortify();

	void printListOfCountries();
	void printListOfCountriesWithMoreThanOneArmy();
	void printListOfCountryNeighbors(CountryNode & country);
	void printListOfPlayersCountryNeighbors(CountryNode& country);
	void printListOfAllCountriesEnemies();
	void printListOfCountryAdjacentEnemies(CountryNode & country);

	void placeArmiesOnCountries();

	DicesRoller* getDice()  { return dice; };
	HandOfCards* getHandOfCards() { return hand; };
	string getPlayerName() { return *playerName; };
	void setNumberOfArmies(int value) { *numberOfArmies = value; };
	int getNumberOfArmies() { return *numberOfArmies; };
	vector<int> getContinentsOwnedByPlayer();
	void setMap(Map * mapToSet) { map = mapToSet; };

	int getNumberPlayerCountries();
	int getNumberTotalCountries();
};
