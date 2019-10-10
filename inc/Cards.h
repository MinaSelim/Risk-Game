#pragma once
#include <vector>
#include <new>
#include <map>
using namespace std;
enum  CardType
{
	infantry = 0,
	artillery,
	cavalry
};

class Card {

private:
	string* cardtype;

public:
	Card();
	Card(CardType type);
	string getCard();
	void setCard(string newCard);
	~Card();
};

class HandOfCards {
private:
	map<string*, int*> * playersCards;

public:
	HandOfCards();
	~HandOfCards();
	int getValue(string * key);
	int exchange();
	void reduceByOne();
	void PrintValues();
};



class Deck {

private:
	vector<Card*> * deck;

public:
	Deck();
	Deck(int numberOfCountries);
	~Deck();
	Card* draw();
	void generateDeck(int numberOfCountries);
	void showDeck();
	int getRandomInt(int min, int max);
	int getSize();
};
