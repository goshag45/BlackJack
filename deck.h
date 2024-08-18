#ifndef DECK_H
#define DECK_H

#include <vector>
#include <array>
#include <stdexcept>
#include "card.h"

class Deck {
  public:
    Deck() {
        std::vector<Card> deck;
        const std::array<Card::Suit, 4> suits = {
            Card::Suit::HEARTS, 
            Card::Suit::CLUBS, 
            Card::Suit::SPADES, 
            Card::Suit::DIAMONDS
        };
        const std::array<Card::Value, 13> values = {
            Card::Value::TWO, 
            Card::Value::THREE, 
            Card::Value::FOUR, 
            Card::Value::FIVE, 
            Card::Value::SIX, 
            Card::Value::SEVEN, 
            Card::Value::EIGHT, 
            Card::Value::NINE, 
            Card::Value::TEN,
            Card::Value::ACE, 
            Card::Value::KING, 
            Card::Value::QUEEN, 
            Card::Value::JACK
        };
        for (auto suit : suits) {
            for (auto value : values) {
                deck.push_back(Card(suit, value));
            }   
        }
        if (deck.size() != 52) {
            throw std::runtime_error("Deck initialised with less than 52 cards!");
        }
    }

    Deck shuffle() {

    }

    Card draw() {

    }

  private:
    std::vector<Card> deck;
};

#endif