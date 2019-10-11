// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MapDriver.h"
#include "DiceDriver.h"
#include "PlayerDriver.h"
int main()
{
	// Map map = MapLoader::loadMap("./InvalidWorld.map");
	DiceDriver * diceTest = new DiceDriver();
	diceTest->DiceTester();
	PlayerDriver * playerTest = new  PlayerDriver();
	playerTest->PlayerTester();
}

