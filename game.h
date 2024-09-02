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
        dealerFirstTurn = false;
        while (isRunning) { 
            std::cout << "-----------Starting Game-----------" << std::endl;
            sleep(1000);
            dealPlayerAndDealer();
            std::cout << "Player: \n" << player.getHand().showHand(dealerFirstTurn) << std::endl;
            dealerFirstTurn = true;
            std::cout << "Dealer: \n " << dealer.getHand().showHand(dealerFirstTurn) << std::endl;
            dealerFirstTurn = false;
            continuePrompt();
            promptPlayer();
        }

    }

    void promptPlayer() {
        std::cout << "----------Choose your play----------" << std::endl;
        std::cout << "1. Hit" << std::endl;
        std::cout << "2. Stand" << std::endl;
        std::cout << "3. Double Down" << std::endl;
        std::cout << "4. Split" << std::endl;
        std::cout << "5. Insurance" << std::endl;
        int choice;
        //TYPE CHECKING!!!
        std::cin >> choice;
        switch (choice) {
            case 1: 
                player.hit();
                break;
            case 2:
                player.stand();
                break;
            case 3:
                player.doubleDown();
                break;
            case 4:
                player.split();
                break;
            case 5:
                // nothing here yet!
                break;
            default:
                std::cout << "Invalid choise!" << std::endl;
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
    bool dealerFirstTurn = false;
};

inline void sleep(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

inline void continuePrompt() {
    std::cout << "Press Enter to Continue";
    std::cin.ignore();
} 

#endif