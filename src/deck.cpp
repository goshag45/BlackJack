#include <vector>
#include <array>
#include <stdexcept>
#include <random>
#include <utility>


#include "deck.h"

Deck::Deck() {
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
    shuffle();
}

void Deck::shuffle() {
    std::vector<Card> unshuffled = deck;
    // https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
    std::random_device rd;
    std::mt19937 gen(rd());

    // Fisher-Yates shuffle
    size_t n = deck.size();
    for (size_t i = n-1; i > 1; i--) {
        std::uniform_int_distribution<size_t> distr(0, i);
        size_t j = distr(gen);
        std::swap(deck[i], deck[j]);
    }
}

Card Deck::draw() {
    Card lastcard = deck.back();
    deck.pop_back();
    return lastcard;
}