#include <iostream>
#include <iomanip>
#include "ManagerPuntaje.h"
#include "ArchivoEquipo.h"

ManagerPuntaje::ManagerPuntaje():_ap("TablaDePuntajes.fix")
{
}

void ManagerPuntaje::listarPorPuntajeDescendente()
{
    int cantidad = _ap.cantidadRegistros();
    Puntaje* puntajes;
    puntajes = new Puntaje[cantidad];

    if (puntajes == nullptr) return;

    
    _ap.leerTodos(puntajes, cantidad);

   ordenarPuntajesDescendente(puntajes, cantidad);

   mostrarTabla(puntajes,cantidad);
 
    delete[] puntajes;
}

void ManagerPuntaje::ordenarPuntajesDescendente(Puntaje puntajes[], int cantidad)
{
    int i, j;
    int posMaximo;

    for (i = 0; i < cantidad - 1; i++) {
        posMaximo = i;

        for (j = i + 1; j < cantidad; j++) {
            if (puntajes[j].getPuntos() > puntajes[posMaximo].getPuntos()) {
                posMaximo = j;
            }
        }

        if (i != posMaximo) {
            Puntaje aux = puntajes[i];
            puntajes[i] = puntajes[posMaximo];
            puntajes[posMaximo] = aux;
        }
    }
}

void ManagerPuntaje::agregarPuntajeATabla(Equipo &equipo)
{
    Puntaje puntajeNuevo;
    puntajeNuevo.setIdEquipo(equipo.getId());
    _ap.grabarRegistro(puntajeNuevo);
    
}

void ManagerPuntaje::actualizarPuntaje(int idEquipo, int golesJug1, int golesJug2)
{
    ArchivoEquipo ae("Equipos.fix");
    Equipo eq;
    int posEq, GF, GC;

    posEq = ae.buscarPorId(idEquipo);
    eq = ae.leerRegistro(posEq);

    std::cout << "id" << eq.getNombre() << eq.getIdJugador() << std::endl;

    if (eq.getIdJugador() == 1) {
        GF = golesJug1;
        GC = golesJug2;
    }
    else {
        GF = golesJug2;
        GC = golesJug1;
    }

    Puntaje aux;
    for (int i = 0; i < _ap.cantidadRegistros(); i++) {
        aux = _ap.leerRegistro(i);
        if (aux.getIdEquipo() == idEquipo) {
            aux.addPartidosJugados();
            if (GF > GC) {
                aux.addGanados();
            }
            else if (GC > GF) {
                aux.addPerdidos();
            }
            else{
                aux.addEmpatados();
            }
            aux.setGolesAFavor(GF);
            aux.setGolesEnContra(GC);
            aux.setPuntos();
            if (_ap.modificarRegistro(aux, i)) {
                std::cout << "Puntaje Actualizado" << std::endl;
            }
            else {
                std::cout << "No se pudo actualizar el puntaje" << std::endl;
            }
        }
    }
}

void ManagerPuntaje::mostrarTabla(Puntaje puntajes[], int cantidad)
{
    Puntaje aux;
    Equipo eq;
    int posEq;
    ArchivoEquipo ae("Equipos.fix");

    std::cout << std::setw(3) << std::left << "P"
        << std::setw(10) << std::left << "Equipo"
        << std::setw(5) << std::left << "PJ"
        << std::setw(5) << "G" 
        << std::setw(5) << "E" 
        << std::setw(5) << "P"
        << std::setw(5) << std::left << "GF-GC"
        << std::setw(3) << ""
        << std::setw(5) << "Pts." << std::endl;

    for (int i = 0; i < cantidad; i++) {
        posEq= ae.buscarPorId(puntajes[i].getIdEquipo());
        eq= ae.leerRegistro(posEq);
        std::cout  << std::setw(3) << std::left << i+1
           << std::setw(10)  << std::left << eq.getNombre()
           << puntajes[i].toString() << std::endl;
    }
      
}


