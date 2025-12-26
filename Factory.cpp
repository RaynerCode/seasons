#include "Factory.h"
constexpr sf::Color GRAY = sf::Color({109, 106, 100});
constexpr float LEVEL_HEIGHT_WINDOW_RATIO = 5.4f;
float LEVEL_HEIGHT;
constexpr sf::Vector2f PLATFORM_WINDOW_SIZE_RATIO = {9.6, 54};
constexpr sf::Vector2f PLATFORM_WINDOW_POSITION_RATIO = {19.2, 1.54};
sf::Vector2u WINDOW_SIZE;
sf::Vector2f PLATFORM_SIZE;;
sf::Vector2f PLATFORM_POSITION;;



void createDefaultMap(Map& map) {
    if(WINDOW_SIZE.x == 0) { //ensures only happens once
        WINDOW_SIZE = map.window_size;
        std::cout << "window size x: " << WINDOW_SIZE.x << "window size y: " << WINDOW_SIZE.y << std::endl;
        PLATFORM_SIZE = {static_cast<float>(WINDOW_SIZE.x) / PLATFORM_WINDOW_SIZE_RATIO.x, static_cast<float>(WINDOW_SIZE.y) / PLATFORM_WINDOW_SIZE_RATIO.y};
        std::cout << "platform size x: " << PLATFORM_SIZE.x << "platform size y: " << PLATFORM_SIZE.y << std::endl;
        PLATFORM_POSITION = {static_cast<float>(WINDOW_SIZE.x) / PLATFORM_WINDOW_POSITION_RATIO.x, static_cast<float>(WINDOW_SIZE.y) / PLATFORM_WINDOW_POSITION_RATIO.y};
        std::cout << "platform position x: " << PLATFORM_POSITION.x << "platform position y: " << PLATFORM_POSITION.y << std::endl;
        LEVEL_HEIGHT = static_cast<float>(WINDOW_SIZE.y) / LEVEL_HEIGHT_WINDOW_RATIO;
        std::cout << "level height: " << LEVEL_HEIGHT << std::endl;
    }

    //addStoneWallInGray(sf::Vector2f{300, 1000}, (PLATFORM_POSITION + sf::Vector2f{400, -1000}), map);
    addStoneWallInGray(PLATFORM_SIZE, (PLATFORM_POSITION + sf::Vector2f{convertX(100), -2 * LEVEL_HEIGHT}), map);
    addStoneWallInGray(PLATFORM_SIZE, (PLATFORM_POSITION + sf::Vector2f{convertX(800), -2 * LEVEL_HEIGHT}), map);
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
            const auto platform1 = map.addWall(std::make_unique<LeafPlatform>(PLATFORM_SIZE,PLATFORM_POSITION - sf::Vector2f{convertX(100),convertY(200)}));
            platform1->m_shape.setFillColor(season_colors[static_cast<int>(map.season)]);
            break;
        }
        case Map::Season::Winter: {
            createDefaultMap(map);
            break;
        }
        case Map::Season::Spring: {
            createDefaultMap(map);
            addStoneWallInColor(PLATFORM_SIZE + sf::Vector2f{convertX(200),0}, PLATFORM_POSITION + sf::Vector2f({convertX(1400),-2 * LEVEL_HEIGHT}),map);

            break;
        }
        case Map::Season::Summer: {
            createDefaultMap(map);
        }
    }
}

float convertX(const float original) {
    return static_cast<float>(WINDOW_SIZE.x) / (1920.f / original);
}

float convertY(const float original) {
    return static_cast<float>(WINDOW_SIZE.y) / (1080.f / original);
}
