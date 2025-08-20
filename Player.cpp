#include "Player.h"
constexpr sf::Color GREEN(100,250,50);

constexpr sf::Vector2f PLAYER_SIZE({50,50});
constexpr float PLAYER_VELOCITY = 10.f;


Player::Player() :
    m_shape(PLAYER_SIZE) ,m_position(0,0) {
    m_shape.setFillColor(GREEN);
}

void Player::MoveByVelocity() {
    m_shape.move(m_velocity);
    m_position += m_velocity;
}

void Player::move(const sf::Vector2f velocity) {
    m_shape.move(velocity);
    m_position += velocity;
}


void Player::Draw(sf::RenderWindow &window) const {
    window.draw(m_shape);
}

void Player::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        this->move({-PLAYER_VELOCITY,0});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        this->move({PLAYER_VELOCITY,0});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        this->move({0, -PLAYER_VELOCITY});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        this->move({0,PLAYER_VELOCITY});

    }
}


