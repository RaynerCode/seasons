#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Platform.h"

class Map {
public:
    explicit Map(int index = 3);
    ~Map() = default;
    void Draw(sf::RenderWindow& window);

    void addWall(const Platform& wall);
    void createWall(sf::Vector2f size, sf::Vector2f position);

    [[nodiscard]] Platform& getWall(int index);
    [[nodiscard]] std::vector<Platform> getWalls();
private:
    std::vector<Platform> m_walls;
};

void createWall(sf::Vector2f, sf::Vector2f, Map&);


