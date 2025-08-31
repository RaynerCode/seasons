#include "Player.h"
constexpr sf::Color GREEN(100,250,50);

constexpr sf::Vector2f PLAYER_SIZE({50,50});
constexpr float PLAYER_VELOCITY = 10.f;


Player::Player() :
    m_shape(PLAYER_SIZE){
    m_shape.setFillColor(GREEN);
    m_shape.setPosition({500,500});
}

void Player::MoveByVelocity() {
    m_shape.move(m_velocity);
}

bool checkCollision(const Player& player, Map& map) {
    if(player.isColliding(map.getWall(0)))
        return false;
    return true;
}

void Player::move(const sf::Vector2f velocity, Map& map) {
    if(checkCollision(*this, map))
        return
    m_shape.move(velocity);
}


void Player::Draw(sf::RenderWindow &window) const {
    window.draw(m_shape);
}

void Player::update(Map& map) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        this->move({-PLAYER_VELOCITY,0}, map);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        this->move({PLAYER_VELOCITY,0}, map);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        this->move({0, -PLAYER_VELOCITY}, map);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        this->move({0,PLAYER_VELOCITY}, map);

    }
}

bool Player::isColliding(const sf::Shape &other) const {
    const sf::FloatRect boundingBoxPlayer = this->m_shape.getGlobalBounds();
    sf::FloatRect boundingBoxOther = other.getGlobalBounds();
    if(boundingBoxPlayer.findIntersection(boundingBoxOther)) {
        return true;
    }
    return false;
}


