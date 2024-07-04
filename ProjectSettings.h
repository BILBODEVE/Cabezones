#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


/// Configuracioon ventana
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

/// Configuracion mundo
const float GRAVITY_X = 0.0f;
const float GRAVITY_Y = 9.8f;

/// RUTAS SPRITES
const std::string spritesheetplayerRaul = "Recursos/sprites-players/sprite-player-raul.png";
const std::string spritesheetplayerCarlos = "Recursos/sprites-players/sprite-player-carlos.png";
const std::string spritesheetplayerClara = "Recursos/sprites-players/sprite-player-clara.png";
const std::string spritesheetplayerFacundo = "Recursos/sprites-players/sprite-player-facundo.png";
const std::string spritesheetplayerJorge = "Recursos/sprites-players/sprite-player-jorge.png";
const std::string spritesheetplayerJuan = "Recursos/sprites-players/sprite-player-juan.png";
const std::string spritesheetplayerSoledad = "Recursos/sprites-players/sprite-player-soledad.png";

/// Configuraciones arco
const sf::Vector2f sizeArco = sf::Vector2f(80, 220);
const sf::Vector2f posicionArco1 = sf::Vector2f(40, 375);
const sf::Vector2f posicionArco2 = sf::Vector2f(WINDOW_WIDTH - sizeArco.x / 2, 375);

const enum Entity_type {
	ARCO,
	PELOTA,
	JUGADOR,
	OBSTACULO,
};
