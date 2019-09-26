#pragma once
#include <vector>

class DicesRoller
{
private:
	//multidimensional vector to keep track of all previous rolls
	std::vector<std::vector<int>> rollHistory;
public:
	std::vector<int> roll(int numDice);
	void addToRollHistory(std::vector <int> roll);
	void showRollHistory();

};

class DicesPrompt
{
public:
	int getRolledNumberOfDice();
};

