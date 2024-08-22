#ifndef GAME_U
#define GAME_U

#include <iostream>
#include "player.h"

class Game {
  public:

    Game() {
        isRunning = true;
    }

    void start() {
        Deck deck;
        Player player(Deck& deck);

        // need to loop through amount of player hands

        // need to write dealer ai FUCK

        while (isRunning) {
            switch () {
                case 1: player.hit();
                case 2: ;
                case 3: ;
                case 4: ;
                case 5: ;
                default: break;
                }
            }
    }

    void end() {

    }

  private:
    bool isRunning;
};

#endif