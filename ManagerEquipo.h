#pragma once
#include "ArchivoEquipo.h"

class ManagerEquipo
{
public:
	ManagerEquipo();
	void agregarEquipo(std::string nombreEquipo);
	void eliminarEquipos();
	void modificarEquipo(int id, Equipo& equipo);
	Equipo getEquipoPorID(int id);
	int* getIdEquipos();
	
private:
	ArchivoEquipo _ae;
};

