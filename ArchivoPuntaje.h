#pragma once
#include <string>
#include "Puntaje.h"

class ArchivoPuntaje
{
public:
	ArchivoPuntaje(const std::string &nombre);
	bool crearNuevaTabla();
	bool grabarRegistro(const Puntaje &puntaje);
	Puntaje leerRegistro(int pos);
	void leerTodos(Puntaje registros[], int cantidad);
	bool modificarRegistro(Puntaje& puntaje, int posicion);
	int buscarRegistro(int nroEquipo);
	int cantidadRegistros();

private:
	char _nombre[20];
};

