#ifndef DEALER_H
#define DEALER_H

#include "iostream"
#include "player.h"

class Dealer : public Player {
  public:
    bool canhit = true;
    bool isFirstTurn = true;

    Dealer(Deck& deckref, Cash& cashref) : Player(deckref, cashref) {}

    void dealerhit() {
        if (hand.getTotalValue() < 17) {
            hit();            
        } else { canhit = false; }
    }

    void showHandString() {
        std::cout << "Dealer: \n" << getHand().showHand(isFirstTurn) << '\n';
    }
};

#endif