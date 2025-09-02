#include "Platform.h"

Platform::Platform(const sf::Vector2f& size, const sf::Vector2f& position, const Type type) :
m_shape(size), m_type(type){
    m_shape.move(position);
}

Platform::Type Platform::getType() const {return m_type;}

IcePlatform::IcePlatform(const sf::Vector2f& size, const sf::Vector2f& position, const float m1, const float m2)
: Platform(size, position, Type::Ice), mu_s_max(m1), mu_k(m2){

}

ThornPlatform::ThornPlatform(const sf::Vector2f& size, const sf::Vector2f& position) :
Platform(size, position, Type::Thorn) {}


LeafPlatform::LeafPlatform(const sf::Vector2f& size, const sf::Vector2f& position) :
Platform(size, position, Type::Leaf) {}


VinePlatform::VinePlatform(const sf::Vector2f& size, const sf::Vector2f& position) :
Platform(size, position, Type::Vine) {}

