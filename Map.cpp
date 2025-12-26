#include "Map.h"

constexpr float FLOOR_SIZE_Y_RATIO = 54.f;
constexpr float FLOOR_POSITION_Y_RATIO = 1.54f;


Map::Map(const Map::Season season_type, const sf::Vector2u window_size) : season(season_type), window_size(window_size){
    m_walls.emplace_back(std::make_unique<Platform>(sf::Vector2f({static_cast<float>(window_size.x * 10),static_cast<float>(window_size.y) / FLOOR_SIZE_Y_RATIO}), sf::Vector2f({0,static_cast<float>(window_size.y) / FLOOR_POSITION_Y_RATIO}))); //19200,20,0,700
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

