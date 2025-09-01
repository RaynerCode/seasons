#include "Map.h"
constexpr sf::Color RED(250,100,50);
constexpr sf::Vector2f WALL_SIZE({20,20});
constexpr sf::Vector2f OFFSET({500,100});

Platform::Platform(const sf::Vector2f& size) : m_shape(size){}


Map::Map(const int index) {
    for(int i = 0;i < index; i++) {
        m_walls.emplace_back(WALL_SIZE);
        m_walls[i].m_shape.setFillColor(RED);
        m_walls[i].m_shape.move(OFFSET * static_cast<float>(i+1));}
    m_walls.emplace_back(sf::Vector2f({2000,20}));
    m_walls[index].m_shape.move(sf::Vector2f({0,700}));
}

void Map::createWall(const sf::Vector2f size, const sf::Vector2f position) {
    Platform wall(size);
    wall.m_shape.move(position);
    addWall(wall);
}

void Map::Draw(sf::RenderWindow &window) {
    for (const Platform& wall : m_walls) {
        window.draw(wall.m_shape);
    }
}

void Map::addWall(const Platform& wall) {
    m_walls.emplace_back(wall);
}


Platform& Map::getWall(const int index) {
    if(index >= static_cast<int>(m_walls.size()))
        throw std::out_of_range("invalid wall of map, out of range");
    return m_walls[index];
}

std::vector<Platform> Map::getWalls() {
    return m_walls;
}

