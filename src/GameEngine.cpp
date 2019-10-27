#include "GameEngine.h"

using namespace std;

GameEngine::GameEngine() : listOfPlayers(new vector<Player*>())
{
	cout << "Welcome To the Risk Game" << endl;
	chooseMap();
	int numOfPlayers = selectPlayersNumber();

	//We need to create the map here :) 

	for (int i = 0; i < numOfPlayers; i++) 
	{
		listOfPlayers->push_back(new Player());
	}

	//Replace 45 by the number of countries later:
	Deck* deck = new Deck(45);
	cout << "The deck consists of: " << deck->getSize() << " cards" << endl;

}

void GameEngine::chooseMap()
{
	userInput();
}

bool GameEngine::checkIfFileExist(const string& path_to_file)
{
	ifstream readFile;
	readFile.open(path_to_file);
	if (!readFile.is_open()) {
		return false;
	}
	else {
		readFile.close();
		return true;
	}
}

string GameEngine::userInput()
{
	string userInput = "";
	bool fileExist = false;
	
	do {
		cout << "Please type the map's file name (Select one of the mentioned below):";
		cin >> userInput;
		//showListOfMapFiles()
		fileExist = checkIfFileExist(userInput);
	} while (!fileExist);
		
	return userInput;
}

void GameEngine::showListOfMapFiles()
{
}


int GameEngine::selectPlayersNumber()
{
	int userInput = 0;
	do {
		cout << "Please insert the number of Players: ";
		cin >> userInput;
		while (!cin)
		{
			cout << "That was not an integer! Please enter an integer (2-6): ";
			cin.clear();
			cin.ignore();
			cin >> userInput;
		}
	} while (userInput < 2  || userInput > 6);
	return userInput;
}
