#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Map {
public:
    explicit Map(int index = 3);
    ~Map() = default;
    void Draw(sf::RenderWindow& window);

    void addWall(const sf::RectangleShape& wall);
    void createWall(sf::Vector2f size, sf::Vector2f position);

    [[nodiscard]] sf::RectangleShape& getWall(int index);
    [[nodiscard]] std::vector<sf::RectangleShape> getWalls();
private:
    std::vector<sf::RectangleShape> m_walls;
};

void createWall(sf::Vector2f, sf::Vector2f, Map&);
