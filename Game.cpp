#include "Game.h"
#include <iostream>
constexpr int FRAME_RATE_LIMIT = 60;
constexpr sf::Vector2f PLATFORM_SIZE = {200,20};
constexpr sf::Vector2f PLATFORM_POSITION = {100,600};
constexpr sf::Vector2f PLATFORM_GAP = {300,200};
constexpr std::array<sf::Color, 4> season_colors = {sf::Color({229,89,28}), sf::Color::Cyan, sf::Color::Green, sf::Color::Yellow};

Game::Game() : current_map_index(0),
m_maps{{Map(0, Map::Season::Fall),Map(1, Map::Season::Winter),Map(2, Map::Season::Spring),Map(3, Map::Season::Summer)}}
{
    // std::cout << m_maps.size() << std::endl;
    // for(int i = 0; i < static_cast<int>(m_maps.size()); i++) {
    //     std::cout << "constructing map" << std::endl;
    //     for (int j = 0; j < 10; j++) {
    //         m_maps[i].createWall(PLATFORM_SIZE, {PLATFORM_POSITION.x + PLATFORM_GAP.x * i, PLATFORM_POSITION.y - PLATFORM_GAP.y * i - (PLATFORM_GAP.y * 2 * j)});
    //     }
    // }
    for(auto& map : m_maps) {
        if(map.season == Map::Season::Winter) {
            auto platform1 = map.addWall(std::make_unique<VinePlatform>(PLATFORM_SIZE, (PLATFORM_POSITION + sf::Vector2f{800,-150})));
            platform1->m_shape.setFillColor(season_colors[static_cast<int>(map.season)]);
        }
        else {
            //auto& platform1 = map.createWall(PLATFORM_SIZE, (PLATFORM_POSITION + sf::Vector2f{800,-150}));
        }
        if(map.season != Map::Season::Winter) {
            auto& platform2 = map.createWall(PLATFORM_SIZE, (PLATFORM_POSITION + sf::Vector2f{100,-450}));
            auto& waterfall = map.createWall(PLATFORM_SIZE + sf::Vector2f{100,PLATFORM_SIZE.y * 50}, (PLATFORM_POSITION + sf::Vector2f{400,-900}));
            platform2.m_shape.setFillColor(season_colors[static_cast<int>(map.season)]);
            waterfall.m_shape.setFillColor(season_colors[static_cast<int>(map.season)]);
        }

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



        m_player.update(m_maps[current_map_index]);


        m_player.Draw(m_window);
        m_maps[current_map_index].Draw(m_window);

        m_window.setView(sf::View(sf::Rect<float>({0,m_player.getPosition().y - 700}, m_window.getView().getSize())));

        m_window.display();
    }
}


