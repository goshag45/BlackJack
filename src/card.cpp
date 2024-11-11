#include "card.h"

Card::Card(Suit _suit, Value _value) : suit(_suit), value(_value) {}

std::string Card::getSuit() const {
    switch (suit) {
        case Suit::HEARTS: return "Hearts";
        case Suit::CLUBS: return "Clubs";
        case Suit::SPADES: return "Spades";
        case Suit::DIAMONDS: return "Diamonds";
        default: return "Unknown";
    }
}

std::string Card::getFace() const {
    static const std::map<Value, std::string> valueToFace{
        {Value::TWO, "TWO"}, {Value::THREE, "THREE"}, {Value::FOUR, "FOUR"},
        {Value::FIVE, "FIVE"}, {Value::SIX, "SIX"}, {Value::SEVEN, "SEVEN"},
        {Value::EIGHT, "EIGHT"}, {Value::NINE, "NINE"}, {Value::TEN, "TEN"},
        {Value::KING, "KING"}, {Value::QUEEN, "QUEEN"}, {Value::JACK, "JACK"},
        {Value::ACE, "ACE"}
    };

    auto it = valueToFace.find(value);
    return (it != valueToFace.end()) ? it->second : "UNKNOWN";
}

int Card::getValue() const {
    return static_cast<int>(value);
}

bool Card::operator==(const Card& other) const {
    return suit == other.suit && value == other.value;
}
