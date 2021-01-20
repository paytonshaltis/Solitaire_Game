//=================================================================================================//
//Payton Shaltis                                                                                   //
//January 20, 2021                                                                                 //
//Solitaire Project: Deck CPP File                                                                 //  
//                                                                                                 //
//This file serves as the CPP file to the Deck Class, which defines a Deck object's functions. All //
//of the functions are well-documented to explain why certain actions are take for each, since the //
//Deck functions can be a bit more unclear than the Card objects' functions.                       //
//=================================================================================================//

#include <string>
#include <iostream>
#include "Card.h"
#include "Deck.h"
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

Deck::Deck() {                                          //constructor for a Deck object
    
    size = 0;                                           //initializes deck size, increments with each insertion
    
    vector<string> values;                              //creates a vector with all of the possible card values
    values.push_back("Ace");
    values.push_back("Two");
    values.push_back("Three");
    values.push_back("Four");
    values.push_back("Five");
    values.push_back("Six");
    values.push_back("Seven");
    values.push_back("Eight");
    values.push_back("Nine");
    values.push_back("Ten");
    values.push_back("Jack");
    values.push_back("Queen");
    values.push_back("King");

    vector<string> suits;                               //creates a vector with all of the possible card suits
    suits.push_back("Spades");
    suits.push_back("Hearts");
    suits.push_back("Clubs");
    suits.push_back("Diamonds");
    
    for(int i = 0; i < suits.size(); i++) {             //adds cards to the deck in order of value and suit
        for(int j = 0; j < values.size(); j++) {
            Card card;
            card.setSuit(suits.at(i));
            card.setValue(values.at(j));
            contents.push_back(card);
            size++;                                     //increases the size of the deck by one each time
        }
    }
}

void Deck::displayDeck() {                              //prints one card per line until the entire deck is shown    
    for(int i = 0; i < this->size; i++) {
        contents.at(i).displayCard();
    }
}

void Deck::displayDeckMini() {                          //prints one mini card per line until the entire deck is shown
    for(int i = 0; i < this->size; i++) {
        contents.at(i).displayCardMini();
    }
}

void Deck::shuffleDeck() {                              
    vector<Card> newContents;                           //creates a new empty vector
    srand(time(nullptr));                               //seeds the random number at the current time
    for(int i = 52; i > 0; i--) {                       //loop goes from 51 to 0, reps number of cards left
        int random = rand() % i;                        //picks a random number from 0 - i
        newContents.push_back(contents.at(random));     //puts the card from that position into the new vector
        contents.erase(contents.begin() + random);      //deletes that card from the old vector
    }
    contents = newContents;                             //finish by making 'contents' equal to 'newContents'
}

Card Deck::randomCard() {                               //returns a random card from the deck
    srand(time(nullptr));
    int random = rand() % 52;
    return contents.at(random);
}

Card Deck::cardAt(int pos) {                            //returns the card at position 'pos' from the deck
    if(pos > 51 || pos < 0) {
        cout << "WARNING: OUT OF BOUNDS" << endl;       //will give warning if request is out of bounds
        Card card;
        return card;                                    //if so, returns a blank card
    }
    return contents.at(pos);
}

Card Deck::dealCard() {                                 //returns the top card and removes it from the deck
    Card temp = contents.at(0);
    contents.erase(contents.begin());
    size--;
    return temp;
}

int Deck::getSize() {                                   //returns the size of the deck
    return this->size;
}

void Deck::addCard(Card card) {                                  //adds a card to the bottom of the deck
    this->contents.push_back(card);
    size++;
}