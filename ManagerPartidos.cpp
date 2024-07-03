#include <iomanip>
#include <iostream>
#include "ManagerPartidos.h"
#include "Partido.h"
#include "ArchivoEquipo.h"

ManagerPartidos::ManagerPartidos():_ap("FixtureTorneo.fix")
{
}

void ManagerPartidos::mostrarFixture(int cantJorndas)
{
    Partido aux;
    ArchivoEquipo _ae("Equipos.fix");
    Equipo eqA, eqB;
    int posE;

    for (int i = 0; i < cantJorndas; i++) {
        std::cout << "            JORNADA " << i+1 << std::endl;
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
                std::cout << std::setw(4) << std::left << aux.getGolesA()
                    << std::setw(10) << std::right << eqA.getNombre()
                    << std::setw(4) << std::left << " vs "
                    << std::setw(10) << std::left << eqB.getNombre()
                    << std::setw(4) << std::right << aux.getGolesB()<<std::endl;
            }
        }      
    }
}
