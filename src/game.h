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
    enum GameState { START, BET, DEALING, PLAYER_TURN, HIT_LOOP, DEALER_TURN, GAME_OVER, CLOSE };
    GameState gameState;

    Game()
        : deck(),
          cash(),
          player(deck, cash),
          dealer(deck, cash),
          gameState(START)
    { 
        isGameRunning = true; 
    }

    void promptPlayer(Gui& gui) {
        int choice = gui.getPlayerAction();
        if (choice != 0) {  // Ensure we wait until an action is chosen
            switch (choice) {
                case 1:
                    player.hit();
                    // checkEndGameState();
                    if (!player.hand.isBust() && !player.hand.isBlackjack()) {
                        gameState = HIT_LOOP;
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

    // void getPlayerBet() {
    //     cash.cash = ui.getPlayerInputInt("Enter bet: ");
    // }

    void resetGame() {
        player.reset();
        dealer.reset();
        isDealerFirstTurn = true;
    }

    void GameLogic(Gui& gui) {
        int startOrQuit = -1;
        int toBetOrNotToBet = -1;
        int hitAgain = -1;
        int playAgain = -1;
        int exitGame = -1;
        if (gameState != START && gameState != BET) {
            gui.GameWindow(getPlayer(), getDealer(), isDealerFirstTurn);
        }
        gui.betWindow(cash.currentBet);

        switch (gameState) {
            case START:
                startOrQuit = gui.startWindow();
                if (startOrQuit == 1) {
                    gameState = BET;
                } else if (startOrQuit == 0) {
                    gui.getWindow().close();
                    isGameRunning = false;
                }
                break;
            
            case BET:
                toBetOrNotToBet = gui.enterBetWindow(cash.currentBet);
                if (toBetOrNotToBet == 1) {
                    gameState = DEALING;
                } else if (toBetOrNotToBet == 0) {
                    gameState = START;
                }
                break;

            case DEALING:
                resetGame();
                dealInitialCards();
                gameState = PLAYER_TURN;
                break;

            case PLAYER_TURN:
                promptPlayer(gui);
                break;

            case HIT_LOOP:
                hitAgain = gui.binaryGUIPromp("Hit or Stand?", "Hit", "Stand");
                if (hitAgain == 1) {
                    player.hit();
                    // checkEndGameState();
                    if (player.hand.isBust() || player.hand.isBlackjack()) {
                        gameState = DEALER_TURN;
                    }
                } else if (hitAgain == 0) {
                    player.stand();
                    gameState = DEALER_TURN;
                } 
                break;

            case DEALER_TURN:
                isDealerFirstTurn = false;
                dealerTurn();
                gameState = GAME_OVER;
                break;

            case GAME_OVER:
                playAgain = gui.binaryGUIPromp("Play Again?", "Yes", "No");
                if (playAgain == 1) {
                    gameState = START;
                } else if (playAgain == 0) {
                    gameState = CLOSE;
                } 
                break;

            case CLOSE:
                exitGame = gui.binaryGUIPromp("Exit Game?", "Yes", "No");
                if (exitGame == 1) {
                    gui.getWindow().close();
                    isGameRunning = false;
                } else if (exitGame == 0) {
                    gameState = GAME_OVER;
                }
                break;
        }
    }

    const Player& getPlayer() const { return player; }
    const Dealer& getDealer() const { return dealer; }
    const bool& getIsFirstTurn() const {return isDealerFirstTurn; }

  private:
    // void checkEndGameState() {
    //     playerBustCheck();
    //     playerBlackJackCheck();
    // }

    Deck deck;
    Cash cash;
    Player player;
    Dealer dealer;
    Ui ui;

    bool isDealerFirstTurn;
};

#endif