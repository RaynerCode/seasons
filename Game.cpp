#include "Game.h"
#include <iostream>
constexpr int FRAME_RATE_LIMIT = 60;

Game::Game() :m_map(3){
    std::cout << "Game constructed" << std::endl;
}

void Game::Run() {
    sf::RenderWindow m_window(sf::VideoMode::getFullscreenModes()[0], "My Game Window", sf::Style::None);
    m_window.setFramerateLimit(FRAME_RATE_LIMIT);

    while(m_window.isOpen()){

        while (const std::optional event = m_window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
                m_window.close();
        }
        m_window.clear(sf::Color::Black);

        m_player.MoveByVelocity();

        m_player.Draw(m_window);
        m_map.Draw(m_window);

        m_window.display();
    }
}


