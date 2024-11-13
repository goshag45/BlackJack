#include <vector>
#include <algorithm>
#include <iostream>

#include "hand.h"
#include "card.h"

Hand::Hand() : hand() {}

void Hand::addCard(Card card) {
    hand.push_back(card);
    totalvalue = getTotalValue();
};

int Hand::getTotalValue() {
    int value = 0;
    int acecount = 0;

    for (const Card& card : hand) {
        if (card.getValue() == 11) {
            acecount++;
        }
        value += card.getValue();
    }

    if (value > 21) {
        while (value > 21 && acecount > 0) {
            value -= 10;
            acecount--;
        }
    }

    totalvalue = value;
    return value;
};

bool Hand::isBlackjack() {
    return totalvalue == 21;
};

bool Hand::isBust() {
    return totalvalue > 21;
};

void Hand::clearhand() {
    hand.clear();
}

Hand Hand::split() {
    Hand newhand;
    newhand.hand.push_back(Hand::hand[1]);
    Hand::hand.pop_back();
    return newhand;
}

const std::vector<Card>& Hand::getHandVector() const {
    return hand;
}