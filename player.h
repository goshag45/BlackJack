#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include "deck.h"

class Player
{
  public:
    Player() : hand() {}
    void hit() {
        hand.addCard(deck.draw());
    }
    void stand() {}
    void doubledown() {}
    void split() {}
    void surrender() {}
  
  private:
    Hand hand;
};

#endif