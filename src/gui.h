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

            GameWindow();
            PlayerWindow();
            
            ImGui::SFML::Render(window);
            window.display();
        }

        // Clean up
        ImGui::SFML::Shutdown();
    }

    void GameplayActions() {
        if (ImGui::Button("Hit")) {
            std::cout << "Hit\n";
        }
        if (ImGui::Button("Stand")) {
            std::cout << "Stand\n";
        }
        if (ImGui::Button("Double Down")) {
            std::cout << "Double Down\n";
        }
        if (ImGui::Button("Split")) {
            std::cout << "Split\n";
        }
    }

    void GameWindow() {
        ImGui::Begin("Game Screen");

        // Load the texture
        static sf::Texture texture;
        std::string imgFilePath = "..\\..\\src\\";
        std::string ace = "ace_of_spades.png";

        if (!texture.loadFromFile(imgFilePath+ace)) {
            std::cout << "Image import error\n";
        } else {
            // Get the texture size
            sf::Vector2u texSize = texture.getSize();
            
            ImVec2 imgSize = ImVec2(83.3f, 121.0f);  // Desired width and height

            // Render the image with the specified size
            ImGui::Image(texture, imgSize);
        }

        ImGui::End();
    }
    void PlayerWindow() {
        ImGui::Begin("Actions");

        GameplayActions();

        ImGui::End();
    }
};

#endif