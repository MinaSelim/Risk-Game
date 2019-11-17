#include "PlayerStrategies.h"
#include "Player.h"
#include "Utility.h"
#include "Dice.h"
#include "ErrorCodes.h"
#include <iostream>

using namespace::std;

//The purpose of the method is to interact with the user during the reinforce to ask them 
//where they want to place their armies
void HumanBehaviour::placeArmiesDuringReinforce()
{
	vector<int> neightboursIds;
	int chosenArmyNumber = 0;
	string chosenCountry = "N/A";

	//Asking the user to choose a country 
	chosenCountry = player->choosingCountry();

	if (player->getNumberOfArmies() == 1)
	{
		chosenArmyNumber = 1;
	}
	else
	{
		cout << "Choose how many armies you wish to place (Between 1 - " << player->getNumberOfArmies() << ")" << endl;
		cin >> chosenArmyNumber;
	}

	//The player has to leave at least one army at the country
	while (chosenArmyNumber < 1 || player->getNumberOfArmies() < chosenArmyNumber) {
		cout << "You don't have enough armies please choose again: ";
		cin >> chosenArmyNumber;

		cout << chosenArmyNumber << "  " << " Armies available" << player->getNumberOfArmies() << endl;
		while (!cin)
		{
			cout << "That was not an integer! Please enter an integer between 1-" << player->getNumberOfArmies() - 1 << endl;
			cin.clear();
			cin.ignore();
			cin >> chosenArmyNumber;
		}
	}

	int numOfArmiesAtChosenCountry = player->getNumberOfArmyAtCountry(player->map->getNodeFromGraphByName(chosenCountry)->countryInformation->getCountryName());
	player->setNumberOfArmyAtCountry(*player->map->getNodeFromGraphByName(chosenCountry), numOfArmiesAtChosenCountry + chosenArmyNumber);
	cout << "The number of armies is: " << numOfArmiesAtChosenCountry + chosenArmyNumber << " armies at " << chosenCountry << endl;
	player->setNumberOfArmies(player->getNumberOfArmies() - chosenArmyNumber);

}


//If the player was human, they will asked which country they want to attack
void HumanBehaviour::attackEnemies()
{
	if (player->countries->size() != 0) {
		bool repeat = true;
		do
		{
			string question = "Would you like to attack? (yes/no): ";
			if (Utility::userConfirmation(question).compare("yes") == 0)
			{
				//temp is just so it follows constructor format
				string attackingCountry;
				string defendingCountry;
				player->printListOfAllCountriesEnemies();

				//choosing the country from where the player will attack
				attackingCountry = player->chooseAttackingCountry();

				//The country which will defend itself from the attack
				defendingCountry = player->chooseCountryToBeAttacked(attackingCountry);

				//in case if the player change their mind and they don't want to attack anymore.
				if (defendingCountry.compare("cancel") != 0)
				{
					player->attackSequence(player->map->getNodeFromGraphByName(attackingCountry), player->map->getNodeFromGraphByName(defendingCountry));
				}
			}
			else
			{
				repeat = false;
			}

		} while (repeat);
	}
	else
	{
		cout << "You don't have any country to attack another one" << endl;
	}
}

//In case if the player was human, they wil be asked to choose the country they want to fortify and move 
//the armies to which country
void HumanBehaviour::fortify()
{
	//if the player doesn't have any countries.
	if (player->countries->size() != 0) {
		cout << "Executing the Fortify Method:\n" << endl;
		string question = "Would you like to fortify your position (yes/no): ";
		if (Utility::userConfirmation(question).compare("yes") == 0)
		{
			//The repeat is to be used in case the player chooses a country and none of its neighbors belong to the player.
			//Thus they can't fortify and we give them the option or choosing again
			bool repeat = false;
			bool proceed = false;
			string chosenCountryString;
			string chosenNeighborCountryString;
			do {
				//Giving the the opportunity for the player to choose the country:
				chosenCountryString = player->choosingCountry();
				repeat = false;
				if (player->map->getNodeFromGraphByName(chosenCountryString)->playerInfo->getNumberOfArmies() <= 1) {
					cout << "\n The choosen Country Doesn't have enough army to move. Please Try with a different country" << endl;
					repeat = true;
				}
				else {
					//Then, they choose to which neighbor they want to transport their army: 
					chosenNeighborCountryString = player->choosingNeighboringCountry(player->map->getNodeFromGraphByName(chosenCountryString), repeat);
					if (!repeat) {
						proceed = true;
					}
				}

				//This method will move the army from one country to its chosen neighbor: 
				if (proceed) {
					auto chosenCountry = player->map->getNodeFromGraphByName(chosenCountryString);
					auto chosenNeighborCountry = player->map->getNodeFromGraphByName(chosenNeighborCountryString);
					int numOfarmiesAtChosenCountry = player->getNumberOfArmyAtCountry(*chosenCountry->countryInformation->countryName);
					//int numOfArmiesAtNeighboringCountry = player->getNumberOfArmyAtCountry(*chosenNeighborCountry->countryInformation->countryName);
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



						player->armyManipulationFortify(chosenNeighborCountry, chosenCountry, numOfMovingArmies);
						repeat = false;
					}
					else
					{
						cout << "You have only 1 army at " << *chosenCountry->countryInformation->countryName << ". Thus, you can't proceed";
					}
				}
			} while (repeat);
		}
	}
	else {
		cout << "You don't have any country to fortify" << endl;
	}
}

//Mina
int HumanBehaviour::getAttackRoll(int attackArmiesOnNode)
{
	DicesPrompt dicesPrompt;
	int attackerNumDice = dicesPrompt.getRolledNumberOfDice(true, attackArmiesOnNode);

	return attackerNumDice;
}

//Mina
int HumanBehaviour::getDefenseRoll(int defenseArmiesOnNode)
{
	DicesPrompt dicesPrompt;
	int attackerNumDice = dicesPrompt.getRolledNumberOfDice(false, defenseArmiesOnNode);

	return attackerNumDice;
}

//The player can choose the number of armies they want to move to the new coquered country 
int HumanBehaviour::getNumberOfTroopsToTransfer(int attackerArmies)
{
	int numArmiesToTransfer = 0;
	do
	{
		cout << "How many armies will you transfer to the newly conquered country select between 1 - " << (attackerArmies - 1) << endl;
		cin >> numArmiesToTransfer;
	} while (numArmiesToTransfer < 0 || numArmiesToTransfer > attackerArmies - 1);

	return numArmiesToTransfer;
}

HumanBehaviour::HumanBehaviour(Player * player)
{
	this->player = player;
}

//In case of the player was of type aggressive--> they will reinforce the country which has the most number of armies
void AggresiveAIBehaviour::placeArmiesDuringReinforce()
{
	if (player->countries->size() == 0)
		return;

	//Getting the node of the country with most number of armies
	auto nodeToReinforce = findCountryNodeWithHighestAmountOfTroupsThatCanAttack();

	cout << "The player " << player->getPlayerName() << " has chosen to reinforce " << nodeToReinforce->countryInformation->getCountryName() << endl;
	
	nodeToReinforce->playerInfo->setNumberOfArmies(player->getNumberOfArmies() + nodeToReinforce->playerInfo->getNumberOfArmies());

	cout << "The country " << nodeToReinforce->countryInformation->countryName << " contains " << player->getNumberOfArmies() + nodeToReinforce->playerInfo->getNumberOfArmies() << " armies" << endl;

	player->setNumberOfArmies(0);
}

// The aggressive Type player will choose to attack with its country that contains the most number of armies
void AggresiveAIBehaviour::attackEnemies()
{
	if (player->countries->size() == 0)
		return;

	//choosing the country with which the country will attack 
	auto attackingNode = findCountryNodeWithHighestAmountOfTroupsThatCanAttack();

	cout << "The player " << player->getPlayerName() << " has chosen " << attackingNode->countryInformation->getCountryName() << " to attack from" << endl;

	//The player will keep trying to attack until they have one army left in the country
	while (attackingNode->playerInfo->getNumberOfArmies() != 1)
	{

		auto neighbours = attackingNode->neighbouringCountries;
		CountryNode * defendingNeighbours = nullptr;

		for (unsigned int i = 0; i < neighbours.size(); i++)
		{
			if (player->isEnemy(*neighbours[i]->countryInformation->countryName))
			{
				defendingNeighbours = neighbours[i];
			}
		}

		if (defendingNeighbours == NULL)
		{
			break;
		}
		
		cout << "The country " << defendingNeighbours->countryInformation->countryName << " has been chosen to be attacked " << endl;

		player->rollingSequence(attackingNode, defendingNeighbours);

		//choosing the country that has the biggest number of armies 
		attackingNode = findCountryNodeWithHighestAmountOfTroupsThatCanAttack();
	}
}

//In case if the player was of type fortify, by putting all its armies in one country
void AggresiveAIBehaviour::fortify()
{
	if (player->countries->size() == 0)
		return;

	//choose the country that has the biggest number of armies which doesn't have armies around it
	auto countryNodeWithTroups = findCountryNodeWithHighestAmountOfTroupsThatCannotAttack();

	cout << "The player " << player->getPlayerName() << " has chosen the country " << countryNodeWithTroups->countryInformation->getCountryName() << " to fortify" << endl;


	if (countryNodeWithTroups->playerInfo->getNumberOfArmies() > 1)
	{
		//The list of the neighbors that belong to countryNodeWithTroups
		auto neighbours = countryNodeWithTroups->neighbouringCountries;
		CountryNode * fortifiedNode = nullptr;
		for (unsigned int i = 0; i < neighbours.size(); i++)
		{
			if (player->countryOwnedByPlayer(*neighbours[i]->countryInformation->countryName))
			{
				fortifiedNode = neighbours[i];
				if (nodeHasEnemies(neighbours[i]))
				{
					break;
				}
			}
		}
		if (fortifiedNode)
		{
			cout << "The player " << player->getPlayerName() << " has chosen the country " << fortifiedNode->countryInformation->getCountryName()
				<< " to move their armies from " << countryNodeWithTroups->countryInformation->getCountryName() << endl;
			player->armyManipulationFortify(fortifiedNode, countryNodeWithTroups, countryNodeWithTroups->playerInfo->getNumberOfArmies() - 1);
		}

	}
	else {
		cout << "The player " << player->getPlayerName()  << " have only one army at " << countryNodeWithTroups->countryInformation->countryName << " to fortify " <<  endl;
	}

}

AggresiveAIBehaviour::AggresiveAIBehaviour(Player * player)
{
	this->player = player;
}


//The purpose of this method is to find the country that contains the country with the most number of armies
//Mina
CountryNode * AggresiveAIBehaviour::findCountryNodeWithHighestAmountOfTroupsThatCanAttack()
{
	auto ownedCountries = *player->countries;
	auto countryNode = ownedCountries[0];

	for(unsigned int i = 0; i < ownedCountries.size(); i++)
	{
		if (!nodeHasEnemies(countryNode))
		{
			countryNode = ownedCountries[i];
		}
		else if (countryNode->playerInfo->getNumberOfArmies() < ownedCountries[i]->playerInfo->getNumberOfArmies())
		{
			int countEnemies = 0;
			for (unsigned int j = 0; j < ownedCountries[i]->neighbouringCountries.size(); j++)
			{
				if (player->isEnemy(ownedCountries[i]->neighbouringCountries[j]->countryInformation->getCountryName()))
				{
					countEnemies++;
				}

			}

			if (countEnemies>0)
			{
				countryNode = ownedCountries[i];
			}
		}
	}

	return countryNode;
}


//Mina
CountryNode * AggresiveAIBehaviour::findCountryNodeWithHighestAmountOfTroupsThatCannotAttack()
{
	auto ownedCountries = *player->countries;
	auto countryNode = ownedCountries[0];

	for (unsigned int i = 0; i < ownedCountries.size(); i++)
	{
		if (nodeHasEnemies(countryNode))
		{
			continue;
		}
		else if (countryNode->playerInfo->getNumberOfArmies() < ownedCountries[i]->playerInfo->getNumberOfArmies())
		{

			countryNode = ownedCountries[i];
			
		}
	}

	return countryNode;
}

//The purpose of this method is to verify if a country has enemy country around them
bool  AggresiveAIBehaviour::nodeHasEnemies(CountryNode * node)
{

	//Getting the list of neighbors to country node 
	auto neighbours = node->neighbouringCountries;

	for (unsigned int i = 0; i < neighbours.size(); i++)
	{
		if (player->isEnemy(*neighbours[i]->countryInformation->countryName)) {
			return true;
		}
	}

	return false;
}

//The purpose of this method is to reinforce the country according to Benvolent player's logic
void BenevolentAIBehaviour::placeArmiesDuringReinforce()
{
	//While the player has more armies they can place 
	while (player->getNumberOfArmies())
	{
		cout << "The player " << player->getPlayerName() << " has " << player->getNumberOfArmies() << " to place" << endl;
		//find the country which has the least number of armies
		auto nodeToReinforce = findWeakestNodeOwnedByPlayer();

		cout << "The player " << player->getPlayerName() << " has chosen " << nodeToReinforce->countryInformation->getCountryName() << " to reinforce" << endl;
		
		//increase the number of armies that exist in the the chosen country 
		nodeToReinforce->playerInfo->setNumberOfArmies(nodeToReinforce->playerInfo->getNumberOfArmies() + 1);

		player->setNumberOfArmies(player->getNumberOfArmies()-1);
	}
}


void BenevolentAIBehaviour::attackEnemies()
{
	std::cout << "I am too benevolent to attack, ignoring the irony that my pacifism approach will cause more death in the long run";
}


//The purpose of this method is to implement the fortify logic according to the player of Benevolent type
void BenevolentAIBehaviour::fortify()
{
	if (player->countries->size() == 0)
		return;

	//Chosing the country to frotify 
	auto nodeToFortify = findWeakestNodeOwnedByPlayer();

	cout << "The player " << player->getPlayerName() << " has chosen the country " << nodeToFortify->countryInformation->getCountryName() << " to move their armies to from one of its neighbors" << endl;

	auto neighbours = nodeToFortify->neighbouringCountries;
	CountryNode * countryNodeWithTroups = nullptr;
	for (unsigned int i = 0; i < neighbours.size(); i++)
	{
		if (player->countryOwnedByPlayer(*neighbours[i]->countryInformation->countryName))
		{
			countryNodeWithTroups = neighbours[i];
			if (countryNodeWithTroups->playerInfo->getNumberOfArmies() -1 > nodeToFortify->playerInfo->getNumberOfArmies())
			{

				cout << "The player " << player->getPlayerName() << " has chosen the country " << nodeToFortify->countryInformation->getCountryName()
					<< " to move their armies from " << countryNodeWithTroups->countryInformation->getCountryName() << endl;

				int numOfArmiesToTransfer = (countryNodeWithTroups->playerInfo->getNumberOfArmies() + nodeToFortify->playerInfo->getNumberOfArmies())/2;
				numOfArmiesToTransfer = countryNodeWithTroups->playerInfo->getNumberOfArmies() - numOfArmiesToTransfer;
				player->armyManipulationFortify(nodeToFortify, countryNodeWithTroups, numOfArmiesToTransfer);
				break;
			}
		}
	}


}

BenevolentAIBehaviour::BenevolentAIBehaviour(Player * player)
{
	this->player = player;
}

//Find the country that has the least number of armies owned by the player
CountryNode * BenevolentAIBehaviour::findWeakestNodeOwnedByPlayer()
{
	//Get the list of countries owned by the player
	auto ownedCountries = *player->countries;
	auto countryNode = ownedCountries[0];

	for (unsigned int i = 0; i < ownedCountries.size(); i++)
	{
		if (countryNode->playerInfo->getNumberOfArmies() > ownedCountries[i]->playerInfo->getNumberOfArmies())
		{
			countryNode = ownedCountries[i];
		}
	}

	return countryNode;
}

int Behaviour::getAttackRoll(int attackArmiesOnNode)
{
	if (attackArmiesOnNode > 3)
		return 3;
	return attackArmiesOnNode - 1;
}

int Behaviour::getDefenseRoll(int defenseArmiesOnNode)
{
	if (defenseArmiesOnNode > 2)
		return 2;
	else
		return defenseArmiesOnNode;
}

int Behaviour::getNumberOfTroopsToTransfer(int attackerArmies)
{
	return attackerArmies -1;
}
