#include "Bomba.h"
#include "funcionesglobales.h"

Bomba::Bomba(b2World& world)
{
	_world = &world;
}

void Bomba::update()
{
	if (_itemBody != nullptr) {
		b2Vec2 position = _itemBody->GetPosition();
		float angle = _itemBody->GetAngle();

		sf::Vector2f pixelPosition = WorldToPixel(position);
		_bomba.setPosition(pixelPosition);
		_bomba.setRotation(angle * 180.0f / b2_pi);
	}
}

void Bomba::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_bomba, states);
}

void Bomba::Aparecer(b2World& world)
{
	_random_number = 150 + std::rand() % 551;

	_bodyDef.type = b2_dynamicBody;
	_bodyDef.position = b2Vec2(_random_number / SCALE, 300 / SCALE);
	_bodyDef.fixedRotation = true;
	_bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	_itemBody = world.CreateBody(&_bodyDef);

	b2CircleShape _shape;
	_shape.m_radius = 30 / SCALE;
	_itemBody->CreateFixture(&_shape, 1.0);

	_textureBomba.loadFromFile("Recursos/bomba.png");
	_bomba.setTexture(_textureBomba);
	_bomba.setOrigin(_bomba.getGlobalBounds().width / 2, _bomba.getGlobalBounds().height / 2);
}

int Bomba::GenerarSiguienteIntervalo()
{
	int intervalo = 20 + std::rand() % 10;
	return intervalo;
}

void Bomba::setUltimaAparicion(int intervalo)
{
	_ultimaAparicion = intervalo;
}

b2Body* Bomba::getBody()
{
	return _itemBody;
}

int Bomba::getUltimaAparicion()
{
	return _ultimaAparicion;
}

void Bomba::Destroy()
{
	if (_itemBody != nullptr) {
		_world->DestroyBody(_itemBody);
		_itemBody = NULL;
	}
}
