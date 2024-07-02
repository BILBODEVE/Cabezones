#include "Limite.h"
#include "funcionesglobales.h"

const int CANT_VERTICES = 4;

Limite::Limite(b2World& world, sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d)
{
    /*b2Vec2 vs[CANT_VERTICES];
    vs[0] = PixelToWorld(a);
    vs[1] = PixelToWorld(b);
    vs[2] = PixelToWorld(c);
    vs[3] = PixelToWorld(d);
  
    _limite.CreateLoop(vs, 4);*/
    setShapeLimite(a,b,c,d);
    setBodyLimite(world);
    //b2BodyDef bodyDef;
    //bodyDef.position.Set(0.0f, 0.0f);
    //bodyDef.type = b2_staticBody; //estatico, dinamico o kinetico
    //_bodyLimite = world.CreateBody(&bodyDef);

    //_bodyLimite->CreateFixture(&_limite,0.0f);
 }

void Limite::setShapeLimite(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d)
{
    b2Vec2 vertices[4];
    vertices[0] = PixelToWorld(a);
    vertices[1] = PixelToWorld(b);
    vertices[2] = PixelToWorld(c);
    vertices[3] = PixelToWorld(d);

    _limite.CreateLoop(vertices, CANT_VERTICES);
}

void Limite::setBodyLimite(b2World& world)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(0.0f, 0.0f);
    bodyDef.type = b2_staticBody;
    _bodyLimite = world.CreateBody(&bodyDef);

    _bodyLimite->CreateFixture(&_limite, 0.0f);
}

const b2Body* Limite::getBody()
{
    return _bodyLimite;
}




