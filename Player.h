#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    ~Player() = default;

    void MoveByVelocity();

    void Draw(sf::RenderWindow& window) const;

private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_velocity;
    sf::Vector2f m_position;
};