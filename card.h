#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
  public:
    enum class Suit{ HEARTS, CLUBS, SPADES, DIAMONDS };
    enum class Value {
        TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
        ACE = 11, KING = 10, QUEEN = 10, JACK = 10
    };

    Card(Suit Suit, Value Value): suit(Suit), value(Value) {}

    std::string getSuit() const {
      switch(suit) {
        case Suit::HEARTS: return "Hearts";
        case Suit::CLUBS: return "Clubs";
        case Suit::SPADES: return "Spades";
        case Suit::DIAMONDS: return "Diamonds";
        default: return "unkown";
      }
    }

    int getValue() const {
      return static_cast<int>(value);
    }

  private:
    Suit suit;
    Value value;
};

#endif