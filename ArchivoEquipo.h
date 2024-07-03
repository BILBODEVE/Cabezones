#pragma once
#include <string>
#include "Equipo.h"

class ArchivoEquipo
{
public:
	ArchivoEquipo(const std::string& nombre);
	bool grabarRegistro(const Equipo &equipo);
	bool modificarRegistro(int pos, Equipo& equipo);
	Equipo leerRegistro(int pos);
	int buscarPorId(int idEquipo);
	bool borrarRegistros();
	int getCantidadRegistros();
	int getNuevoID();
private:
	char _nombre[20];
};

