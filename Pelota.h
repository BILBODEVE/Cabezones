#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "funcionesglobales.h"

class Pelota: public sf::Drawable
{
public:
	Pelota() {}
	Pelota(b2World& world, const sf::Vector2f& position, float radius);
	void setBodyPelota(b2World& world, const sf::Vector2f& position);
	void setShapePelota(const sf::Vector2f& position);
	void setRadius(float radius);
	void update();
	void setPosition(const sf::Vector2f& position);
	float getRadius();
	b2Body* getBody();
	void setWorldPosition(const b2Vec2& worldPosition);
	bool setTexture(const std::string& textureFile);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	b2Body* _bodyPelota;
	sf::CircleShape _pelota;
	sf::Texture _texture;
	float _radius;
};

