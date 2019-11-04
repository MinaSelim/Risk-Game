#include "GameEngine.h"
#include "MapLoader.h"
#include <string>
#include <cstdlib>

using namespace std;

GameEngine::GameEngine() 
	: listOfPlayers(new vector<Player*>())
{
	cout << "Welcome To the Risk Game" << endl;
	chooseMap();
	int numOfPlayers = selectPlayersNumber();


	for (int i = 0; i < numOfPlayers; i++) 
	{
		listOfPlayers->push_back(new Player(to_string(i)));
	}

	Deck* deck = new Deck(map->getNumberOfCountriesInMap());
	cout << "The deck consists of: " << deck->getSize() << " cards" << endl;

}

void GameEngine::chooseMap()
{
	std::vector<string> mapsNames = FileIO::readDirectory(MAPS_DIRECTORY);
	std::cout << "Select a map: \n";
	Utility::displayItemsInAVector(mapsNames);
	int choice = -1;
	do {
		std::cout << "Select a valid number: \n";
		cin >> choice;	
	} while (cin.fail() || choice < 0 || choice >= (int)(mapsNames.size()));

	try {
		map = MapLoader::loadMap( MAPS_DIRECTORY + mapsNames[choice]);
	}
	catch (int /*i*/)
	{
		cout << "You selected an Invalid map, please try a different map";
		chooseMap();
	}

}

bool GameEngine::gameWon()
{
	auto countryGraph = map->getCountriesGraph();

	auto firstNode = map->getFirstNode();
	for (unsigned int i = 1; i < countryGraph.size(); i++)
	{
		if (countryGraph[i]->playerInfo->getPlayer()->getPlayerName().compare(firstNode->playerInfo->getPlayer()->getPlayerName()))
		{
			return false;
		}
	}

	return true;
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

void GameEngine::startGame()
{
	setupGame();
	mainLoop();
}


void GameEngine::setupGame()
{
	const int MAX_INITIAL_NUMBER_OF_TROOPS = 40;
	int initialNumberOfTroops = MAX_INITIAL_NUMBER_OF_TROOPS - ((listOfPlayers->size() - 2) * 5);
	for (unsigned int i = 0; i < listOfPlayers->size(); i++)
	{
		(*listOfPlayers)[i]->setNumberOfArmies(initialNumberOfTroops);
	}

	int currentPlayer = rand() % listOfPlayers->size();
	auto countryGraphShallowCopy = map->getCountriesGraph();

	while (countryGraphShallowCopy.size())
	{
		int randomCountry = rand() % countryGraphShallowCopy.size();
		(*listOfPlayers)[currentPlayer]->addCountryOwnerShip(countryGraphShallowCopy[randomCountry], 2);

		countryGraphShallowCopy.erase(countryGraphShallowCopy.begin() + randomCountry);

		currentPlayer = (++currentPlayer) % listOfPlayers->size();
	}

	for (unsigned int i = 0; i < listOfPlayers->size(); i++)
	{
		cout << "player " << i << endl;
		(*listOfPlayers)[i]->printListOfCountries();
	}

}

void GameEngine::mainLoop()
{
	int currentPlayer = rand() % listOfPlayers->size();
	while (true)
	{
		(*listOfPlayers)[currentPlayer]->reinforce();
		(*listOfPlayers)[currentPlayer]->attack();
		(*listOfPlayers)[currentPlayer]->fortify();
		if (gameWon())
		{
			break;
		}
		currentPlayer = (++currentPlayer) % listOfPlayers->size();
	}

	cout << "The winner is " << (*listOfPlayers)[currentPlayer]->getPlayerName();
	
}

std::vector<string> FileIO::readDirectory(const std::string& directoryName)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	std::vector<string> directoryVector;
	std::string pattern(directoryName);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			if (data.nFileSizeLow != 0)
			{
				directoryVector.push_back(data.cFileName);
			}
			
		} while (FindNextFile(hFind, &data) != 0);
FindClose(hFind);
	}
#else
	std::vector<string> directoryVector;
	DIR* dirp = opendir(directoryName.c_str());
	struct dirent * dp;
	while ((dp = readdir(dirp)) != NULL) {
		directoryVector.push_back(dp->d_name);
	}
	closedir(dirp);
#endif
	return directoryVector;
}

