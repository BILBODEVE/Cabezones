#pragma once
#include <string>
#include "Puntaje.h"

class Equipo
{
public:
	Equipo();
	Equipo(std::string nombre);
	void setNombre(const std::string &nombre);
	const char* getNombre();
	void setIdJugador(int idJugador);
	int getIdJugador();
	void setId(int id);
	int getId();
	void setGoles(int goles);
	int getGoles();
	void setPuntaje(Puntaje puntaje);
	std::string toString();

private:
	char _nombre[20];
	int _idJugador;
	int _id;
	int _goles;
	Puntaje _puntaje;

};

