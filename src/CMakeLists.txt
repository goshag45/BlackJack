# Add executable
add_executable(Blackjack 
    main.cpp
    card.h
    card.cpp
    cash.h
    dealer.h
    deck.h
    game.h
    hand.h
    player.h
    gui.h
)
target_link_libraries(Blackjack PRIVATE ImGui-SFML::ImGui-SFML)
set_target_properties(Blackjack PROPERTIES WIN32_EXECUTABLE TRUE)