#include "ArchivoPartido.h"

ArchivoPartido::ArchivoPartido(const std::string& nombre)
{
	strcpy(_nombre, nombre.c_str());
}

bool ArchivoPartido::grabarRegistro(const Partido& partido)
{
	FILE* p;
	p = fopen(_nombre, "ab");
	if (p == nullptr) return false;
	bool ok= fwrite(&partido, sizeof(Partido), 1, p);
	fclose(p);
	return true;
}

bool ArchivoPartido::modificarRegistro(int pos, const Partido& partido)
{
	FILE* p;
	p = fopen(_nombre, "rb+");
	if (p == nullptr) return false;
	fseek(p, sizeof(Partido) * pos, SEEK_SET);
	bool ok = fwrite(&partido, sizeof(Partido), 1, p);
	fclose(p);
	return ok;
}

bool ArchivoPartido::crearNuevoFixture()
{
	FILE* p;
	p = fopen(_nombre, "wb");
	if (p == nullptr) return false;
	fclose(p);
	return true;
}

Partido ArchivoPartido::leerRegistro(int pos)
{
	FILE* p;
	Partido aux;
	aux.setNroJornada(-1);
	p = fopen(_nombre, "rb");
	if (p == nullptr) return aux;
	fseek(p, sizeof(Partido) * pos, SEEK_SET);
	fread(&aux, sizeof(Partido), 1, p);
	fclose(p);
	return aux;
}

int ArchivoPartido::cantidadRegistros()
{
	FILE* p;
	p = fopen(_nombre, "rb");
	if (p == nullptr) return 0;
	fseek(p, 0, SEEK_END);
	int tam = ftell(p) / sizeof(Partido);
	fclose(p);
	return tam;
}
