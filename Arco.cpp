#include <box2d/box2d.h>
#include <iostream>
#include "Arco.h"
#include "funcionesglobales.h"

Arco::Arco(b2World& world, int id, const sf::Vector2f& position, const sf::Vector2f& size)
{
    setPosicionSensor(position);
    setBodyArco(world, position, size);
    setShapeArco(position, size);
    setID(id);
    //b2BodyDef bodyarc;
    //sf::Vector2f posSensor;

    //if (id == 1) {
    //    posSensor=sf::Vector2f(position.x - (diamPelota / 2), position.y);
    //}
    //else {
    //    posSensor = sf::Vector2f(position.x + (diamPelota / 2), position.y);
    //}

    //bodyarc.position=PixelToWorld(posSensor);
    //bodyarc.type = b2_staticBody;
    //bodyarc.userData.pointer = reinterpret_cast<uintptr_t>(this);
    //_bodyArco = world.CreateBody(&bodyarc);
    //
    //b2PolygonShape polygonShape;
    //polygonShape.SetAsBox((size.x-diamPelota)/2/SCALE, size.y/2/SCALE);
    //
    //b2FixtureDef arcfix;
    //arcfix.shape = &polygonShape;
    //arcfix.isSensor=true; // se declara como sensor para que no colisione con otros elementos
    //_bodyArco->CreateFixture(&arcfix);

 
    //_textureArc.loadFromFile("recursos/arco.png");
    //_arco.setTexture(&_textureArc);
    //_arco.setSize(size);
    //_arco.setPosition(position);
    //_arco.setOrigin(size.x / 2, size.y / 2);

    
    // travesaño
    //b2BodyDef bodyTra;
    //bodyTra.type = b2_staticBody;
    //sf::Vector2f pos(position.x, position.y - (size.y / 2));
    //bodyTra.position = PixelToWorld(pos);
    //_bodyT = world.CreateBody(&bodyTra);

    //b2PolygonShape polTravesanio;
    //polTravesanio.SetAsBox(size.x/SCALE/2, 5/SCALE/2);

    //b2FixtureDef fixTravesanio;
    //fixTravesanio.shape= &polTravesanio;
    //fixTravesanio.restitution = 0.0f; //entre 0 y 1;
    //fixTravesanio.friction = 0.3f;
    //_bodyT->CreateFixture(&fixTravesanio);

    _travesanio.setFillColor(sf::Color::Transparent);
    _travesanio.setOrigin(size.x / 2, size.y / 2);
    _travesanio.setPosition(position);
    _travesanio.setSize(sf::Vector2f(size.x, 5));

}

void Arco::setBodyArco(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size/*, float diamPelota*/)
{
    b2BodyDef bodyarc;
    ///sf::Vector2f posSensor;

    bodyarc.position = PixelToWorld(posicionSensor);
    bodyarc.type = b2_staticBody;
    bodyarc.userData.pointer = reinterpret_cast<uintptr_t>(this);
    _bodyArco = world.CreateBody(&bodyarc);

    b2PolygonShape polygonShape;
    /*polygonShape.SetAsBox((size.x - diamPelota) / 2 / SCALE, size.y / 2 / SCALE);*/
    polygonShape.SetAsBox(size.x / 2 / SCALE, size.y / 2 / SCALE);

    b2FixtureDef arcfix;
    arcfix.shape = &polygonShape;
    arcfix.isSensor = true; // se declara como sensor para que no colisione con otros elementos
    _bodyArco->CreateFixture(&arcfix);

    // travesaño
    b2BodyDef bodyTra;
    bodyTra.type = b2_staticBody;
    //sf::Vector2f pos(position.x, position.y - (size.y / 2));
    sf::Vector2f pos(position.x, position.y - (size.y / 2));
    bodyTra.position = PixelToWorld(pos);
    _bodyT = world.CreateBody(&bodyTra);

    b2PolygonShape polTravesanio;
    //polTravesanio.SetAsBox(size.x/SCALE/2, 5/SCALE/2);
    polTravesanio.SetAsBox(size.x / SCALE / 2, 5 / SCALE / 2);

    b2FixtureDef fixTravesanio;
    fixTravesanio.shape = &polTravesanio;
    fixTravesanio.restitution = 0.0f; //entre 0 y 1;
    fixTravesanio.friction = 0.3f;
    _bodyT->CreateFixture(&fixTravesanio);

}

void Arco::setShapeArco(const sf::Vector2f& position, const sf::Vector2f& size)
{
    _textureArc.loadFromFile("recursos/arco.png");
    _arco.setTexture(&_textureArc);
    _arco.setSize(size);
    _arco.setPosition(position);
    _arco.setOrigin(size.x / 2, size.y / 2);

    _travesanio.setFillColor(sf::Color::Transparent);
    _travesanio.setOrigin(size.x / 2, size.y / 2);
    _travesanio.setPosition(position);
    _travesanio.setSize(sf::Vector2f(size.x, 5));
}

void Arco::setID(int id)
{
    this->id = id;
}


void Arco::setPosicionSensor(const sf::Vector2f& position)
{
    /*if (id == 1) {
        posSensor = sf::Vector2f(position.x - (diamPelota / 2), position.y);
    }
    else {
        posSensor = sf::Vector2f(position.x + (diamPelota / 2), position.y);
    }*/
    posicionSensor = sf::Vector2f(position.x, position.y);
    
}

int Arco::getID() const
{
    return id;
}

const b2Body* Arco::getBody()
{
    return _bodyArco;
}

sf::RectangleShape Arco::getShape()
{
    return _arco;
}

void Arco::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = &_textureArc;
    target.draw(_arco, states);
    target.draw(_travesanio);
}
