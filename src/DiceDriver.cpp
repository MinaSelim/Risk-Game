#include "Dice.h"

void diceDriverTest(){
	DicesRoller diceRoller1;
	DicesRoller diceRoller2;

	DicesPrompt dicesPrompt;

	int roll1 = dicesPrompt.getRolledNumberOfDice();
	
	diceRoller1.roll(roll1);
	
	int roll2 = dicesPrompt.getRolledNumberOfDice();

	diceRoller2.roll(roll2);

}

