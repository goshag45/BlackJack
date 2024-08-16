#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"

class Player
{
  private:
    Hand hand;

  public:
    Player();
    player hit() {}
    player stand() {}
    player doubledown() {}
    player split() {}
    player surrender() {}

};

#endif