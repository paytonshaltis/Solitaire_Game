//=================================================================================================//
//Payton Shaltis                                                                                   //
//January 20, 2021                                                                                 //
//Solitaire Project: Deck Class Header                                                             //  
//                                                                                                 //
//This file serves as the header to the Deck Class, which defines a Card object and declares its   //
//functions. Some functions include displaying each of the cards in a deck in full and in their    //
//miniature version, shuffling the deck to randomize card order, dealing the top card or returning //
//the value at any card at random, and accessing deck size and adding cards to the deck.           //
//=================================================================================================//

#include <string>
#include <iostream>
#include "Card.h"
#include <vector>

#ifndef DECK_H
#define DECK_H

using namespace std;

class Deck {

    private:
    vector<Card> contents;      //vector which will contain the 52 cards
    int size;                   //number of cards in the deck

    public:
    Deck();                     //constructor, fills deck with 52 in-order cards
    void displayDeck();         //displays each card in the deck on a seperate line
    void displayDeckMini();     //displays each card in the deck as a two character symbol
    void shuffleDeck();         //shuffles the order of the cards
    Card randomCard();          //returns a card at random from the deck
    Card cardAt(int pos);       //returns the card from the position at 'pos'
    Card dealCard();            //deals the top card, removing it from the deck
    int getSize();              //returns the size of the deck
    void addCard(Card card);             //adds a card to the bottom of the deck
};

#endif