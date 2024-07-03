#include <iostream>
#include <string>
#include "ManagerEquipo.h"
#include "ManagerPuntaje.h"
#include "Equipo.h"

ManagerEquipo::ManagerEquipo(): _ae("Equipos.fix")
{
}

void ManagerEquipo::agregarEquipo()
{
	ManagerPuntaje _mp;
	Equipo aux;
	std::string nombreEquipo;
	std::cout << "Ingrese nombre del Equipo o Jugador: ";
	std::cin >> nombreEquipo;
	aux.setNombre(nombreEquipo);
	int id = _ae.getNuevoID();
	aux.setId(id);
	if (_ae.grabarRegistro(aux)) {
		_mp.agregarPuntajeATabla(aux);
		std::cout << "Equipo agregado correctamente" << std::endl;
	}
	else {
		std::cout << "No se pudo agregar el Equipo " << std::endl;
	}
}

void ManagerEquipo::eliminarEquipos()
{
	if (_ae.borrarRegistros()) {
		std::cout << "Equipos eliminados" << std::endl;
	}
}

int* ManagerEquipo::getIdEquipos()
{
	Equipo aux;
	int cant= _ae.getCantidadRegistros();
	if (cant == 0) return 0;

	int* ids = new int[cant];

	if (ids == nullptr) return nullptr;

	for (int i = 0; i < cant; i++) {
		aux = _ae.leerRegistro(i);
		ids[i] = aux.getId();
	}

	return ids;
}
