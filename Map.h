#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Map {
public:
    explicit Map(int index);
    ~Map() = default;
    void Draw(sf::RenderWindow& window);
private:
    std::vector<sf::RectangleShape> m_walls;

};