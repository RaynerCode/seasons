#include "Map.h"
constexpr sf::Color RED(250,100,50);
constexpr sf::Vector2f WALL_SIZE({20,20});
constexpr sf::Vector2f OFFSET({500,100});


Map::Map(const int index, const Map::Season season_type) : season(season_type){
    for(int i = 0;i < index; i++) {
        m_walls.emplace_back(std::make_unique<Platform>(WALL_SIZE, OFFSET * static_cast<float>(i+1)));
        m_walls[i]->m_shape.setFillColor(RED);
    }
    m_walls.emplace_back(std::make_unique<Platform>(sf::Vector2f({2000,20}), sf::Vector2f({0,700})));
}

Platform& Map::createWall(const sf::Vector2f size, const sf::Vector2f position) {
    const auto& wall = m_walls.emplace_back(std::make_unique<Platform>(size, position));
    return *wall;
}

void Map::Draw(sf::RenderWindow &window) {
    for (const std::unique_ptr<Platform>& wall : m_walls) {
        window.draw(wall->m_shape);
    }
}



Platform& Map::getWall(const int index) const {
    if(index >= static_cast<int>(m_walls.size()))
        throw std::out_of_range("invalid wall of map, out of range");
    return *m_walls[index];
}

Platform* Map::addWall(std::unique_ptr<Platform> wall) {
    m_walls.push_back(std::move(wall));
    return m_walls.back().get(); // return raw pointer to last element
}


std::vector<std::unique_ptr<Platform>>& Map::getWalls() {
    return m_walls;
}

