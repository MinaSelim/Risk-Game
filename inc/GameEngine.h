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
#include "PlayerStrategies.h"
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
	Deck * deck;
	vector <string> * finalTable;

public:
	GameEngine();
	bool eliminatedPlayer();
	bool gameWon();
	void startGame(int gameType);
	void assignTheWorldToAPlayer();
	void eliminatePlayer();
	void setupGame();
	void mainLoop(int gameType);
	vector <Player*> getListOfPlayers();
	int getNumberOfPlayers();
	~GameEngine();
	void choosePlayerType(int numOfPlayers, int gameType);
	void update(string s) override;
private:
	void chooseMap();
	int chooseNumberOfGames();
	int chooseNumberOfTurns();
	void changingPlayerBehviour(Player & player);
	void startTournament(int numberOfGames, int numberOfPlayers);
	void resetMap(std::vector<Map> * mapVector);
	void resetPlayers();
	int selectPlayersNumber(int gameType);
	EliminationObserver * eliminateObs;
	WinnerObserver * winnerObs;
	ConquerObserver * conquerObs;
	AttackObserver * attackObs;
	ReinforceObserver * reinforceObs;
	FortifyObserver * fortifyObs;
	int numberOfTurns;
};

namespace FileIO
{
	bool verifyTypeOfMapFile(std::string fileName);
	std::vector<string> readDirectory(const std::string& directoryName);
	bool checkUpFileType(std::ifstream & inputStream, std::string lineContent);
}
