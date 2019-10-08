#pragma once
#include <vector>
#include <new>
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
};



class Deck {

private:
	vector<Card*> deck;

public:
	Deck();
	Deck(int numberOfCountries);
	~Deck();
	void draw(vector<Card*>&deck);
	void generateDeck(vector<Card*>&deck);
};
