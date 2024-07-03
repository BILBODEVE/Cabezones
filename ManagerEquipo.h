#pragma once
#include "ArchivoEquipo.h"

class ManagerEquipo
{
public:
	ManagerEquipo();
	void agregarEquipo();
	void eliminarEquipos();
	int* getIdEquipos();
	
private:
	ArchivoEquipo _ae;
};

