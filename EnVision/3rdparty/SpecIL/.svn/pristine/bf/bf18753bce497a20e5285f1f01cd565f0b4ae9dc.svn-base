#ifndef SPECIL_TGD_H
#define SPECIL_TGD_H

#include "SpecIL_Base.h"
#include "SpecIL_Nuance.h"
#include <string>
#include <vector>

class SpecIL_TGD : public SpecIL_Base
{
public:
	// Destruktor
	~SpecIL_TGD();
	// Konstruktor
	SpecIL_TGD();
	// Bild/Daten-Eigenschaften setzen:
	void setImageProperties(const char* id,
		int width,
		int height,
		int planes,
		t_SpecHead::t_interleave il,
		t_SpecHead::t_data_type dt
		);
	// Einlesen der Headerdaten und ggf. Bilddaten, wenn sie nicht zu groﬂ sind
	int read();
	// Headerdaten aus der Datei lesen
	int readFileHeader();
	// Ebene
//	int getPlane(void* plane, int x, int y, int z);
	// Vektor
	int getVector(void* vector, int x, int y, int z);
	//
	int getPoint(void* point, int x, int y, int z);

protected:
	// Laed das gesetzte Profil
	int loadProfile();
	// Datei oeffnen und Daten laden
	int readImageData();
	// TGD Meta-File einlesen '.tgd.meta'
	int readMetaFile(std::string metafilename);

	void setDataTypeMaxMin();

private:
	void TGDinit();
	// .tgd Header Informationen
	int header_dimensions;						// Anzahl der Dinensionen
	unsigned int header_dims[4];				// Dimensionen und ihre Ausdehnungen
	unsigned int header_datatype;				// Datentyp
	unsigned int header_headersize;				// Dateiheadergroesse

	// .tgd.meta Informationen
	std::string meta_camera;					// Kamera(name)
	std::string meta_sensor;					// Sensor(name)
	unsigned int  meta_bitdepth;				// Bittiefe: Anzahl der verwendeten Bits im 4Byte Block
												// Aufloesung:
	unsigned int meta_sensorheight;				//	Hoehe
	unsigned int meta_sensorwidth;				//	Breite
	unsigned int meta_planes;					//	Ebenen, Bildkanaele, 3. Dimension
	std::vector <float> meta_wavelengths;		//	Wellenlaengen
	t_SpecHead::t_interleave meta_interleave;
	t_SpecHead::t_data_type meta_datatype;
	std::string meta_datatype_str;

	// Manuelle Bildwerte
	unsigned int user_width;
	unsigned int user_height;
	unsigned int user_planes;
	t_SpecHead::t_interleave user_interleave;
	t_SpecHead::t_data_type user_datatype;
	std::string user_camera;					// Kamera(name)
};
#endif // SPECIL_TGD_H