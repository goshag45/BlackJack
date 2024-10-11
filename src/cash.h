#ifndef CASH_H
#define CASH_H

class Cash {
  public:
    int currentBet = 0;
    int cash;

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
    
    const int& getCash() const { return cash;}
    const int& getCurrentBet() const { return currentBet;}

  protected:
};

#endif 