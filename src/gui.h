#ifndef GUI_U
#define GUI_U

#include <iostream>
#include <string>

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
    Gui(): window(sf::VideoMode(800, 600), "Blackjack GUI") {
        window.setFramerateLimit(60);
    };

    void startGUIWindow() {
        // Initialize ImGui and SFML
        ImGui::SFML::Init(window);
    }

    void startClockGUI() {
        deltaClock.restart();
    }
    
    void shutDownGUI() {
        // Clean up
        ImGui::SFML::Shutdown();
    }

    void GameplayActions() {
        if (ImGui::Button("Hit"))           { std::cout << "Hit\n"; }
        if (ImGui::Button("Stand"))         { std::cout << "Stand\n"; }
        if (ImGui::Button("Double Down"))   { std::cout << "Double Down\n"; }
        if (ImGui::Button("Split"))         { std::cout << "Split\n"; }
    }

    void GameWindow() {
        ImGui::Begin("Game Screen");
        // DisplayCard();
        ImGui::End();
    }
    void PlayerWindow() {
        ImGui::Begin("Actions");
        GameplayActions();
        ImGui::End();
    }

    void showHand(const Player& player) {
        for (const Card& card : player.getPlayerHand().getHandVector()) {
            DisplayCard(card);
        }
    }

    void DisplayCard(const Card& card) {
        // Load the texture
        static sf::Texture texture;
        std::string cardName = BuildCardFileName(card);

        if (!texture.loadFromFile(imgFilePath+cardName)) {
            std::cout << "Image import error\n";
        } else {
            // Get the texture size
            sf::Vector2u texSize = texture.getSize();
            // Render the image with the specified size
            ImGui::Image(texture, cardSize);
        }
    }

    std::string BuildCardFileName(const Card& card) {
        std::string cardName;
        // NUMBER
        std::string cardSuit = card.getSuit();
        cardSuit[0] = std::tolower(cardSuit[0]);
        // TYPE
        std::string cardFace = card.getFace();
        // DAMN this is ugly - please fix !!!
        if ((card.getValue() < 11) && (card.getFace() != "JACK") && (card.getFace() != "QUEEN") && (card.getFace() != "KING")) {
            cardFace = std::to_string(card.getValue());
        }

        cardName = cardFace + "_of_" + cardSuit + ".png";
        std::cout << cardName << '\n';
        return cardName;
    }

    sf::RenderWindow& getWindow() { return window; }
    sf::Clock& getClock() { return deltaClock; }

  private:
    ImVec2 cardSize = ImVec2(83.3f, 121.0f);  // Desired width and height
    std::string imgFilePath = "..\\..\\src\\img\\";

    sf::RenderWindow window;
    sf::Clock deltaClock;
};

#endif