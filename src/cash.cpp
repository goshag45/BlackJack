#include "cash.h"

Cash::Cash() : cash(1000) {}

Cash::Cash(int startingcash) : cash(startingcash) {}

void Cash::setBet(int bet) {
    cash -= bet;
    currentBet = bet;
}

void Cash::doubleBet() {
    cash -= currentBet;
    currentBet *= 2;
}

void Cash::betWin() {
    cash += (currentBet * 2);
}

void Cash::surrender() {
    cash += (currentBet / 2);
}

void Cash::setCash(int input) {
    cash = input;
}

const int& Cash::getCash() const {
    return cash;
}

const int& Cash::getCurrentBet() const {
    return currentBet;
}
