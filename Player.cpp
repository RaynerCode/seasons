#include "Player.h"

#define PLAYER_SIZE_X 50
#define PLAYER_SIZE_Y 50
#define PLAYER_DEFAULT_VELOCITY_X 2
#define PLAYER_DEFAULT_VELOCITY_Y 2

Player::Player() {
    sf::RectangleShape m_shape({PLAYER_SIZE_X,PLAYER_SIZE_Y});
    sf::Vector2<double> m_velocity(PLAYER_DEFAULT_VELOCITY_X,PLAYER_DEFAULT_VELOCITY_Y);
    sf::Vector2<double> m_position(0,0);
}
