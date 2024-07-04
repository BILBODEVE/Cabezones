#include "Puntaje.h"
#include "ArchivoEquipo.h"
#include <iomanip>
#include <sstream>

Puntaje::Puntaje():_partidosJugados(0), _ganados(0), _empatados(0), _perdidos(0), _golesAFavor(0), _golesEnContra(0), _puntos(0)
{
}

int Puntaje::getIdEquipo()
{
	return _idEquipo;
}

int Puntaje::getPartidosJugados()
{
	return _partidosJugados;
}

int Puntaje::getGanados()
{
	return _ganados;
}

int Puntaje::getEmpatados()
{
	return _empatados;
}

int Puntaje::getPerdidos()
{
	return _perdidos;
}

int Puntaje::getGolesAFavor()
{
	return _golesAFavor;
}

int Puntaje::getGolesEnContra()
{
	return _golesEnContra;
}

int Puntaje::getPuntos()
{
	return _puntos;
}

void Puntaje::setIdEquipo(int idEquipo)
{
	_idEquipo = idEquipo;
}

void Puntaje::addPartidosJugados()
{
	_partidosJugados++;
}

void Puntaje::addGanados()
{
	_ganados++;
}

void Puntaje::addEmpatados()
{
	_empatados++;
}

void Puntaje::addPerdidos()
{
	_perdidos++;
}

void Puntaje::setGolesAFavor(int golesAFavor)
{
	_golesAFavor += golesAFavor;
}

void Puntaje::setGolesEnContra(int golesEnContra)
{
	_golesEnContra += golesEnContra;
}

void Puntaje::setPuntos()
{
	_puntos = _ganados * 3 + _empatados * 1;
}

std::string Puntaje::toString()
{
	std::ostringstream aux;
	aux << std::setw(5) << std::left << std::to_string(_partidosJugados)
		<< std::setw(5) << std::left << std::to_string(_ganados)
		<< std::setw(5) << std::left << std::to_string(_empatados)
		<< std::setw(5) << std::left << std::to_string(_perdidos)
		<< std::setw(2) << std::right << std::to_string(_golesAFavor) << "-"
		<< std::setw(5) << std::left << std::to_string(_golesEnContra)
		<< std::setw(5) << std::left << std::to_string(_puntos);
	return aux.str();
}


