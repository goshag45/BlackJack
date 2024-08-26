#ifndef CASH_H
#define CASH_H

class Cash {
  public:
    Cash() {cash = 0;};

    Cash(int startingcash) : cash(startingcash) {};

    void setBet(int bet) {
        currentBet = bet;
    };

    void doubleBet() {
        cash -= currentBet;
        currentBet *= 2;
    }

    void setCash(int input) {cash = input;}
    
  protected:
    int currentBet = 0;;
    int cash;
};

#endif 