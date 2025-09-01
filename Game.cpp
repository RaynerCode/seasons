#include "Game.h"
#include <iostream>
constexpr int FRAME_RATE_LIMIT = 60;

Game::Game() :m_map(3){
    for(int i = 0; i < 5; i++) {
        m_map.createWall({200,20},{600,600.f - static_cast<float>(300 * i)});
        m_map.createWall({200,20},{200,470 - static_cast<float>(300 * i)});
    }
    std::cout << "Game constructed" << std::endl;
}

void handleEvent(sf::RenderWindow& window, Player& player) {
    // check all the window's events that were triggered since the last iteration of the loop
    while (const std::optional event = window.pollEvent())
    {
        // "close requested" event: we close the window
        if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
            window.close();
    }
}

void Game::Run() {
    sf::RenderWindow m_window(sf::VideoMode::getFullscreenModes()[0], "My Game Window", sf::Style::None);
    m_window.setFramerateLimit(FRAME_RATE_LIMIT);
    while(m_window.isOpen()){

        handleEvent(m_window, m_player);
        m_window.clear(sf::Color::Black);

        m_player.update(m_map);


        m_player.Draw(m_window);
        m_map.Draw(m_window);

        m_window.setView(sf::View(sf::Rect<float>({0,m_player.getPosition().y - 700}, m_window.getView().getSize())));

        m_window.display();
    }
}


