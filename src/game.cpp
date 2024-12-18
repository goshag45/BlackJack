#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h> 

#include "card.h"
#include "cash.h"
#include "dealer.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "gui.h"
#include "ui.h"
#include "game.h"

Game::Game()
    : deck(),
        cash(),
        player(deck, cash),
        dealer(deck, cash),
        gameState(START)
{ 
    isGameRunning = true; 
}

std::string Game::getGameEndStateString() {
    if (gameEndState == Game::GameEndState::WIN) {
        return "You win!";
    } else if (gameEndState == Game::GameEndState::PUSH) {
        return "Its a push!";
    } else if (gameEndState == Game::GameEndState::LOSE) {
        return "You Lose!";
    }
    return "ERROR, no gameEndState";
}

void Game::promptPlayer(Gui& gui) {
    int choice = gui.getPlayerAction();
    if (choice != 0) {  // Ensure we wait until an action is chosen
        switch (choice) {
            case 1:
                player.hit();
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
                // can split with 1 card
                // can split with 0 cards (and crash)
                player.split();
                break;
            case 5:
                player.surrender();
                gameState = GAME_OVER;
                break;
        }
    }
}


// not sure how im gonna implement playing on multiple cards in turn
void Game::split(Gui& gui) {
    
    for (Hand hand : player.getHandVector()) {
        promptPlayer(gui);
    }
}

void Game::dealerTurn() {
    while (dealer.canhit) {
        dealer.hit();
        if (dealer.hand.getTotalValue() > 17) {
            dealer.canhit = false;
        }
    }
}

void Game::dealInitialCards() {
    dealer.hit();
    dealer.hit();
    player.hit();
    player.hit();
    gameState = PLAYER_TURN;
}

void Game::winCheck() {
    if (!winsUpdated) {
        int playerTotal = player.hand.getTotalValue();
        int dealerTotal = dealer.hand.getTotalValue();

        if (player.hand.isBust()) {
            gameEndState = GameEndState::LOSE;
            loseCount++;
        } else if (dealer.hand.isBust()) {
            gameEndState = GameEndState::WIN;
            winCount++;
        } else if (player.hand.isBlackjack()){
            gameEndState = GameEndState::WIN;
            winCount++;
        } else if (playerTotal > dealerTotal) {
            gameEndState = GameEndState::WIN;
            winCount++;
        } else if (playerTotal < dealerTotal && !(dealer.isbusted)) {
            gameEndState = GameEndState::LOSE;
            loseCount++;
        } else if (playerTotal == dealerTotal) {
            gameEndState = GameEndState::PUSH;
            pushCount++;
        }
        winsUpdated = true;
    }
}

void Game::resetGame() {
    player.reset();
    dealer.reset();
    dealer.canhit = true;
    isDealerFirstTurn = true;
    recordStats = true;
    betHasPayed = false;
    winsUpdated = false;
    numGamesUpdated = false;  
}

void Game::startGameWindow(Gui& gui) {
    if (gameState != START && gameState != BET) {
        gui.GameWindow(getPlayer(), getDealer(), isDealerFirstTurn);
    }
}

void Game::startBetWindow(Gui& gui) {
    if (gameState != START) {
        gui.cashWindow(cash.currentBet, cash.cash);
    }
}

float Game::winPercentage() {
    if (numGames == 0) {return 0.0;}
    return (static_cast<float>(winCount) / numGames) * 100;
}

void Game::betSurrenderCheck() {
    if (player.issurrendered && betHasPayed == false) {
        cash.surrender();
        betHasPayed = true;
    }
}

void Game::betWinCheck() {
    if (gameEndState == GameEndState::WIN && betHasPayed == false) {
        cash.betWin();
        betHasPayed = true;
    }
}

void Game::GameLogic(Gui& gui) {
    int startOrQuit = -1;
    int toBetOrNotToBet = -1;
    int hitAgain = -1;
    int playAgain = -1;
    int exitGame = -1;
    std::string gameEndStateStatus;
    
    startGameWindow(gui);
    startBetWindow(gui);
    gui.statsWindow("Wins", winCount, "Win Rate", winPercentage());

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
            // function for statistics 
            if (!numGamesUpdated) {
                numGames++;
                numGamesUpdated = true;
            }
            winCheck();
            gameEndStateStatus = getGameEndStateString();
            betSurrenderCheck();
            betWinCheck();
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

const Player& Game::getPlayer() const { return player; }
const Dealer& Game::getDealer() const { return dealer; }