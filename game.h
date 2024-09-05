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
inline void choiceMessage(std::string choice);

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

    void promptPlayer() {
        std::cout << "\n----------Choose your play----------\n";
        std::cout << "[1] Hit\n";
        std::cout << "[2] Stand\n";
        std::cout << "[3] Double Down\n";
        std::cout << "[4] Split\n";
        std::cout << "[5] Insurance\n";
        int choice;
        //TYPE CHECKING!!!
        std::cin >> choice;
        switch (choice) {
            case 1: 
                player.hit();
                choiceMessage("Hit!");
                player.showHandString();
                playerHitLoop();
                break;
            case 2:
                player.stand();
                choiceMessage("Stand");
                break;
            case 3:
                player.doubleDown();
                choiceMessage("Double Down");
                break;
            case 4:
                player.split();
                choiceMessage("Split");
                break;
            case 5:
                // nothing here yet!
                break;
            default:
                std::cout << "Invalid choise!\n";
        }
    }
    
    void playerHitLoop() {
        while (!player.hand.isBust() && !player.hand.isBlackjack()) {
            std::cout << "Would you like to [1] Hit or [2] Stand\n";
            int choice;
            std::cin >> choice;
            switch (choice) {
                case 1: 
                    player.hit();
                    choiceMessage("Hit!");
                    player.showHandString();
                    break;
                case 2:
                    player.stand();
                    choiceMessage("Stand!");
                    player.showHandString();
                    break;
            }
        }
    }

    void playerHandStateMessage() {
        // IF BUST WRITE BUST, IF BJ WRITE BJ
    }

    void dealerTurn() {
        std::cout << "Dealer playing...\n";
        sleep(1000);
        while (dealer.canhit) {
            dealer.dealerhit();
            if (dealer.canhit) {
                dealer.showHandString();
            }
        }
    }

    void dealPlayerAndDealer() {
        std::cout << "dealing...\n";
        dealer.hit();
        dealer.hit();
        player.hit();
        player.hit();
    }

    void getPlayerBet() {
        std::cout << "Enter bet: \n";
        // add type checking?
        std::cin >> bet;
    }

    void coreLoop() {
        isRunning = true;
        while (isRunning) { 
            std::cout << "\n-----------Starting Game-----------\n";
            sleep(1000);
            dealPlayerAndDealer();
            player.showHandString();
            dealer.showHandString();
            dealer.isFirstTurn = false;
            continuePrompt();
            promptPlayer();
            continuePrompt();
            dealerTurn();
            continuePrompt();
        }
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
    std::cout << "Press Enter to Continue\n";
    std::cin.ignore();
} 

inline void choiceMessage(std::string choice) {
    std::cout << "\n" << "You chose: " << choice << '\n';
}

#endif