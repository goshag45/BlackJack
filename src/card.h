#ifndef CARD_H
#define CARD_H

#include <map>
#include <string>

class Card {
  public:
    enum class Suit { HEARTS, CLUBS, SPADES, DIAMONDS };
    enum class Value {
        TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
        ACE = 11, KING = 10, QUEEN = 10, JACK = 10
    };

    Card(Suit _suit, Value _value);

    std::string getSuit() const;
    std::string getFace() const;
    int getValue() const;

    bool operator==(const Card& other) const;

  private:
    Suit suit;
    Value value;
};

#endif
