#include "Pelota.h"

Pelota::Pelota(b2World& world, const sf::Vector2f& position, float radius)
{
    setRadius(radius);
    setBodyPelota(world, position);
    setShapePelota(position);
    //// Crear el cuerpo de Box2D
    //b2BodyDef bodyDef;
    //bodyDef.type = b2_dynamicBody;
    //bodyDef.position = PixelToWorld(position);
    //bodyDef.linearDamping = 0.4f;
    //bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    //_bodyPelota = world.CreateBody(&bodyDef);
    //   
    // // Crear la forma de la pelota en Box2D
    //b2CircleShape circleShape;
    //circleShape.m_radius = radius / SCALE;

    //// Definir las propiedades físicas de la pelota
    //b2FixtureDef fixtureDef;
    //fixtureDef.shape = &circleShape;
    //fixtureDef.density = 0.5f;
    //fixtureDef.friction = 0.6f;
    //fixtureDef.restitution = 0.6f; // Rebote
    //_bodyPelota->CreateFixture(&fixtureDef);

    // Crear la representación gráfica de SFML
 /*   _texture.loadFromFile("recursos/pelota.png");
    _pelota.setTexture(&_texture);
    _pelota.setRadius(radius);
    _pelota.setOrigin(radius, radius);
    _pelota.setPosition(position);*/
}

void Pelota::setBodyPelota(b2World& world, const sf::Vector2f& position)
{
    // Crear el cuerpo de Box2D
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = PixelToWorld(position);
    bodyDef.linearDamping = 0.4f;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    _bodyPelota = world.CreateBody(&bodyDef);

    // Crear la forma de la pelota en Box2D
    b2CircleShape circleShape;
    circleShape.m_radius = radius / SCALE;

    // Definir las propiedades físicas de la pelota
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.6f;
    fixtureDef.restitution = 0.6f; // Rebote
    _bodyPelota->CreateFixture(&fixtureDef);
}

void Pelota::setShapePelota(const sf::Vector2f& position)
{
    _texture.loadFromFile("recursos/pelota.png");
    _pelota.setTexture(&_texture);
    _pelota.setRadius(radius);
    _pelota.setOrigin(radius, radius);
    _pelota.setPosition(position);
}

void Pelota::setRadius(float radius)
{
    this->radius = radius;
}

void Pelota::update()
{
    // Obtener la posición y ángulo del cuerpo de Box2D
    b2Vec2 position = _bodyPelota->GetPosition();
    float angle = _bodyPelota->GetAngle();

    // Convertir la posición a píxeles y actualizar la forma de SFML
    sf::Vector2f pixelPosition = WorldToPixel(position);
    _pelota.setPosition(pixelPosition);
    _pelota.setRotation(angle * 180.0f / b2_pi); //de radianes a grados
}

void Pelota::setPosition(const sf::Vector2f& position)
{
    b2Vec2 worldPosition = PixelToWorld(position);
    _bodyPelota->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    _bodyPelota->SetAngularVelocity(0.0f);
    _bodyPelota->SetTransform(PixelToWorld(position),0);
}

float Pelota::getRadius()
{
    return radius;
}

b2Body* Pelota::getBody()
{
    return _bodyPelota;
}

void Pelota::setWorldPosition(const b2Vec2& worldPosition)
{
    _bodyPelota->SetTransform(worldPosition, _bodyPelota->GetAngle());
    _pelota.setPosition(WorldToPixel(worldPosition));
}


bool Pelota::setTexture(const std::string& textureFile) {
    if (!_texture.loadFromFile(textureFile)) {
        return false; // Error al cargar la textura
    }
    _pelota.setTexture(&_texture);
    return true;
}

void Pelota::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_pelota, states);
}
