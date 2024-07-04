#include "Equipo.h"
#include <cstring>

Equipo::Equipo():_idJugador(0), _id(0), _goles(0), _puntaje()
{
	std::strcpy(_nombre, "Descanso");
}

Equipo::Equipo(std::string nombre):_idJugador(0), _id(0), _goles(0), _puntaje()
{
	std::strcpy(_nombre, nombre.c_str());

}

void Equipo::setNombre(const std::string &nombre)
{
	std::strcpy(_nombre, nombre.c_str());
}

const char* Equipo::getNombre()
{
	return _nombre;
}

void Equipo::setIdJugador(int idJugador)
{
	_idJugador = idJugador;
}

int Equipo::getIdJugador()
{
	return _idJugador;
}

void Equipo::setId(int id)
{
	_id = id;
}

int Equipo::getId()
{
	return _id;
}

void Equipo::setGoles(int goles)
{
	_goles += goles;
}

int Equipo::getGoles()
{
	return _goles;
}

void Equipo::setPuntaje(Puntaje puntaje)
{
	_puntaje = puntaje;
}

std::string Equipo::toString()
{
	std::string aux = _nombre;
	return aux;
}



