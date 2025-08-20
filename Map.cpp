#include "Map.h"
constexpr sf::Color RED(250,100,50);
constexpr sf::Vector2f WALL_SIZE({20,20});
constexpr sf::Vector2f OFFSET({500,0});

Map::Map(const int index) {
    for(int i = 0;i < index; i++) {
        m_walls.emplace_back(WALL_SIZE);
        m_walls[i].setFillColor(RED);
        m_walls[i].move(OFFSET * static_cast<float>(i));
    }
}

void Map::Draw(sf::RenderWindow &window) {
    for (const sf::RectangleShape& wall : m_walls) {
        window.draw(wall);
    }
}

