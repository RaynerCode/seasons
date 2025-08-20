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
    Map m_map;
};
