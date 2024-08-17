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
        int value;

        for (Card card : hand) {
            value += card.getValue();
        }

        if (std::find_if(hand.begin(), hand.end(), [](const Card& card) {
                return card.getValue() == static_cast<int>(Card::Value::ACE);
            }) != hand.end()) {
            /* hand contains ACE card */
        } else {
            /* hand does not contain ACE card */
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