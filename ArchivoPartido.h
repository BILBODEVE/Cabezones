#pragma once
#include <string>
#include "Partido.h"
class ArchivoPartido
{
public:
	ArchivoPartido(const std::string& nombre);
	bool grabarRegistro(const Partido& partido);
	bool modificarRegistro(int pos, const Partido& partido);
	bool crearNuevoFixture();
	Partido leerRegistro(int pos);
	int cantidadRegistros();

private:
	char _nombre[20];
};


