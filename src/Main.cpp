#include <iostream>
#include "MapDriver.h"
#include "MapLoaderDriver.h"
#include "DiceDriver.h"
#include "PlayerDriver.h"
#include "CardsDriver.h"
#include "GameEngine.h"
int main()
{
	GameEngine e;
	std::vector<std::string> files = FileIO::readDirectory("maps");
	//MapDriver::MapTester();
	//MapLoaderDriver::MapTester();
	//DiceDriver::DiceTester();
	PlayerDriver::PlayerTester();
	//CardsDriver::CardsTester();
}

