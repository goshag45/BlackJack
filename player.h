#ifndef PLAYER_H
#define PLAYER_H

#include "cash.h"
#include "deck.h"
#include "hand.h"

class Player {
  public:
    // pass deck by reference in constructor
    Player(Deck& deckref, Cash& cashref) : deck(deckref), cash(cashref) {
            Hand hand;
        }
  
    void hit() {
        hand.addCard(deck.draw());
        if (hand.isBust()) {
            isbusted = true;
        }
    }

    void doubleDown() {
        cash.doubleBet();
        hit();
    }

    void split() {
        if (hand.canSplit()) {
            secondhand = hand.split();
        }
    }

    void stand() { isstanding = true; }

    void surrender() { issurrendered = true; }

    void resetPlayer() {
        isstanding = false;
        isbusted = false;
        issurrendered = false;
        hand.clearhand();
        secondhand.clearhand();
    }

  private:
    // only 2 hands
    // need better implementation than this for more splits
    Hand hand;
    Hand secondhand;
    Deck& deck;
    Cash& cash;

    bool isstanding;
    bool isbusted;
    bool issurrendered;
};

#endif