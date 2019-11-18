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
	AttackObserver(GameEngine* p);
	~AttackObserver();
	void update(string) override;
	GameEngine* getSubject() const { return subject; };
private:
	GameEngine * subject;
};

class FortifyObserver : public GameObservers {
public:
	FortifyObserver(GameEngine* p);
	~FortifyObserver();
	void update(string) override;
	GameEngine* getSubject() const { return subject; };
private:
	GameEngine * subject;
};

class ReinforceObserver : public GameObservers {
public:
	ReinforceObserver(GameEngine* p);
	~ReinforceObserver();
	void update(string) override;
	GameEngine* getSubject() const { return subject; };
private:
	GameEngine * subject;
};

class ConquerObserver : public GameObservers {
public:
	ConquerObserver(GameEngine* p);
	~ConquerObserver();
	void update(string) override;
	GameEngine* getSubject() const { return subject; };
private:
	GameEngine * subject;
};

class EliminationObserver : public GameObservers {
public:
	EliminationObserver(GameEngine* g);
	~EliminationObserver();
	void update(string) override;
	GameEngine* getSubject() const { return subject; };
private:
	GameEngine * subject;
};

class WinnerObserver : public GameObservers {
public:
	WinnerObserver(GameEngine* g);
	~WinnerObserver();
	void update(string) override;
	GameEngine* getSubject() const { return subject; };
private:
	GameEngine * subject;
};

