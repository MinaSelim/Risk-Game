
// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MapDriver.h"
#include "DiceDriver.h"
#include "PlayerDriver.h"
int main()
{
	MapDriver::MapTester();
	DiceDriver::DiceTester();
	PlayerDriver::PlayerTester();

	return 0;
}

