#pragma once
#include <string>
#include <vector>
#include "Player.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "Cards.h"
#include <sys/types.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#else
#include <dirent.h>
#endif

#define MAPS_DIRECTORY "./maps/"

using namespace std;

class GameEngine {
private:
	vector <Player*> * listOfPlayers;
	Map * map;
	Deck * deck;

public:
	GameEngine();
	bool gameWon();
	void startGame();
	void assignTheWorldToAPlayer();
	void setupGame();
	void mainLoop();
	~GameEngine();
private:
	void chooseMap();
	int selectPlayersNumber();
};

namespace FileIO
{
	std::vector<string> readDirectory(const std::string& directoryName);
}
