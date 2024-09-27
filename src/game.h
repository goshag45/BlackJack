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
#include "gui.h"
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
                checkEndGameState();
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
        while (!player.hand.isBust() && !player.hand.isBlackjack() && !(player.isstanding)) {
            int choice = ui.getPlayerInputInt("Would you like to [1] Hit or [2] Stand");
            switch (choice) {
                case 1: 
                    player.hit();
                    checkEndGameState();
                    break;
                case 2:
                    player.stand();
                    // NEED TO SOMEHOW BREAK OUT OF THE LOOP HERE
                    break;
            }
        }
    }

    void dealerTurn() {
        if (dealer.canhit) { ui.showMessage("Dealer playing..."); }
        while (dealer.canhit) {
            dealer.dealerhit();
            if (dealer.canhit) { }
        }
        if (!dealer.canhit) {
            ui.showMessage("Dealer Final Hand");
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

    void playerBustCheck() {
        if (player.isbusted) {
            ui.showMessage("You are BUST! With a hand value of: ", player.hand.getTotalValue());
        }
    }

    void playerBlackJackCheck() {
        if (player.isBlackjack) {
            ui.showMessage("You have BLACKJACK!");
        }
    }

    void checkEndGameState() {
        playerBustCheck();
        playerBlackJackCheck();
    }

    void resetGame() {
        player.reset();
        dealer.reset();
    }

    void coreLoop() {
        Gui gui;

        isRunning = true;
        while (isRunning) { 
            resetGame();
            
            dealInitialCards();
            // player.showHandString();
            
            checkEndGameState();
            // dealer.showHandString();
            dealer.isFirstTurn = false;
            ui.continuePrompt();
            promptPlayer();
            dealerTurn();
            ui.continuePrompt();
        }
    }

    Deck deck;
    Cash cash;
    Player player;
    Dealer dealer;
    Ui ui;
    bool isRunning;
    // THIS NEEDS TO LINK TO CASH
    int bet = 0;
};

#endif