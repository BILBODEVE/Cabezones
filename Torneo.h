#pragma once
#include "Equipo.h"
#include "Fixture.h"

class Torneo
{
public:
	Torneo();
	void setCantidadEquipos(int cantEquipos);
	void crearFixture();
	int getCantidadJornadas();
	~Torneo();

private:
	Fixture* _fixture;
	int _cantJornadas;
	int _cantEquipos;

};

