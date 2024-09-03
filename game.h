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
            std::cout << "\n-----------Starting Game-----------\n";
            sleep(1000);
            dealPlayerAndDealer();
            showHandString(true, dealerFirstTurn);
            dealerFirstTurn = true;
            showHandString(false, dealerFirstTurn);
            dealerFirstTurn = false;
            continuePrompt();
            promptPlayer();
            showHandString(true, dealerFirstTurn);
            showHandString(false, dealerFirstTurn);
            continuePrompt();
        }
    }

    void showHandString(bool playerCheck, bool firstTurn) {
        if (playerCheck) {
            std::cout << "Player: \n" << player.getHand().showHand(firstTurn) << '\n';
            return;
        }
        std::cout << "Dealer: \n" << dealer.getHand().showHand(firstTurn) << '\n';
    }

    void promptPlayer() {
        std::cout << "\n----------Choose your play----------" << std::endl;
        std::cout << "1. Hit\n";
        std::cout << "2. Stand\n";
        std::cout << "3. Double Down\n";
        std::cout << "4. Split\n";
        std::cout << "5. Insurance\n";
        int choice;
        //TYPE CHECKING!!!
        std::cin >> choice;
        switch (choice) {
            case 1: 
                // NEED A HIT LOOP HERE
                player.hit();
                choiceMessage("Hit");
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

    void choiceMessage(std::string choice) {
        std::cout << "\n" << "You chose: " << choice << '\n' << std::endl;
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
    bool dealerFirstTurn;
};

inline void sleep(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

inline void continuePrompt() {
    std::cout << "Press Enter to Continue";
    std::cin.ignore();
} 

#endif