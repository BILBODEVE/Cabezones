#include <iostream>
#include <box2d/box2d.h>
#include "funcionesglobales.h"
#include "CampoDeJuego.h"


CampoDeJuego::CampoDeJuego(b2World &world) 
{
    _cancha.loadFromFile("recursos/cancha.jpg");
    _spriteCancha.setTexture(_cancha);

    _viga1.loadFromFile("recursos/viga3.png");
    _spriteViga1.setTexture(_viga1);

    _viga2.loadFromFile("recursos/viga4.png");
    _spriteViga2.setTexture(_viga2);

    _spriteViga1.setOrigin(_spriteViga1.getGlobalBounds().width / 2, 0);
    _spriteViga1.setPosition(270, 0);
    
    _spriteViga2.setOrigin(_spriteViga2.getGlobalBounds().width / 2, 0);
    _spriteViga2.setPosition(530, 0);

    
    _obstaculo.setPrimitiveType(sf::Quads);
    _obstaculo.resize(8);
    _obstaculo[0].position = sf::Vector2f(170, 135);
    _obstaculo[1].position = sf::Vector2f(170, 155);
    _obstaculo[2].position = sf::Vector2f(368, 100);
    _obstaculo[3].position = sf::Vector2f(368, 60);

    _obstaculo[4].position = sf::Vector2f(628, 135);
    _obstaculo[5].position = sf::Vector2f(628, 155);
    _obstaculo[6].position = sf::Vector2f(432, 100);
    _obstaculo[7].position = sf::Vector2f(432, 60);

    for (int i = 0; i < 8; i++) {
        _obstaculo[i].color = sf::Color::Transparent;
    }

    b2BodyDef bodyViga;
    bodyViga.type = b2_staticBody;
    bodyViga.userData.pointer = reinterpret_cast<uintptr_t>(this);

    _bodyViga1 = world.CreateBody(&bodyViga);
    _bodyViga2 = world.CreateBody(&bodyViga);


    b2Vec2 vertices[4];
    vertices[0] = PixelToWorld(_obstaculo[0].position);
    vertices[1] = PixelToWorld(_obstaculo[1].position);
    vertices[2] = PixelToWorld(_obstaculo[2].position);
    vertices[3] = PixelToWorld(_obstaculo[3].position);

    b2Vec2 vertices2[4];
    vertices2[0] = PixelToWorld(_obstaculo[4].position);
    vertices2[1] = PixelToWorld(_obstaculo[5].position);
    vertices2[2] = PixelToWorld(_obstaculo[6].position);
    vertices2[3] = PixelToWorld(_obstaculo[7].position);

    int32 count = 4;
    b2PolygonShape polygon;
    polygon.Set(vertices, count);

    b2PolygonShape polygon2;
    polygon2.Set(vertices2, count);

    b2FixtureDef fixViga1;
    fixViga1.friction = 0.3f;
    fixViga1.restitution = 0.4f;
    fixViga1.shape = &polygon;
    _bodyViga1->CreateFixture(&fixViga1);

    
    b2FixtureDef fixViga2;
    fixViga2.friction = 0.3f;
    fixViga2.restitution = 1.0f;
    fixViga2.shape = &polygon2;
    _bodyViga2->CreateFixture(&fixViga2);

}


void CampoDeJuego::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_spriteCancha);
    target.draw(_spriteViga1); 
    target.draw(_spriteViga2);
    target.draw(_obstaculo);

}

sf::FloatRect CampoDeJuego::getBounds() const
{
    return _obstaculo.getBounds();
}
