#include <iomanip>
#include <sstream>
#include <iostream>
#include "ManagerPartidos.h"
#include "ManagerEquipo.h"
#include "Partido.h"
#include "ArchivoEquipo.h"

ManagerPartidos::ManagerPartidos():_ap("FixtureTorneo.fix")
{
}

const std::string ManagerPartidos::getNombreGanador(int nroPartido)
{
    Partido partido;
    ManagerEquipo me;
    
    Equipo eqA, eqB;

    partido= _ap.leerRegistro(nroPartido);
    eqA = me.getEquipoPorID(partido.getEquipoA());
    eqB = me.getEquipoPorID(partido.getEquipoB());

    if (partido.getGolesA()>partido.getGolesB()) {
        return eqA.getNombre();
    }
    else if (partido.getGolesB()>partido.getGolesA()) {
        return eqB.getNombre();
    }

    return "Empate";
}

int ManagerPartidos::getCantidadPartidos()
{
    return _ap.cantidadRegistros();
}

void ManagerPartidos::eliminarFixture()
{
    _ap.crearNuevoFixture();
}

std::string ManagerPartidos::mostrarFixture()
{
    std::ostringstream cadena;
    Partido aux;
    ArchivoEquipo _ae("Equipos.fix");
    Equipo eqA, eqB;
    int posE, cantJornadas;

    int cantR= _ap.cantidadRegistros();
    aux= _ap.leerRegistro(cantR - 1);
    cantJornadas= aux.getNroJornada();


    for (int i = 0; i < cantJornadas; i++) {
        cadena << std::left << "            JORNADA " << i+1 << std::endl;
        for (int j = 0; j < _ap.cantidadRegistros(); j++) {
            aux = _ap.leerRegistro(j);
            if (aux.getNroJornada() == (i + 1)) {
                posE= _ae.buscarPorId(aux.getEquipoA());
                
                if (posE != -1) {
                    eqA = _ae.leerRegistro(posE);
                }
                else {
                    eqA.setId(0);
                    eqA.setNombre("Descanso");
                }
                posE = _ae.buscarPorId(aux.getEquipoB());
                
                if (posE != -1) {
                    eqB = _ae.leerRegistro(posE);
                }
                else {
                    eqB.setId(0);
                    eqB.setNombre("Descanso");
                }
                cadena << std::setw(4) << std::left << aux.getGolesA()
                    << std::setw(10) << std::right << eqA.getNombre()
                    << std::setw(4) << std::left << " vs "
                    << std::setw(10) << std::left << eqB.getNombre()
                    << std::setw(4) << std::right << aux.getGolesB()<< std::endl;
            }
        }      
    }

    return cadena.str();
}
