#ifndef SPECIL_HYSPEX_H
#define SPECIL_HYSPEX_H

#include "SpecIL_Base.h"

class SpecIL_HySpex : public SpecIL_Base
{
public:
	// Destruktor
	~SpecIL_HySpex();
	// Konstruktor
	SpecIL_HySpex();
	// Einlesen der Headerdaten und ggf. Bilddaten, wenn sie nicht zu groﬂ sind
	int read();
	// Headerdaten aus der Cubedatei lesen
	int readFileHeader();
protected:
	// Datei oeffnen und Daten laden
	int readImageData();

private:
	void cleanup();

	// Alle (!) Informationen aus dem Header von NEO .hyspex, .im oder .bin Dateien
	void init_NEOheader();
	// word                   = fread(fid,  8,'*char')';
	char hdr_word[8];
	// hdrSize                = fread(fid,  1,'*int');
	int hdr_hdrSize;
	// serialNumber           = fread(fid,  1,'*uint');
	unsigned long hdr_serialNumber;
	// configFile             = fread(fid,200,'*char')';
	char hdr_configFile[200];
	// settingFile            = fread(fid,120,'*char')';
	char hdr_settingFile[120];
	// scalingFactor          = fread(fid,  1,'*double');
	double hdr_scalingFactor;
	// electronics            = fread(fid,  1,'*uint');
	unsigned long hdr_electronics;
	// comsettingsElectronics = fread(fid,  1,'*uint');
	unsigned long hdr_comsettingsElectronics;
	// comportElectronics     = fread(fid, 44,'*char')';
	char hdr_comportElectronics[44];
	// fanSpeed               = fread(fid,  1,'*uint');
	unsigned long hdr_fanSpeed;
	// backTemperature        = fread(fid,  1,'*uint');
	unsigned long hdr_backTemperature;
	// Pback                  = fread(fid,  1,'*uint');
	unsigned long hdr_Pback;
	// Iback                  = fread(fid,  1,'*uint');
	unsigned long hdr_Iback;
	// Dback                  = fread(fid,  1,'*uint');
	unsigned long hdr_Dback;
	// comport                = fread(fid, 64,'*char')';
	char hdr_comport[64];
	// detectstring           = fread(fid,200,'*char')';
	char hdr_detectstring[200];
	// sensor                 = fread(fid,200,'*char')';
	char hdr_sensor[200];
	// framegrabber           = fread(fid,200,'*char')';
	char hdr_framegrabber[200];
	// ID                     = fread(fid,200,'*char')';
	char hdr_ID[200];
	// supplier               = fread(fid,200,'*char')';
	char hdr_bufferSupplier[200];
	// leftGain               = fread(fid, 32,'*char')';
	char hdr_bufferLeftGain[32];
	// rightGain              = fread(fid, 32,'*char')';
	char hdr_bufferRightGain[32];
	// comment                = fread(fid,200,'*char')';
	char hdr_comment[200];
	// backgroundFile         = fread(fid,200,'*char')';
	char hdr_backgroundFile[200];
	// recordHD               = fread(fid,  1,'*char')';
	char hdr_recordHD;
	// unknownPOINTER         = fread(fid,  1,'*uint');    %4 byte pointer [useless] XCamera*m_hCam
	unsigned long hdr_unknownPOINTER;
	// serverIndex            = fread(fid,  1,'*uint');
	unsigned long hdr_serverIndex;
	// comsettings            = fread(fid,  1,'*uint');
	unsigned long hdr_comsettings;
	// numberOfBackground     = fread(fid,  1,'*uint');
	unsigned long hdr_numberOfBackground;
	// spectralSize           = fread(fid,  1,'*uint');
	unsigned long hdr_spectralSize;
	// spatialSize            = fread(fid,  1,'*uint');
	unsigned long hdr_spatialSize;
	// binning                = fread(fid,  1,'*uint');
	unsigned long hdr_binning;
	// detected               = fread(fid,  1,'*uint');
	unsigned long hdr_detected;
	// integrationtime        = fread(fid,  1,'*uint');
	unsigned long hdr_integrationtime;
	// frameperiod            = fread(fid,  1,'*uint');
	unsigned long hdr_frameperiod;
	// defaultR               = fread(fid,  1,'*uint');
	unsigned long hdr_defaultR;
	// defaultG               = fread(fid,  1,'*uint');
	unsigned long hdr_defaultG;
	// defaultB               = fread(fid,  1,'*uint');
	unsigned long hdr_defaultB;
	// bitshift               = fread(fid,  1,'*uint');
	unsigned long hdr_bitshift;
	// temperatureOffset      = fread(fid,  1,'*uint');
	unsigned long hdr_temperatureOffset;
	// shutter                = fread(fid,  1,'*uint');
	unsigned long hdr_shutter;
	// backgroundPresent      = fread(fid,  1,'*uint');
	unsigned long hdr_backgroundPresent;
	// power                  = fread(fid,  1,'*uint');
	unsigned long hdr_power;
	// current                = fread(fid,  1,'*uint');
	unsigned long hdr_current;
	// bias                   = fread(fid,  1,'*uint');
	unsigned long hdr_bias;
	// bandwidth              = fread(fid,  1,'*uint');
	unsigned long hdr_bandwidth;
	// vin                    = fread(fid,  1,'*uint');
	unsigned long hdr_vin;
	// vref                   = fread(fid,  1,'*uint');
	unsigned long hdr_vref;
	// sensorVin              = fread(fid,  1,'*uint');
	unsigned long hdr_sensorVin;
	// sensorVref             = fread(fid,  1,'*uint');
	unsigned long hdr_sensorVref;
	// coolingTemperature     = fread(fid,  1,'*uint');
	unsigned long hdr_coolingTemperature;
	// windowStart            = fread(fid,  1,'*uint');
	unsigned long hdr_windowStart;
	// windowStop             = fread(fid,  1,'*uint');
	unsigned long hdr_windowStop;
	// readoutTime            = fread(fid,  1,'*uint');
	unsigned long hdr_readoutTime;
	// p                      = fread(fid,  1,'*uint');
	unsigned long hdr_p;
	// i                      = fread(fid,  1,'*uint');
	unsigned long hdr_i;
	// d                      = fread(fid,  1,'*uint');
	unsigned long hdr_d;
	// numberOfFrames         = fread(fid,  1,'*uint');
	unsigned long hdr_numberOfFrames;
	// nobp                   = fread(fid,  1,'*uint');
	unsigned long hdr_nobp;
	// dw                     = fread(fid,  1,'*uint');
	unsigned long hdr_dw;
	// EQ                     = fread(fid,  1,'*uint');
	unsigned long hdr_EQ;
	// lens                   = fread(fid,  1,'*uint');
	unsigned long hdr_lens;
	// FOVexp                 = fread(fid,  1,'*uint');
	unsigned long hdr_FOVexp;
	// scanningMode           = fread(fid,  1,'*uint');
	unsigned long hdr_scanningMode;
	// calibAvailable         = fread(fid,  1,'*uint');
	unsigned long hdr_calibAvailable;
	// numberOfAvg            = fread(fid,  1,'*uint');
	unsigned long hdr_numberOfAvg;
	// SF                     = fread(fid,  1,'*double');
	double hdr_SF;
	// apertureSize           = fread(fid,  1,'*double');
	double hdr_apertureSize;
	// pixelSizeX             = fread(fid,  1,'*double');
	double hdr_pixelSizeX;
	// pixelSizeY             = fread(fid,  1,'*double');
	double hdr_pixelSizeY;
	// temperature            = fread(fid,  1,'*double');
	double hdr_temperature;
	// maxFramerate           = fread(fid,  1,'*double');
	double hdr_maxFramerate;
	// spectralCalibPOINTER   = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = spectralSize*sizeof(double)
	long hdr_spectralCalibPOINTER;
	// REPOINTER              = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = spectralSize*spatialSize*sizeof(double)
	long hdr_REPOINTER;
	// QEPOINTER              = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = spectralSize*sizeof(double)
	long hdr_QEPOINTER;
	// backgroundPOINTER      = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = spatialSize*spectralSize*sizeof(double)
	long hdr_backgroundPOINTER;
	// badPixelsPOINTER       = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = nobp*sizeof(uint)
	long hdr_badPixelsPOINTER;
	// imageFormat            = fread(fid,  1,'*uint');
	unsigned long hdr_imageFormat;// Interleave: BIL, BSQ, BIP

	// spectralVector         = fread(fid,// spectralSize,'*double');
	size_t hdr_spectralVectorSize = 0;
	char* hdr_spectralVectorBuffer;

	// QE                     = fread(fid,// spectralSize,'*double');
	size_t hdr_QESize = 0;
	char* hdr_QEBuffer;

	// RE                     = fread(fid,// spectralSize*// spatialSize,'*double');
	size_t hdr_RESize = 0;
	char* hdr_REBuffer;

	// background             = fread(fid,// spatialSize*// spectralSize,'*double');
	size_t hdr_backgroundSize = 0;
	char* hdr_backgroundBuffer;

	// badPixels              = fread(fid,// nobp,'*uint');
	size_t hdr_badPixelsSize = 0;
	char* hdr_badPixelsBuffer;
};
#endif // SPECIL_HYSPEX_H