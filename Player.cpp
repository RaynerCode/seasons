#include "Player.h"
constexpr sf::Color GREEN(100,250,50);
constexpr int FRAME_RATE_LIMIT = 60;
constexpr sf::Vector2f PLAYER_WINDOW_SIZE_RATIO({38.4,21.6}); //50,50
sf::Vector2f PLAYER_SIZE;
constexpr sf::Vector2f PLAYER_INITIAL_POSITION_WINDOW_RATIO({19.2,1.8}); //100,600
sf::Vector2f PLAYER_INITIAL_POSITION;
constexpr float PLAYER_VELOCITY_X_WINDOW_RATIO = 192.f; //10
float PLAYER_VELOCITY_X;
constexpr float PLAYER_VELOCITY_Y_WINDOW_RATIO = 90.f; //12
float PLAYER_VELOCITY_Y;
constexpr float GRAVITY_WINDOW_RATIO = 54.f;
float GRAVITY;
constexpr float EPSILON = 0.01f;
constexpr int DASH_TIME = 10;
constexpr int DASH_MULTIPLIER = 5;



Player::Player(const sf::Vector2u window_size) : m_shape({static_cast<float>(window_size.y) / PLAYER_WINDOW_SIZE_RATIO.y, static_cast<float>(window_size.y) / PLAYER_WINDOW_SIZE_RATIO.y}),m_touching(Platform::Type::Stone){
    static int time_initialized = 0;
    time_initialized++;
    if(time_initialized >= 2) {
        std::cout << "player initialized more than once" << std::endl;
    }
    PLAYER_SIZE = {static_cast<float>(window_size.y) / PLAYER_WINDOW_SIZE_RATIO.y, static_cast<float>(window_size.y) / PLAYER_WINDOW_SIZE_RATIO.y};
    //currently player is a square with ratio compatible to window_size.y
    std::cout << "player size x: " << PLAYER_SIZE.x << "player size y: " << PLAYER_SIZE.y << std::endl;
    m_shape.setFillColor(GREEN);
    PLAYER_INITIAL_POSITION = {static_cast<float>(window_size.x) / PLAYER_INITIAL_POSITION_WINDOW_RATIO.x, static_cast<float>(window_size.y) / PLAYER_INITIAL_POSITION_WINDOW_RATIO.y};
    m_shape.setPosition(PLAYER_INITIAL_POSITION);
    PLAYER_VELOCITY_X = static_cast<float>(window_size.x) / PLAYER_VELOCITY_X_WINDOW_RATIO;
    PLAYER_VELOCITY_Y = static_cast<float>(window_size.y) / PLAYER_VELOCITY_Y_WINDOW_RATIO;
    std::cout << "player velocity x: " << PLAYER_VELOCITY_X << "player velocity y: " << PLAYER_VELOCITY_Y << std::endl;
    GRAVITY = static_cast<float>(window_size.y) / GRAVITY_WINDOW_RATIO;
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


std::optional<const Platform*> checkCollisionMap(const sf::Rect<float> rect, Map& map) {
    for(const std::unique_ptr<Platform>& platform : map.getWalls()) {
        const auto& platform_rect = platform->m_shape.getGlobalBounds();
        if(checkCollision(rect, platform_rect)) {
            return platform.get();
        }
    }
    return std::nullopt;
}

sf::Vector2f RectDistance(const sf::Rect<float> rect1, const sf::Rect<float> rect2) {
    sf::Vector2f distance; //right_distance meaning the player is to the right of the object etc.
    const float right_distance = rect1.position.x - (rect2.position.x + rect2.size.x); //positive
    const float left_distance = rect1.position.x + rect1.size.x - rect2.position.x; //negative
    const float bottom_distance = rect1.position.y - (rect2.position.y + rect2.size.y); //positive
    const float top_distance = rect1.position.y + rect1.size.y - rect2.position.y;//negative
    if(std::abs(left_distance) < std::abs(right_distance))
        distance.x = left_distance;
    else {
        distance.x = right_distance;
    }
    if(std::abs(bottom_distance) < std::abs(top_distance)) {
        distance.y = bottom_distance;
        if(bottom_distance < 0) {
            std::cout << "inside object" << std::endl;
            distance.y *= -1;
        }
    }
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
    if(value > 0)
        return 1.f;
    if(value < 0)
        return -1.f;
    return 0;
}

void Player::closeGap(const sf::Vector2f& dist,const sf::Vector2f& velocity) {
    if(dist.x == 0) {
        m_shape.move({0,velocity.y});
        return;
    }
    if(std::abs(dist.x) < std::abs(dist.y)) { //should still be in air but now touching problematic rect
        m_shape.move({-1.f * dist.x, 0});
        m_shape.move({0,velocity.y});
    }
    else { //grounding the player (or making him hit the celling)
        m_velocity.y = 0;
        m_shape.move({0, -1.f * dist.y});
    }
}

void markPlatformCollision(const Platform* platform, Player& player) {
    if(platform->getType() == Platform::Type::Stone) { //restore normal behaviour
        //std::cout << "touching Stone" << std::endl;
        player.m_touching = Platform::Type::Stone;
    }
    if(platform->getType() == Platform::Type::Vine) {
        //std::cout << "touching Vine" << std::endl;
        player.m_touching = Platform::Type::Vine;
    }
    if(platform->getType() == Platform::Type::Thorn) {
        //std::cout << "touching Thorn" << std::endl;
        player.m_touching = Platform::Type::Thorn;
    }
    if(platform->getType() == Platform::Type::Ice) {
        //std::cout << "touching Ice" << std::endl;
        player.m_touching = Platform::Type::Ice;
    }
    if(platform->getType() == Platform::Type::Leaf) {
        //std::cout << "touching Leaf!" << std::endl;
        player.m_touching = Platform::Type::Leaf;
    }
}


void Player::move(const sf::Vector2f velocity, Map& map) { //basically I am creating another rect that is in the position theoretically will be and collision checking it
    const sf::Rect<float> potential_rect = getPotentialRect(m_shape, velocity);
    if(const auto& problematic_platform = checkCollisionMap(potential_rect, map)) {
        std::cout << "size y" << problematic_platform.value()->m_shape.getSize().y << std::endl;
        markPlatformCollision(*problematic_platform, *this);
        const auto& problematic_rect = (*problematic_platform)->m_shape.getGlobalBounds();
        const auto dist = RectDistance(m_shape.getGlobalBounds(), problematic_rect);
        std::cout << "dist y" << dist.y << std::endl;
        closeGap(dist, velocity);
        return;
    }
    m_shape.move(velocity); //everything is ok, we can move velocity with no collision
}

sf::Vector2f Player::getPosition() const {
    return m_shape.getPosition();
}


void Player::Draw(sf::RenderWindow &window) const {
    window.draw(m_shape);
}

bool inAir(const sf::RectangleShape& shape, Map& map, Player& player) {
    if(const auto& problematic_platform = checkCollisionMap(getPotentialRect(shape, {0,EPSILON}), map)) {
        markPlatformCollision(*problematic_platform, player);
        return false;
    }
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
    move(sf::Vector2f({0,0}), map); //making sure player isn't in a foul spot
    if(m_shape.getPosition().y > 1000) {
        m_shape.setPosition(PLAYER_INITIAL_POSITION);
    }
    m_velocity.x = 0;
    static int jump_count = 0;
    static int dash_jump_count = 0;
    static int dash_count = 0; //currently can be bool (can_dash) but later might dash more than once
    static int dash_left_dir = 0; //amount of frames left for the dash
    if(dash_left_dir != 0) {
        dash_jump_count = 1;
        m_velocity.y = 0;
        m_velocity.x = PLAYER_VELOCITY_X * sign(dash_left_dir) * DASH_MULTIPLIER;
        if(dash_left_dir > 0) //basically instead of another variable called dash_dir and dash_time i have just this going to zero from both ends
            dash_left_dir--;
        else
            dash_left_dir++;
        MoveByVelocity(map);
        return;
    }
    const bool airborne = inAir(m_shape, map, *this);
    m_velocity.y += (1.f/FRAME_RATE_LIMIT) * GRAVITY;
    if(!airborne) {
        m_velocity.y = 0;
        dash_count = 1;
        jump_count = 1;
    }
    else {
        jump_count = 0; //making it impossible to jump after falling from platform
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && (jump_count > 0)){// || dash_jump_count > 0)) { //uncomment to enable jump after dash
        jump_count--;
        dash_jump_count--;
        m_velocity.y = -PLAYER_VELOCITY_Y;
    }

    //giving effects based on platform type if standing on it

    if(!airborne && m_touching == Platform::Type::Leaf) {
        constexpr float leaf_multiplier = 0.5f;
        m_velocity.x *= leaf_multiplier;
    }
    if(m_touching == Platform::Type::Thorn) { //currently i am just teleporting back to beginning
        m_touching = Platform::Type::Stone;
        m_shape.setPosition(PLAYER_INITIAL_POSITION);
        //m_velocity.y = 0;
        return;
    }

    MoveByVelocity(map);

}

bool Player::isColliding(const sf::Rect<float> &other) const {
    //checking if the player is colliding with a bounding rectangle right now
    return checkCollision(m_shape.getGlobalBounds(), other);
}


