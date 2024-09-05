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
#include "ui.h"


class Game {
  public:
    Game()
        : deck(),
          cash(),
          player(deck, cash),
          dealer(deck, cash),
          ui()
    { 
        isRunning = true; 
    }

    void promptPlayer() {
        ui.playerPlayMenu();
        int choice = ui.getPlayerInputInt("");
        switch (choice) {
            case 1: 
                player.hit();
                ui.choiceMessage("Hit!");
                player.showHandString();
                playerHitLoop();
                break;
            case 2:
                player.stand();
                ui.choiceMessage("Stand");
                break;
            case 3:
                player.doubleDown();
                ui.choiceMessage("Double Down");
                break;
            case 4:
                player.split();
                ui.choiceMessage("Split");
                break;
            case 5:
                // nothing here yet!
                break;
            default:
                ui.showMessage("Invalid choise!");
        }
    }
    
    void playerHitLoop() {
        while (!player.hand.isBust() && !player.hand.isBlackjack()) {
            int choice = ui.getPlayerInputInt("Would you like to [1] Hit or [2] Stand");
            switch (choice) {
                case 1: 
                    player.hit();
                    ui.choiceMessage("Hit!");
                    player.showHandString();
                    break;
                case 2:
                    player.stand();
                    ui.choiceMessage("Stand!");
                    player.showHandString();
                    break;
            }
        }
    }

    void playerHandStateMessage() {
        // IF BUST WRITE BUST, IF BJ WRITE BJ
    }

    void dealerTurn() {
        ui.showMessage("Dealer playing...");
        sleep(1000);
        while (dealer.canhit) {
            dealer.dealerhit();
            if (dealer.canhit) {
                dealer.showHandString();
            }
        }
    }

    void dealInitialCards() {
        ui.showMessage("dealing...");
        dealer.hit();
        dealer.hit();
        player.hit();
        player.hit();
    }

    void getPlayerBet() {
        bet = ui.getPlayerInputInt("Enter bet: ");
    }

    void coreLoop() {
        isRunning = true;
        while (isRunning) { 
            ui.showMessage("-----------Starting Game-----------");
            // sleep(1000);
            dealInitialCards();
            player.showHandString();
            dealer.showHandString();
            dealer.isFirstTurn = false;
            ui.continuePrompt();
            promptPlayer();
            ui.continuePrompt();
            dealerTurn();
            ui.continuePrompt();
        }
    }

  private:
    Deck deck;
    Cash cash;
    Player player;
    Dealer dealer;
    Ui ui;
    bool isRunning;
    // THIS NEEDS TO LINK TO CASH
    int bet = 0;
};

// might not need this?
inline void sleep(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#endif