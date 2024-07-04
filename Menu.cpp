#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
	cant = 4;
	options = new sf::Text[cant];

	if (options == NULL)
		exit(0);

	if (!font.loadFromFile("varsity_regular.ttf"))
		std::cout << "no font";

	options[0].setString("Jugar");
	options[1].setString("Torneo");
	options[2].setString("Controles");
	options[3].setString("Salir");
	setPositionOptions(height, width);
	setDefaultStyle();

	currentOption = 0;
	options[currentOption].setFillColor(sf::Color::Red);
}

void Menu::setDefaultStyle()
{
	for (int i = 0; i < cant; i++)
	{
		options[i].setFillColor(sf::Color::White);
		options[i].setFont(font);
		options[i].setCharacterSize(30);
		sf::FloatRect sizeText = options[i].getGlobalBounds();
		options[i].setOrigin(sizeText.width / 2.0f,
			sizeText.getSize().y / 2.0f);
	}
}
void Menu::setPositionOptions(float height, float width)
{
	const int WORD_SPACE = 40.0F;
	sf::Vector2f firstElement = sf::Vector2f(width / 2, height / 3.5);
	options[0].setPosition(firstElement);

	for (int i = 1; i < cant; i++)
	{
		firstElement.y += WORD_SPACE;
		options[i].setPosition(firstElement.x, firstElement.y);
	}
}

void Menu::moveUp()
{
	if (currentOption - 1 >= 0)
	{
		options[currentOption].setFillColor(sf::Color::White);
		currentOption--;
		options[currentOption].setFillColor(sf::Color::Red);
	}
}

void Menu::moveBottom()
{
	if (currentOption + 1 < cant)
	{
		options[currentOption].setFillColor(sf::Color::White);
		currentOption++;
		options[currentOption].setFillColor(sf::Color::Red);
	}
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < cant; i++)
	{
		window.draw(options[i]);
	}
}

Menu::~Menu()
{
	delete[]options;
}
