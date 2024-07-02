#pragma once
#include <iostream>
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "Limite.h"
#include  "Suelo.h"
#include "CampoDeJuego.h"
#include "Pelota.h"
#include "Arco.h"
#include "Jugador.h"
#include "Hielo.h"
#include "Aumentador.h"
#include "Bomba.h"
#include "MyContactListener.h"

class Gameplay: public Suelo, public Limite, public CampoDeJuego
{
public:
	Gameplay(b2World& world, sf::RenderWindow& window);
	void command(b2World& world);
	void update();
	void draw(sf::RenderWindow& window);

private:
	Limite _limite;
	Suelo _suelo;
	CampoDeJuego _campo;
	Pelota _pelota;
	Arco _arcoPlayer1;
	Arco _arcoPlayer2;
	Jugador _player1;
	Jugador _player2;
	bool _golJ1;
	bool _golJ2;

	Hielo _hielo;
	sf::Time _tiempoCongelado;
	sf::Clock _hieloClock1;
	sf::Clock _hieloClock2;
	bool _hieloJ1;
	bool _hieloJ2;
	Bomba _bomba;
	sf::Time _tiempoBomba;
	sf::Clock _bombaClock1;
	sf::Clock _bombaClock2;
	bool _bombaJ1;
	bool _bombaJ2;
	Aumentador _aumentador;
	sf::Time tiempoAumentador;
	sf::Clock _aumentadorClock1;
	sf::Clock _aumentadorClock2;
	bool _aumentadorJ1;
	bool _aumentadorJ2;
	bool _aumentadoJ1;
	bool _aumentadoJ2;

	sf::Clock _delay;
	sf::Clock _clock;
	sf::Time cronometro;
	int _tiempoInicial;
	int _tiempoRestante;
	sf::Time _tiempoTranscurrido;

	sf::Font _fuente;
	sf::Text _textoCronometro;
	sf::Text _resultado;
	sf::Texture _marcadorTexture;
	sf::Sprite _marcadorSprite;
	sf::Texture _cartelGolTexture;
	sf::Sprite _cartelGolSprite;

	MyContactListener managerColisiones;
};

