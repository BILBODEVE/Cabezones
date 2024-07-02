#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Colisionable.h"
#include "Entity.h"

class CampoDeJuego : public sf::Drawable, public Colisionable
{
public:
	CampoDeJuego() {}
	CampoDeJuego(b2World &world);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::FloatRect getBounds() const override;
private:
	sf::Sprite _spriteCancha;
	sf::Texture _cancha;
	sf::Sprite _spriteViga1;
	sf::Sprite _spriteViga2;
	b2Body* _bodyViga1;
	b2Body* _bodyViga2;
	sf::Texture _viga1;
	sf::Texture _viga2;
	sf::VertexArray _obstaculo;
};