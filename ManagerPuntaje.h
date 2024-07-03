#pragma once
#include "Equipo.h"
#include "ArchivoPuntaje.h"

class ManagerPuntaje
{
public:
	ManagerPuntaje();
	void listarPorPuntajeDescendente();
	void ordenarPuntajesDescendente(Puntaje puntajes[], int cantidad);
	void agregarPuntajeATabla(Equipo &equipo);
	void actualizarPuntaje(int idEquipo, int golesJug1, int golesJug2);
	void mostrarTabla(Puntaje puntajes[], int cantidad);

private:
	ArchivoPuntaje _ap;
};

