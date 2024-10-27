#ifndef DEALER_H
#define DEALER_H

#include "iostream"
#include "player.h"

class Dealer : public Player {
  public:
    bool canhit = true;
    bool isFirstTurn = true;

    Dealer(Deck& deckref, Cash& cashref) : Player(deckref, cashref) {}
};

#endif