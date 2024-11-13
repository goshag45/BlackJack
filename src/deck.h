#ifndef DECK_H
#define DECK_H

#include "card.h"

class Deck {
  public:
    Deck() {}

    void shuffle() {}

    Card draw() {}

  private:
    std::vector<Card> deck;
};

#endif