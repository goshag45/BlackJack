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

class Gui;

class Game {
  public:
    bool isGameRunning;
    enum GameState { START, BET, DEALING, PLAYER_TURN, HIT_LOOP, DEALER_TURN, GAME_OVER, CLOSE };
    enum class GameEndState { WIN, LOSE, PUSH };
    GameState gameState;
    GameEndState gameEndState;

    Game()
        : deck(),
          cash(),
          player(deck, cash),
          dealer(deck, cash),
          gameState(START)
    { 
        isGameRunning = true; 
    }

    std::string getGameEndStateString() {
        if (gameEndState == Game::GameEndState::WIN) {
            return "You win!";
        } else if (gameEndState == Game::GameEndState::PUSH) {
            return "Its a push!";
        } else if (gameEndState == Game::GameEndState::LOSE) {
            return "You Lose!";
        }
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

    // I DONT THINK THIS FULLY WORKS - DOESNT DRAW UNTIL 17 SOMETMIES - INVESTIGATE
    void dealerTurn() {
        if (dealer.canhit) { ui.showMessage("Dealer playing..."); }
        while (dealer.canhit) {
            dealer.dealerhit();
            // ui.showMessage("HITTED");
            std::cout << dealer.canhit << '\n';
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

    void winCheck() {
        if (player.hand.isBust()) {
            gameEndState = GameEndState::LOSE;
        } else if (player.hand.getTotalValue() == dealer.hand.getTotalValue()) {
            gameEndState = GameEndState::PUSH;
        } else if (player.hand.isBlackjack()){
            gameEndState = GameEndState::WIN;
        } else if (player.hand.getTotalValue() < dealer.hand.getTotalValue()) {
            gameEndState = GameEndState::WIN;
        }
    }

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
        std::string gameEndStateStatus;
        if (gameState != START && gameState != BET) { // ADDING SECOND CONDITION, NOW DISPLAYS BETWINDOW???
            gui.GameWindow(getPlayer(), getDealer(), isDealerFirstTurn);
        }
        if (gameState != START) {
            gui.cashWindow(cash.currentBet, cash.cash);
        }

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
                    cash.setBet(cash.currentBet);
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
                hitAgain = gui.binaryGUIPrompt("Hit or Stand?", "Hit", "Stand");
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
                winCheck();
                gameEndStateStatus = getGameEndStateString();
                if (gameEndState == GameEndState::WIN) {
                    cash.betWin();
                }
                // TODO: DISPLAY DIFFERENT MESSAGE BASED ON GAME OUTCOME
                playAgain = gui.gameOverWindow(gameEndStateStatus, "Play Again?", "Yes", "No");
                if (playAgain == 1) {
                    gameState = START;
                } else if (playAgain == 0) {
                    gameState = CLOSE;
                } 
                break;

            case CLOSE:
                exitGame = gui.binaryGUIPrompt("Exit Game?", "Yes", "No");
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
    Deck deck;
    Cash cash;
    Player player;
    Dealer dealer;
    Ui ui;

    bool isDealerFirstTurn;
};

#endif