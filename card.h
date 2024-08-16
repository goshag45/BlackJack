#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
  public:
    enum class Suit{ HEARTS, CLUBS, SPADES, DIAMONDS };
    enum class Value{TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,ACE,KING,QUEEN,JACK};

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
      switch(value) {
        case Value::TWO: return 2;
        case Value::THREE: return 3;
        case Value::FOUR: return 4;
        case Value::FIVE: return 5;
        case Value::SIX: return 6;
        case Value::SEVEN: return 7;
        case Value::EIGHT: return 8;
        case Value::NINE: return 9;
        case Value::TEN: return 10;
        case Value::KING: return 10; 
        case Value::QUEEN: return 10;
        case Value::JACK: return 10;
        case Value::ACE: return 11;
        default: return 0;
      }
    }

  private:
    Suit suit;
    Value value;
};

#endif