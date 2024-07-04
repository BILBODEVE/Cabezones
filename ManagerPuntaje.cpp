#include <iostream>
#include <iomanip>
#include <sstream>
#include "ManagerPuntaje.h"
#include "ArchivoEquipo.h"
#include "ManagerEquipo.h"

ManagerPuntaje::ManagerPuntaje():_ap("TablaDePuntajes.fix"), _puntajes(nullptr), _cantidad(0)
{
}

Puntaje* ManagerPuntaje::listarPorPuntajeDescendente()
{
    _cantidad = _ap.cantidadRegistros();
  
    _puntajes = new Puntaje[_cantidad];

    if (_puntajes == nullptr) return nullptr;
            
    _ap.leerTodos(_puntajes, _cantidad);

   ordenarPuntajesDescendente();

   //mostrarTabla(puntajes,cantidad);
 
    return _puntajes;
}

int ManagerPuntaje::getCantidad()
{
    return _cantidad;
}

void ManagerPuntaje::ordenarPuntajesDescendente()
{
    int i, j;
    int posMaximo;

    for (i = 0; i < _cantidad - 1; i++) {
        posMaximo = i;

        for (j = i + 1; j < _cantidad; j++) {
            if (_puntajes[j].getPuntos() > _puntajes[posMaximo].getPuntos()) {
                posMaximo = j;
            }
        }

        if (i != posMaximo) {
            Puntaje aux = _puntajes[i];
            _puntajes[i] = _puntajes[posMaximo];
            _puntajes[posMaximo] = aux;
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

void ManagerPuntaje::eliminarTabla()
{
    _ap.crearNuevaTabla();
}

std::string ManagerPuntaje::mostrarTabla()
{
    std::ostringstream cadena;
    Puntaje aux;
    Equipo eq;
    int posEq;
    ArchivoEquipo ae("Equipos.fix");

    cadena << std::setw(3) << std::left << "P"
        << std::setw(10) << std::left << "Equipo"
        << std::setw(5) << std::left << "PJ"
        << std::setw(5) << "G" 
        << std::setw(5) << "E" 
        << std::setw(5) << "P"
        << std::setw(5) << std::left << "GF-GC"
        << std::setw(3) << ""
        << std::setw(5) << "Pts." << std::endl;

    for (int i = 0; i < _cantidad; i++) {
        posEq= ae.buscarPorId(_puntajes[i].getIdEquipo());
        eq= ae.leerRegistro(posEq);
        cadena  << std::setw(3) << std::left << i+1
           << std::setw(10)  << std::left << eq.getNombre()
           << _puntajes[i].toString() << std::endl;
    }

    return cadena.str();
}

std::string ManagerPuntaje::mostrarGanador()
{
    std::string aux;
    ManagerEquipo me;
    Equipo eq;
    for (int i = 0; i < _cantidad; i++) {
        if (_puntajes[i].getPuntos() >= _puntajes[0].getPuntos()) {
            eq= me.getEquipoPorID(_puntajes[i].getIdEquipo());
            aux += eq.getNombre();
            aux += "\n";
        }
    }
    return aux;
}

ManagerPuntaje::~ManagerPuntaje()
{
    if (_cantidad != 0) {
        delete[] _puntajes;
    }
}


