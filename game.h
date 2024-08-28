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

    void sleep(int ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    void coreLoop() {
        isRunning = true;
        while (isRunning) { 
            std::cout << "-----------Starting Game-----------" << std::endl;
            sleep(1000);
            dealAndShowHands();
            std::cout << "Press Enter to Continue";
            std::cin.ignore();
        }

    }

    void dealAndShowHands() {
        std::cout << "dealing..." << std::endl;
        dealer.hit();
        dealer.hit();
        player.hit();
        player.hit();
        std::cout << "Player: " << player.getHand().showHand() << std::endl;
        std::cout << "Dealer: " << dealer.getHand().showHand() << std::endl;
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