#include "Player.h"
constexpr sf::Color GREEN(100,250,50);

constexpr sf::Vector2f PLAYER_SIZE({50,50});
constexpr sf::Vector2f PLAYER_VELOCITY({2,2});


Player::Player() :
    m_shape(PLAYER_SIZE), m_velocity(PLAYER_VELOCITY),m_position(0,0) {
    m_shape.setFillColor(GREEN);
}

void Player::MoveByVelocity() {
    m_shape.move(m_velocity);
    m_position += m_velocity;
}

void Player::Draw(sf::RenderWindow &window) const {
    window.draw(m_shape);
}


