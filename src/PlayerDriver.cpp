
#pragma once 
#include <new>
#include "PlayerDriver.h"

void PlayerDriver::PlayerTester()
{
	Player* player = new Player();
	player->attack();
	player->fortify();
	player->reinforce();

	delete player;
}
