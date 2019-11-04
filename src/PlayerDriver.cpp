

#include <new>
#include "PlayerDriver.h"
#include <iostream>

void PlayerDriver::PlayerTester()
{
	/*	Map * map = MapLoader::loadMap("./maps/worldNew.map");
	auto mapNode = map->getFirstNode();
	std::vector<CountryNode*> countries;
	std::vector<CountryNode*> * kok = new std::vector< CountryNode*>();
	kok->push_back(mapNode);
	kok->push_back(mapNode->neighbouringCountries[0]);
	Player* player = new Player("Hambrsoom", kok, *map);
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

<<<<<<< HEAD
	/*DicesPrompt * dicesPrompt = new DicesPrompt();
	Deck* deck = new Deck(map->getNumberOfCountriesInMap());*/
=======
	DicesPrompt * dicesPrompt = new DicesPrompt();
	Deck* deck = new Deck(map->getNumberOfCountriesInMap());

	
	cout << "The deck has " << deck->getSize() << " " << " cards" << endl;
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	cout << "The deck is left with " << deck->getSize() << " " << " cards" << endl;

	
	cout << "The deck has " << deck->getSize() << " " << " cards" << endl;
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	cout << "The deck is left with " << deck->getSize() << " " << " cards" << endl;

	
	cout << "The deck has " << deck->getSize() << " " << " cards" << endl;
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	cout << "The deck is left with " << deck->getSize() << " " << " cards" << endl;

>>>>>>> origin/master
	//Testing the functionality of the three methods:
	//player->attack();
	//player->fortify();
	//player->reinforce();
	*/
}
