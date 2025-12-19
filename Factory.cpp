#include "Factory.h"
constexpr sf::Color GRAY = sf::Color({109, 106, 100});
constexpr int LEVEL_HEIGHT = 200;


void createDefaultMap(Map& map) {
    //addStoneWallInGray(sf::Vector2f{300, 1000}, (PLATFORM_POSITION + sf::Vector2f{400, -1000}), map);
    addStoneWallInGray(PLATFORM_SIZE, (PLATFORM_POSITION + sf::Vector2f{100, -2 * LEVEL_HEIGHT}), map);
    addStoneWallInGray(PLATFORM_SIZE, (PLATFORM_POSITION + sf::Vector2f{800, -2 * LEVEL_HEIGHT}), map);
}

void addStoneWallInColor(const sf::Vector2f& size,const sf::Vector2f& position, Map& map) {
    const auto platform1 = map.addWall(std::make_unique<Platform>(size,position));
    platform1->m_shape.setFillColor(season_colors[static_cast<int>(map.season)]);
}

void addStoneWallInGray(const sf::Vector2f& size,const sf::Vector2f& position, Map& map) {
    const auto platform1 = map.addWall(std::make_unique<Platform>(size,position));
    platform1->m_shape.setFillColor(GRAY);
    std::cout << "created gray" << std::endl;
}


void Factory::createMap(Map& map, const Map::Season season) {

    switch(season){
        case Map::Season::Fall: {
            createDefaultMap(map);
            const auto platform1 = map.addWall(std::make_unique<LeafPlatform>(PLATFORM_SIZE,PLATFORM_POSITION - sf::Vector2f{100,200}));
            platform1->m_shape.setFillColor(season_colors[static_cast<int>(map.season)]);
            break;
        }
        case Map::Season::Winter: {
            createDefaultMap(map);
            break;
        }
        case Map::Season::Spring: {
            createDefaultMap(map);
            addStoneWallInColor(PLATFORM_SIZE + sf::Vector2f{2000,0}, PLATFORM_POSITION + sf::Vector2f({1400,-2 * LEVEL_HEIGHT}),map);

            break;
        }
        case Map::Season::Summer: {
            createDefaultMap(map);
        }
    }
}
