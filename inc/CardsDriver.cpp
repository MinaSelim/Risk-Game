#include "CardsDriver.h"
#include "MapLoader.h"
#include <iostream>

using namespace std;

void CardsDriver::CardsTester()
{
	Map * map				   = MapLoader::loadMap("./worldNew.map");
	HandOfCards * handOfCards	   = new HandOfCards();

	int numberOfCountriesInMap = map->getNumberOfCountriesInMap();
	int numberOfCardsInDeck    = numberOfCountriesInMap;

	cout << "The number of Countries in the Map: " << numberOfCountriesInMap << endl;
	cout << "The number of Cards in the deck is: " << numberOfCardsInDeck << endl;

	Deck * deck = new Deck(numberOfCardsInDeck);
	bool done = false;
	deck->showDeck();
	
	//The player has no cards:
	handOfCards->exchange();

	//asking player input (in case the user has less than 5 cards)-> they have the option 
	//to either try to exchange or not: 
	handOfCards->pickACard(deck);
	handOfCards->pickACard(deck);
	handOfCards->pickACard(deck);
	handOfCards->exchange();
	int sizeOfDeck = deck->getSize();

	//In case of the player has more than 5 cards:
	for (int i = 0; i < sizeOfDeck; i++) {
		handOfCards->pickACard(deck);
	}
	while (!done) {
		int armies = handOfCards->exchange();
		cout << "The number of armies that the player will get is: " << armies << endl;
		if (armies == 0) {
			done = true;
		}
	}
	
	delete map;
	delete deck;
	delete handOfCards;
}
