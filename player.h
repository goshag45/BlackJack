#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"

class Player
{
  private:
    Hand hand;

  public:
    Player();
    Player hit() {}
    Player stand() {}
    Player doubledown() {}
    Player split() {}
    Player surrender() {}

};

#endif