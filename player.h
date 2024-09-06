#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "cash.h"
#include "deck.h"
#include "hand.h"

class Player {
  public:
    Hand hand;
    // THIS IS NOT PROPERLY IMPLEMENTED
    std::vector<Hand> hands;
    Deck& deck;
    Cash& cash;

    bool isstanding = false;
    bool isbusted;
    bool issurrendered;

    // pass deck by reference in constructor
    Player(Deck& deckref, Cash& cashref) : deck(deckref), cash(cashref), hand(), hands(1, Hand()) {}
  
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
            hands.push_back(hand.split());
        }
    }

    void stand() { isstanding = true; }

    void surrender() { issurrendered = true; }

    void reset() {
        isstanding = false;
        isbusted = false;
        issurrendered = false;
        hand.clearhand();
        hands.resize(1);
        hands[0].clearhand();
    }

    void showHandString() {
        std::cout << "Player: \n" << getHand().showHand(false) << '\n';
    }

    const Hand& getHand() const {
        return hand;
    }
};

#endif