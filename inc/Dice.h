#pragma once
#include <vector>
//todo
//write contructor/destructor
class DicesRoller
{
private:
	//array which will track number of times each value is rolled
	std::vector<int> * rollHistory;
	int * totalDiceRolled;
public:
	DicesRoller();
	std::vector<int> roll(int numDice);
	void addToRollHistory(std::vector <int> roll);
	void showRollHistory();
	~DicesRoller();
};

class DicesPrompt
{
public:
	DicesPrompt();
	int getRolledNumberOfDice();
	~DicesPrompt();
};

