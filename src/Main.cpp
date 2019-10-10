// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MapLoader.h"
#include "DiceDriver.h"
#include "../inc/Cards.h"
#include "../inc/PlayerDriver.h"

int main()
{
	// Map map = MapLoader::loadMap("./InvalidWorld.map");
	//DiceDriver * diceTest = new DiceDriver();
	//diceTest->DiceTester();
	PlayerDriver * playerTest = new  PlayerDriver();
	playerTest->PlayerTester();
	Player *player = new Player();
	Deck * deckOfCards = new Deck();
	deckOfCards->generateDeck(15);
	/*int i = 0;
	while (i < 15) {
		Card * nek = deckOfCards->draw();
		cout << nek->getCard() << " and " << deckOfCards->getSize() << endl;
		i++;
	}*/
	player->attack();
	//HandOfCards* hand = new HandOfCards();
	//hand->PrintValues();
//	string* str = new string("artillery");
	//cout <<<< endl;
	
	player->getDice().addToRollHistory(player->getDice().roll(3));
}
	
	
	

	





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
