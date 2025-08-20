#include "Game.h"
#include <iostream>
constexpr int FRAME_RATE_LIMIT = 60;

Game::Game() :m_map(3){
    std::cout << "Game constructed" << std::endl;
}

void handleEvent(sf::RenderWindow& window, Player& player) {
    static int counter = 0;
    // check all the window's events that were triggered since the last iteration of the loop
    while (const std::optional event = window.pollEvent())
    {
        // "close requested" event: we close the window
        if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
            window.close();
        if (event->is<sf::Event::MouseButtonPressed>()) {
            window.setTitle(std::to_string((++counter)));
            player.move({50.f,5.f});
            player.Draw(window);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            window.setTitle(std::to_string((++counter)));
            player.move({-1.f,0});
            player.Draw(window);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            window.setTitle(std::to_string((++counter)));
            player.move({1.f,0});
            player.Draw(window);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            window.setTitle(std::to_string((++counter)));
            player.move({0,-1.f});
            player.Draw(window);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            window.setTitle(std::to_string((++counter)));
            player.move({0,1.f});
            player.Draw(window);
        }
    }
}

void Game::Run() {
    sf::RenderWindow m_window(sf::VideoMode::getFullscreenModes()[0], "My Game Window", sf::Style::None);
    m_window.setFramerateLimit(FRAME_RATE_LIMIT);

    while(m_window.isOpen()){

        handleEvent(m_window, m_player);
        m_window.clear(sf::Color::Black);

        m_player.MoveByVelocity();

        m_player.Draw(m_window);
        m_map.Draw(m_window);

        m_window.display();
    }
}


