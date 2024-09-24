#ifndef GUI_U
#define GUI_U

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

class Gui {
  public:
    Gui() {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Blackjack GUI");
        window.setFramerateLimit(60);
        
        // Initialize ImGui and SFML
        ImGui::SFML::Init(window);
        
        sf::Clock deltaClock;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                ImGui::SFML::ProcessEvent(event);
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            ImGui::SFML::Update(window, deltaClock.restart());

            // Clear the window and draw ImGui interface
            window.clear();
            // Add your ImGui logic here
            ImGui::Begin("Blackjack");

            // Draw UI elements for your classes

            ImGui::End();
            ImGui::SFML::Render(window);
            window.display();
        }

        // Clean up
        ImGui::SFML::Shutdown();
    }

};

#endif