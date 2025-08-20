#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    ~Player() = default;

private:
    sf::RectangleShape m_shape;
    sf::Vector2<double> m_velocity;
    sf::Vector2<double> m_position;
};