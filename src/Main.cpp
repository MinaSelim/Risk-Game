#include <iostream>
#include "GameEngine.h"
#include "PlayerDriver.h"

int main()
{
	GameEngine e;
	//e.startGame();
	//e.setupGame();
	e.assignTheWorldToAPlayer();
	//e.eliminatePlayer();
	e.mainLoop();
	
	//PlayerDriver::PlayerTester();
}

