#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"

class player
{
  private:
    hand hand;
  public:
    player(/* args */);
    player hit() {}
    player stand() {}
    player doubledown() {}
    player split() {}
    player surrender() {}

};

#endif