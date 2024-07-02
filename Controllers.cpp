#include "Controllers.h"

Controllers::Controllers() {}

Controllers::Controllers(sf::Keyboard::Key jump, sf::Keyboard::Key moveRight, sf::Keyboard::Key moveLeft, sf::Keyboard::Key kick)
{
	setKeyToJump(jump);
	setKeyToMoveForward(moveRight);
	setKeyToMoveBackward(moveLeft);
	setKeyToKick(kick);
}

void Controllers::setKeyToJump(sf::Keyboard::Key jump)
{
	_jump = jump;
}

void Controllers::setKeyToMoveForward(sf::Keyboard::Key moveRight)
{
	_moveForward = moveRight;
}

void Controllers::setKeyToMoveBackward(sf::Keyboard::Key moveLeft)
{
	_moveBackward = moveLeft;
}

void Controllers::setKeyToKick(sf::Keyboard::Key kick)
{
	_kick = kick;
}

sf::Keyboard::Key Controllers::getKeyToJump()
{
	return _jump;
}

sf::Keyboard::Key Controllers::getKeyToMoveForward()
{
	return _moveForward;
}

sf::Keyboard::Key Controllers::getKeyToMoveBackward()
{
	return _moveBackward;
}

sf::Keyboard::Key Controllers::getKeyToKick()
{
	return _kick;
}
