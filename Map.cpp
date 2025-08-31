#include "Map.h"
constexpr sf::Color RED(250,100,50);
constexpr sf::Vector2f WALL_SIZE({20,20});
constexpr sf::Vector2f OFFSET({500,100});

Map::Map(const int index) {
    for(int i = 0;i < index; i++) {
        m_walls.emplace_back(WALL_SIZE);
        m_walls[i].setFillColor(RED);
        m_walls[i].move(OFFSET * static_cast<float>(i+1));}
    m_walls.emplace_back(sf::Vector2f({2000,20}));
    m_walls[index].move(sf::Vector2f({0,700}));
    sf::RectangleShape platform1({200,20});
    platform1.setPosition({600,600});
    addWall(platform1);
    createWall({200,20},{600,600},*this);
    createWall({200,20},{200,470},*this);
}

void createWall(const sf::Vector2f size, const sf::Vector2f position, Map& map) {
    sf::RectangleShape wall(size);
    wall.setPosition(position);
    map.addWall(wall);
}

void Map::Draw(sf::RenderWindow &window) {
    for (const sf::RectangleShape& wall : m_walls) {
        window.draw(wall);
    }
}

void Map::addWall(const sf::RectangleShape& wall) {
    m_walls.emplace_back(wall);
}


sf::RectangleShape& Map::getWall(const int index) {
    if(index >= static_cast<int>(m_walls.size()))
        throw std::out_of_range("invalid wall of map, out of range");
    return m_walls[index];
}

std::vector<sf::RectangleShape> Map::getWalls() {
    return m_walls;
}

