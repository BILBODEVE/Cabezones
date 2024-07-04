#include "Torneo.h"
#include "ArchivoPartido.h"
#include "Partido.h"
#include <iostream>

Torneo::Torneo(): _fixture(nullptr), _cantJornadas(0), _cantEquipos(0)
{
}

void Torneo::setCantidadEquipos(int cantEquipos)
{
	if (cantEquipos > 1) {
		if (cantEquipos % 2 == 0) {
			_cantJornadas = cantEquipos - 1;
		}
		else {
			_cantJornadas = cantEquipos;
		}
		_fixture = new Fixture[_cantJornadas];

		if (_fixture == nullptr) {
			_cantJornadas = 0;
			exit(-5);
		}
		_cantEquipos = cantEquipos;

	}
	else {
		_fixture = nullptr;
		_cantJornadas = 0;
		_cantEquipos = 0;
	}

}

Torneo::~Torneo()
{
	if (_cantJornadas != 0) {
		delete[] _fixture;
	}
}

void Torneo::crearFixture()
{
	Partido aux;
	Partido part;
	ArchivoPartido ap("FixtureTorneo.fix");
	
	for (int j = 0; j < _cantJornadas; j++) {
		_fixture[j].setCantidadEquipos(_cantEquipos);
	}

	_fixture[0].asignarEquipos();

	//guardar Equipos de Jornada1
	for (int x = 0; x < _fixture[0].getCantidadPartidos(); x++) {
		aux.setEquipoA(_fixture[0].getIdEquipoA(x));
		aux.setEquipoB(_fixture[0].getIdEquipoB(x));
		aux.setNroJornada(1);
		ap.grabarRegistro(aux);
	}

	for(int k=1; k<_cantJornadas; k++){
		for (int i = 0; i < _fixture[k].getCantidadPartidos(); i++) {
			int na = _fixture[k-1].getIdEquipoA(i);
			int nb = _fixture[k-1].getIdEquipoB(i);
			_fixture[k].setIdEquipoA(i, na);
			_fixture[k].setIdEquipoB(i, nb);
		}
		_fixture[k].rotarEquipos();
		for (int y = 0; y < _fixture[k].getCantidadPartidos(); y++) {
			aux.setEquipoA(_fixture[k].getIdEquipoA(y));
			aux.setEquipoB(_fixture[k].getIdEquipoB(y));
			aux.setNroJornada(k+1);
			ap.grabarRegistro(aux);
		}
	}
	
}


int Torneo::getCantidadJornadas()
{
	return _cantJornadas;
}



