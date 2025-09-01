#include "Game.h"
#include <iostream>
constexpr int FRAME_RATE_LIMIT = 60;

Game::Game() : m_maps() , current_map_index(0){
    for (int i = 0; i < 5; i++) {
        m_maps[current_map_index].createWall({200, 20}, {600, 600.f - static_cast<float>(300 * i)});
        m_maps[current_map_index].createWall({200, 20}, {200, 470 - static_cast<float>(300 * i)});
    }
    std::cout << "Game constructed" << std::endl;
}

int handleEvent(sf::RenderWindow& window, Player& player) {
    // check all the window's events that were triggered since the last iteration of the loop
    while (const std::optional event = window.pollEvent())
    {
        // "close requested" event: we close the window
        if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
            window.close();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            return 0;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            return 1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            return 2;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            return 3;
        }
    }
    return -1;
}

void Game::Run() {
    static int new_map_index;
    sf::RenderWindow m_window(sf::VideoMode::getFullscreenModes()[3], "My Game Window", sf::Style::Default);
    m_window.setFramerateLimit(FRAME_RATE_LIMIT);
    while(m_window.isOpen()){

        if((new_map_index = handleEvent(m_window, m_player)) >= 0) {
            if(new_map_index != current_map_index) {
                current_map_index = new_map_index;
            }
        }
        m_window.clear(sf::Color::Black);



        m_player.update(m_maps[current_map_index]);


        m_player.Draw(m_window);
        m_maps[current_map_index].Draw(m_window);

        m_window.setView(sf::View(sf::Rect<float>({0,m_player.getPosition().y - 700}, m_window.getView().getSize())));

        m_window.display();
    }
}


