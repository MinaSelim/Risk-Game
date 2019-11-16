#pragma once
#include<list>
using namespace std;
class Player;
class GameEngine;

class GameObservers
{
public:
	virtual void update(string) = 0;
	~GameObservers();
	void printMapOwnership(GameEngine * g);
protected:
	GameObservers();
};

class Subject : public GameObservers {

public:
	Subject();
	~Subject();
	void attach(GameObservers *);
	void detach(GameObservers *);
	void notify(string);

private:
	list<GameObservers*>* _observers;
};


class AttackObserver : public GameObservers {
public:
	AttackObserver(Player* p);
	~AttackObserver();
	void update(string) override;
	Player* getSubject() const { return subject; };
private:
	Player * subject;
};

class FortifyObserver : public GameObservers {
public:
	FortifyObserver(Player* p);
	~FortifyObserver();
	void update(string) override;
	Player* getSubject() const { return subject; };
private:
	Player * subject;
};

class ReinforceObserver : public GameObservers {
public:
	ReinforceObserver(Player* p);
	~ReinforceObserver();
	void update(string) override;
	Player * getSubject() const { return subject; };
private:
	Player * subject;
};

class ConquerObserver : public GameObservers {
public:
	ConquerObserver(Player * p);
	~ConquerObserver();
	void update(string) override;
	Player * getSubject() const { return subject; };
private:
	Player * subject;
};

class EliminationObserver : public GameObservers {
public:
	EliminationObserver(GameEngine * g);
	~EliminationObserver();
	void update(string) override;
	GameEngine * getSubject() const { return subject; };
private:
	GameEngine * subject;
};

class WinnerObserver : public GameObservers {
public:
	WinnerObserver(GameEngine * g);
	~WinnerObserver();
	void update(string) override;
	GameEngine * getSubject() const { return subject; };
private:
	GameEngine * subject;
};

