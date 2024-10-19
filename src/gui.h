#ifndef GUI_U
#define GUI_U

#include <iostream>
#include <string>
#include <unordered_map> // For caching card textures

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "card.h"
#include "cash.h"
#include "dealer.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "ui.h"
#include "game.h"

class Gui {
  public:
    Gui() : window(sf::VideoMode(800, 600), "Blackjack GUI") {
        // window.setFramerateLimit(30);
        window.setVerticalSyncEnabled(true);
    };
    // Functions to setup SFML imgui window
    inline void startGUIWindow() { ImGui::SFML::Init(window); }
    inline void startClockGUI() { deltaClock.restart(); }
    inline void shutDownGUI() { ImGui::SFML::Shutdown(); }

    int getPlayerAction() {
        ImGui::Begin("Player Actions");
        int playerChoice = 0;
        if (ImGui::Button("Hit"))           { std::cout << "Hit\n"; playerChoice = 1;}
        if (ImGui::Button("Stand"))         { std::cout << "Stand\n"; playerChoice = 2;}
        if (ImGui::Button("Double Down"))   { std::cout << "Double Down\n"; playerChoice = 3;}
        if (ImGui::Button("Split"))         { std::cout << "Split\n"; playerChoice = 4;}
        ImGui::End();
        return playerChoice;
    }

    int binaryGUIPrompt(std::string _title, const std::string _yesOption, const std::string _noOption) {
        // imgui takes const char* not string FOR SOME REASON
        const char* title = _title.c_str();
        const char* yesOption = _yesOption.c_str();
        const char* noOption = _noOption.c_str();
        ImGui::Begin(title);
        int result = -1;
        if (ImGui::Button(yesOption)) { result = 1; }
        if (ImGui::Button(noOption)) { result = 0; }
        ImGui::End();
        return result;
    }

    int gameOverWindow(const std::string _gameStatus, std::string _title, const std::string _yesOption, const std::string _noOption) {
        const char* title = _title.c_str();
        const char* gameStatus = _gameStatus.c_str();
        const char* yesOption = _yesOption.c_str();
        const char* noOption = _noOption.c_str();
        ImGui::Begin(title);
        ImGui::Text(gameStatus);
        int result = -1;
        if (ImGui::Button(yesOption)) { result = 1; }
        if (ImGui::Button(noOption)) { result = 0; }
        ImGui::End();
        return result;        
    }


    void showHand(const Hand& hand, bool isDealerFirstTurn) {
        int cardIndex = 0;
        for (const Card& card : hand.getHandVector()) {
            DisplayCard(card, isDealerFirstTurn, cardIndex);
            ImGui::SameLine(); // Display cards horizontally
            cardIndex++;
        }
        ImGui::NewLine(); // After all cards, start a new line
    }

    void DisplayCard(const Card& card, bool isDealerFirstTurn, int cardIndex) {
        std::string cardName;
        if (isDealerFirstTurn && cardIndex == 1) {
            cardName = "blank.png";
        } else {
            cardName = BuildCardFileName(card);
        }


        // Check if the texture is already loaded in the map
        if (cardTextures.find(cardName) == cardTextures.end()) {
            sf::Texture texture;
            if (!texture.loadFromFile(imgFilePath + cardName)) {
                std::cout << "Image import error for " << cardName << '\n';
                return;
            }
            // Add the texture to the map
            cardTextures[cardName] = texture;
        }

        // Get the texture from the map
        sf::Texture& texture = cardTextures[cardName];
        // Render the image with the specified size
        ImGui::Image(texture, cardSize);
    }

    std::string BuildCardFileName(const Card& card) {
        std::string cardName;
        std::string cardSuit = card.getSuit();
        cardSuit[0] = std::tolower(cardSuit[0]);
        std::string cardFace = card.getFace();

        if ((card.getValue() < 11) && (card.getFace() != "JACK") && 
            (card.getFace() != "QUEEN") && (card.getFace() != "KING")) {
            cardFace = std::to_string(card.getValue());
        }

        cardName = cardFace + "_of_" + cardSuit + ".png";
        return cardName;
    }

    void GameWindow(const Player& player, const Dealer& dealer, bool isDealerFirstTurn) {
        ImGui::Begin("Game Window");

        // Render the dealer's hand
        ImGui::Text("Dealer's Hand:");
        showHand(dealer.getHand(), isDealerFirstTurn);

        ImGui::Separator();

        // Render the player's hand
        ImGui::Text("Player's Hand:");
        showHand(player.getHand(), false);

        ImGui::Separator();

        ImGui::End();
    }

    // NOT USING GENERIC FUNCTION AS IM LEAVING THIS ONE OPEN TO EXPANSION
    int startWindow() {
        ImGui::Begin("Menu");
        int playerChoice = -1;

        if (ImGui::Button("Play Game"))    { std::cout << "Play\n"; playerChoice = 1;}
        if (ImGui::Button("Exit"))         { std::cout << "Exit\n"; playerChoice = 0;}

        ImGui::End();
        return playerChoice;
    }

    int enterBetWindow(int& bet) {
        ImGui::Begin("Bet");
        ImGui::Text("Please enter your bet: ");
        ImGui::InputInt("##intInput", &bet);
        int playerChoice = -1;

        if (ImGui::Button("Submit"))    { playerChoice = 1; }
        if (ImGui::Button("Cancel"))    { playerChoice = 0; }

        ImGui::End();
        return playerChoice;
    }

    void cashWindow(int& bet, int& cash) {
        ImGui::Begin("Cash");
        ImGui::Text("Current Bet: %d", bet);
        ImGui::Text("Total Cash: %d", cash);
        ImGui::End();
    }

    sf::RenderWindow& getWindow() { return window; }
    sf::Clock& getClock() { return deltaClock; }

  private:
    ImVec2 cardSize = ImVec2(83.3f, 121.0f);  // Desired width and height
    std::string imgFilePath = "..\\..\\src\\img\\";

    sf::RenderWindow window;
    sf::Clock deltaClock;

    // Map to store textures for each card (caching)
    std::unordered_map<std::string, sf::Texture> cardTextures;
};

#endif