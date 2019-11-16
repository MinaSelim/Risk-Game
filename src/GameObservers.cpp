
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


AttackObserver::AttackObserver(Player* p)
{
	subject = p;
	subject->attach(this);
}

AttackObserver ::~AttackObserver()
{
	subject->detach(this);
}

FortifyObserver::FortifyObserver(Player* p)
{
	subject = p;
	subject->attach(this);
}

FortifyObserver ::~FortifyObserver()
{
	subject->detach(this);
}

ReinforceObserver::ReinforceObserver(Player* p)
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
	if (type.compare("attack") == 0) {
		Player * p = getSubject();
		cout << endl << endl << "Player " << p->getPlayerName() << ":Attack phase" << endl << endl;
	}
}


void FortifyObserver::update(string type)
{
	if (type.compare("fortify") == 0) {
		Player * p = getSubject();
		cout << endl << endl << "Player " << p->getPlayerName() << ": Fortify phase" << endl << endl;
	}
}

void ReinforceObserver::update(string type)
{
	if (type.compare("reinforce") == 0) {
		system("CLS");
		Player * p = getSubject();
		cout << endl << endl << "Player " << p->getPlayerName() << ":Reinforce phase" << endl << endl;
	}
}

ConquerObserver::ConquerObserver(Player * p)
{
	subject = p;
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
	if (type.compare("conquer") == 0) {
		Player * p = getSubject();
		//printMapOwnership(p);
		cout << endl << endl << "Player " << p->getPlayerName() << " has conquered a country." << endl << endl;
		
	}
}


void EliminationObserver::update(string type)
{
	if (type.compare("eliminate") == 0) {
		GameEngine * p = getSubject();
		//printMapOwnership(p);
		cout << endl << endl << "Player " << " has been Eliminated." << endl << endl;
		
	}
}

void WinnerObserver::update(string type)
{
	if (type.compare("win") == 0) {
		GameEngine * g = getSubject();
		//printMapOwnership(g);
		cout << endl << endl << "Player "  << " has won the game! Congratulations!" << endl << endl;
		
	}
}

void GameObservers::printMapOwnership(GameEngine * g)
{
	for (int i = 0; i < g->getListOfPlayers; i++)
	{
		Player * p = g->getListOfPlayers[i];
		int playerCountries = p->numberPlayerCountries();
		int mapCountries = p->numberTotalCountries();
		double percentageOwnership = 100 * (double)playerCountries / (double)mapCountries;
		cout << endl << endl << "Player " << p->getPlayerName() << " has " << percentageOwnership << "% of countries on the Map." << endl << endl;
	}
	
	
}