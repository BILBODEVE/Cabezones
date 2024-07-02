#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Suelo: public sf::Drawable
{
public:
	Suelo() {}
	Suelo(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size);
	void setBodySuelo(b2World& world, const sf::Vector2f& position);
	void setShapeSuelo(const sf::Vector2f& size, const sf::Vector2f& position);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	b2Body* _bodySuelo;
	sf::RectangleShape _suelo;
};

