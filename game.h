#ifndef GAME_U
#define GAME_U

#include <iostream>

#include "card.h"
#include "cash.h"
#include "dealer.h"
#include "deck.h"
#include "hand.h"
#include "player.h"

class Game {
  public:
    Game() { 
        // initialise relevant game objects
        Deck deck;
        Cash cash;
        Player player = Player(deck, cash);
        Hand playerHand;
        // dont like that im sharing cash object here!
        Dealer dealer = Dealer(deck, cash);
        Hand dealerHand;

        isRunning = true; 
    }
    
    void initialiseGame() {
        // maybe?
    }

    void coreLoop() {
        while (isRunning) { }

    }

    void getPlayerBet() {
        std::cout << "Please Enter your bet for this round: " << std::endl;
        // add type checking?
        std::cin >> bet;
    }

    void start() {
        Deck deck;
        Player player(Deck& deck);

        // need to loop through amount of player hands
    }

    void end() {}

  private:
    bool isRunning;
    // THIS NEEDS TO LINK TO CASH
    int bet = 0;
};

#endif