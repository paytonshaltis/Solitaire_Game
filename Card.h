//=================================================================================================//
//Payton Shaltis                                                                                   //
//January 20, 2021                                                                                 //
//Solitaire Project: Card Class Header                                                             //  
//                                                                                                 //
//This file serves as the header to the Card Class, which defines a Card object and declares its   //
//functions. Some functions include setter and getter functions for attributes of the cards such as// 
//its value, suit, or color, displaying the card's name in full or in a miniature version, masking //
//a card so that its values cannot be seen, and testing for equivalency between cards.             //
//=================================================================================================//

#include <string>
#include <iostream>

#ifndef CARD_H
#define CARD_H

using namespace std;

class Card {
    
    private:
    string value;                               //value of the card (ace - king)
    string suit;                                //suit of the card
    bool visible;                               //determines if the card is visible or not
    bool red;                                   //if the card is a red card
    bool black;                                 //if the card is a black card
    void setColor();                            //sets the correct color of the card

    public:
    Card();                                     //constructor, makes suit and value "blank"
    string getValue();                          //returns the card's value
    string getSuit();                           //returns the card's suit
    string getColor();                          //returns the card's color
    void setValue(string value);                //sets the card's value to "value"
    void setSuit(string suit);                  //sets the card's suit to "suit"
    void displayCard();                         //prints the name of the card
    void displayCardMini();                     //prints the mini version of a card, one character per suit and value
    Card maskCard();                            //returns a masked version of the card
    void unmaskCard();                          //unmasks the card
    bool isMasked();                            //returns true if the card is masked
    bool isEqual(Card card);                    //returns true if the two cards are equal
    bool operator==(Card card2);                //overloads the equivalency operator
    string returnMini();                        //returns the mini string of a card

};

#endif