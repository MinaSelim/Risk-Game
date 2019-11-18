
#include "GameObservers.h"
#include "GameEngine.h"
#include <iostream>
#include "Player.h"
using namespace std;

GameObservers::GameObservers()
{
}


GameObservers::~GameObservers()
{
}

Subject::Subject() {
	_observers = new list<GameObservers*>;
}
Subject::~Subject() {
	delete _observers;
}

void Subject::attach(GameObservers* o) {
	_observers->push_back(o);
};

void Subject::detach(GameObservers* o) {
	_observers->remove(o);
};

void Subject::notify(string type) {
	list<GameObservers *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->update(type);
};


AttackObserver::AttackObserver(GameEngine* p)
{
	subject = p;
	subject->attach(this);
}

AttackObserver ::~AttackObserver()
{
	subject->detach(this);
}

FortifyObserver::FortifyObserver(GameEngine* p)
{
	subject = p;
	subject->attach(this);
}

FortifyObserver ::~FortifyObserver()
{
	subject->detach(this);
}

ReinforceObserver::ReinforceObserver(GameEngine* p)
{
	subject = p;
	subject->attach(this);
}

ReinforceObserver ::~ReinforceObserver()
{
	subject->detach(this);
}

void AttackObserver::update(string type)
{
	std::string delimiter = " ";
	std::string phase;
	std::string currentPlayer;

	char* cstr = const_cast<char*>(type.c_str());
	char* token;
	char *next = NULL;
	token = strtok_s(cstr, delimiter.c_str(), &next);
	phase = token;
	token = strtok_s(nullptr, delimiter.c_str(), &next);
	currentPlayer = token;

	if (phase.compare("attack") == 0) {
		vector <Player*> list = subject->getListOfPlayers();
		auto g = getSubject();
		printMapOwnership(g);
		cout << endl << endl << "Player " << currentPlayer << ":Attack phase" << endl << endl;
	}
}


void FortifyObserver::update(string type)
{
	std::string delimiter = " ";
	std::string phase;
	std::string currentPlayer;

	char* cstr = const_cast<char*>(type.c_str());
	char* token;
	char *next = NULL;
	token = strtok_s(cstr, delimiter.c_str(), &next);
	phase = token;
	token = strtok_s(nullptr, delimiter.c_str(), &next);
	currentPlayer = token;

	if (phase.compare("fortify") == 0) {
		GameEngine * p = getSubject();
		printMapOwnership(p);
		cout << endl << endl << "Player " << currentPlayer << ": Fortify phase" << endl << endl;
	}
}

void ReinforceObserver::update(string type)
{
	std::string delimiter = " ";
	std::string phase;
	std::string currentPlayer;

	char* cstr = const_cast<char*>(type.c_str());
	char* token;
	char *next = NULL;
	token = strtok_s(cstr, delimiter.c_str(), &next);
	phase = token;
	token = strtok_s(nullptr, delimiter.c_str(), &next);
	currentPlayer = token;

	if (phase.compare("reinforce") == 0) {
		GameEngine * p = getSubject();
		printMapOwnership(p);
		cout << endl << endl << "Player " << currentPlayer << ":Reinforce phase" << endl << endl;
	}
}

ConquerObserver::ConquerObserver(GameEngine * g)
{
	subject = g;
	subject->attach(this);
}

ConquerObserver::~ConquerObserver()
{
	subject->detach(this);
}

EliminationObserver::EliminationObserver(GameEngine* g)
{
	subject = g;
	subject->attach(this);
}

EliminationObserver::~EliminationObserver()
{
	subject->detach(this);
}

WinnerObserver::WinnerObserver(GameEngine* g)
{
	subject = g;
	subject->attach(this);
}

WinnerObserver ::~WinnerObserver()
{
	subject->detach(this);
}


void ConquerObserver::update(string type)
{
	std::string delimiter = " ";
	std::string phase;
	std::string currentPlayer;

	char* cstr = const_cast<char*>(type.c_str());
	char* token;
	char *next = NULL;
	token = strtok_s(cstr, delimiter.c_str(), &next);
	phase = token;
	token = strtok_s(nullptr, delimiter.c_str(), &next);
	currentPlayer = token;

	if (phase.compare("conquer") == 0) {
		GameEngine * p = getSubject();
		printMapOwnership(p);
		cout << endl << endl << "Player "<< currentPlayer << " has conquered some country/ies." << endl << endl;
		
	}
}


void EliminationObserver::update(string type)
{	
	std::string delimiter = " ";
	std::string phase;
	std::string currentPlayer;

	char* cstr = const_cast<char*>(type.c_str());
	char* token;
	char *next = NULL;
	token = strtok_s(cstr, delimiter.c_str(), &next);
	phase = token;
	token = strtok_s(nullptr, delimiter.c_str(), &next);
	currentPlayer = token;

	if (phase.compare("eliminate") == 0) {
		GameEngine * g = getSubject();
		printMapOwnership(g);
		cout << "Player " << currentPlayer << " has eliminated another Player." << endl;

	}
}

void WinnerObserver::update(string type)
{
	std::string delimiter = " ";
	std::string phase;
	std::string currentPlayer;

	char* cstr = const_cast<char*>(type.c_str());
	char* token;
	char *next = NULL;
	token = strtok_s(cstr, delimiter.c_str(), &next);
	phase = token;
	token = strtok_s(nullptr, delimiter.c_str(), &next);
	currentPlayer = token;

	if (phase.compare("win") == 0) {
		GameEngine * g = getSubject();
		printMapOwnership(g);
		cout << endl << endl << "Player " << currentPlayer << " has won the game! Congratulations!" << endl << endl;
		
	}
}

void GameObservers::printMapOwnership(GameEngine * g)
{	
	vector <Player*>  players = g->getListOfPlayers();
	cout << endl;
	cout << "***Player World Domination View***" << endl;
	for (unsigned int i = 0; i < players.size(); i++)
	{
		Player * p = new Player();
		p = players[i];
		int playerCountries = p->getNumberPlayerCountries();
		int mapCountries = p->getNumberTotalCountries();
		double percentageOwnership = 100 * (double)playerCountries / (double)mapCountries;
		cout << "Player " << p->getPlayerName() << " has " << percentageOwnership << "% of countries on the Map." << endl;
		// delete p;
	}
	
	cout << endl;
}

