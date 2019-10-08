#include <vector>
#include "..\inc\Cards.h"

using namespace std;
enum  CardType
{
	infantry = 0,
	artillery,
	cavalry
};
Card::Card()
{
	this->cardtype = new string("njnjn:");
	//*this->cardtype = nullptr;
}
Card::Card(CardType type)
{
	switch (type)
	{
	case 0:
		this->cardtype  = new string("infantry");
		break;
	case 1:
		this->cardtype  = new string("artillery");
		break;
	case 2:
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
Deck::Deck()
{
	this->deck = new vector<Card>();
}

Deck::Deck(int numberOfCountries)
{
	int counter					 = 0;
	int counterInfantry			 = 0;
	int counterArtillery		 = 0;
	int counterCavalry			 = 0;
	//What should I do if the number isn't divisble by 3 ?
	int numberOfCardsForEachType = numberOfCountries/3;
	this->deck = new vector<Card> (numberOfCountries);

	while (counter != numberOfCountries) {
		CardType cardType = CardType(rand() % 3);
	}
}

Deck::~Deck()
{
}


void Deck::draw(vector<Card>& deck)
{
}

void Deck::generateDeck(vector<Card>& deck, int numberOfCountries)
{
	int counter = 0
	bool done = false;
	int numberOfCardsOfEachType = numberOfCountries/3;
	int numberOfInfantry  = numberOfCardsOfEachType;
	int numberOfArtillery = numberOfCardsOfEachType;
	int numberOfCavalry   = numberOfCardsOfEachType;
	while (!done) {
		Type type = Type(rand() % 3);
		if (type == 0 && numberOfInfantry > 0) {
			Card * card = new Card(type);
			deck.insert();
			numberOfInfantry--;
		}
	}
}

