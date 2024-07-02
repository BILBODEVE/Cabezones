#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <cstdlib>
#include <ctime>
#include "CampoDeJuego.h"
#include "Suelo.h"
#include "Arco.h"
#include "Pelota.h"
#include "Limite.h"
#include "Jugador.h"
#include "ProjectSettings.h"
#include "Controllers.h"
#include "MyContactListener.h"
#include "Hielo.h"
#include "Bomba.h"
#include "Aumentador.h"
#include "Gameplay.h"
#include "Menu.h"

int main() {

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CABEZONES");
	window.setFramerateLimit(60);

	sf::Text title;
	sf::Font fontTitle;
	if (!fontTitle.loadFromFile("varsity_regular.ttf"))
		std::cout << "no font";
	title.setString("Cabezones");
	title.setFont(fontTitle);
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(55);
	sf::FloatRect titleSize = title.getGlobalBounds();
	title.setOrigin(titleSize.width / 2, titleSize.height / 2);
	title.setPosition(window.getSize().x / 2, 100.0f);

	Menu menu(window.getSize().x, window.getSize().y);

	sf::Sprite backgroudShape;
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("Recursos/background-menu3.png"))
		std::cout << "no hay imagen";
	backgroudShape.setTexture(backgroundTexture);

	sf::Vector2u windowSize = window.getSize();
	sf::Vector2u textureSize = backgroundTexture.getSize();

	float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
	float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

	backgroudShape.setScale(scaleX, scaleY);

	b2Vec2 gravity(GRAVITY_X, GRAVITY_Y);
	b2World world(gravity);
	Gameplay gameplay(world, window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					menu.moveUp();
					break;
				}
				else if (event.key.code == sf::Keyboard::S)
				{
					menu.moveBottom();
					break;
				}
				if (event.key.code == sf::Keyboard::Enter)
				{
					sf::RenderWindow playWindow(sf::VideoMode(800, 600), "Jugar");
					sf::RenderWindow torneoWindow(sf::VideoMode(800, 600), "Torneo");
					playWindow.setFramerateLimit(60);
					torneoWindow.setFramerateLimit(60);

					if (menu.getCurrentOption() == 0)
					{
						torneoWindow.close();
						window.close();
						while (playWindow.isOpen())
						{
							sf::Event event;
							while (playWindow.pollEvent(event))
							{
								if (event.type == sf::Event::Closed)
								{
									playWindow.close();
								}
								if (event.type == sf::Event::KeyPressed)
								{
									if (event.key.code == sf::Keyboard::Escape)
										playWindow.close();
								}
							}

							world.Step(1.0f / 60.0f, 6, 2);
							gameplay.command(world);
							gameplay.update();

							playWindow.clear();
							gameplay.draw(playWindow);
							playWindow.display();
						}
					}

					if (menu.getCurrentOption() == 1)
					{
						playWindow.close();
						while (torneoWindow.isOpen())
						{
							sf::Event event;
							while (torneoWindow.pollEvent(event))
							{
								if (event.type == sf::Event::Closed)
								{
									torneoWindow.close();
								}
								if (event.type == sf::Event::KeyPressed)
								{
									if (event.key.code == sf::Keyboard::Escape)
										torneoWindow.close();
								}
							}
							torneoWindow.clear();
							torneoWindow.draw(title);
							torneoWindow.display();
						}
					}
					if (menu.getCurrentOption() == 2)
					{
						window.close();
					}
				}
			}
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
		}

		window.clear();
		window.draw(backgroudShape);
		window.draw(title);
		menu.draw(window);
		window.display();
	}
	return 0;

}