#ifndef CARD_H
#define CARD_H

#include <map>
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

    std::string getFace() const {
        static const std::map<Value, std::string> valueToFace {
            {Value::TWO, "TWO"},
            {Value::THREE, "THREE"},
            {Value::FOUR, "FOUR"},
            {Value::FIVE, "FIVE"},
            {Value::SIX, "SIX"},
            {Value::SEVEN, "SEVEN"},
            {Value::EIGHT, "EIGHT"},
            {Value::NINE, "NINE"},
            {Value::TEN, "TEN"},
            {Value::KING, "KING"},
            {Value::QUEEN, "QUEEN"},
            {Value::JACK, "JACK"},
            {Value::ACE, "ACE"}
        };

        auto it = valueToFace.find(value);
        return (it != valueToFace.end()) ? it->second : "UNKNOWN";
    }

    int getValue() const {
      return static_cast<int>(value);
    }

    bool operator==(const Card& other) const {
        return suit == other.suit && value == other.value;
    }

  private:
    Suit suit;
    Value value;
};

#endif