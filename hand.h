#ifndef HAND_H
#define HAND_H 

#include <vector>
#include "card.h"

class Hand
{
  public:
    int totalvalue;

    Hand(std::vector<Card> hand): hand(hand) {};

    void addCard(Card card) {
      hand.push_back(card);
    };

    int getTotalValue(std::vector<Card> hand) {
      int value;

      for (Card card : hand) {
        value =+ card.getValue();
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