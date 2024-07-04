#include "Fixture.h"
#include "ManagerEquipo.h"

Fixture::Fixture() : _cantPartidos(0), _cantEquipos(0)
{
}

Fixture::Fixture(int cantEquipos): _cantPartidos(0), _cantEquipos(cantEquipos)
{

}


void Fixture::setCantidadEquipos(int cantEquipos)
{
	if (cantEquipos > 1) {
		if (cantEquipos % 2 == 0) {
			_cantPartidos = cantEquipos / 2;
		}
		else {
			_cantPartidos = (cantEquipos + 1) / 2;
		}	

		_partidos = new Partido[_cantPartidos];
		if (_partidos == nullptr) {
			_cantEquipos = 0;
			_cantPartidos = 0;
			return;
		}
		_cantEquipos = cantEquipos;
		
	}
	else {
		_partidos = nullptr;
		_cantPartidos = 0;
		_cantEquipos = 0;
	}
}


void Fixture::asignarEquipos()
{
	ManagerEquipo _me;
	int* vecIds = _me.getIdEquipos();

	int j=0;

	int* orden = new int[_cantEquipos];
	if (orden == nullptr) return;

	crearOrdenAleatorio(orden, _cantEquipos);

	if (_cantPartidos == _cantEquipos / 2) {
		for (int i = 0; i < _cantPartidos; i++) {
			_partidos[i].setEquipoA(vecIds[orden[j]]);
			j++;
			_partidos[i].setEquipoB(vecIds[orden[j]]);
			j++;
		}
	}
	else {//si son impares la cantidad de partidos sera uno la mitad del total de equipos
		for (int i = 0; i < _cantPartidos; i++) {
			if (j != _cantEquipos) {
				_partidos[i].setEquipoA(vecIds[orden[j]]);
				j++;
			}
			if (j != _cantEquipos) {
				_partidos[i].setEquipoB(vecIds[orden[j]]);

				j++;
			}
			if (j == _cantEquipos) {
				_partidos[i].setEquipoB(0);
			}
		}
	}

}

void Fixture::rotarEquipos()
{
	int aux = _partidos[_cantPartidos - 1].getEquipoA();

	for (int i = _cantPartidos-1; i > 0; i--) {
		_partidos[i].setEquipoA(_partidos[i - 1].getEquipoA());
	}

	_partidos[1].setEquipoA(_partidos[0].getEquipoB());

	for (int j = 0; j < _cantPartidos - 1; j++) {
		_partidos[j].setEquipoB(_partidos[j + 1].getEquipoB());
	}

	_partidos[_cantPartidos - 1].setEquipoB(aux);
}

int Fixture::getCantidadPartidos()
{
	return _cantPartidos;
}

int Fixture::getIdEquipoA(int indice)
{
	return _partidos[indice].getEquipoA();
}

int Fixture::getIdEquipoB(int indice)
{
	return _partidos[indice].getEquipoB();
}
void Fixture::setIdEquipoA(int indice, int idA) {
	_partidos[indice].setEquipoA(idA);
}
void Fixture::setIdEquipoB(int indice, int idB) {
	_partidos[indice].setEquipoB(idB);
}

void Fixture::crearOrdenAleatorio(int* orden, int cant)
{
	bool repetido = false;
	orden[0] = std::rand() % cant;

	for (int i = 1; i < cant; i++) {
		do {
			repetido = false;
			orden[i] = std::rand() % cant;

			for (int j = 0; j < i; j++) {
				if (orden[j] == orden[i]) {
					repetido = true;
					break;
				}
			}

		} while (repetido == true);
	}

}

std::string Fixture::toString()
{
	std::string aux;
	aux += "\n";
	aux += "Equipos A vs. Equipos B\n";

	for (int i = 0; i < _cantPartidos; i++) {
		aux += _partidos[i].getEquipoA() + " vs " + _partidos[i].getEquipoB();
		aux+= " \n";
	}

	return aux;
}

Fixture::~Fixture()
{
	if (_cantEquipos != 0) {
		delete[] _partidos;
	}
}
