#pragma once
#include<list>
using namespace std;

class GameObservers
{
public:
	virtual void update() = 0;
	~GameObservers();
protected:
	GameObservers();
};

class AttachObserver : public GameObservers 
{
public:
	AttachObserver();
	~AttachObserver();
	void update() override;
private:
	Player * subject;
};

class Subject : public GameObservers {

public:
	Subject();
	~Subject();

	void attach(GameObservers *);
	void detach(GameObservers *);
	void notify();

private:
	list<GameObservers*>* _observers;
};

class GameObservers
{
public:
	GameObservers();
	~GameObservers();
};

