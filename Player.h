#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class Player {
public:
    Player();
    ~Player() = default;

    void MoveByVelocity();

    void move(sf::Vector2f, Map& map);

    void update(Map& map);

    void Draw(sf::RenderWindow& window) const;

    bool isColliding(const sf::Shape& other) const;

private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_velocity;
};