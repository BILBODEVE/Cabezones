#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

const float SCALE = 80.0F;

sf::Vector2f WorldToPixel(const b2Vec2& worldCoords);

b2Vec2 PixelToWorld(const sf::Vector2f& pixelCoords);
