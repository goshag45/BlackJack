#ifndef HAND_H
#define HAND_H 

#include <vector>
#include "card.h"

class hand
{
  private:  
    std::vector<card> cards;
  public:
    hand(/* args */);
    hand addcard() {};
    hand calculatevalue() {};
    bool checkblackjack() {};
};


#endif