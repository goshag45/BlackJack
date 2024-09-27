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
    // DEPRACATED
    // void showHandString() {
    //     if (!isFirstTurn) {
    //         std::cout << "Hand Value: " << hand.getTotalValue() << '\n';
    //     }
    //     std::cout << getHand().showHand(isFirstTurn) << '\n';
    // }
};

#endif