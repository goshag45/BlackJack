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

    while (game.isGameRunning) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            // Check if the event type is a resize event
            if (event.type == sf::Event::Resized) {
                // Adjust the viewport of the render window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::Closed) {
                window.close();
                game.isGameRunning = false;
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        window.clear();
        
        game.GameLogic(gui);
        gui.GameWindow(game.getPlayer(), game.getDealer());
        
        ImGui::SFML::Render(window);
        window.display();
    }
    gui.shutDownGUI();
    return 0;
}