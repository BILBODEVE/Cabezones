#pragma once

class Partido
{
public:
	Partido();
	void setEquipoA(int idEquipoA);
	void setEquipoB(int idEquipoB);
	void setGolesA(int gA);
	void setGolesB(int gB);
	int getGolesA();
	int getGolesB();
	int getEquipoA();
	int getEquipoB();
	void setNroJornada(int j);
	int getNroJornada();
	void setEjecutado(bool estado);
	bool getEjecutado();

private:
	int _equipoA;
	int _equipoB;
	int _golesA;
	int _golesB;
	int _nroJornada;
	bool _ejecutado;

};

