#pragma once
#include <vector>
class DicesRoller
{
private:
	//vector which will track the number of times each value is rolled
	std::vector<int*> * rollHistory;
	int * totalDiceRolled;
public:
	DicesRoller();
	std::vector<int> roll(int numDice);
	void addToRollHistory(std::vector <int> roll);
	void showRollHistory();
	void increaseValue();
	int getValueAt(int index);
	~DicesRoller();
};

class DicesPrompt
{
public:
	DicesPrompt();
	int getRolledNumberOfDice();
	~DicesPrompt();
};

