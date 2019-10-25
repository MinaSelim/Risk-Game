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
	~Card();
	inline string getCard()const { return *this->cardtype; };
	inline void setCard(string card) { *cardtype = card; };
};

class Deck {

private:
	vector<Card*> * deck;

public:
	Deck();
	Deck(int numberOfCountries);
	~Deck();
	string draw();
	void showDeck();
	int getRandomInt(int min, int max);
	int getSize();
};

class HandOfCards {
private:
	map<string*, int*> * playersCards;
	string userInputMethod();

public:
	HandOfCards();
	~HandOfCards();
	void pickACard(Deck * deck);
	void AddByOneValueOfCardType(string type);
	void reduceByOne();
	void PrintValues();
	int getNumberOfCards(string key);
	int exchange();
	int getTotalNumberOfCards();
};




