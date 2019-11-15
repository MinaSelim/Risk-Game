#pragma once

#include <vector>
#include "Map.h"
#include "Cards.h"
#include "Dice.h"
#include "Utility.h"
#include "PlayerStrategies.h"

using namespace std;

enum BehaviourEnum { Human = 0, Aggresive, Benevolent };

class Player {
	
private:
	string * playerName;
	vector<CountryNode*> * countries;
	HandOfCards * hand;
	DicesRoller * dice;
	Map * map;
	int * numberOfArmies;
	BehaviourEnum * currentBehaviourEnum;
	Behaviour * playerBehaviour;


public:
	Player();
	Player(string playerName, Map * map, BehaviourEnum behaviour);
	Player(string playerName, vector<CountryNode*>* listOfCountries, Map * map, BehaviourEnum behaviour);
	~Player();
	friend HumanBehaviour;
	friend BenevolentAIBehaviour;
	friend AggresiveAIBehaviour;
	
	void addCountryOwnerShip(CountryNode * node, int numOfArmies);
	int  getArmiesAccordingToContinents();

	void reinforce();
	void attack();
	void fortify();

	void printListOfCountries();
	void printListOfCountryNeighbors(CountryNode & country);
	void printListOfPlayersCountryNeighbors(CountryNode& country);
	void printListOfAllCountriesEnemies();
	void printListOfCountryAdjacentEnemies(CountryNode & country);
	bool countryOwnedByPlayer(string countryName);

	void placeArmiesOnCountries();

	DicesRoller* getDice()  { return dice; };
	HandOfCards* getHandOfCards() { return hand; };
	string getPlayerName() { return *playerName; };
	void setNumberOfArmies(int value) { *numberOfArmies = value; };
	int getNumberOfArmies() { return *numberOfArmies; };
	void setMap(Map * mapToSet) { map = mapToSet; };

private:
	void armyManipulationFortify(CountryNode * chosenNeighborCountry, CountryNode * chosenCountry, int numOfMovingArmies);
	void attackSequence(CountryNode * attackingCountry, CountryNode * countryToBeAttacked);
	string chooseAttackingCountry();
	string chooseCountryToBeAttacked(string chosenAttackingCountry);
	string choosingCountry();
	string choosingNeighboringCountry(CountryNode * chosenCountry, bool & repeat);
	int getNumberOfArmyAtCountry(const string& countryName);
	bool hasANeighbor(CountryNode & country);
	
	bool isEnemy(string country);
	bool isEnemyNeighbor(CountryNode & country, string enemyNeighbor);
	void rollingSequence(CountryNode * attackingCountry, CountryNode * defendingCountry);
	void setNumberOfArmyAtCountry(CountryNode & country, int armies);
	void transferDefeatedCountry(CountryNode * attackingCountry, CountryNode * defendingCountry);

};
