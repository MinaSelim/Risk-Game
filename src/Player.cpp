#pragma once

#include "Player.h"
#include <iostream>

using namespace std;
using Utility::userConfirmation;


Player::Player() :playerName(new string("Player")), countries (new vector<CountryNode*>()),
	numberOfArmies(new int(0)),dice(new DicesRoller()), hand(new HandOfCards())
{
}

Player::Player(string playerName, Map * map) : playerName(new string(playerName)), countries(new vector<CountryNode*>()),
numberOfArmies(new int(0)), dice(new DicesRoller()), hand(new HandOfCards()), map(map)
{
}

Player::Player(string playerName, vector<CountryNode*> * listOfCountries, Map * map) : playerName(new string(playerName)), countries(listOfCountries),
numberOfArmies(new int(0)), dice(new DicesRoller()), hand(new HandOfCards()), map(map)
{
}

Player::~Player()
{
	//We can't delete the countryNode otherwise 
	//Mina :3 how will we delete the countries vector ?
	delete playerName;
	playerName = NULL;
	delete numberOfArmies;
	numberOfArmies = NULL;
	delete dice;
	dice = NULL;
	delete hand;
	hand = NULL;
}

//This method will ask the user the number of the armies they want to move from one country to another
//and it will move the army from one country to one of its chosen neighbor:
void Player::armyManipulationFortify(CountryNode * chosenNeighborCountry, CountryNode * chosenCountry)
{
	int numOfarmiesAtChosenCountry = getNumberOfArmyAtCountry(*chosenCountry->countryInformation->countryName);
	int numOfArmiesAtNeighboringCountry = getNumberOfArmyAtCountry(*chosenNeighborCountry->countryInformation->countryName);
	int numOfMovingArmies = 0;

	if (numOfarmiesAtChosenCountry > 1) 
	{
		cout << "In the chosen Country, " << *chosenCountry->countryInformation->countryName << ", you have: " << numOfarmiesAtChosenCountry << endl;
		do {
			cout << "How many armies you want to move to your neighboring country? Your answer should be between 1-" << numOfarmiesAtChosenCountry - 1 << endl;
			cin >> numOfMovingArmies;
			
			//To Makse sure the player is inputing an integer:
			while (!cin)
			{
				cout << "That was not an integer! Please enter an integer between 1-" << numOfarmiesAtChosenCountry - 1 << endl;
				cin.clear();
				cin.ignore();
				cin >> numOfMovingArmies;
			}
		} while (numOfMovingArmies < 1 || numOfMovingArmies >= numOfarmiesAtChosenCountry);

		setNumberOfArmyAtCountry(*chosenCountry, numOfarmiesAtChosenCountry - numOfMovingArmies);
		setNumberOfArmyAtCountry(*chosenNeighborCountry, numOfArmiesAtNeighboringCountry + numOfMovingArmies);

		cout << "The number of Armies at " << *chosenCountry->countryInformation->countryName << " is " << getNumberOfArmyAtCountry(*chosenCountry->countryInformation->countryName) << endl;
		cout << "The number of Armies at " << *chosenNeighborCountry->countryInformation->countryName << " is " << getNumberOfArmyAtCountry(*chosenNeighborCountry->countryInformation->countryName) <<"\n" << endl;
	}
	else
	{
		cout << "You have only 1 army at " << *chosenCountry->countryInformation->countryName << ". Thus, you can't proceed";
	}
	
}



void Player::fortify()
{
	//if the player doesn't have any countries.
	if (countries->size() != 0) {
		cout << "Executing the Fortify Method:\n" << endl;
		string question = "Would you like to fortify your position (yes/no): ";
		if (userConfirmation(question).compare("yes") == 0) 
		{
			//The repeat is to be used in case the player chooses a country and none of its neighbors belong to the player.
			//Thus they can't fortify and we give them the option or choosing again
			bool repeat = false;
			bool proceed = false;
			string chosenCountry;
			string chosenNeighborCountry;
			do {
				//Giving the the opportunity for the player to choose the country:
				chosenCountry = choosingCountry();
				repeat = false;
				if (map->getNodeFromGraphByName(chosenCountry)->playerInfo->getNumberOfArmies() <= 1) {
					cout << "\n The choosen Country Doesn't have enough army to move. Please Try with a different country" << endl;
					repeat = true;
				}
				else {
					//Then, they choose to which neighbor they want to transport their army: 
					chosenNeighborCountry = choosingNeighboringCountry(map->getNodeFromGraphByName(chosenCountry), repeat);
					if (!repeat) {
						proceed = true;
					}
				}

				//This method will move the army from one country to its chosen neighbor: 
				if (proceed) {
					armyManipulationFortify(map->getNodeFromGraphByName(chosenNeighborCountry), map->getNodeFromGraphByName(chosenCountry));
					repeat = false;
				}
			} while (repeat);
		}
	}
	else {
		cout << "You don't have any country to fortify" << endl;
	}
}


//The purpose of the function is to print the list of countries that a player is ruling
//And the number of arrmies they have on each country
void Player::printListOfCountries()
{
	for (unsigned int i = 0; i < countries->size(); i++)
	{
		cout << *(*countries)[i]->countryInformation->countryName << " has " << (*countries)[i]->playerInfo->getNumberOfArmies() << " armies." << endl;
	}
}


//The purpose of this method is basically to print the list of neighbor countries for a country
void Player::printListOfCountryNeighbors(CountryNode & country)
{
	for(unsigned int i = 0; i < country.neighbouringCountries.size(); i++)
	{
		cout << *country.neighbouringCountries[i]->countryInformation->countryName << endl;
	}
}

//The purpose of this method is to print the list of neighbors that a player is rulling to one of thier countries
void Player::printListOfPlayersCountryNeighbors(CountryNode & country)
{
	for (unsigned int i = 0; i < country.neighbouringCountries.size(); i++) 
	{
		if (inListOfCountries(country.neighbouringCountries[i]->countryInformation->getCountryName()))
		{
			cout << *country.neighbouringCountries[i]->countryInformation->countryName << endl;
		}		
	}
}

//To check if a country of a player has at a least one neighbor country which is ruled by the same player:
bool Player::hasANeighbor(CountryNode & country)
{
	for (unsigned int i = 0; i < country.neighbouringCountries.size(); i++) 
	{
		if (inListOfCountries(country.neighbouringCountries[i]->countryInformation->getCountryName()))
		{
			return true;
		}
	}
	return false;
}

//This method will handle the I/O with the user regarding the country the player wants to fortify.
string Player::choosingCountry()
{
	string inputCountryName = "N/A";
	bool value = false;
	do {
		cout << "Which one of your countries you wish to choose: " << endl;
		printListOfCountries();
		cin >> inputCountryName;
		value = inListOfCountries(inputCountryName);

		if (!value) {
			cout << "The inserted country Name doesn't exist in the list of countries. Please Try again: \n\n" << endl;
		}
	} while (!value);

	return inputCountryName;
}

//This method will handle the I/O with the user regarding with which country the player wants to complete the 
//fortify
string Player::choosingNeighboringCountry(CountryNode * chosenCountry, bool & repeat)
{
	string inputUser="N/A";
	bool found = false;
	do {
		if (hasANeighbor(*chosenCountry)) 
		{
			cout << "Which one of your neighbor countries to move your army to: " << endl;
			printListOfPlayersCountryNeighbors(*chosenCountry);
			cin >> inputUser;
			found = inListOfCountries(inputUser);
			if (!found) {
				cout << "The inserted Country Name doesn't exist please try again " << endl;
				string question = "Would you like to go back to the list of your countries? (yes/no):";
				if (userConfirmation(question).compare("yes")==0) {
					found = true;
					repeat = true;
				}
			}
		}
		else
		{
			cout << "The chosen country doesn't have any neighbor countries which is ruled by the player \n\n" << endl;
			found = true;
			repeat = true;
		}
	} while (!found);

	return inputUser;
}

//This method will verify is the country is one of the countries the player is rulling.
bool Player::inListOfCountries(string countryName)
{
	for (unsigned int i = 0; i < countries->size(); ++i)
	{
		if ((*countries)[i]->countryInformation->countryName->compare(countryName) == 0)
		{
			return true;
		}
	}
	return false;
}

//This will get the number of army a player has at countryName
int Player::getNumberOfArmyAtCountry(const string & countryName)
{
	int armies = 0;
	for (unsigned i = 0; i < countries->size(); ++i)
	{
		if ((*countries)[i]->countryInformation->countryName->compare(countryName) == 0)
		{
			armies = (*countries)[i]->playerInfo->getNumberOfArmies();
			break;
		}
	}
	return armies;
}

//the purpose of this method is to change the number of armies that  a player has at country with
// armies parameter number
void Player::setNumberOfArmyAtCountry(CountryNode & country, int armies)
{
	for (unsigned i =0; i <countries->size(); i++ )
	{
		if ((*countries)[i]->countryInformation->countryName->compare(*country.countryInformation->countryName) == 0)
		{
			(*countries)[i]->playerInfo->setNumberOfArmies(armies);
			break;
		}
	}
}
//provides a view of a Player's countries and which countries they can attack from those countries and number of armies
void Player::printListOfAllCountriesEnemies() 
{
	for (unsigned int i = 0; i < countries->size(); i++)
	{
		cout << *(*countries)[i]->countryInformation->countryName << " has " << (*countries)[i]->playerInfo->getNumberOfArmies() << " armies." << endl;
		cout << *(*countries)[i]->countryInformation->countryName << " can attack the following Countries: " << endl;
		
		printListOfCountryAdjacentEnemies(*(*countries)[i]);
	}
	cout << "\n" << endl;
}

//Prints the countries that are neighbours and enemies with number of armies (country doesnt belong to player)
void Player::printListOfCountryAdjacentEnemies(CountryNode & country)
{
	int countEnemies = 0;

	for (unsigned int i = 0; i < country.neighbouringCountries.size(); i++)
	{
		if (isEnemy(country.neighbouringCountries[i]->countryInformation->getCountryName()))
		{
			cout << *country.neighbouringCountries[i]->countryInformation->countryName << " (" << country.neighbouringCountries[i]->playerInfo->getNumberOfArmies() << ")" << endl;
			countEnemies++;
		}
		
	}
	cout << "\n" << endl;

	if (countEnemies == 0) 
	{
		cout << "There are no enemies to attack from this country." << endl;
	}
}


void Player::addCountryOwnerShip(CountryNode * node, int numOfArmies)
{
	if (node->playerInfo)
	{
		//add code to remove country
	}

	node->playerInfo->setNumberOfArmies(numOfArmies);
	node->playerInfo->assignPlayer(this);

	countries->push_back(node);
}

//returns true if the country is an enemy country, false if not
bool Player::isEnemy(string country)
{
	bool isEnemy = true;
	for (unsigned int i = 0; i < countries->size(); i++)
	{
		if ((*countries)[i]->countryInformation->countryName->compare(country) == 0)
		{
			//if the country passed is in the player country list then it is not an enemy
			isEnemy = false;
		}
	}
	return isEnemy;
}

//chooses the attacking country (modified one of Hamsbroom's methods cause it's basically the same logic)
string Player::chooseAttackingCountry()
{
	string chosenCountry ="N/A";
	bool value = false;
	do {
		cout << "Which one of your countries will Attack? " << endl;
		printListOfCountries();
		cin >> chosenCountry;
		value = inListOfCountries(chosenCountry);
		//if the country has less than 2 armies reset value to -1, since you need minimum 2 armies to attack
		if (!value) {
			cout << "The inserted country Name doesn't exist in the list of countries. Please Try again: \n\n" << endl;
		}
		if (value) {
			if (getNumberOfArmyAtCountry(chosenCountry) < 2)
			{
				cout << "You need a minimum of 2 armies to attack, please select a different country" << endl;
				value = true;
			}
		}
		
	} while (!value);

	return chosenCountry;
}
//this method will ask the user to pick a country to attack
string Player::chooseCountryToBeAttacked(string chosenAttackingCountry)
{
	string chosenCountryToBeAttacked;
	bool value = false;
	do {
		cout << "Which country will be attacked?" << endl;
		printListOfCountryAdjacentEnemies(*map->getNodeFromGraphByName(chosenAttackingCountry));
		cin >> chosenCountryToBeAttacked;
		value = isEnemy(chosenCountryToBeAttacked);
		if (value) {
			value = isEnemyNeighbor(*map->getNodeFromGraphByName(chosenAttackingCountry), chosenCountryToBeAttacked);
		}
		
		//value = inListOfEnemyCountries(map->getNodeFromGraphByName(chosenAttackingCountry), chosenCountryToBeAttacked);
	} while (!value);


		return chosenCountryToBeAttacked;

}

//this will verify if enemyNeighbor is actually an enemy of a country 
bool Player::isEnemyNeighbor(CountryNode & country, string enemyNeighbor)
{
	for (unsigned int i = 0; i < country.neighbouringCountries.size(); i++)
	{
		if (country.neighbouringCountries[i]->countryInformation->getCountryName().compare(enemyNeighbor)==0)
		{
			return true;
		}
	}
	return false;
}


void Player::reinforce()
{

	cout << endl << "Executing the reinforce method" << endl;

	int countriesToBePlaced = countries->size() / 3;
	if (countriesToBePlaced < 3) {
		countriesToBePlaced = 3;
	}
	setNumberOfArmies(countriesToBePlaced + getNumberOfArmies());

	cout << "Player" << getPlayerName() << " has " << countries->size() << " countries, this will give him "
		<< countriesToBePlaced << " armies. The user now has " << getNumberOfArmies() << " armies." << endl;

	int armiesContinents = getArmiesAccordingToContinents();
	setNumberOfArmies(armiesContinents + getNumberOfArmies());
	cout << "Player" << getPlayerName() << " will get " << armiesContinents << " from his continents" << endl;

	int cardsExchangeArmies = hand->exchange();
	setNumberOfArmies(cardsExchangeArmies + getNumberOfArmies());

	cout << "Player" << getPlayerName() << " acquired " << cardsExchangeArmies << " armies from exchanging cards " << ". User now has "
		<< getNumberOfArmies() << endl;

	do {
		placeArmiesOnCountries();
	} while (getNumberOfArmies() > 0);

}


void Player::placeArmiesOnCountries() {
	vector<int> neightboursIds;
	//int value = -1;
	int chosenArmyNumber = 0;
	string chosenCountry = "N/A";
	chosenCountry = choosingCountry();

	cout << "Choose how many armies you wish to place (Between 1 - " << getNumberOfArmies() << ")" << endl;
	cin >> chosenArmyNumber;

	while (chosenArmyNumber < 1 || getNumberOfArmies() < chosenArmyNumber) {
		cout << "You don't have enough armies please choose again: ";
		cin >> chosenArmyNumber;

		cout << chosenArmyNumber << "  " << " Armies available" << getNumberOfArmies() << endl;
		while (!cin)
		{
			cout << "That was not an integer! Please enter an integer between 1-" << getNumberOfArmies() - 1 << endl;
			cin.clear();
			cin.ignore();
			cin >> chosenArmyNumber;
		}
	}

	int numOfArmiesAtChosenCountry = getNumberOfArmyAtCountry(map->getNodeFromGraphByName(chosenCountry)->countryInformation->getCountryName());
	setNumberOfArmyAtCountry(*map->getNodeFromGraphByName(chosenCountry), numOfArmiesAtChosenCountry + chosenArmyNumber);
	setNumberOfArmies(getNumberOfArmies() - chosenArmyNumber);
}

//this method handles the attacking sequence, player can either anihilate, roll, retreat
//when an army takes over another country, transfer troops to conquered country
void Player::rollingSequence(CountryNode * attackingCountry, CountryNode * defendingCountry)
{
	Player * defender = defendingCountry->playerInfo->getPlayer();
	DicesPrompt * dicesPrompt = new DicesPrompt();

	//get armies for attacker and defender
	int attackerArmies = attackingCountry->playerInfo->getNumberOfArmies();
	int defenderArmies = defendingCountry->playerInfo->getNumberOfArmies();
	cout << "Attacker has " << attackerArmies << " armies." << endl;
	cout << "Defender has " << defenderArmies << " armies." << endl;

	//initializing rolls to compare later
	vector <int> attackerRoll;
	vector <int> defenderRoll;
	int attackerNumDice = 0;
	int defenderNumDice = 0;

	cout << "Attacker choose the number of dice you will roll: " << endl;
	//get number of dice to roll for attacker, max 3, or armies - 1
	attackerNumDice = dicesPrompt->getRolledNumberOfDice(true, attackerArmies);
	
	cout << "Defender choose the number of dice you will roll: " << endl;
	//get number of dice to roll for defender, max 2, or armies - 1
	defenderNumDice = dicesPrompt->getRolledNumberOfDice(false, attackerArmies);
	
	//attacker rolls (maximum of 3 dice)
	cout << "Attacker rolls the following:" << endl;
	attackerRoll = dice->roll(attackerNumDice);

	//defender rolls (maximum of 2 dice)
	cout << "Defender rolls the following:" << endl;
	defenderRoll = defender->dice->roll(defenderNumDice);
	
	//compare dice
	//since they are sorted we compare the pairs
	//ex: if attack rolls 3 and defense rolls 2 we dont check the entire array of attack, just the first 2
	for (int i = 0; i < defenderNumDice; i++)
	{
		if (attackerRoll[i] > defenderRoll[i])
		{
			defenderArmies--;
		}
		else if (attackerRoll[i] <= defenderRoll[i])
		{
			attackerArmies--;
		}
	}

	cout << "attacker armies: " << attackerArmies << endl;
	cout << "defender armies: " << defenderArmies << endl;

	attackingCountry->playerInfo->setNumberOfArmies(attackerArmies);
	defendingCountry->playerInfo->setNumberOfArmies(defenderArmies);

	if (defenderArmies == 0)
	{
		transferDefeatedCountry(attackingCountry, defendingCountry);
	}

	delete dicesPrompt;
}

//this method handles when a country is defeated and has to transfer ownership to a enemy player
void Player::transferDefeatedCountry(CountryNode * attackingCountry, CountryNode * defendingCountry)
{
	int attackerArmies = attackingCountry->playerInfo->getNumberOfArmies();
	string defendingCountryName = *defendingCountry->countryInformation->countryName;
	int numArmiesToTransfer = 0;
	do
	{
		cout << "How many armies will you transfer to " << defendingCountryName << " select between 1 - " << (attackerArmies - 1) << endl;
		cin >> numArmiesToTransfer;
	} while (numArmiesToTransfer < 0 || numArmiesToTransfer > attackerArmies - 1);

	//update attacking country after army transfer
	attackerArmies = attackerArmies - numArmiesToTransfer;
	attackingCountry->playerInfo->setNumberOfArmies(attackerArmies);
	//add new country to player country list
	addCountryOwnerShip(defendingCountry, numArmiesToTransfer);
	
}

void Player::attackSequence(CountryNode * attackingCountry, CountryNode * defendingCountry)
{	
	//ask user if they want to:
	//anihilate: keep rolling until they beat their oponent or have 1 army left
	//roll: roll once
	//retreat: stop attacking this country, go back and prompt to attack a different country

	cout << *attackingCountry->countryInformation->countryName << " is going to attack " << *defendingCountry->countryInformation->countryName << endl;
	
	string question = "will you roll or retreat?";
	string userInput = "";
	
	do 
	{
		cout << question << endl;
		cin >> userInput;

	} while (!userInput.compare("roll") == 0 && !userInput.compare("retreat"));
		
	if (userInput.compare("roll") == 0)
	{
		rollingSequence(attackingCountry, defendingCountry);
	}
	if (userInput.compare("retreat") == 0)
	{
		cout << "You have retreated." << endl;
		exit(0);
	}
}

//The method will return the number of armies a player deserves according to the number of contitents they rule.
int Player::getArmiesAccordingToContinents()
{
	int armies = 0;
	std::vector<int> continentsIdOwned;
	std::vector<int> continentIds = map->getContinentIds();

	// Checking how many continents user owns
	for (unsigned int i = 0; i < continentIds.size(); i++) {
		if (map->checkUserContinents(continentIds[i], *playerName)) {
			continentsIdOwned.push_back(continentIds[i]);
		}
	}

	cout << endl << "Player has " << continentsIdOwned.size() << " continents" << endl;

	for (unsigned i = 0; i < continentsIdOwned.size(); i++) {
		armies += map->getContinentControlValue(continentsIdOwned[i] - 1);
	}
	return armies;
}


//Attack Part:
void Player::attack()
{
	if (countries->size() != 0) {
		bool repeat = true;
		do 
		{
			string question = "Would you like to attack? (yes/no): ";
			if (userConfirmation(question).compare("yes") == 0)
			{
				//temp is just so it follows constructor format
				string attackingCountry;
				string defendingCountry;
				printListOfAllCountriesEnemies();
				attackingCountry = chooseAttackingCountry();
				defendingCountry = chooseCountryToBeAttacked(attackingCountry);
				attackSequence(map->getNodeFromGraphByName(attackingCountry),map->getNodeFromGraphByName(defendingCountry));
			}
			else
			{
				repeat = false;
			}

		} while (repeat);
		
	}
}

