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

    int getPlayerAction() {
        if (ImGui::Button("Hit"))           { std::cout << "Hit\n"; return 1;}
        if (ImGui::Button("Stand"))         { std::cout << "Stand\n"; return 2;}
        if (ImGui::Button("Double Down"))   { std::cout << "Double Down\n"; return 3;}
        if (ImGui::Button("Split"))         { std::cout << "Split\n"; return 4;}
        return 0;
    }

    int getPlayerActionLoop() {
        if (ImGui::Button("Hit"))           { std::cout << "Hit\n"; return 1;}
        if (ImGui::Button("Stand"))         { std::cout << "Stand\n"; return 2;}
        return 0;
    }

    void showHand(const Hand& hand) {
        for (const Card& card : hand.getHandVector()) {
            DisplayCard(card);
            ImGui::SameLine(); // Display cards horizontally
        }
        ImGui::NewLine(); // After all cards, start a new line
    }

    void DisplayCard(const Card& card) {
        std::string cardName = BuildCardFileName(card);

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

    void GameWindow(const Player& player, const Dealer& dealer) {
        ImGui::Begin("Game Window");

        // Render the dealer's hand
        ImGui::Text("Dealer's Hand:");
        showHand(dealer.getHand());

        ImGui::Separator();

        // Render the player's hand
        ImGui::Text("Player's Hand:");
        showHand(player.getHand());

        ImGui::Separator();

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