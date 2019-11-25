#pragma once
#include "Map.h"


class Player;
const int MAX_NUMBER_OF_RANDOM_ATTACKS = 15;

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
protected:
	bool nodeHasEnemies(CountryNode * node);
	
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

class  RandomAIBehaviour : public Behaviour {
public:
	virtual void placeArmiesDuringReinforce();
	virtual void attackEnemies();
	virtual void fortify();
	RandomAIBehaviour(Player * player);
	CountryNode * findRandomNodeOwnedByPlayerThatCanAttack();
private:
	std::vector<CountryNode *> findEveryFortifiableNode();
	bool hasNeighboursThatCanFortify(CountryNode * node);
	std::vector<CountryNode *> findEveryNeighbourNodeThatCanFortify(CountryNode* node);
	std::vector<CountryNode *> findEveryNodeThatCanAttack();

};