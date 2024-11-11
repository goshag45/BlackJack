# Add executable
add_executable(Blackjack 
    main.cpp
    card.h
    card.cpp
    cash.h
    cash.cpp
    dealer.h
    dealer.cpp
    deck.h
    deck.cpp
    game.h
    game.cpp
    hand.h
    hand.cpp
    player.h
    player.cpp
    gui.h
    gui.cpp
)
target_link_libraries(Blackjack PRIVATE ImGui-SFML::ImGui-SFML)
set_target_properties(Blackjack PROPERTIES WIN32_EXECUTABLE TRUE)