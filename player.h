#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include "deck.h"
#include "cash.h"

class Player
{
  public:
    // pass deck by reference in constructor
    Player(Deck& deckref, Cash& cashref) : deck(deckref), cash(cashref), hand() {}
    
    void hit() {
        hand.addCard(deck.draw());
        if (hand.isBust()) {
            isbusted = true;
        }
    }
    void stand() {
        isstanding = true;
    }
    void doubleDown() {
        cash.doubleBet();
        hit();
    }
    void split() {}
    void surrender() {
        issurrendered = true;
    }

    void resetPlayer() {
        isstanding = false;
        isbusted = false;
        issurrendered = false;
    }
  
  private:
    Hand hand;
    // reference to deck in deck class
    Deck& deck;
    Cash& cash;

    bool isstanding;
    bool isbusted;
    bool issurrendered;
};

#endif