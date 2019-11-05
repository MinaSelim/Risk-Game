#include <new>
#include "PlayerDriver.h"
#include <iostream>

using namespace std;
void PlayerDriver::PlayerTester()
{
	Map * map = MapLoader::loadMap("./maps/worldNew.map");
	Deck* deck = new Deck(map->getNumberOfCountriesInMap());
	auto mapNode = map->getFirstNode();

	//Creating the first player:
	vector<CountryNode*> * hambrsoomCountries = new std::vector< CountryNode*>();
	Player* player = new Player("Hambrsoom", hambrsoomCountries, map);

	//The fortify, attack and reinforce will tell the player that they can't fortify because they don't have any countries yet
	player->fortify();
	player->attack();
	player->reinforce();

	//Assigning the countries to the player 
	hambrsoomCountries->push_back(mapNode);
	hambrsoomCountries->push_back(mapNode->neighbouringCountries[0]);
	hambrsoomCountries->at(0)->playerInfo->assignPlayer(player);
	hambrsoomCountries->at(0)->playerInfo->setNumberOfArmies(12);
	hambrsoomCountries->at(1)->playerInfo->setNumberOfArmies(4);
	hambrsoomCountries->at(1)->playerInfo->assignPlayer(player);


	//Creating the second player:
	//The purpose of the second player is to assign some of the neigbors of player1 so that player1 can attack them.
	std::vector<CountryNode*> *  patrickCountries = new std::vector< CountryNode*>();
	patrickCountries->push_back(mapNode->neighbouringCountries[1]);
	patrickCountries->push_back(mapNode->neighbouringCountries[2]);
	Player* player2 = new Player("Patrick", patrickCountries, map);
	patrickCountries->at(0)->playerInfo->assignPlayer(player2);
	patrickCountries->at(0)->playerInfo->setNumberOfArmies(10);
	patrickCountries->at(1)->playerInfo->assignPlayer(player2);
	patrickCountries->at(1)->playerInfo->setNumberOfArmies(20);

	//Normally Testing fortify:
	player->fortify();

	//Will call the reinforce method and try to use the cards which will fail because the player doesn't have any yet:
	player->reinforce();
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	//The player still won't be able to get army because he doesn't have enough army.
	player->reinforce();
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);
	player->getHandOfCards()->pickACard(deck);

	//The player will be able to exchange cards forcibly because they have 5 cards
	player->reinforce();

	player->attack();
	player->printListOfCountries();

	cout << "Creating player reinforce" << endl;
	Player* reinforcePlayer = new Player("Reinforce Player", new std::vector< CountryNode*>(), map);
	auto countriesGraph = map->getCountriesGraph();
	for (unsigned int i = 0; i < countriesGraph.size(); i++) {
		if (*countriesGraph[i]->countryInformation->continentId == 1) {
			reinforcePlayer->addCountryOwnerShip(countriesGraph[i], 9);
		}
	}

	reinforcePlayer->reinforce();

	delete map;
	delete player;
	delete player2;
	delete deck;
}