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
	~DicesRoller();
	std::vector<int> roll(int numDice);
	void addToRollHistory(std::vector <int> roll);
	void showRollHistory();
	int getValueAt(int index);
};

class DicesPrompt
{
public:
	DicesPrompt();
	~DicesPrompt();

	int getRolledNumberOfDice();
};

