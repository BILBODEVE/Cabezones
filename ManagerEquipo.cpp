#include <iostream>
#include <string>
#include "ManagerEquipo.h"
#include "ManagerPuntaje.h"
#include "Equipo.h"

ManagerEquipo::ManagerEquipo(): _ae("Equipos.fix")
{
}

void ManagerEquipo::agregarEquipo(std::string nombreEquipo)
{
	ManagerPuntaje _mp;
	Equipo aux;
	
	//std::cout << "Ingrese nombre del Equipo o Jugador: ";
	//std::cin >> nombreEquipo;
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

void ManagerEquipo::modificarEquipo(int idEquipo, Equipo& equipo)
{
	int pos = _ae.buscarPorId(idEquipo);
	_ae.modificarRegistro(pos, equipo);
}

Equipo ManagerEquipo::getEquipoPorID(int id)
{
	Equipo aux;
	int pos= _ae.buscarPorId(id);
	aux= _ae.leerRegistro(pos);
	return aux;
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
