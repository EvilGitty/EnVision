#ifndef SPECIL_MAT_H
#define SPECIL_MAT_H

#include "SpecIL_Base.h"
#include <string>

#include "matio.h"

class SpecIL_MAT : public SpecIL_Base
{
public:
	// Destruktor
	~SpecIL_MAT();
	// Konstruktor
	SpecIL_MAT();
	// Einlesen der Headerdaten und ggf. Bilddaten, wenn sie nicht zu groß sind
	int read();
	// Headerdaten aus der Datei lesen
	int readFileHeader();
	// Ebene
	int getPlane(void* plane, int x, int y, int z);
	int getPlane(void* plane, int *x, int *y, int *z);
	// Vektor
	int getVector(void* vector, int x, int y, int z);
	//
	int getPoint(void* point, int x, int y, int z);

protected:
	// Datei oeffnen und Daten laden
	int readImageData();

	int getPlane_BandHDD(void* plane, int *x, int *y, int z);
	int getPlane_FrameHDD(void* plane, int *x, int y, int *z);
	int getPlane_SampleHDD(void* plane, int x, int *y, int *z);

	int getVector_X(void* vector, int y, int z);
	int getVector_Y(void* vector, int x, int z);
	int getVector_Z(void* vector, int x, int y);

private:
	void MATinit();

	unsigned short pixelsize;

	// data.hyspec:
	unsigned long long hyspec_imgsize[3];
		// header_imgsize[0] => samples
		// header_imgsize[1] => bands
		// header_imgsize[2] => lines
	char* hyspec_dataorder;
	unsigned long long hyspec_headsize;
	unsigned long long hyspec_saturated;
	unsigned short hyspec_imgcube_datatyp;
		//	MAT_T_UNKNOWN = 0,	UNKNOWN data type
		//	MAT_T_INT8 = 1,	8-bit signed integer data type
		//	MAT_T_UINT8 = 2,	8-bit unsigned integer data type
		//	MAT_T_INT16 = 3,	16-bit signed integer data type
		//	MAT_T_UINT16 = 4,	16-bit unsigned integer data type
		//	MAT_T_INT32 = 5,	32-bit signed integer data type
		//	MAT_T_UINT32 = 6,	32-bit unsigned integer data type
		//	MAT_T_SINGLE = 7,	IEEE 754 single precision data type
		//	MAT_T_DOUBLE = 9,	IEEE 754 double precision data type
		//	MAT_T_INT64 = 12,	64-bit signed integer data type
		//	MAT_T_UINT64 = 13,	64-bit unsigned integer data type
		//	MAT_T_MATRIX = 14,	matrix data type
		//	MAT_T_COMPRESSED = 15,	compressed data type
		//	MAT_T_UTF8 = 16,	8-bit Unicode text data type
		//	MAT_T_UTF16 = 17,	16-bit Unicode text data type
		//	MAT_T_UTF32 = 18,	32-bit Unicode text data type
		//	MAT_T_STRING = 20,	String data type
		//	MAT_T_CELL = 21,	Cell array data type
		//	MAT_T_STRUCT = 22,	Structure data type
		//	MAT_T_ARRAY = 23,	Array data type
		//	MAT_T_FUNCTION = 24	Function data type
	double hyspec_flag_normwhite;

	//data.lab
	std::string lab_colormap;

};
#endif // SPECIL_MAT_H