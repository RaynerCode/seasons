#include "Player.h"
constexpr sf::Color GREEN(100,250,50);
constexpr int FRAME_RATE_LIMIT = 60;
constexpr sf::Vector2f PLAYER_SIZE({50,50});
constexpr float PLAYER_VELOCITY_X = 6.3f;
constexpr float PLAYER_VELOCITY_Y = 12.f;
constexpr float GRAVITY = 20.f;
constexpr float EPSILON = 0.01f;
constexpr int DASH_TIME = 10;
constexpr int DASH_MULTIPLIER = 5;



Player::Player() :
    m_shape(PLAYER_SIZE){
    m_shape.setFillColor(GREEN);
    m_shape.setPosition({500,500});
}

void Player::MoveByVelocity(Map& map) {
    this->move(m_velocity, map);
}

bool checkCollision(const sf::Rect<float>& rect, const sf::Rect<float>& other) {
    if(rect.findIntersection(other)) {
        return true;
    }
    return false;
}

std::optional<sf::Rect<float>> checkCollisionMap(const sf::Rect<float> rect, Map& map) {
    for(const Platform& platform : map.getWalls()) {
        const auto& platform_rect = platform.m_shape.getGlobalBounds();
        if(checkCollision(rect, platform_rect)) {
            if(platform.getType() == Platform::Type::Vine) {
                std::cout << "touching Vine" << std::endl;
            }
            return platform_rect;
        }
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
        distance.x = left_distance;
    else {
        distance.x = right_distance;
    }
    if(std::abs(bottom_distance) < std::abs(top_distance))
        distance.y = bottom_distance;
    else
        distance.y = top_distance;
    return distance;
}

sf::Rect<float> getPotentialRect(const sf::RectangleShape& shape, const sf::Vector2f& velocity) {
    const sf::Rect<float> rect = shape.getGlobalBounds();
    sf::Rect<float> potential_rect = rect;
    potential_rect.position += velocity;
    return potential_rect;
}

float sign(const float value) {
    std::cout <<"value : " << value << std::endl;
    if(value > 0)
        return 1.f;
    if(value < 0)
        return -1.f;
    return 0;
}

void Player::move(const sf::Vector2f velocity, Map& map) {
    //move gets a map because later there will be more than one map...
    //basically I am creating another rect that is in the position theoretically will be and collision checking it
    const sf::Rect<float> potential_rect = getPotentialRect(m_shape, velocity);
    if(const auto& problematic_rect = checkCollisionMap(potential_rect, map)) {
        //if it can't go velocity, calculate the distance left and go there
        auto dist = RectDistance(m_shape.getGlobalBounds(), *problematic_rect);
        if(dist.x == 0) {
            m_shape.move({0,velocity.y});
            return;
        }
        std::cout << "dist x: " << dist.x << "dist y: " << dist.y << std::endl;
        if(std::abs(dist.x) < std::abs(dist.y)) {
            //const float sign_dist = sign(dist.x);
            //std::cout << sign_dist << std::endl;
            m_shape.move({-1.f * dist.x, 0});
            m_shape.move({0,velocity.y});
        }
        else {
            m_velocity.y = 0;
            m_shape.move({0, -1.f * dist.y});
        }
        std::cout << "closing gap" << std::endl;
        return;
    }
    m_shape.move(velocity);
}

sf::Vector2f Player::getPosition() const {
    return m_shape.getPosition();
}


void Player::Draw(sf::RenderWindow &window) const {
    window.draw(m_shape);
}

bool inAir(const sf::RectangleShape& shape, Map& map) {
    if(checkCollisionMap(getPotentialRect(shape, {0,EPSILON}), map).has_value())
        return false;
    return true;
}

bool dash(int& count, const bool airborne) {
    if(count && airborne) {
        count--;
        return true;
    }
    return false;
}

void Player::update(Map& map) {
    m_velocity.x = 0;
    static int dash_count = 0; //currently can be bool (can_dash) but later might dash more than once
    static int dash_left_dir = 0; //amount of frames left for the dash
    if(dash_left_dir != 0) {
        m_velocity.y = 0;
        m_velocity.x = PLAYER_VELOCITY_X * sign(dash_left_dir) * DASH_MULTIPLIER;
        if(dash_left_dir > 0)
            dash_left_dir--;
        else
            dash_left_dir++;
        std::cout << dash_left_dir << std::endl;
        MoveByVelocity(map);
        return;
    }
    const bool airborne = inAir(m_shape, map);
    m_velocity.y += (1.f/FRAME_RATE_LIMIT) * GRAVITY;
    if(!airborne) {
        m_velocity.y = 0;
        dash_count = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        m_velocity.x -= PLAYER_VELOCITY_X;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            if(dash(dash_count, airborne)) {
                dash_left_dir = -1 * DASH_TIME;
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        m_velocity.x += PLAYER_VELOCITY_X;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            if(dash(dash_count, airborne)) {
                dash_left_dir = DASH_TIME;
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !airborne) {
        m_velocity.y = -PLAYER_VELOCITY_Y;
        std::cout << "jumping, should be once" << std::endl;
    }


    MoveByVelocity(map);

}

bool Player::isColliding(const sf::Rect<float> &other) const {
    //checking if the player is colliding with a bounding rectangle right now
    return checkCollision(m_shape.getGlobalBounds(), other);
}


