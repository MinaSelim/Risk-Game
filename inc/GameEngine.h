#pragma once
#include <string>
#include <vector>
#include "Player.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "Cards.h"

using namespace std;

class GameEngine {
private:
	vector <Player*> * listOfPlayers;

public:
	GameEngine();
	void chooseMap();
	bool checkIfFileExist(const string& path_to_file);
	string userInput();
	void showListOfMapFiles();
	int selectPlayersNumber(); 
		
};
