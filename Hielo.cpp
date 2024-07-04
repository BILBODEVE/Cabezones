#include "Hielo.h"
#include "funcionesglobales.h"

Hielo::Hielo(b2World& world)
{
	_world = &world;	
}

void Hielo::update()
{
	if (_itemBody != nullptr) {
		b2Vec2 position = _itemBody->GetPosition();
		float angle = _itemBody->GetAngle();

		sf::Vector2f pixelPosition = WorldToPixel(position);
		_hielo.setPosition(pixelPosition);
		_hielo.setRotation(angle * 180.0f / b2_pi);
	}
}

void Hielo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_hielo, states);
}

void Hielo::Aparecer(b2World& world)
{
	random_number = 150 + std::rand() % 551;

	_bodyDef.type = b2_dynamicBody;    
	_bodyDef.position = b2Vec2(random_number / SCALE, 300 / SCALE);
	_bodyDef.fixedRotation = true;
	_bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	_itemBody = world.CreateBody(&_bodyDef);
		
	b2Vec2 cubo[5];
	cubo[0].Set(40/ SCALE, 0 / SCALE);
	cubo[1].Set(0 / SCALE, 16 / SCALE);
	cubo[2].Set(0 / SCALE,65 / SCALE);
	cubo[3].Set(80 / SCALE, 65 / SCALE);
	cubo[4].Set(80 / SCALE, 16 / SCALE);

	b2Vec2 currentCentroid(0.0f, 0.0f);

	for (int32 i = 0; i < 5; ++i) {
		currentCentroid += cubo[i];
	}

	currentCentroid *= 1.0f / 5;

	for (int32 i = 0; i < 5; i++) {
		cubo[i] -= currentCentroid;
	}

	b2PolygonShape _shape;
	_shape.Set(cubo, 5);
	_itemBody->CreateFixture(&_shape, 1.0);

	_textureHielo.loadFromFile("Recursos/cubohielo.png");
	_hielo.setTexture(_textureHielo);
	_hielo.setOrigin(_hielo.getGlobalBounds().width / 2, _hielo.getGlobalBounds().height / 2);
}

int Hielo::GenerarSiguienteIntervalo()
{
	int intervalo = 20 + std::rand() % 10;
	return intervalo;
}

void Hielo::setUltimaAparicion(int intervalo)
{
	_ultimaAparicion = intervalo;
}

b2Body* Hielo::getBody()
{
	return _itemBody;
}

int Hielo::getUltimaAparicion()
{
	return _ultimaAparicion;
}

void Hielo::Destroy()
{
	if (_itemBody != nullptr) {
		_world->DestroyBody(_itemBody);//mundo destruye el cuerpo
		_itemBody = NULL;//body=null
	}
}
