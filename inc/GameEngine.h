#pragma once
#include <string>
#include <vector>
#include "Player.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "Cards.h"
#include <sys/types.h>
#include "GameObservers.h"
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#else
#include <dirent.h>
#endif

#define MAPS_DIRECTORY "./maps/"

using namespace std;

class GameEngine : public Subject {
private:
	vector <Player*> * listOfPlayers;
	Map * map;

public:
	GameEngine();
	bool gameWon();
	void startGame();
	void assignTheWorldToAPlayer();
	void setupGame();
	void mainLoop();
	vector <Player*> getListOfPlayers();
	~GameEngine();
	void update(string s) override;
private:
	void chooseMap();
	int selectPlayersNumber();
};

namespace FileIO
{
	std::vector<string> readDirectory(const std::string& directoryName);
}
