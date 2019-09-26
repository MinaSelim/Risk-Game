#include "Dice.h"
#include "ErrorCodes.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <algorithm>

// returns number of dice/number rolled on each dice, in a sorted container
std::vector<int> DicesRoller::roll(int numDice) {
	//initialize vector for rolled values and rng seed
	std::vector <int> rolledValues;

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

	addToRollHistory(&rolledValues);

	return rolledValues;
}

//to be called within roll function
void DicesRoller::addToRollHistory(std::vector <int> roll) 
{
	rollHistory.insert(rollHistory.begin(), roll);
}

//use to display all previous rolls
void DicesRoller::showRollHistory() 
{
	std::cout << "Here are your previous rolls: \n";

	for (unsigned int i = 0; i < *rollHistory.size(); i++) 
	{
		for (unsigned int j = 0; j < *rollHistory[i].size(); j++)
			std::cout << "[" << *rollHistory[i][j] << "] ";

		std::cout << "\n";
	}
}

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