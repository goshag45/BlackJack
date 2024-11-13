#ifndef GUI_U
#define GUI_U

#include <SFML/Graphics.hpp>
#include <imgui.h>

#include "unordered_map"

class Gui {
  public:
    Gui() : window(sf::VideoMode(800, 600), "Blackjack GUI") {};
    // Functions to setup SFML imgui window
    inline void startGUIWindow() {}
    inline void startClockGUI() {}
    inline void shutDownGUI() {}

    int getPlayerAction() {}

    int binaryGUIPrompt(std::string _title, const std::string _yesOption, const std::string _noOption) {}

    // basically an overload of the above ^ with addtional field for game state
    int gameOverWindow(std::string _gameStatus, std::string _text, const std::string _yesOption, const std::string _noOption) {}

    void statsWindow(std::string _stat1, int val1, std::string _stat2, int val2) {}

    void showHand(const Hand& hand, bool isDealerFirstTurn) {}

    void DisplayCard(const Card& card, bool isDealerFirstTurn, int cardIndex) { }

    std::string BuildCardFileName(const Card& card) {}

    void GameWindow(const Player& player, const Dealer& dealer, bool isDealerFirstTurn) {}

    // NOT USING GENERIC FUNCTION AS IM LEAVING THIS ONE OPEN TO EXPANSION
    int startWindow() {}

    int enterBetWindow(int& bet) {}

    // hardcoded stats for now
    void cashWindow(int& bet, int& cash) {}

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