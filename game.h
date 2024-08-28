#ifndef GAME_U
#define GAME_U

#include <iostream>

#include "card.h"
#include "cash.h"
#include "dealer.h"
#include "deck.h"
#include "hand.h"
#include "player.h"

class Game {
  public:
    Game()
        : deck(),
          cash(),
          player(deck, cash),
          dealer(deck, cash)
    { 
        isRunning = true; 
    }
    
    void initialiseGame() {
        // maybe?
    }

    void coreLoop() {
        isRunning = true;
        while (isRunning) { 
            std::cout << "-----------Starting Game-----------" << std::endl;

        }

    }

    void getPlayerBet() {
        std::cout << "Enter bet: " << std::endl;
        // add type checking?
        std::cin >> bet;
    }

    void start() {
        // need to loop through amount of player hands
    }

    void end() {}

  private:
    Deck deck;
    Cash cash;
    Player player;
    Dealer dealer;
    bool isRunning;
    // THIS NEEDS TO LINK TO CASH
    int bet = 0;
};

#endif