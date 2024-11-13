#ifndef HAND_H
#define HAND_H 

class Hand
{
  public:
    Hand() : hand() {}

    void addCard(Card card) {}

    int getTotalValue() {}

    bool isBlackjack() {}

    bool isBust() {}

    void clearhand() {}

    Hand split() {}

    const std::vector<Card>& getHandVector() const {}
 
  private:
    std::vector<Card> hand;
    int totalvalue;
};


#endif