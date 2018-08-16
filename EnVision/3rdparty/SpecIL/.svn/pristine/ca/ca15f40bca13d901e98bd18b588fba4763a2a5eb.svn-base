#ifndef SPECIL_TIFF_H
#define SPECIL_TIFF_H

#include "SpecIL_Base.h"

// libtiff
#include <tiffio.h>

class SpecIL_TIFF : public SpecIL_Base
{

	// TIFF wird keine Profile mehr unterstuetzen!

public:
	// Destruktor
	~SpecIL_TIFF();
	// Konstruktor
	SpecIL_TIFF();
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
	int getPlane(void* plane, int x, int y, int z);
	int getPlane(void* plane, int *x, int *y, int *z); //  Noch nicht unterstuetzt
	// Vektor
	int getVector(void* vector, int x, int y, int z);
	//
	int getPoint(void* point, int x, int y, int z);

protected:
	// Datei oeffnen und Bilddaten (wenn moeglich bei ausreichend RAM)
	// einlesen
	int readImageData();

	// Ebenen
	int getPlane_Band_tiled(void* plane, int z);
	int getPlane_Band_striped(void* plane, int z);
	int getPlane_Frame_tiled(void* plane, int y);
	int getPlane_Frame_striped(void* plane, int y);
	int getPlane_Sample_tiled(void* plane, int x);
	int getPlane_Sample_striped(void* plane, int x);

	int getVector_X(void* vector, int y, int z);
	int getVector_Y(void* vector, int x, int z);
	int getVector_Z(void* vector, int x, int y);

private:
	void TIFFinit();
	unsigned int directories;	// Anzahl der directories in der Datei. (wird gezaehlt und steht nicht direkt im Header)
								//	= Anzahl der unabh‰ngigne Bilder in der Datei

	// .tiff/.tif Header Informationen
	unsigned char header_byteorder;
	unsigned int header_samples;
	unsigned int header_lines;
	unsigned int header_bands;
	unsigned int header_bitdepth;
	unsigned int header_sampleformat;
	unsigned short header_PlanarConfig;	//1 = Chunky = BIP, 2 = Planar = BSQ
	unsigned short header_PhotometricInterpretation;	// 0 = WhiteIsZero, 1 = BlackIsZero, 2 = RGB, 3 = Palette color, 4 = Transparency Mask
	
	// Interne Informationen zu den Daten
	bool IsTiled;	// Ist das Bild in Strips oder Tiles hinterlegt?`true = tiled!
	unsigned long long CubeSize;

	// Fuer Tiles
	unsigned int NumOfTiles;
	signed int TileSize;//in Byte
	unsigned int header_TileWidth;
	unsigned int header_TileLength;
	unsigned int TilesAcross;// Anzahl der Tiles in der horizontalen Achse
	unsigned int TilesDown;// Anzahl der Tiles in der vertikalen Achse
	unsigned int TilesPerImage;
	unsigned long long RestoredCubeOfTilesSize; // Die groesse des aus Tiles zusammengesetzten Cubes.
												// Diese ist fast immer groesser als das Original, weil Tiles bestimmte Vorgaben
												// bei ihrer Dimensionierung haben. Daher werden oft Pixel hinzugefuegt (Padding)

	// Fuer Strips
	unsigned int NumOfStrips;
	signed int StripSize;	//in Byte. ACHTUNG! Der letzte Strip kann kleiner sein. Anders als bei Tiles gibt es kein Padding
							// und die restlichen Zeilen werden dann im letzten Strip gelegt, das koennen unter umstaenden weniger
							// Zeilen sein!
	unsigned long long RestoredCubeOfStripSize;// Die groesse des aus Strips zusammengesetzten Cubes.
	long RowsPerStrip;
	bool RestoredStripCubeWithPadding;


};

#endif // SPECIL_TIFF_H