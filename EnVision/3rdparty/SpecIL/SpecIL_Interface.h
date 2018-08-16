#ifndef SPECIL_INTERFACE_H
#define SPECIL_INTERFACE_H

#include <string>
#include <vector>

// Minimum Header
struct t_SpecHead
{
	std::string filename;				//	Filename des Bildes (fuer type=2)
	int type;							//	Type des Bildes
										//		type = 0   - undefiniert
										//		type = 1   - cube geladen
										//		type = 2   - cube nicht geladen
										//			(auf Festplatte halten,
										//			wegen Speicherplatz)
	void * imgcube;						//	Datacube (fuer type=1)

	std::string ID;						//	ENVI Feld unter description: ID 
	std::string wavelenunit;			// 
	std::vector <float> wavelen;		//	Wellenlaengen
	std::vector <float> exposureTimeUS;	//	Belichtung
	unsigned long long headsize;		//	header size der eingelesenen Datei
	unsigned int numdim;				//	Anzahl der Dimensionen
	unsigned long long imgsize[3];		//	Bildgroesse:
										//	 Achtung! Diese Anordnung ist jedoch keine Aussage,
										//	 wie die Daten im Speicher liegen! -> interleave
										//			[0] - spatial (samples) (x)
										//			[1] - spectral	(bands)	(z)
										//			[2] - frame (lines)		(y)
	enum t_interleave {					//	interleave:
										//	 Achtung! So liegen die Daten in der Datei UND
										//	 auch im geladenen Zustand im Speicher (type = 1) ! 
		IL_UNKNOWN,						//		Unbekannt
		IL_BSQ,							//		BSQ - band sequential
		IL_BIP,							//		BIP - band interleaved by pixel
		IL_BIL							//		BIL - band interleaved by line
	} interleave;						//
	unsigned int  bitdepth;				//	Bit Tiefe (Wie viele Bits von allen wirklich genutzt werden.
										//		Hauptsaechlich fuer .tgd Dateien. Diese sind immer
										//		4 Byte gross, aber nutzen nicht alle Bits.
										//
	enum t_data_type {					//	ENVI Datentyp
		DT_UNKNOWN		=	0,			//		Unbekannt
		DT_8_BYTE		=	1,			//		1 Byte
		DT_16_SINT		=	2,			//		2 Byte Integer
		DT_32_SLONG		=	3,			//		4 Byte Integer
		DT_32_FLOAT		=	4,			//		4 Byte Float
		DT_64_DOUBLE	=	5,			//		8 Byte Float (Double)
		DT_2x32_COMPLEX	=	6,			//	2x	4 Byte Komplex	
		DT_2x64_COMPLEX	=	9,			//	2x	8 Byte Komplex
		DT_16_UINT		=	12,			//		2 Byte Unsigned Integer
		DT_32_ULONG		=	13,			//		4 Byte Unsigned Integer
		DT_64_SLONG		=	14,			//		8 Byte Integer
		DT_64_ULONG		=	15			//		8 Byte Unsigned Integer
	} data_type;
	std::string data_type_str;			//	Den Datentyp als Namen! fuer evtl. Unterscheidungen
										//	bei z.B. Tapsansi:
										//		byte, bool, char, uchar, short, ushort, int, uint,
										//		long, ulong, float, double
	double data_type_maxval;			// Maximaler Wert den der verwendete Datentyp erreichen kann;
	double data_type_minval;			// Minimaler Wert den der verwendete Datentyp erreichen kann;
	enum{								//	Byte Order
		BO_UNKNOWN	=	-1,				//
		BO_LSF		=	0,				//		least significant byte (Little-endian)
		BO_MSF		=	1				//		most significant byte (Big-endian)
	} byte_order;
	unsigned long long pixelsize;		// Pixelgroesse in Byte
	double maxval;						//

	double Frameperiod;					// Frameperiod
	double Integration_time;			// Integration time

	double pixelSizeX;					// Hardware Pixel groesse
	double pixelSizeY;					// Hardware Pixel groesse

// #####################################
// Fuer folgende Felder sind die Bezeichnungen direkt aus dem hyspex header uebernommen worden!
	
	void* QEarray;						// QE
	unsigned long long QEarraySize;		// in Byte, aber das Array ist eigentlich double.. war aber irgendwie nicht schicker mit fstream::read zu proggen...
	void* REarray;						// RE
	unsigned long long REarraySize;		// in Byte, Array ist aber mit double Werten gefuellt
	void* BGarray;						// BG... Background... Dunkelstrom
	unsigned long long BGarraySize;		// in Byte, Array ist aber mit double Werten gefuellt
	void* BadPixelsarray;					// BG... Background... Dunkelstrom
	unsigned long long BadPixelsarraySize;		// in Byte, Array ist aber mit double Werten gefuellt
	unsigned int nobp; // Number of Bad Pixels

	unsigned int serialNumber;
	double scalingFactor;

	double SF;
	double apertureSize;

};

// Spectral Image Loader Interface Class
class SpecIL_Interface
{
public:
	// (durch static wie eine globale Funktion zu sehen
	// und verletzt damit eigentlich nicht die Definition eines Interfaces)
	// ------------------------------------------------------------------------
	// Datei oeffnen:
	//	Diese Funktion verwenden um ein Objekt zu erzeugen, das mit einer bestehenden Datei genutzt werden soll.
	//	Das Standard Profil ist immer RAW.
	// Unterstuetzte Formate:
	//	HySpex:		.img und .bin	mit BSQ, BIL, BIP
	//	Nuance:		.im3
	//	TapSansi:	.tgd			mit BSQ, BIL, BIP
	// 
	// cstr_filename	-	Absoluter Dateipfad
	// mode				-	Modus:
	//								r		-	read: Eine bestehende Datei wird zum lesen geoeffnet.
	//								w		-	write: Es wird eine neue Datei im img+hdr Format angelegt!
	//	(noch nicht implementiert)	rw,wr	-	read+write: Eine bestehende Datei wird zum lesen geöffnet und 
	//														es koennen die Werte manipuliert werden, jedoch
	//														NICHT die Pixelgroesse und das Format!
	// return false if file-format is not supported
	static SpecIL_Interface* open(const char* mode, const char* cstr_filename);

	// Destruktor
	virtual ~SpecIL_Interface(){};
	//	virtual ~SpecIL_Interface()=0; // Geht so nicht! Warum?

	// lesen der Datei und des Headers, ggf. zusätzlich aus einer extra Header Datei
	virtual int read() = 0;

	// schreiben (noch nicht zum verwenden!)
	virtual int write() = 0;

	// Objekt schließen
	virtual void close() = 0;

	// ------------------------------------------------------------------------
	// SET METHODEN: Eigenschaften

	// Bild/Daten-Eigenschaften setzen:
	//	Manuelles setzen von Eigenschaften, wenn diese nicht vorhaneden sind. Diese Informationen werden in den
	//	SpecHeader gespeichert.
	//	Aufloesung der Dimensionen:	
	//		width - x - Samples
	//		height - y - Frames
	//		depth - z - Bands
	//			=> Weitere Dimensionen koennten ergaenzt werden. Noch NICHT implementiert!
	//	il		- Interleave, Anordnung der Daten in der Dateil: bsq, bil, bip (siehe t_SpecHead::t_interleave)
	//	dt		- Datentyp nach ENVI Formatierung, siehe t_SpecHead::t_data_type 
	virtual void setImageProperties(	const char* id,
									int width,
									int height,
									int planes,
									t_SpecHead::t_interleave il,
									t_SpecHead::t_data_type dt
									) = 0;

	// Dimensionsgroessen
	//	width - samples
	//	planes - bands
	//	height - lines
	virtual void setImageSize(unsigned int width, unsigned int height, unsigned int planes) = 0;

	// Datentyp nach ENVI Formtat (s. Oben!)
	//	Die Pixelgroesse wird dementsprechend gesetzt
	virtual void setDataType(t_SpecHead::t_data_type dt) = 0;

	// Interleave
	virtual void setInterleave(t_SpecHead::t_interleave il) = 0;

	// ID
	virtual void setID(const char* id) = 0;

	// Wellenlaengen
	//	wavelen - Wellenlaengen der Baender
	virtual void setWavelen(std::vector <float> wavelen) = 0;

	// Belichtungszeiten der Wellenlaengen
	virtual void setExposureTimeUS(std::vector <float> exposureTimeUS) = 0;
	
	// Cube nicht in den RAM laden
	virtual void setReadOnlyFromHDD()=0;

	// Maximale groesse einer Datei um vollstaendig in den RAM geladen zu werden
	// Standard ist 3500000000Byte !
	// Fuer groessere Volumen MUSS setCubeMaxSize VOR read gesetzt werden !
	virtual void setCubeMaxSize(unsigned long long cms) = 0;

	// Error Log System an/aus 
	virtual void EnableErrorLog() = 0;
	virtual void DisableErrorLog() = 0;
	// weitere werden folgen...


	// Die Headerdaten einer anderen Datei kopiere.
	// ACHTUNG!!! Es werden nicht die eigentlichen Daten kopiert:
	// imgcube, QEarray, REarray, BGarray, BadPixelsarray
	virtual void CopyHeaderFrom(t_SpecHead HeaderSource) = 0;

	//
	virtual int copyQEfrom(void* QEarray, size_t QESize) = 0;
	virtual int copyREfrom(void* REarray, size_t RESize) = 0;
	virtual int copyBGfrom(void* BGarray, size_t BGSize) = 0;
	virtual int copyBadPixelfrom(void* BadPixelarray, size_t BadPixelSize) = 0;
	// ------------------------------------------------------------------------
	// GET METHODEN: Eigenschaften

	// Pointer auf den Header
	virtual t_SpecHead* getHeaderPointer() = 0;
	virtual t_SpecHead* getHeader() = 0;


	// gibt den Datentyp in der OpenCV Numerierung zurueck (CV_8U = 0, CV_32S = 4, usw)
	virtual int getOpenCVDatatype() = 0;


	// ------------------------------------------------------------------------
	// GET METHODEN: Daten

	//Definition des ImgCubes:
	//
	//		     /\ z = imgsize[1] => spectral (bands)
	//		     /
	//		    /
	//		   /
	//	    0 .--------------> x = imgsize[0] => spatial (samples)
	//		  |
	//		  |
	//		  |
	//		  |
	//		  V y = imgsize[2] => frame (lines)
	//
	// ------------------------------------------------------------------------
	//
	// Ebene anfordern
	// Speicher muss bereitgestellt sein!
	// -> Speicherverwaltung obligt dem Anwender!!!!
	// Es sind nur positive Koordinaten zulaessig!
	// Mit eine Koordinate = -1 wird die gewuenschte Ebenenrichtung angegeben, Bsp:
	// Fuer die z-Richtung und damit x-y Ebene: x=-1 und y=-1
	// Mit z wird dann die Ebene in z-Richtung gewaehlt
	// void* plane muss extern freigegeben werden! SpecIL macht das nicht!
	//
	// Ausgegeben Koordinatensysteme:
	// Ebene: Band
	// 0 .--------------> x = imgsize[0] => spatial (samples)
	//	 |
	//	 |
	//	 |
	//	 |
	//   V y = imgsize[2] => frame (lines)
	// Ebene: Frame
	// 0 .--------------> x = imgsize[0] => spatial (samples)
	//	 |
	//	 |
	//	 |
	//	 |
	//   V z = imgsize[1] => spectral (bands)
	// Ebene: Samples
	// 0 .--------------> z = imgsize[1] => spectral (bands)
	//	 |
	//	 |
	//	 |
	//	 |
	//   V y = imgsize[2] => frame (lines)
	virtual int getPlane(void* plane, int x, int y, int z)=0;

	// Ausschnitt einer Ebene anfordern
	// x,y,z sind nun Arrays mit zwei Elementen
	// Fuer einen Ausschnitt werden zwei davon in der Form [von, bis] als abgeschlossenes Intervall gesetzt, wobei Null der Startindex ist
	// beim dritten Parameter gibt das erste Elemnt die gewuenschte Ebene an und im zweiten steht -1 !Wichtig! 
	virtual int getPlane(void* plane, int *x, int *y, int *z) = 0;

	// Vektor anfordern
	// Speicher muss bereitgestellt sein!
	// -> Speicherverwaltung obligt dem Anwender!!!!
	// Es sind nur positive Koordinaten zulaessig!
	// Mit eine Koordinate = -1 wird die gewuenschte Vektorrichtung angegeben, Bsp:
	// Fuer einen Vektor in z-Richtung wird z=-1 gesetzt
	// x und y bestimmen dann den Vektor
	virtual int getVector(void* vector, int x, int y, int z)=0;

	// Punkt anfordern
	// Speicher muss bereitgestellt sein!
	// -> Speicherverwaltung obligt dem Anwender!!!!
	// Mit alles drei Variablen wird die Koordinate im Bildraum angegeben
	virtual int getPoint(void* point, int x, int y, int z)=0;


	// ------------------------------------------------------------------------
	// SET METHODEN: Daten

	// Ebene ueberschreiben
	virtual int setPlane(void* plane, int x, int y, int z)=0;
	// Vektor schreiben
	virtual int setVector(void* vector, int x, int y, int z)=0;
	// Punkt schreiben
	virtual int setPoint(void* point, int x, int y, int z)=0;

};
#endif // SPECIL_INTERFACE_H