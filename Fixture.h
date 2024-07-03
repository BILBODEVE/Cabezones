#pragma once
#include <string>
#include "Partido.h"

class Fixture
{
public:
	Fixture();
	Fixture(int cantEquipos);
	void setCantidadEquipos(int cantEquipos);
	void asignarEquipos();
	void rotarEquipos();
	void crearOrdenAleatorio(int* orden, int cant);
	int getCantidadPartidos();
	int getIdEquipoA(int indice);
	int getIdEquipoB(int indice);
	void setIdEquipoA(int indice, int idA);
	void setIdEquipoB(int indice, int idB);
	std::string toString();
	~Fixture();

private:
	Partido* _partidos;
	int _cantPartidos;
	int _cantEquipos;
	int _nroJornada;
};

