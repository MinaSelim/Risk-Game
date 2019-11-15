#include "PlayerStrategies.h"
#include "Player.h"
#include "Utility.h"
#include "Dice.h"
#include "ErrorCodes.h"
#include <iostream>

using namespace::std;
void HumanBehaviour::placeArmiesDuringReinforce()
{
	vector<int> neightboursIds;
	int chosenArmyNumber = 0;
	string chosenCountry = "N/A";
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
	player->setNumberOfArmies(player->getNumberOfArmies() - chosenArmyNumber);

}

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
				attackingCountry = player->chooseAttackingCountry();
				defendingCountry = player->chooseCountryToBeAttacked(attackingCountry);
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
					int numOfArmiesAtNeighboringCountry = player->getNumberOfArmyAtCountry(*chosenNeighborCountry->countryInformation->countryName);
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

int HumanBehaviour::getAttackRoll(int attackArmiesOnNode)
{
	DicesPrompt dicesPrompt;
	int attackerNumDice = dicesPrompt.getRolledNumberOfDice(true, attackArmiesOnNode);

	return attackerNumDice;
}

int HumanBehaviour::getDefenseRoll(int defenseArmiesOnNode)
{
	DicesPrompt dicesPrompt;
	int attackerNumDice = dicesPrompt.getRolledNumberOfDice(false, defenseArmiesOnNode);

	return attackerNumDice;
}

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


void AggresiveAIBehaviour::placeArmiesDuringReinforce()
{
	if (player->countries->size() == 0)
		return;
	auto nodeToReinforce = findCountryNodeWithHighestAmountOfTroupsThatCanAttack();
	nodeToReinforce->playerInfo->setNumberOfArmies(player->getNumberOfArmies() + nodeToReinforce->playerInfo->getNumberOfArmies());

	player->setNumberOfArmies(0);

}

void AggresiveAIBehaviour::attackEnemies()
{
	if (player->countries->size() == 0)
		return;
	auto attackingNode = findCountryNodeWithHighestAmountOfTroupsThatCanAttack();
	while (attackingNode->playerInfo->getNumberOfArmies() != 1)
	{
		auto neighbours = attackingNode->neighbouringCountries;
		CountryNode * defendingNeighbours = nullptr;

		for (int i = 0; i < neighbours.size(); i++)
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


		player->rollingSequence(attackingNode, defendingNeighbours);

		attackingNode = findCountryNodeWithHighestAmountOfTroupsThatCanAttack();

	}
}

void AggresiveAIBehaviour::fortify()
{
	if (player->countries->size() == 0)
		return;
	auto countryNodeWithTroups = findCountryNodeWithHighestAmountOfTroupsThatCannotAttack();
	if (countryNodeWithTroups->playerInfo->getNumberOfArmies() > 1)
	{
		auto neighbours = countryNodeWithTroups->neighbouringCountries;
		CountryNode * fortifiedNode = nullptr;
		for (int i = 0; i < neighbours.size(); i++)
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
			player->armyManipulationFortify(fortifiedNode, countryNodeWithTroups, countryNodeWithTroups->playerInfo->getNumberOfArmies() - 1);
		}

	}
}

AggresiveAIBehaviour::AggresiveAIBehaviour(Player * player)
{
	this->player = player;
}

CountryNode * AggresiveAIBehaviour::findCountryNodeWithHighestAmountOfTroupsThatCanAttack()
{
	auto ownedCountries = *player->countries;
	auto countryNode = ownedCountries[0];

	for(int i = 0; i < ownedCountries.size(); i++)
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

CountryNode * AggresiveAIBehaviour::findCountryNodeWithHighestAmountOfTroupsThatCannotAttack()
{
	auto ownedCountries = *player->countries;
	auto countryNode = ownedCountries[0];

	for (int i = 0; i < ownedCountries.size(); i++)
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

bool  AggresiveAIBehaviour::nodeHasEnemies(CountryNode * node)
{
	auto neighbours = node->neighbouringCountries;

	for (int i = 0; i < neighbours.size(); i++)
	{
		if (player->isEnemy(*neighbours[i]->countryInformation->countryName)) {
			return true;
		}
	}

	return false;
}

void BenevolentAIBehaviour::placeArmiesDuringReinforce()
{
	while (player->getNumberOfArmies())
	{
		auto nodeToReinforce = findWeakestNodeOwnedByPlayer();
		nodeToReinforce->playerInfo->setNumberOfArmies(nodeToReinforce->playerInfo->getNumberOfArmies() + 1);

		player->setNumberOfArmies(player->getNumberOfArmies()-1);
	}
}

void BenevolentAIBehaviour::attackEnemies()
{
	std::cout << "I am too benevolent to attack, ignoring the irony that my pacifism approach will cause more death in the long run";
}

void BenevolentAIBehaviour::fortify()
{
	if (player->countries->size() == 0)
		return;
	auto nodeToFortify = findWeakestNodeOwnedByPlayer();

	auto neighbours = nodeToFortify->neighbouringCountries;
	CountryNode * countryNodeWithTroups = nullptr;
	for (int i = 0; i < neighbours.size(); i++)
	{
		if (player->countryOwnedByPlayer(*neighbours[i]->countryInformation->countryName))
		{
			countryNodeWithTroups = neighbours[i];
			if (countryNodeWithTroups->playerInfo->getNumberOfArmies() -1 > nodeToFortify->playerInfo->getNumberOfArmies())
			{
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

CountryNode * BenevolentAIBehaviour::findWeakestNodeOwnedByPlayer()
{
	auto ownedCountries = *player->countries;
	auto countryNode = ownedCountries[0];

	for (int i = 0; i < ownedCountries.size(); i++)
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
