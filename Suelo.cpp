#include "Suelo.h"
#include "funcionesglobales.h"

Suelo::Suelo(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size)
{
	setBodySuelo(world, position);
	setShapeSuelo(size, position);
	/*b2BodyDef sueloDef;
	sueloDef.position = PixelToWorld(position);
	sueloDef.type = b2_staticBody;
	sueloDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	_bodySuelo = world.CreateBody(&sueloDef);*/

	/*b2PolygonShape polygonShape;
	polygonShape.SetAsBox(size.x/ 2 / SCALE, size.y / 2 / SCALE);
	
	b2FixtureDef suelofix;
	suelofix.friction = .8f;
	suelofix.restitution = 0;
	suelofix.shape = &polygonShape;
	_bodySuelo->CreateFixture(&suelofix);
		
	_suelo.setOrigin(size.x / 2, size.y / 2);
	_suelo.setPosition(position);
	_suelo.setSize(size);
	_suelo.setFillColor(sf::Color::Transparent);*/
}

void Suelo::setBodySuelo(b2World& world, const sf::Vector2f& position)
{
	b2BodyDef sueloDef;
	sueloDef.position = PixelToWorld(position);
	sueloDef.type = b2_staticBody;
	sueloDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	_bodySuelo = world.CreateBody(&sueloDef);
}

void Suelo::setShapeSuelo(const sf::Vector2f& size, const sf::Vector2f& position)
{
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(size.x / 2 / SCALE, size.y / 2 / SCALE);

	b2FixtureDef suelofix;
	suelofix.friction = .8f;
	suelofix.restitution = 0;
	suelofix.shape = &polygonShape;
	_bodySuelo->CreateFixture(&suelofix);

	_suelo.setOrigin(size.x / 2, size.y / 2);
	_suelo.setPosition(position);
	_suelo.setSize(size);
	_suelo.setFillColor(sf::Color::Transparent);
}

void Suelo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_suelo,states);

}
