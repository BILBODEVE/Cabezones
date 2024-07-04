#include "funcionesglobales.h"

// 80 PIXELES = 1 METRO

sf::Vector2f WorldToPixel(const b2Vec2& worldCoords)
{
    return sf::Vector2f(worldCoords.x * SCALE, worldCoords.y * SCALE);
}

b2Vec2 PixelToWorld(const sf::Vector2f& pixelCoords) {
    return b2Vec2(pixelCoords.x / SCALE, pixelCoords.y / SCALE);
}
