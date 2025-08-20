#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>



sf::Vector2<float> handleCollision(sf::RectangleShape& shape, sf::RenderWindow& window ,sf::Vector2<float> velocity) {
    sf::Vector2<float> newVelocity = velocity;
    float shape_x = shape.getPosition().x;
    float shape_y = shape.getPosition().y;
    int window_x = window.getSize().x;
    int window_y = window.getSize().y;
    float shape_width = shape.getSize().x;
    float shape_height = shape.getSize().y;
    std::cout << "dimensions: shape x: " << shape_x << "shape y: " << shape_y << "window x: " << window_x << "window y: " << window_y << "shape widht: " << shape_width << "shape height: " << shape_height << std::endl;
    if(shape_x < 0 || (shape_x + shape_width) >= window_x) {
        newVelocity.x *= -1;
    }
    if(shape_y < 0 || (shape_y + shape_height) >= window_y) {
        newVelocity.y *= -1;
    }
    std::cout << "velocity x: " << newVelocity.x << "velocity y: " << newVelocity.y << std::endl;
    return newVelocity;
}



int main() {
    Game game1;
    game1.Run();
}