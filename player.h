#ifndef PLAYER_H
#define PLAYER_H

#include "cash.h"
#include "deck.h"
#include "hand.h"

class Player {
  public:
    // pass deck by reference in constructor
    Player(Deck& deckref, Cash& cashref, Hand& handref)
        : deck(deckref), cash(cashref), hand(handref) {}
  
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

    bool canSplit() {
        // if card 1 in hand == card 2 in hand
        if (hand.hand[0].getValue() == hand.hand[1].getValue()) {
            return true;
        }
        return false;
    }

    void split() {
        if (canSplit) {

        }
    }

    void stand() { isstanding = true; }

    void surrender() { issurrendered = true; }

    void resetPlayer() {
        isstanding = false;
        isbusted = false;
        issurrendered = false;
    }

  private:
    Hand& hand;
    // reference to deck in deck class
    Deck& deck;
    Cash& cash;

    bool isstanding;
    bool isbusted;
    bool issurrendered;
};

#endif