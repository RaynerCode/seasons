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
    const float right_distance = rect1.position.x - (rect2.position.x + rect2.size.x); //positive
    const float left_distance = rect1.position.x + rect1.size.x - rect2.position.x; //negative
    const float bottom_distance = rect1.position.y - (rect2.position.y + rect2.size.y); //positive
    const float top_distance = rect1.position.y + rect1.size.y - rect2.position.y;//negative
    if(std::abs(left_distance) < std::abs(right_distance))
        distance.x = -left_distance;
    else {
        distance.x = right_distance;
    }
    if(std::abs(bottom_distance) < std::abs(top_distance))
        distance.y = bottom_distance;
    else
        distance.y = -top_distance;
    return distance;
}

void Player::move(const sf::Vector2f velocity, Map& map) {
    //move gets a map because later there will be more than one map...
    //basically I am creating another rect that is in the position theoretically will be and collision checking it
    const sf::Rect<float> rect = m_shape.getGlobalBounds();
    sf::Rect<float> potential_rect = rect;
    potential_rect.position += velocity;
    if(const auto& problematic_rect = checkCollisionMap(potential_rect, map)) {
        auto dist = RectDistance(rect, *problematic_rect);
        std::cout << "dist x: " << dist.x << "dist y: " << dist.y << std::endl;
        if(velocity.x > 0) {
            move({dist.x,0}, map);
        }
        else if(velocity.x < 0) {
            move({-dist.x,0}, map);
        }
        else if(velocity.y > 0) {
            move({0,dist.y}, map);
        }
        else if(velocity.y < 0) {
            move({0,-dist.y}, map);
        }
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


