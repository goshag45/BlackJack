#ifndef HAND_H
#define HAND_H 

#include <vector>
#include <algorithm>
#include "card.h"

class Hand
{
  public:
    int totalvalue;

    Hand() {
        std::vector<Card> hand;
    };

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
        if (totalvalue == 21) {
            return true;
        }
        return false;
    };

    bool isBust() {
        if (totalvalue > 21) {
            return true;
        }
        return false;
    };

    std::string showHand() {

    }

  private:  
    std::vector<Card> hand;
};


#endif