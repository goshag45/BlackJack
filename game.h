#ifndef GAME_U
#define GAME_U

#include <iostream>
#include "player.h"

class Game {
  private:
    bool isRunning;

  public:

    Game() {
        isRunning = true;
    }

    void start() {
        Player player;

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
};

#endif