#include <iostream>
#include "GameEngine.h"
#include "PlayerDriver.h"
#include "MapLoader.h"
int main()
{
	ConquestMapReader reader;
	reader.conquestLoadMap("C:\\Program Files (x86)\\Conquest\\Maps\\Atlantis.map");
	//GameEngine e;
	//e.startGame();
	//e.setupGame();
	//e.assignTheWorldToAPlayer();
	//e.mainLoop();

	//PlayerDriver::PlayerTester();
}

