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
    bool isGameRunning;

    Game()
        : deck(),
          cash(),
          player(deck, cash),
          dealer(deck, cash),
          ui()
    { 
        isGameRunning = true; 
    }

    void promptPlayer(Gui& gui) {
        int choice = gui.getPlayerAction();
        switch (choice) {
            case 1: 
                player.hit();
                checkEndGameState();
                playerHitLoop(gui);
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
                ui.showMessage("Invalid choise!");
        }
    }
    
    void playerHitLoop(Gui& gui) {
        while (!player.hand.isBust() && !player.hand.isBlackjack() && !(player.isstanding)) {
            int choice = gui.getPlayerActionLoop();
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

    void resetGame() {
        player.reset();
        dealer.reset();
    }

    // void coreLoop(Gui& gui) {
    //     isGameRunning = true;
    //     while (isGameRunning) { 
    //         resetGame();
    //         dealInitialCards();

    //         // player.showHandString();
    //         std::cout << "working!\n";
    //         // gui.DisplayCard(player.hand.getHandVector()[0]);
    //         // gui.showHand(player);
            
    //         checkEndGameState();
    //         // dealer.showHandString();
    //         dealer.isFirstTurn = false;
    //         ui.continuePrompt();
    //         promptPlayer();
    //         dealerTurn();
    //         ui.continuePrompt();
    //     }
    // }

    void GameLogic(Gui& gui) {
        resetGame();
        dealInitialCards();
        promptPlayer(gui);
    }

    const Player& getPlayer() const{ return player; }
    const Dealer& getDealer() const{ return dealer; }

  private:
    void checkEndGameState() {
        playerBustCheck();
        playerBlackJackCheck();
    }

    Deck deck;
    Cash cash;
    Player player;
    Dealer dealer;
    Ui ui;
    // THIS NEEDS TO LINK TO CASH
    int bet = 0;
};

#endif