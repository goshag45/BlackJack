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

    std::string showHand() {
        std::string handStr;
        for (const Card& card : hand) {
            handStr += card.getFace() + " of " + card.getSuit() + "\n";
        }
        return handStr;
    }


  private:  
    std::vector<Card> hand;
    int totalvalue;
};


#endif