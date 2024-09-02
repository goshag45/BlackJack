#ifndef GAME_U
#define GAME_U

#include <iostream>
#include <chrono>
#include <thread>

#include "card.h"
#include "cash.h"
#include "dealer.h"
#include "deck.h"
#include "hand.h"
#include "player.h"

// Function declarations
inline void sleep(int ms);
inline void continuePrompt();

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

    void coreLoop() {
        isRunning = true;
        while (isRunning) { 
            std::cout << "-----------Starting Game-----------" << std::endl;
            sleep(1000);
            dealPlayerAndDealer();
            std::cout << "Player: \n" << player.getHand().showHand() << std::endl;
            // possible ideas for a dealer showhand:
            // overloaded showhand method with flag?
            // super specific method showDealerHandTurnOne()
            std::cout << "Dealer: " << dealer.getHand().showHand() << std::endl;
            continuePrompt();
        }

    }

    void dealPlayerAndDealer() {
        std::cout << "dealing..." << std::endl;
        dealer.hit();
        dealer.hit();
        player.hit();
        player.hit();
    }

    void getPlayerBet() {
        std::cout << "Enter bet: " << std::endl;
        // add type checking?
        std::cin >> bet;
    }

  private:
    Deck deck;
    Cash cash;
    Player player;
    Dealer dealer;
    bool isRunning;
    // THIS NEEDS TO LINK TO CASH
    int bet = 0;
};

inline void sleep(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

inline void continuePrompt() {
    std::cout << "Press Enter to Continue";
    std::cin.ignore();
} 

#endif