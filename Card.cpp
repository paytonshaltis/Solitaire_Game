//=================================================================================================//
//Payton Shaltis                                                                                   //
//January 20, 2021                                                                                 //
//Solitaire Project: Card CPP File                                                                 //
//                                                                                                 //
//This file serves as the CPP file to the Card Class, which defines a Card object's functions. Most//
//of the definitions are self explanatory, such as the getters and setters, but each function has  //
//been well-documented to clearly explain something that is not as trivial.                        //
//=================================================================================================//

#include <string>
#include <iostream>
#include "Card.h"

using namespace std;

Card::Card() {                                          //constructor that initializes value and suit to "blank"
    value = "blank";
    suit = "blank";
    visible = true;                                     //card is initially visible
    red = false;                                        //color of the card is initially neither
    black = false;
}

string Card::getValue() {                               //returns value of card
    return value;
}

string Card::getSuit() {                                //returns suit of card
    return suit;
}

string Card::getColor() {                               //returns color of card
    if(this->red)
        return "Red";
    else
        return "Black";
}

void Card::setValue(string value) {                     //sets the value of the card to "value"
    this->value = value;
}

void Card::setSuit(string suit) {                       //sets the suit of the card to "suit"
    this->suit = suit;
    this->setColor();
}

void Card::setColor() {                                 //private function used by the setSuit() function to assign color
    if(this->suit == "Spades" || this->suit == "Clubs") {
        this->black = true;
    }
    else {
        this->red = true;
    }
    
}

void Card::displayCard() {                              //prints the name of the card
    if(visible == false) {                              //prints "Unknown" if the card is not visible
        cout << "Unknown" << endl;
    }
    else
        cout << value << " of " << suit << endl;        //otherwise prints the name of the card
}

void Card::displayCardMini() {                          //will display the card as two characters        
    
    string miniValue = "error";                         //mini version of the card's value
    string miniSuit = "error";                          //mini version of the card's suit
    
    if(visible == false) {                              //prints "--" if the card is not visible
        cout << "--";
    }
    else {                                              //otherwise prints the mini name of the card
        if(suit == "Spades")
            miniSuit = "S";
        if(suit == "Hearts")
            miniSuit = "H";
        if(suit == "Clubs")
            miniSuit = "C";
        if(suit == "Diamonds")
            miniSuit = "D";
        
        if(value == "Ace")
            miniValue = "A";
        if(value == "Two")
            miniValue = "2";
        if(value == "Three")
            miniValue = "3";
        if(value == "Four")
            miniValue = "4";
        if(value == "Five")
            miniValue = "5";
        if(value == "Six")
            miniValue = "6";
        if(value == "Seven")
            miniValue = "7";
        if(value == "Eight")
            miniValue = "8";
        if(value == "Nine")
            miniValue = "9";
        if(value == "Ten")
            miniValue = "T";
        if(value == "Jack")
            miniValue = "J";
        if(value == "Queen")
            miniValue = "Q";
        if(value == "King")
            miniValue = "K";
        cout << miniValue << miniSuit;
    }                                          
}

Card Card::maskCard() {                                 //masks the card in its mini version
    visible = false;
    Card newCard;
    newCard.suit = this->suit;
    newCard.value = this->value;
    newCard.visible = this->visible;
    return newCard;
}

void Card::unmaskCard() {                              //unmasks the card
    this->visible = true;
}

bool Card::isMasked() {                                //returns true if the card is masked
    if(this->visible == true)
        return false;
    else
        return true;
}

bool Card::isEqual(Card card) {                         //returns true if the two cards are equal
    if(this->getSuit() == card.getSuit() && this->getValue() == card.getValue())
        return true;
    else
        return false;
}

bool Card::operator==(Card card2) {                     //returns true if both sides of the == are the same card
    if(this->getSuit() == card2.getSuit() && this->getValue() == card2.getValue())
        return true;
    else
        return false;
}

string Card::returnMini() {                             //returns the mini string of a card
    
    //note that if a value is missing, it will not be visible in the final mini version of the card. This is
    //used for the aces that initially can be placed on win piles by typing "AC to C", etc.
    string miniValue = "";                              //mini version of the card's value
    string miniSuit = "";                               //mini version of the card's suit
    
    if(suit == "Spades")
        miniSuit = "S";
    if(suit == "Hearts")
        miniSuit = "H";
    if(suit == "Clubs")
        miniSuit = "C";
    if(suit == "Diamonds")
        miniSuit = "D";
    
    if(value == "Ace")
        miniValue = "A";
    if(value == "Two")
        miniValue = "2";
    if(value == "Three")
        miniValue = "3";
    if(value == "Four")
        miniValue = "4";
    if(value == "Five")
        miniValue = "5";
    if(value == "Six")
        miniValue = "6";
    if(value == "Seven")
        miniValue = "7";
    if(value == "Eight")
        miniValue = "8";
    if(value == "Nine")
        miniValue = "9";
    if(value == "Ten")
        miniValue = "T";
    if(value == "Jack")
        miniValue = "J";
    if(value == "Queen")
        miniValue = "Q";
    if(value == "King")
        miniValue = "K";
    
    return miniValue + miniSuit;
}