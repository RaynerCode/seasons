#include "Player.h"
constexpr sf::Color GREEN(100,250,50);
constexpr int FRAME_RATE_LIMIT = 60;
constexpr sf::Vector2f PLAYER_SIZE({50,50});
constexpr float PLAYER_VELOCITY_X = 6.f;
constexpr float PLAYER_VELOCITY_Y = 200.f;
constexpr float GRAVITY = 9.81f;
constexpr float EPSILON = 0.01f;



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

sf::Rect<float> getPotentialRect(const sf::RectangleShape& shape, const sf::Vector2f& velocity) {
    const sf::Rect<float> rect = shape.getGlobalBounds();
    sf::Rect<float> potential_rect = rect;
    potential_rect.position += velocity;
    return potential_rect;
}


void Player::move(const sf::Vector2f velocity, Map& map) {
    //move gets a map because later there will be more than one map...
    //basically I am creating another rect that is in the position theoretically will be and collision checking it
    const sf::Rect<float> potential_rect = getPotentialRect(m_shape, velocity);
    if(const auto& problematic_rect = checkCollisionMap(potential_rect, map)) {
        //if it can't go velocity, calculate the distance left and go there
        auto dist = RectDistance(m_shape.getGlobalBounds(), *problematic_rect);
        if(velocity.x > 0) {
            move({dist.x,0}, map);
        }
        if(velocity.x < 0) {
            move({-dist.x,0}, map);
        }
        if(velocity.y > 0) {
            move({0,dist.y}, map);
        }
        if(velocity.y < 0) {
            move({0,-dist.y}, map);
        }
        return;
    }
    m_shape.move(velocity);
}


void Player::Draw(sf::RenderWindow &window) const {
    window.draw(m_shape);
}

bool inAir(const sf::RectangleShape& shape, Map& map) {
    if(checkCollisionMap(getPotentialRect(shape, {0,EPSILON}), map).has_value())
        return false;
    return true;
}

void jump(Player& player, Map& map) {
    int iterations = PLAYER_VELOCITY_Y / 5;
    for(int i = 0; i < iterations; i++) {
        player.move({0, -5}, map);
    }
}

void Player::update(Map& map) {
    static float gravity_velocity = 0;
    const bool airborne = inAir(m_shape, map);
    gravity_velocity += (1.f/FRAME_RATE_LIMIT) * GRAVITY;
    if(!airborne) {
        gravity_velocity = 0;
    }
    else
        this->move(sf::Vector2f({0,gravity_velocity}),map);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        this->move({-PLAYER_VELOCITY_X,0}, map);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        this->move({PLAYER_VELOCITY_X,0}, map);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !airborne) {
        jump(*this, map);
    }
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
    //     this->move({0,PLAYER_VELOCITY}, map);
    // } at the moment no usage for s key
}

bool Player::isColliding(const sf::Rect<float> &other) const {
    //checking if the player is colliding with a bounding rectangle right now
    return checkCollision(m_shape.getGlobalBounds(), other);
}


