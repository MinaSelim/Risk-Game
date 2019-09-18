#include "Dice.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <algorithm>

// returns number of dice/number rolled on each dice, in a sorted container
void Dice::roll() {

	int numDice = 0;
	int* numDice_ptr{ nullptr };
	numDice_ptr = &numDice;

	std::cout << "How many dice will you roll?[1-3]: ";
	std::cin >> numDice;

	if (numDice > 3 || numDice < 1) {
		do {
			std::cout << "Please pick a number between 1-3: ";
			std::cin >> numDice;
		} while (numDice > 3 || numDice < 1);
	}

	//initialize vector for rolled values and rng seed
	std::vector <int> rolled_values;

	//make some random values between 1-6 and insert them in vector
	std::cout << "You rolled the following: \n";
	for (int i = 0; i < *numDice_ptr; i++) {
		int r = (rand() % 6) + 1;
		rolled_values.insert(rolled_values.begin(), r);
		std::cout << "[" << r << "] ";
	}
	std::cout << "\n";

	std::sort(rolled_values.begin(), rolled_values.end());

	addToRollHistory(rolled_values);
}

//to be called within roll function
void Dice::addToRollHistory(std::vector <int> roll) {
	rollHistory.insert(rollHistory.begin(), roll);
}

//use to display all previous rolls
void Dice::showRollHistory() {
	std::cout << "Here are your previous rolls: \n";
	for (unsigned int i = 0; i < rollHistory.size(); i++) {
		for (unsigned int j = 0; j < rollHistory[i].size(); j++)
			std::cout << "[" << rollHistory[i][j] << "] ";
		std::cout << "\n";
	}


}
