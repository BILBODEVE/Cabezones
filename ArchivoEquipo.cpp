#include "ArchivoEquipo.h"

ArchivoEquipo::ArchivoEquipo(const std::string& nombre)
{
	strcpy(_nombre, nombre.c_str());
}

bool ArchivoEquipo::grabarRegistro(const Equipo& equipo)
{
	FILE* p;
	p = fopen(_nombre, "ab");
	if (p == nullptr) return false;
	bool ok= fwrite(&equipo, sizeof(Equipo), 1, p);
	fclose(p);
	return ok;
}

bool ArchivoEquipo::modificarRegistro(int pos, Equipo &equipo)
{
	FILE* p;
	p = fopen(_nombre, "rb+");
	if (p == nullptr) return false;
	fseek(p, sizeof(Equipo) * pos, SEEK_SET);
	bool ok = fwrite(&equipo, sizeof(Equipo), 1, p);
	fclose(p);
	return ok;
}

Equipo ArchivoEquipo::leerRegistro(int pos)
{
	FILE* p;
	Equipo aux;
	aux.setId(0);
	p = fopen(_nombre, "rb");
	if (p == nullptr) return aux;
	fseek(p, sizeof(Equipo) * pos, SEEK_SET);
	fread(&aux, sizeof(Equipo), 1, p);
	fclose(p);
	return aux;

}

int ArchivoEquipo::buscarPorId(int idEquipo) {
	Equipo reg;
	int pos = 0;
	FILE* pFile;

	pFile = fopen(_nombre, "rb");
	if (pFile == nullptr) {
		return -1;
	}

	while (fread(&reg, sizeof(Equipo), 1, pFile)) {
		if (reg.getId() == idEquipo) {
			fclose(pFile);
			return pos;
		}
		pos++;
	}
	fclose(pFile);
	return -1;
}

bool ArchivoEquipo::borrarRegistros()
{
	FILE* p;
	p = fopen(_nombre, "wb");
	if (p == nullptr) return false;
	fclose(p);
	return true;
}

int ArchivoEquipo::getNuevoID() {

	int cantidad = getCantidadRegistros();

	if (cantidad > 0) {
		return leerRegistro(cantidad - 1).getId() + 1;
	}
	else {
		return 1;
	}
}

int ArchivoEquipo::getCantidadRegistros() {
	FILE* pFile;
	int tam;

	pFile = fopen(_nombre, "rb");

	if (pFile == nullptr) {
		return 0;
	}

	fseek(pFile, 0, SEEK_END);

	tam = ftell(pFile) / sizeof(Equipo);

	fclose(pFile);

	return tam;
}