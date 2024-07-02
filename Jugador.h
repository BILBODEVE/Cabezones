#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "ProjectSettings.h"
#include "Entity.h"
#include "Controllers.h"

class Jugador : public sf::Drawable
{
public:
	Jugador();
	Jugador(b2World& world, std::string textureRoute, sf::Vector2f position, int id, sf::Keyboard::Key jump, sf::Keyboard::Key moveRight, sf::Keyboard::Key moveLeft, sf::Keyboard::Key kick);
	void setPlayerID(int ID);
	void createBodyPlayer(b2World& world);
	void createSprite(std::string textureRoute);
	void setPosicion(sf::Vector2f position);
	void setControles(sf::Keyboard::Key jump, sf::Keyboard::Key moveRight, sf::Keyboard::Key moveLeft, sf::Keyboard::Key kick);
	void setPosicionInicial(int id);
	void setMoveSpeed(float velocity);
	void setJumpSpeed(float jumpVelocity);
	sf::Sprite& getSprite();
	b2Body* getBody();
	bool isKicking();
	void command();
	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	void addGol();
	int getGoles();
	
private:
	b2Body* _bodyJugador;
	b2BodyDef _playerBody;
	b2PolygonShape _shape;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f velocity;
	Controllers keyOfMovement;
	float moveSpeed;
	float jumpSpeed;
	float frame;
	enum PlayerState {
		STILL,
		RUNNING_FORWARD,
		RUNNING_BACKWARD,
		JUMPING,
		KICKING
	};
	PlayerState move;
	PlayerState state;
	int playerID;
	int _goles;
	std::string _textRoute;
	sf::Vector2f _posicion;
	int _spriteFrames;
	int _spriteHeight;
	int _spriteWidth;
};

