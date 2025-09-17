#pragma once
#include "Map.h"
#include <SFML/Graphics.hpp>

constexpr sf::Vector2f PLATFORM_SIZE = {200,20};
constexpr sf::Vector2f PLATFORM_POSITION = {100,700};
constexpr std::array<sf::Color, 4> season_colors = {sf::Color({255,165,0}), sf::Color::Cyan, sf::Color::Green, sf::Color::Yellow};


class Factory {
public:
    static void createMap(Map& map, Map::Season season);
};