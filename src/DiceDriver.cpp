#include "Dice.h"
#include "DiceDriver.h"

void DiceDriver::DiceTester(){
	
	//Testing the history functionality of dice for one player
	DicesRoller * diceRoller1 = new DicesRoller();
	DicesPrompt * dicesPrompt = new DicesPrompt();

	int numDice = dicesPrompt->getRolledNumberOfDice();
	diceRoller1->roll(numDice);
	diceRoller1->showRollHistory();

	numDice = dicesPrompt->getRolledNumberOfDice();
	diceRoller1->roll(numDice);
	diceRoller1->showRollHistory();

	numDice = dicesPrompt->getRolledNumberOfDice();
	diceRoller1->roll(numDice);
	diceRoller1->showRollHistory();

	numDice = dicesPrompt->getRolledNumberOfDice();
	diceRoller1->roll(numDice);
	diceRoller1->showRollHistory();

	delete diceRoller1;
	delete dicesPrompt;


	//Testing the history in case if we have two different players.
	DicesRoller * diceRoller1 = new DicesRoller();
	DicesRoller * diceRoller2 = new DicesRoller();
	DicesPrompt * dicesPrompt = new DicesPrompt();

	int numDice = dicesPrompt->getRolledNumberOfDice();
	diceRoller1->roll(numDice);
	diceRoller1->showRollHistory();

	numDice = dicesPrompt->getRolledNumberOfDice();
	diceRoller2->roll(numDice);
	diceRoller2->showRollHistory();

	
	delete diceRoller1;
	delete diceRoller2;
	delete dicesPrompt;



	/*Testing the "fairness" of the Dice
	//we will roll the Dice many times and check the percentage of each roll
	Assuming "fair" dice will be more or less split evenly between the face values of the dice [1-6]*/


	//DicesRoller * diceRoller3 = new DicesRoller;
	//int numDice = 3; //we will ignore the prompt because we are rolling many times, setting the dice to 3 will provide us more data

	//for (unsigned int i = 0; i < 1000; i++) 
	//{
	//	diceRoller3->roll(numDice);
	//}

	//diceRoller3->showRollHistory();
	//
	//delete diceRoller3;

}
