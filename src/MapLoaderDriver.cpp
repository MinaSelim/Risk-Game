#include "Map.h"
#include "MapLoaderDriver.h"
#include "MapLoader.h"
#include <iostream>

void MapLoaderDriver::MapTester() {

	Map * map = MapLoader::loadMap("./worldNew.map");

	delete map;

	try {
		map = MapLoader::loadMap("./InvalidWorld.map");
		delete map;
	}
	catch (int a)
	{
		std::cout << a;
	}

	try {
		map = MapLoader::loadMap("./InterconnectedInvalidWorld.map");
		delete map;
	}
	catch (int a)
	{
		std::cout << a;
	}
}
