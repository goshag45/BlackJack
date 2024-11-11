#ifndef CASH_H
#define CASH_H

class Cash {
  public:
    int currentBet = 0;
    int cash;

    Cash();
    Cash(int startingcash);

    void setBet(int bet);
    void doubleBet();
    void betWin();
    void surrender();
    void setCash(int input);
    
    const int& getCash() const;
    const int& getCurrentBet() const;
};

#endif
