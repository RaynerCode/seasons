#include "Factory.h"

void createDefaultMap(Map& map) {
    auto &platform2 = map.createWall(PLATFORM_SIZE, (PLATFORM_POSITION + sf::Vector2f{100, -450}));
    auto &waterfall = map.createWall(PLATFORM_SIZE + sf::Vector2f{100, PLATFORM_SIZE.y * 50},
                                     (PLATFORM_POSITION + sf::Vector2f{400, -900}));
    platform2.m_shape.setFillColor(season_colors[static_cast<int>(map.season)]);
    waterfall.m_shape.setFillColor(season_colors[static_cast<int>(map.season)]);
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
            break;
        }
        case Map::Season::Summer: {
            const auto platform1 = map.addWall(std::make_unique<ThornPlatform>(PLATFORM_SIZE, (PLATFORM_POSITION + sf::Vector2f{800, -150})));
            platform1->m_shape.setFillColor(season_colors[static_cast<int>(map.season)]);
        }
    }
}
