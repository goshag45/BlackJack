#ifndef GAME_U
#define GAME_U

#include "player.h"
#include "dealer.h"

class Gui;

class Game {
  public:
    bool isGameRunning;
    enum GameState { START, BET, DEALING, PLAYER_TURN, HIT_LOOP, DEALER_TURN, GAME_OVER, CLOSE };
    enum class GameEndState { WIN, LOSE, PUSH };
    GameState gameState;
    GameEndState gameEndState = Game::GameEndState::LOSE;

    Game(): 
        deck(),
        cash(),
        player(deck, cash),
        dealer(deck, cash),
        gameState(START) {}

    std::string getGameEndStateString() {}

    void promptPlayer(Gui& gui) {}

    void split(Gui& gui) {}

    void dealerTurn() {}

    void dealInitialCards() {}

    void winCheck() {}

    void resetGame() {}

    void startGameWindow(Gui& gui) {}

    void startBetWindow(Gui& gui) {}

    float winPercentage() {}

    void betSurrenderCheck() {}
    
    void betWinCheck() {}

    void GameLogic(Gui& gui) {}

    const Player& getPlayer() const {}
    const Dealer& getDealer() const {}

  private:
    Deck deck;
    Cash cash;
    Player player;
    Dealer dealer;

    bool isDealerFirstTurn = true;;
    bool recordStats = true;
    bool betHasPayed = false;
    bool winsUpdated = false;
    bool numGamesUpdated = false;

    int pushCount = 0;
    int winCount = 0;
    int loseCount = 0;
    int numGames = 0;
};

#endif