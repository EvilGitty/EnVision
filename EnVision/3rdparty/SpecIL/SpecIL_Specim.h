#ifndef SPECIL_SPECIM_H
#define SPECIL_SPECIM_H

#include "SpecIL_Base.h"
#include "Helper/commonfunctions.h"

/*
const unsigned short HAWK_RAW_MAX = 16383;
const unsigned short EAGLE_RAW_MAX = 4095;
const unsigned short FENIX_VNIR_RAW_MAX = 4095;
const unsigned short FENIX_SWIR_RAW_MAX = 65535;

const double FRAME_TRANSFER_TIME = 0.002;

const unsigned int RADIANCE_DATA_SCALAR = 1000;
const unsigned short CALIBRATED_DATA_MAX = std::numeric_limits<unsigned short>::max();

const int EAGLE_SENSOR_IDS_INTARR[2] = { 100022,110001 };
const int HAWK_SENSOR_IDS_INTARR[2] = { 300011,310018 };
const int FENIX_SENSOR_IDS_INTARR[2] = { 350005,350002 };

//Constant vectors that contain the sensor id numbers for each sensor type
const std::vector<int> EAGLE_SENSOR_IDS(EAGLE_SENSOR_IDS_INTARR, EAGLE_SENSOR_IDS_INTARR + sizeof(EAGLE_SENSOR_IDS_INTARR) / sizeof(int));
const std::vector<int> HAWK_SENSOR_IDS(HAWK_SENSOR_IDS_INTARR, HAWK_SENSOR_IDS_INTARR + sizeof(HAWK_SENSOR_IDS_INTARR) / sizeof(int));
const std::vector<int> FENIX_SENSOR_IDS(FENIX_SENSOR_IDS_INTARR, FENIX_SENSOR_IDS_INTARR + sizeof(FENIX_SENSOR_IDS_INTARR) / sizeof(int));

//Defines for functions
enum SENSORTYPE { EAGLE, HAWK, FENIX };
bool CheckSensorID(SENSORTYPE s, int id);

//Enum a type to use in functions to specify which data to use
enum Subsensor { VNIR = 0, SWIR = 1 };

*/

class SpecIL_Specim : public SpecIL_Base
{
public:
	// Destruktor
	~SpecIL_Specim();
	// Konstruktor
	SpecIL_Specim();
	// Einlesen der Headerdaten und ggf. Bilddaten, wenn sie nicht zu groﬂ sind
	int read();
	// Headerdaten aus der Cubedatei lesen
	int readFileHeaderRaw();
	int readFileHeaderImg();


protected:
	// Datei oeffnen und Daten laden
	int readImageData();

private:
	void cleanup();

	void init_SPECIMheader();

	std::string hdr_sensor_type;			//sensor type = FX10 , Lumo - Recorder v2017-490
	std::string hdr_acquisition_date;		//acquisition date = DATE(yyyy-mm-dd): 2018-01-24
	std::string hdr_start_time;				//Start Time = UTC TIME: 22:47:35
	std::string hdr_stop_time;				//Stop Time = UTC TIME: 22:47:55

	unsigned long long hdr_spectralSize;	//bands = 224
	unsigned long long hdr_spatialSize;		//samples = 512
	unsigned long long hdr_numberOfFrames;

	std::vector<string> hdr_errors; //errors = {none}

	std::string hdr_imageFormat;
	unsigned int hdr_data_type; 
	unsigned int  hdr_hdrSize; 
	unsigned int  hdr_byte_order; 
	unsigned int  hdr_x_start; 
	unsigned int  hdr_y_start; 
	std::vector<int> hdr_default_bands;

	std::vector<int> hdr_himg; 
	std::vector<int> hdr_vimg; 
	std::vector<int> hdr_hroi; 
	std::vector<int> hdr_vroi;

	float hdr_fps; 
	float hdr_fps_qpf;
	double hdr_integrationtime;
	std::vector<int> hdr_binning;
	std::string hdr_trigger_mode; 
	bool hdr_trigger_sync; 
	std::vector<int> hdr_fodis; 
	std::string hdr_ID; 
	unsigned int hdr_acquisitionwindow_left; 
	unsigned int hdr_acquisitionwindow_top; 
	std::string	hdr_calibration_pack; 

	std::vector<float> hdr_temperature;
	std::vector<float> hdr_wavelength;
	std::vector<float> hdr_fwhm;

};
#endif // SPECIL_SPECIM_H#pragma once
