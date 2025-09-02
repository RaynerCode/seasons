#pragma once
#include <SFML/Graphics.hpp>

class Platform {
public:
    enum class Type{
        Stone,
        Ice,
        Thorn,
        Leaf,
        Vine
    };
    sf::RectangleShape m_shape;
    Platform(const sf::Vector2f&, const sf::Vector2f&, Type = Type::Stone);
    virtual ~Platform() = default;
    Type getType() const;
private:
    Type m_type;
};

class IcePlatform : public Platform {
public:
    IcePlatform(const sf::Vector2f&, const sf::Vector2f&, float, float);
private:
    float mu_s_max;
    float mu_k;
};

class ThornPlatform : public Platform {
    ThornPlatform(const sf::Vector2f&, const sf::Vector2f&);
};

class LeafPlatform : public Platform {
    LeafPlatform(const sf::Vector2f&, const sf::Vector2f&);

};

class VinePlatform : public Platform {
    VinePlatform(const sf::Vector2f&, const sf::Vector2f&);
};