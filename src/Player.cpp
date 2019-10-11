#pragma once

#include "..\inc\Player.h"
#include <iostream>
using namespace std;


Player::Player()
{
	this->playerName	 = new string();
	this->countries		 = new vector<CountryNode*>();
	this->numberOfArmies = new int(0);
	this->dice			 = new DicesRoller();
	this->hand			 = new HandOfCards();
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

DicesRoller* Player::getDice()
{
	return dice;
}

int  Player::getNumberOfArmies()
{
	int armies = *this->numberOfArmies;
	return armies;
}

HandOfCards* Player::getCard() {
	return hand;
}

//vector<CountryNode*>* Player::getListOfCountries()
//{
//	return ;
//}
