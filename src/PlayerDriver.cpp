

#include <new>
#include "PlayerDriver.h"
#include <iostream>

void PlayerDriver::PlayerTester()
{
	Map * map = MapLoader::loadMap("./worldNew.map");
	auto mapNode = map->getFirstNode();
	std::vector<CountryNode*> countries;
	countries.push_back(mapNode);
	countries.push_back(mapNode->neighbouringCountries[0]);
	Player* player = new Player("Hambersoom", countries);
	DicesPrompt * dicesPrompt = new DicesPrompt();
	Deck* deck = new Deck(map->getNumberOfCountriesInMap());

	//Testing the functionality of the three methods:
	player->attack();
	player->fortify();
	player->reinforce();

	
	cout << "The deck has " << deck->getSize() << " " << " cards" << endl;
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	cout << "The deck is left with " << deck->getSize() << " " << " cards" << endl;


	cout << "The player has no w in their hand: " << endl;
	player->getHandOfCards()->PrintValues();

	int numberOfCardsWillBeGiven = 0;
	if (player->getHandOfCards()->getTotalNumberOfCards() >= 5)
	{
		for (int i = 0; i < 2; i++)
		{
			numberOfCardsWillBeGiven = player->getHandOfCards()->exchange();
			cout << "The number of given this round is " << numberOfCardsWillBeGiven << " cards" << endl;
			player->setNumberOfArmies(player->getNumberOfArmies() + numberOfCardsWillBeGiven);
			cout << "The number of the player's armies after executing exchange is: " << player->getNumberOfArmies() << endl;
		}
	}
	else
	{
		numberOfCardsWillBeGiven = player->getHandOfCards()->exchange();
		cout << "The number of given this round is " << numberOfCardsWillBeGiven << " cards" << endl;
		player->setNumberOfArmies(player->getNumberOfArmies() + numberOfCardsWillBeGiven);
		cout << "The number of the player's armies after executing exchange is: " << player->getNumberOfArmies() << endl;
	}
	

	//Player's Dice Test:
	int numDice = dicesPrompt->getRolledNumberOfDice();
	player->getDice()->roll(numDice);
	player->getDice()->showRollHistory();

	numDice = dicesPrompt->getRolledNumberOfDice();
	player->getDice()->roll(numDice);
	player->getDice()->showRollHistory();
	
	delete player;
	delete map;
	delete dicesPrompt;
	delete deck;
}
