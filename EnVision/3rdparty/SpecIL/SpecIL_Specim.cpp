#include "SpecIL_Specim.h"

SpecIL_Specim::~SpecIL_Specim()
{
	this->cleanup();
};
//
SpecIL_Specim::SpecIL_Specim()
{
	//this->init_SPECIMheader();
};

//
void SpecIL_Specim::init_SPECIMheader()				//triggert through class instantation
{
		std::string hdr_sensor_type = "";			//sensor type = FX10 , Lumo - Recorder v2017-490
		std::string hdr_acquisition_date = "";		//acquisition date = DATE(yyyy-mm-dd): 2018-01-24
		std::string hdr_start_time = "";			//Start Time = UTC TIME: 22:47:35
		std::string hdr_stop_time = "";				//Stop Time = UTC TIME: 22:47:55

		unsigned long long hdr_spectralSize = 1;	//bands = 224
		unsigned long long hdr_spatialSize = 1;		//samples = 512
		unsigned long long hdr_numberOfFrames =1;

		std::vector<string> hdr_errors = {"none"}; //errors = {none}

		std::string hdr_imageFormat = "bil";// Interleave: BIL, BSQ, BIP
		unsigned int hdr_data_type = 12; //data type = 12
		unsigned int  hdr_hdrSize = 0; //header offset = 0
		unsigned int  hdr_byte_order = 0;  //byte order = 0
		unsigned int  hdr_x_start = 0; //x start = 0
		unsigned int  hdr_y_start = 0; //y start = 0
		std::vector<int> hdr_default_bands = {1, 1, 1};//default bands = {89, 59, 1}

		std::vector<int> hdr_himg = { 1, 1};  //himg = {1, 512}
		std::vector<int> hdr_vimg = { 1, 1 }; //vimg = {1, 224}
		std::vector<int> hdr_hroi = { 1, 1 }; //hroi = {1, 512}
		std::vector<int> hdr_vroi = { 1, 1 }; //vroi = {1, 224}

		double hdr_fps = 0; // fps = 16.00
		double hdr_fps_qpf = 0; // fps_qpf = 16.05
		double hdr_integrationtime = 0; // tint = 49.000000
		std::vector<int> hdr_binning = { 1, 1 };//binning = {2, 2}}
		std::string hdr_trigger_mode = "Internal"; //trigger mode = Internal
		bool hdr_trigger_sync = 1; //trigger sync = true (only swir)
		std::vector<int> hdr_fodis = {0, 0}; //fodis = { 0, 0 }
		std::string hdr_ID = 0; // sensorid = 1200057
		unsigned int hdr_acquisitionwindow_left = 0; //  = 0
		unsigned int hdr_acquisitionwindow_top = 0; //  = 0
		std::string	hdr_calibration_pack = ""; //= C: / Users / Public / Documents / Specim / 461055_20171031_oles15.scp

		std::vector<double> hdr_temperature = {0, 0, 0, 0}; //= {/*151.00,28.21,25.70,30.35,26.30}*/
		std::vector<double> hdr_spectralVectorSize; //wavelengths

	return;
};
//
void SpecIL_Specim::cleanup()
{

};
//
int SpecIL_Specim::read()			// triggered by user module (e.g. Imagefile::imageRecord.SpecData->read();)
{									//all local class parameters  are handed over to this->SpecHeader.interleave which is then access outside of SpecIL by the User

										// ENVI Header Datei ".hdr" einlesen und ggf. die Werte uebernehmen
		if (this->readENVIhdr2() != 0)
		{
			std::string emsg;
			emsg = "Warning in SpecIL_Specim::read(): No .hdr was read!";
			this->ErrorMsgLog(emsg);
		}

		// Datei oeffnen testen
		std::ifstream ifs(this->SpecHeader.filename.c_str(), std::ifstream::in | std::ifstream::binary);
		if (ifs.is_open() == 1) {


			if (0 == this->SpecHeader.fileext.compare(".raw")){
				if (this->readFileHeaderRaw() == 0) {
					this->setDataTypeMaxMin();
					this->readImageData();
					return 0;
				};
			}

			if (0 == this->SpecHeader.fileext.compare(".img")) {
				if (this->readFileHeaderRaw() == 0) {
					this->setDataTypeMaxMin();
					this->readImageData();
					return 0;
				};
			}
		}else{
			ifs.close();
			std::string emsg;
			emsg = "In SpecIL_Specim::read():Konte Datei " + this->SpecHeader.filename + " nicht oeffnen";
			this->ErrorMsgLog(emsg);
		}


	return -1;
};

int SpecIL_Specim::readFileHeaderRaw()
{

	//nothing
	return 0;
};

int SpecIL_Specim::readFileHeaderImg()
{
	return 0;
};

//
int SpecIL_Specim::readImageData()
{

		std::ifstream ifs(this->SpecHeader.filename.c_str(), std::ifstream::in | std::ifstream::binary);
		if (ifs.is_open() == false)
		{
			std::string emsg;
			emsg = "In SpecIL_Specim::readImageData: Konnte Datei " + this->SpecHeader.filename + " nicht oeffnen";
			this->ErrorMsgLog(emsg);
			ifs.close();
			return -1;
		};

		if (this->FileDataLoaded == 0)
		{

			//debug
			/*
			(unsigned long long)this->SpecHeader.headsize = 0;
			this->cubemaxsize = 500000;
			this->ReadOnlyFromHDD = 0;

			this->SpecHeader.pixelsize = 4;
			this->SpecHeader.imgsize[0] = 512;
			this->SpecHeader.imgsize[1] = 224;
			this->SpecHeader.imgsize[2] = 316;
			*/

			// Groesse der Datei ermitteln
			ifs.seekg(0, ifs.end);
			unsigned long long filesize = ifs.tellg();
			ifs.seekg(0, ifs.beg);

			// bis ca 1GB erlaubt, dann auf Datei arbeiten!
			// Das muss hier noch huebscher geregelt werden
			if (((filesize - ((unsigned long long)this->SpecHeader.headsize)) < this->cubemaxsize) && this->ReadOnlyFromHDD == 0)
			{
				// Buffergroesse bestimmen
				unsigned long long imagedatesize = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[2];

				// Buffer allokieren
				try {
					this->SpecHeader.imgcube = static_cast<void*>(new char[imagedatesize]);
				}
				catch (const std::bad_alloc&)
				{
					ifs.close();
					this->ErrorMsgLog(std::string("In SpecIL_Specim::readImageData(): Datei zu groß fuer Speicher -> std::bad_alloc"));

					this->SpecHeader.imgcube = NULL;
					this->SpecHeader.type = 2;

					return -1;
				};
				// Vom Filestream in der Buffer schreiben
				ifs.seekg(this->SpecHeader.headsize, ifs.beg);
				ifs.read(static_cast<char*>(this->SpecHeader.imgcube), imagedatesize);

				// Check Failbits
				if (ifs.eof())
				{
					this->ErrorMsgLog(std::string("In SpecIL_Specim::readImageData(): ifs.eof() == true ! -> End-of-File reached on input operation"));
					ifs.close();
					delete[] this->SpecHeader.imgcube;
					return -1;
				};
				if (ifs.bad())
				{
					this->ErrorMsgLog(std::string("In SpecIL_Specim::readImageData(): ifs.bad() == true ! -> Read-writing error on i-o operation or Logical error on i-o operation !"));
					ifs.close();
					delete[] this->SpecHeader.imgcube;
					return -1;
				};

				// Bilddaten nun geladen
				this->SpecHeader.type = 1;
			}
			else
			{
				// Bilddaten nicht in den Speicher geladen
				this->SpecHeader.imgcube = NULL;
				this->SpecHeader.type = 2;
			};
			ifs.close();
			this->FileDataLoaded = 1;
			return 0;
		};

		std::string emsg;
		emsg = "In SpecIL_Specim::readImageData: Konnte Datei " + this->SpecHeader.filename + " nicht oeffnen";
		this->ErrorMsgLog(emsg);
		ifs.close();
	
	return -1;
};