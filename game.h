#ifndef GAME_U
#define GAME_U

#include <iostream>

#include "player.h"

class Game {
  public:
    Game() { isRunning = true; }
    
    void initialiseGame() {
        // maybe?
    }

    void coreLoop() {
        while (isRunning) {
            switch () {
                case 1: ;
                case 2: ;
                case 3: ;
                case 4: ;
                case 5: ;
                default: break;
                }
            }
    }

    void playerTurn() {
        std::cout << "Please Enter your bet for this round: " << std::endl;

    }

    void start() {
        Deck deck;
        Player player(Deck& deck);

        // need to loop through amount of player hands

        // need to write dealer ai FUCK
    }

    void end() {}

  private:
    bool isRunning;
};

#endif