#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Map {
public:
    explicit Map(int index);
    ~Map() = default;
    void Draw(sf::RenderWindow& window);

    [[nodiscard]] sf::RectangleShape& getWall(int index);
private:
    std::vector<sf::RectangleShape> m_walls;

};