#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

void handleEvent(sf::RenderWindow& window, sf::RectangleShape& shape) {
    static int counter = 0;
    // check all the window's events that were triggered since the last iteration of the loop
    while (const std::optional event = window.pollEvent())
    {
        // "close requested" event: we close the window
        if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
            window.close();
        if (event->is<sf::Event::MouseButtonPressed>()) {
            window.setTitle(std::to_string((++counter)));
            shape.move({50.f,5.f});
            window.draw(shape);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            window.setTitle(std::to_string((++counter)));
            shape.move({-1.f,0});
            window.draw(shape);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            window.setTitle(std::to_string((++counter)));
            shape.move({1.f,0});
            window.draw(shape);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            window.setTitle(std::to_string((++counter)));
            shape.move({0,-1.f});
            window.draw(shape);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            window.setTitle(std::to_string((++counter)));
            shape.move({0,1.f});
            window.draw(shape);
        }
    }
}

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

// int main()
// {
//     // create the window
//     sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "My window", sf::Style::None);
//     window.setFramerateLimit(60);
//     std::cout << "x: " << window.getPosition().x << "y: " << window.getPosition().y << std::endl;
//     // run the program as long as the window is open
//     sf::RectangleShape shape({50,50});
//     std::cout << "x: " << shape.getPosition().x << "y: " << shape.getPosition().y << std::endl;
//
//     // set the shape color to green
//     shape.setFillColor(sf::Color(100, 250, 50));
//     sf::Vector2<float> velocity = {2,2};
//
//     while (window.isOpen())
//     {
//         handleEvent(window, shape);
//
//         // clear the window with black color
//         window.clear(sf::Color::Black);
//
//         velocity = handleCollision(shape,window, velocity);
//         shape.move(velocity);
//
//         window.draw(shape);
//
//         // end the current frame
//         window.display();
//     }
//     std::cout << "x: " << shape.getPosition().x << "y: " << shape.getPosition().y << std::endl;
//
// }

int main() {
    Game game1;
    game1.Run();
}