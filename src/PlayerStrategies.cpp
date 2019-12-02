#include "PlayerStrategies.h"
#include "Player.h"
#include "Utility.h"
#include "Dice.h"
#include "ErrorCodes.h"
#include <iostream>

using namespace::std;

//The purpose of the method is to interact with the user during the reinforce phase to ask them 
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

	//Placing the armies at the chosen country
	player->setNumberOfArmyAtCountry(*player->map->getNodeFromGraphByName(chosenCountry), numOfArmiesAtChosenCountry + chosenArmyNumber);

	cout << "The number of armies is: " << numOfArmiesAtChosenCountry + chosenArmyNumber << " armies at " << chosenCountry << endl;

	//Decrease the number of armies they can place in a country during the reiforce phase
	player->setNumberOfArmies(player->getNumberOfArmies() - chosenArmyNumber);
}


//If the player was human, they will asked which country they want to attack
void HumanBehaviour::attackEnemies()
{
	//Making sure that the player has some countries to use it in the attack
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

//Prompts human player to roll
int HumanBehaviour::getAttackRoll(int attackArmiesOnNode)
{
	DicesPrompt dicesPrompt;
	int attackerNumDice = dicesPrompt.getRolledNumberOfDice(true, attackArmiesOnNode);

	return attackerNumDice;
}

//Prompts Human player to roll
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

	//Getting the node of the country with most number of armies and that can attack its neighbors
	auto nodeToReinforce = findCountryNodeWithHighestAmountOfTroupsThatCanAttack();

	cout << "The player " << player->getPlayerName() << " has chosen to reinforce " << nodeToReinforce->countryInformation->getCountryName() << endl;
	
	nodeToReinforce->playerInfo->setNumberOfArmies(player->getNumberOfArmies() + nodeToReinforce->playerInfo->getNumberOfArmies());

	cout << "The country " << nodeToReinforce->countryInformation->getCountryName() << " contains " << player->getNumberOfArmies() + nodeToReinforce->playerInfo->getNumberOfArmies() << " armies" << endl;

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

	//The player will keep attacking until they have one army left in the country
	while (attackingNode->playerInfo->getNumberOfArmies() != 1)
	{
		//Get the list of the neighbors
		auto neighbours = attackingNode->neighbouringCountries;
		CountryNode * defendingNeighbours = nullptr;

		//Find the neighbor which is an enemy
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
		
		cout << "The player " << player->getPlayerName() << " has chosen the country " << defendingNeighbours->countryInformation->getCountryName() << " to attack" << endl;

		player->rollingSequence(attackingNode, defendingNeighbours);

		//choosing the country that has the biggest number of armies and that can attack
		attackingNode = findCountryNodeWithHighestAmountOfTroupsThatCanAttack();
	}
}

//In case if the player was of type fortify, by putting all its armies in one country
void AggresiveAIBehaviour::fortify()
{
	if (player->countries->size() == 0)
		return;

	//choose the country that has the biggest number of armies which doesn't have enemies around it
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
			cout << "The player " << player->getPlayerName() << " has chosen to move their armies to the country " << fortifiedNode->countryInformation->getCountryName()
				<< " from " << countryNodeWithTroups->countryInformation->getCountryName() << endl;
			player->armyManipulationFortify(fortifiedNode, countryNodeWithTroups, countryNodeWithTroups->playerInfo->getNumberOfArmies() - 1);
		}

	}
	else {
		cout << "The player " << player->getPlayerName()  << " have only one army at " << countryNodeWithTroups->countryInformation->getCountryName() << " to fortify " <<  endl;
	}

}

AggresiveAIBehaviour::AggresiveAIBehaviour(Player * player)
{
	this->player = player;
}


//The purpose of this method is to find the country that contains the most number of armies that can attack
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


//The purpose of this method is to find the country that contains the most number of armies that cannot attack
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
bool  Behaviour::nodeHasEnemies(CountryNode * node)
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
		cout << "The player " << player->getPlayerName() << " has " << player->getNumberOfArmies() << " to place in a country" << endl;

		//find the country which has the least number of armies
		auto nodeToReinforce = findWeakestNodeOwnedByPlayer();

		cout << "The player " << player->getPlayerName() << " has chosen " << nodeToReinforce->countryInformation->getCountryName() << " to reinforce" << endl;
		
		//increase the number of armies that exist in the the chosen country 
		nodeToReinforce->playerInfo->setNumberOfArmies(nodeToReinforce->playerInfo->getNumberOfArmies() + 1);

		cout << "The country " << nodeToReinforce->countryInformation->getCountryName() << " has " << nodeToReinforce->playerInfo->getNumberOfArmies() << " armies" << endl;

		player->setNumberOfArmies(0);
	}
}


void BenevolentAIBehaviour::attackEnemies()
{
	std::cout << "I am too benevolent to attack, ignoring the irony that my pacifism approach will cause more death in the long run";
}


//The purpose of this method is to implement the fortify logic according to the player of type Benevolent
void BenevolentAIBehaviour::fortify()
{
	if (player->countries->size() == 0)
		return;

	//Choose the country to which the player will their armies to from one of its neigbors  
	auto nodeToFortify = findWeakestNodeOwnedByPlayer();

	cout << "The player " << player->getPlayerName() << " has chosen  to move their armies to the country " << nodeToFortify->countryInformation->getCountryName() << " from one of its neighbors" << endl;

	//Get the list of the neighbors
	auto neighbours = nodeToFortify->neighbouringCountries;

	CountryNode * countryNodeWithTroups = nullptr;

	for (unsigned int i = 0; i < neighbours.size(); i++)
	{
		//Make sure the country is owned by the player
		if (player->countryOwnedByPlayer(*neighbours[i]->countryInformation->countryName))
		{
			countryNodeWithTroups = neighbours[i];
			if (countryNodeWithTroups->playerInfo->getNumberOfArmies() -1 > nodeToFortify->playerInfo->getNumberOfArmies())
			{
				cout << "The player " << player->getPlayerName() << " has chosen to move their armies to the country " << nodeToFortify->countryInformation->getCountryName()
					<< " from " << countryNodeWithTroups->countryInformation->getCountryName() << endl;

				//Calculating the number of armies to be moved
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
		//Find the country owned by the player and has the least number of armies
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

//Thearmies are placed randomly on a Node that can attack
void RandomAIBehaviour::placeArmiesDuringReinforce()
{
	if (player->countries->size() == 0)
		return;

	//Getting a random node that can attack. A random Node can cause a game to become unwinnable (which is against the instruction)
	auto nodeToReinforce = findRandomNodeOwnedByPlayerThatCanAttack(); 

	cout << "The player " << player->getPlayerName() << " has chosen to reinforce " << nodeToReinforce->countryInformation->getCountryName() << endl;

	nodeToReinforce->playerInfo->setNumberOfArmies(player->getNumberOfArmies() + nodeToReinforce->playerInfo->getNumberOfArmies());

	cout << "The country " << nodeToReinforce->countryInformation->getCountryName() << " contains " << player->getNumberOfArmies() + nodeToReinforce->playerInfo->getNumberOfArmies() << " armies" << endl;

	player->setNumberOfArmies(0);
	player->printListOfCountries();
}

//The random Ai attacks enemmies a random amount of times
void RandomAIBehaviour::attackEnemies()
{
	auto potentialAttackers = findEveryNodeThatCanAttack();
	int numOfAttacksLeft = rand() % MAX_NUMBER_OF_RANDOM_ATTACKS; // Picked a random number of Max attacks

	while (potentialAttackers.size() > 0 && numOfAttacksLeft > 0)
	{
		int attackerIndex = rand() % potentialAttackers.size();
		auto attackingNode = potentialAttackers[attackerIndex];

		//Get the list of the neighbors
		auto neighbours = attackingNode->neighbouringCountries;
		CountryNode * defendingNeighbours = nullptr;

		//Find the neighbor which is an enemy
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

		cout << "The player " << player->getPlayerName() << " has chosen the country " << defendingNeighbours->countryInformation->getCountryName() << " to attack" << endl;

		player->rollingSequence(attackingNode, defendingNeighbours);

		numOfAttacksLeft--;
		potentialAttackers = findEveryNodeThatCanAttack();
	}
}

//fortify a random node to fortify
void RandomAIBehaviour::fortify()
{
	auto nodes = findEveryFortifiableNode();
	int nodeToFortifyIndex = rand() % nodes.size();
	CountryNode * nodeToFortify = nodes[nodeToFortifyIndex];

	auto neigboursThatCanReinforce = findEveryNeighbourNodeThatCanFortify(nodeToFortify);
	int reinforcingNeighbourIndex = rand() % neigboursThatCanReinforce.size();
	CountryNode * reinforcingNeighbour = neigboursThatCanReinforce[reinforcingNeighbourIndex];

	int randomNumberOfTroopsToTransfer = (rand() % reinforcingNeighbour->playerInfo->getNumberOfArmies()-1) + 1; // this gets a number between 1 and num of armies

	player->armyManipulationFortify(nodeToFortify, reinforcingNeighbour, randomNumberOfTroopsToTransfer);

}

RandomAIBehaviour::RandomAIBehaviour(Player * player)
{
	this->player = player;
}

//Helped function to find which node to reinforce
CountryNode * RandomAIBehaviour::findRandomNodeOwnedByPlayerThatCanAttack()
{
	auto ownedCountries = *player->countries;
	std::vector<CountryNode*> nodes;
	for (int i = 0; i < ownedCountries.size(); i++)
	{
		if (nodeHasEnemies(ownedCountries[i]))
		{
			nodes.push_back(ownedCountries[i]);
		}
	}
	int randomCountryIndex = rand() % nodes.size();

	return  nodes[randomCountryIndex];
}

// Helper find every fortifiable node
std::vector<CountryNode*> RandomAIBehaviour::findEveryFortifiableNode()
{
	auto countryNodes = player->countries;

	std::vector<CountryNode*> nodes;

	for (int i = 0; i < countryNodes->size(); i++)
	{
		CountryNode * node = (*countryNodes)[i];
		if (hasNeighboursThatCanFortify(node)) {
			nodes.push_back(node);
		}
	}

	return nodes;
}

//helper function to find fortifiable neighbours
bool RandomAIBehaviour::hasNeighboursThatCanFortify(CountryNode * node)
{
	auto neighbours = node->neighbouringCountries;
	for (int i = 0; i < neighbours.size(); i++)
	{
		if (player->countryOwnedByPlayer(*neighbours[i]->countryInformation->countryName) &&
			neighbours[i]->playerInfo->getNumberOfArmies() > 1)
		{
			return true;
		}
	}

	return false;
}

//Find every neighbour that can fortify
std::vector<CountryNode*> RandomAIBehaviour::findEveryNeighbourNodeThatCanFortify(CountryNode * node)
{
	std::vector<CountryNode*> neighboursToReturn;
	auto neighbours = node->neighbouringCountries;
	for (int i = 0; i < neighbours.size(); i++)
	{
		if (player->countryOwnedByPlayer(*neighbours[i]->countryInformation->countryName) &&
			neighbours[i]->playerInfo->getNumberOfArmies() > 1)
		{
			neighboursToReturn.push_back(neighbours[i]);
		}
	}

	return neighboursToReturn;
}

//helper functions that finds every node that can attack
std::vector<CountryNode*> RandomAIBehaviour::findEveryNodeThatCanAttack()
{
	std::vector<CountryNode*> retVector;
	auto countryNodes = player->countries;

	for (int i = 0; i < countryNodes->size(); i++)
	{
		if ((*countryNodes)[i]->playerInfo->getNumberOfArmies() > 1 && nodeHasEnemies((*countryNodes)[i]))
		{
			retVector.push_back((*countryNodes)[i]);
		}
	}

	return retVector;

}

CheaterAIBehaviour::CheaterAIBehaviour(Player * player)
{
	this->player = player;
}

//The cheater will reinforce each country they have by doubling the number of armies
void CheaterAIBehaviour::placeArmiesDuringReinforce()
{
	//it will count the number of time the method will be called
	//its purpose is to let the cheater only double the number of armies once 
	//during the setup time
	static int gameSetupTurn = 0;
	
	//the last turn in the reinforce calling method during the setup
	if (gameSetupTurn == 39) {
		//Multiplying by two the number of armies of each country 
		for (int i = 0; i < player->countries->size(); i++) {
			int originalNumberOfArmy = player->countries->at(i)->playerInfo->getNumberOfArmies();
			player->countries->at(i)->playerInfo->setNumberOfArmies(originalNumberOfArmy * 2);
		}
		cout << "After the attack phase, player " << player->getPlayerName() << " has these many armies in each of their country: \n" << endl;
		player->printListOfCountries();
	}

	//Everytime after the setup.
	else if (gameSetupTurn > 39) {
		//Multiplying by two the number of armies of each country 
		for (int i = 0; i < player->countries->size(); i++) {
			if (player->countries->at(i)->playerInfo->getNumberOfArmies() < 100000) {
				int originalNumberOfArmy = player->countries->at(i)->playerInfo->getNumberOfArmies();
				player->countries->at(i)->playerInfo->setNumberOfArmies(originalNumberOfArmy * 2);
			}
		}
		cout << "After the attack phase, player " << player->getPlayerName() << " has these many armies in each of their country: \n" << endl;
		player->printListOfCountries();
	}
	
	player->setNumberOfArmies(0);
	gameSetupTurn++;
}

//The cheater will conquer the neighbor countries without even attacking them.
void CheaterAIBehaviour::attackEnemies()
{
	if (player->countries->size() == 0)
		return;

	//will go through all the countries of the player which has enemy neighbors
	for (int i = 0; i < player->countries->size(); i++)
	{
		//To make sure that the neighbor is an enemy
		if (hasAnEnemyNeighbor(*player->countries->at(i))) 
		{
			attackingNeighbors(*player->countries->at(i));
		}
	}
	cout << "After the attack phase, player " << player->getPlayerName() << " rules these countries: \n" << endl;
	player->printListOfCountries();
}


//Will conquer every enemy neighbor without executing the atacking method.
void CheaterAIBehaviour::attackingNeighbors(CountryNode & country)
{
	for (int i = 0; i < country.neighbouringCountries.size(); i++) 
	{
		//To make sure that the neighbor is an enemy
		if (player->isEnemy(country.neighbouringCountries.at(i)->countryInformation->getCountryName()))
		{
			player->addCountryOwnerShip(country.neighbouringCountries.at(i), country.neighbouringCountries.at(i)->playerInfo->getNumberOfArmies());
		}
	}
} 


//The player will basically multiple by two the number of armies they have in each county 
//which has at least one enemy neighbor
void CheaterAIBehaviour::fortify()
{
	if (player->countries->size() == 0)
		return;

	//looping through the list of player's countries
	for (int i = 0; i < player->countries->size(); i++) 
	{
		//To make sure that the player has at least one enemy neighbor
		if (hasAnEnemyNeighbor(*player->countries->at(i)) && player->countries->at(i)->playerInfo->getNumberOfArmies() < 100000)
		{
			int originalNumberOfArmy = player->countries->at(i)->playerInfo->getNumberOfArmies();
			player->countries->at(i)->playerInfo->setNumberOfArmies(originalNumberOfArmy * 2);
			cout << "The country " << player->countries->at(i)->countryInformation->getCountryName() << 
				" has " << player->countries->at(i)->playerInfo->getNumberOfArmies() << endl;
		}
	}
}

//The method is to make sure that the player's country has at least one enemy neighbor
bool CheaterAIBehaviour::hasAnEnemyNeighbor(CountryNode & country)
{
	for (unsigned int i = 0; i < country.neighbouringCountries.size(); i++)
	{
		if (player->isEnemy(country.neighbouringCountries.at(i)->countryInformation->getCountryName()))
		{
			return true;
		}
	}
	return false;
}


//The mehod is to validate that the country has at least 2 armies.
bool CheaterAIBehaviour::hasEnoughArmies(CountryNode & country)
{
	return country.playerInfo->getNumberOfArmies() > 1;
}