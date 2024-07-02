#pragma once
#include <SFML/Graphics.hpp>
#include "Colisionable.h"
#include "ProjectSettings.h"
#include "Entity.h"

class Arco : public sf::Drawable
{
public:
	Arco() {}
	///Arco(b2World &world, int id, const sf::Vector2f &position, const sf::Vector2f &size , float diamPelota);
	Arco(b2World& world, int id, const sf::Vector2f& position, const sf::Vector2f& size);
	void setBodyArco(b2World& world, const sf::Vector2f& position,const sf::Vector2f& size);
	void setShapeArco(const sf::Vector2f& position, const sf::Vector2f& size);
	void setID(int id);
	void setPosicionSensor(const sf::Vector2f& position);
	int getID() const;
	const b2Body* getBody();
	sf::RectangleShape getShape();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	b2Body *_bodyArco;
	sf::Texture _textureArc;
	sf::RectangleShape _arco;
	b2Body* _bodyT;
	sf::RectangleShape _travesanio;
	sf::Vector2f posicionSensor;
	int id;
};

