#include "GameEngine.h"
#include "MapLoader.h"
#include "Utility.h"
#include <string>
#include <cstdlib>
#include <sstream>
#include <thread>
#include <chrono>
#include <fstream>
#include "ErrorCodes.h"


using namespace std;

GameEngine::GameEngine()
	: listOfPlayers(new vector<Player*>())
{
	cout << "Welcome To the Risk Game" << endl;

	int gameType;
	do {
		cout << "Press 1 for single game, 2 for tournament";
		cin >> gameType;
	} while (gameType < 0 || gameType > 2);

	int numOfPlayers = selectPlayersNumber(gameType);

	if (gameType == 1) {
		chooseMap();
		deck = new Deck(map->getNumberOfCountriesInMap());
		cout << "The deck consists of: " << deck->getSize() << " cards" << endl;
		choosePlayerType(numOfPlayers, gameType);
	}


	eliminateObs = new EliminationObserver(this);
	winnerObs = new WinnerObserver(this);
	conquerObs = new ConquerObserver(this);
	attackObs = new AttackObserver(this);
	reinforceObs = new ReinforceObserver(this);
	fortifyObs = new FortifyObserver(this);

	if (gameType == 2) {
		int numberOfGames = chooseNumberOfGames();
		numberOfTurns = chooseNumberOfTurns();
		startTournament(numberOfGames, numOfPlayers);
	}

}


void GameEngine::chooseMap() // Function that lets the users select a map
{
	std::vector<string> mapsNames = FileIO::readDirectory(MAPS_DIRECTORY);
	std::cout << "Select a map: \n";
	Utility::displayItemsInAVector(mapsNames);
	int choice = -1;
	do {
		if (choice != -1) {
			cin.clear();
			cin.ignore(300, '\n');
		}

		std::cout << "Select a valid number: \n";
		cin >> choice;
	} while (cin.fail() || choice < 0 || choice >= (int)(mapsNames.size()));

	try {

		bool verify = FileIO::verifyTypeOfMapFile(MAPS_DIRECTORY + mapsNames[choice]);
		if (!verify) {
			ConquestMapReader * coquestMapReader = new ConquestMapReader();
			MapLoader* mapLoader = new MapLoaderAdapter(coquestMapReader);
			map = mapLoader->loadMap(MAPS_DIRECTORY + mapsNames[choice]);
			delete mapLoader;
		}

		else {
			MapLoader mapLoader;
			map = mapLoader.loadMap(MAPS_DIRECTORY + mapsNames[choice]);
		}

	}
	catch (int /*i*/)
	{
		cout << "You selected an Invalid map, please try a different map"; // It means the map in invalid
		chooseMap();
	}

}

bool GameEngine::gameWon()
{
	auto countryGraph = map->getCountriesGraph();

	auto firstNode = map->getFirstNode();
	for (unsigned int i = 1; i < countryGraph.size(); i++) //Checks if one player owns all the countries
	{
		if (countryGraph[i]->playerInfo->getPlayer()->getPlayerName().compare(firstNode->playerInfo->getPlayer()->getPlayerName()))
		{
			return false;
		}
	}

	return true;
}


int GameEngine::selectPlayersNumber(int gameType) //Selection for number of players
{
	int singleGame[2];
	if (gameType == 1) {
		singleGame[0] = 2;
		singleGame[1] = 6;
	}
	else {
		singleGame[0] = 2;
		singleGame[1] = 4;
	}
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
	} while (userInput < singleGame[0] || userInput > singleGame[1]);
	return userInput;
}

// 1 for single player, 2 for tournament
void GameEngine::startGame(int gameType = 1) //Starts the game
{
	setupGame();
	mainLoop(gameType);
}

void GameEngine::assignTheWorldToAPlayer()// A testing Function that assigns the entire world to a player
{
	auto countryGraphShallowCopy = map->getCountriesGraph();
	for (unsigned int i = 0; i < countryGraphShallowCopy.size(); i++)
	{
		(*listOfPlayers)[0]->addCountryOwnerShip(countryGraphShallowCopy[i], 1);
	}
}

// A testing Function that assigns countries to 2 players, then reassigns 1 players countries to another, trying to trigger elimination observer
void GameEngine::eliminatePlayer()
{
	auto countryGraphShallowCopy = map->getCountriesGraph();

	//set up situation for player 0 to eliminate player 1
	for (unsigned int i = 0; i < countryGraphShallowCopy.size() - 1; i++)
	{
		(*listOfPlayers)[0]->addCountryOwnerShip(countryGraphShallowCopy[i], 2);
	}
	(*listOfPlayers)[1]->addCountryOwnerShip(countryGraphShallowCopy[countryGraphShallowCopy.size()], 1);
}

void GameEngine::setupGame()
{
	int currentPlayer = rand() % listOfPlayers->size();
	auto countryGraphShallowCopy = map->getCountriesGraph();

	//This loop randomly assigns countries to players.
	while (countryGraphShallowCopy.size())
	{
		int randomCountry = rand() % countryGraphShallowCopy.size();
		(*listOfPlayers)[currentPlayer]->addCountryOwnerShip(countryGraphShallowCopy[randomCountry], 1);

		countryGraphShallowCopy.erase(countryGraphShallowCopy.begin() + randomCountry);

		currentPlayer = (++currentPlayer) % listOfPlayers->size();
	}

	//This prints the new values
	for (unsigned int i = 0; i < listOfPlayers->size(); i++)
	{
		cout << "player " << i << endl;
		(*listOfPlayers)[i]->printListOfCountries();
		cout << endl;
	}

	const int MAX_INITIAL_NUMBER_OF_TROOPS = 40;
	int troopsLeftToPlace = MAX_INITIAL_NUMBER_OF_TROOPS - ((listOfPlayers->size() - 2) * 5); //formula to calculate number of initial troops

//	troopsLeftToPlace = 5;

	while (troopsLeftToPlace > 0)
	{
		std::cout << "Troops left to place : " << troopsLeftToPlace << endl;
		for (unsigned int i = 0; i < listOfPlayers->size(); i++)
		{
			(*listOfPlayers)[i]->setNumberOfArmies(1);
			(*listOfPlayers)[i]->placeArmiesOnCountries();
		}

		troopsLeftToPlace--;
	}
}

void GameEngine::mainLoop(int gameType = 1) // main game loop, runs until the game ends
{
	int counter = 0;
	int currentPlayer = rand() % listOfPlayers->size();
	while (true)
	{
		counter++;
		system("CLS");
		stringstream currentPlayerAsStream;
		currentPlayerAsStream << currentPlayer;
		std::string currentPlayerAsString;
		currentPlayerAsStream >> currentPlayerAsString;

		std::string phase = "reinforce ";
		notify(phase.append(currentPlayerAsString));
		(*listOfPlayers)[currentPlayer]->reinforce();
		system("CLS");

		phase = "attack ";
		int countriesBeforeAttack = (*listOfPlayers)[currentPlayer]->getNumberPlayerCountries();
		notify(phase.append(currentPlayerAsString));
		(*listOfPlayers)[currentPlayer]->attack();
		int countriesAfterAttack = (*listOfPlayers)[currentPlayer]->getNumberPlayerCountries();

		if (countriesAfterAttack > countriesBeforeAttack)
		{
			(*listOfPlayers)[currentPlayer]->getHandOfCards()->pickACard(deck);
			system("CLS");
			phase = "conquer ";
			notify(phase.append(currentPlayerAsString));
			this_thread::sleep_for(chrono::milliseconds(6000));
		}

		system("CLS");
		phase = "fortify ";
		notify(phase.append(currentPlayerAsString));
		(*listOfPlayers)[currentPlayer]->fortify();

		//remove player from list when they are eliminated
		int playerCountries = (*listOfPlayers)[currentPlayer]->getNumberPlayerCountries();
		if (playerCountries == 0)
		{
			system("CLS");
			phase = "eliminate ";
			notify(phase.append(currentPlayerAsString));
			this_thread::sleep_for(chrono::milliseconds(6000));
		}

		if (gameWon())
		{
			system("CLS");
			phase = "win ";
			notify(phase.append(currentPlayerAsString));
			break;
		}

		if (gameType == 2 && numberOfTurns == counter)
		{
			cout << "A draw occured";
			break;
		}


		(*listOfPlayers)[currentPlayer]->printListOfCountries();
		currentPlayer = (++currentPlayer) % listOfPlayers->size();
	}

	string enumType;
	switch (*(*listOfPlayers)[currentPlayer]->currentBehaviourEnum) 
	{
	case BehaviourEnum::Aggresive:
		enumType = "Aggresive";
		break;
	case BehaviourEnum::Benevolent:
		enumType = "Benevolent";
		break;
	case BehaviourEnum::Human:
		enumType = "Human";
		break;
	}
	finalTable->push_back(enumType);

	cout << "The winner is player " << (*listOfPlayers)[currentPlayer]->getPlayerName();
	system("pause");

}

GameEngine::~GameEngine()
{
	delete map;
	for (unsigned int i = 0; i < listOfPlayers->size(); i++)
	{
		delete (*listOfPlayers)[i];
	}
	delete listOfPlayers;

	delete eliminateObs;
	delete winnerObs;
	delete reinforceObs;
	delete fortifyObs;
	delete attackObs;
	delete conquerObs;

	eliminateObs = nullptr;
	winnerObs = nullptr;
	reinforceObs = nullptr;
	fortifyObs = nullptr;
	attackObs = nullptr;
	conquerObs = nullptr;

}

bool FileIO::checkUpFileType(std::ifstream & inputStream, std::string lineContent)
{
	std::streamsize  count = 400;
	char nextLine[400];

	while (!inputStream.eof())
	{
		inputStream.getline(nextLine, count);

		if (!lineContent.compare(nextLine))
		{
			return true;
		}
		if (inputStream.eof()) {
			return false;
		}
	}
}

bool FileIO::verifyTypeOfMapFile(std::string fileName)
{
	if (!Utility::fileExist(fileName))
	{
		throw FILE_DOES_NOT_EXIST;
	}

	std::ifstream mapFile(fileName);
	bool found = FileIO::checkUpFileType(mapFile, "[borders]");
	if (found) {
		return true;
	}
	return false;
}

std::vector<string> FileIO::readDirectory(const std::string& directoryName)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__) // This is windows only Compatible code
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
	//The #else contains untested code for Linux
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
void GameEngine::update(string s) {}

// TODO: Uncomment strategy codes
void GameEngine::choosePlayerType(int numOfPlayers, int gameType) // Function that lets the users select a map
{
	for (int i = 0; i < numOfPlayers; i++)
	{
		std::vector<string> playerTypes;
		if (gameType == 1) {
			playerTypes = { "Aggressive","Benevolent", "Human" };
		}
		else {
			playerTypes = { "Aggressive","Benevolent", "Random", "Cheater" };
		}

		std::cout << "Select the type of the player " << i << " \n";
		Utility::displayItemsInAVector(playerTypes);
		int choice = -1;
		do {
			cin.clear();
			cin.ignore(300, '\n');
			std::cout << "Select a valid number: \n";
			cin >> choice;
		} while (cin.fail() || choice < 0 || choice >= (int)(playerTypes.size()));

		if (choice == 0) {
			listOfPlayers->push_back(new Player(to_string(i), map, BehaviourEnum::Aggresive));
		}
		else if (choice == 1) {
			listOfPlayers->push_back(new Player(to_string(i), map, BehaviourEnum::Benevolent));
		}
		else if (choice == 3 && gameType == 1) {
			listOfPlayers->push_back(new Player(to_string(i), map, BehaviourEnum::Human));
		}
		else if (choice == 3 && gameType == 2) {
			//listOfPlayers->push_back(new Player(to_string(i), map, BehaviourEnum::Random));
		}
		else if (choice == 4) {
			//listOfPlayers->push_back(new Player(to_string(i), map, BehaviourEnum::Cheater));
		}
	}
}

int GameEngine::chooseNumberOfGames() {
	std::cout << "Select number of games" << " \n";
	int choice;
	do {
		cin.clear();
		cin.ignore(300, '\n');
		std::cout << "Select a valid number: \n";
		cin >> choice;
	} while (cin.fail() || choice < 1 || choice > 5);
	return choice;
}

int GameEngine::chooseNumberOfTurns() {
	std::cout << "Select number of turns" << " \n";
	int choice;
	do {
		cin.clear();
		cin.ignore(300, '\n');
		std::cout << "Select a valid number: \n";
		cin >> choice;
	} while (cin.fail() || choice < 10 || choice > 50);
	return choice;
}

void GameEngine::startTournament(int numberOfGames, int numberOfPlayers) {
	std::cout << "Select number of maps" << " \n";
	int choice;
	finalTable = new vector <string>;
	do {
		cin.clear();
		cin.ignore(300, '\n');
		std::cout << "Select a valid number: \n";
		cin >> choice;
	} while (cin.fail() || choice < 1 || choice > 5);

	std::vector<Map> * mapVector = new vector<Map>;
	while (mapVector->size() < choice) {
		chooseMap();
		deck = new Deck(map->getNumberOfCountriesInMap());
		cout << "The deck consists of: " << deck->getSize() << " cards" << endl;
		mapVector->push_back(*map);
	}

	bool playersChosen = false;
	for (int i = 0; i < numberOfGames; i++) {
		for (unsigned i = 0; i < mapVector->size(); i++) {
			*map = mapVector->at(i);
			if (!playersChosen)
			{
				choosePlayerType(numberOfPlayers, 2);
				playersChosen = true;
			}
			else
			{
				resetPlayers();
			}
			startGame(2);
			//reset players after each game
			//resetPlayers();
		}
		
	}

	for (unsigned int i = 0; i < finalTable->size(); i++) {
		std::cout << finalTable->at(i) << endl;
	}
}


void GameEngine::resetMap() 
{
	
}

void GameEngine::resetPlayers()
{
	vector<Player*>  newPlayers;

	for (unsigned int i = 0; i < listOfPlayers->size(); i++)
	{
		string playerName = (*listOfPlayers)[i]->getPlayerName();
		BehaviourEnum strategy = (*listOfPlayers)[i]->getBehaviourEnum();
		delete (*listOfPlayers)[i];
		(*listOfPlayers)[i] = nullptr;
		Player * p = new Player(playerName, this->map, strategy);
		newPlayers.push_back(p);
		
	}

	*listOfPlayers = newPlayers;



}

vector <Player*> GameEngine::getListOfPlayers()
{
	return *listOfPlayers;
}

int GameEngine::getNumberOfPlayers()
{
	return listOfPlayers->size();
}


