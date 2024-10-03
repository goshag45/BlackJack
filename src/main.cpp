#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "game.h"
#include "gui.h"

int main() {
    Game game;
    Gui gui;

    gui.startGUIWindow();
    gui.startClockGUI();
    
    sf::RenderWindow& window = gui.getWindow();
    sf::Clock& deltaClock = gui.getClock();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        window.clear();

        gui.GameWindow();
        gui.PlayerWindow();
        
        game.dealInitialCards();
        game.displayPlayerHand(gui);
        
        ImGui::SFML::Render(window);
        window.display();
    }
    gui.shutDownGUI();

    return 0;
}