#ifndef HAND_H
#define HAND_H 

#include <vector>
#include <algorithm>
#include <iostream>
#include "card.h"

class Hand
{
  public:
    Hand() : hand() {}

    void addCard(Card card) {
        hand.push_back(card);
        totalvalue = getTotalValue();
    };

    int getTotalValue() {
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

    bool isBlackjack() {
        return totalvalue == 21;
    };

    bool isBust() {
        return totalvalue > 21;
    };

    bool canSplit() {
        // if card 1 in hand == card 2 in hand
        if (hand[0].getValue() == hand[1].getValue()) {
            return true;
        }
        return false;
    }

    void clearhand() {
        hand.clear();
    }

    Hand split() {
        Hand secondhand;
        secondhand.hand.push_back(Hand::hand[1]);
        Hand::hand.pop_back();
        secondhand.totalvalue = getTotalValue();
        return secondhand;
    }

    const std::vector<Card>& getHandVector() const {
        return hand;
    }

    // DEPRACATED
    // std::string showHand(bool isDealerFirstTurn) const{
    //     std::string handStr;
    //     if (isDealerFirstTurn) {
    //         handStr += "*CARD HIDDEN*\n";
    //         handStr += hand[1].getFace() + " of " + hand[1].getSuit() + '\n';
    //         return handStr;
    //     }
    //     for (const Card& card : hand) {
    //         handStr += card.getFace() + " of " + card.getSuit() + '\n';
    //     }
    //     return handStr;
    // }
 
  private:
    std::vector<Card> hand;
    int totalvalue;
};


#endif