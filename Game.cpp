#include "Game.h"
#include <iostream>
constexpr int FRAME_RATE_LIMIT = 60;
constexpr int CAMERA_OFFSET_Y = 700;
Game::Game() : current_map_index(0),
m_maps({Map(Map::Season::Fall),Map(Map::Season::Winter),Map(Map::Season::Spring),Map(Map::Season::Summer)}) {
    for(auto& map: m_maps) {
        Factory::createMap(map, map.season);
    }
    std::cout << "Game constructed" << std::endl;
}

int handleEvent(sf::RenderWindow& window) {
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
    sf::RenderWindow m_window(sf::VideoMode::getFullscreenModes()[0], "My Game Window", sf::Style::None);
    m_window.setFramerateLimit(FRAME_RATE_LIMIT);
    while(m_window.isOpen()){

        if((new_map_index = handleEvent(m_window)) >= 0) {
            if(new_map_index != current_map_index) {
                current_map_index = new_map_index;
            }
        }
        m_window.clear(sf::Color::Black);

        m_maps[current_map_index].Draw(m_window);


        m_player.update(m_maps[current_map_index]);


        m_player.Draw(m_window);

        static float current_camera_x = 0;
        float window_center_x = m_window.getView().getCenter().x;
        float player_x = m_player.getPosition().x;
        if(std::abs(window_center_x - player_x) > m_window.getSize().x / 2 - 10) {
            if(player_x > window_center_x) {
                current_camera_x = m_player.getPosition().x - 10;
                //m_window.setView(sf::View(sf::Rect<float>({m_player.getPosition().x - 10,m_player.getPosition().y - CAMERA_OFFSET_Y}, m_window.getView().getSize())));
            }
            else {
                // m_window.setView(sf::View(sf::Rect<float>({m_player.getPosition().x - m_window.getSize().x + 10,m_player.getPosition().y - CAMERA_OFFSET_Y}, m_window.getView().getSize())));
                // std::cout << "moving window left" << std::endl;
                current_camera_x = m_player.getPosition().x - m_window.getSize().x + 10;
            }
        }
        m_window.setView(sf::View(sf::Rect<float>({current_camera_x,m_player.getPosition().y - CAMERA_OFFSET_Y}, m_window.getView().getSize())));


        m_window.display();
    }
}


