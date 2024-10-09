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
    enum GameState { DEALING, PLAYER_TURN, DEALER_TURN, GAME_OVER, CLOSE };
    GameState gameState;

    Game()
        : deck(),
          cash(),
          player(deck, cash),
          dealer(deck, cash),
          gameState(DEALING)
    { 
        isGameRunning = true; 
    }

    void promptPlayer(Gui& gui) {
        ImGui::Begin("Player Actions");
        int choice = gui.getPlayerAction();
        ImGui::End();
        if (choice != 0) {  // Ensure we wait until an action is chosen
            switch (choice) {
                case 1:
                    player.hit();
                    checkEndGameState();
                    if (!player.hand.isBust() && !player.hand.isBlackjack()) {
                        playerHitLoop(gui);
                    } else {
                        gameState = DEALER_TURN;  // Move to dealer's turn
                    }
                    break;
                case 2:
                    player.stand();
                    gameState = DEALER_TURN;  // Move to dealer's turn after standing
                    break;
                case 3:
                    player.doubleDown();
                    gameState = DEALER_TURN;  // Double down means the player's turn is over
                    break;
                case 4:
                    player.split();
                    break;
                default:
                    ui.showMessage("Invalid choice!");
            }
        }
    }
    
    void playerHitLoop(Gui& gui) {
        while (!player.hand.isBust() && !player.hand.isBlackjack() && !(player.isstanding)) {
            std::cout << "entered loop\n";
            int choice;
            if (ImGui::Begin("Hit or Stand?")) {
                    ImGui::Text("Do you want to hit or stand?");
                    if (ImGui::Button("Hit")) {
                        choice = 1;
                    }
                    if (ImGui::Button("Stand")) {
                        choice = 2;
                    }
                    ImGui::End();
                }

            switch (choice) {
                case 1: 
                    player.hit();
                    checkEndGameState();
                    break;
                case 2:
                    player.stand();
                    gameState = DEALER_TURN;
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
        gameState = PLAYER_TURN;
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

    void GameLogic(Gui& gui) {
        bool startAgain = false;

        switch (gameState) {
            case DEALING:
                resetGame();
                dealInitialCards();
                gameState = PLAYER_TURN;  // Move to player turn after dealing
                break;

            case PLAYER_TURN:
                promptPlayer(gui);
                break;

            case DEALER_TURN:
                dealerTurn();
                gameState = GAME_OVER;  // Once dealer's turn is done, move to game over
                break;

            // 
            case GAME_OVER:
                if (ImGui::Begin("Play Again?")) {
                    ImGui::Text("Do you want to play again?");
                    if (ImGui::Button("Yes")) {
                        gameState = DEALING;
                    }
                    if (ImGui::Button("No")) {
                        gameState = CLOSE;
                    }
                    ImGui::End();
                }
                ui.showMessage("Game Over");  // Display game over message
                break;

            case CLOSE:
                if (ImGui::Begin("Exit Game?")) {
                    ImGui::Text("Do you want to exit?");
                    if (ImGui::Button("Yes")) {
                        gui.getWindow().close();  // Close the window when the user confirms
                        isGameRunning = false;
                    }
                    if (ImGui::Button("No")) {
                        gameState = GAME_OVER;  // Return to the game over state if user doesn't want to close
                    }
                    ImGui::End();
                }
                break;
        }
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