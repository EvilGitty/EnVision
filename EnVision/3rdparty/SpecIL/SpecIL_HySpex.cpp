#include "SpecIL_HySpex.h"

SpecIL_HySpex::~SpecIL_HySpex()
{
	this->cleanup();
};
//
SpecIL_HySpex::SpecIL_HySpex()
{
//	this->init();
	this->init_NEOheader();
};
//
void SpecIL_HySpex::init_NEOheader()
{
	size_t ii;
	// word                   = fread(fid,  8,'*char')';
	for (ii = 0; ii < 8; ii++)
		hdr_word[ii] = NULL;

	for (ii = 0; ii < 200; ii++)
	{
	// configFile             = fread(fid,200,'*char')';
	this->hdr_configFile[ii];
	// detectstring           = fread(fid,200,'*char')';
	this->hdr_detectstring[ii];
	// sensor                 = fread(fid,200,'*char')';
	this->hdr_sensor[ii];
	// framegrabber           = fread(fid,200,'*char')';
	this->hdr_framegrabber[ii];
	// ID                     = fread(fid,200,'*char')';
	this->hdr_ID[ii];
	// supplier               = fread(fid,200,'*char')';
	this->hdr_bufferSupplier[ii];
	// settingFile            = fread(fid,120,'*char')';
	// comment                = fread(fid,200,'*char')';
	this->hdr_comment[ii];
	// backgroundFile         = fread(fid,200,'*char')';
	this->hdr_backgroundFile[ii];
	};

	for (ii = 0; ii < 120; ii++)
	{
		this->hdr_settingFile[ii];
	};

	for (ii = 0; ii < 64; ii++)
	{
		// comport                = fread(fid, 64,'*char')';
		this->hdr_comport[ii];
	};

	for (ii = 0; ii < 32; ii++)
	{
		// leftGain               = fread(fid, 32,'*char')';
		this->hdr_bufferLeftGain[ii];
		// rightGain              = fread(fid, 32,'*char')';
		this->hdr_bufferRightGain[ii];
	};

	// hdrSize                = fread(fid,  1,'*int');
	this->hdr_hdrSize = NULL;
	// serialNumber           = fread(fid,  1,'*uint');
	this->hdr_serialNumber = NULL;
	// scalingFactor          = fread(fid,  1,'*double');
	this->hdr_scalingFactor = NULL;
	// electronics            = fread(fid,  1,'*uint');
	this->hdr_electronics = NULL;
	// comsettingsElectronics = fread(fid,  1,'*uint');
	this->hdr_comsettingsElectronics = NULL;
	// comportElectronics     = fread(fid, 44,'*char')';
	this->hdr_comportElectronics[44];
	// fanSpeed               = fread(fid,  1,'*uint');
	this->hdr_fanSpeed = NULL;
	// backTemperature        = fread(fid,  1,'*uint');
	this->hdr_backTemperature = NULL;
	// Pback                  = fread(fid,  1,'*uint');
	this->hdr_Pback = NULL;
	// Iback                  = fread(fid,  1,'*uint');
	this->hdr_Iback = NULL;
	// Dback                  = fread(fid,  1,'*uint');
	this->hdr_Dback = NULL;
	// recordHD               = fread(fid,  1,'*char')';
	this->hdr_recordHD = NULL;
	// unknownPOINTER         = fread(fid,  1,'*uint');    %4 byte pointer [useless] XCamera*m_hCam
	this->hdr_unknownPOINTER = NULL;
	// serverIndex            = fread(fid,  1,'*uint');
	this->hdr_serverIndex = NULL;
	// comsettings            = fread(fid,  1,'*uint');
	this->hdr_comsettings = NULL;
	// numberOfBackground     = fread(fid,  1,'*uint');
	this->hdr_numberOfBackground = NULL;
	// spectralSize           = fread(fid,  1,'*uint');
	this->hdr_spectralSize = NULL;
	// spatialSize            = fread(fid,  1,'*uint');
	this->hdr_spatialSize = NULL;
	// binning                = fread(fid,  1,'*uint');
	this->hdr_binning = NULL;
	// detected               = fread(fid,  1,'*uint');
	this->hdr_detected = NULL;
	// integrationtime        = fread(fid,  1,'*uint');
	this->hdr_integrationtime = NULL;
	// frameperiod            = fread(fid,  1,'*uint');
	this->hdr_frameperiod = NULL;
	// defaultR               = fread(fid,  1,'*uint');
	this->hdr_defaultR = NULL;
	// defaultG               = fread(fid,  1,'*uint');
	this->hdr_defaultG = NULL;
	// defaultB               = fread(fid,  1,'*uint');
	this->hdr_defaultB = NULL;
	// bitshift               = fread(fid,  1,'*uint');
	this->hdr_bitshift = NULL;
	// temperatureOffset      = fread(fid,  1,'*uint');
	this->hdr_temperatureOffset = NULL;
	// shutter                = fread(fid,  1,'*uint');
	this->hdr_shutter = NULL;
	// backgroundPresent      = fread(fid,  1,'*uint');
	this->hdr_backgroundPresent = NULL;
	// power                  = fread(fid,  1,'*uint');
	this->hdr_power = NULL;
	// current                = fread(fid,  1,'*uint');
	this->hdr_current = NULL;
	// bias                   = fread(fid,  1,'*uint');
	this->hdr_bias = NULL;
	// bandwidth              = fread(fid,  1,'*uint');
	this->hdr_bandwidth = NULL;
	// vin                    = fread(fid,  1,'*uint');
	this->hdr_vin = NULL;
	// vref                   = fread(fid,  1,'*uint');
	this->hdr_vref = NULL;
	// sensorVin              = fread(fid,  1,'*uint');
	this->hdr_sensorVin = NULL;
	// sensorVref             = fread(fid,  1,'*uint');
	this->hdr_sensorVref = NULL;
	// coolingTemperature     = fread(fid,  1,'*uint');
	this->hdr_coolingTemperature = NULL;
	// windowStart            = fread(fid,  1,'*uint');
	this->hdr_windowStart = NULL;
	// windowStop             = fread(fid,  1,'*uint');
	this->hdr_windowStop = NULL;
	// readoutTime            = fread(fid,  1,'*uint');
	this->hdr_readoutTime = NULL;
	// p                      = fread(fid,  1,'*uint');
	this->hdr_p = NULL;
	// i                      = fread(fid,  1,'*uint');
	this->hdr_i = NULL;
	// d                      = fread(fid,  1,'*uint');
	this->hdr_d = NULL;
	// numberOfFrames         = fread(fid,  1,'*uint');
	this->hdr_numberOfFrames = NULL;
	// nobp                   = fread(fid,  1,'*uint');
	this->hdr_nobp = NULL;
	// dw                     = fread(fid,  1,'*uint');
	this->hdr_dw = NULL;
	// EQ                     = fread(fid,  1,'*uint');
	this->hdr_EQ = NULL;
	// lens                   = fread(fid,  1,'*uint');
	this->hdr_lens = NULL;
	// FOVexp                 = fread(fid,  1,'*uint');
	this->hdr_FOVexp = NULL;
	// scanningMode           = fread(fid,  1,'*uint');
	this->hdr_scanningMode = NULL;
	// calibAvailable         = fread(fid,  1,'*uint');
	this->hdr_calibAvailable = NULL;
	// numberOfAvg            = fread(fid,  1,'*uint');
	this->hdr_numberOfAvg = NULL;
	// SF                     = fread(fid,  1,'*double');
	this->hdr_SF = NULL;
	// apertureSize           = fread(fid,  1,'*double');
	this->hdr_apertureSize = NULL;
	// pixelSizeX             = fread(fid,  1,'*double');
	this->hdr_pixelSizeX = NULL;
	// pixelSizeY             = fread(fid,  1,'*double');
	this->hdr_pixelSizeY = NULL;
	// temperature            = fread(fid,  1,'*double');
	this->hdr_temperature = NULL;
	// maxFramerate           = fread(fid,  1,'*double');
	this->hdr_maxFramerate = NULL;
	// spectralCalibPOINTER   = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = spectralSize*sizeof(double)
	this->hdr_spectralCalibPOINTER = NULL;
	// REPOINTER              = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = spectralSize*spatialSize*sizeof(double)
	this->hdr_REPOINTER = NULL;
	// QEPOINTER              = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = spectralSize*sizeof(double)
	this->hdr_QEPOINTER = NULL;
	// backgroundPOINTER      = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = spatialSize*spectralSize*sizeof(double)
	this->hdr_backgroundPOINTER = NULL;
	// badPixelsPOINTER       = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = nobp*sizeof(uint)
	this->hdr_badPixelsPOINTER = NULL;
	// imageFormat            = fread(fid,  1,'*uint');
	this->hdr_imageFormat = NULL;

	// spectralVector         = fread(fid,// spectralSize,'*double');
	this->hdr_spectralVectorSize = 0;
	this->hdr_spectralVectorBuffer = NULL;

	// QE                     = fread(fid,// spectralSize,'*double');
	this->hdr_QESize = 0;
	this->hdr_QEBuffer = NULL;

	// RE                     = fread(fid,// spectralSize*// spatialSize,'*double');
	this->hdr_RESize = 0;
	this->hdr_REBuffer = NULL;

	// background             = fread(fid,// spatialSize*// spectralSize,'*double');
	this->hdr_backgroundSize = 0;
	this->hdr_backgroundBuffer = NULL;

	// badPixels              = fread(fid,// nobp,'*uint');
	this->hdr_badPixelsSize = 0;
	this->hdr_badPixelsBuffer = NULL;
};
//
void SpecIL_HySpex::cleanup()
{
	if (this->hdr_spectralVectorBuffer != NULL)
	{
		delete[] this->hdr_spectralVectorBuffer;
		this->hdr_spectralVectorBuffer = NULL;
	};

	// Werden in SpecIL_Base frei gegeben!
	this->hdr_QEBuffer = NULL;
	this->hdr_REBuffer = NULL;
	this->hdr_backgroundBuffer = NULL;
	this->hdr_badPixelsBuffer = NULL;
};
//
int SpecIL_HySpex::read()
{
	// Datei oeffnen testen
	std::ifstream ifs(this->SpecHeader.filename.c_str(), std::ifstream::in|std::ifstream::binary);
	if(ifs.is_open() != false)
	{
		// Fileheader einlesen
		if (this->readFileHeader() == 0)
		{
			// Hier jetzt die Headerwerte in den ENVI Header zuordnen

			this->SpecHeader.headsize = (unsigned long long)this->hdr_hdrSize;
			this->SpecHeader.serialNumber = this->hdr_serialNumber;
			this->SpecHeader.scalingFactor = this->hdr_scalingFactor;
			this->SpecHeader.ID = this->hdr_ID;
			this->SpecHeader.imgsize[1] = (unsigned long long)this->hdr_spectralSize;
			this->SpecHeader.imgsize[0] = (unsigned long long)this->hdr_spatialSize;
			this->SpecHeader.Integration_time = (double)this->hdr_integrationtime;
			this->SpecHeader.Frameperiod = (double)this->hdr_frameperiod;
			this->SpecHeader.pixelSizeX = this->hdr_pixelSizeX;
			this->SpecHeader.pixelSizeY = this->hdr_pixelSizeY;
			this->SpecHeader.nobp = this->hdr_nobp;

			// Interleave
			switch (this->hdr_imageFormat)
			{
			case 3: this->SpecHeader.interleave = t_SpecHead::IL_BIL;
				break;
			case 2: this->SpecHeader.interleave = t_SpecHead::IL_BSQ;
				break;
			case 1: this->SpecHeader.interleave = t_SpecHead::IL_BIP;
				break;
			default:this->SpecHeader.interleave = t_SpecHead::IL_BIL;
			};

			// steht nicht explizit im header drin, aber die Daten waren von den NEO Kameras bis jetzt immer 16Bit Integers(.hyspex) oder floats (.img)
			std::string endung = this->SpecHeader.filename.substr(this->SpecHeader.filename.find_last_of("."), std::string::npos);
			if (endung == ".hyspex")
			{
				this->SpecHeader.data_type = t_SpecHead::DT_16_UINT;
				this->SpecHeader.pixelsize = 2;
			}
			else if (endung == ".img" || endung == ".bin")
			{
				this->SpecHeader.data_type = t_SpecHead::DT_32_FLOAT;
				this->SpecHeader.pixelsize = 4;
			};

			// Wellenlaengen da?
			if (this->hdr_spectralVectorSize > 0)
			{
				double wavelength = 0;
				for (int i = 0; i < this->hdr_spectralVectorSize; i = i + 8)
				{
					((char*)&wavelength)[0] = this->hdr_spectralVectorBuffer[i + 0];
					((char*)&wavelength)[1] = this->hdr_spectralVectorBuffer[i + 1];
					((char*)&wavelength)[2] = this->hdr_spectralVectorBuffer[i + 2];
					((char*)&wavelength)[3] = this->hdr_spectralVectorBuffer[i + 3];
					((char*)&wavelength)[4] = this->hdr_spectralVectorBuffer[i + 4];
					((char*)&wavelength)[5] = this->hdr_spectralVectorBuffer[i + 5];
					((char*)&wavelength)[6] = this->hdr_spectralVectorBuffer[i + 6];
					((char*)&wavelength)[7] = this->hdr_spectralVectorBuffer[i + 7];

					this->SpecHeader.wavelen.push_back((float)wavelength);
				};
			};

			// Pointer fuer die Arrays
			this->SpecHeader.QEarraySize = (unsigned long long)this->hdr_QESize;
			this->SpecHeader.QEarray = this->hdr_QEBuffer;

			this->SpecHeader.REarraySize = (unsigned long long)this->hdr_RESize;
			this->SpecHeader.REarray = this->hdr_REBuffer;

			this->SpecHeader.BGarraySize = (unsigned long long)this->hdr_backgroundSize;
			this->SpecHeader.BGarray = this->hdr_backgroundBuffer;

			this->SpecHeader.BadPixelsarraySize = (unsigned long long)this->hdr_badPixelsSize;
			this->SpecHeader.BadPixelsarray = this->hdr_badPixelsBuffer;

			// ENVI Header Datei ".hdr" einlesen und ggf. die Werte uebernehmen
			if (this->readENVIhdr() != 0)
			{
				std::string emsg;
				emsg = "Warning in SpecIL_HySpex::read(): No .hdr was read!";
				this->ErrorMsgLog(emsg);
			};

			this->setDataTypeMaxMin();

			// Daten lesen
			this->readImageData();

			return 0;
		};
	};

	ifs.close();
	std::string emsg;
	emsg = "In SpecIL_HySpex::read():Konte Datei " + this->SpecHeader.filename + " nicht oeffnen";
	this->ErrorMsgLog(emsg);
	return -1;
};
//
int SpecIL_HySpex::readFileHeader()
{
	// Datei oeffnen
	std::ifstream ifs(this->SpecHeader.filename.c_str(), std::ifstream::in|std::ifstream::binary);
	if(ifs.is_open() == false)
	{
		std::string emsg;
		emsg = "In SpecIL_HySpex::readFileHeader(): Konte Datei " + this->SpecHeader.filename + " nicht oeffnen";
		this->ErrorMsgLog(emsg);
		ifs.close();
		return -1;
	};
	// Prüfen, ob es eine HySpex Datei ist
	// word                   = fread(fid,  8,'*char')';
	char buffer8[8];
	ifs.read(buffer8, 8);
	char checkbuffer[] = {'H', 'Y', 'S', 'P', 'E', 'X', 0x00, 0x00};
	


	if(*buffer8 == *checkbuffer)
	{
		std::memcpy(this->hdr_word, buffer8, 8);

		// Headergroesse MUSS vorhanden sein!
		// hdrSize                = fread(fid,  1,'*int');
		this->SpecHeader.headsize = 0;
		char buffer4[4];
		ifs.read(buffer4, sizeof(buffer4));
		long size;
		((char*) &size)[0] = buffer4[0];
		((char*) &size)[1] = buffer4[1];
		((char*) &size)[2] = buffer4[2];
		((char*) &size)[3] = buffer4[3];
		this->hdr_hdrSize = size;

		// serialNumber           = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long serialNumber;
		((char*)&serialNumber)[0] = buffer4[0];
		((char*)&serialNumber)[1] = buffer4[1];
		((char*)&serialNumber)[2] = buffer4[2];
		((char*)&serialNumber)[3] = buffer4[3];
		this->hdr_serialNumber = serialNumber;

		// configFile             = fread(fid,200,'*char')';
		ifs.read(this->hdr_configFile, 200);

		// settingFile            = fread(fid,120,'*char')';
		ifs.read(this->hdr_settingFile, 120);

		// scalingFactor          = fread(fid,  1,'*double');
		ifs.read(buffer8, sizeof(buffer8));
		double scalingFactor;
		((char*)&scalingFactor)[0] = buffer8[0];
		((char*)&scalingFactor)[1] = buffer8[1];
		((char*)&scalingFactor)[2] = buffer8[2];
		((char*)&scalingFactor)[3] = buffer8[3];
		((char*)&scalingFactor)[4] = buffer8[4];
		((char*)&scalingFactor)[5] = buffer8[5];
		((char*)&scalingFactor)[6] = buffer8[6];
		((char*)&scalingFactor)[7] = buffer8[7];
		this->hdr_scalingFactor = scalingFactor;

		// electronics            = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long electronics;
		((char*)&electronics)[0] = buffer4[0];
		((char*)&electronics)[1] = buffer4[1];
		((char*)&electronics)[2] = buffer4[2];
		((char*)&electronics)[3] = buffer4[3];
		this->hdr_electronics = electronics;

		// comsettingsElectronics = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long comsettingsElectronics;
		((char*)&comsettingsElectronics)[0] = buffer4[0];
		((char*)&comsettingsElectronics)[1] = buffer4[1];
		((char*)&comsettingsElectronics)[2] = buffer4[2];
		((char*)&comsettingsElectronics)[3] = buffer4[3];
		this->hdr_comsettingsElectronics = comsettingsElectronics;

		// comportElectronics     = fread(fid, 44,'*char')';
		ifs.read(this->hdr_comportElectronics, 44);

		// fanSpeed               = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long fanSpeed;
		((char*)&fanSpeed)[0] = buffer4[0];
		((char*)&fanSpeed)[1] = buffer4[1];
		((char*)&fanSpeed)[2] = buffer4[2];
		((char*)&fanSpeed)[3] = buffer4[3];
		this->hdr_fanSpeed = fanSpeed;

		// backTemperature        = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long backTemperature;
		((char*)&backTemperature)[0] = buffer4[0];
		((char*)&backTemperature)[1] = buffer4[1];
		((char*)&backTemperature)[2] = buffer4[2];
		((char*)&backTemperature)[3] = buffer4[3];
		this->hdr_backTemperature = backTemperature;

		// Pback                  = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long Pback;
		((char*)&Pback)[0] = buffer4[0];
		((char*)&Pback)[1] = buffer4[1];
		((char*)&Pback)[2] = buffer4[2];
		((char*)&Pback)[3] = buffer4[3];
		this->hdr_Pback = Pback;

		// Iback                  = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long Iback;
		((char*)&Iback)[0] = buffer4[0];
		((char*)&Iback)[1] = buffer4[1];
		((char*)&Iback)[2] = buffer4[2];
		((char*)&Iback)[3] = buffer4[3];
		this->hdr_Iback = Iback;

		// Dback                  = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long Dback;
		((char*)&Dback)[0] = buffer4[0];
		((char*)&Dback)[1] = buffer4[1];
		((char*)&Dback)[2] = buffer4[2];
		((char*)&Dback)[3] = buffer4[3];
		this->hdr_Dback = Dback;

		// comport                = fread(fid, 64,'*char')';
		ifs.read(this->hdr_comport, 64);

		// detectstring           = fread(fid,200,'*char')';
		ifs.read(this->hdr_detectstring, 200);

		// sensor                 = fread(fid,200,'*char')';
		ifs.read(this->hdr_sensor, 200);

		// framegrabber           = fread(fid,200,'*char')';
		ifs.read(this->hdr_framegrabber, 200);

		// ID                     = fread(fid,200,'*char')';
		ifs.read(this->hdr_ID, 200);

		// supplier               = fread(fid,200,'*char')';
		ifs.read(this->hdr_bufferSupplier, 200);

		// leftGain               = fread(fid, 32,'*char')';
		ifs.read(this->hdr_bufferLeftGain, 32);

		// rightGain              = fread(fid, 32,'*char')';
		ifs.read(this->hdr_bufferRightGain, 32);

		// comment                = fread(fid,200,'*char')';
		ifs.read(this->hdr_comment, 200);

		// backgroundFile         = fread(fid,200,'*char')';
		ifs.read(this->hdr_backgroundFile, 200);

		// recordHD               = fread(fid,  1,'*char')';
		ifs.read(&(this->hdr_recordHD), 1);

		// unknownPOINTER         = fread(fid,  1,'*uint');    %4 byte pointer [useless] XCamera*m_hCam
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long unknownPOINTER;
		((char*)&unknownPOINTER)[0] = buffer4[0];
		((char*)&unknownPOINTER)[1] = buffer4[1];
		((char*)&unknownPOINTER)[2] = buffer4[2];
		((char*)&unknownPOINTER)[3] = buffer4[3];
		this->hdr_unknownPOINTER = unknownPOINTER;

		// serverIndex            = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long serverIndex;
		((char*)&serverIndex)[0] = buffer4[0];
		((char*)&serverIndex)[1] = buffer4[1];
		((char*)&serverIndex)[2] = buffer4[2];
		((char*)&serverIndex)[3] = buffer4[3];
		this->hdr_serverIndex = serverIndex;

		// comsettings            = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long comsettings;
		((char*)&comsettings)[0] = buffer4[0];
		((char*)&comsettings)[1] = buffer4[1];
		((char*)&comsettings)[2] = buffer4[2];
		((char*)&comsettings)[3] = buffer4[3];
		this->hdr_comsettings = comsettings;

		// numberOfBackground     = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long numberOfBackground;
		((char*)&numberOfBackground)[0] = buffer4[0];
		((char*)&numberOfBackground)[1] = buffer4[1];
		((char*)&numberOfBackground)[2] = buffer4[2];
		((char*)&numberOfBackground)[3] = buffer4[3];
		this->hdr_numberOfBackground = numberOfBackground;

		// spectralSize           = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long spectralSize;
		((char*)&spectralSize)[0] = buffer4[0];
		((char*)&spectralSize)[1] = buffer4[1];
		((char*)&spectralSize)[2] = buffer4[2];
		((char*)&spectralSize)[3] = buffer4[3];
		this->hdr_spectralSize = spectralSize;

		// spatialSize            = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long spatialSize;
		((char*)&spatialSize)[0] = buffer4[0];
		((char*)&spatialSize)[1] = buffer4[1];
		((char*)&spatialSize)[2] = buffer4[2];
		((char*)&spatialSize)[3] = buffer4[3];
		this->hdr_spatialSize = spatialSize;

		// binning                = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long binning;
		((char*)&binning)[0] = buffer4[0];
		((char*)&binning)[1] = buffer4[1];
		((char*)&binning)[2] = buffer4[2];
		((char*)&binning)[3] = buffer4[3];
		this->hdr_binning = binning;

		// detected               = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long detected;
		((char*)&detected)[0] = buffer4[0];
		((char*)&detected)[1] = buffer4[1];
		((char*)&detected)[2] = buffer4[2];
		((char*)&detected)[3] = buffer4[3];
		this->hdr_detected = detected;

		// integrationtime        = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long integrationtime;
		((char*)&integrationtime)[0] = buffer4[0];
		((char*)&integrationtime)[1] = buffer4[1];
		((char*)&integrationtime)[2] = buffer4[2];
		((char*)&integrationtime)[3] = buffer4[3];
		this->hdr_integrationtime = integrationtime;

		// frameperiod            = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long frameperiod;
		((char*)&frameperiod)[0] = buffer4[0];
		((char*)&frameperiod)[1] = buffer4[1];
		((char*)&frameperiod)[2] = buffer4[2];
		((char*)&frameperiod)[3] = buffer4[3];
		this->hdr_frameperiod = frameperiod;

		// defaultR               = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long defaultR;
		((char*)&defaultR)[0] = buffer4[0];
		((char*)&defaultR)[1] = buffer4[1];
		((char*)&defaultR)[2] = buffer4[2];
		((char*)&defaultR)[3] = buffer4[3];
		this->hdr_defaultR = defaultR;

		// defaultG               = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long defaultG;
		((char*)&defaultG)[0] = buffer4[0];
		((char*)&defaultG)[1] = buffer4[1];
		((char*)&defaultG)[2] = buffer4[2];
		((char*)&defaultG)[3] = buffer4[3];
		this->hdr_defaultG = defaultG;

		// defaultB               = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long defaultB;
		((char*)&defaultB)[0] = buffer4[0];
		((char*)&defaultB)[1] = buffer4[1];
		((char*)&defaultB)[2] = buffer4[2];
		((char*)&defaultB)[3] = buffer4[3];
		this->hdr_defaultB = defaultB;

		// bitshift               = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long bitshift;
		((char*)&bitshift)[0] = buffer4[0];
		((char*)&bitshift)[1] = buffer4[1];
		((char*)&bitshift)[2] = buffer4[2];
		((char*)&bitshift)[3] = buffer4[3];
		this->hdr_bitshift = bitshift;

		// temperatureOffset      = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long temperatureOffset;
		((char*)&temperatureOffset)[0] = buffer4[0];
		((char*)&temperatureOffset)[1] = buffer4[1];
		((char*)&temperatureOffset)[2] = buffer4[2];
		((char*)&temperatureOffset)[3] = buffer4[3];
		this->hdr_temperatureOffset = temperatureOffset;

		// shutter                = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long shutter;
		((char*)&shutter)[0] = buffer4[0];
		((char*)&shutter)[1] = buffer4[1];
		((char*)&shutter)[2] = buffer4[2];
		((char*)&shutter)[3] = buffer4[3];
		this->hdr_shutter = shutter;

		// backgroundPresent      = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long backgroundPresent;
		((char*)&backgroundPresent)[0] = buffer4[0];
		((char*)&backgroundPresent)[1] = buffer4[1];
		((char*)&backgroundPresent)[2] = buffer4[2];
		((char*)&backgroundPresent)[3] = buffer4[3];
		this->hdr_backgroundPresent = backgroundPresent;

		// power                  = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long power;
		((char*)&power)[0] = buffer4[0];
		((char*)&power)[1] = buffer4[1];
		((char*)&power)[2] = buffer4[2];
		((char*)&power)[3] = buffer4[3];
		this->hdr_power = power;

		// current                = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long current;
		((char*)&current)[0] = buffer4[0];
		((char*)&current)[1] = buffer4[1];
		((char*)&current)[2] = buffer4[2];
		((char*)&current)[3] = buffer4[3];
		this->hdr_current = current;

		// bias                   = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long bias;
		((char*)&bias)[0] = buffer4[0];
		((char*)&bias)[1] = buffer4[1];
		((char*)&bias)[2] = buffer4[2];
		((char*)&bias)[3] = buffer4[3];
		this->hdr_bias = bias;

		// bandwidth              = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long bandwidth;
		((char*)&bandwidth)[0] = buffer4[0];
		((char*)&bandwidth)[1] = buffer4[1];
		((char*)&bandwidth)[2] = buffer4[2];
		((char*)&bandwidth)[3] = buffer4[3];
		this->hdr_bandwidth = bandwidth;

		// vin                    = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long vin;
		((char*)&vin)[0] = buffer4[0];
		((char*)&vin)[1] = buffer4[1];
		((char*)&vin)[2] = buffer4[2];
		((char*)&vin)[3] = buffer4[3];
		this->hdr_vin = vin;

		// vref                   = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long vref;
		((char*)&vref)[0] = buffer4[0];
		((char*)&vref)[1] = buffer4[1];
		((char*)&vref)[2] = buffer4[2];
		((char*)&vref)[3] = buffer4[3];
		this->hdr_vref = vref;

		// sensorVin              = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long sensorVin;
		((char*)&sensorVin)[0] = buffer4[0];
		((char*)&sensorVin)[1] = buffer4[1];
		((char*)&sensorVin)[2] = buffer4[2];
		((char*)&sensorVin)[3] = buffer4[3];
		this->hdr_sensorVin = sensorVin;

		// sensorVref             = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long sensorVref;
		((char*)&sensorVref)[0] = buffer4[0];
		((char*)&sensorVref)[1] = buffer4[1];
		((char*)&sensorVref)[2] = buffer4[2];
		((char*)&sensorVref)[3] = buffer4[3];
		this->hdr_sensorVref = sensorVref;

		// coolingTemperature     = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long coolingTemperature;
		((char*)&coolingTemperature)[0] = buffer4[0];
		((char*)&coolingTemperature)[1] = buffer4[1];
		((char*)&coolingTemperature)[2] = buffer4[2];
		((char*)&coolingTemperature)[3] = buffer4[3];
		this->hdr_coolingTemperature = coolingTemperature;

		// windowStart            = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long windowStart;
		((char*)&windowStart)[0] = buffer4[0];
		((char*)&windowStart)[1] = buffer4[1];
		((char*)&windowStart)[2] = buffer4[2];
		((char*)&windowStart)[3] = buffer4[3];
		this->hdr_windowStart = windowStart;

		// windowStop             = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long windowStop;
		((char*)&windowStop)[0] = buffer4[0];
		((char*)&windowStop)[1] = buffer4[1];
		((char*)&windowStop)[2] = buffer4[2];
		((char*)&windowStop)[3] = buffer4[3];
		this->hdr_windowStop = windowStop;

		// readoutTime            = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long readoutTime;
		((char*)&readoutTime)[0] = buffer4[0];
		((char*)&readoutTime)[1] = buffer4[1];
		((char*)&readoutTime)[2] = buffer4[2];
		((char*)&readoutTime)[3] = buffer4[3];
		this->hdr_readoutTime = readoutTime;

		// p                      = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long hdrp;
		((char*)&hdrp)[0] = buffer4[0];
		((char*)&hdrp)[1] = buffer4[1];
		((char*)&hdrp)[2] = buffer4[2];
		((char*)&hdrp)[3] = buffer4[3];
		this->hdr_p = hdrp;

		// i                      = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long hdri;
		((char*)&hdri)[0] = buffer4[0];
		((char*)&hdri)[1] = buffer4[1];
		((char*)&hdri)[2] = buffer4[2];
		((char*)&hdri)[3] = buffer4[3];
		this->hdr_i = hdri;

		// d                      = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long hdrd;
		((char*)&hdrd)[0] = buffer4[0];
		((char*)&hdrd)[1] = buffer4[1];
		((char*)&hdrd)[2] = buffer4[2];
		((char*)&hdrd)[3] = buffer4[3];
		this->hdr_i = hdri;

		// numberOfFrames         = fread(fid,  1,'*uint');
		ifs.read(buffer4, sizeof(buffer4));
		unsigned long numberOfFrames;
		((char*)&numberOfFrames)[0] = buffer4[0];
		((char*)&numberOfFrames)[1] = buffer4[1];
		((char*)&numberOfFrames)[2] = buffer4[2];
		((char*)&numberOfFrames)[3] = buffer4[3];
		this->hdr_numberOfFrames = numberOfFrames;

		if (this->hdr_hdrSize > 2077)
		{
			// nobp                   = fread(fid,  1,'*uint');
			ifs.read(buffer4, sizeof(buffer4));
			unsigned long nobp;
			((char*)&nobp)[0] = buffer4[0];
			((char*)&nobp)[1] = buffer4[1];
			((char*)&nobp)[2] = buffer4[2];
			((char*)&nobp)[3] = buffer4[3];
			this->hdr_nobp = nobp;

			// dw                     = fread(fid,  1,'*uint');
			ifs.read(buffer4, sizeof(buffer4));
			unsigned long dw;
			((char*)&dw)[0] = buffer4[0];
			((char*)&dw)[1] = buffer4[1];
			((char*)&dw)[2] = buffer4[2];
			((char*)&dw)[3] = buffer4[3];
			this->hdr_dw = dw;

			// EQ                     = fread(fid,  1,'*uint');
			ifs.read(buffer4, sizeof(buffer4));
			unsigned long EQ;
			((char*)&EQ)[0] = buffer4[0];
			((char*)&EQ)[1] = buffer4[1];
			((char*)&EQ)[2] = buffer4[2];
			((char*)&EQ)[3] = buffer4[3];
			this->hdr_EQ = EQ;

			// lens                   = fread(fid,  1,'*uint');
			ifs.read(buffer4, sizeof(buffer4));
			unsigned long lens;
			((char*)&lens)[0] = buffer4[0];
			((char*)&lens)[1] = buffer4[1];
			((char*)&lens)[2] = buffer4[2];
			((char*)&lens)[3] = buffer4[3];
			this->hdr_lens = lens;

			// FOVexp                 = fread(fid,  1,'*uint');
			ifs.read(buffer4, sizeof(buffer4));
			unsigned long FOVexp;
			((char*)&FOVexp)[0] = buffer4[0];
			((char*)&FOVexp)[1] = buffer4[1];
			((char*)&FOVexp)[2] = buffer4[2];
			((char*)&FOVexp)[3] = buffer4[3];
			this->hdr_FOVexp = FOVexp;

			// scanningMode           = fread(fid,  1,'*uint');
			ifs.read(buffer4, sizeof(buffer4));
			unsigned long scanningMode;
			((char*)&scanningMode)[0] = buffer4[0];
			((char*)&scanningMode)[1] = buffer4[1];
			((char*)&scanningMode)[2] = buffer4[2];
			((char*)&scanningMode)[3] = buffer4[3];
			this->hdr_scanningMode = scanningMode;

			// calibAvailable         = fread(fid,  1,'*uint');
			ifs.read(buffer4, sizeof(buffer4));
			unsigned long calibAvailable;
			((char*)&calibAvailable)[0] = buffer4[0];
			((char*)&calibAvailable)[1] = buffer4[1];
			((char*)&calibAvailable)[2] = buffer4[2];
			((char*)&calibAvailable)[3] = buffer4[3];
			this->hdr_calibAvailable = calibAvailable;

			// numberOfAvg            = fread(fid,  1,'*uint');
			ifs.read(buffer4, sizeof(buffer4));
			unsigned long numberOfAvg;
			((char*)&numberOfAvg)[0] = buffer4[0];
			((char*)&numberOfAvg)[1] = buffer4[1];
			((char*)&numberOfAvg)[2] = buffer4[2];
			((char*)&numberOfAvg)[3] = buffer4[3];
			this->hdr_numberOfAvg = numberOfAvg;

			// SF                     = fread(fid,  1,'*double');
			ifs.read(buffer8, sizeof(buffer8));
			double SF;
			((char*)&SF)[0] = buffer8[0];
			((char*)&SF)[1] = buffer8[1];
			((char*)&SF)[2] = buffer8[2];
			((char*)&SF)[3] = buffer8[3];
			((char*)&SF)[4] = buffer8[4];
			((char*)&SF)[5] = buffer8[5];
			((char*)&SF)[6] = buffer8[6];
			((char*)&SF)[7] = buffer8[7];
			this->hdr_SF = SF;

			// apertureSize           = fread(fid,  1,'*double');
			ifs.read(buffer8, sizeof(buffer8));
			double apertureSize;
			((char*)&apertureSize)[0] = buffer8[0];
			((char*)&apertureSize)[1] = buffer8[1];
			((char*)&apertureSize)[2] = buffer8[2];
			((char*)&apertureSize)[3] = buffer8[3];
			((char*)&apertureSize)[4] = buffer8[4];
			((char*)&apertureSize)[5] = buffer8[5];
			((char*)&apertureSize)[6] = buffer8[6];
			((char*)&apertureSize)[7] = buffer8[7];
			this->hdr_apertureSize = apertureSize;

			// pixelSizeX             = fread(fid,  1,'*double');
			ifs.read(buffer8, sizeof(buffer8));
			double pixelSizeX;
			((char*)&pixelSizeX)[0] = buffer8[0];
			((char*)&pixelSizeX)[1] = buffer8[1];
			((char*)&pixelSizeX)[2] = buffer8[2];
			((char*)&pixelSizeX)[3] = buffer8[3];
			((char*)&pixelSizeX)[4] = buffer8[4];
			((char*)&pixelSizeX)[5] = buffer8[5];
			((char*)&pixelSizeX)[6] = buffer8[6];
			((char*)&pixelSizeX)[7] = buffer8[7];
			this->hdr_pixelSizeX = pixelSizeX;

			// pixelSizeY             = fread(fid,  1,'*double');
			ifs.read(buffer8, sizeof(buffer8));
			double pixelSizeY;
			((char*)&pixelSizeY)[0] = buffer8[0];
			((char*)&pixelSizeY)[1] = buffer8[1];
			((char*)&pixelSizeY)[2] = buffer8[2];
			((char*)&pixelSizeY)[3] = buffer8[3];
			((char*)&pixelSizeY)[4] = buffer8[4];
			((char*)&pixelSizeY)[5] = buffer8[5];
			((char*)&pixelSizeY)[6] = buffer8[6];
			((char*)&pixelSizeY)[7] = buffer8[7];
			this->hdr_pixelSizeY = pixelSizeY;

			// temperature            = fread(fid,  1,'*double');
			ifs.read(buffer8, sizeof(buffer8));
			double temperature;
			((char*)&temperature)[0] = buffer8[0];
			((char*)&temperature)[1] = buffer8[1];
			((char*)&temperature)[2] = buffer8[2];
			((char*)&temperature)[3] = buffer8[3];
			((char*)&temperature)[4] = buffer8[4];
			((char*)&temperature)[5] = buffer8[5];
			((char*)&temperature)[6] = buffer8[6];
			((char*)&temperature)[7] = buffer8[7];
			this->hdr_temperature = temperature;

			// maxFramerate           = fread(fid,  1,'*double');
			ifs.read(buffer8, sizeof(buffer8));
			double maxFramerate;
			((char*)&maxFramerate)[0] = buffer8[0];
			((char*)&maxFramerate)[1] = buffer8[1];
			((char*)&maxFramerate)[2] = buffer8[2];
			((char*)&maxFramerate)[3] = buffer8[3];
			((char*)&maxFramerate)[4] = buffer8[4];
			((char*)&maxFramerate)[5] = buffer8[5];
			((char*)&maxFramerate)[6] = buffer8[6];
			((char*)&maxFramerate)[7] = buffer8[7];
			this->hdr_maxFramerate = maxFramerate;

			// spectralCalibPOINTER   = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = spectralSize*sizeof(double)
			ifs.read(buffer4, sizeof(buffer4));
			long spectralCalibPOINTER;
			((char*)&spectralCalibPOINTER)[0] = buffer4[0];
			((char*)&spectralCalibPOINTER)[1] = buffer4[1];
			((char*)&spectralCalibPOINTER)[2] = buffer4[2];
			((char*)&spectralCalibPOINTER)[3] = buffer4[3];
			this->hdr_spectralCalibPOINTER = spectralCalibPOINTER;

			// REPOINTER              = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = spectralSize*spatialSize*sizeof(double)
			ifs.read(buffer4, sizeof(buffer4));
			long REPOINTER;
			((char*)&REPOINTER)[0] = buffer4[0];
			((char*)&REPOINTER)[1] = buffer4[1];
			((char*)&REPOINTER)[2] = buffer4[2];
			((char*)&REPOINTER)[3] = buffer4[3];
			this->hdr_REPOINTER = REPOINTER;

			// QEPOINTER              = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = spectralSize*sizeof(double)
			ifs.read(buffer4, sizeof(buffer4));
			long QEPOINTER;
			((char*)&QEPOINTER)[0] = buffer4[0];
			((char*)&QEPOINTER)[1] = buffer4[1];
			((char*)&QEPOINTER)[2] = buffer4[2];
			((char*)&QEPOINTER)[3] = buffer4[3];
			this->hdr_QEPOINTER = QEPOINTER;

			// backgroundPOINTER      = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = spatialSize*spectralSize*sizeof(double)
			ifs.read(buffer4, sizeof(buffer4));
			long backgroundPOINTER;
			((char*)&backgroundPOINTER)[0] = buffer4[0];
			((char*)&backgroundPOINTER)[1] = buffer4[1];
			((char*)&backgroundPOINTER)[2] = buffer4[2];
			((char*)&backgroundPOINTER)[3] = buffer4[3];
			this->hdr_backgroundPOINTER = backgroundPOINTER;

			// badPixelsPOINTER       = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = nobp*sizeof(uint)
			ifs.read(buffer4, sizeof(buffer4));
			long badPixelsPOINTER;
			((char*)&badPixelsPOINTER)[0] = buffer4[0];
			((char*)&badPixelsPOINTER)[1] = buffer4[1];
			((char*)&badPixelsPOINTER)[2] = buffer4[2];
			((char*)&badPixelsPOINTER)[3] = buffer4[3];
			this->hdr_badPixelsPOINTER = badPixelsPOINTER;

			// imageFormat            = fread(fid,  1,'*uint');
			ifs.read(buffer4, sizeof(buffer4));
			unsigned long imageFormat;
			((char*)&imageFormat)[0] = buffer4[0];
			((char*)&imageFormat)[1] = buffer4[1];
			((char*)&imageFormat)[2] = buffer4[2];
			((char*)&imageFormat)[3] = buffer4[3];
			this->hdr_imageFormat = imageFormat;

			if (this->hdr_hdrSize > 2181)
			{

				// spectralVector         = fread(fid,// spectralSize,'*double');
				this->hdr_spectralVectorSize = 8 * spectralSize;
				this->hdr_spectralVectorBuffer = new char[this->hdr_spectralVectorSize];
				ifs.read(this->hdr_spectralVectorBuffer, this->hdr_spectralVectorSize);

				/*size_t bufferwavelensize = 0;
				if (this->SpecHeader.headsize > 2181)
				{
				ifs.seekg(2181); // 2169 + 12
				bufferwavelensize = 8 * spectralSize; // 8 Byte pro Wert
				char* bufferwavelen = new char[bufferwavelensize];
				ifs.read(bufferwavelen, bufferwavelensize);
				// vom buffer in den Vektor
				double wavelength = 0;
				for (int i = 0; i < bufferwavelensize; i = i + 8)
				{
				((char*)&wavelength)[0] = bufferwavelen[i + 0];
				((char*)&wavelength)[1] = bufferwavelen[i + 1];
				((char*)&wavelength)[2] = bufferwavelen[i + 2];
				((char*)&wavelength)[3] = bufferwavelen[i + 3];
				((char*)&wavelength)[4] = bufferwavelen[i + 4];
				((char*)&wavelength)[5] = bufferwavelen[i + 5];
				((char*)&wavelength)[6] = bufferwavelen[i + 6];
				((char*)&wavelength)[7] = bufferwavelen[i + 7];

				this->SpecHeader.wavelen.push_back((float)wavelength);
				};
				delete[] bufferwavelen;
				};*/

				this->hdr_QESize = 8 * this->hdr_spectralSize;
				if (this->hdr_hdrSize > (2181 + this->hdr_QESize))
				{
					// QE                     = fread(fid,// spectralSize,'*double');
					this->hdr_QEBuffer = new char[this->hdr_QESize];
					ifs.read(this->hdr_QEBuffer, this->hdr_QESize);

					/*this->SpecHeader.QEarraySize = 0;
					if (this->SpecHeader.headsize > (2181 + bufferwavelensize))
					{
					ifs.seekg(2181 + bufferwavelensize);

					this->SpecHeader.QEarraySize = this->SpecHeader.imgsize[1] * 8;

					this->SpecHeader.QEarray = static_cast<void*>(new char[this->SpecHeader.QEarraySize]);

					ifs.read((char*)this->SpecHeader.QEarray, this->SpecHeader.QEarraySize);
					};*/

					this->hdr_RESize = 8 * this->hdr_spectralSize * this->hdr_spatialSize;
					if (this->hdr_hdrSize > (2181 + this->hdr_QESize + this->hdr_RESize))
					{
						// RE                     = fread(fid,// spectralSize*// spatialSize,'*double');
						this->hdr_REBuffer = new char[this->hdr_RESize];
						ifs.read(this->hdr_REBuffer, this->hdr_RESize);
						/*this->SpecHeader.REarraySize = 0;
						if (this->SpecHeader.headsize > (2181 + bufferwavelensize + this->SpecHeader.QEarraySize))
						{
						ifs.seekg(2181 + bufferwavelensize + this->SpecHeader.QEarraySize);

						this->SpecHeader.REarraySize = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * 8;

						this->SpecHeader.REarray = static_cast<void*>(new char[this->SpecHeader.REarraySize]);

						ifs.read((char*)this->SpecHeader.REarray, this->SpecHeader.REarraySize);
						};*/

						this->hdr_backgroundSize = 8 * this->hdr_spectralSize * this->hdr_spatialSize;
						if (this->hdr_hdrSize > (2181 + this->hdr_QESize + this->hdr_RESize + this->hdr_backgroundSize))
						{
							// background             = fread(fid,// spatialSize*// spectralSize,'*double');
							this->hdr_backgroundBuffer = new char[this->hdr_backgroundSize];
							ifs.read(this->hdr_backgroundBuffer, this->hdr_backgroundSize);
							/*this->SpecHeader.BGarraySize = 0;
							if (this->SpecHeader.headsize > (2181 + bufferwavelensize + this->SpecHeader.QEarraySize + this->SpecHeader.REarraySize))
							{
							ifs.seekg(2181 + bufferwavelensize + this->SpecHeader.QEarraySize + this->SpecHeader.REarraySize);

							this->SpecHeader.BGarraySize = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * 8;

							this->SpecHeader.BGarray = static_cast<void*>(new char[this->SpecHeader.BGarraySize]);

							ifs.read((char*)this->SpecHeader.BGarray, this->SpecHeader.BGarraySize);
							};*/

							this->hdr_badPixelsSize = this->hdr_nobp * 4;
							if (this->hdr_hdrSize > (2181 + this->hdr_QESize + this->hdr_RESize + this->hdr_backgroundSize + this->hdr_badPixelsSize))
							{
								// badPixels              = fread(fid,// nobp,'*uint');
								this->hdr_badPixelsBuffer = new char[this->hdr_badPixelsSize];
								ifs.read(this->hdr_badPixelsBuffer, this->hdr_badPixelsSize);
								/*if (this->SpecHeader.headsize > (2181 + bufferwavelensize + this->SpecHeader.QEarraySize + this->SpecHeader.REarraySize + (unsigned long long)nobp))
								{
								ifs.seekg(2181 + bufferwavelensize + this->SpecHeader.QEarraySize + this->SpecHeader.REarraySize + (unsigned long long)nobp);

								this->SpecHeader.BadPixelsarraySize = (unsigned long long)nobp * 4;

								this->SpecHeader.BadPixelsarray = static_cast<void*>(new char[this->SpecHeader.BadPixelsarraySize]);

								ifs.read((char*)this->SpecHeader.BadPixelsarray, this->SpecHeader.BadPixelsarraySize);
								};*/
							};
						};
					};
				};
			};
		};
		/*
		// Alte Implementierung
		if(this->SpecHeader.headsize > 1961)
		{
			// Anzahl der Kanaele
			//int ifspos1 = ifs.tellg();
			ifs.seekg(1961); //ifspos1 + 1949
			ifs.read(buffer4, sizeof(buffer4));
			unsigned int spectralchannels;
			((char*) &spectralchannels)[0] = buffer4[0];
			((char*) &spectralchannels)[1] = buffer4[1];
			((char*) &spectralchannels)[2] = buffer4[2];
			((char*) &spectralchannels)[3] = buffer4[3];

			this->SpecHeader.imgsize[1] = spectralchannels;

			if(this->SpecHeader.headsize > 1965)
			{
				// Raeumliche Aufloesung
				// 1965 -> kein seekg noetig
				ifs.read(buffer4, sizeof(buffer4));
				unsigned int spatialpixels;
				((char*) &spatialpixels)[0] = buffer4[0];
				((char*) &spatialpixels)[1] = buffer4[1];
				((char*) &spatialpixels)[2] = buffer4[2];
				((char*) &spatialpixels)[3] = buffer4[3];

				this->SpecHeader.imgsize[0] = spatialpixels;

				if(this->SpecHeader.headsize > 2073)
				{
					// Aufnahmenummer (frame)
					//int ifspos2 = ifs.tellg();
					ifs.seekg(2073); //ifspos2 + 4*26
					ifs.read(buffer4, sizeof(buffer4));
					unsigned int framenumber;
					((char*) &framenumber)[0] = buffer4[0];
					((char*) &framenumber)[1] = buffer4[1];
					((char*) &framenumber)[2] = buffer4[2];
					((char*) &framenumber)[3] = buffer4[3];

					this->SpecHeader.imgsize[2] = framenumber;

					// Wellenlaengen drin?
					size_t bufferwavelensize = 0;
					if(this->SpecHeader.headsize > 2181)
					{
						ifs.seekg(2181); // 2169 + 12
						bufferwavelensize = 8 * spectralchannels; // 8 Byte pro Wert
						char* bufferwavelen = new char[bufferwavelensize];
						ifs.read(bufferwavelen, bufferwavelensize);
						// vom buffer in den Vektor
						double wavelength = 0;
						for(int i = 0; i < bufferwavelensize; i = i + 8)
						{
							((char*) &wavelength)[0] = bufferwavelen[i + 0];
							((char*) &wavelength)[1] = bufferwavelen[i + 1];
							((char*) &wavelength)[2] = bufferwavelen[i + 2];
							((char*) &wavelength)[3] = bufferwavelen[i + 3];
							((char*) &wavelength)[4] = bufferwavelen[i + 4];
							((char*) &wavelength)[5] = bufferwavelen[i + 5];
							((char*) &wavelength)[6] = bufferwavelen[i + 6];
							((char*) &wavelength)[7] = bufferwavelen[i + 7];

							this->SpecHeader.wavelen.push_back( (float) wavelength);
						};
						delete( bufferwavelen );
					};

					// QE
					this->SpecHeader.QEarraySize = 0;
					if (this->SpecHeader.headsize > (2181 + bufferwavelensize))
					{
						ifs.seekg(2181 + bufferwavelensize);

						this->SpecHeader.QEarraySize = this->SpecHeader.imgsize[1] * 8;

						this->SpecHeader.QEarray = static_cast<void*>(new char[this->SpecHeader.QEarraySize]);

						ifs.read((char*)this->SpecHeader.QEarray, this->SpecHeader.QEarraySize);
					};

					// RE
					this->SpecHeader.REarraySize = 0;
					if (this->SpecHeader.headsize > (2181 + bufferwavelensize + this->SpecHeader.QEarraySize))
					{
						ifs.seekg(2181 + bufferwavelensize + this->SpecHeader.QEarraySize);

						this->SpecHeader.REarraySize = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * 8;

						this->SpecHeader.REarray = static_cast<void*>(new char[this->SpecHeader.REarraySize]);

						ifs.read((char*)this->SpecHeader.REarray, this->SpecHeader.REarraySize);
					};

					// BG
					this->SpecHeader.BGarraySize = 0;
					if (this->SpecHeader.headsize > (2181 + bufferwavelensize + this->SpecHeader.QEarraySize + this->SpecHeader.REarraySize))
					{
						ifs.seekg(2181 + bufferwavelensize + this->SpecHeader.QEarraySize + this->SpecHeader.REarraySize);

						this->SpecHeader.BGarraySize = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * 8;

						this->SpecHeader.BGarray = static_cast<void*>(new char[this->SpecHeader.BGarraySize]);

						ifs.read((char*)this->SpecHeader.BGarray, this->SpecHeader.BGarraySize);
					};
				};
			};
		};*/
	}
	else
	{
		std::string emsg;
		emsg = "Warning in SpecIL_HySpex::readFileHeader(): In File " + this->SpecHeader.filename + " is no HYSPEX keyword.";
		this->ErrorMsgLog(emsg);
		ifs.close();

		return -1;
	};

	this->FileHeaderLoaded = 1;

	ifs.close();
	return 0;
};
//
int SpecIL_HySpex::readImageData()
{
	std::ifstream ifs(this->SpecHeader.filename.c_str(), std::ifstream::in|std::ifstream::binary);
	if(ifs.is_open() == false)
	{
		std::string emsg;
		emsg = "In SpecIL_HySpex::readImageData: Konnte Datei " + this->SpecHeader.filename + " nicht oeffnen";
		this->ErrorMsgLog(emsg);
		ifs.close();
		return -1;
	};

	if(this->FileDataLoaded == 0)
	{
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
			try{
				this->SpecHeader.imgcube = static_cast<void*>(	new char[imagedatesize]	);
			}
			catch(const std::bad_alloc&)
			{
				ifs.close();
				this->ErrorMsgLog(std::string("In SpecIL_HySpex::readImageData(): Datei zu groß fuer Speicher -> std::bad_alloc"));

				this->SpecHeader.imgcube = NULL;
				this->SpecHeader.type = 2;

				return -1;
			};
			// Vom Filestream in der Buffer schreiben
			ifs.seekg( this->SpecHeader.headsize, ifs.beg );
			ifs.read(static_cast<char*>(this->SpecHeader.imgcube), imagedatesize);

			// Check Failbits
			if(ifs.eof())
			{
				this->ErrorMsgLog(std::string("In SpecIL_HySpex::readImageData(): ifs.eof() == true ! -> End-of-File reached on input operation"));
				ifs.close();
				delete[] this->SpecHeader.imgcube;
				return -1;
			};
			if(ifs.bad())
			{
				this->ErrorMsgLog(std::string("In SpecIL_HySpex::readImageData(): ifs.bad() == true ! -> Read-writing error on i-o operation or Logical error on i-o operation !"));
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
	emsg = "In SpecIL_HySpex::readImageData: Konnte Datei " + this->SpecHeader.filename + " nicht oeffnen";
	this->ErrorMsgLog(emsg);
	ifs.close();
	return -1;
};