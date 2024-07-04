#pragma once
#include "Equipo.h"
#include "ArchivoPuntaje.h"

class ManagerPuntaje
{
public:
	ManagerPuntaje();
	Puntaje* listarPorPuntajeDescendente();
	int getCantidad();
	void ordenarPuntajesDescendente();
	void agregarPuntajeATabla(Equipo &equipo);
	void actualizarPuntaje(int idEquipo, int golesJug1, int golesJug2);
	void eliminarTabla();
	std::string mostrarTabla();
	std::string mostrarGanador();
	~ManagerPuntaje();

private:
	ArchivoPuntaje _ap;
	Puntaje* _puntajes;
	int _cantidad;
};

