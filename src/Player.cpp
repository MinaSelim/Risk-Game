#pragma once

#include "..\inc\Player.h"
#include <iostream>
using namespace std;


Player::Player()
{
	this->playerName	  = new string();
	this->countries		  = new vector<CountryNode*>();
	this->numberOfArmies  = new int(0);
	this->dice			  = new DicesRoller();
	this->hand			  = new HandOfCards();
}

Player::Player(string playerName, vector<CountryNode*> countries)
{
	this->playerName	  = new string(playerName);
	this->countries		  = new vector<CountryNode*>(countries);
	this->numberOfArmies  = new int(0);
	this->dice			  = new DicesRoller();
	this->hand			  = new HandOfCards();
}

Player::~Player()
{
	delete playerName;
	playerName = NULL;
	delete numberOfArmies;
	numberOfArmies = NULL;
	delete dice;
	delete hand;

	countries->clear();
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

DicesRoller* Player::getDice()
{
	return dice;
}

HandOfCards* Player::getHandOfCards() 
{
	return hand;
}

string Player::getPlayerName()
{
	return *this->playerName;
}

int Player::getNumberOfArmies()
{
	int armies = *this->numberOfArmies;
	return armies;
}

void Player::setNumberOfArmies(int value)
{
	*this->numberOfArmies = value;
}

void Player::printListOfCountries()
{
	for (unsigned int i = 0; i < this->countries->size(); i++) 
	{
		cout << "Country " << i << " " << (*countries)[i]->countryInformation->getCountryName() << endl;
	}
}
