#include "ArchivoPuntaje.h"
#include <cstring>

ArchivoPuntaje::ArchivoPuntaje(const std::string &nombre)
{
	strcpy(_nombre, nombre.c_str());
}

bool ArchivoPuntaje::crearNuevaTabla()
{
	FILE* p;
	p = fopen(_nombre, "wb");
	if (p == nullptr) return false;
	fclose(p);
	return true;
}

bool ArchivoPuntaje::grabarRegistro(const Puntaje& puntaje)
{
	FILE* p;
	p = fopen(_nombre, "ab");
	if (p == nullptr) return false;
	bool ok=fwrite(&puntaje, sizeof(Puntaje), 1, p);
	fclose(p);
	return ok;
}


Puntaje ArchivoPuntaje::leerRegistro(int pos)
{
	FILE* p;
	Puntaje aux;
	p = fopen(_nombre, "rb");
	if (p == nullptr) return aux;
	fseek(p, sizeof(Puntaje) * pos, SEEK_SET);
	fread(&aux, sizeof(Puntaje), 1, p);
	fclose(p);
	return aux;

}

void ArchivoPuntaje::leerTodos(Puntaje registros[], int cantidad) {
	bool result;
	FILE* pFile;

	pFile = fopen(_nombre, "rb");

	if (pFile == nullptr) {
		return;
	}

	fread(registros, sizeof(Puntaje), cantidad, pFile);

	fclose(pFile);
}

bool ArchivoPuntaje::modificarRegistro(Puntaje& puntaje, int posicion)
{
	FILE* p;
	p = fopen(_nombre, "rb+");
	if (p == nullptr) return false;
	fseek(p, sizeof(Puntaje) * posicion, SEEK_SET);
	bool ok= fwrite(&puntaje, sizeof(Puntaje), 1, p);
	fclose(p);
	return ok;
}

int ArchivoPuntaje::buscarRegistro(int nroEquipo)
{
	FILE* p;
	int pos = 0;
	Puntaje aux;
	p = fopen(_nombre, "rb");
	while (fread(&aux, sizeof(Puntaje), 1, p )== 1) {
		if (aux.getIdEquipo() == nroEquipo) {
			return pos;
		}
		pos++;
	}
	return -1;
}

int ArchivoPuntaje::cantidadRegistros()
{
	FILE* p;
	int tam;
	p = fopen(_nombre, "rb");
	if (p == nullptr) return 0;
	fseek(p, 0, SEEK_END);
	tam = ftell(p) / sizeof(Puntaje);
	fclose(p);
	return tam;
}
