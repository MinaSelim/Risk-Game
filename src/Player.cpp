#pragma once

#include "..\inc\Player.h"
#include <iostream>
using namespace std;


Player::Player()
{
	this->playerName = new string();
	this->countries = new vector<CountryNode>();
}

Player::Player(string playerName, vector<CountryNode> countries)
{
	this->playerName  = new string();
	this->countries	  = new vector<CountryNode>();
	*this->playerName = playerName;
	*this->countries  = countries;
}

Player::~Player()
{
	delete playerName;
	delete countries;
}

void Player::reinforce()
{
	cout << "Executing the reinforce method" << endl;
}

void Player::attack()
{
	cout << "Executing the attack method" << endl;
}

void Player::fortify()
{
	cout << "Executing the fortify() method" << endl;
}
