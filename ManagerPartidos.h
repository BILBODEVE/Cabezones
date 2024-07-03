#pragma once
#include "ArchivoPartido.h"

class ManagerPartidos
{
public:
    ManagerPartidos();
    void mostrarFixture(int cantJornadas);

private:
    ArchivoPartido _ap;
};

