#pragma once
#include <string>
class Puntaje
{
public:
	Puntaje();
	int getIdEquipo();
	int getPartidosJugados();
	int getGanados();
	int getEmpatados();
	int getPerdidos();
	int getGolesAFavor();
	int getGolesEnContra();
	int getPuntos();
	void setIdEquipo(int idEquipo);
	void addPartidosJugados();
	void addGanados();
	void addEmpatados();
	void addPerdidos();
	void setGolesAFavor(int golesAFavor);
	void setGolesEnContra(int golesEnContra);
	void setPuntos();
	std::string toString();

private:
	int _idEquipo;
	int _partidosJugados;
	int _ganados;
	int _empatados;
	int _perdidos;
	int _golesAFavor;
	int _golesEnContra;
	int _puntos;
};

