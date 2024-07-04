#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Hielo: public sf::Drawable
{
public:
	Hielo(b2World& world);
	void setUltimaAparicion(int intervalo);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Aparecer(b2World& world);
	int GenerarSiguienteIntervalo();
	b2Body* getBody();
	int getUltimaAparicion();
	void Destroy();
private:
	sf::Sprite _hielo;
	sf::Texture _textureHielo;
	b2World* _world;
	b2Body* _itemBody;
	b2BodyDef _bodyDef;
	int _random_number;
	int _ultimaAparicion;
};

