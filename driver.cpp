//=================================================================================================//
//Payton Shaltis                                                                                   //
//January 20, 2021                                                                                 //
//Solitaire Project: Solitaire Driver                                                              //  
//                                                                                                 //
//This file serves as the driver to the Solitaire game itself. By including both the Card and Deck //
//header files, it gains access to a variety of functions that allow the game of Solitaire to be   //
//played. It does, however, require some of its own functions for certain actions required by the  //
//game, as well as certain global variables that make some game functions much easier to implement.//
//There is often a lot going on, so this file is well-documented to allow for the reader to be able//
//to get a better understanding for what is going on. One small note is that the verifyMove()      //
//function is the largest, most repetetive, and confusing of the functions, and will thus require  //
//more work in the future to compact it down with things such as helper functions. The game still  //
//works, however confusing the verifyMove() function may be.                                       //
//=================================================================================================//

#include <string>
#include <iostream>
#include "Card.h"
#include "Deck.h"
#include <stack>
#include <queue>

using namespace std;

//global variables that are used when the program checks for what moves are possible, and when trying to make those moves
bool toPile1 = false;
bool toPile2 = false;
bool toPile3 = false;
bool toPile4 = false;
bool toPile5 = false;
bool toPile6 = false;
bool toPile7 = false;
bool toWin1 = false;
bool toWin2 = false;
bool toWin3 = false;
bool toWin4 = false;

//global variables that are modified by settings in the menu and determine what is shown on the gameboard
bool showDeckSize;
bool showPossibleMoves;

//global variables that keep track of the times the deck is refilled. Used to control lose condition
int timesRefilled = 0;
bool deckRefilled = false;

//global variables that control what text is displayed in the ALERTS box when a move fails
bool wrongMove = false;
bool noMoves = false;

//accepts a string and returns the uppercase version of the word
string toUpper(string word) {
    
    int wordSize = word.size();                 //size of the word passed to function
    string finalWord = "";                      //the lowercase word that will be returned
    
    //for each letter, if it is an uppercase letter, it becomes lowercase, otherwise it remains the same
    for(int i = 0; i < wordSize; i++) {
        if(word.at(i) == 'a')
            finalWord += "A";
        else if(word.at(i) == 'b')
            finalWord += "B";
        else if(word.at(i) == 'c')
            finalWord += "C";
        else if(word.at(i) == 'd')
            finalWord += "D";
        else if(word.at(i) == 'e')
            finalWord += "E";
        else if(word.at(i) == 'f')
            finalWord += "F";
        else if(word.at(i) == 'g')
            finalWord += "G";
        else if(word.at(i) == 'h')
            finalWord += "H";
        else if(word.at(i) == 'i')
            finalWord += "I";
        else if(word.at(i) == 'j')
            finalWord += "J";
        else if(word.at(i) == 'k')
            finalWord += "K";
        else if(word.at(i) == 'l')
            finalWord += "L";
        else if(word.at(i) == 'm')
            finalWord += "M";
        else if(word.at(i) == 'n')
            finalWord += "N";
        else if(word.at(i) == 'o')
            finalWord += "O";
        else if(word.at(i) == 'p')
            finalWord += "P";
        else if(word.at(i) == 'q')
            finalWord += "Q";
        else if(word.at(i) == 'r')
            finalWord += "R";
        else if(word.at(i) == 's')
            finalWord += "S";
        else if(word.at(i) == 't')
            finalWord += "T";
        else if(word.at(i) == 'u')
            finalWord += "U";
        else if(word.at(i) == 'v')
            finalWord += "V";
        else if(word.at(i) == 'w')
            finalWord += "W";
        else if(word.at(i) == 'x')
            finalWord += "X";
        else if(word.at(i) == 'y')
            finalWord += "Y";
        else if(word.at(i) == 'z')
            finalWord += "Z";
        else
            finalWord += word.at(i);
    }

    //returns the final lowercase version of the word
    return finalWord;
}

//returns the card that is the deepest visible card of a main pile stack. NOTE: the pile is sent here in REVERSED ORDER from main
Card deepestVisible(stack<Card> pile) {
    
    //start by reversing the order of the pile
    stack<Card> reversed;
    while(pile.empty() == false) {
        reversed.push(pile.top());
        pile.pop();
    }

    //while loop will go and remove all of the masked cards from the stack
    while(reversed.top().isMasked() == true) {
        reversed.pop();
    }
    
    //this will then return the deepest visible card in that pile
    return reversed.top();
}

//returns the deepest card of a pile. Used to see if the deepest visible king is also the deepest card. NOTE: the pile is sent here in REVERSED ORDER from main
Card deepestCard(stack<Card> pile) {
    
    //start by reversing the order of the pile
    stack<Card> reversed;
    while(pile.empty() == false) {
        reversed.push(pile.top());
        pile.pop();
    }

    //this will then return the deepest card in that pile
    return reversed.top();
}

//prints the contents of the hand in order
void printHand(stack<Card> hand) {
    while(hand.empty() == false) {
        hand.top().displayCard();
        hand.pop();
    }
}

//displays the board, which consists of 7 main piles, 4 win piles, and the 'hand' of other useable cards
void displayBoard(stack<Card> pile1, stack<Card> pile2, stack<Card> pile3, stack<Card> pile4, stack<Card> pile5, stack<Card> pile6, stack<Card> pile7, stack<Card> win1, stack<Card> win2, stack<Card> win3, stack<Card> win4, stack<Card> hand, Deck deck)  {
    cout << "I-----------------------------------------------------I" << endl;
    cout << "I------------S O L I T A I R E   B O A R D------------I" << endl;
    cout << "I-----------------------------------------------------I" << endl;

    //displays the board's seven main piles
    for(int i = 0; i < 19; i++) {
        
        cout << "|  ";
        
        if(pile1.empty() == false) {
            pile1.top().displayCardMini();
            pile1.pop();
            cout << "  ";
        }
        else {
            cout << "    ";       
        }
        if(pile2.empty() == false) {
            pile2.top().displayCardMini();
            pile2.pop();
            cout << "  ";
        }
        else {
            cout << "    ";       
        }
        if(pile3.empty() == false) {
            pile3.top().displayCardMini();
            pile3.pop();
            cout << "  ";
        }
        else {
            cout << "    ";       
        }
        if(pile4.empty() == false) {
            pile4.top().displayCardMini();
            pile4.pop();
            cout << "  ";
        }
        else {
            cout << "    ";       
        }  
        if(pile5.empty() == false) {
            pile5.top().displayCardMini();
            pile5.pop();
            cout << "  ";
        }
        else {
            cout << "    ";       
        }  
        if(pile6.empty() == false) {
            pile6.top().displayCardMini();
            pile6.pop();
            cout << "  ";
        }
        else {
            cout << "    ";       
        }
        if(pile7.empty() == false) {
            pile7.top().displayCardMini();
            pile7.pop();
            cout << "  ";
        }
        else {
            cout << "    ";       
        }   

        //displays the win pile aside from the second row of the board
        if(i == 1) {                                
            cout << "  " <<  "  ";
            win1.top().displayCardMini();
            cout << "  ";
            win2.top().displayCardMini();
            cout << "  ";
            win3.top().displayCardMini();
            cout << "  ";
            win4.top().displayCardMini();
            cout << "     |";
            goto nextline;
        }

        //displays the cards dealt to the hand
        if(i == 5) {
            cout << "          ";
            if(hand.empty() == false)
                hand.top().displayCardMini();
            else
                cout << "--";
            
            if(showDeckSize) {
                if(deck.getSize() >= 10) {
                    cout << " *" << deck.getSize();   
                }
                else {
                    cout << " *" << deck.getSize() << " ";
                }
            }
            else {
                cout << "    ";
            }
                

            cout << "       |";
            goto nextline;
        }
        
        cout << "                       |";

        nextline:
        cout << endl;
    }
    cout << "I-----------------------------------------------------I" << endl;
}

//displays this screen when the player exits the game early
void exitScreen() {

    cout <<  "*******************************************************" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*             _____                                   *" << endl;
    cout <<  "*            |A .  | _____                            *" << endl;
    cout <<  "*            | /.\\ ||A ^  | _____                     *" << endl;
    cout <<  "*            |(_._)|| / \\ ||A _  | _____              *" << endl;
    cout <<  "*            |  |  || \\ / || ( ) ||A_ _ |             *" << endl;
    cout <<  "*            |____V||  .  ||(_'_)||( v )|             *" << endl;
    cout <<  "*                   |____V||  |  || \\ / |             *" << endl;
    cout <<  "*                          |____V||  .  |             *" << endl;
    cout <<  "*                                 |____V|             *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*         ╭━━━┳━━━┳╮╱╱╭━━┳━━━━┳━━━┳━━┳━━━┳━━━╮        *" << endl;
    cout <<  "*         ┃╭━╮┃╭━╮┃┃╱╱╰┫┣┫╭╮╭╮┃╭━╮┣┫┣┫╭━╮┃╭━━╯        *" << endl;
    cout <<  "*         ┃╰━━┫┃╱┃┃┃╱╱╱┃┃╰╯┃┃╰┫┃╱┃┃┃┃┃╰━╯┃╰━━╮        *" << endl;
    cout <<  "*         ╰━━╮┃┃╱┃┃┃╱╭╮┃┃╱╱┃┃╱┃╰━╯┃┃┃┃╭╮╭┫╭━━╯        *" << endl;
    cout <<  "*         ┃╰━╯┃╰━╯┃╰━╯┣┫┣╮╱┃┃╱┃╭━╮┣┫┣┫┃┃╰┫╰━━╮        *" << endl;
    cout <<  "*         ╰━━━┻━━━┻━━━┻━━╯╱╰╯╱╰╯╱╰┻━━┻╯╰━┻━━━╯        *" << endl;
    cout <<  "*                          by Payton Shaltis          *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl; 
    cout <<  "*             THANKS FOR PLAYING THE GAME!            *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*******************************************************" << endl;

}

//displays this screen when the player looses the game
void loseScreen() {

    cout <<  "*******************************************************" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*             _____                                   *" << endl;
    cout <<  "*            |A .  | _____                            *" << endl;
    cout <<  "*            | /.\\ ||A ^  | _____                     *" << endl;
    cout <<  "*            |(_._)|| / \\ ||A _  | _____              *" << endl;
    cout <<  "*            |  |  || \\ / || ( ) ||A_ _ |             *" << endl;
    cout <<  "*            |____V||  .  ||(_'_)||( v )|             *" << endl;
    cout <<  "*                   |____V||  |  || \\ / |             *" << endl;
    cout <<  "*                          |____V||  .  |             *" << endl;
    cout <<  "*                                 |____V|             *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*         ╭━━━┳━━━┳╮╱╱╭━━┳━━━━┳━━━┳━━┳━━━┳━━━╮        *" << endl;
    cout <<  "*         ┃╭━╮┃╭━╮┃┃╱╱╰┫┣┫╭╮╭╮┃╭━╮┣┫┣┫╭━╮┃╭━━╯        *" << endl;
    cout <<  "*         ┃╰━━┫┃╱┃┃┃╱╱╱┃┃╰╯┃┃╰┫┃╱┃┃┃┃┃╰━╯┃╰━━╮        *" << endl;
    cout <<  "*         ╰━━╮┃┃╱┃┃┃╱╭╮┃┃╱╱┃┃╱┃╰━╯┃┃┃┃╭╮╭┫╭━━╯        *" << endl;
    cout <<  "*         ┃╰━╯┃╰━╯┃╰━╯┣┫┣╮╱┃┃╱┃╭━╮┣┫┣┫┃┃╰┫╰━━╮        *" << endl;
    cout <<  "*         ╰━━━┻━━━┻━━━┻━━╯╱╰╯╱╰╯╱╰┻━━┻╯╰━┻━━━╯        *" << endl;
    cout <<  "*                          by Payton Shaltis          *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                    YOU HAVE LOST.                   *" << endl; 
    cout <<  "*         THERE ARE POSSIBLE MOVES REMAINING.         *" << endl;
    cout <<  "*             THANKS FOR PLAYING THE GAME!            *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*******************************************************" << endl;

}

//displays this screen when the player wins the game
void winScreen() {

    cout <<  "*******************************************************" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*             _____                                   *" << endl;
    cout <<  "*            |A .  | _____                            *" << endl;
    cout <<  "*            | /.\\ ||A ^  | _____                     *" << endl;
    cout <<  "*            |(_._)|| / \\ ||A _  | _____              *" << endl;
    cout <<  "*            |  |  || \\ / || ( ) ||A_ _ |             *" << endl;
    cout <<  "*            |____V||  .  ||(_'_)||( v )|             *" << endl;
    cout <<  "*                   |____V||  |  || \\ / |             *" << endl;
    cout <<  "*                          |____V||  .  |             *" << endl;
    cout <<  "*                                 |____V|             *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*         ╭━━━┳━━━┳╮╱╱╭━━┳━━━━┳━━━┳━━┳━━━┳━━━╮        *" << endl;
    cout <<  "*         ┃╭━╮┃╭━╮┃┃╱╱╰┫┣┫╭╮╭╮┃╭━╮┣┫┣┫╭━╮┃╭━━╯        *" << endl;
    cout <<  "*         ┃╰━━┫┃╱┃┃┃╱╱╱┃┃╰╯┃┃╰┫┃╱┃┃┃┃┃╰━╯┃╰━━╮        *" << endl;
    cout <<  "*         ╰━━╮┃┃╱┃┃┃╱╭╮┃┃╱╱┃┃╱┃╰━╯┃┃┃┃╭╮╭┫╭━━╯        *" << endl;
    cout <<  "*         ┃╰━╯┃╰━╯┃╰━╯┣┫┣╮╱┃┃╱┃╭━╮┣┫┣┫┃┃╰┫╰━━╮        *" << endl;
    cout <<  "*         ╰━━━┻━━━┻━━━┻━━╯╱╰╯╱╰╯╱╰┻━━┻╯╰━┻━━━╯        *" << endl;
    cout <<  "*                          by Payton Shaltis          *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                    YOU HAVE WON!                    *" << endl; 
    cout <<  "*            YOU HAVE FILLED ALL WIN PILES!           *" << endl;
    cout <<  "*             THANKS FOR PLAYING THE GAME!            *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*                                                     *" << endl;
    cout <<  "*******************************************************" << endl;

}

//helper function for checkMoves that updates the possibleMoves variable if the top card from a certain pile or hand can be moved
void checkPileOrHand(stack<Card> pile1, stack<Card> pile2, stack<Card> pile3, stack<Card> pile4, stack<Card> pile5, stack<Card> pile6, stack<Card> pile7, stack<Card> observe, string sentPileName, bool isMainPile, stack<Card> win1, stack<Card> win2, stack<Card> win3, stack<Card> win4, int &possibleMoves) {

    //clear these global variables
    toPile1 = false;
    toPile2 = false;
    toPile3 = false;
    toPile4 = false;
    toPile5 = false;
    toPile6 = false;
    toPile7 = false;
    toWin1 = false;
    toWin2 = false;
    toWin3 = false;
    toWin4 = false;

    Card cardObserved;                                  //the top card of the stack; used for the hand to check mains and wins, used for the main to check wins
    Card cardObserved2;                                 //the deepest visible card of the stack; used for the main to check mains
    Card cardNeededInPile1;                             //card 1 needed in piles 1-7 for observed
    Card cardNeededInPile2;                             //card 2 needed in piles 1-7 for observed
    Card cardNeededInWinPile;                           //card needed in win pile for observed
    
    //if the pile is empty, return, there is no card to check
    if(observe.empty() == true) {
        return;
    }

    //if the observed variable is the hand, we just look at the top card of that stack
    if(!isMainPile) {
        cardObserved = observe.top();                       
    }
    //if the observed variable is one of the main piles, we look at the top card and the deepest visible card
    else {
        cardObserved = observe.top();
        
        stack<Card> observeCopy = observe;
        stack<Card> temp;
        
        Card current = observeCopy.top();
        while(current.isMasked() == false) {
            temp.push(current);
            observeCopy.pop();
            if(observeCopy.empty() == false)
                current = observeCopy.top();
            else
                break;
        }
        cardObserved2 = temp.top();
        //cardObserved.displayCard();
        //cardObserved2.displayCard();
    }
    
    
    //figure out the cards needed for any possible card on top of the hand
    if(!isMainPile) {
        //determines the values
        if(cardObserved.getValue() == "Ace") {              
            cardNeededInWinPile.setValue("blank");
        }
        else if(cardObserved.getValue() == "Two") {              
            cardNeededInPile1.setValue("Three");
            cardNeededInPile2.setValue("Three");
            cardNeededInWinPile.setValue("Ace");
        }
        else if(cardObserved.getValue() == "Three") {              
            cardNeededInPile1.setValue("Four");
            cardNeededInPile2.setValue("Four");
            cardNeededInWinPile.setValue("Two");
        }
        else if(cardObserved.getValue() == "Four") {           
            cardNeededInPile1.setValue("Five");
            cardNeededInPile2.setValue("Five");
            cardNeededInWinPile.setValue("Three");
        }
        else if(cardObserved.getValue() == "Five") {              
            cardNeededInPile1.setValue("Six");
            cardNeededInPile2.setValue("Six");
            cardNeededInWinPile.setValue("Four");
        }
        else if(cardObserved.getValue() == "Six") {              
            cardNeededInPile1.setValue("Seven");
            cardNeededInPile2.setValue("Seven");
            cardNeededInWinPile.setValue("Five");
        }
        else if(cardObserved.getValue() == "Seven") {              
            cardNeededInPile1.setValue("Eight");
            cardNeededInPile2.setValue("Eight");
            cardNeededInWinPile.setValue("Six");
        }
        else if(cardObserved.getValue() == "Eight") {              
            cardNeededInPile1.setValue("Nine");
            cardNeededInPile2.setValue("Nine");
            cardNeededInWinPile.setValue("Seven");
        }
        else if(cardObserved.getValue() == "Nine") {              
            cardNeededInPile1.setValue("Ten");
            cardNeededInPile2.setValue("Ten");
            cardNeededInWinPile.setValue("Eight");
        }
        else if(cardObserved.getValue() == "Ten") {              
            cardNeededInPile1.setValue("Jack");
            cardNeededInPile2.setValue("Jack");
            cardNeededInWinPile.setValue("Nine");
        }
        else if(cardObserved.getValue() == "Jack") {              
            cardNeededInPile1.setValue("Queen");
            cardNeededInPile2.setValue("Queen");
            cardNeededInWinPile.setValue("Ten");
        }
        else if(cardObserved.getValue() == "Queen") {              
            cardNeededInPile1.setValue("King");
            cardNeededInPile2.setValue("King");
            cardNeededInWinPile.setValue("Jack");
        }
        else if(cardObserved.getValue() == "King") {
            cardNeededInWinPile.setValue("Queen");
        }
    
        //determines the suits
        if(cardObserved.getSuit() == "Clubs") {
            cardNeededInPile1.setSuit("Hearts");
            cardNeededInPile2.setSuit("Diamonds");
            cardNeededInWinPile.setSuit("Clubs");
        }
        else if(cardObserved.getSuit() == "Spades") {
            cardNeededInPile1.setSuit("Hearts");
            cardNeededInPile2.setSuit("Diamonds");
            cardNeededInWinPile.setSuit("Spades");
        }
        else if(cardObserved.getSuit() == "Hearts") {
            cardNeededInPile1.setSuit("Clubs");
            cardNeededInPile2.setSuit("Spades");
            cardNeededInWinPile.setSuit("Hearts");
        }
        else if(cardObserved.getSuit() == "Diamonds") {
            cardNeededInPile1.setSuit("Clubs");
            cardNeededInPile2.setSuit("Spades");
            cardNeededInWinPile.setSuit("Diamonds");
        }
    }
    //if the cards observed are from one of the main piles
    else {
        //determines the value for win piles
        if(cardObserved.getValue() == "Ace") {              
            cardNeededInWinPile.setValue("blank");
        }
        else if(cardObserved.getValue() == "Two") {              
            cardNeededInWinPile.setValue("Ace");
        }
        else if(cardObserved.getValue() == "Three") {              
            cardNeededInWinPile.setValue("Two");
        }
        else if(cardObserved.getValue() == "Four") {           
            cardNeededInWinPile.setValue("Three");
        }
        else if(cardObserved.getValue() == "Five") {              
            cardNeededInWinPile.setValue("Four");
        }
        else if(cardObserved.getValue() == "Six") {              
            cardNeededInWinPile.setValue("Five");
        }
        else if(cardObserved.getValue() == "Seven") {              
            cardNeededInWinPile.setValue("Six");
        }
        else if(cardObserved.getValue() == "Eight") {              
            cardNeededInWinPile.setValue("Seven");
        }
        else if(cardObserved.getValue() == "Nine") {              
            cardNeededInWinPile.setValue("Eight");
        }
        else if(cardObserved.getValue() == "Ten") {              
            cardNeededInWinPile.setValue("Nine");
        }
        else if(cardObserved.getValue() == "Jack") {              
            cardNeededInWinPile.setValue("Ten");
        }
        else if(cardObserved.getValue() == "Queen") {              
            cardNeededInWinPile.setValue("Jack");
        }
        else if(cardObserved.getValue() == "King") {
            cardNeededInWinPile.setValue("Queen");
        }

        //determines the suit for win piles
        if(cardObserved.getSuit() == "Clubs") {
            cardNeededInWinPile.setSuit("Clubs");
        }
        else if(cardObserved.getSuit() == "Spades") {
            cardNeededInWinPile.setSuit("Spades");
        }
        else if(cardObserved.getSuit() == "Hearts") {
            cardNeededInWinPile.setSuit("Hearts");
        }
        else if(cardObserved.getSuit() == "Diamonds") {
            cardNeededInWinPile.setSuit("Diamonds");
        }

        //determines the values for main piles
        if(cardObserved2.getValue() == "Two") {              
            cardNeededInPile1.setValue("Three");
            cardNeededInPile2.setValue("Three");
        }
        else if(cardObserved2.getValue() == "Three") {              
            cardNeededInPile1.setValue("Four");
            cardNeededInPile2.setValue("Four");
        }
        else if(cardObserved2.getValue() == "Four") {           
            cardNeededInPile1.setValue("Five");
            cardNeededInPile2.setValue("Five");
        }
        else if(cardObserved2.getValue() == "Five") {              
            cardNeededInPile1.setValue("Six");
            cardNeededInPile2.setValue("Six");
        }
        else if(cardObserved2.getValue() == "Six") {              
            cardNeededInPile1.setValue("Seven");
            cardNeededInPile2.setValue("Seven");
        }
        else if(cardObserved2.getValue() == "Seven") {              
           cardNeededInPile1.setValue("Eight");
           cardNeededInPile2.setValue("Eight");
        }
        else if(cardObserved2.getValue() == "Eight") {              
            cardNeededInPile1.setValue("Nine");
            cardNeededInPile2.setValue("Nine");
        }
        else if(cardObserved2.getValue() == "Nine") {              
            cardNeededInPile1.setValue("Ten");
            cardNeededInPile2.setValue("Ten");
        }
        else if(cardObserved2.getValue() == "Ten") {              
            cardNeededInPile1.setValue("Jack");
            cardNeededInPile2.setValue("Jack");
        }
        else if(cardObserved2.getValue() == "Jack") {              
            cardNeededInPile1.setValue("Queen");
            cardNeededInPile2.setValue("Queen");
        }
        else if(cardObserved2.getValue() == "Queen") {              
            cardNeededInPile1.setValue("King");
            cardNeededInPile2.setValue("King");
        }

        //determines the suits for main piles
        if(cardObserved2.getSuit() == "Clubs") {
            cardNeededInPile1.setSuit("Hearts");
            cardNeededInPile2.setSuit("Diamonds");
        }
        else if(cardObserved2.getSuit() == "Spades") {
            cardNeededInPile1.setSuit("Hearts");
            cardNeededInPile2.setSuit("Diamonds");
        }
        else if(cardObserved2.getSuit() == "Hearts") {
            cardNeededInPile1.setSuit("Clubs");
            cardNeededInPile2.setSuit("Spades");
        }
        else if(cardObserved2.getSuit() == "Diamonds") {
            cardNeededInPile1.setSuit("Clubs");
            cardNeededInPile2.setSuit("Spades");
        }
    }
    
    //to avoid error in move detection, we must determine which pile the observe pile is.
    bool isPile1 = false;
    bool isPile2 = false;
    bool isPile3 = false;
    bool isPile4 = false;
    bool isPile5 = false;
    bool isPile6 = false;
    bool isPile7 = false;

    //we do this by using the string that is sent called "sentPileName"
    if(sentPileName == "pile1")
        isPile1 = true;
    else if(sentPileName == "pile2")
        isPile2 = true;
    else if(sentPileName == "pile3")
        isPile3 = true;
    else if(sentPileName == "pile4")
        isPile4 = true;
    else if(sentPileName == "pile5")
        isPile5 = true;
    else if(sentPileName == "pile6")
        isPile6 = true;
    else if(sentPileName == "pile7")
        isPile7 = true;

    //checks to see if the card can be moved to another of the 7 main piles
    if(pile1.empty() == false && !isPile1 && ((pile1.top().getSuit() == cardNeededInPile1.getSuit() && pile1.top().getValue() == cardNeededInPile1.getValue()) || (pile1.top().getSuit() == cardNeededInPile2.getSuit() && pile1.top().getValue() == cardNeededInPile2.getValue()))) {
        //cout << "A card can be placed onto pile 1" << endl;
        toPile1 = true;
        possibleMoves++;
    }
    if(pile2.empty() == false && !isPile2 && ((pile2.top().getSuit() == cardNeededInPile1.getSuit() && pile2.top().getValue() == cardNeededInPile1.getValue()) || (pile2.top().getSuit() == cardNeededInPile2.getSuit() && pile2.top().getValue() == cardNeededInPile2.getValue()))) {
        //cout << "A card can be placed onto pile 2" << endl;
        toPile2 = true;
        possibleMoves++;
    }
    if(pile3.empty() == false && !isPile3 && ((pile3.top().getSuit() == cardNeededInPile1.getSuit() && pile3.top().getValue() == cardNeededInPile1.getValue()) || (pile3.top().getSuit() == cardNeededInPile2.getSuit() && pile3.top().getValue() == cardNeededInPile2.getValue()))) {
        //cout << "A card can be placed onto pile 3" << endl;
        toPile3 = true;
        possibleMoves++;
    }
    if(pile4.empty() == false && !isPile4 && ((pile4.top().getSuit() == cardNeededInPile1.getSuit() && pile4.top().getValue() == cardNeededInPile1.getValue()) || (pile4.top().getSuit() == cardNeededInPile2.getSuit() && pile4.top().getValue() == cardNeededInPile2.getValue()))) {
        //cout << "A card can be placed onto pile 4" << endl;
        toPile4 = true;
        possibleMoves++;
    }
    if(pile5.empty() == false && !isPile5 && ((pile5.top().getSuit() == cardNeededInPile1.getSuit() && pile5.top().getValue() == cardNeededInPile1.getValue()) || (pile5.top().getSuit() == cardNeededInPile2.getSuit() && pile5.top().getValue() == cardNeededInPile2.getValue()))) {
        //cout << "A card can be placed onto pile 5" << endl;
        toPile5 = true;
        possibleMoves++;
    }
    if(pile6.empty() == false && !isPile6 && ((pile6.top().getSuit() == cardNeededInPile1.getSuit() && pile6.top().getValue() == cardNeededInPile1.getValue()) || (pile6.top().getSuit() == cardNeededInPile2.getSuit() && pile6.top().getValue() == cardNeededInPile2.getValue()))) {
        //cout << "A card can be placed onto pile 6" << endl;
        toPile6 = true;
        possibleMoves++;
    }
    if(pile7.empty() == false && !isPile7 && ((pile7.top().getSuit() == cardNeededInPile1.getSuit() && pile7.top().getValue() == cardNeededInPile1.getValue()) || (pile7.top().getSuit() == cardNeededInPile2.getSuit() && pile7.top().getValue() == cardNeededInPile2.getValue()))) {
        //cout << "A card can be placed onto pile 7" << endl;
        toPile7 = true;
        possibleMoves++;
    }

    //checks to see if the card can be moved to a win pile
    if(win1.top().getSuit() == cardNeededInWinPile.getSuit() && win1.top().getValue() == cardNeededInWinPile.getValue()) {
        //cout << "A card can be placed onto a WIN PILE!" << endl;
        toWin1 = true;
        possibleMoves++;
    }
    if(win2.top().getSuit() == cardNeededInWinPile.getSuit() && win2.top().getValue() == cardNeededInWinPile.getValue()) {
        //cout << "A card can be placed onto a WIN PILE!" << endl;
        toWin2 = true;
        possibleMoves++;
    }
    if(win3.top().getSuit() == cardNeededInWinPile.getSuit() && win3.top().getValue() == cardNeededInWinPile.getValue()) {
        //cout << "A card can be placed onto a WIN PILE!" << endl;
        toWin3 = true;
        possibleMoves++;
    }
    if(win4.top().getSuit() == cardNeededInWinPile.getSuit() && win4.top().getValue() == cardNeededInWinPile.getValue()) {
        //cout << "A card can be placed onto a WIN PILE!" << endl;
        toWin4 = true;
        possibleMoves++;
    }
}

//based on the current state of the board, updates the possibleMoves variable. possible moves consist of moving a king to a blank pile, moving a card from the hand or other main piles to another main pile, or moving a card from the hand or other main piles to one of the win piles
void checkMoves(stack<Card> pile1, stack<Card> pile2, stack<Card> pile3, stack<Card> pile4, stack<Card> pile5, stack<Card> pile6, stack<Card> pile7, stack<Card> win1, stack<Card> win2, stack<Card> win3, stack<Card> win4, stack<Card> hand, int &filledWinPiles, int &possibleMoves) {
    
    int kingCount = 0;                              //counts the number of visible kings at the start of a turn
    int emptyPiles = 0;                             //counts the number of empty piles at the start of a turn

    //temporary stacks used to reverse the order of each pile
    stack<Card> temp1;                      
    stack<Card> temp2;
    stack<Card> temp3;
    stack<Card> temp4;
    stack<Card> temp5;
    stack<Card> temp6;
    stack<Card> temp7;

    //7 loops that make temp stacks the reverse order of the piles
    while(pile1.empty() == false) {         
        temp1.push(pile1.top());
        pile1.pop();
    }
    while(pile2.empty() == false) {
        temp2.push(pile2.top());
        pile2.pop();
    }
    while(pile3.empty() == false) {
        temp3.push(pile3.top());
        pile3.pop();
    }
    while(pile4.empty() == false) {
        temp4.push(pile4.top());
        pile4.pop();
    }
    while(pile5.empty() == false) {
        temp5.push(pile5.top());
        pile5.pop();
    }
    while(pile6.empty() == false) {
        temp6.push(pile6.top());
        pile6.pop();
    }
    while(pile7.empty() == false) {
        temp7.push(pile7.top());
        pile7.pop();
    }

    //reassign each pile, now in their proper reversed order
    pile1 = temp1;                          
    pile2 = temp2;
    pile3 = temp3;
    pile4 = temp4;
    pile5 = temp5;
    pile6 = temp6;
    pile7 = temp7;

    //updates the number of kings that are visible from top and deepest of the main 7 piles and the hand
    if(pile1.empty() == false && (deepestVisible(pile1).getValue() == "King")) {
        if(deepestCard(pile1).isMasked())
            kingCount++;
    }
    if(pile2.empty() == false && (deepestVisible(pile2).getValue() == "King")) {
        if(deepestCard(pile2).isMasked())
            kingCount++;
    }
    if(pile3.empty() == false && (deepestVisible(pile3).getValue() == "King")) {
        if(deepestCard(pile3).isMasked())
            kingCount++;
    }
    if(pile4.empty() == false && (deepestVisible(pile4).getValue() == "King")) {
        if(deepestCard(pile4).isMasked())
            kingCount++;
    }
    if(pile5.empty() == false && (deepestVisible(pile5).getValue() == "King")) {
        if(deepestCard(pile5).isMasked())
            kingCount++;
    }
    if(pile6.empty() == false && (deepestVisible(pile6).getValue() == "King")) {
        if(deepestCard(pile6).isMasked())
            kingCount++;
    }
    if(pile7.empty() == false && (deepestVisible(pile7).getValue() == "King")) {
        if(deepestCard(pile7).isMasked())
            kingCount++;
    }
    if(hand.empty() == false && hand.top().getValue() == "King") {
        kingCount++;
    }

    //updates the number of piles that are empty out of the main 7
    if(pile1.empty()) {                                                        
        emptyPiles++;
    }
    if(pile2.empty()) {         
        emptyPiles++;
    }
    if(pile3.empty()) {         
        emptyPiles++;
    }
    if(pile4.empty()) {         
        emptyPiles++;
    }
    if(pile5.empty()) {         
        emptyPiles++;
    }
    if(pile6.empty()) {                 
        emptyPiles++;
    }
    if(pile7.empty()) {         
        emptyPiles++;
    }
    
    //updates the number of win piles that are filled
    if(win1.top().getValue() == "King") {
        filledWinPiles++;
    }
    if(win2.top().getValue() == "King") {
        filledWinPiles++;
    }
    if(win3.top().getValue() == "King") {
        filledWinPiles++;
    }
    if(win4.top().getValue() == "King") {
        filledWinPiles++;
    }

    //updates possibleMoves based on kings and empty piles
    if(kingCount > 0 && emptyPiles > 0) {
        
        possibleMoves += kingCount;
        
        //sends a message if a king can be moved onto an empty pile
        for(int i = 0; i < kingCount; i++) {
            //cout << "A King can be placed onto an empty pile!" << endl;
        }
    }

    //checks the top card of each of the 7 main piles to see if any of them has a move available
    checkPileOrHand(pile1, pile2, pile3, pile4, pile5, pile6, pile7, pile1, "pile1", true, win1, win2, win3, win4, possibleMoves);
    checkPileOrHand(pile1, pile2, pile3, pile4, pile5, pile6, pile7, pile2, "pile2", true, win1, win2, win3, win4, possibleMoves);
    checkPileOrHand(pile1, pile2, pile3, pile4, pile5, pile6, pile7, pile3, "pile3", true, win1, win2, win3, win4, possibleMoves);
    checkPileOrHand(pile1, pile2, pile3, pile4, pile5, pile6, pile7, pile4, "pile4", true, win1, win2, win3, win4, possibleMoves);
    checkPileOrHand(pile1, pile2, pile3, pile4, pile5, pile6, pile7, pile5, "pile5", true, win1, win2, win3, win4, possibleMoves);
    checkPileOrHand(pile1, pile2, pile3, pile4, pile5, pile6, pile7, pile6, "pile6", true, win1, win2, win3, win4, possibleMoves);
    checkPileOrHand(pile1, pile2, pile3, pile4, pile5, pile6, pile7, pile7, "pile7", true, win1, win2, win3, win4, possibleMoves);                                             

    checkPileOrHand(pile1, pile2, pile3, pile4, pile5, pile6, pile7, hand, "hand", false, win1, win2, win3, win4, possibleMoves);
}

//helper function for moveStack that reveals the top card of each stack of the main 7 piles
void flipNewCards(stack<Card> &pile1, stack<Card> &pile2, stack<Card> &pile3, stack<Card> &pile4, stack<Card> &pile5, stack<Card> &pile6, stack<Card> &pile7) {

    //needed to prevent alteration of our referenced variables
    stack<Card> copyPile1 = pile1;
    stack<Card> copyPile2 = pile2;
    stack<Card> copyPile3 = pile3;
    stack<Card> copyPile4 = pile4;
    stack<Card> copyPile5 = pile5;
    stack<Card> copyPile6 = pile6;
    stack<Card> copyPile7 = pile7;

    //needed to reverse each of the main piles
    stack<Card> newPile1;
    stack<Card> newPile2;
    stack<Card> newPile3;
    stack<Card> newPile4;
    stack<Card> newPile5;
    stack<Card> newPile6;
    stack<Card> newPile7;

    //blank stack to clear out the referenced main piles
    stack<Card> blankStack;

    //while loops to reverse the piles
    while(copyPile1.empty() == false) {
        newPile1.push(copyPile1.top());
        copyPile1.pop();
    }
    while(copyPile2.empty() == false) {
        newPile2.push(copyPile2.top());
        copyPile2.pop();
    }
    while(copyPile3.empty() == false) {
        newPile3.push(copyPile3.top());
        copyPile3.pop();
    }
    while(copyPile4.empty() == false) {
        newPile4.push(copyPile4.top());
        copyPile4.pop();
    }
    while(copyPile5.empty() == false) {
        newPile5.push(copyPile5.top());
        copyPile5.pop();
    }
    while(copyPile6.empty() == false) {
        newPile6.push(copyPile6.top());
        copyPile6.pop();
    }
    while(copyPile7.empty() == false) {
        newPile7.push(copyPile7.top());
        copyPile7.pop();
    }

    //flips to top card of each if needed
    if(newPile1.empty() == false && newPile1.top().isMasked())
        newPile1.top().unmaskCard();
    if(newPile2.empty() == false && newPile2.top().isMasked())
        newPile2.top().unmaskCard();
    if(newPile3.empty() == false && newPile3.top().isMasked())
        newPile3.top().unmaskCard();
    if(newPile4.empty() == false && newPile4.top().isMasked())
        newPile4.top().unmaskCard();
    if(newPile5.empty() == false && newPile5.top().isMasked())
        newPile5.top().unmaskCard();
    if(newPile6.empty() == false && newPile6.top().isMasked())
        newPile6.top().unmaskCard();
    if(newPile7.empty() == false && newPile7.top().isMasked())
        newPile7.top().unmaskCard();
    
    //blanks out each of the main 7 piles
    pile1 = blankStack;
    pile2 = blankStack;
    pile3 = blankStack;
    pile4 = blankStack;
    pile5 = blankStack;
    pile6 = blankStack;
    pile7 = blankStack;

    //rereverses the order of the copy piles back into their original piles, so that the bottom card will now be unmasked
    while(newPile1.empty() == false) {
        pile1.push(newPile1.top());
        newPile1.pop();
    }
    while(newPile3.empty() == false) {
        pile3.push(newPile3.top());
        newPile3.pop();
    }
    while(newPile2.empty() == false) {
        pile2.push(newPile2.top());
        newPile2.pop();
    }
    while(newPile4.empty() == false) {
        pile4.push(newPile4.top());
        newPile4.pop();
    }
    while(newPile5.empty() == false) {
        pile5.push(newPile5.top());
        newPile5.pop();
    }
    while(newPile6.empty() == false) {
        pile6.push(newPile6.top());
        newPile6.pop();
    }
    while(newPile7.empty() == false) {
        pile7.push(newPile7.top());
        newPile7.pop();
    }
}

//moves a stack of cards from 1 - 12 to either a win pile or another main pile
void moveStack(stack<Card> &source, stack<Card> &destination, stack<Card> &pile1, stack<Card> &pile2, stack<Card> &pile3, stack<Card> &pile4, stack<Card> &pile5, stack<Card> &pile6, stack<Card> &pile7) {
    
    //temp source so that the original reference is not messed up
    stack<Card> tempSource = source;

    //counts that will determine how many pops are needed to clear the moved cards from the source
    int maskedCount = 0;
    int unmaskedCount;
    
    //the new source stack without masked cards
    stack<Card> newSource;
    
    //the new, correctly reversed order of the destination stack
    stack<Card> newDestination;

    //the reversed order stack of the source
    stack<Card> reversedSource;

    //creates a new source stack from only the visible cards
    while(tempSource.top().isMasked()) {
        tempSource.pop();
        maskedCount++;
    }
    
    newSource = tempSource;
    
    //reverses the order of the destination stack to be in its proper order
    while(destination.empty() == false) {         
        newDestination.push(destination.top());
        destination.pop();
    }

    //moves all of the visible cards from the source to the destination
    while(newSource.empty() == false) {
        newDestination.push(newSource.top());
        newSource.pop();
    }

    //rereverses the order of the destination stack
    stack<Card> correctDestination;
    while(newDestination.empty() == false) {
        correctDestination.push(newDestination.top());
        newDestination.pop();
    }

    //this is the number of moved cards that must be popped from the source stack
    unmaskedCount = source.size() - maskedCount;

    //reverses the order of the original source
    while(source.empty() == false) {
        reversedSource.push(source.top());
        source.pop();
    }
    source = reversedSource;

    //pops the appropriate number of moved cards from the top of the reversed source stack
    for(int i = unmaskedCount; i > 0; i--) {
        reversedSource.pop();
    }

    stack<Card> finalSource;

    //rereverses the reversedSource back to its proper order
    while(reversedSource.empty() == false) {
        finalSource.push(reversedSource.top());
        reversedSource.pop();
    }
    
    //reassigns the reference to the source to the newly updated stack
    source = finalSource;

    //reassigns the reference to the destination to the newly updated stack
    destination = correctDestination;

    //flip new cards based on the move that was made
    flipNewCards(pile1, pile2, pile3, pile4, pile5, pile6, pile7);
}   

//moves the top card of a hand to either a win pile or another main pile
void moveHand(stack<Card> &hand, stack<Card> &destination, bool isMainPile, stack<Card> &pile1, stack<Card> &pile2, stack<Card> &pile3, stack<Card> &pile4, stack<Card> &pile5, stack<Card> &pile6, stack<Card> &pile7) {

    //if the hand is going right to the win pile...
    if(!isMainPile) {
        destination.push(hand.top());
        hand.pop();
    }
    
    //if the hand is going to a main pile...
    else {

        //we have to reverse the destination pile
        stack<Card> temp;
        while(destination.empty() == false) {
            temp.push(destination.top());
            destination.pop();
        }
        destination = temp;

        //then we can push the card onto the pile
        destination.push(hand.top());
        hand.pop();

        //then, rereverse the destination stack
        stack<Card> temp2;
        while(destination.empty() == false) {
            temp2.push(destination.top());
            destination.pop();
        }
        destination = temp2;
    }

}

//moves one card from the top of a main pile to one of the win piles
void mainToWin(stack<Card> &source, stack<Card> &destination, stack<Card> &pile1, stack<Card> &pile2, stack<Card> &pile3, stack<Card> &pile4, stack<Card> &pile5, stack<Card> &pile6, stack<Card> &pile7) {
    
    //first must reverse the order of the source pile
    stack<Card> temp;
    while(source.empty() == false) {
        temp.push(source.top());
        source.pop();
    }
    source = temp;

    //simply pops the top card from the main pile and pushes it onto the win pile
    destination.push(source.top());
    source.pop();

    //rereverses the source stack so that it is back to normal
    stack<Card> temp2;
    while(source.empty() == false) {
        temp2.push(source.top());
        source.pop();
    }
    source = temp2;
    
    //flip new cards based on the move that was made
    flipNewCards(pile1, pile2, pile3, pile4, pile5, pile6, pile7);
}

//deals 3 new cards from the remaining deck into the hand
void dealNewCards(stack<Card> &hand, Deck &deck) {

    //used to store cards that will be reversed into the hand
    stack<Card> firstStack;            

    //if the deck is empty upon requesting new cards, the hand must be transfered back to the deck
    if(deck.getSize() == 0) {
        //cout << "Refilling deck from hand..." << endl;
        timesRefilled += 1;
        deckRefilled = true;

        //used to reverse the hand before putting it back in the deck 
        stack<Card> temp;
        while(hand.empty() == false) {
            temp.push(hand.top());
            hand.pop();
        }

        //adds the reversed stack back to the deck
        while(temp.empty() == false) {
            deck.addCard(temp.top());
            temp.pop();
        }
    }

    //puts the top 3 cards of the deck into firstStack, or less if the deck is not divisible by 3
    for(int i = 0; i < 3 && deck.getSize() != 0; i++) {
        firstStack.push(deck.dealCard());
    }

    //empties firstStack by pushing the cards into the hand
    while(firstStack.empty() == false) {
        hand.push(firstStack.top());
        firstStack.pop();
    }
}

//verifies the requested move when the player wants to move a stack from one pile to another
bool verifyMove(stack<Card> &pile1, stack<Card> &pile2, stack<Card> &pile3, stack<Card> &pile4, stack<Card> &pile5, stack<Card> &pile6, stack<Card> &pile7, stack<Card> &win1, stack<Card> &win2, stack<Card> &win3, stack<Card> &win4, stack<Card> &hand, string sourceCard, string destinationCard, int &possibleMoves) {
    
    bool deep = false;
    bool shallow = false;
    bool sr1 = false;
    bool sr2 = false;
    bool sr3 = false;
    bool sr4 = false;
    bool sr5 = false;
    bool sr6 = false;
    bool sr7 = false;
    bool srh = false;

    bool tom1 = false;
    bool tom2 = false;
    bool tom3 = false;
    bool tom4 = false;
    bool tom5 = false;
    bool tom6 = false;
    bool tom7 = false;
    bool tow1 = false;
    bool tow2 = false;
    bool tow3 = false;
    bool tow4 = false;

    //must reverse each of the main piles
    stack<Card> temp1;
    while(pile1.empty() == false) {
        temp1.push(pile1.top());
        pile1.pop();
    }
    pile1 = temp1;
    
    stack<Card> temp2;
    while(pile2.empty() == false) {
        temp2.push(pile2.top());
        pile2.pop();
    }
    pile2 = temp2;
    
    stack<Card> temp3;
    while(pile3.empty() == false) {
        temp3.push(pile3.top());
        pile3.pop();
    }
    pile3 = temp3;
    
    stack<Card> temp4;
    while(pile4.empty() == false) {
        temp4.push(pile4.top());
        pile4.pop();
    }
    pile4 = temp4;
    
    stack<Card> temp5;
    while(pile5.empty() == false) {
        temp5.push(pile5.top());
        pile5.pop();
    }
    pile5 = temp5;
    
    stack<Card> temp6;
    while(pile6.empty() == false) {
        temp6.push(pile6.top());
        pile6.pop();
    }
    pile6 = temp6;
    
    stack<Card> temp7;
    while(pile7.empty() == false) {
        temp7.push(pile7.top());
        pile7.pop();
    }
    pile7 = temp7;

    //if there are no possible moves
    if(possibleMoves < 1) {
        noMoves = true;

        //must reverse each of the main piles
        stack<Card> temp12;
        while(pile1.empty() == false) {
            temp12.push(pile1.top());
            pile1.pop();
        }
        pile1 = temp12;
        
        stack<Card> temp22;
        while(pile2.empty() == false) {
            temp22.push(pile2.top());
            pile2.pop();
        }
        pile2 = temp22;
        
        stack<Card> temp32;
        while(pile3.empty() == false) {
            temp32.push(pile3.top());
            pile3.pop();
        }
        pile3 = temp32;
        
        stack<Card> temp42;
        while(pile4.empty() == false) {
            temp42.push(pile4.top());
            pile4.pop();
        }
        pile4 = temp42;
        
        stack<Card> temp52;
        while(pile5.empty() == false) {
            temp52.push(pile5.top());
            pile5.pop();
        }
        pile5 = temp52;
        
        stack<Card> temp62;
        while(pile6.empty() == false) {
            temp62.push(pile6.top());
            pile6.pop();
        }
        pile6 = temp62;
        
        stack<Card> temp72;
        while(pile7.empty() == false) {
            temp72.push(pile7.top());
            pile7.pop();
        }
        pile7 = temp72;
        
        return false;
    
    }

    //determines if the source card is deep, and which pile it is in
    if(pile1.empty() == false && deepestVisible(pile1).returnMini() == sourceCard) {
        deep = true;
        sr1 = true;
    }
    else if(pile2.empty() == false && deepestVisible(pile2).returnMini() == sourceCard) {
        deep = true;
        sr2 = true;
    }
    else if(pile3.empty() == false && deepestVisible(pile3).returnMini() == sourceCard) {
        deep = true;
        sr3 = true;
    }
    else if(pile4.empty() == false && deepestVisible(pile4).returnMini() == sourceCard) {
        deep = true;
        sr4 = true;
    }
    else if(pile5.empty() == false && deepestVisible(pile5).returnMini() == sourceCard) {
        deep = true;
        sr5 = true;
    }
    else if(pile6.empty() == false && deepestVisible(pile6).returnMini() == sourceCard) {
        deep = true;
        sr6 = true;
    }
    else if(pile7.empty() == false && deepestVisible(pile7).returnMini() == sourceCard) {
        deep = true;
        sr7 = true;
    }

    //determines if the source card is shallow, and which pile it is in
    if(pile1.empty() == false && pile1.top().returnMini() == sourceCard) {
        shallow = true;
        sr1 = true;
    }
    else if(pile2.empty() == false && pile2.top().returnMini() == sourceCard) {
        shallow = true;
        sr2 = true;
    }
    else if(pile3.empty() == false && pile3.top().returnMini() == sourceCard) {
        shallow = true;
        sr3 = true;
    }
    else if(pile4.empty() == false && pile4.top().returnMini() == sourceCard) {
        shallow = true;
        sr4 = true;
    }
    else if(pile5.empty() == false && pile5.top().returnMini() == sourceCard) {
        shallow = true;
        sr5 = true;
    }
    else if(pile6.empty() == false && pile6.top().returnMini() == sourceCard) {
        shallow = true;
        sr6 = true;
    }
    else if(pile7.empty() == false && pile7.top().returnMini() == sourceCard) {
        shallow = true;
        sr7 = true;
    }

    //determines if the source card is in the hand
    if(hand.empty() == false && hand.top().returnMini() == sourceCard) {
        srh = true;
    }

    //determines which pile has the destination card in it
    if(pile1.empty() == false && pile1.top().returnMini() == destinationCard) {
        tom1 = true;
    }
    else if(pile2.empty() == false && pile2.top().returnMini() == destinationCard) {
        tom2 = true;
    }
    else if(pile3.empty() == false && pile3.top().returnMini() == destinationCard) {
        tom3 = true;
    }
    else if(pile4.empty() == false && pile4.top().returnMini() == destinationCard) {
        tom4 = true;
    }
    else if(pile5.empty() == false && pile5.top().returnMini() == destinationCard) {
        tom5 = true;
    }
    else if(pile6.empty() == false && pile6.top().returnMini() == destinationCard) {
        tom6 = true;
    }
    else if(pile7.empty() == false && pile7.top().returnMini() == destinationCard) {
        tom7 = true;
    }
    else if(win1.empty() == false && win1.top().returnMini() == destinationCard) {
        tow1 = true;
    }
    else if(win2.empty() == false && win2.top().returnMini() == destinationCard) {
        tow2 = true;
    }
    else if(win3.empty() == false && win3.top().returnMini() == destinationCard) {
        tow3 = true;
    }
    else if(win4.empty() == false && win4.top().returnMini() == destinationCard) {
        tow4 = true;
    }

    //once we know what the user has requested to move, we can check and see if it is a possible move.
    if(sr1) {
        
        //we will check pile1 to see all of its possible moves. It will update global variables to see where pile1 can go
        checkPileOrHand(pile1, pile2, pile3, pile4, pile5, pile6, pile7, pile1, "pile1", true, win1, win2, win3, win4, possibleMoves);

        bool kingMove;
        if(pile1.empty() == false && deepestVisible(pile1).getValue() == "King" && sourceCard.at(0) == 'K')
            kingMove = true;

        //must reverse each of the main piles
        stack<Card> temp12;
        while(pile1.empty() == false) {
            temp12.push(pile1.top());
            pile1.pop();
        }
        pile1 = temp12;
        
        stack<Card> temp22;
        while(pile2.empty() == false) {
            temp22.push(pile2.top());
            pile2.pop();
        }
        pile2 = temp22;
        
        stack<Card> temp32;
        while(pile3.empty() == false) {
            temp32.push(pile3.top());
            pile3.pop();
        }
        pile3 = temp32;
        
        stack<Card> temp42;
        while(pile4.empty() == false) {
            temp42.push(pile4.top());
            pile4.pop();
        }
        pile4 = temp42;
        
        stack<Card> temp52;
        while(pile5.empty() == false) {
            temp52.push(pile5.top());
            pile5.pop();
        }
        pile5 = temp52;
        
        stack<Card> temp62;
        while(pile6.empty() == false) {
            temp62.push(pile6.top());
            pile6.pop();
        }
        pile6 = temp62;
        
        stack<Card> temp72;
        while(pile7.empty() == false) {
            temp72.push(pile7.top());
            pile7.pop();
        }
        pile7 = temp72;

        //if the deepest visible card of the pile is a king...
        if(kingMove) {

            if(destinationCard == "2" && pile2.empty()) {
                moveStack(pile1, pile2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "3"  && pile3.empty()) {
                moveStack(pile1, pile3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "4"  && pile4.empty()) {
                moveStack(pile1, pile4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "5"  && pile5.empty()) {
                moveStack(pile1, pile5, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "6"  && pile6.empty()) {
                moveStack(pile1, pile6, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "7"  && pile7.empty()) {
                moveStack(pile1, pile7, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
        }

        //now we will see if the destination requested is a possible move
        if(tom2 && toPile2 && deep) {
            moveStack(pile1, pile2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tom3 && toPile3 && deep) {
            moveStack(pile1, pile3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom4 && toPile4 && deep) {
            moveStack(pile1, pile4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom5 && toPile5 && deep) {
            moveStack(pile1, pile5, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom6 && toPile6 && deep) {
            moveStack(pile1, pile6, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom7 && toPile7 && deep) {
            moveStack(pile1, pile7, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tow1 && toWin1 && shallow) {
            mainToWin(pile1, win1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow2 && toWin2 && shallow) {
            mainToWin(pile1, win2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow3 && toWin3 && shallow) {
            mainToWin(pile1, win3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow4 && toWin4 && shallow) {
            mainToWin(pile1, win4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else {
            wrongMove = true;
            return false;
        }
    }

    if(sr2) {
        
        //we will check the pile to see all of its possible moves. It will update global variables to see where the pile can go
        checkPileOrHand(pile1, pile2, pile3, pile4, pile5, pile6, pile7, pile2, "pile2", true, win1, win2, win3, win4, possibleMoves);

        bool kingMove;
        if(pile2.empty() == false && deepestVisible(pile2).getValue() == "King" && sourceCard.at(0) == 'K')
            kingMove = true;

        //must reverse each of the main piles
        stack<Card> temp12;
        while(pile1.empty() == false) {
            temp12.push(pile1.top());
            pile1.pop();
        }
        pile1 = temp12;
        
        stack<Card> temp22;
        while(pile2.empty() == false) {
            temp22.push(pile2.top());
            pile2.pop();
        }
        pile2 = temp22;
        
        stack<Card> temp32;
        while(pile3.empty() == false) {
            temp32.push(pile3.top());
            pile3.pop();
        }
        pile3 = temp32;
        
        stack<Card> temp42;
        while(pile4.empty() == false) {
            temp42.push(pile4.top());
            pile4.pop();
        }
        pile4 = temp42;
        
        stack<Card> temp52;
        while(pile5.empty() == false) {
            temp52.push(pile5.top());
            pile5.pop();
        }
        pile5 = temp52;
        
        stack<Card> temp62;
        while(pile6.empty() == false) {
            temp62.push(pile6.top());
            pile6.pop();
        }
        pile6 = temp62;
        
        stack<Card> temp72;
        while(pile7.empty() == false) {
            temp72.push(pile7.top());
            pile7.pop();
        }
        pile7 = temp72;

        //if the deepest visible card of the pile is a king...
        if(kingMove) {
            if(destinationCard == "1" && pile1.empty()) {
                moveStack(pile2, pile1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "3"  && pile3.empty()) {
                moveStack(pile2, pile3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "4"  && pile4.empty()) {
                moveStack(pile2, pile4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "5"  && pile5.empty()) {
                moveStack(pile2, pile5, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "6"  && pile6.empty()) {
                moveStack(pile2, pile6, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "7"  && pile7.empty()) {
                moveStack(pile2, pile7, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
        }

        //now we will see if the destination requested is a possible move
        if(tom1 && toPile1 && deep) {
            moveStack(pile2, pile1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tom3 && toPile3 && deep) {
            moveStack(pile2, pile3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom4 && toPile4 && deep) {
            moveStack(pile2, pile4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom5 && toPile5 && deep) {
            moveStack(pile2, pile5, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom6 && toPile6 && deep) {
            moveStack(pile2, pile6, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom7 && toPile7 && deep) {
            moveStack(pile2, pile7, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tow1 && toWin1 && shallow) {
            mainToWin(pile2, win1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow2 && toWin2 && shallow) {
            mainToWin(pile2, win2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow3 && toWin3 && shallow) {
            mainToWin(pile2, win3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow4 && toWin4 && shallow) {
            mainToWin(pile2, win4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else {
            wrongMove = true;
            return false;
        }
    }

    if(sr3) {
        
        //we will check the pile to see all of its possible moves. It will update global variables to see where the pile can go
        checkPileOrHand(pile1, pile2, pile3, pile4, pile5, pile6, pile7, pile3, "pile3", true, win1, win2, win3, win4, possibleMoves);

        bool kingMove;
        if(pile3.empty() == false && deepestVisible(pile3).getValue() == "King" && sourceCard.at(0) == 'K')
            kingMove = true;

        //must reverse each of the main piles
        stack<Card> temp12;
        while(pile1.empty() == false) {
            temp12.push(pile1.top());
            pile1.pop();
        }
        pile1 = temp12;
        
        stack<Card> temp22;
        while(pile2.empty() == false) {
            temp22.push(pile2.top());
            pile2.pop();
        }
        pile2 = temp22;
        
        stack<Card> temp32;
        while(pile3.empty() == false) {
            temp32.push(pile3.top());
            pile3.pop();
        }
        pile3 = temp32;
        
        stack<Card> temp42;
        while(pile4.empty() == false) {
            temp42.push(pile4.top());
            pile4.pop();
        }
        pile4 = temp42;
        
        stack<Card> temp52;
        while(pile5.empty() == false) {
            temp52.push(pile5.top());
            pile5.pop();
        }
        pile5 = temp52;
        
        stack<Card> temp62;
        while(pile6.empty() == false) {
            temp62.push(pile6.top());
            pile6.pop();
        }
        pile6 = temp62;
        
        stack<Card> temp72;
        while(pile7.empty() == false) {
            temp72.push(pile7.top());
            pile7.pop();
        }
        pile7 = temp72;

        //if the deepest visible card of the pile is a king...
        if(kingMove) {
            if(destinationCard == "2" && pile2.empty()) {
                moveStack(pile3, pile2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "1"  && pile1.empty()) {
                moveStack(pile3, pile1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "4"  && pile4.empty()) {
                moveStack(pile3, pile4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "5"  && pile5.empty()) {
                moveStack(pile3, pile5, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "6"  && pile6.empty()) {
                moveStack(pile3, pile6, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "7"  && pile7.empty()) {
                moveStack(pile3, pile7, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
        }

        //now we will see if the destination requested is a possible move
        if(tom1 && toPile1 && deep) {
            moveStack(pile3, pile1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tom2 && toPile2 && deep) {
            moveStack(pile3, pile2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom4 && toPile4 && deep) {
            moveStack(pile3, pile4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom5 && toPile5 && deep) {
            moveStack(pile3, pile5, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom6 && toPile6 && deep) {
            moveStack(pile3, pile6, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom7 && toPile7 && deep) {
            moveStack(pile3, pile7, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tow1 && toWin1 && shallow) {
            mainToWin(pile3, win1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow2 && toWin2 && shallow) {
            mainToWin(pile3, win2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow3 && toWin3 && shallow) {
            mainToWin(pile3, win3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow4 && toWin4 && shallow) {
            mainToWin(pile3, win4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else {
            wrongMove = true;
            return false;
        }
    }

    if(sr4) {
        
        //we will check the pile to see all of its possible moves. It will update global variables to see where the pile can go
        checkPileOrHand(pile1, pile2, pile3, pile4, pile5, pile6, pile7, pile4, "pile4", true, win1, win2, win3, win4, possibleMoves);

        bool kingMove;
        if(pile4.empty() == false && deepestVisible(pile4).getValue() == "King" && sourceCard.at(0) == 'K')
            kingMove = true;

        //must reverse each of the main piles
        stack<Card> temp12;
        while(pile1.empty() == false) {
            temp12.push(pile1.top());
            pile1.pop();
        }
        pile1 = temp12;
        
        stack<Card> temp22;
        while(pile2.empty() == false) {
            temp22.push(pile2.top());
            pile2.pop();
        }
        pile2 = temp22;
        
        stack<Card> temp32;
        while(pile3.empty() == false) {
            temp32.push(pile3.top());
            pile3.pop();
        }
        pile3 = temp32;
        
        stack<Card> temp42;
        while(pile4.empty() == false) {
            temp42.push(pile4.top());
            pile4.pop();
        }
        pile4 = temp42;
        
        stack<Card> temp52;
        while(pile5.empty() == false) {
            temp52.push(pile5.top());
            pile5.pop();
        }
        pile5 = temp52;
        
        stack<Card> temp62;
        while(pile6.empty() == false) {
            temp62.push(pile6.top());
            pile6.pop();
        }
        pile6 = temp62;
        
        stack<Card> temp72;
        while(pile7.empty() == false) {
            temp72.push(pile7.top());
            pile7.pop();
        }
        pile7 = temp72;

        //if the deepest visible card of the pile is a king...
        if(kingMove) {
            if(destinationCard == "2" && pile2.empty()) {
                moveStack(pile4, pile2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "3"  && pile3.empty()) {
                moveStack(pile4, pile3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "1"  && pile1.empty()) {
                moveStack(pile4, pile1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "5"  && pile5.empty()) {
                moveStack(pile4, pile5, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "6"  && pile6.empty()) {
                moveStack(pile4, pile6, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "7"  && pile7.empty()) {
                moveStack(pile4, pile7, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
        }

        //now we will see if the destination requested is a possible move
        if(tom1 && toPile1 && deep) {
            moveStack(pile4, pile1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tom2 && toPile2 && deep) {
            moveStack(pile4, pile2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom3 && toPile3 && deep) {
            moveStack(pile4, pile3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom5 && toPile5 && deep) {
            moveStack(pile4, pile5, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom6 && toPile6 && deep) {
            moveStack(pile4, pile6, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom7 && toPile7 && deep) {
            moveStack(pile4, pile7, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tow1 && toWin1 && shallow) {
            mainToWin(pile4, win1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow2 && toWin2 && shallow) {
            mainToWin(pile4, win2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow3 && toWin3 && shallow) {
            mainToWin(pile4, win3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow4 && toWin4 && shallow) {
            mainToWin(pile4, win4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else {
            wrongMove = true;
            return false;
        }
    }

    if(sr5) {
        
        //we will check the pile to see all of its possible moves. It will update global variables to see where the pile can go
        checkPileOrHand(pile1, pile2, pile3, pile4, pile5, pile6, pile7, pile5, "pile5", true, win1, win2, win3, win4, possibleMoves);

        bool kingMove;
        if(pile5.empty() == false && deepestVisible(pile5).getValue() == "King" && sourceCard.at(0) == 'K')
            kingMove = true;

        //must reverse each of the main piles
        stack<Card> temp12;
        while(pile1.empty() == false) {
            temp12.push(pile1.top());
            pile1.pop();
        }
        pile1 = temp12;
        
        stack<Card> temp22;
        while(pile2.empty() == false) {
            temp22.push(pile2.top());
            pile2.pop();
        }
        pile2 = temp22;
        
        stack<Card> temp32;
        while(pile3.empty() == false) {
            temp32.push(pile3.top());
            pile3.pop();
        }
        pile3 = temp32;
        
        stack<Card> temp42;
        while(pile4.empty() == false) {
            temp42.push(pile4.top());
            pile4.pop();
        }
        pile4 = temp42;
        
        stack<Card> temp52;
        while(pile5.empty() == false) {
            temp52.push(pile5.top());
            pile5.pop();
        }
        pile5 = temp52;
        
        stack<Card> temp62;
        while(pile6.empty() == false) {
            temp62.push(pile6.top());
            pile6.pop();
        }
        pile6 = temp62;
        
        stack<Card> temp72;
        while(pile7.empty() == false) {
            temp72.push(pile7.top());
            pile7.pop();
        }
        pile7 = temp72;

        //if the deepest visible card of the pile is a king...
        if(kingMove) {
            if(destinationCard == "2" && pile2.empty()) {
                moveStack(pile5, pile2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "3"  && pile3.empty()) {
                moveStack(pile5, pile3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "4"  && pile4.empty()) {
                moveStack(pile5, pile4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "1"  && pile1.empty()) {
                moveStack(pile5, pile1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "6"  && pile6.empty()) {
                moveStack(pile5, pile6, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "7"  && pile7.empty()) {
                moveStack(pile5, pile7, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
        }

        //now we will see if the destination requested is a possible move
        if(tom1 && toPile1 && deep) {
            moveStack(pile5, pile1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tom2 && toPile2 && deep) {
            moveStack(pile5, pile2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom3 && toPile3 && deep) {
            moveStack(pile5, pile3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom4 && toPile4 && deep) {
            moveStack(pile5, pile4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom6 && toPile6 && deep) {
            moveStack(pile5, pile6, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom7 && toPile7 && deep) {
            moveStack(pile5, pile7, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tow1 && toWin1 && shallow) {
            mainToWin(pile5, win1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow2 && toWin2 && shallow) {
            mainToWin(pile5, win2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow3 && toWin3 && shallow) {
            mainToWin(pile5, win3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow4 && toWin4 && shallow) {
            mainToWin(pile5, win4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else {
            wrongMove = true;
            return false;
        }
    }

    if(sr7) {
        
        //we will check the pile to see all of its possible moves. It will update global variables to see where the pile can go
        checkPileOrHand(pile1, pile2, pile3, pile4, pile5, pile6, pile7, pile7, "pile7", true, win1, win2, win3, win4, possibleMoves);

        bool kingMove;
        if(pile7.empty() == false && deepestVisible(pile7).getValue() == "King" && sourceCard.at(0) == 'K')
            kingMove = true;

        //must reverse each of the main piles
        stack<Card> temp12;
        while(pile1.empty() == false) {
            temp12.push(pile1.top());
            pile1.pop();
        }
        pile1 = temp12;
        
        stack<Card> temp22;
        while(pile2.empty() == false) {
            temp22.push(pile2.top());
            pile2.pop();
        }
        pile2 = temp22;
        
        stack<Card> temp32;
        while(pile3.empty() == false) {
            temp32.push(pile3.top());
            pile3.pop();
        }
        pile3 = temp32;
        
        stack<Card> temp42;
        while(pile4.empty() == false) {
            temp42.push(pile4.top());
            pile4.pop();
        }
        pile4 = temp42;
        
        stack<Card> temp52;
        while(pile5.empty() == false) {
            temp52.push(pile5.top());
            pile5.pop();
        }
        pile5 = temp52;
        
        stack<Card> temp62;
        while(pile6.empty() == false) {
            temp62.push(pile6.top());
            pile6.pop();
        }
        pile6 = temp62;
        
        stack<Card> temp72;
        while(pile7.empty() == false) {
            temp72.push(pile7.top());
            pile7.pop();
        }
        pile7 = temp72;

        //if the deepest visible card of the pile is a king...
        if(kingMove) {
            if(destinationCard == "2" && pile2.empty()) {
                moveStack(pile7, pile2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "3"  && pile3.empty()) {
                moveStack(pile7, pile3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "4"  && pile4.empty()) {
                moveStack(pile7, pile4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "5"  && pile5.empty()) {
                moveStack(pile7, pile5, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "6"  && pile6.empty()) {
                moveStack(pile7, pile6, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "1"  && pile1.empty()) {
                moveStack(pile7, pile1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
        }

        //now we will see if the destination requested is a possible move
        if(tom1 && toPile1 && deep) {
            moveStack(pile7, pile1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tom2 && toPile2 && deep) {
            moveStack(pile7, pile2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom3 && toPile3 && deep) {
            moveStack(pile7, pile3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom4 && toPile4 && deep) {
            moveStack(pile7, pile4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom5 && toPile5 && deep) {
            moveStack(pile7, pile5, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom6 && toPile6 && deep) {
            moveStack(pile7, pile6, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tow1 && toWin1 && shallow) {
            mainToWin(pile7, win1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow2 && toWin2 && shallow) {
            mainToWin(pile7, win2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow3 && toWin3 && shallow) {
            mainToWin(pile7, win3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow4 && toWin4 && shallow) {
            mainToWin(pile7, win4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else {
            wrongMove = true;
            return false;
        }
    }

    if(sr6) {
        
        //we will check the pile to see all of its possible moves. It will update global variables to see where the pile can go
        checkPileOrHand(pile1, pile2, pile3, pile4, pile5, pile6, pile7, pile6, "pile6", true, win1, win2, win3, win4, possibleMoves);

        bool kingMove;
        if(pile6.empty() == false && deepestVisible(pile6).getValue() == "King" && sourceCard.at(0) == 'K')
            kingMove = true;

        //must reverse each of the main piles
        stack<Card> temp12;
        while(pile1.empty() == false) {
            temp12.push(pile1.top());
            pile1.pop();
        }
        pile1 = temp12;
        
        stack<Card> temp22;
        while(pile2.empty() == false) {
            temp22.push(pile2.top());
            pile2.pop();
        }
        pile2 = temp22;
        
        stack<Card> temp32;
        while(pile3.empty() == false) {
            temp32.push(pile3.top());
            pile3.pop();
        }
        pile3 = temp32;
        
        stack<Card> temp42;
        while(pile4.empty() == false) {
            temp42.push(pile4.top());
            pile4.pop();
        }
        pile4 = temp42;
        
        stack<Card> temp52;
        while(pile5.empty() == false) {
            temp52.push(pile5.top());
            pile5.pop();
        }
        pile5 = temp52;
        
        stack<Card> temp62;
        while(pile6.empty() == false) {
            temp62.push(pile6.top());
            pile6.pop();
        }
        pile6 = temp62;
        
        stack<Card> temp72;
        while(pile7.empty() == false) {
            temp72.push(pile7.top());
            pile7.pop();
        }
        pile7 = temp72;

        //if the deepest visible card of the pile is a king...
        if(kingMove) {
            if(destinationCard == "2" && pile2.empty()) {
                moveStack(pile6, pile2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "3"  && pile3.empty()) {
                moveStack(pile6, pile3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "4"  && pile4.empty()) {
                moveStack(pile6, pile4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "5"  && pile5.empty()) {
                moveStack(pile6, pile5, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "1"  && pile1.empty()) {
                moveStack(pile6, pile1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "7"  && pile7.empty()) {
                moveStack(pile6, pile7, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
        }

        //now we will see if the destination requested is a possible move
        if(tom1 && toPile1 && deep) {
            moveStack(pile6, pile1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tom3 && toPile3 && deep) {
            moveStack(pile6, pile3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom4 && toPile4 && deep) {
            moveStack(pile6, pile4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom5 && toPile5 && deep) {
            moveStack(pile6, pile5, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom2 && toPile2 && deep) {
            moveStack(pile6, pile2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom7 && toPile7 && deep) {
            moveStack(pile6, pile7, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tow1 && toWin1 && shallow) {
            mainToWin(pile6, win1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow2 && toWin2 && shallow) {
            mainToWin(pile6, win2, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow3 && toWin3 && shallow) {
            mainToWin(pile6, win3, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow4 && toWin4 && shallow) {
            mainToWin(pile6, win4, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else {
            wrongMove = true;
            return false;
        }
    }

    if(srh) {
        
        //we will check the hand to see all of its possible moves. It will update global variables to see where the hand can go
        checkPileOrHand(pile1, pile2, pile3, pile4, pile5, pile6, pile7, hand, "hand", false, win1, win2, win3, win4, possibleMoves);

        //must reverse each of the main piles
        stack<Card> temp12;
        while(pile1.empty() == false) {
            temp12.push(pile1.top());
            pile1.pop();
        }
        pile1 = temp12;
        
        stack<Card> temp22;
        while(pile2.empty() == false) {
            temp22.push(pile2.top());
            pile2.pop();
        }
        pile2 = temp22;
        
        stack<Card> temp32;
        while(pile3.empty() == false) {
            temp32.push(pile3.top());
            pile3.pop();
        }
        pile3 = temp32;
        
        stack<Card> temp42;
        while(pile4.empty() == false) {
            temp42.push(pile4.top());
            pile4.pop();
        }
        pile4 = temp42;
        
        stack<Card> temp52;
        while(pile5.empty() == false) {
            temp52.push(pile5.top());
            pile5.pop();
        }
        pile5 = temp52;
        
        stack<Card> temp62;
        while(pile6.empty() == false) {
            temp62.push(pile6.top());
            pile6.pop();
        }
        pile6 = temp62;
        
        stack<Card> temp72;
        while(pile7.empty() == false) {
            temp72.push(pile7.top());
            pile7.pop();
        }
        pile7 = temp72;

        //if the top card of the hand is a king...
        if(hand.empty() == false && hand.top().getValue() == "King" && sourceCard.at(0) == 'K') {
            if(destinationCard == "2" && pile2.empty()) {
                moveHand(hand, pile2, true, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "3"  && pile3.empty()) {
                moveHand(hand, pile3, true, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "4"  && pile4.empty()) {
                moveHand(hand, pile4, true, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "5"  && pile5.empty()) {
                moveHand(hand, pile5, true, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "6"  && pile6.empty()) {
                moveHand(hand, pile6, true, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "7"  && pile7.empty()) {
                moveHand(hand, pile7, true, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
            else if(destinationCard == "1"  && pile1.empty()) {
                moveHand(hand, pile1, true, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
                return true;
            }
        }

        //now we will see if the destination requested is a possible move
        if(tom1 && toPile1) {
            moveHand(hand, pile1, true, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tom2 && toPile2) {
            moveHand(hand, pile2, true, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom4 && toPile4) {
            moveHand(hand, pile4, true, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tom5 && toPile5) {
            moveHand(hand, pile5, true, pile1, pile2, pile3, pile4, pile5, pile6, pile7);           
            return true;
        }
        else if(tom6 && toPile6) {
            moveHand(hand, pile6, true, pile1, pile2, pile3, pile4, pile5, pile6, pile7);           
            return true;
        }
        else if(tom7 && toPile7) {
            moveHand(hand, pile7, true, pile1, pile2, pile3, pile4, pile5, pile6, pile7);           
            return true;
        }
        else if(tom3 && toPile3) {
            moveHand(hand, pile3, true, pile1, pile2, pile3, pile4, pile5, pile6, pile7);            
            return true;
        }
        else if(tow1 && toWin1) {
            moveHand(hand, win1, false, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow2 && toWin2) {
            moveHand(hand, win2, false, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow3 && toWin3) {
            moveHand(hand, win3, false, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else if(tow4 && toWin4) {
            moveHand(hand, win4, false, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
            return true;
        }
        else {
            wrongMove = true;
            return false;
        }
    }

    //must reverse each of the main piles
    stack<Card> temp12;
    while(pile1.empty() == false) {
        temp12.push(pile1.top());
        pile1.pop();
    }
    pile1 = temp12;
    
    stack<Card> temp22;
    while(pile2.empty() == false) {
        temp22.push(pile2.top());
        pile2.pop();
    }
    pile2 = temp22;
    
    stack<Card> temp32;
    while(pile3.empty() == false) {
        temp32.push(pile3.top());
        pile3.pop();
    }
    pile3 = temp32;
    
    stack<Card> temp42;
    while(pile4.empty() == false) {
        temp42.push(pile4.top());
        pile4.pop();
    }
    pile4 = temp42;
    
    stack<Card> temp52;
    while(pile5.empty() == false) {
        temp52.push(pile5.top());
        pile5.pop();
    }
    pile5 = temp52;
    
    stack<Card> temp62;
    while(pile6.empty() == false) {
        temp62.push(pile6.top());
        pile6.pop();
    }
    pile6 = temp62;
    
    stack<Card> temp72;
    while(pile7.empty() == false) {
        temp72.push(pile7.top());
        pile7.pop();
    }
    pile7 = temp72;

    wrongMove = true;
    return false;

}

//when player types their move, this function will take that request and take the appropriate turn
void takeTurn(string playerMove1, string playerMove2, string playerMove3, stack<Card> &pile1, stack<Card> &pile2, stack<Card> &pile3, stack<Card> &pile4, stack<Card> &pile5, stack<Card> &pile6, stack<Card> &pile7, stack<Card> &win1, stack<Card> &win2, stack<Card> &win3, stack<Card> &win4, stack<Card> &hand, Deck &deck, int filledWinPiles, int &possibleMoves) {
    
    //if the player would like to deal new cards into the hand...
    if(playerMove1 == "deal" || playerMove1 == "DEAL") {
        dealNewCards(hand, deck);
    }

    //if the player would like to move a card or a stack of cards...
    if(playerMove2 == "to" || playerMove2 == "TO") {
        verifyMove(pile1, pile2, pile3, pile4, pile5, pile6, pile7, win1, win2, win3, win4, hand, playerMove1, playerMove3, possibleMoves);
    }
    
    //resets the number of possible moves at the beginning of a turn
    possibleMoves = 0;

    displayBoard(pile1, pile2, pile3, pile4, pile5, pile6, pile7, win1, win2, win3, win4, hand, deck);
    checkMoves(pile1, pile2, pile3, pile4, pile5, pile6, pile7, win1, win2, win3, win4, hand, filledWinPiles, possibleMoves);
    
    cout << endl << "ALERTS:" << endl;
    cout << "I-----------------------------------------------------I" << endl;
    
    if(deckRefilled) {
        cout << "|  The deck has been refilled from the hand.          |" << endl;
        deckRefilled = false;
    }
    else if(noMoves) {
        cout << "|  There are no available moves. Deal new cards.      |" << endl;
        noMoves = false;
    }
    else if(wrongMove) {
        cout << "|  Cannot move card(s). Please take a different turn. |" << endl;
        wrongMove = false;
    }
    else {
        cout << "|                                                     |" << endl;
    }
    
    if(showPossibleMoves)
        cout << "|  Number of Possible Moves: " << possibleMoves << "                        |" << endl;
    else
        cout << "|                                                     |" << endl;
}

//main function, where the game functions are called from
int main() {

    //+++++VARIABLES+++++//
    //===================//
    
    int filledWinPiles = 0;                         //counts the number of filled win piles, 4 to win
    int possibleMoves = 0;                          //keeps track of the possible moves one can take on a turn                         
   
    Card noneCard;                                  //creates a none card. variety of uses
    Card blankSpades;                               //blank suit cards used for the start of the win piles, one per suit
    Card blankClubs;
    Card blankHearts;
    Card blankDiamonds;

    Deck deck;                                      //deck of cards that will be used for the game

    stack<Card> pile1;                              //each of the 7 main piles                
    stack<Card> pile2;
    stack<Card> pile3;
    stack<Card> pile4;
    stack<Card> pile5;
    stack<Card> pile6;
    stack<Card> pile7;
    stack<Card> win1;                               //each of the win piles
    stack<Card> win2;
    stack<Card> win3;
    stack<Card> win4;

    stack<Card> hand;                               //hand where 3 cards are dealt at a time for use
    

    //+++++GAME SETUP+++++//
    //====================//

    deck.shuffleDeck();                             //shuffles the deck

    noneCard.maskCard();                            //sets up the none card to have special value and suit
    noneCard.setSuit("none");
    noneCard.setValue("none");

    blankSpades.setSuit("Spades");                  //sets up the blank suit cards, note they still have value "blank"
    blankSpades.maskCard();
    blankClubs.setSuit("Clubs");
    blankClubs.maskCard();
    blankHearts.setSuit("Hearts");
    blankHearts.maskCard();
    blankDiamonds.setSuit("Diamonds");  
    blankDiamonds.maskCard();

    win1.push(blankSpades);                         //pushes each of the blank suit cards into a win pile        
    win2.push(blankClubs);
    win3.push(blankHearts);
    win4.push(blankDiamonds);

    pile1.push(deck.dealCard());                    //deals the correct number of cards onto each pile,
    pile2.push(deck.dealCard());                    //in the correct order just like in real solitare
    pile3.push(deck.dealCard());
    pile4.push(deck.dealCard());
    pile5.push(deck.dealCard());
    pile6.push(deck.dealCard());
    pile7.push(deck.dealCard());

    

    /*
    Card test2;
    test2.setSuit("Spades");
    test2.setValue("Ace");
    Card test3;
    test3.setSuit("Clubs");
    test3.setValue("King");
    Card test4;
    test4.setSuit("Clubs");
    test4.setValue("King");
    Card test5;
    test5.setSuit("Hearts");
    test5.setValue("Ace");
    Card test6;
    test6.setSuit("Spades");
    test6.setValue("King");
    

    pile4.push(test1);
    pile4.push(test2);
    pile4.push(test3);
    pile4.push(test4);
    pile4.push(test5);
    pile4.push(test6);
    */

    pile2.push(deck.dealCard().maskCard());         //all of these cards need to be marked "unknown" before entering stack
    pile3.push(deck.dealCard().maskCard());
    pile4.push(deck.dealCard().maskCard());
    pile5.push(deck.dealCard().maskCard());
    pile6.push(deck.dealCard().maskCard());
    pile7.push(deck.dealCard().maskCard());

    pile3.push(deck.dealCard().maskCard());
    pile4.push(deck.dealCard().maskCard());
    pile5.push(deck.dealCard().maskCard());
    pile6.push(deck.dealCard().maskCard());
    pile7.push(deck.dealCard().maskCard());

    pile4.push(deck.dealCard().maskCard());
    pile5.push(deck.dealCard().maskCard());
    pile6.push(deck.dealCard().maskCard());
    pile7.push(deck.dealCard().maskCard());

    pile5.push(deck.dealCard().maskCard());
    pile6.push(deck.dealCard().maskCard());
    pile7.push(deck.dealCard().maskCard());

    pile6.push(deck.dealCard().maskCard());
    pile7.push(deck.dealCard().maskCard());

    pile7.push(deck.dealCard().maskCard());


    //+++++START OF GAME+++++//
    //=======================//

    //main menu that persists until the player types "start"
    string trash;
    string setting1;
    string setting2;
    string trash2;

    while(toUpper(trash) != "START")  {
    
        cout <<  "*******************************************************" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*             _____                                   *" << endl;
        cout <<  "*            |A .  | _____                            *" << endl;
        cout <<  "*            | /.\\ ||A ^  | _____                     *" << endl;
        cout <<  "*            |(_._)|| / \\ ||A _  | _____              *" << endl;
        cout <<  "*            |  |  || \\ / || ( ) ||A_ _ |             *" << endl;
        cout <<  "*            |____V||  .  ||(_'_)||( v )|             *" << endl;
        cout <<  "*                   |____V||  |  || \\ / |             *" << endl;
        cout <<  "*                          |____V||  .  |             *" << endl;
        cout <<  "*                                 |____V|             *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*         ╭━━━┳━━━┳╮╱╱╭━━┳━━━━┳━━━┳━━┳━━━┳━━━╮        *" << endl;
        cout <<  "*         ┃╭━╮┃╭━╮┃┃╱╱╰┫┣┫╭╮╭╮┃╭━╮┣┫┣┫╭━╮┃╭━━╯        *" << endl;
        cout <<  "*         ┃╰━━┫┃╱┃┃┃╱╱╱┃┃╰╯┃┃╰┫┃╱┃┃┃┃┃╰━╯┃╰━━╮        *" << endl;
        cout <<  "*         ╰━━╮┃┃╱┃┃┃╱╭╮┃┃╱╱┃┃╱┃╰━╯┃┃┃┃╭╮╭┫╭━━╯        *" << endl;
        cout <<  "*         ┃╰━╯┃╰━╯┃╰━╯┣┫┣╮╱┃┃╱┃╭━╮┣┫┣┫┃┃╰┫╰━━╮        *" << endl;
        cout <<  "*         ╰━━━┻━━━┻━━━┻━━╯╱╰╯╱╰╯╱╰┻━━┻╯╰━┻━━━╯        *" << endl;
        cout <<  "*                          by Payton Shaltis          *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl; 
        cout <<  "*                                                     *" << endl;
        cout <<  "*            -Resize your window to 55x31!-           *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*       -Type \"start\" to configure game settings-     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*       -Type \"exit\" at any time to stop playing-     *" << endl;
        cout <<  "*******************************************************" << endl;
        
        cin >> trash;

        if(toUpper(trash) == "EXIT") {
            exitScreen();
            return 0;
        }
    }

    while(toUpper(setting1) != "ON" && toUpper(setting1) != "OFF") {

        cout <<  "*******************************************************" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*             _____                                   *" << endl;
        cout <<  "*            |A .  | _____                            *" << endl;
        cout <<  "*            | /.\\ ||A ^  | _____                     *" << endl;
        cout <<  "*            |(_._)|| / \\ ||A _  | _____              *" << endl;
        cout <<  "*            |  |  || \\ / || ( ) ||A_ _ |             *" << endl;
        cout <<  "*            |____V||  .  ||(_'_)||( v )|             *" << endl;
        cout <<  "*                   |____V||  |  || \\ / |             *" << endl;
        cout <<  "*                          |____V||  .  |             *" << endl;
        cout <<  "*                                 |____V|             *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*    -->     Show number of possible moves?           *" << endl;
        cout <<  "*                 (type \"on\" of \"off\")                *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*             Show cards left in the deck?            *" << endl;
        cout <<  "*                 (type \"on\" of \"off\")                *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl; 
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*******************************************************" << endl;

        cin >> setting1;

        if(toUpper(setting1) == "ON") {
            showPossibleMoves = true;
        }
        if(toUpper(setting1) == "OFF") {
            showPossibleMoves = false;
        }
        if(toUpper(setting1) == "EXIT") {
            exitScreen();
            return 0;
        }
    }

    while(toUpper(setting2) != "ON" && toUpper(setting2) != "OFF") {

        cout <<  "*******************************************************" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*             _____                                   *" << endl;
        cout <<  "*            |A .  | _____                            *" << endl;
        cout <<  "*            | /.\\ ||A ^  | _____                     *" << endl;
        cout <<  "*            |(_._)|| / \\ ||A _  | _____              *" << endl;
        cout <<  "*            |  |  || \\ / || ( ) ||A_ _ |             *" << endl;
        cout <<  "*            |____V||  .  ||(_'_)||( v )|             *" << endl;
        cout <<  "*                   |____V||  |  || \\ / |             *" << endl;
        cout <<  "*                          |____V||  .  |             *" << endl;
        cout <<  "*                                 |____V|             *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*            Show number of possible moves?           *" << endl;
        cout <<  "*                 (type \"on\" of \"off\")                *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*             Show cards left in the deck?            *" << endl;
        cout <<  "*    -->          (type \"on\" of \"off\")                *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl; 
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*                                                     *" << endl;
        cout <<  "*******************************************************" << endl;

        cin >> setting2;

        if(toUpper(setting2) == "ON") {
            showDeckSize = true;
        }
        if(toUpper(setting2) == "OFF") {
            showDeckSize = false;
        }
        if(toUpper(setting2) == "EXIT") {
            exitScreen();
            return 0;
        }
    }

    //these functions will more than likely be called by the turn function, which will be called forever in a while loop
    possibleMoves = 0;
    displayBoard(pile1, pile2, pile3, pile4, pile5, pile6, pile7, win1, win2, win3, win4, hand, deck);
    checkMoves(pile1, pile2, pile3, pile4, pile5, pile6, pile7, win1, win2, win3, win4, hand, filledWinPiles, possibleMoves);
    
    cout << endl << "ALERTS:" << endl;
    cout << "I-----------------------------------------------------I" << endl;
    
    if(deckRefilled) {
        cout << "|  The deck has been refilled from the hand.          |" << endl;
        deckRefilled = false;
    }
    else if(noMoves) {
        cout << "|  There are no available moves. Deal new cards.      |" << endl;
        noMoves = false;
    }
    else if(wrongMove) {
        cout << "|  Cannot move card(s). Please take a different turn. |" << endl;
        wrongMove = false;
    }
    else {
        cout << "|                                                     |" << endl;
    }
    
    if(showPossibleMoves)
        cout << "|  Number of Possible Moves: " << possibleMoves << "                        |" << endl;
    else
        cout << "|                                                     |" << endl;
    
    /*
    moveStack(pile4, pile6, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
    displayBoard(pile1, pile2, pile3, pile4, pile5, pile6, pile7, win1, win2, win3, win4, hand);
    checkMoves(pile1, pile2, pile3, pile4, pile5, pile6, pile7, win1, win2, win3, win4, hand, filledWinPiles, possibleMoves);
    cout << "Number of Possible Moves: " << possibleMoves << endl;
    possibleMoves = 0;
    moveStack(pile6, pile1, pile1, pile2, pile3, pile4, pile5, pile6, pile7);
    displayBoard(pile1, pile2, pile3, pile4, pile5, pile6, pile7, win1, win2, win3, win4, hand);
    checkMoves(pile1, pile2, pile3, pile4, pile5, pile6, pile7, win1, win2, win3, win4, hand, filledWinPiles, possibleMoves);
    cout << "Number of Possible Moves: " << possibleMoves << endl;
    possibleMoves = 0;
    */

    while(true) {
        
        cout << "I-----------------------------------------------------I" << endl;

        //game cycle will check for a win before each turn, which is a king on each win pile
        filledWinPiles = 0;
        
        if(win1.top().getValue() == "King")
            filledWinPiles++;
        if(win2.top().getValue() == "King")
            filledWinPiles++;
        if(win3.top().getValue() == "King")
            filledWinPiles++;
        if(win4.top().getValue() == "King")
            filledWinPiles++;

        if(filledWinPiles == 4) {
            //cout << "You have won SOLITAIRE!" << endl;
            winScreen();
            return 0;
        }

        //game cycle will check for a loss before each turn, which is where timesRefilled gets to 3
        if(possibleMoves > 0) {
            timesRefilled = 0;
        }

        if(timesRefilled == 3) {
            //cout << "There are no more moves available. You have lost." << endl;
            loseScreen();
            return 0;
        }

        //strings that store player move requests
        string playerMove1;                                 
        string playerMove2;                                 
        string playerMove3;                                 

        //requests the user enter their move, stores it in these variables
        cout << "Enter your move:" << endl;
        cin >> playerMove1;                                 
        
        //allows for break from taking turns
        if(toUpper(playerMove1) == "EXIT") {
            exitScreen();
            return 0;
        }
        
        //allows for dealing without requiring 3 different words
        if(toUpper(playerMove1) == "DEAL") {
            goto turn;
        }

        //collects the second two words of the user's move
        cin >> playerMove2;
        cin >> playerMove3;

        //calls the takeTurn function which decides which action to take based on strings sent
        turn:
        takeTurn(toUpper(playerMove1), toUpper(playerMove2), toUpper(playerMove3), pile1, pile2, pile3, pile4, pile5, pile6, pile7, win1, win2, win3, win4, hand, deck, filledWinPiles, possibleMoves);
    }

    return 0;
}