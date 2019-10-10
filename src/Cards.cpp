#include <vector>
#include "..\inc\Cards.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
//Talk with mina if u have a number of cards that is not divisble by 3 --> what will u do  ?


using namespace std;

Card::Card()
{
	this->cardtype = new string("N/A");
}
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

string Card::getCard()
{
	return (*cardtype);
}

void Card::setCard(string newCard)
{
	*cardtype = newCard;
}




Card::~Card()
{
	delete cardtype;
}


//Functions related to the Deck Class:
Deck::Deck()
{
	 this->deck = new vector<Card*>();
}

Deck::Deck(int numberOfCountries)
{
	 this->deck = new vector<Card*>(numberOfCountries);
}

Deck::~Deck()
{
	for (unsigned int i = 0; i < deck->size(); i++) {
		delete (*deck)[i];
		(*deck)[i] = NULL;
	}
	deck->clear();
}

Card* Deck::draw()
{
	if (this->deck->size() > 0) {
		int choosenCard = getRandomInt(0, deck->size() - 1);
 		string newValue = (*deck)[choosenCard]->getCard();
		Card *newCard = new Card();
		newCard->setCard(newValue);
		(*deck).erase((*deck).begin() + (choosenCard));
		return newCard;
	}
	else {
		return NULL;
	}
	
}


int Deck::getRandomInt(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

int Deck::getSize()
{
	return deck->size();
}

void Deck::generateDeck(int numberOfCountries)
{
	bool done = false;
	int numberOfCardsOfEachType = numberOfCountries/3;
	int numberOfInfantry  = numberOfCardsOfEachType;
	int numberOfArtillery = numberOfCardsOfEachType;
	int numberOfCavalry   = numberOfCardsOfEachType;
	while (!done) {
		CardType type = CardType(rand() % 3);
		if (type == CardType::infantry && numberOfInfantry > 0) {
			this->deck->push_back( new Card(type) );
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

void Deck::showDeck()
{
	for (unsigned int i = 0; i < deck->size(); i++) {
		cout << "element " << i << " " << (*deck)[i]->getCard() << endl;
	}
}

//Methods for HandOfCards:

HandOfCards::HandOfCards()
{
	this->playersCards = new map<string*, int*>();
	this->playersCards->insert({ new string("infantry"), new int(36) });
	this->playersCards->insert({ new string("artillery"), new int(5) });
	this->playersCards->insert({ new string("cavalry"), new int(6) });
}

HandOfCards::~HandOfCards()
{
	for (auto it = this->playersCards->begin(); it != this->playersCards->end(); ++it) {
		delete it->first;
		delete it->second;
	}
	playersCards->clear();
}

int HandOfCards::getValue(string *key) {
	int  value =-1;
	for (auto it = this->playersCards->begin(); it != this->playersCards->end(); ++it) {
		string cardType = *it->first;
		if (cardType.compare(*key)) {
			value = *it->second;
		}
	}
	return value;
}
void HandOfCards::reduceByOne() {
	for (auto it = this->playersCards->begin(); it != this->playersCards->end(); ++it) {
		*it->second -= 1;
	}
}


int HandOfCards::exchange()
{
	static int numberOfArmies = 4;
	int numberOfTypes		  = 0;
	bool possibleExchange	  = false;
	for (auto it = this->playersCards->begin(); it != this->playersCards->end(); ++it) {
		int numberOfCardsOfAType = *it->second;
		string cardType			 = *it->first;
		
		if (numberOfCardsOfAType >= 3) {
			*it->second -= 3;
			possibleExchange = true;
			break;
		}
		else if (numberOfCardsOfAType >= 0 && numberOfCardsOfAType != 3) {
			numberOfTypes += 1;
		}
		else if (numberOfTypes == 3) {
			possibleExchange = true;
			this->reduceByOne();
			break;
		}
	}
	if (possibleExchange) {
		if (numberOfArmies < 12) {
			numberOfArmies += 2;
		}
		else if (numberOfArmies == 12) {
			numberOfArmies += 3;
		}
		else {
			numberOfArmies += 5;
		}
		return numberOfArmies;
	}
	else {
		cout << "You don't have enough cards to execute the exchange mehtod" << endl;
		return 0;
	}	
}

void HandOfCards::PrintValues() {
	for (auto it = this->playersCards->begin(); it != this->playersCards->end(); ++it) {
		cout << "Card: " << *it->first << "   " <<  *it->second << endl;
	}
}
