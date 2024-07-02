#include "Gameplay.h"

Gameplay::Gameplay(b2World& world, sf::RenderWindow& window) : _campo(world), _hielo(world), _bomba(world), _aumentador(world)
{
	if (!_fuente.loadFromFile("Recursos/cronometroFuente.ttf"))
		exit(-1);
	_textoCronometro.setFont(_fuente);
	_textoCronometro.setFillColor(sf::Color::White);
	_textoCronometro.setCharacterSize(45);
	_textoCronometro.setPosition(400, 530);
	_tiempoInicial = 60;
	_tiempoRestante = 0;

	_resultado.setCharacterSize(45);
	_resultado.setFillColor(sf::Color::White);
	_resultado.setPosition(400, 530);
	_resultado.setFont(_fuente);
	std::string res;

	_marcadorTexture.loadFromFile("Recursos/marcador.png");
	_marcadorSprite.setTexture(_marcadorTexture);
	_marcadorSprite.setPosition(400, 490);
	_marcadorSprite.setOrigin(_marcadorSprite.getGlobalBounds().getSize().x / 2, 0);

	_cartelGolTexture.loadFromFile("Recursos/gol.png");
	_cartelGolSprite.setTexture(_cartelGolTexture);
	_cartelGolSprite.setOrigin(_cartelGolSprite.getGlobalBounds().getSize().x / 2, _cartelGolSprite.getGlobalBounds().getSize().y / 2);
	_cartelGolSprite.setPosition(400, 200);

	_limite.setShapeLimite(sf::Vector2f(window.getSize().x, 0), sf::Vector2f(0, 0), sf::Vector2f(0, 800), sf::Vector2f(window.getSize().x, 800));
	_limite.setBodyLimite(world);

	_suelo.setBodySuelo(world, sf::Vector2f(400, 535));
	_suelo.setShapeSuelo(sf::Vector2f(800, 130), sf::Vector2f(400, 535));

	_pelota.setRadius(20);
	_pelota.setBodyPelota(world, sf::Vector2f(400, 25));
	_pelota.setShapePelota(sf::Vector2f(400, 25));

	_arcoPlayer1.setID(1);
	_arcoPlayer2.setID(2);

	float radioPelota = _pelota.getRadius();

	if (_arcoPlayer1.getID() == 1)
	{
		_arcoPlayer1.setPosicionSensor(sf::Vector2f(40 - (radioPelota / 2), 375));
	}
	if (_arcoPlayer2.getID() == 2)
	{
		_arcoPlayer2.setPosicionSensor(sf::Vector2f((window.getSize().x - 40) + (radioPelota / 2), 375));
	}

	_arcoPlayer1.setShapeArco(sf::Vector2f(40, 375), sf::Vector2f(80, 220));
	_arcoPlayer1.setBodyArco(world, sf::Vector2f(40, 375), sf::Vector2f(80, 220));
	_arcoPlayer2.setShapeArco(sf::Vector2f(window.getSize().x - (sizeArco.x / 2), 375), sf::Vector2f(80, 220));
	_arcoPlayer2.setBodyArco(world, sf::Vector2f(window.getSize().x - (sizeArco.x / 2), 375), sf::Vector2f(80, 220));

	_player1.setPlayerID(1);
	_player1.setPosicion(sf::Vector2f(80 + 80 / 2, 429));
	_player1.createSprite(spritesheetplayerRaul);
	_player1.createBodyPlayer(world);
	_player1.setControles(sf::Keyboard::Key::W, sf::Keyboard::Key::D, sf::Keyboard::Key::A, sf::Keyboard::Key::Space);

	_player2.setPlayerID(2);
	_player2.setPosicion(sf::Vector2f(window.getSize().x - sizeArco.x - (80 / 2), 429));
	_player2.createSprite(spritesheetplayerJuan);
	_player2.createBodyPlayer(world);
	_player2.setControles(sf::Keyboard::Key::I, sf::Keyboard::Key::L, sf::Keyboard::Key::J, sf::Keyboard::Key::M);
	_player2.getSprite().setScale(-1, 1);

	_hielo.setUltimaAparicion(_hielo.GenerarSiguienteIntervalo());

	_hieloJ1 = false;
	_hieloJ2 = false;

	_bomba.setUltimaAparicion(_bomba.GenerarSiguienteIntervalo());
	_bombaJ1 = false;
	_bombaJ2 = false;


	_aumentador.setUltimaAparicion(_aumentador.GenerarSiguienteIntervalo());
	_aumentadorJ1 = false;
	_aumentadorJ2 = false;
	_aumentadoJ1 = false;
	_aumentadoJ2 = false;

	_golJ1 = false;
	_golJ2 = false;
	
	managerColisiones.createContact(_pelota, _arcoPlayer1, _arcoPlayer2, _player1, _player2, _golJ1, _golJ2, _delay, _hielo, _hieloClock1, _hieloClock2, _hieloJ1, _hieloJ2, _bomba, _bombaClock1, _bombaClock2, _bombaJ1, _bombaJ2, _aumentador, _aumentadorClock1, _aumentadorClock2, _aumentadorJ1, _aumentadorJ2);
	world.SetContactListener(&managerColisiones);
}

void Gameplay::draw(sf::RenderWindow& window)
{
	window.draw(_campo);
	window.draw(_suelo);
	window.draw(_pelota);
	window.draw(_player1);
	window.draw(_player2);

	if (_hielo.getBody() != nullptr) {
		window.draw(_hielo);
	}
	if (_bomba.getBody() != nullptr) {
		window.draw(_bomba);
	}
	if (_aumentador.getBody() != nullptr) {
		window.draw(_aumentador);
	}

	window.draw(_arcoPlayer1);
	window.draw(_arcoPlayer2);
	window.draw(_marcadorSprite);
	window.draw(_textoCronometro);
	if (_golJ1 == true || _golJ2 == true) {
		window.draw(_cartelGolSprite);
	}
	window.draw(_resultado);
}

void Gameplay::command(b2World& world)
{
	cronometro = _clock.getElapsedTime();
	int seconds = static_cast<int>(cronometro.asSeconds());
	_tiempoRestante = _tiempoInicial - seconds;
	_player1.command();
	_player2.command();

	if (_tiempoRestante <= 0) {
		_clock.restart();
		seconds = 0;
	}

	if (_tiempoRestante < 10) {
		_textoCronometro.setString("00:0" + std::to_string(_tiempoRestante));
	}
	else if (_tiempoRestante == 60) {
		_textoCronometro.setString("01:00");
	}
	else {
		_textoCronometro.setString("00:" + std::to_string(_tiempoRestante));
	}

	if (_tiempoRestante == 0) {
		_aumentador.setUltimaAparicion(_aumentador.GenerarSiguienteIntervalo());
		_bomba.setUltimaAparicion(_bomba.GenerarSiguienteIntervalo());
		_hielo.setUltimaAparicion(_hielo.GenerarSiguienteIntervalo());

	}

	_textoCronometro.setOrigin(sf::Vector2f(_textoCronometro.getGlobalBounds().width / 2, 0));

	if (_delay.getElapsedTime().asSeconds() > 1) {
		if (_golJ1 == true) {
			_player1.addGol();
			_player1.setPosicionInicial(1);
			_player2.setPosicionInicial(2);
			_pelota.setPosition(sf::Vector2f(400, 25));
			_golJ1 = false;
		}

		if (_golJ2 == true) {
			_player2.addGol();
			_player1.setPosicionInicial(1);
			_player2.setPosicionInicial(2);
			_pelota.setPosition(sf::Vector2f(400, 25));
			_golJ2 = false;
		}
	}

	if (_clock.getElapsedTime().asSeconds() >= _hielo.getUltimaAparicion()) {
		if (_hielo.getBody() != nullptr) {
			_hielo.Destroy();
		}
		_hielo.Aparecer(world);
		_tiempoTranscurrido = _clock.getElapsedTime();
		_hielo.setUltimaAparicion(static_cast<int>(_tiempoTranscurrido.asSeconds() + _hielo.GenerarSiguienteIntervalo()));
	}

	if (_clock.getElapsedTime().asSeconds() >= _bomba.getUltimaAparicion()) {
		if (_bomba.getBody() != nullptr) {
			_bomba.Destroy();
		}
		_bomba.Aparecer(world);
		_tiempoTranscurrido = _clock.getElapsedTime();
		_bomba.setUltimaAparicion(static_cast<int>(_tiempoTranscurrido.asSeconds() + _bomba.GenerarSiguienteIntervalo()));
	}

	if (_clock.getElapsedTime().asSeconds() >= _aumentador.getUltimaAparicion()) {
		if (_aumentador.getBody() != nullptr) {
			_aumentador.Destroy();
		}

		_aumentador.Aparecer(world);
		_tiempoTranscurrido = _clock.getElapsedTime();
		_aumentador.setUltimaAparicion(static_cast<int>(_tiempoTranscurrido.asSeconds() + _aumentador.GenerarSiguienteIntervalo()));
	}

	if (_hieloJ1 == true) {
		if (_hielo.getBody() != nullptr) {
			_hielo.Destroy();
		}
		_tiempoCongelado = _hieloClock1.getElapsedTime();
		if (_tiempoCongelado.asSeconds() <= 1.5) {
			_player1.getBody()->SetType(b2_staticBody);
		}
		else {
			_player1.getBody()->SetType(b2_dynamicBody);
			_hieloJ1 = false;
		}
	}

	if (_hieloJ2 == true) {
		if (_hielo.getBody() != nullptr) {
			_hielo.Destroy();
		}
		_tiempoCongelado = _hieloClock2.getElapsedTime();
		if (_tiempoCongelado.asSeconds() <= 1.5) {
			_player2.getBody()->SetType(b2_staticBody);
		}
		else {
			_player2.getBody()->SetType(b2_dynamicBody);
			_hieloJ2 = false;
		}
	}

	if (_bombaJ1 == true) {
		if (_bomba.getBody() != nullptr) {
			_bomba.Destroy();
		}
		_tiempoBomba = _bombaClock1.getElapsedTime();
		if (_tiempoBomba.asSeconds() <= 3) {
			_player1.setJumpSpeed(100);
			_player1.setMoveSpeed(100);
		}
		else {
			_player1.setJumpSpeed(250);
			_player1.setMoveSpeed(250);
			_bombaJ1 = false;
		}
	}

	if (_bombaJ2 == true) {
		if (_bomba.getBody() != nullptr) {
			_bomba.Destroy();
		}
		_tiempoBomba = _bombaClock2.getElapsedTime();
		if (_tiempoBomba.asSeconds() <= 3) {
			_player2.setJumpSpeed(100);
			_player2.setMoveSpeed(100);
		}
		else {
			_player2.setJumpSpeed(250);
			_player2.setMoveSpeed(250);
			_bombaJ2 = false;
		}
	}

	if (_aumentadorJ1 == true) {
		if (_aumentador.getBody() != nullptr) {
			_aumentador.Destroy();
		}
		//j1.crearJugador(true);
		_player1.getSprite().setScale(1.5, 1.5);
		_aumentadoJ1 = true;
		_aumentadorJ1 = false;

	}
	if (_aumentadorJ2 == true) {
		if (_aumentador.getBody() != nullptr) {
			_aumentador.Destroy();
		}

		//j2.crearJugador(true);
		_player2.getSprite().setScale(-1.5, 1.5);
		_aumentadoJ2 = true;
		_aumentadorJ2 = false;
	}

	tiempoAumentador = _aumentadorClock1.getElapsedTime();
	if (tiempoAumentador.asSeconds() >= 4 && _aumentadoJ1) {
		//j1.crearJugador();
		_player1.getSprite().setScale(1, 1);
		_aumentadoJ1 = false;
	}

	tiempoAumentador = _aumentadorClock2.getElapsedTime();
	if (tiempoAumentador.asSeconds() >= 4 && _aumentadoJ2) {
		//j2.crearJugador();
		_player2.getSprite().setScale(-1, 1);
		_aumentadoJ2 = false;
	}

	std::string res;
	res = std::to_string(_player2.getGoles()) + "                       " + std::to_string(_player1.getGoles());
	_resultado.setString(res);
	_resultado.setOrigin(sf::Vector2f(_resultado.getGlobalBounds().width / 2, 0));

	_player1.setJumpSpeed(450);
	_player1.setMoveSpeed(250);
	_player2.setJumpSpeed(450);
	_player2.setMoveSpeed(250);
}

void Gameplay::update()
{
	_hielo.update();
	_bomba.update();
	_aumentador.update();
	_pelota.update();
	_player1.update();
	_player2.update();
}
