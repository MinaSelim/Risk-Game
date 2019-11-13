#pragma once
#include<list>
using namespace std;
class Player;

class GameObservers
{
public:
	virtual void update(string) = 0;
	~GameObservers();
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
