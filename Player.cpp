#include "Player.h"
constexpr sf::Color GREEN(100,250,50);

constexpr sf::Vector2f PLAYER_SIZE({50,50});
constexpr float PLAYER_VELOCITY = 6.f;


Player::Player() :
    m_shape(PLAYER_SIZE){
    m_shape.setFillColor(GREEN);
    m_shape.setPosition({500,500});
}

void Player::MoveByVelocity() {
    m_shape.move(m_velocity);
}

bool checkCollision(const sf::Rect<float>& rect, const sf::Rect<float>& other) {
    if(rect.findIntersection(other)) {
        return true;
    }
    return false;
}

std::optional<sf::Rect<float>> checkCollisionMap(const sf::Rect<float> rect, Map& map) {
    for(const sf::RectangleShape& object : map.getWalls()) {
        const auto& other = object.getGlobalBounds();
        if(checkCollision(rect, other))
            return object.getGlobalBounds();
    }
    return std::nullopt;
}

sf::Vector2f RectDistance(const sf::Rect<float> rect1, const sf::Rect<float> rect2) {
    sf::Vector2f distance;
    float left_distance = std::abs(rect1.position.x - rect2.position.x + rect2.size.x);
    float right_distance = std::abs(rect1.position.x + rect1.size.x - rect2.position.x);
    float top_distance = std::abs(rect1.position.y - rect2.position.y + rect2.size.y);
    float bottom_distance = std::abs(rect1.position.y + rect1.size.x - rect2.position.y);
    distance.x = std::min(left_distance , right_distance);
    distance.y = std::min(top_distance, bottom_distance);
    return distance;
}

void Player::move(const sf::Vector2f velocity, Map& map) {
    //move gets a map because later there will be more than one map...
    //basically I am creating another rect that is in the position theoretically will be and collision checking it
    const sf::Rect<float> rect = m_shape.getGlobalBounds();
    sf::Rect<float> potential_rect = rect;
    potential_rect.position += velocity;
    if(const auto& problematic_rect = checkCollisionMap(potential_rect, map)) {
        move(RectDistance(rect, *problematic_rect), map);
        return;
    }
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

bool Player::isColliding(const sf::Rect<float> &other) const {
    //checking if the player is colliding with a bounding rectangle right now
    return checkCollision(m_shape.getGlobalBounds(), other);
}


