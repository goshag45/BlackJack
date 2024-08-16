#ifndef HAND_H
#define HAND_H 

#include <vector>
#include "card.h"

class Hand
{
  private:  
    std::vector<Card> cards;
  public:
    Hand(/* args */);
    Hand addcard() {

    };
    int calculatevalue() {

    };
    bool checkblackjack() {

    };
    Hand showplayerhand() {

    }
    Hand showdealerhand() {
      
    }
};


#endif