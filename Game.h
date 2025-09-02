#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "Player.h"
#include "Map.h"

class Game {
public:
    Game();
    ~Game() = default;

    void Run();

private:
    sf::RenderWindow m_window;
    Player m_player;
    int current_map_index;
    std::array<Map, 4> m_maps;
};
