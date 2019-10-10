#include "Map.h"
#include "MapDriver.h"
#include "MapLoader.h"
#include <iostream>

void MapDriver::MapTester() {

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
	

}