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

	int getUserContinents();

	inline DicesRoller* getDice()  { return dice; };
	inline HandOfCards* getHandOfCards() { return hand; };
	inline string getPlayerName() { return *playerName; };
	inline void setNumberOfArmies(int value) { *numberOfArmies = value; };
	inline int getNumberOfArmies() { return *numberOfArmies; };
	inline void setMap(Map & map) { map = map; };
};
