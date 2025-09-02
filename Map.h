#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Platform.h"

class Map {
public:
    enum class Season {
        Fall,
        Winter,
        Spring,
        Summer
    };
    Map(int index, Map::Season season_type);
    ~Map() = default;
    void Draw(sf::RenderWindow& window);
    Season season;
    void addWall(const Platform& wall);
    Platform& createWall(sf::Vector2f size, sf::Vector2f position);

    [[nodiscard]] Platform& getWall(int index);
    [[nodiscard]] std::vector<Platform> getWalls();
private:
    std::vector<Platform> m_walls;
};

void createWall(sf::Vector2f, sf::Vector2f, Map&);


