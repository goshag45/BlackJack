#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include "deck.h"

class Player
{
  public:
    // pass deck by reference in constructor
    Player(Deck& deckref) : deck(deckref), hand() {}
    
    void hit() {
        hand.addCard(deck.draw());
    }
    void stand() {}
    void doubledown() {}
    void split() {}
    void surrender() {}
  
  private:
    Hand hand;
    // reference to deck in deck class
    Deck& deck;
};

#endif