#include "Aumentador.h"
#include "funcionesglobales.h"

Aumentador::Aumentador(b2World& world)
{
	_world = &world;
}

void Aumentador::update()
{
	if (_itemBody != nullptr) {
		b2Vec2 position = _itemBody->GetPosition();
		float angle = _itemBody->GetAngle();

		sf::Vector2f pixelPosition = WorldToPixel(position);
		_aumentador.setPosition(pixelPosition);
		_aumentador.setRotation(angle * 180.0f / b2_pi);
	}
}

void Aumentador::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_aumentador, states);
}

void Aumentador::Aparecer(b2World& world)
{
	random_number = 150 + std::rand() % 551;

	_bodyDef.type = b2_dynamicBody;
	_bodyDef.position = b2Vec2(random_number / SCALE, 300 / SCALE);
	_bodyDef.fixedRotation = true;
	_bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	_itemBody = world.CreateBody(&_bodyDef);

	b2CircleShape _shape;
	_shape.m_radius = 30 / SCALE;
	_itemBody->CreateFixture(&_shape, 1.0);

	_textureAumentador.loadFromFile("Recursos/aumentador.png");
	_aumentador.setTexture(_textureAumentador);
	_aumentador.setOrigin(_aumentador.getGlobalBounds().width / 2, _aumentador.getGlobalBounds().height / 2);
}

int Aumentador::GenerarSiguienteIntervalo()
{
	int intervalo = 20 + std::rand() % 10;
	return intervalo;
}

void Aumentador::setUltimaAparicion(int intervalo)
{
	_ultimaAparicion = intervalo;
}

b2Body* Aumentador::getBody()
{
	return _itemBody;
}

int Aumentador::getUltimaAparicion()
{
	return _ultimaAparicion;
}

void Aumentador::Destroy()
{
	if (_itemBody != nullptr) {
		_world->DestroyBody(_itemBody);//mundo destruye el cuerpo
		_itemBody = NULL;//body=null
	}
}
