#include "Dice.h"
#include "ErrorCodes.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

DicesRoller::DicesRoller() 
{
	this->rollHistory = new std::vector<int>{ 0,0,0,0,0,0 };
	this->totalDiceRolled = new int();
}

DicesRoller::~DicesRoller()
{
	delete[] rollHistory;
	delete totalDiceRolled;
}

// returns number of dice/number rolled on each dice, in a sorted container
std::vector<int> DicesRoller::roll(int numDice) {
	//initialize vector for rolled values and rng seed
	std::vector <int> rolledValues;

	auto& totalDiceRef = *totalDiceRolled;
	totalDiceRef = totalDiceRef + numDice;
	
	//make some random values between 1-6 and insert them in vector
	std::cout << "You rolled the following: \n";

	for (int i = 0; i < numDice; i++) 
	{
		int r = (rand() % 6) + 1;

		rolledValues.insert(rolledValues.begin(), r);
		std::cout << "[" << r << "] ";
	}
	std::cout << "\n";

	std::sort(rolledValues.begin(), rolledValues.end());

	addToRollHistory(rolledValues);

	return rolledValues;
}

//to be called within roll function
void DicesRoller::addToRollHistory(std::vector <int> roll) 
{
	auto& rollRef = *rollHistory;
	
	for (unsigned int i = 0; i < roll.size(); i++)
	{
		switch (roll[i]) 
		{
			case 1: rollRef[0]++;
					break;
			case 2: rollRef[1]++;
					break;
			case 3: rollRef[2]++;
					break;
			case 4: rollRef[3]++;
					break;
			case 5: rollRef[4]++;
					break;
			case 6: rollRef[5]++;
					break;

		}
	}
}

//use to display all previous rolls
void DicesRoller::showRollHistory() 
{
	auto& totalDiceRef = *totalDiceRolled;
	auto& rollRef = *rollHistory;
	
	std::cout << "total rolls: " << totalDiceRef <<" \n";

	std::cout << "Breakdown of previous rolls: \n";
	//calculate percentage of each value rolled [1-6]
	for (unsigned int i = 0; i < rollRef.size(); i++)
	{
		double rollRatio = ((double)rollRef[i]) / ((double)totalDiceRef);
		double percentageRoll = rollRatio * 100;
		std::cout << "Percentage of " << (i + 1) << "'s rolled: " << percentageRoll;
		std::cout << "\n";
	}
}

//Are these even necessary for this class?
DicesPrompt::DicesPrompt()
{
	
}

DicesPrompt::~DicesPrompt()
{
	
}
//IO for getting number of dice to roll
int DicesPrompt::getRolledNumberOfDice()
{
	int numDice = 0;

	std::cout << "How many dice will you roll?[1-3]: ";
	std::cin >> numDice;

	if (numDice > 3 || numDice < 1) 
	{
		throw INVALID_DICEROLL;
	}

	return numDice;
}

