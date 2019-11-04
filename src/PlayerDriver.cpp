

#include <new>
#include "PlayerDriver.h"
#include <iostream>

void PlayerDriver::PlayerTester()
{
	Map * map = MapLoader::loadMap("./worldNew.map");
	auto mapNode = map->getFirstNode();
	std::vector<CountryNode*> countries;
	std::vector<CountryNode*> * kok = new std::vector< CountryNode*>();
	kok->push_back(mapNode);
	kok->push_back(mapNode->neighbouringCountries[0]);
	Player* player = new Player("Hambrsoom", kok);
	kok->at(0)->playerInfo->setPlayerName("Hambrsoom");
	kok->at(0)->playerInfo->setNumberOfArmies(12);
	kok->at(1)->playerInfo->setNumberOfArmies(4);
	kok->at(1)->playerInfo->setPlayerName("Hambrsoom");

	std::vector<CountryNode*> *  patrickCountries = new std::vector< CountryNode*>();
	
	patrickCountries->push_back(mapNode->neighbouringCountries[1]);
	patrickCountries->push_back(mapNode->neighbouringCountries[2]);
	Player* player2 = new Player("Patrick", patrickCountries);
	patrickCountries->at(0)->playerInfo->setPlayerName("Patrick");
	patrickCountries->at(0)->playerInfo->setNumberOfArmies(10);
	patrickCountries->at(1)->playerInfo->setNumberOfArmies(20);
	patrickCountries->at(1)->playerInfo->setPlayerName("Patrick");

	cout << "Player 2 turn to fortify" << endl;
	player2->attack();

	/*DicesPrompt * dicesPrompt = new DicesPrompt();
	Deck* deck = new Deck(map->getNumberOfCountriesInMap());*/
	//Testing the functionality of the three methods:
	cout << "Player 1 turn to fortify" << endl;
	player->attack();
	player->fortify();
	player->reinforce();

	//
	//cout << "The deck has " << deck->getSize() << " " << " cards" << endl;
	//player->getHandOfCards()->pickACard(deck);
	//player->getHandOfCards()->pickACard(deck);
	//player->getHandOfCards()->pickACard(deck);
	//player->getHandOfCards()->pickACard(deck);
	//player->getHandOfCards()->pickACard(deck);
	//cout << "The deck is left with " << deck->getSize() << " " << " cards" << endl;


	//cout << "The player has no w in their hand: " << endl;
	//player->getHandOfCards()->PrintValues();

	//int numberOfCardsWillBeGiven = 0;
	//if (player->getHandOfCards()->getTotalNumberOfCards() >= 5)
	//{
	//	for (int i = 0; i < 2; i++)
	//	{
	//		numberOfCardsWillBeGiven = player->getHandOfCards()->exchange();
	//		cout << "The number of given this round is " << numberOfCardsWillBeGiven << " cards" << endl;
	//		player->setNumberOfArmies(player->getNumberOfArmies() + numberOfCardsWillBeGiven);
	//		cout << "The number of the player's armies after executing exchange is: " << player->getNumberOfArmies() << endl;
	//	}
	//}
	//else
	//{
	//	numberOfCardsWillBeGiven = player->getHandOfCards()->exchange();
	//	cout << "The number of given this round is " << numberOfCardsWillBeGiven << " cards" << endl;
	//	player->setNumberOfArmies(player->getNumberOfArmies() + numberOfCardsWillBeGiven);
	//	cout << "The number of the player's armies after executing exchange is: " << player->getNumberOfArmies() << endl;
	//}
	//

	////Player's Dice Test:
	//int numDice = dicesPrompt->getRolledNumberOfDice();
	//player->getDice()->roll(numDice);
	//player->getDice()->showRollHistory();

	//numDice = dicesPrompt->getRolledNumberOfDice();
	//player->getDice()->roll(numDice);
	//player->getDice()->showRollHistory();
	//
	//delete player;
	//delete map;
	//delete dicesPrompt;
	//delete deck;
}
