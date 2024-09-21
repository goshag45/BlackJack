# Add executable
add_executable(Blackjack 
    main.cpp
    main.cpp
    card.h
    cash.h
    dealer.h
    deck.h
    game.h
    hand.h
    player.h
    ui.h
)
target_link_libraries(Blackjack PRIVATE ImGui-SFML::ImGui-SFML)