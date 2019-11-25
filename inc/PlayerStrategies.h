#pragma once
#include "Map.h"


class Player;

class Behaviour
{
protected:
	Player * player;
public:
	virtual void placeArmiesDuringReinforce() = 0;
	virtual void attackEnemies() = 0;
	virtual void fortify() = 0;
	virtual int getAttackRoll(int attackArmiesOnNode);
	virtual int getDefenseRoll(int defenseArmiesOnNode);
	virtual int getNumberOfTroopsToTransfer(int attackerArmies);
	
};

class  HumanBehaviour : public Behaviour {
public:
	virtual void placeArmiesDuringReinforce();
	virtual void attackEnemies();
	virtual void fortify();
	virtual int getAttackRoll(int attackArmiesOnNode);
	virtual int getDefenseRoll(int defenseArmiesOnNode);
	virtual int getNumberOfTroopsToTransfer(int attackerArmies);
	HumanBehaviour(Player * player);
};

class  AggresiveAIBehaviour : public Behaviour {
public:
	virtual void placeArmiesDuringReinforce();
	virtual void attackEnemies();
	virtual void fortify();
	AggresiveAIBehaviour(Player * player);
private:
	CountryNode * findCountryNodeWithHighestAmountOfTroupsThatCanAttack();
	CountryNode * findCountryNodeWithHighestAmountOfTroupsThatCannotAttack();
	bool nodeHasEnemies(CountryNode * node);
};

class  BenevolentAIBehaviour : public Behaviour {
public:
	virtual void placeArmiesDuringReinforce();
	virtual void attackEnemies();
	virtual void fortify();
	BenevolentAIBehaviour(Player * player);
private:
	CountryNode * findWeakestNodeOwnedByPlayer();
};

class  RandomAiBehaviour : public Behaviour {
public:
	virtual void placeArmiesDuringReinforce();
	virtual void attackEnemies();
	virtual void fortify();
	RandomAiBehaviour(Player * player);
	CountryNode * findRandomNodeOwnedByPlayer();
	std::vector<CountryNode *> findEveryFortifiableNode;
};