#include "Partido.h"

Partido::Partido()
{
	_equipoA = 0;
	_equipoB = 0;
	_golesA = 0;
	_golesB = 0;
	_nroJornada = 0;
	_ejecutado = false;

}

void Partido::setEquipoA(int idEquipoA)
{
	_equipoA = idEquipoA;
}

void Partido::setEquipoB(int idEquipoB)
{
	_equipoB = idEquipoB;
}

void Partido::setGolesA(int gA)
{
	_golesA = gA;
}

void Partido::setGolesB(int gB)
{
	_golesB = gB;
}

int Partido::getGolesA()
{
	return _golesA;
}

int Partido::getGolesB()
{
	return _golesB;
}

int Partido::getEquipoA()
{
	return _equipoA;
}

int Partido::getEquipoB()
{
	return _equipoB;
}

void Partido::setNroJornada(int j)
{
	_nroJornada = j;
}

int Partido::getNroJornada()
{
	return _nroJornada;
}

void Partido::setEjecutado(bool estado)
{
	_ejecutado = estado;
}

bool Partido::getEjecutado()
{
	return _ejecutado;
}
