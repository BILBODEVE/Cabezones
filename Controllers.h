#pragma once
#include "SFML/Graphics.hpp"

class Controllers
{
public:
	Controllers();
	Controllers(sf::Keyboard::Key jump, sf::Keyboard::Key moveForward, sf::Keyboard::Key moveBackward, sf::Keyboard::Key kick);
	void setKeyToJump(sf::Keyboard::Key jump);
	void setKeyToMoveForward(sf::Keyboard::Key moveForward);
	void setKeyToMoveBackward(sf::Keyboard::Key moveBackward);
	void setKeyToKick(sf::Keyboard::Key kick);
	sf::Keyboard::Key getKeyToJump();
	sf::Keyboard::Key getKeyToMoveForward();
	sf::Keyboard::Key getKeyToMoveBackward();
	sf::Keyboard::Key getKeyToKick();

private:
	sf::Keyboard::Key _jump;
	sf::Keyboard::Key _moveForward;
	sf::Keyboard::Key _moveBackward;
	sf::Keyboard::Key _kick;
};

