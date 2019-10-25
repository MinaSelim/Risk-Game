#include <vector>
#include "Cards.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include "Player.h"

using namespace std;

Card::Card(): cardtype(new string("N/A")){}

Card::Card(CardType type)
{
	switch (type)
	{
	case CardType::infantry:
		this->cardtype  = new string("infantry");
		break;
	case CardType::artillery:
		this->cardtype  = new string("artillery");
		break;
	case CardType::cavalry:
		this->cardtype  = new string("cavalry");
		break;
	default:
		break;
	}
}

Card::~Card()
{
	delete cardtype;
}

//Functions related to the Deck Class:
Deck::Deck() : deck(new vector<Card*>()){}

//Constructiing a deck of equal numbers of cards for each type:
Deck::Deck(int numberOfCountries)
{
	 this->deck = new vector<Card*>();

	 bool done = false;
	 int numberOfCardsOfEachType = numberOfCountries / 3;
	 int numberOfInfantry = numberOfCardsOfEachType;
	 int numberOfArtillery = numberOfCardsOfEachType;
	 int numberOfCavalry = numberOfCardsOfEachType;
	 while (!done) {
		 CardType type = CardType(rand() % 3);
		 if (type == CardType::infantry && numberOfInfantry > 0) {
			 this->deck->push_back(new Card(type));
			 numberOfInfantry--;
		 }
		 if (type == CardType::artillery && numberOfArtillery > 0) {
			 this->deck->push_back(new Card(type));
			 numberOfArtillery--;
		 }
		 if (type == CardType::cavalry && numberOfCavalry > 0) {
			 this->deck->push_back(new Card(type));
			 numberOfCavalry--;
		 }
		 if (numberOfArtillery == 0 && numberOfCavalry == 0 && numberOfInfantry == 0) {
			 done = true;
		 }
	 }
}

Deck::~Deck()
{
	for (unsigned int i = 0; i < deck->size(); i++) {
		delete (*deck)[i];
		(*deck)[i] = NULL;
	}
	deck->clear();
}

//Drawing a card randmonly from the deck 
string Deck::draw()
{
	if (this->deck->size() > 0) {
		int choosenCard = getRandomInt(0, deck->size() - 1);
 		string newValue = (*deck)[choosenCard]->getCard();
		(*deck).erase((*deck).begin() + (choosenCard));
		return newValue;
	}
	else {
		return NULL;
	}
	
}

//Get a random number, but it should be between 0 and the 
//The number of cards in the deck which are represened by min and max respectively
int Deck::getRandomInt(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

//It returns the number of cards in the deck
int Deck::getSize()
{
	return deck->size();
}

//It prints out how many cards there is in the deck of each type in the deck:
void Deck::showDeck()
{
	int numberOfInfantry  = 0;
	int numberOfartillery = 0;
	int numberOfCavalry   = 0;
	for (unsigned int i = 0; i < deck->size(); i++) {
		if ((*deck)[i]) {
			if ((*deck)[i]->getCard().compare("infantry") == 0) {
				numberOfInfantry += 1;
			}
			else if ((*deck)[i]->getCard().compare("artillery") == 0) {
				numberOfartillery += 1;
			}
			else if ((*deck)[i]->getCard().compare("cavalry") == 0) {
				numberOfCavalry += 1;
			}
		}
	}
	cout << "There is " << numberOfInfantry << " of type infantry in the deck" << endl;
	cout << "There is " << numberOfartillery << " of type artillery in the deck" << endl;
	cout << "There is " << numberOfCavalry << "  of type cavalry in the deck" << endl;
}

//Methods for HandOfCards:

//Create an object of the hand class where it is made of a map where 
//the key is the type of a card and the value is the number of cards of that
//type in the player's hand
HandOfCards::HandOfCards()
{
	this->playersCards = new map<string*, int*>();
	this->playersCards->insert({ new string("infantry"), new int(0) });
	this->playersCards->insert({ new string("artillery"), new int(0) });
	this->playersCards->insert({ new string("cavalry"), new int(0) });
}

HandOfCards::~HandOfCards()
{
	for (auto it = this->playersCards->begin(); it != this->playersCards->end(); ++it) {
		delete it->first;
		delete it->second;
	}
	playersCards->clear();
	playersCards = NULL;
}


//The player can use this method the pick a card from the deck
void HandOfCards::pickACard(Deck * deck)
{
	string  cardValue = deck->draw();

	Card * card = new Card();
	card->setCard(cardValue);

	//Increating the value of the card type that has been drawn from the deck
	this->AddByOneValueOfCardType(card->getCard());
	delete card;
	card = NULL;
}

//This will increase the value of a card type (parameter type) in the player's hand by one:
void HandOfCards::AddByOneValueOfCardType(string type) {
	for (auto it = this->playersCards->begin(); it != this->playersCards->end(); ++it) {
		if (type.compare(*it->first) == 0) {
			*it->second += 1;
			break;
		}
	}
}

//This method will decrease the value of each type by one
void HandOfCards::reduceByOne() {
	for (auto it = this->playersCards->begin(); it != this->playersCards->end(); ++it) {
		*it->second -= 1;
	}
}


//It will return the number of card of a specific type in the player's hand
int HandOfCards::getNumberOfCards(string key) {
	int  value =0;
	for (auto it = this->playersCards->begin(); it != this->playersCards->end(); ++it) {
		string cardType = *it->first;
		if (cardType.compare(key)) {
			value = *it->second;
		}
	}
	return value;
}

//The Player can exchange between the cards they have and armies
int HandOfCards::exchange()
{
	static int nextTurnNumberOfArmies = 4;
	static int numberOfArmies		  = 4;
	numberOfArmies					  = nextTurnNumberOfArmies;
	int numberOfCardsInHand		      = this->getTotalNumberOfCards();
	string userInput				  = "yes";

	//Represent the number of the types of cards that it has more than 0 cards in hand
	int numberOfTypesValid			  = 0;
	bool possibleExchange			  = false;

	//The player have the options of exchaging or not if they have more than 5 cards
	if (numberOfCardsInHand < 5) 
	{
		userInput = userInputMethod();
	}
	
	if (userInput.compare("yes") == 0) {
		for (auto it = this->playersCards->begin(); it != this->playersCards->end(); ++it) 
		{
			int numberOfCardsOfAType = *it->second;
			string cardType = *it->first;

			if (numberOfCardsOfAType >= 3) 
			{
				*it->second -= 3;
				possibleExchange = true;
				break;
			}
			else if (numberOfCardsOfAType > 0 && numberOfCardsOfAType != 3)
			{
				numberOfTypesValid += 1;
			}
			if (numberOfTypesValid == 3) 
			{
				possibleExchange = true;
				this->reduceByOne();
				break;
			}
		}

		//If the player has enough cards then:
		if (possibleExchange) 
		{
			if (numberOfArmies < 12) 
			{
				nextTurnNumberOfArmies += 2;
			}
			else if (numberOfArmies == 12) {
				nextTurnNumberOfArmies += 3;
			}
			else {
				nextTurnNumberOfArmies += 5;
			}
			return numberOfArmies;
		}
		else 
		{
			cout << "The player doesn't have enough cards to execute the exchange mehtod \n" << endl;
			return 0;
		}
	}
	else 
	{
		cout << "The player doesn't want to exchange() their cards with armies \n";
		return NULL;
	}
		
}

//Method to take the input of the user for the exchange method:
string HandOfCards::userInputMethod()
{
	string userInput = "";
	do {
		cout << "Do you want to exchange your cards with some armies (yes/no): ";
		cin >> userInput;
	} while (!userInput.compare("yes") == 0 && !userInput.compare("no") == 0);
	return userInput;

}
//To get the total number of cards in player's hand:
int HandOfCards::getTotalNumberOfCards()
{
	int total = 0;
	for (auto it = this->playersCards->begin(); it != this->playersCards->end(); ++it) 
	{
		total += *it->second;
	}
	return total;
}

//To display how many cards the player has from each type of cards.
void HandOfCards::PrintValues() {
	for (auto it = this->playersCards->begin(); it != this->playersCards->end(); ++it) {
		cout << "Card: " << *it->first << "   " <<  *it->second << endl;
	}
}
