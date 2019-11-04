#include "Dice.h"
#include "ErrorCodes.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

//To create an object od the dice which belongs to every player and it contains the history of their rolling.
DicesRoller::DicesRoller() 
{
	this->rollHistory = new vector<int*>{new int (0),new int(0),new int (0),new int(0),new int(0), new int (0) };
	this->totalDiceRolled = new int();
}

DicesRoller::~DicesRoller()
{
	for (unsigned int i = 0; i < rollHistory->size(); i++)
	{
		delete (*rollHistory)[i];
		(*rollHistory)[i] = NULL;
	}
	rollHistory->clear();
	delete totalDiceRolled;
}

// returns number of dice/number rolled on each dice, in a sorted container
vector<int> DicesRoller::roll(int numDice) {
	//initialize vector for rolled values and rng seed
	vector <int> rolledValues;

	auto& totalDiceRef = *totalDiceRolled;
	totalDiceRef = totalDiceRef + numDice;
	
	//make some random values between 1-6 and insert them in vector

	for (int i = 0; i < numDice; i++) 
	{
		int r = (rand() % 6) + 1;

		rolledValues.insert(rolledValues.begin(), r);
		cout << "[" << r << "] ";
	}
	cout << "\n";

	sort(rolledValues.begin(), rolledValues.end());
	//sorts high to low for compare wise pairs
	reverse(rolledValues.begin(), rolledValues.end());
	addToRollHistory(rolledValues);

	return rolledValues;
}

//to be called within roll function
void DicesRoller::addToRollHistory(vector <int> roll) 
{
	//Increasingt the number of times a dice face (1,2,3,4,5 or 6) has 
	//Came up to include them in the history vector
	for (unsigned int i = 0; i < roll.size(); i++)
	{
		switch (roll[i]) 
		{
			case 1: 
				*(*rollHistory)[0]+=1;
				break;
			case 2: 
				*(*rollHistory)[1]+=1;
				break;
			case 3:
				*(*rollHistory)[2]+=1;
				break;
			case 4:
				*(*rollHistory)[3]+=1;
				break;
			case 5:
				*(*rollHistory)[4]+=1;
				break;
			case 6:
				*(*rollHistory)[5]+=1;
				break;

		}
	}
}

//use to display all previous rolls
void DicesRoller::showRollHistory() 
{
	auto& totalDiceRef = *totalDiceRolled;
	
	std::cout << "total rolls: " << totalDiceRef <<" \n";

	std::cout << "Breakdown of previous rolls: \n";
	//calculate percentage of each value rolled [1-6]
	for (unsigned int i = 0; i < rollHistory->size(); i++)
	{
		double rollRatio = ((double)*(*rollHistory)[i]) / (double)(totalDiceRef);
		double percentageRoll = rollRatio * 100;
		std::cout << "Percentage of " << (i + 1) << "'s rolled: " << percentageRoll;
		std::cout << "\n";
	}
}

int DicesRoller::getValueAt(int index)
{
	cout << *this->rollHistory->at(index) << endl;
	return *this->rollHistory->at(index);
}

DicesPrompt::DicesPrompt()
{
}

DicesPrompt::~DicesPrompt()
{
}

//IO for getting number of dice to roll
int DicesPrompt::getRolledNumberOfDice(bool attack, int armies)
{
	int numDice = 0;
	int maxDice = 0;

	//if the player is attacking or defending the maximum number of dice changes

	if (attack)
	{
		maxDice = 3;
		do
		{
			cout << "How many dice will you roll? ";
			cin >> numDice;

			if (numDice > maxDice || numDice < 1) 
			{
				cout << "Cannot roll more than 3 dice or less than 1" << endl;
			}
			if (numDice > (armies - 1))
			{
				cout << "Cannot roll more than one dice because you have only two arrmies and you need to leave at least one behind" << endl;
			}

		} while (numDice > maxDice || numDice < 1 || numDice >(armies - 1));
	}
	else
	{
		maxDice = 2;
		do
		{
			cout << "How many dice will you roll? ";
			cin >> numDice;

			if (numDice > maxDice || numDice < 1)
			{
				cout << "Cannot roll more than 2 dice or less than 1" << endl;
			}
			if (numDice > armies)
			{
				cout << "Cannot roll more dice than armies you own" << endl;
			}

		} while (numDice > maxDice || numDice < 1 || numDice > armies );
	}
	
	
	return numDice;
}



