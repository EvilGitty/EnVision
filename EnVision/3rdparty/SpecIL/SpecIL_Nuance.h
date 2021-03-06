#ifndef SPECIL_NUANCE_H
#define SPECIL_NUANCE_H

#include <Windows.h>

#include "SpecIL_Base.h"

class SpecIL_Nuance : public SpecIL_Base
{
public:
	// Destruktor
	~SpecIL_Nuance();
	// Konstruktor
	SpecIL_Nuance();
	// Einlesen der Headerdaten und ggf. Bilddaten, wenn sie nicht zu gro� sind
	int read();
	// Header lesen
	int readFileHeader();
	// Ebene
	//int getPlane(void* plane, int x, int y, int z);
	// Vektor
	int getVector(void* vector, int x, int y, int z);
	// Punkt
	int getPoint(void* point, int x, int y, int z);

	// relevante Bild/Daten-Eigenschaften setzen (wird nicht unterstuetzt!):
	void setImageProperties(const char* id,
		int width,
		int height,
		int depth,
		t_SpecHead::t_interleave il,
		t_SpecHead::t_data_type dt
		);

protected:
	// Laed das gesetzte Profil
	int loadProfile();

	// Datei oeffnen und Daten laden
	int readImageData();

private:
	// Modul handle fuer Bilder Nuance Kamera
	// HMODULE ist in Windows.h
	HMODULE dllNuance;
};
#endif // SPECIL_NUANCE_H