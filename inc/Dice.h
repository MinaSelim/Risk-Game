#pragma once
#include <vector>

class Dice
{
private:
	//multidimensional vector to keep track of all previous rolls
	std::vector<std::vector <int>> rollHistory;
public:
	void roll();
	void addToRollHistory(std::vector <int> roll);
	void showRollHistory();

};