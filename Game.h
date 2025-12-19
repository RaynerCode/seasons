#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "Player.h"
#include "Map.h"
#include "Factory.h"

class Game {
public:
    Game();
    ~Game() = default;
    sf::Vector2u get_window_size() const;
    void Run();

private:
    sf::RenderWindow m_window;
    Player m_player;
    int current_map_index;
    std::array<Map, 4> m_maps;
};
