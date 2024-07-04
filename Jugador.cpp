#include <iostream>
#include "Jugador.h"
#include "funcionesglobales.h"

Jugador::Jugador()
{
	_velocity = sf::Vector2f(0, 0);
	_moveSpeed = 250;
	_jumpSpeed = 450;
	_goles = 0;
	_frame = 0;
	_spriteFrames = 6;
	_stateMove = PlayerState::STILL;
	_moveX = PlayerState::STILL;
}

Jugador::Jugador(b2World& world, std::string textureRoute, sf::Vector2f position, int id, sf::Keyboard::Key jump, sf::Keyboard::Key moveRight, sf::Keyboard::Key moveLeft, sf::Keyboard::Key kick)
	: _keyOfMovement(jump, moveRight, moveLeft, kick)
{
	_playerID = id;
	_velocity = sf::Vector2f(0, 0);
	_frame = 0;
	_moveSpeed = 250;
	_jumpSpeed = 450;
	_stateMove = PlayerState::STILL;
	_moveX = PlayerState::STILL;
	_posicion = position;
	_goles = 0;
	_spriteFrames = 6;

	createSprite(textureRoute);
	createBodyPlayer(world);
}

void Jugador::command()
{
	_stateMove = PlayerState::STILL;
	_moveX = PlayerState::STILL;
	
	if (_bodyJugador->GetLinearVelocity().y == 0) {
		if (sf::Keyboard::isKeyPressed(_keyOfMovement.getKeyToMoveForward())) {
			_stateMove = PlayerState::RUNNING_FORWARD;
		}
		if (sf::Keyboard::isKeyPressed(_keyOfMovement.getKeyToMoveBackward())) {
			_stateMove = PlayerState::RUNNING_BACKWARD;
		}
		if (sf::Keyboard::isKeyPressed(_keyOfMovement.getKeyToJump()))
		{
			_stateMove = PlayerState::JUMPING;
			if (sf::Keyboard::isKeyPressed(_keyOfMovement.getKeyToMoveForward()))
				_moveX = PlayerState::RUNNING_FORWARD;
			if (sf::Keyboard::isKeyPressed(_keyOfMovement.getKeyToMoveBackward()))
				_moveX = PlayerState::RUNNING_BACKWARD;
		}
		if (sf::Keyboard::isKeyPressed(_keyOfMovement.getKeyToKick()))
			_stateMove = PlayerState::KICKING;
	}
}

void Jugador::update()
{
	switch (_stateMove)
	{
	case PlayerState::RUNNING_FORWARD:
		_velocity.x = _moveSpeed;
		_bodyJugador->SetLinearVelocity(PixelToWorld(_velocity));
		break;
	case PlayerState::RUNNING_BACKWARD:
		_velocity.x = -_moveSpeed;
		_bodyJugador->SetLinearVelocity(PixelToWorld(_velocity));
		break;
	case PlayerState::JUMPING:
		if (_moveX == PlayerState::RUNNING_FORWARD)
			_velocity.x = _moveSpeed / 4;
		if (_moveX == PlayerState::RUNNING_BACKWARD)
			_velocity.x = -_moveSpeed / 4;
		_velocity.y = -_jumpSpeed;
		_bodyJugador->ApplyLinearImpulseToCenter(PixelToWorld(_velocity), true);
		break;
	case PlayerState::KICKING:
		if (_frame >= _spriteFrames)
			_frame = 0;
		else
			_frame += 1.0f;
		break;
	case PlayerState::STILL:
		_frame = 0;
		_velocity.x = 0;
		_velocity.y = 0;
		break;
	}

	_sprite.setTextureRect({ 0 + (int)_frame * _spriteWidth , 0, _spriteWidth, _spriteHeight });

	b2Vec2 playerPosition = _bodyJugador->GetPosition();
	float angle = _bodyJugador->GetAngle();
	_sprite.setPosition(WorldToPixel(playerPosition));
	_sprite.setOrigin(_spriteWidth / 2.0f, _spriteHeight / 2.0f);
	_sprite.setRotation(angle * 180.0f / b2_pi);
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
	if (!_texture.loadFromFile(_textRoute))
		exit(-1);
	_sprite.setTexture(_texture);
	_spriteHeight = _sprite.getGlobalBounds().getSize().y;
	_spriteWidth = _sprite.getGlobalBounds().getSize().x / _spriteFrames;
	_sprite.setTextureRect({ 0,0,_spriteWidth, _spriteHeight });
	_sprite.setOrigin(_spriteWidth / 2.0f, _spriteHeight / 2.0f);
	_sprite.setPosition(_posicion);
}

void Jugador::setPosicion(sf::Vector2f position)
{
	_posicion = position;
}

void Jugador::setControles(sf::Keyboard::Key jump, sf::Keyboard::Key moveRight, sf::Keyboard::Key moveLeft, sf::Keyboard::Key kick)
{
	_keyOfMovement.setKeyToJump(jump);
	_keyOfMovement.setKeyToMoveForward(moveRight);
	_keyOfMovement.setKeyToMoveBackward(moveLeft);
	_keyOfMovement.setKeyToKick(kick);
}

void Jugador::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(_sprite, state);
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
	return _sprite;
}

b2Body* Jugador::getBody()
{
	return _bodyJugador;
}

bool Jugador::isKicking()
{
	if (sf::Keyboard::isKeyPressed(_keyOfMovement.getKeyToKick())) {
		return true;
	}
	return false;
}

void Jugador::setPlayerID(int ID)
{
	if (ID > 0 && ID <= 2)
		_playerID = ID;
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
	_moveSpeed = velocity;
}

void Jugador::setJumpSpeed(float jumpVelocity)
{
	_jumpSpeed = jumpVelocity;
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

