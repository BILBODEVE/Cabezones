#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Menu
{
public:
	Menu(float width, float height);
	void setDefaultStyle();
	void setPositionOptions(float width, float height);
	void moveBottom();
	void moveUp();;
	int getCurrentOption() { return currentOption; }
	void draw(sf::RenderWindow& window);
	~Menu();
	//void setOptions(int amount);
private:
	sf::Text* options;
	int cant;
	sf::Font font;
	int currentOption;
	enum optionState {
		JUGAR,
		TORNEO,
		SALIR
	};
};



