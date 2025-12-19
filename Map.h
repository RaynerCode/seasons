#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Platform.h"



class Map {
public:
    enum class Season {
        Fall,
        Winter,
        Spring,
        Summer
    };
    Season season;

    sf::Vector2u window_size;
    explicit Map(Map::Season season_type, sf::Vector2u window_size);
    ~Map() = default;
    void Draw(sf::RenderWindow& window);
    Platform* addWall(std::unique_ptr<Platform> wall);
    Platform& createWall(sf::Vector2f size, sf::Vector2f position);

    [[nodiscard]] Platform& getWall(int index) const;
    [[nodiscard]] std::vector<std::unique_ptr<Platform>>& getWalls();
private:
    std::vector<std::unique_ptr<Platform>> m_walls;
};

void createWall(sf::Vector2f, sf::Vector2f, Map&);


