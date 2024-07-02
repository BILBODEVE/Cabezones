#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
class Bomba: public sf::Drawable
{
public:
	Bomba(b2World& world);
	void setUltimaAparicion(int intervalo);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Aparecer(b2World& world);
	int GenerarSiguienteIntervalo();
	b2Body* getBody();
	int getUltimaAparicion();
	void Destroy();
private:
	sf::Sprite _bomba;
	sf::Texture _textureBomba;
	b2World* _world;
	b2Body* _itemBody;
	b2BodyDef _bodyDef;
	int random_number;
	int _ultimaAparicion;
};

