#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Limite
{
public:
    Limite() {}
    Limite(b2World &world, sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d);
    void setBodyLimite(b2World& world);
    void setShapeLimite(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d);
    const b2Body* getBody();
private:
    b2Body* _bodyLimite;
    b2ChainShape _limite;
};

