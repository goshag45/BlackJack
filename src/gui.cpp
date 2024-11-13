#include <iostream>
#include <string>
#include <unordered_map> // For caching card textures

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "gui.h"
#include "game.h"

//class Game;

Gui::Gui() : window(sf::VideoMode(800, 600), "Blackjack GUI") {
    // window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);
};
// Functions to setup SFML imgui window
inline void Gui::startGUIWindow() { ImGui::SFML::Init(window); }
inline void Gui::startClockGUI() { deltaClock.restart(); }
inline void Gui::shutDownGUI() { ImGui::SFML::Shutdown(); }

int Gui::getPlayerAction() {
    ImGui::Begin("Player Actions");
    int playerChoice = 0;
    if (ImGui::Button("Hit"))           { playerChoice = 1;}
    if (ImGui::Button("Stand"))         { playerChoice = 2;}
    if (ImGui::Button("Double Down"))   { playerChoice = 3;}
    if (ImGui::Button("Split"))         { playerChoice = 4;}
    if (ImGui::Button("Surrender"))     { playerChoice = 5;}
    ImGui::End();
    return playerChoice;
}

int Gui::binaryGUIPrompt(std::string _title, const std::string _yesOption, const std::string _noOption) {
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

// basically an overload of the above ^ with addtional field for game state
int Gui::gameOverWindow(std::string _gameStatus, std::string _text, const std::string _yesOption, const std::string _noOption) {
    const char* title = _gameStatus.c_str();
    const char* text = _text.c_str();
    const char* yesOption = _yesOption.c_str();
    const char* noOption = _noOption.c_str();

    ImGui::Begin(title);
    ImGui::Text(text);
    int result = -1;
    if (ImGui::Button(yesOption)) { result = 1; }
    if (ImGui::Button(noOption)) { result = 0; }
    ImGui::End();
    return result;        
}

void Gui::statsWindow(std::string _stat1, int val1, std::string _stat2, int val2) {
    std::string str1 = _stat1 + ": " + std::to_string(val1);
    std::string str2 = _stat2 + ": " + std::to_string(val2);
    const char* stat1 = str1.c_str();
    const char* stat2 = str2.c_str();
    ImGui::Begin("Statistics:");
    ImGui::Text(stat1);
    ImGui::Text(stat2);
    ImGui::End();
}

void Gui::showHand(const Hand& hand, bool isDealerFirstTurn) {
    int cardIndex = 0;
    for (const Card& card : hand.getHandVector()) {
        DisplayCard(card, isDealerFirstTurn, cardIndex);
        ImGui::SameLine(); // Display cards horizontally
        cardIndex++;
    }
    ImGui::NewLine(); // After all cards, start a new line
}

void Gui::DisplayCard(const Card& card, bool isDealerFirstTurn, int cardIndex) {
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

std::string Gui::BuildCardFileName(const Card& card) {
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

void Gui::GameWindow(const Player& player, const Dealer& dealer, bool isDealerFirstTurn) {
    ImGui::Begin("Game Window");

    // Render the dealer's hand
    ImGui::Text("Dealer's Hand:");
    showHand(dealer.getHand(), isDealerFirstTurn);

    ImGui::Separator();

    for (Hand hand : player.getHandVector()) {
        // Render the player's hand
        ImGui::Text("Player's Hand:");
        showHand(player.getHand(), false);
    }

    ImGui::Separator();

    ImGui::End();
}

// NOT USING GENERIC FUNCTION AS IM LEAVING THIS ONE OPEN TO EXPANSION
int Gui::startWindow() {
    ImGui::Begin("Menu");
    int playerChoice = -1;

    if (ImGui::Button("Play Game"))    { playerChoice = 1;}
    if (ImGui::Button("Exit"))         { playerChoice = 0;}

    ImGui::End();
    return playerChoice;
}

int Gui::enterBetWindow(int& bet) {
    ImGui::Begin("Bet");
    ImGui::Text("Please enter your bet: ");
    ImGui::InputInt("##intInput", &bet);
    int playerChoice = -1;

    if (ImGui::Button("Submit"))    { playerChoice = 1; }
    if (ImGui::Button("Cancel"))    { playerChoice = 0; }

    ImGui::End();
    return playerChoice;
}

// hardcoded stats for now
void Gui::cashWindow(int& bet, int& cash) {
    ImGui::Begin("Cash");
    ImGui::Text("Current Bet: %d", bet);
    ImGui::Text("Total Cash: %d", cash);
    ImGui::End();
}

sf::RenderWindow& Gui::getWindow() { return window; }
sf::Clock& Gui::getClock() { return deltaClock; }