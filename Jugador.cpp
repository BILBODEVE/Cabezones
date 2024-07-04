#include <iostream>
#include "Jugador.h"
#include "funcionesglobales.h"

Jugador::Jugador()
{
	velocity = sf::Vector2f(0, 0);
	moveSpeed = 250;
	jumpSpeed = 450;
	_goles = 0;
	frame = 0;
	_spriteFrames = 6;
	state = PlayerState::STILL;
	move = PlayerState::STILL;
}

Jugador::Jugador(b2World& world, std::string textureRoute, sf::Vector2f position, int id, sf::Keyboard::Key jump, sf::Keyboard::Key moveRight, sf::Keyboard::Key moveLeft, sf::Keyboard::Key kick)
	: keyOfMovement(jump, moveRight, moveLeft, kick)
{
	playerID = id;
	velocity = sf::Vector2f(0, 0);
	frame = 0;
	moveSpeed = 250;
	jumpSpeed = 450;
	state = PlayerState::STILL;
	move = PlayerState::STILL;
	_posicion = position;
	_goles = 0;
	_spriteFrames = 6;

	createSprite(textureRoute);
	createBodyPlayer(world);
}

void Jugador::command()
{
	state = PlayerState::STILL;
	move = PlayerState::STILL;
	
	if (_bodyJugador->GetLinearVelocity().y == 0) {
		if (sf::Keyboard::isKeyPressed(keyOfMovement.getKeyToMoveForward())) {
			state = PlayerState::RUNNING_FORWARD;
		}
		if (sf::Keyboard::isKeyPressed(keyOfMovement.getKeyToMoveBackward())) {
			state = PlayerState::RUNNING_BACKWARD;
		}
		if (sf::Keyboard::isKeyPressed(keyOfMovement.getKeyToJump()))
		{
			state = PlayerState::JUMPING;
			if (sf::Keyboard::isKeyPressed(keyOfMovement.getKeyToMoveForward()))
				move = PlayerState::RUNNING_FORWARD;
			if (sf::Keyboard::isKeyPressed(keyOfMovement.getKeyToMoveBackward()))
				move = PlayerState::RUNNING_BACKWARD;
		}
		if (sf::Keyboard::isKeyPressed(keyOfMovement.getKeyToKick()))
			state = PlayerState::KICKING;
	}
}

void Jugador::update()
{
	switch (state)
	{
	case PlayerState::RUNNING_FORWARD:
		velocity.x = moveSpeed;
		_bodyJugador->SetLinearVelocity(PixelToWorld(velocity));
		break;
	case PlayerState::RUNNING_BACKWARD:
		velocity.x = -moveSpeed;
		_bodyJugador->SetLinearVelocity(PixelToWorld(velocity));
		break;
	case PlayerState::JUMPING:
		if (move == PlayerState::RUNNING_FORWARD)
			velocity.x = moveSpeed / 4;
		if (move == PlayerState::RUNNING_BACKWARD)
			velocity.x = -moveSpeed / 4;
		velocity.y = -jumpSpeed;
		_bodyJugador->ApplyLinearImpulseToCenter(PixelToWorld(velocity), true);
		break;
	case PlayerState::KICKING:
		if (frame >= _spriteFrames)
			frame = 0;
		else
			frame += 1.0f;
		break;
	case PlayerState::STILL:
		frame = 0;
		velocity.x = 0;
		velocity.y = 0;
		break;
	}

	sprite.setTextureRect({ 0 + (int)frame * _spriteWidth , 0, _spriteWidth, _spriteHeight });

	b2Vec2 playerPosition = _bodyJugador->GetPosition();
	float angle = _bodyJugador->GetAngle();
	sprite.setPosition(WorldToPixel(playerPosition));
	sprite.setOrigin(_spriteWidth / 2.0f, _spriteHeight / 2.0f);
	sprite.setRotation(angle * 180.0f / b2_pi);
}

void Jugador::createBodyPlayer(b2World& world)
{
	_playerBody.type = b2_dynamicBody;
	_playerBody.position = PixelToWorld(_posicion);
	_playerBody.linearDamping = 1.0f;
	_playerBody.fixedRotation = true;
	_playerBody.userData.pointer = reinterpret_cast<uintptr_t>(this);
	_bodyJugador = world.CreateBody(&_playerBody);

	const b2Vec2 center = b2Vec2(0, 0);
	_shape.SetAsBox((_spriteWidth / 2.0f) / SCALE, (_spriteHeight / 2.0f) / SCALE);

	b2FixtureDef _playerFixture;
	_playerFixture.shape = &_shape;
	_playerFixture.density = 1.0f;
	_playerFixture.friction = 1.0f;
	_playerFixture.restitution = 0.0f;
	_playerFixture.restitutionThreshold = 500;
	_bodyJugador->CreateFixture(&_playerFixture);
}

void Jugador::createSprite(std::string textureRoute)
{
	_textRoute = textureRoute;
	if (!texture.loadFromFile(_textRoute))
		exit(-1);
	sprite.setTexture(texture);
	_spriteHeight = sprite.getGlobalBounds().getSize().y;
	_spriteWidth = sprite.getGlobalBounds().getSize().x / _spriteFrames;
	sprite.setTextureRect({ 0,0,_spriteWidth, _spriteHeight });
	sprite.setOrigin(_spriteWidth / 2.0f, _spriteHeight / 2.0f);
	sprite.setPosition(_posicion);
}

void Jugador::setPosicion(sf::Vector2f position)
{
	_posicion = position;
}

void Jugador::setControles(sf::Keyboard::Key jump, sf::Keyboard::Key moveRight, sf::Keyboard::Key moveLeft, sf::Keyboard::Key kick)
{
	keyOfMovement.setKeyToJump(jump);
	keyOfMovement.setKeyToMoveForward(moveRight);
	keyOfMovement.setKeyToMoveBackward(moveLeft);
	keyOfMovement.setKeyToKick(kick);
}

void Jugador::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(sprite, state);
}


void Jugador::addGol()
{
	_goles++;
}

int Jugador::getGoles()
{
	return _goles;
}

void Jugador::resetGoles()
{
	_goles = 0;
}

void Jugador::setName(std::string name)
{
	_name = name;
}

std::string Jugador::getName()
{
	return _name;
}

sf::Sprite& Jugador::getSprite()
{
	return sprite;
}

b2Body* Jugador::getBody()
{
	return _bodyJugador;
}

bool Jugador::isKicking()
{
	if (sf::Keyboard::isKeyPressed(keyOfMovement.getKeyToKick())) {
		return true;
	}
	return false;
}

void Jugador::setPlayerID(int ID)
{
	if (ID > 0 && ID <= 2)
		playerID = ID;
}

void Jugador::setPosicionInicial(int id)
{
	if (id == 1) {
		_bodyJugador->SetTransform(PixelToWorld(sf::Vector2f(0 + 40 + 82, 429)), 0);
	}

	if (id == 2) {
		_bodyJugador->SetTransform(PixelToWorld(sf::Vector2f(800 - 40 - 82, 429)), 0);
	}
}

void Jugador::setMoveSpeed(float velocity)
{
	moveSpeed = velocity;
}

void Jugador::setJumpSpeed(float jumpVelocity)
{
	jumpSpeed = jumpVelocity;
}

//void Jugador::crearJugador(bool cabezaAumentada)
//{
//	if (_bodyJugador != nullptr) {
//		_posicion = WorldToPixel(_bodyJugador->GetPosition());
//		_world->DestroyBody(_bodyJugador);
//	}
//
//	_playerBody.type = b2_dynamicBody;
//	_playerBody.position = PixelToWorld(_posicion);
//	_playerBody.linearDamping = 1.0f;
//	_playerBody.fixedRotation = true;
//	_playerBody.userData.pointer = reinterpret_cast<uintptr_t>(this);
//	_bodyJugador = _world->CreateBody(&_playerBody);
//
//	shape.SetAsBox((_spriteWidth / 2.0f) / SCALE, (_spriteHeight / 2.0f) / SCALE);
//
//	b2FixtureDef _playerFixture;
//	_playerFixture.shape = &shape;
//	_playerFixture.density = 1.0f;
//	_playerFixture.friction = 1.0f;
//	_playerFixture.restitution = 0.0f;
//	_playerFixture.restitutionThreshold = 500;
//	_bodyJugador->CreateFixture(&_playerFixture);
//
//	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
//
//	if (playerID == 2) {
//		sprite.setScale(-1, 1);
//		if (cabezaAumentada == true) {
//			sprite.setScale(-1.5, 1.5);
//		}
//	}
//	else {
//		sprite.setScale(1, 1);
//		if (cabezaAumentada == true) {
//			sprite.setScale(1.5, 1.5);
//		}
//
//	}
//	sprite.setPosition(_posicion);
//}

