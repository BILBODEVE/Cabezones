#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <cstdlib>
#include <ctime>
#include <string>
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
#include "Torneo.h"
#include "Menu.h"
#include "ManagerEquipo.h"
#include "ManagerPartidos.h"
#include "ManagerPuntaje.h"
#include "ArchivoPartido.h"

enum class EstadoTorneo { IngresoDeCantidad, IngresoDeNombres, MuestraResultados, Juego, MuestraGanador, Finalizado };

void handleInput(sf::Event event, std::string& texto, sf::Text& usuarioE, sf::Clock& clock) {
	static std::string currentInput;
	const sf::Time debounceTime = sf::milliseconds(120);

	if (event.type == sf::Event::TextEntered) {
		if (clock.getElapsedTime() >= debounceTime) {
			if (std::isdigit(event.text.unicode)) {
				currentInput += static_cast<char>(event.text.unicode);
			}
			else if (event.text.unicode == 8 && !currentInput.empty()) { // Backspace
				currentInput.pop_back();
			}
			else if (event.text.unicode == 13) { // Enter key

				texto = currentInput;
				std::cout << texto << std::endl;
				currentInput.clear();
			}
			else if (event.text.unicode == '\b' && !texto.empty()) {
				currentInput.pop_back(); // Eliminar el último carácter si se presiona la tecla de retroceso
			}
			else if (event.text.unicode < 128 && event.text.unicode != '\b') {
				currentInput += static_cast<char>(event.text.unicode); // Agregar el carácter ingresado al string
			}
			clock.restart();
		}

		usuarioE.setString(currentInput);
	}
}

int main() {

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CABEZONES");
	window.setFramerateLimit(60);

	sf::Font fontTablas;
	if (!fontTablas.loadFromFile("recursos/Mono.ttf")) {
		std::cout << "no font";
	}

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

	sf::Text VTorneo;
	VTorneo.setString("Ingrese cantidad de jugadores: ");
	VTorneo.setFont(fontTitle);
	VTorneo.setFillColor(sf::Color::White);
	VTorneo.setCharacterSize(25);
	VTorneo.setPosition(50.0f, 200);

	sf::Text text;
	text.setString("Ingrese nombre de jugadores: ");
	text.setFont(fontTitle);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(25);
	text.setPosition(50.0f, 200);

	sf::Text entradaUsuario;
	entradaUsuario.setFont(fontTitle);
	entradaUsuario.setFillColor(sf::Color::White);
	entradaUsuario.setCharacterSize(25);
	entradaUsuario.setPosition(50.0f, 250.0f);

	sf::Text entradaUsuario2;
	entradaUsuario2.setFont(fontTitle);
	entradaUsuario2.setFillColor(sf::Color::White);
	entradaUsuario2.setCharacterSize(25);
	entradaUsuario2.setPosition(50.0f, 250);

	std::string nroDeJugadores = "";
	bool torneocreado = false;
	bool banderaTorneo = false;
	//bool banderaEquipos = false;
	//bool banderaReloj = false;
	int numJug = 0;
	std::string nombreJug;

	sf::Clock clock;
	EstadoTorneo estadoActual = EstadoTorneo::IngresoDeCantidad;

	Torneo torneo;
	ManagerPartidos _mpar;
	ManagerEquipo _me;
	ManagerPuntaje _mp;
	ArchivoPartido _ap("FixtureTorneo.fix");
	Partido part;
	Equipo a, b;
	bool banderaPartido = false;
	int nroPartido = 0;

	sf::Text textFixture;
	textFixture.setFont(fontTablas);
	textFixture.setFillColor(sf::Color::White);
	textFixture.setCharacterSize(20);
	textFixture.setPosition(5, 5);

	sf::Text textTabla;
	textTabla.setFont(fontTablas);
	textTabla.setFillColor(sf::Color::Yellow);
	textTabla.setCharacterSize(20);
	textTabla.setPosition(5, 400);

	sf::Text ganador;
	float xPos = window.getSize().x / 2;
	float yPos = 250.0f;
	ganador.setFont(fontTitle);
	ganador.setFillColor(sf::Color::White);
	ganador.setCharacterSize(45);
	ganador.setPosition(200, 100);

	sf::Text teclas;
	teclas.setString("Esc: Salir                           Siguiente->");
	teclas.setFont(fontTablas);
	teclas.setFillColor(sf::Color::Green);
	teclas.setCharacterSize(20);
	teclas.setPosition(5, 550.0f);

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

	sf::Sprite backgroudShapeControles;
	sf::Texture backgroundTextureControles;
	backgroundTextureControles.loadFromFile("Recursos/windowControles.png");
	backgroudShapeControles.setTexture(backgroundTextureControles);

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
				if (event.key.code == sf::Keyboard::Up)
				{
					menu.moveUp();
					break;
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					menu.moveBottom();
					break;
				}
				if (event.key.code == sf::Keyboard::Enter)
				{
					sf::RenderWindow playWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jugar");
					sf::RenderWindow torneoWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Torneo");
					playWindow.setFramerateLimit(60);
					torneoWindow.setFramerateLimit(60);
					if (menu.getCurrentOption() == 0)
					{
						torneoWindow.close();
						window.close();
						gameplay.reiniciarPartido();
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
						_me.eliminarEquipos();
						_mp.eliminarTabla();
						_mpar.eliminarFixture();
						playWindow.close();
						window.close();

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


								if (estadoActual == EstadoTorneo::IngresoDeCantidad) {
									handleInput(event, nroDeJugadores, entradaUsuario, clock);
									if (strcmp(nroDeJugadores.c_str(), "") != 0) {
										banderaTorneo = true;
									}
									if (banderaTorneo) {
										if (torneocreado == false) {
											numJug = std::stoi(nroDeJugadores);
											torneo.setCantidadEquipos(numJug);

											torneocreado = true;
											estadoActual = EstadoTorneo::IngresoDeNombres;
										}
									}
								}

								else if (estadoActual == EstadoTorneo::IngresoDeNombres) {
									handleInput(event, nombreJug, entradaUsuario2, clock);
									if (std::strcmp(nombreJug.c_str(), "") != 0) {
										_me.agregarEquipo(nombreJug);
										nombreJug.clear();
										entradaUsuario2.setString("");
										numJug--;
										if (numJug == 0) {
											torneo.crearFixture();
											estadoActual = EstadoTorneo::MuestraResultados;
										}
									}
								}

								else if (estadoActual == EstadoTorneo::MuestraResultados) {
									textFixture.setString(_mpar.mostrarFixture());
									_mp.listarPorPuntajeDescendente();
									textTabla.setString(_mp.mostrarTabla());


									if (event.type == sf::Event::KeyPressed) {
										if (event.key.code == sf::Keyboard::Right) {
											if (estadoActual == EstadoTorneo::MuestraResultados) {
												part = _ap.leerRegistro(nroPartido);
												if (part.getEquipoA() == 0 || part.getEquipoB() == 0) {
													part.setEjecutado(true);
													_ap.modificarRegistro(nroPartido, part);
													nroPartido++;
												}

												if (nroPartido == _mpar.getCantidadPartidos()) {
													estadoActual = EstadoTorneo::Finalizado;

												}
												else {

													estadoActual = EstadoTorneo::Juego;
													gameplay.reiniciarPartido();
												}

											}
										}
									}
								}



								else if (estadoActual == EstadoTorneo::Juego) {
									world.Step(1.0f / 60.0f, 6, 2);
									gameplay.command(world);
									//leer el fixture de partidos
									//setearle al equipoA el jugador1
									//setearle al equipoB el jugador2
									if (banderaPartido == false) {
										part = _ap.leerRegistro(nroPartido);
										a = _me.getEquipoPorID(part.getEquipoA());
										b = _me.getEquipoPorID(part.getEquipoB());


										if (part.getEjecutado() == false) {

											a.setIdJugador(1);
											b.setIdJugador(2);
											_me.modificarEquipo(a.getId(), a);
											_me.modificarEquipo(b.getId(), b);

											gameplay.setNombreJugador(a, 1);
											gameplay.setNombreJugador(b, 2);

											part.setEjecutado(true);
											_ap.modificarRegistro(nroPartido, part);
										}
										banderaPartido = true;
									}

									gameplay.update();

									if (gameplay.getTime() <= 0) {

										part.setGolesA(gameplay.getGolesJugador2());
										part.setGolesB(gameplay.getGolesJugador1());
										_ap.modificarRegistro(nroPartido, part);

										a.setGoles(gameplay.getGolesJugador2());
										b.setGoles(gameplay.getGolesJugador1());

										_me.modificarEquipo(a.getId(), a);
										_me.modificarEquipo(b.getId(), b);

										_mp.actualizarPuntaje(a.getId(), gameplay.getGolesJugador2(), gameplay.getGolesJugador1());
										_mp.actualizarPuntaje(b.getId(), gameplay.getGolesJugador2(), gameplay.getGolesJugador1());

										estadoActual = EstadoTorneo::MuestraGanador;
										banderaPartido = false;
										nroPartido++;
									}
								}

								else if (estadoActual == EstadoTorneo::MuestraGanador) {
									std::cout << "nro partido" << nroPartido << std::endl;
									ganador.setString("Ganador : \n" + _mpar.getNombreGanador(nroPartido - 1));

									if (event.type == sf::Event::KeyPressed) {
										if (event.key.code == sf::Keyboard::Right) {
											if (estadoActual == EstadoTorneo::MuestraGanador) {
												estadoActual = EstadoTorneo::MuestraResultados;

											}
										}
									}

								}
								else if (estadoActual == EstadoTorneo::Finalizado) {
									ganador.setString("Ganador Del Torneo: \n" + _mp.mostrarGanador());

									if (event.type == sf::Event::KeyPressed) {
										if (event.key.code == sf::Keyboard::Right) {
											if (estadoActual == EstadoTorneo::Finalizado) {
												torneoWindow.close();
											}
										}
									}

								}

								torneoWindow.clear();

								if (estadoActual == EstadoTorneo::IngresoDeCantidad) {
									torneoWindow.draw(VTorneo);
									torneoWindow.draw(entradaUsuario);
									torneoWindow.draw(title);

								}
								else if (estadoActual == EstadoTorneo::IngresoDeNombres) {
									torneoWindow.draw(text);
									torneoWindow.draw(entradaUsuario2);
									torneoWindow.draw(title);
								}
								else if (estadoActual == EstadoTorneo::MuestraResultados) {
									torneoWindow.draw(textFixture);
									torneoWindow.draw(textTabla);
									torneoWindow.draw(teclas);
								}
								else if (estadoActual == EstadoTorneo::Juego) {
									gameplay.draw(torneoWindow);
								}
								else if (estadoActual == EstadoTorneo::MuestraGanador) {
									torneoWindow.draw(ganador);
									torneoWindow.draw(teclas);
								}
								else if (estadoActual == EstadoTorneo::Finalizado) {
									torneoWindow.draw(ganador);
								}

								torneoWindow.display();
							}

						}

					}
					if (menu.getCurrentOption() == 2)
					{
						sf::RenderWindow windowControles(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Controles");
						windowControles.setFramerateLimit(60);
						sf::Text controles;
						controles.setString("Controles");
						controles.setFont(fontTitle);
						controles.setFillColor(sf::Color::White);
						controles.setCharacterSize(40);
						sf::FloatRect titleSize = controles.getGlobalBounds();
						controles.setOrigin(titleSize.width / 2, titleSize.height / 2);
						controles.setPosition(window.getSize().x / 2, 50.0f);
						sf::Text unJugador;
						unJugador.setFont(fontTitle);
						unJugador.setFillColor(sf::Color::Black);
						unJugador.setString("Un jugador");
						unJugador.setPosition(50.0f,100.0f);
						sf::Text dosJugadores;
						dosJugadores.setString("Dos jugadores");
						dosJugadores.setFont(fontTitle);
						dosJugadores.setFillColor(sf::Color::Black);
						dosJugadores.setString("Dos jugadores");
						dosJugadores.setPosition(50.0f, 350.0f);

						while (windowControles.isOpen())
						{
							sf::Event event;
							while (windowControles.pollEvent(event))
							{
								if (event.type == sf::Event::Closed)
								{
									windowControles.close();
								}
								if (event.type == sf::Event::KeyPressed)
								{
									if (event.key.code == sf::Keyboard::Escape)
										windowControles.close();
								}
							}
							windowControles.clear();
							windowControles.draw(backgroudShapeControles);
							windowControles.draw(controles);
							windowControles.draw(unJugador);
							windowControles.draw(dosJugadores);
							windowControles.display();
						}
					}
					if (menu.getCurrentOption() == 3)
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