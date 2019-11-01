#include "Map.h"
#include "MapDriver.h"
#include "MapLoader.h"
#include <iostream>


void MapDriver::MapTester() {

	Map * map = MapLoader::loadMap("./maps/worldNew.map");

	Map * map2 = new Map(*map);

	delete map;

	try {
		map = MapLoader::loadMap("./maps/InvalidWorld.map");
		delete map;
	}
	catch (int a)
	{
		std::cout << a;
	}

	try {
		map = MapLoader::loadMap("./maps/InterconnectedInvalorld.map");
		delete map;
	}
	catch (int a)
	{
		std::cout << a;
	}

	delete map2;
}
