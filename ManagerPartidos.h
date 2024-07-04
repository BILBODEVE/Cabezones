#pragma once
#include "ArchivoPartido.h"

class ManagerPartidos
{
public:
    ManagerPartidos();
    const std::string getNombreGanador(int nroPartido);
    int getCantidadPartidos();
    void eliminarFixture();
    std::string mostrarFixture();

private:
    ArchivoPartido _ap;
};

