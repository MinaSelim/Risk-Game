#pragma once

#include "Player.h"

#include <iostream>

using namespace std;
using Utility::userConfirmation;


Player::Player() :playerName(new string("Player")), countries(new vector<CountryNode*>()),
numberOfArmies(new int(0)), dice(new DicesRoller()), hand(new HandOfCards())
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
		cout << "The number of Armies at " << *chosenNeighborCountry->countryInformation->countryName << " is " << getNumberOfArmyAtCountry(*chosenNeighborCountry->countryInformation->countryName) << endl;
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
		string question = "Would you like to fortify your position (yes/no): ";
		if (userConfirmation(question).compare("yes") == 0)
		{
			vector<int> neightboursIds;
			//The repeat is to be used in case the player chooses a country and none of its neighbors belong to the player.
			//Thus they can't fortify and we give them the option or choosing again
			bool repeat = false;
			//CountryInformation * temp = new CountryInformation(1, 1, 1, 2, "city", neightboursIds);
			//CountryInformation * temp2 = new CountryInformation(1, 1, 1, 2, "city", neightboursIds);
			CountryNode * chosenCountry;
			CountryNode * chosenNeighborCountry;

			do {
				//Giving the the opportunity for the player to choose the country:
				chosenCountry = choosingCountry(*chosenCountry);

				//Then, they choose to which neighbor they want to transport their army: 
				chosenNeighborCountry = choosingNeighboringCountry(chosenNeighborCountry, chosenCountry, repeat);

				//This method will move the army from one country to its chosen neighbor: 
				if (!repeat ) {
					armyManipulationFortify(chosenNeighborCountry, chosenCountry);
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
	for (unsigned int i = 0; i < country.neighbouringCountries.size(); i++)
	{
		cout << *country.neighbouringCountries[i]->countryInformation->countryName << endl;
	}
}

//The purpose of this method is to print the list of neighbors that a player is rulling to one of thier countries
void Player::printListOfPlayersCountryNeighbors(CountryNode & country)
{
	for (unsigned int i = 0; i < country.neighbouringCountries.size(); i++)
	{
		if (inListOfCountries(country.neighbouringCountries[i], false) > -1)
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
		if (inListOfCountries(country.neighbouringCountries[i], false) > -1)
		{
			return true;
		}
	}
	return false;
}

//This method will handle the I/O with the user regarding the country the player wants to fortify.
CountryNode * Player::choosingCountry(CountryNode & chosenCountry)
{
	int value = -1;
	do {
		cout << "Which one of your countries you wish to choose: " << endl;
		printListOfCountries();
		cin >> *chosenCountry.countryInformation->countryName;
		value = inListOfCountries(&chosenCountry, true);
	} while (value == -1);

	return (*countries)[value];
}

//This method will handle the I/O with the user regarding with which country the player wants to complete the 
//fortify
CountryNode * Player::choosingNeighboringCountry(CountryNode * chosenNeighborCountry, CountryNode * chosenCountry, bool & repeat)
{
	int value = -1;
	do {
		if (hasANeighbor(*chosenCountry))
		{
			cout << "Which one of your neighbor countries to move your army to: " << endl;
			printListOfPlayersCountryNeighbors(*chosenCountry);
			cin >> *chosenNeighborCountry->countryInformation->countryName;
			value = inListOfCountries(chosenNeighborCountry, true);
			return (*countries)[value];
		}
		else
		{
			cout << "The chosen country doesn't have any neighbor countries which is ruled by the player" << endl;
			value = -1;
			repeat = true;
		}
	} while (value == -1 && !repeat);

	return chosenNeighborCountry;
}

//This method will verify is the country is one of the countries the player is rulling.
int Player::inListOfCountries(CountryNode * chosenCountry, bool modifyChoosenCountry)
{
	int indexAt = -1;
	string countryName = *chosenCountry->countryInformation->countryName;
	for (unsigned int i = 0; i < countries->size(); ++i)
	{
		if ((*countries)[i]->countryInformation->countryName->compare(countryName) == 0)
		{
			indexAt = i;
			if (modifyChoosenCountry)
			{
				chosenCountry = (*countries)[i];
			}
			break;
		}
	}
	return indexAt;
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
	for (unsigned i = 0; i < countries->size(); i++)
	{
		if ((*countries)[i]->countryInformation->countryName->compare(*country.countryInformation->countryName) == 0)
		{
			(*countries)[i]->playerInfo->setNumberOfArmies(armies);
			break;
		}
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


//Reinforce Part:
void Player::reinforce()
{
	cout << endl << "Executing the reinforce method" << endl;

	int countriesToBePlaced = countries->size() / 3;
	if (countriesToBePlaced < 3) {
		countriesToBePlaced = 3;
	}
	setNumberOfArmies(countriesToBePlaced + getNumberOfArmies());

	cout << "Player" << getPlayerName() << " has " << countries->size() << " countries, this will give him "
		<< countriesToBePlaced << " armies. The user now has " << getNumberOfArmies() << "armies." << endl;

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
	CountryInformation * temp = new CountryInformation(1, 1, 1, 2, "city", neightboursIds);
	CountryNode * chosenCountry = new CountryNode(temp);
	int value = -1;
	int chosenArmyNumber = 0;

	chosenCountry = choosingCountry(*chosenCountry);

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

	int numOfArmiesAtChosenCountry = getNumberOfArmyAtCountry(*chosenCountry->countryInformation->countryName);
	setNumberOfArmyAtCountry(*chosenCountry, numOfArmiesAtChosenCountry + chosenArmyNumber);
	setNumberOfArmies(getNumberOfArmies() - chosenArmyNumber);
}

// Check how many continents the user owns and return the cnotrol-value of that continent
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
	cout << "Executing the attack method" << endl;
}

