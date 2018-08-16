#include "SpecIL_Base.h"
#include <fstream>
#include <stdio.h>

// OpenCV
//#include <opencv2/core/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui/highgui.hpp>

SpecIL_Base::~SpecIL_Base()
{
	this->CleanMemory();
};
//
SpecIL_Base::SpecIL_Base()
{
	this->init();
};
//
t_SpecHead* SpecIL_Base::getHeaderPointer()
{
	return &SpecHeader;
};
t_SpecHead* SpecIL_Base::getHeader()
{
	return &SpecHeader;
};
//
int SpecIL_Base::init()
{
	this->cubemaxsize = 3500000000; // ~3,5GB
	// ------------------------------------------------------------------------
	// FLAGs
	this->FileMode = 0;
	this->FileDataLoaded = 0;
	this->FileHeaderLoaded = 0;
	this->ProfileLoaded = 0;
	this->NewFileData = 0;
	this->ReadOnlyFromHDD = 0;
	this->UsingErrorLog = false;
	this->ENVIhdrLoaded = false;
	// ------------------------------------------------------------------------


	this->OutputProfile = 0;
	this->SelectedImgProperties = 0;

	// SpecHeader
	this->SpecHeader.filename = "";
	this->SpecHeader.type = 0;
	this->SpecHeader.imgcube = NULL;
	this->SpecHeader.headsize = 0;
	this->SpecHeader.numdim = 3;
	this->SpecHeader.imgsize[0] = 0;
	this->SpecHeader.imgsize[1] = 0;
	this->SpecHeader.imgsize[2] = 0;
	this->SpecHeader.interleave = t_SpecHead::IL_UNKNOWN;
	this->SpecHeader.data_type = t_SpecHead::DT_UNKNOWN;
	this->SpecHeader.data_type_str = "DT_UNKNOWN";
	this->SpecHeader.byte_order = t_SpecHead::BO_UNKNOWN;
	this->SpecHeader.bitdepth = 0;
	this->SpecHeader.pixelsize = 0;
	this->SpecHeader.maxval = 0;
	this->SpecHeader.ID = "SpecIL_Object";
	this->SpecHeader.wavelen.clear();
	this->SpecHeader.wavelenunit = "";
	this->SpecHeader.exposureTimeUS.clear();
	this->SpecHeader.data_type_maxval = 0.0;
	this->SpecHeader.data_type_minval = 0.0;
	this->SpecHeader.Frameperiod = 0.0;
	this->SpecHeader.Integration_time = 0.0;
	this->SpecHeader.QEarray = NULL;
	this->SpecHeader.REarray = NULL;
	this->SpecHeader.BGarray = NULL;
	this->SpecHeader.QEarraySize = 0;
	this->SpecHeader.REarraySize = 0;
	this->SpecHeader.BGarraySize = 0;


	this->SpecHeader.BadPixelsarray = NULL;
	this->SpecHeader.BadPixelsarraySize = 0;
	this->SpecHeader.nobp = 0;
	this->SpecHeader.serialNumber = 0;
	this->SpecHeader.scalingFactor = 0.0;
	this->SpecHeader.apertureSize = 0.0;
	this->SpecHeader.SF = 0.0;

	this->SpecHeader.pixelSizeX = 0.0;
	this->SpecHeader.pixelSizeY = 0.0;



	return 0;
};
//
int SpecIL_Base::CleanMemory()
{
	if (this->SpecHeader.imgcube != NULL)
	{
		delete[] this->SpecHeader.imgcube;
	};
	this->SpecHeader.imgcube = NULL;

	this->SpecHeader.wavelen.clear();
	this->SpecHeader.exposureTimeUS.clear();

	if (this->SpecHeader.QEarray != NULL)
	{
		delete[] this->SpecHeader.QEarray;
		this->SpecHeader.QEarray = NULL;
	};

	if (this->SpecHeader.REarray != NULL)
	{
		delete[] this->SpecHeader.REarray;
		this->SpecHeader.REarray = NULL;
	};

	if (this->SpecHeader.BGarray != NULL)
	{
		delete[] this->SpecHeader.BGarray;
		this->SpecHeader.BGarray = NULL;
	};

	if (this->SpecHeader.BadPixelsarray != NULL)
	{
		delete[] this->SpecHeader.BadPixelsarray;
		this->SpecHeader.BadPixelsarray = NULL;
	};

	return 0;
};
//
void SpecIL_Base::CopyHeaderFrom(t_SpecHead HeaderSource)
{
//	this->SpecHeader = HeaderSource;// so infach geht das leider nicht.......

	this->SpecHeader.type = 2;
	this->SpecHeader.ID = HeaderSource.ID;
	this->SpecHeader.wavelenunit = HeaderSource.wavelenunit;
	this->SpecHeader.wavelen = HeaderSource.wavelen;
	this->SpecHeader.exposureTimeUS = HeaderSource.exposureTimeUS;
	this->SpecHeader.numdim = HeaderSource.numdim;
	this->SpecHeader.imgsize[0] = HeaderSource.imgsize[0];
	this->SpecHeader.imgsize[1] = HeaderSource.imgsize[1];
	this->SpecHeader.imgsize[2] = HeaderSource.imgsize[2];

	this->SpecHeader.interleave = HeaderSource.interleave;
	this->setDataType(HeaderSource.data_type);

	this->SpecHeader.data_type_maxval = HeaderSource.data_type_maxval;
	this->SpecHeader.data_type_minval = HeaderSource.data_type_minval;
	this->SpecHeader.byte_order = HeaderSource.byte_order;

	this->SpecHeader.maxval = HeaderSource.maxval;
	this->SpecHeader.Frameperiod = HeaderSource.Frameperiod;
	this->SpecHeader.Integration_time = HeaderSource.Integration_time;
	this->SpecHeader.pixelSizeX = HeaderSource.pixelSizeX;
	this->SpecHeader.pixelSizeY = HeaderSource.pixelSizeY;

	this->SpecHeader.nobp = HeaderSource.nobp;
	this->SpecHeader.serialNumber = HeaderSource.serialNumber;
	this->SpecHeader.scalingFactor = HeaderSource.scalingFactor;
	this->SpecHeader.SF = HeaderSource.SF;
	this->SpecHeader.apertureSize = HeaderSource.apertureSize;

	this->SpecHeader.QEarraySize = 0;
	this->SpecHeader.REarraySize = 0;
	this->SpecHeader.BGarraySize = 0;
	this->SpecHeader.BadPixelsarraySize = 0;

	//this->SpecHeader.QEarray;
	//this->SpecHeader.REarray;
	//this->SpecHeader.BGarray;
	//this->SpecHeader.BadPixelsarray;
	//this->SpecHeader.imgcube;

};
//
int SpecIL_Base::copyQEfrom(void* QEarray, size_t QESize)
{
	if (QEarray != NULL && QESize > 0)
	{
		this->SpecHeader.QEarraySize = (unsigned long long)QESize;
		this->SpecHeader.QEarray = new char[this->SpecHeader.QEarraySize];
		std::memcpy(this->SpecHeader.QEarray, QEarray, this->SpecHeader.QEarraySize);
	};
	return 0;
};
int SpecIL_Base::copyREfrom(void* REarray, size_t RESize)
{
	if (REarray != NULL && RESize > 0)
	{
		this->SpecHeader.REarraySize = (unsigned long long)RESize;
		this->SpecHeader.REarray = new char[this->SpecHeader.REarraySize];
		std::memcpy(this->SpecHeader.REarray, REarray, this->SpecHeader.REarraySize);
	};
	return 0;
};
int SpecIL_Base::copyBGfrom(void* BEarray, size_t BESize)
{
	if (BEarray != NULL && BESize > 0)
	{
		this->SpecHeader.BGarraySize = (unsigned long long)BESize;
		this->SpecHeader.BGarray = new char[this->SpecHeader.BGarraySize];
		std::memcpy(this->SpecHeader.BGarray, BEarray, this->SpecHeader.BGarraySize);
	};
	return 0;
};
int SpecIL_Base::copyBadPixelfrom(void* BadPixelarray, size_t BadPixelSize)
{
	if (BadPixelarray != NULL && BadPixelSize > 0)
	{
		this->SpecHeader.BadPixelsarraySize = (unsigned long long)BadPixelSize;
		this->SpecHeader.BadPixelsarray = new char[this->SpecHeader.BadPixelsarraySize];
		std::memcpy(this->SpecHeader.BadPixelsarray, BadPixelarray, this->SpecHeader.BadPixelsarraySize);
	};
	return 0;
};
//
void SpecIL_Base::ErrorMsgLog(std::string errmsg)
{
	if (this->UsingErrorLog == true)
	{
		//Logdatei
		std::string file = this->SpecHeader.filename;

		size_t len = file.find_last_of(".");

		std::string logfile = file.substr(0, len);

		logfile = logfile + "_SpecIL_ERROR_LOG" + ".txt";

		std::fstream fsError(logfile, std::fstream::out | std::fstream::app);

		fsError << errmsg << std::endl;

		fsError.close();
	};
	// Anwendungsbsp:
	// this->ErrorMsgLog(std::string("HALLOLOOL"));
};
//
void SpecIL_Base::setReadOnlyFromHDD()
{
	this->ReadOnlyFromHDD = 1;
};
//
int SpecIL_Base::setProfile(std::string profile)
{
	// Startzustand: RAW Profil
	if (profile.compare("Standard") == 0)
	{
		this->OutputProfile = 0;
		return 0;
	};
	if (profile.compare("CWorkflow") == 0)
	{
		this->OutputProfile = 1;
		return 0;
	};
	//Err
	this->ErrorMsgLog("In SpecIL_Base::setProfile(): Invalid string parameter.");
	return -1;
};
//
void SpecIL_Base::setImageProperties(const char* id, int width, int height, int planes, t_SpecHead::t_interleave il, t_SpecHead::t_data_type dt)
{
	this->SpecHeader.ID = std::string(id);
	this->SpecHeader.interleave = il;
	this->SpecHeader.data_type = dt;
	this->SpecHeader.imgsize[0] = width;
	this->SpecHeader.imgsize[1] = planes;
	this->SpecHeader.imgsize[2] = height;


	if (this->SpecHeader.data_type == t_SpecHead::DT_8_BYTE)
	{
		this->SpecHeader.pixelsize = 1;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_16_SINT || this->SpecHeader.data_type == t_SpecHead::DT_16_UINT)
	{
		this->SpecHeader.pixelsize = 2;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_32_SLONG || this->SpecHeader.data_type == t_SpecHead::DT_32_FLOAT || this->SpecHeader.data_type == t_SpecHead::DT_32_ULONG)
	{
		this->SpecHeader.pixelsize = 4;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_64_DOUBLE || this->SpecHeader.data_type == t_SpecHead::DT_2x32_COMPLEX || this->SpecHeader.data_type == t_SpecHead::DT_64_SLONG || this->SpecHeader.data_type == t_SpecHead::DT_64_ULONG)
	{
		this->SpecHeader.pixelsize = 8;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_2x64_COMPLEX)
	{
		this->SpecHeader.pixelsize = 16;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_UNKNOWN)
	{
		this->SpecHeader.pixelsize = 0;
	};

	this->setDataTypeMaxMin();

	this->SelectedImgProperties = 2;
};
//
void SpecIL_Base::setID(const char* id)
{
	this->SpecHeader.ID = std::string(id);
};
//
void SpecIL_Base::setWavelen(std::vector <float> wavelen)
{
	this->SpecHeader.wavelen = wavelen;
};
//
void SpecIL_Base::setExposureTimeUS(std::vector <float> exposureTimeUS)
{
	this->SpecHeader.exposureTimeUS = exposureTimeUS;
};
//
int SpecIL_Base::loadProfile()
{
	// RAW
	if (this->OutputProfile == 0)
	{
		this->ProfileLoaded = 0;	// oder doch 0 ? Weil ja eigentlich das RAW Profil kein richtiges Profil ist...
		return 0;
	};

	// CWorkflow
	if (this->OutputProfile == 1)
	{
		this->ProfileLoaded = 1;
		return 0;
	};

	//Err
	this->ErrorMsgLog("In SpecIL_Base::loadProfile()");
	return -1;
};
//
int SpecIL_Base::readENVIhdr()
{
	int posFileExt = this->SpecHeader.filename.find_last_of(".") + 1;
	if(posFileExt != this->SpecHeader.filename.npos)
	{
		std::string fileExt = this->SpecHeader.filename.substr(posFileExt);

		// Ueberpruefen ob gueltige Endung
		if (fileExt == "img" || fileExt == "bin" || fileExt == "cue" || fileExt == "hyspex")
		{
			std::string hdrstring = this->SpecHeader.filename.substr(0, posFileExt);
			//hdrstring.replace(posFileExt, 3, "hdr");

			hdrstring = hdrstring + "hdr";

			// ENVI Header oeffnen
			std::ifstream ifs(hdrstring);
			if(ifs.fail() == 0)
			{
				std::string a, b, c;
				char eq = NULL;
				int inum;
				double value_d;

				std::string line;
				while(std::getline(ifs, line))
				{
					if (line.find(" ID") == 0)
					{
						unsigned int pos_eq = line.find_first_of("=");
						std::string stID = line.substr(pos_eq+2);
						this->SpecHeader.ID = stID;
					};

					if (line.find(" Frameperiod") == 0)
					{
						std::stringstream ss(line);
						ss >> a >> eq >> value_d;

						this->SpecHeader.Frameperiod = value_d;
						value_d = 0.0;
						eq = NULL;
						a.clear();
					};

					if (line.find(" Integration time") == 0)
					{
						std::stringstream ss(line);
						ss >> a >> b >> eq >> value_d;

						this->SpecHeader.Integration_time = value_d;
						value_d = 0.0;
						eq = NULL;
						a.clear();
						b.clear();
					};

					if (line.find("interleave") == 0)
					{
						std::stringstream ss(line);
						ss >> a >> eq >> b;

							if(b.compare(std::string("bil")) == 0 ){
								this->SpecHeader.interleave = t_SpecHead::IL_BIL;
							};
							if(b.compare(std::string("bsq")) == 0 ){
								this->SpecHeader.interleave = t_SpecHead::IL_BSQ;
							};
							if(b.compare(std::string("bip")) == 0 ){
								this->SpecHeader.interleave = t_SpecHead::IL_BIP;
							};
							if(b.size() == 0){
								this->SpecHeader.interleave = t_SpecHead::IL_UNKNOWN;
							};

						eq = NULL;
						a.clear();
						b.clear();
					};

					if (line.find("data type") == 0)
					{
						std::stringstream ss(line);
						ss >> a >> b >> eq >> inum;

							switch (inum)
							{
							case 1:
								this->SpecHeader.data_type = t_SpecHead::DT_8_BYTE;
								this->SpecHeader.pixelsize = 1;
								break;
							case 2:
								this->SpecHeader.data_type = t_SpecHead::DT_16_SINT;
								this->SpecHeader.pixelsize = 2;
								break;
							case 3:
								this->SpecHeader.data_type = t_SpecHead::DT_32_SLONG;
								this->SpecHeader.pixelsize = 4;
								break;
							case 4:
								this->SpecHeader.data_type = t_SpecHead::DT_32_FLOAT;
								this->SpecHeader.pixelsize = 4;
								break;
							case 5:
								this->SpecHeader.data_type = t_SpecHead::DT_64_DOUBLE;
								this->SpecHeader.pixelsize = 8;
								break;
							case 6:
								this->SpecHeader.data_type = t_SpecHead::DT_2x32_COMPLEX;
								this->SpecHeader.pixelsize = 8;
								break;
							case 9:
								this->SpecHeader.data_type = t_SpecHead::DT_2x64_COMPLEX;
								this->SpecHeader.pixelsize = 16;
								break;
							case 12:
								this->SpecHeader.data_type = t_SpecHead::DT_16_UINT;
								this->SpecHeader.pixelsize = 2;
								break;
							case 13:
								this->SpecHeader.data_type = t_SpecHead::DT_32_ULONG;
								this->SpecHeader.pixelsize = 4;
								break;
							case 14:
								this->SpecHeader.data_type = t_SpecHead::DT_64_SLONG;
								this->SpecHeader.pixelsize = 8;
								break;
							case 15:
								this->SpecHeader.data_type = t_SpecHead::DT_64_ULONG;
								this->SpecHeader.pixelsize = 8;
								break;
							default:
								this->SpecHeader.data_type = t_SpecHead::DT_UNKNOWN;
								this->SpecHeader.pixelsize = 0;
							};
						inum = 0;
						eq = NULL;
						a.clear();
						b.clear();
					};

					if (line.find("byte order") == 0)
					{
						std::stringstream ss(line);
						ss >> a >> b >> eq >> inum;

						switch (inum)
						{
						case 0:
							this->SpecHeader.byte_order = t_SpecHead::BO_LSF;
							break;
						case 1:
							this->SpecHeader.byte_order = t_SpecHead::BO_MSF;
							break;
						default:
							this->SpecHeader.byte_order = t_SpecHead::BO_UNKNOWN;
						};
						inum = 0;
						eq = NULL;
						a.clear();
						b.clear();
					};

					if (line.find("header offset") == 0)
					{
						std::stringstream ss(line);
						ss >> a >> b >> eq >> inum;

						this->SpecHeader.headsize = (unsigned int) inum;

						inum = 0;
						eq = NULL;
						a.clear();
						b.clear();
					};

					if (line.find("samples") == 0)
					{
						std::stringstream ss(line);
						ss >> a >> eq >> inum;

							this->SpecHeader.imgsize[0] = (unsigned long long) inum;

						inum = 0;
						eq = NULL;
						a.clear();
					};

					if (line.find("lines") == 0)
					{
						std::stringstream ss(line);
						ss >> a >> eq >> inum;

							this->SpecHeader.imgsize[2] = (unsigned long long) inum;

						inum = 0;
						eq = NULL;
						a.clear();
					};

					if (line.find("bands") == 0)
					{
						std::stringstream ss(line);
						ss >> a >> eq >> inum;

							this->SpecHeader.imgsize[1] = (unsigned long long) inum;


						inum = 0;
						eq = NULL;
						a.clear();
					};

					if (line.find("wavelength units") == 0)
					{
						std::stringstream ss(line);
						ss >> a >> b >> eq >> c;

						this->SpecHeader.wavelenunit = c;

						inum = 0;
						eq = NULL;
						a.clear();
						b.clear();
						c.clear();
					};

					if (line.find("wavelength") == 0)
					{
						std::string wavelengths = line.substr(line.find_last_of("=")+1);

						std::string buf;
						buf.clear();

						// stehen schon Wellenlaengen in der Struktur??
						if(this->SpecHeader.wavelen.size()==0)
						{
							for (size_t i=0; i<wavelengths.size(); ++i)
							{
								if (wavelengths[i]=='{' || wavelengths[i]==' ' || wavelengths[i]==',' || wavelengths[i]=='}' || i==wavelengths.size()-1)
								{	
									if (buf.size()>0)
									{
										this->SpecHeader.wavelen.push_back((float)atof(buf.c_str()));
										buf.clear();
									};
								}
								else
								{
									buf.push_back(wavelengths[i]);
								};
							};
						};
					};

				};

				this->ENVIhdrLoaded = true;

				// Datei schliessen
				ifs.close();
				return 0;
			};
		};
	};

	// Err
	this->ErrorMsgLog("Warning in SpecIL_Base::readENVIhdr(): Cant open .hdr");
	return -1;
};
//
int SpecIL_Base::writeENVIhdr(std::string outhdrfile)
{
	std::fstream fsENVIhdroutfile;
	fsENVIhdroutfile.open(outhdrfile, std::fstream::out|std::fstream::binary);

	if(fsENVIhdroutfile.fail() == false)
	{
		int hsize = (int)this->SpecHeader.headsize;
		if (hsize > -1)
		{
			fsENVIhdroutfile << "ENVI" << std::endl;
			fsENVIhdroutfile << "description = { " << std::endl;
			if(this->SpecHeader.ID.size() > 0)
			{
				fsENVIhdroutfile << " ID = " << this->SpecHeader.ID << std::endl;
				fsENVIhdroutfile << " Frameperiod = " << this->SpecHeader.Frameperiod << std::endl;
				fsENVIhdroutfile << " Integration time = " << this->SpecHeader.Integration_time;
			};
			fsENVIhdroutfile << " }" << std::endl;
		
			fsENVIhdroutfile << "samples = " << this->SpecHeader.imgsize[0] << std::endl;
			fsENVIhdroutfile << "lines = " << this->SpecHeader.imgsize[2] << std::endl;
			fsENVIhdroutfile << "bands = " << this->SpecHeader.imgsize[1] << std::endl;
			fsENVIhdroutfile << "header offset = " << this->SpecHeader.headsize << std::endl;
			fsENVIhdroutfile << "data type = " << (int)this->SpecHeader.data_type << std::endl;
		
			if(this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
			{
				fsENVIhdroutfile << "interleave = bsq" << std::endl;
			};
			if(this->SpecHeader.interleave == t_SpecHead::IL_BIP)
			{
				fsENVIhdroutfile << "interleave = bip" << std::endl;
			};
			if(this->SpecHeader.interleave == t_SpecHead::IL_BIL)
			{
				fsENVIhdroutfile << "interleave = bil" << std::endl;
			};
			if(this->SpecHeader.interleave == t_SpecHead::IL_UNKNOWN)
			{
				fsENVIhdroutfile << "interleave = unknown" << std::endl;
			};
		
			if(this->SpecHeader.byte_order != t_SpecHead::BO_UNKNOWN)
			{
				fsENVIhdroutfile << "byte order = " << (int)this->SpecHeader.byte_order << std::endl;
			};
		
			if(this->SpecHeader.wavelen.size() > 0)
			{
				fsENVIhdroutfile << "wavelength units = nm" << std::endl;
				fsENVIhdroutfile << "wavelength  = {";
				for(unsigned int k=0; k<this->SpecHeader.wavelen.size(); k++)
				{
					fsENVIhdroutfile << this->SpecHeader.wavelen[k];
					if (k<this->SpecHeader.wavelen.size()-1)
					{
						fsENVIhdroutfile << ", ";
					};
				};
				fsENVIhdroutfile << "}" << std::endl;
			};

			fsENVIhdroutfile.close();
			return 0;
		}
		else
		{
			//Err
			this->ErrorMsgLog("In SpecIL_Base::writeENVIhdr(): No Headersize is given! First writing the datafile, then the .hdr!");
			return -1;
		};
	};

	this->ErrorMsgLog("In SpecIL_Base::writeENVIhdr(): Error write ENIV .hdr file!");
	return -1;
};
//
int SpecIL_Base::writeDataToHySpexFile(std::string outHySpexFile)
{
	std::string outfile = outHySpexFile;

	std::fstream fsDataOutfile;
	fsDataOutfile.open(outfile, std::fstream::in | std::fstream::out | std::fstream::trunc | std::fstream::binary);
	unsigned long outheadsize = 0;

	// word                   = fread(fid,  8,'*char')';
	char buffer8[8] = { 'H', 'Y', 'S', 'P', 'E', 'X', 0x00, 0x00 };
	fsDataOutfile.write(buffer8, 8);
	outheadsize = outheadsize + 8;

	// hdrSize                = fread(fid,  1,'*int');
	char outheadsizebuffer4[4];
	outheadsizebuffer4[0] = ((char*)&(outheadsize))[0];
	outheadsizebuffer4[1] = ((char*)&(outheadsize))[1];
	outheadsizebuffer4[2] = ((char*)&(outheadsize))[2];
	outheadsizebuffer4[3] = ((char*)&(outheadsize))[3];
	fsDataOutfile.write(outheadsizebuffer4, 4);
	outheadsize = outheadsize + 4;

	// serialNumber           = fread(fid,  1,'*uint');
	char buffer4[4];
	unsigned long SerNum = (unsigned long)this->SpecHeader.serialNumber;
	buffer4[0] = ((char*)&SerNum)[0];
	buffer4[1] = ((char*)&SerNum)[1];
	buffer4[2] = ((char*)&SerNum)[2];
	buffer4[3] = ((char*)&SerNum)[3];
	fsDataOutfile.write(buffer4, 4);
	outheadsize = outheadsize + 4;

	// configFile             = fread(fid,200,'*char')';
	// settingFile            = fread(fid,120,'*char')';
	char buffer320[320];
	for (size_t iii = 0; iii < 320; iii++){
		buffer320[iii] = NULL;
	};
	fsDataOutfile.write(buffer320, 320);
	outheadsize = outheadsize + 320;

	// scalingFactor          = fread(fid,  1,'*double');
	buffer8[0] = ((char*)&(this->SpecHeader.scalingFactor))[0];
	buffer8[1] = ((char*)&(this->SpecHeader.scalingFactor))[1];
	buffer8[2] = ((char*)&(this->SpecHeader.scalingFactor))[2];
	buffer8[3] = ((char*)&(this->SpecHeader.scalingFactor))[3];
	buffer8[4] = ((char*)&(this->SpecHeader.scalingFactor))[4];
	buffer8[5] = ((char*)&(this->SpecHeader.scalingFactor))[5];
	buffer8[6] = ((char*)&(this->SpecHeader.scalingFactor))[6];
	buffer8[7] = ((char*)&(this->SpecHeader.scalingFactor))[7];
	fsDataOutfile.write(buffer8, 8);
	outheadsize = outheadsize + 8;

	// electronics            = fread(fid,  1,'*uint');
	// comsettingsElectronics = fread(fid,  1,'*uint');
	// comportElectronics     = fread(fid, 44,'*char')';
	// fanSpeed               = fread(fid,  1,'*uint');
	// backTemperature        = fread(fid,  1,'*uint');
	// Pback                  = fread(fid,  1,'*uint');
	// Iback                  = fread(fid,  1,'*uint');
	// Dback                  = fread(fid,  1,'*uint');
	// comport                = fread(fid, 64,'*char')';
	// detectstring           = fread(fid,200,'*char')';
	// sensor                 = fread(fid,200,'*char')';
	// framegrabber           = fread(fid,200,'*char')';
	char buffer736[736];
	for (size_t iii = 0; iii < 736; iii++){
	buffer736[iii] = NULL;
	};
	fsDataOutfile.write(buffer736, 736);
	outheadsize = outheadsize + 736;

	// ID                     = fread(fid,200,'*char')';
	std::string substr = this->SpecHeader.ID.substr(0, 200);
	fsDataOutfile.write(substr.c_str(), 200);
	outheadsize = outheadsize + 200;

	// supplier               = fread(fid,200,'*char')';
	// leftGain               = fread(fid, 32,'*char')';
	// rightGain              = fread(fid, 32,'*char')';
	// comment                = fread(fid,200,'*char')';
	// backgroundFile         = fread(fid,200,'*char')';
	// recordHD               = fread(fid,  1,'*char')';
	// unknownPOINTER         = fread(fid,  1,'*uint');    %4 byte pointer [useless] XCamera*m_hCam
	// serverIndex            = fread(fid,  1,'*uint');
	// comsettings            = fread(fid,  1,'*uint');
	// numberOfBackground     = fread(fid,  1,'*uint');
	char buffer681[681];
	for (size_t iii = 0; iii < 681; iii++){
		buffer681[iii] = NULL;
	};
	fsDataOutfile.write(buffer681, 681);
	outheadsize = outheadsize + 681;

	// spectralSize           = fread(fid,  1,'*uint');
	unsigned long bands = (unsigned long) this->SpecHeader.imgsize[1];
	buffer4[0] = ((char*)&(bands))[0];
	buffer4[1] = ((char*)&(bands))[1];
	buffer4[2] = ((char*)&(bands))[2];
	buffer4[3] = ((char*)&(bands))[3];
	fsDataOutfile.write(buffer4, 4);
	outheadsize = outheadsize + 4;

	// spatialSize            = fread(fid,  1,'*uint');
	unsigned long spatial = (unsigned long) this->SpecHeader.imgsize[0];
	buffer4[0] = ((char*)&(spatial))[0];
	buffer4[1] = ((char*)&(spatial))[1];
	buffer4[2] = ((char*)&(spatial))[2];
	buffer4[3] = ((char*)&(spatial))[3];
	fsDataOutfile.write(buffer4, 4);
	outheadsize = outheadsize + 4;

	// binning                = fread(fid,  1,'*uint');
	// detected               = fread(fid,  1,'*uint');
	buffer8[0] = NULL;
	buffer8[1] = NULL;
	buffer8[2] = NULL;
	buffer8[3] = NULL;
	buffer8[4] = NULL;
	buffer8[5] = NULL;
	buffer8[6] = NULL;
	buffer8[7] = NULL;
	fsDataOutfile.write(buffer8, 8);
	outheadsize = outheadsize + 8;

	// integrationtime        = fread(fid,  1,'*uint');
	unsigned long Integration = (unsigned long)(this->SpecHeader.Integration_time + 0.5);
	buffer4[0] = ((char*)&(Integration))[0];
	buffer4[1] = ((char*)&(Integration))[1];
	buffer4[2] = ((char*)&(Integration))[2];
	buffer4[3] = ((char*)&(Integration))[3];
	fsDataOutfile.write(buffer4, 4);
	outheadsize = outheadsize + 4;

	// frameperiod            = fread(fid,  1,'*uint');
	unsigned long frameperiod = (unsigned long)(this->SpecHeader.Frameperiod + 0.5);
	buffer4[0] = ((char*)&(frameperiod))[0];
	buffer4[1] = ((char*)&(frameperiod))[1];
	buffer4[2] = ((char*)&(frameperiod))[2];
	buffer4[3] = ((char*)&(frameperiod))[3];
	fsDataOutfile.write(buffer4, 4);
	outheadsize = outheadsize + 4;

	// defaultR               = fread(fid,  1,'*uint');
	// defaultG               = fread(fid,  1,'*uint');
	// defaultB               = fread(fid,  1,'*uint');
	// bitshift               = fread(fid,  1,'*uint');
	// temperatureOffset      = fread(fid,  1,'*uint');
	// shutter                = fread(fid,  1,'*uint');
	// backgroundPresent      = fread(fid,  1,'*uint');
	// power                  = fread(fid,  1,'*uint');
	// current                = fread(fid,  1,'*uint');
	// bias                   = fread(fid,  1,'*uint');
	// bandwidth              = fread(fid,  1,'*uint');
	// vin                    = fread(fid,  1,'*uint');
	// vref                   = fread(fid,  1,'*uint');
	// sensorVin              = fread(fid,  1,'*uint');
	// sensorVref             = fread(fid,  1,'*uint');
	// coolingTemperature     = fread(fid,  1,'*uint');
	// windowStart            = fread(fid,  1,'*uint');
	// windowStop             = fread(fid,  1,'*uint');
	// readoutTime            = fread(fid,  1,'*uint');
	// p                      = fread(fid,  1,'*uint');
	// i                      = fread(fid,  1,'*uint');
	// d                      = fread(fid,  1,'*uint');
	char buffer88[88];
	for (size_t iii = 0; iii < 88; iii++){
		buffer88[iii] = NULL;
	};
	fsDataOutfile.write(buffer88, 88);
	outheadsize = outheadsize + 88;

	// numberOfFrames         = fread(fid,  1,'*uint');
	unsigned long frames = (unsigned long) this->SpecHeader.imgsize[2];
	buffer4[0] = ((char*)&(frames))[0];
	buffer4[1] = ((char*)&(frames))[1];
	buffer4[2] = ((char*)&(frames))[2];
	buffer4[3] = ((char*)&(frames))[3];
	fsDataOutfile.write(buffer4, 4);
	outheadsize = outheadsize + 4;

	// nobp                   = fread(fid,  1,'*uint');
	unsigned long numberofbadpixel = (unsigned long) this->SpecHeader.nobp;
	buffer4[0] = ((char*)&(numberofbadpixel))[0];
	buffer4[1] = ((char*)&(numberofbadpixel))[1];
	buffer4[2] = ((char*)&(numberofbadpixel))[2];
	buffer4[3] = ((char*)&(numberofbadpixel))[3];
	fsDataOutfile.write(buffer4, 4);
	outheadsize = outheadsize + 4;

	// dw                     = fread(fid,  1,'*uint');
	// EQ                     = fread(fid,  1,'*uint');
	// lens                   = fread(fid,  1,'*uint');
	// FOVexp                 = fread(fid,  1,'*uint');
	// scanningMode           = fread(fid,  1,'*uint');
	// calibAvailable         = fread(fid,  1,'*uint');
	// numberOfAvg            = fread(fid,  1,'*uint');
	char buffer28[28];
	for (size_t iii = 0; iii < 28; iii++){
		buffer28[iii] = NULL;
	};
	fsDataOutfile.write(buffer28, 28);
	outheadsize = outheadsize + 28;

	// SF                     = fread(fid,  1,'*double');
	buffer8[0] = ((char*)&(this->SpecHeader.SF))[0];
	buffer8[1] = ((char*)&(this->SpecHeader.SF))[1];
	buffer8[2] = ((char*)&(this->SpecHeader.SF))[2];
	buffer8[3] = ((char*)&(this->SpecHeader.SF))[3];
	buffer8[4] = ((char*)&(this->SpecHeader.SF))[4];
	buffer8[5] = ((char*)&(this->SpecHeader.SF))[5];
	buffer8[6] = ((char*)&(this->SpecHeader.SF))[6];
	buffer8[7] = ((char*)&(this->SpecHeader.SF))[7];
	fsDataOutfile.write(buffer8, 8);
	outheadsize = outheadsize + 8;

	// apertureSize           = fread(fid,  1,'*double');
	buffer8[0] = ((char*)&(this->SpecHeader.apertureSize))[0];
	buffer8[1] = ((char*)&(this->SpecHeader.apertureSize))[1];
	buffer8[2] = ((char*)&(this->SpecHeader.apertureSize))[2];
	buffer8[3] = ((char*)&(this->SpecHeader.apertureSize))[3];
	buffer8[4] = ((char*)&(this->SpecHeader.apertureSize))[4];
	buffer8[5] = ((char*)&(this->SpecHeader.apertureSize))[5];
	buffer8[6] = ((char*)&(this->SpecHeader.apertureSize))[6];
	buffer8[7] = ((char*)&(this->SpecHeader.apertureSize))[7];
	fsDataOutfile.write(buffer8, 8);
	outheadsize = outheadsize + 8;

	// pixelSizeX             = fread(fid,  1,'*double');
	buffer8[0] = ((char*)&(this->SpecHeader.pixelSizeX))[0];
	buffer8[1] = ((char*)&(this->SpecHeader.pixelSizeX))[1];
	buffer8[2] = ((char*)&(this->SpecHeader.pixelSizeX))[2];
	buffer8[3] = ((char*)&(this->SpecHeader.pixelSizeX))[3];
	buffer8[4] = ((char*)&(this->SpecHeader.pixelSizeX))[4];
	buffer8[5] = ((char*)&(this->SpecHeader.pixelSizeX))[5];
	buffer8[6] = ((char*)&(this->SpecHeader.pixelSizeX))[6];
	buffer8[7] = ((char*)&(this->SpecHeader.pixelSizeX))[7];
	fsDataOutfile.write(buffer8, 8);
	outheadsize = outheadsize + 8;

	// pixelSizeY             = fread(fid,  1,'*double');
	buffer8[0] = ((char*)&(this->SpecHeader.pixelSizeY))[0];
	buffer8[1] = ((char*)&(this->SpecHeader.pixelSizeY))[1];
	buffer8[2] = ((char*)&(this->SpecHeader.pixelSizeY))[2];
	buffer8[3] = ((char*)&(this->SpecHeader.pixelSizeY))[3];
	buffer8[4] = ((char*)&(this->SpecHeader.pixelSizeY))[4];
	buffer8[5] = ((char*)&(this->SpecHeader.pixelSizeY))[5];
	buffer8[6] = ((char*)&(this->SpecHeader.pixelSizeY))[6];
	buffer8[7] = ((char*)&(this->SpecHeader.pixelSizeY))[7];
	fsDataOutfile.write(buffer8, 8);
	outheadsize = outheadsize + 8;

	// temperature            = fread(fid,  1,'*double');
	// maxFramerate           = fread(fid,  1,'*double');
	// spectralCalibPOINTER   = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = spectralSize*sizeof(double)
	// REPOINTER              = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = spectralSize*spatialSize*sizeof(double)
	// QEPOINTER              = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = spectralSize*sizeof(double)
	// backgroundPOINTER      = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = spatialSize*spectralSize*sizeof(double)
	// badPixelsPOINTER       = fread(fid,  1,'*int'); %4 byte pointer [useless]   size = nobp*sizeof(uint)
	char buffer36[36];
	for (size_t iii = 0; iii < 36; iii++){
		buffer36[iii] = NULL;
	};
	fsDataOutfile.write(buffer36, 36);
	outheadsize = outheadsize + 36;

	// imageFormat            = fread(fid,  1,'*uint');
	unsigned long imageFormat;
	switch (this->SpecHeader.interleave)
	{
	case t_SpecHead::IL_BIL:
		imageFormat = 3;
		break;
	case t_SpecHead::IL_BSQ:
		imageFormat = 2;
		break;
	case t_SpecHead::IL_BIP:
		imageFormat = 1;
		break;
	};
	buffer4[0] = ((char*)&(imageFormat))[0];
	buffer4[1] = ((char*)&(imageFormat))[1];
	buffer4[2] = ((char*)&(imageFormat))[2];
	buffer4[3] = ((char*)&(imageFormat))[3];
	fsDataOutfile.write(buffer4, 4);
	outheadsize = outheadsize + 4;

	// spectralVector         = fread(fid,// spectralSize,'*double');
	double value = 0.0;
	if (this->SpecHeader.wavelen.size() > 0)
	{
		// Wellenlaengen
		for (int i = 0; i < this->SpecHeader.wavelen.size(); i++)
		{
			value = (double) this->SpecHeader.wavelen.at(i);
			buffer8[0] = ((char*)&value)[0];
			buffer8[1] = ((char*)&value)[1];
			buffer8[2] = ((char*)&value)[2];
			buffer8[3] = ((char*)&value)[3];
			buffer8[4] = ((char*)&value)[4];
			buffer8[5] = ((char*)&value)[5];
			buffer8[6] = ((char*)&value)[6];
			buffer8[7] = ((char*)&value)[7];
			fsDataOutfile.write(buffer8, 8);
			outheadsize = outheadsize + 8;
		};
	};

	// QE                     = fread(fid,// spectralSize,'*double');
	if (this->SpecHeader.QEarraySize > 0)
	{
		fsDataOutfile.write(static_cast<char*>(this->SpecHeader.QEarray), this->SpecHeader.QEarraySize);
		outheadsize = outheadsize + (unsigned long) this->SpecHeader.QEarraySize;
	};

	// RE                     = fread(fid,// spectralSize*// spatialSize,'*double');
	if (this->SpecHeader.REarraySize > 0)
	{
		fsDataOutfile.write(static_cast<char*>(this->SpecHeader.REarray), this->SpecHeader.REarraySize);
		outheadsize = outheadsize + (unsigned long) this->SpecHeader.REarraySize;
	};

	// background             = fread(fid,// spatialSize*// spectralSize,'*double');
	if (this->SpecHeader.BGarraySize > 0)
	{
		fsDataOutfile.write(static_cast<char*>(this->SpecHeader.BGarray), this->SpecHeader.BGarraySize);
		outheadsize = outheadsize + (unsigned long) this->SpecHeader.BGarraySize;
	};

	// badPixels              = fread(fid,// nobp,'*uint');
	if (this->SpecHeader.BadPixelsarraySize > 0)
	{
		fsDataOutfile.write(static_cast<char*>(this->SpecHeader.BadPixelsarray), this->SpecHeader.BadPixelsarraySize);
		outheadsize = outheadsize + (unsigned long) this->SpecHeader.BadPixelsarraySize;
	};

	// Endgueltige Headergroesse schreiben
	unsigned long outpos = fsDataOutfile.tellp();
	fsDataOutfile.seekp(8);
	outheadsizebuffer4[0] = ((char*)&(outheadsize))[0];
	outheadsizebuffer4[1] = ((char*)&(outheadsize))[1];
	outheadsizebuffer4[2] = ((char*)&(outheadsize))[2];
	outheadsizebuffer4[3] = ((char*)&(outheadsize))[3];
	fsDataOutfile.write(outheadsizebuffer4, 4);
	fsDataOutfile.seekp(outpos);
	this->SpecHeader.headsize = (unsigned long long)outheadsize;	// Fuer die .hdr

	// Bilddaten schreiben
	unsigned long long imgsize = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize;
	unsigned long long bandsize = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize;

	std::ifstream ifs(this->tempOutFileName.c_str(), std::ifstream::in | std::ifstream::binary);
	if (ifs.fail() == false)
	{
		char* buffer = new char[bandsize];
		ifs.seekg(8, ifs.beg);// hat nur einen 8Byte Header

		for (unsigned long long z = 0; z < this->SpecHeader.imgsize[1]; z++)
		{
			int lengthIn = ifs.tellg();
			ifs.read(buffer, bandsize);

			/*
			cv::Mat Band(this->SpecHeader.imgsize[2], this->SpecHeader.imgsize[0], CV_16U, buffer);
			double minVal, maxVal;
			cv::minMaxLoc(Band, &minVal, &maxVal);
			cv::Mat BandOutImage(this->SpecHeader.imgsize[2], this->SpecHeader.imgsize[0], CV_8U);
			Band.convertTo(BandOutImage, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
			std::string OutStr = "C:\\Testausgaben\\GaussCubeFilter\\BandOut-" + std::to_string(z) + ".png";
			cv::imwrite(OutStr.c_str(), BandOutImage);
			//*/

			int lengthOut = fsDataOutfile.tellg();
			fsDataOutfile.write(buffer, bandsize);

		};
		delete[] buffer;
		ifs.close();
	};
	
	
	/*
	if(SpecHeader.type == 1)
	{
		fsDataOutfile.write(static_cast<char*>(this->SpecHeader.imgcube), imgsize);
	};
	if(SpecHeader.type == 2)
	{
		// Das ist hier noch nicht schoen geloest....

		std::ifstream ifs(this->SpecHeader.filename.c_str(), std::ifstream::in | std::ifstream::binary);
		char* buffer = new char[1];
		ifs.seekg(this->SpecHeader.headsize, ifs.beg);
		for(long long i = 0; i < imgsize; i++)
		{
			ifs.read(buffer,1);
			fsDataOutfile.write(buffer, 1);
		};
		delete[] buffer;
		ifs.close();
	};//*/
	
	fsDataOutfile.close();

	return 0;
};
//
int SpecIL_Base::writeDataToTGDfile(std::string outTGDfile)
{
	unsigned int dtype;
	switch (this->SpecHeader.data_type)
	{
	case t_SpecHead::DT_8_BYTE:
		dtype = 4;
		break;
	case t_SpecHead::DT_16_SINT:
		dtype = 8;
		break;
	case t_SpecHead::DT_32_SLONG:
		dtype = 32;
		break;
	case t_SpecHead::DT_32_FLOAT:
		dtype = 512;
		break;
	case t_SpecHead::DT_64_DOUBLE:
		this->ErrorMsgLog("In SpecIL_Base::writeDataToTGDfile(): Datatype is not supported!");
		return -1;
	case t_SpecHead::DT_2x32_COMPLEX:
		this->ErrorMsgLog("In SpecIL_Base::writeDataToTGDfile(): Datatype is not supported!");
		return -1;
	case t_SpecHead::DT_2x64_COMPLEX:
		this->ErrorMsgLog("In SpecIL_Base::writeDataToTGDfile(): Datatype is not supported!");
		return -1;
	case t_SpecHead::DT_16_UINT:
		dtype = 16;
		break;
	case t_SpecHead::DT_32_ULONG:
		dtype = 256;
		break;
	case t_SpecHead::DT_64_SLONG:
		this->ErrorMsgLog("In SpecIL_Base::writeDataToTGDfile(): Datatype is not supported!");
		return -1;
	case t_SpecHead::DT_64_ULONG:
		this->ErrorMsgLog("In SpecIL_Base::writeDataToTGDfile(): Datatype is not supported!");
		return -1;
	default:
		this->ErrorMsgLog("In SpecIL_Base::writeDataToTGDfile(): Datatype is not supported!");
		return -1;
	};

	std::fstream fsDataOutfile;
	fsDataOutfile.open(outTGDfile, std::fstream::in | std::fstream::out | std::fstream::trunc | std::fstream::binary);

	char magic[4] = {'T', 'G', 'D', '!'};
	fsDataOutfile.write(magic, 4);

	unsigned int numdim = this->SpecHeader.numdim;
	char* numdim4 = reinterpret_cast<char*>(&numdim);
	fsDataOutfile.write(numdim4, 4);

	unsigned int numspatial = this->SpecHeader.imgsize[0];
	char* numspatial4 = reinterpret_cast<char*>(&numspatial);
	
	unsigned int numspectral = this->SpecHeader.imgsize[1];
	char* numspectral4 = reinterpret_cast<char*>(&numspectral);
	
	unsigned int numframe = this->SpecHeader.imgsize[2];
	char* numframe4 = reinterpret_cast<char*>(&numframe);
	
	// tgd codiert die Anordnung durch die Reihenfolge der Diomensionen
	if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
	{
		fsDataOutfile.write(numspatial4, 4);
		fsDataOutfile.write(numspectral4, 4);
		fsDataOutfile.write(numframe4, 4);
	}
	else// if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
	{
		fsDataOutfile.write(numspatial4, 4);
		fsDataOutfile.write(numframe4, 4);
		fsDataOutfile.write(numspectral4, 4);
	};

	char* dtype4 = reinterpret_cast<char*>(&dtype);
	fsDataOutfile.write(dtype4, 4);

	this->SpecHeader.headsize = 4 + 4 + 4*numdim + 4;

	// Bilddaten schreiben
//	size_t imgsize = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize;
//	fsDataOutfile.write(static_cast<char*>(this->SpecHeader.imgcube), imgsize);

	unsigned long long bandsize = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize;
	std::ifstream ifs(this->tempOutFileName.c_str(), std::ifstream::in | std::ifstream::binary);
	if (ifs.fail() == false)
	{
		char* buffer = new char[bandsize];
		ifs.seekg(8, ifs.beg);// hat nur einen 8Byte Header

		for (unsigned long long z = 0; z < this->SpecHeader.imgsize[1]; z++)
		{
			int lengthIn = ifs.tellg();
			ifs.read(buffer, bandsize);

			/*
			cv::Mat Band(this->SpecHeader.imgsize[2], this->SpecHeader.imgsize[0], CV_16U, buffer);
			double minVal, maxVal;
			cv::minMaxLoc(Band, &minVal, &maxVal);
			cv::Mat BandOutImage(this->SpecHeader.imgsize[2], this->SpecHeader.imgsize[0], CV_8U);
			Band.convertTo(BandOutImage, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
			std::string OutStr = "C:\\Testausgaben\\GaussCubeFilter\\BandOut-" + std::to_string(z) + ".png";
			cv::imwrite(OutStr.c_str(), BandOutImage);
			//*/

			int lengthOut = fsDataOutfile.tellg();
			fsDataOutfile.write(buffer, bandsize);

		};
		delete[] buffer;
		ifs.close();
	};
	fsDataOutfile.close();

	return 0;
};
//
int SpecIL_Base::getPlane(void* plane, int x, int y, int z)
{
	// wurde read() ausgefuehrt ?
	if(this->SpecHeader.type == 0)
	{
		// Err
		this->ErrorMsgLog("In SpecIL_Base::getPlane(): SpecHeader.type == 0, Data was not read! Run read()!");
		return -1;
	};

	int array_x[2];
	int array_y[2];
	int array_z[2];

	// Ein Band ausgeben
	if(x < 0 && y < 0 && z < this->SpecHeader.imgsize[1])
	{
		array_x[0] = 0;
		array_x[1] = this->SpecHeader.imgsize[0] - 1;

		array_y[0] = 0;
		array_y[1] = this->SpecHeader.imgsize[2] - 1;

		//array_z[0] = z;
		//array_z[1] = -1;

		this->getPlane_Band(plane, array_x, array_y, z);

		return 0;

		// RAW
		/*if(this->OutputProfile == 0)
		{
			this->getPlane_Band(plane, x, y, z);
			return 0;
		};
		// C-Workflow
		if(this->OutputProfile == 1)
		{
			this->getPlane_Band_CWF(plane, x, y, z);
			return 0;
		};*/
	};
	// Einen Frame ausgeben
	if (x < 0 && z < 0 && y < this->SpecHeader.imgsize[2])
	{
		array_x[0] = 0;
		array_x[1] = this->SpecHeader.imgsize[0] - 1;

		//array_y[0] = y;
		//array_y[1] = -1;

		array_z[0] = 0;
		array_z[1] = this->SpecHeader.imgsize[1] - 1;

		this->getPlane_Frame(plane, array_x, y, array_z);
		return 0;
	};
	// Ein Samplebild ausgeben
	if (y < 0 && z < 0 && x < this->SpecHeader.imgsize[0])
	{
		//array_x[0] = x;
		//array_x[1] = -1;

		array_y[0] = 0;
		array_y[1] = this->SpecHeader.imgsize[2] - 1;

		array_z[0] = 0;
		array_z[1] = this->SpecHeader.imgsize[1] - 1;

		this->getPlane_Sample(plane, x, array_y, array_z);
		return 0;
	};
	//Err
	this->ErrorMsgLog("In SpecIL_Base::getPlane(): invalid parameters");
	return -1;
};
//
int SpecIL_Base::getPlane(void* plane, int *x, int *y, int *z)
{
	if (this->SpecHeader.type == 0)
	{
		// Err
		this->ErrorMsgLog("In SpecIL_Base::getPlane(): SpecHeader.type == 0, Data was not read! Run read()!");
		return -1;
	};

	// Ein Bandausschnitt ausgeben
	if (z[1] < 0 && z[0] < this->SpecHeader.imgsize[1] && 
		y[0] >= 0 && y[1] < this->SpecHeader.imgsize[2] &&
		x[0] >= 0 && x[1] < this->SpecHeader.imgsize[0] )
	{
		this->getPlane_Band(plane, x, y, z[0]);
		return 0;
	};

	// Frameausschnitt
	if (y[1] < 0 && y[0] < this->SpecHeader.imgsize[2] &&
		x[0] >= 0 && x[1] < this->SpecHeader.imgsize[0] &&
		z[0] >= 0 && z[1] < this->SpecHeader.imgsize[1])
	{
		this->getPlane_Frame(plane, x, y[0], z);
		return 0;
	};

	// Samplebildausschnitt
	if (x[1] < 0 && x[0] < this->SpecHeader.imgsize[0] &&
		z[0] >= 0 && z[1] < this->SpecHeader.imgsize[1] &&
		y[0] >= 0 && y[1] < this->SpecHeader.imgsize[2])
	{
		this->getPlane_Sample(plane, x[0], y, z);
		return 0;
	};

	//Err
	this->ErrorMsgLog("In SpecIL_Base::getPlane(): invalid parameters");
	return -1;
};
//
int SpecIL_Base::getPlane_Band(void* plane, int *x, int *y, int z)
{
	char* BandImgbuff = static_cast<char*>(plane);

	unsigned long long diff_x = (unsigned long long)(x[1] - x[0]) + 1;
	unsigned long long diff_y = (unsigned long long)(y[1] - y[0]) + 1;

	unsigned long long start_x = (unsigned long long)x[0];
	unsigned long long start_y = (unsigned long long)y[0];

	// Daten vollstaendig im Speicher
	if(this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);

		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			unsigned long long cutoutlinesize = this->SpecHeader.pixelsize * diff_x;
			unsigned long long cubeoff = 0;

			for (unsigned long long j = 0; j < diff_y; j++)
			{
				cubeoff = (((unsigned long long)z + (j + start_y) * this->SpecHeader.imgsize[1]) * this->SpecHeader.imgsize[0]  + start_x) * this->SpecHeader.pixelsize;
				std::memmove(&BandImgbuff[cutoutlinesize * j], &Cubebuff[cubeoff], cutoutlinesize);
			};
			return 0;
		};

		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long bandsize = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2];
			unsigned long long cubeoff = (unsigned long long)z * bandsize;
			unsigned long long cutoutsize = this->SpecHeader.pixelsize * diff_x * diff_y;
			if (bandsize != cutoutsize)
			{
				unsigned long long cutoutlinesize = diff_x * this->SpecHeader.pixelsize;
				cubeoff += (x[0] + y[0] * this->SpecHeader.imgsize[0])* this->SpecHeader.pixelsize;
				for (unsigned long long i = 0; i < diff_y; i++)
				{
					std::memmove(&BandImgbuff[cutoutlinesize * i], &Cubebuff[cubeoff], cutoutlinesize);
					cubeoff += this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
				};
			}
			else
			{
				std::memmove(BandImgbuff, &Cubebuff[cubeoff], bandsize);
			};
			return 0;
		};

		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			unsigned long long cubeoff = 0;
			unsigned long long bandoff = 0;

			unsigned long long pixelmax = diff_x + diff_y;

			for (unsigned long long j = 0; j < diff_y; j++) //y
			{
				cubeoff = ((unsigned long long)z + start_x * this->SpecHeader.imgsize[1] + (start_y+j) * this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[0]) * this->SpecHeader.pixelsize;
				for (unsigned long long i = 0; i < diff_x; i++) //x
				{
					std::memmove(&BandImgbuff[bandoff], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
					bandoff += this->SpecHeader.pixelsize;
					cubeoff += this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
				};
			};
			return 0;
		};
	};
	// Daten auf HDD
	// oder von/auf HDD arbeiten?
	if(this->SpecHeader.type == 2)
	{
		std::ifstream ifs( this->SpecHeader.filename, std::fstream::binary);
		// band interleaved by line
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			unsigned long long fileoff = 0;
			unsigned long long cutoutlinesize = this->SpecHeader.pixelsize * diff_x;

			// Bild zusammenbauen
			for (unsigned long long i = 0; i < diff_y; i++)
			{
				fileoff = (unsigned long long)this->SpecHeader.headsize + (((unsigned long long)z + (i + start_y) * this->SpecHeader.imgsize[1]) * this->SpecHeader.imgsize[0] + start_x) * this->SpecHeader.pixelsize;;
				ifs.seekg(fileoff);
				ifs.read(&BandImgbuff[i * cutoutlinesize], cutoutlinesize);
			};
			ifs.close();
			return 0;
		};
		// band sequential
		if(this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long bandsize = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2];
			unsigned long long cutoutsize = this->SpecHeader.pixelsize * diff_x * diff_y;
			unsigned long long startpos = (unsigned long long)this->SpecHeader.headsize + (unsigned long long)z * bandsize;

			if (bandsize != cutoutsize)
			{
				unsigned long long cutoutlinesize = diff_x * this->SpecHeader.pixelsize;
				startpos += (x[0] + y[0] * this->SpecHeader.imgsize[0])* this->SpecHeader.pixelsize;

				for (unsigned long long i = 0; i < diff_y; i++)
				{
					ifs.seekg(startpos);
					ifs.read(&BandImgbuff[cutoutlinesize * i], cutoutlinesize);
					startpos += this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
				};
			}
			else
			{
				ifs.seekg(startpos);
				ifs.read(BandImgbuff, bandsize);
			};
			ifs.close();
			return 0;
		};
		// band interleaved by pixel
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{

			unsigned long long fileoff = 0;
			unsigned long long bandoff = 0;

			unsigned long long pixelmax = diff_x + diff_y;

			for (unsigned long long j = 0; j < diff_y; j++) //y
			{
				fileoff = (unsigned long long)this->SpecHeader.headsize + ((unsigned long long)z + start_x * this->SpecHeader.imgsize[1] + (start_y + j) * this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[0]) * this->SpecHeader.pixelsize;
				for (unsigned long long i = 0; i < diff_x; i++) //x
				{
					ifs.seekg(fileoff);
					ifs.read(&BandImgbuff[bandoff], this->SpecHeader.pixelsize);

					bandoff += this->SpecHeader.pixelsize;
					fileoff += this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
				};
			};

			ifs.close();
			return 0;
		};
	};
	// Err
	this->ErrorMsgLog("In SpecIL_Base::getPlane_Band(): Invalid Parameter(s) !");
	return -1;
};
//
int SpecIL_Base::getPlane_Frame(void* plane, int *x, int y, int *z)
{
	char* FrameImgbuff = static_cast<char*>(plane);

	unsigned long long diff_x = (unsigned long long)(x[1] - x[0]) + 1;
	unsigned long long diff_z = (unsigned long long)(z[1] - z[0]) + 1;

	unsigned long long start_x = (unsigned long long)x[0];
	unsigned long long start_z = (unsigned long long)z[0];

	if(this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			unsigned long long cubeoff = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize * this->SpecHeader.imgsize[1] * (unsigned long long)y;
			unsigned long long framesize = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1];
			unsigned long long cutoutframesize = diff_x * diff_z * this->SpecHeader.pixelsize;
			
			if (framesize != cutoutframesize)
			{
				cubeoff += (this->SpecHeader.imgsize[0] * start_z + start_x) * this->SpecHeader.pixelsize;
				unsigned long long linesize = diff_x * this->SpecHeader.pixelsize;
				for (unsigned long long i = 0; i < diff_z; i++)
				{
					std::memmove(&FrameImgbuff[linesize * i], &Cubebuff[cubeoff], linesize);
					cubeoff += this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
				};
			}
			else
			{
				std::memmove(FrameImgbuff, &Cubebuff[cubeoff], framesize);
			};
			return 0;
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long cutoutlinesize = this->SpecHeader.pixelsize * diff_x;
			unsigned long long cubeoff = 0;
			for (unsigned long long i = 0; i < diff_z; i++)
			{
				cubeoff = (((unsigned long long)y + (i + start_z) * this->SpecHeader.imgsize[2]) * this->SpecHeader.imgsize[0] + start_x) * this->SpecHeader.pixelsize;
				std::memmove(&FrameImgbuff[cutoutlinesize * i], &Cubebuff[cubeoff], cutoutlinesize);
			};
			return 0;
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			unsigned long long cubeoff = 0;
			unsigned long long frameoff = 0;
			for (unsigned long long i = 0; i < diff_x; i++)		// x
			{
				for(unsigned long long k = 0; k <diff_z; k++)		// z
				{
					cubeoff = (unsigned long long)y * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
					cubeoff += (i + start_x) * this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
					cubeoff += (k + start_z)* this->SpecHeader.pixelsize;
					frameoff = (i + k * diff_x) *this->SpecHeader.pixelsize;
					std::memmove(&FrameImgbuff[frameoff], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
				};
			};
			return 0;
		};
	};
	if(this->SpecHeader.type == 2)
	{
		std::ifstream ifs( this->SpecHeader.filename, std::fstream::binary);
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			unsigned long long fileoff = (unsigned long long)this->SpecHeader.headsize + this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize * this->SpecHeader.imgsize[1] * (unsigned long long)y;
			unsigned long long framesize = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1];
			unsigned long long cutoutframesize = diff_x * diff_z * this->SpecHeader.pixelsize;

			if (framesize != cutoutframesize)
			{
				fileoff += (this->SpecHeader.imgsize[0] * start_z + start_x) * this->SpecHeader.pixelsize;
				unsigned long long linesize = diff_x * this->SpecHeader.pixelsize;
				for (unsigned long long i = 0; i < diff_z; i++)
				{
					ifs.seekg(fileoff);
					ifs.read(&FrameImgbuff[linesize * i], linesize);
					fileoff += this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
				};
			}
			else
			{
				ifs.seekg(fileoff);
				ifs.read(FrameImgbuff, framesize);
			};
			ifs.close();
			return 0;
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long cutoutlinesize = this->SpecHeader.pixelsize * diff_x;
			unsigned long long fileoff = 0;
			for (unsigned long long i = 0; i < diff_z; i++)
			{
				fileoff = (unsigned long long)this->SpecHeader.headsize + (((unsigned long long)y + (i + start_z) * this->SpecHeader.imgsize[2]) * this->SpecHeader.imgsize[0] + start_x) * this->SpecHeader.pixelsize;
				ifs.seekg(fileoff);
				ifs.read(&FrameImgbuff[cutoutlinesize * i], cutoutlinesize);
			};
			ifs.close();
			return 0;
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			unsigned long long fileoff = 0;
			unsigned long long frameoff = 0;
			for (unsigned long long i = 0; i < diff_x; i++)		// x
			{
				for (unsigned long long k = 0; k <diff_z; k++)		// z
				{
					fileoff = (unsigned long long)this->SpecHeader.headsize + (unsigned long long)y * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
					fileoff += (i + start_x) * this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
					fileoff += (k + start_z)* this->SpecHeader.pixelsize;
					frameoff = (i + k * diff_x) *this->SpecHeader.pixelsize;

					ifs.seekg(fileoff);
					ifs.read(&FrameImgbuff[frameoff], this->SpecHeader.pixelsize);
				};
			};
			ifs.close();
			return 0;
		};
	};
	//Err
	this->ErrorMsgLog("In SpecIL_Base::getPlane_RAW_Frame(): invalid parameters");
	return -1;
};
//
int SpecIL_Base::getPlane_Sample(void* plane, int x, int *y, int *z)
{
	char* SampleImgbuff = static_cast<char*>(plane);

	unsigned long long diff_y = (unsigned long long)(y[1] - y[0]) + 1;
	unsigned long long diff_z = (unsigned long long)(z[1] - z[0]) + 1;

	unsigned long long start_y = (unsigned long long)y[0];
	unsigned long long start_z = (unsigned long long)z[0];

	if(this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			unsigned long long cubeoff = ((unsigned long long)x + (start_z + start_y * this->SpecHeader.imgsize[1]) * this->SpecHeader.imgsize[0])* this->SpecHeader.pixelsize;
			unsigned long long jump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
			unsigned long long samples = diff_z * diff_y;
			unsigned long long samplesmax = this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[2];
			if (samplesmax == samples)
			{
				for (unsigned long long i = 0; i < samples; i++)
				{
					std::memmove(&SampleImgbuff[i * this->SpecHeader.pixelsize], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
					cubeoff = cubeoff + jump;
				};
			}
			else
			{
				for (unsigned long long j = 0; j < diff_y; j++)
				{
					cubeoff = ((unsigned long long)x + (start_z + (start_y + j) * this->SpecHeader.imgsize[1]) * this->SpecHeader.imgsize[0])* this->SpecHeader.pixelsize;

					for (unsigned long long i = 0; i < diff_z; i++)
					{
						std::memmove(&SampleImgbuff[(j * diff_z + i) * this->SpecHeader.pixelsize], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
						cubeoff = cubeoff + jump;
					};
				};
			};
			return 0;
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long cubeoff = 0;
			unsigned long long sampleoff = 0;
			unsigned long long framejump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
			unsigned long long bandjump = this->SpecHeader.imgsize[2] * framejump;
			unsigned long long startrawoff = ((unsigned long long)x + (start_y + start_z*this->SpecHeader.imgsize[2])*this->SpecHeader.imgsize[0])* this->SpecHeader.pixelsize;
			for (unsigned long long j = 0; j < diff_y; j++)
			{
				cubeoff = startrawoff + j * framejump;
				for (unsigned long long i = 0; i < diff_z; i++)
				{
					std::memmove(&SampleImgbuff[sampleoff], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
					sampleoff += this->SpecHeader.pixelsize;
					cubeoff += bandjump;
				};
			};
			return 0;
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			unsigned long long cubeoff = 0;
			unsigned long long sampleoff = 0;
			for (unsigned long long k = 0; k < diff_z; k++)		//z
			{
				for (unsigned long long i = 0; i < diff_y; i++)	//y
				{
					cubeoff = (k + start_z + ((unsigned long long)x + (i + start_y) * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[1]) * this->SpecHeader.pixelsize;
					sampleoff = (k + i *diff_z) *this->SpecHeader.pixelsize;
					std::memmove(&SampleImgbuff[sampleoff], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
				};
			};
			return 0;
		};
	};
	if(this->SpecHeader.type == 2)
	{
		std::ifstream ifs( this->SpecHeader.filename, std::fstream::binary);
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			unsigned long long fileoff = (unsigned long long)this->SpecHeader.headsize + ((unsigned long long)x + (start_z + start_y * this->SpecHeader.imgsize[1]) * this->SpecHeader.imgsize[0])* this->SpecHeader.pixelsize;
			unsigned long long jump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
			unsigned long long samples = diff_z * diff_y;
			unsigned long long samplesmax = this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[2];
			if (samplesmax == samples)
			{
				for (unsigned long long i = 0; i < samples; i++)
				{
					ifs.seekg(fileoff);
					ifs.read(&SampleImgbuff[i * this->SpecHeader.pixelsize], this->SpecHeader.pixelsize);
					fileoff = fileoff + jump;
				};
			}
			else
			{
				for (unsigned long long j = 0; j < diff_y; j++)
				{
					fileoff = (unsigned long long)this->SpecHeader.headsize + ((unsigned long long)x + (start_z + (start_y + j) * this->SpecHeader.imgsize[1]) * this->SpecHeader.imgsize[0])* this->SpecHeader.pixelsize;

					for (unsigned long long i = 0; i < diff_z; i++)
					{
						ifs.seekg(fileoff);
						ifs.read(&SampleImgbuff[(j * diff_z + i) * this->SpecHeader.pixelsize], this->SpecHeader.pixelsize);
						fileoff = fileoff + jump;
					};
				};
			};

			ifs.close();
			return 0;
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long fileoff = 0;
			unsigned long long sampleoff = 0;
			unsigned long long framejump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
			unsigned long long bandjump = this->SpecHeader.imgsize[2] * framejump;
			unsigned long long startrawoff = (unsigned long long)this->SpecHeader.headsize + ((unsigned long long)x + (start_y + start_z*this->SpecHeader.imgsize[2])*this->SpecHeader.imgsize[0])* this->SpecHeader.pixelsize;
			for (unsigned long long j = 0; j < diff_y; j++)
			{
				fileoff = startrawoff + j * framejump;
				for (unsigned long long i = 0; i < diff_z; i++)
				{
					ifs.seekg(fileoff);
					ifs.read(&SampleImgbuff[sampleoff], this->SpecHeader.pixelsize);


					
					sampleoff += this->SpecHeader.pixelsize;
					fileoff += bandjump;
				};
			};
			ifs.close();
			return 0;
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			unsigned long long fileoff = 0;
			unsigned long long sampleoff = 0;
			for (unsigned long long k = 0; k < diff_z; k++)		//z
			{
				for (unsigned long long i = 0; i < diff_y; i++)	//y
				{
					fileoff = (unsigned long long)this->SpecHeader.headsize + (k + start_z + ((unsigned long long)x + (i + start_y) * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[1]) * this->SpecHeader.pixelsize;
					sampleoff = (k + i *diff_z) *this->SpecHeader.pixelsize;


					ifs.seekg(fileoff);
					ifs.read(&SampleImgbuff[sampleoff], this->SpecHeader.pixelsize);
				};
			};
			ifs.close();
			return 0;
		};
	};
	//Err
	this->ErrorMsgLog("In SpecIL_Base::getPlane_RAW_Sample(): invalid parameters");
	return -1;
};
//
int SpecIL_Base::getPlane_Band_CWF(void* plane, int x, int y, int z)
{
	char* BandImgbuff = static_cast<char*>(plane);
	// Daten vollstaendig im Speicher
	if (this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);
		// band interleaved by line
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			// Bild zusammenbauen und umsortieren auf vereinbartes Standardformat
			for (unsigned long long j = 0; j < this->SpecHeader.imgsize[2]; j++) //y
			{
				for (unsigned long long i = 0; i < this->SpecHeader.imgsize[0]; i++) //x
				{
					unsigned long long cubeoff = ((this->SpecHeader.imgsize[1] * j + (unsigned long long)z) * this->SpecHeader.imgsize[0] + i) * this->SpecHeader.pixelsize;
					// x und y vertauschen...
					unsigned long long bandoff = (j + i * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize;
					// Kopieren
					std::memmove(&BandImgbuff[bandoff], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
				};
			};
			return 0;
		};
		// band sequential
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long Bandpos = (unsigned long long)z * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize;
			// Bild zusammenbauen und umsortieren auf vereinbartes Standardformat
			for (unsigned long long j = 0; j < this->SpecHeader.imgsize[2]; j++) //y
			{
				for (unsigned long long i = 0; i < this->SpecHeader.imgsize[0]; i++) //x
					{
					unsigned long long cubeoff = (i + j * this->SpecHeader.imgsize[0]) * this->SpecHeader.pixelsize + Bandpos;
					unsigned long long bandoff = (j + i * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize;
					std::memmove(&BandImgbuff[bandoff], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
					};
				};
				return 0;
			};
			// band interleaved by pixel
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
			{
			for (unsigned long long j = 0; j < this->SpecHeader.imgsize[2]; j++) //y
				{
				for (unsigned long long i = 0; i < this->SpecHeader.imgsize[0]; i++) //x
					{
					unsigned long long cubeoff = ((unsigned long long)z + (i + j * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[1])* this->SpecHeader.pixelsize;
					unsigned long long bandoff = (j + i * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize;
					std::memmove(&BandImgbuff[bandoff], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
					};
				};
				return 0;
			};
		};
		// Daten auf HDD
		// oder von/auf HDD arbeiten?
	if (this->SpecHeader.type == 2)
		{
		std::ifstream ifs(this->SpecHeader.filename, std::fstream::binary);
			// band interleaved by line
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
			{
				// Startposition
			unsigned long long fileoff = (unsigned long long)this->SpecHeader.headsize + this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize * (unsigned long long)z;
				// Zeilegroessegroesse
			unsigned long long linesize = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0];
				// Sprungweite zur naechsten Zeile
			unsigned long long jump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize * this->SpecHeader.imgsize[1];
				// Buffer
			char* RAWBandImgbuff = new char[linesize * this->SpecHeader.imgsize[2]];
				// Bild zusammenbauen
			for (unsigned long long i = 0; i < this->SpecHeader.imgsize[2]; i++)
				{
					ifs.seekg(fileoff);
					ifs.read(&RAWBandImgbuff[i * linesize], linesize);
					fileoff = fileoff + jump;
				};
			ifs.close();
			// Bild umbauen
			for (unsigned long long j = 0; j < this->SpecHeader.imgsize[2]; j++) //y
			{
				for (unsigned long long i = 0; i < this->SpecHeader.imgsize[0]; i++) //x
				{
					unsigned long long rawoff = (i + j * this->SpecHeader.imgsize[0]) * this->SpecHeader.pixelsize;
					unsigned long long bandoff = (j + i * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize;
					std::memmove(&BandImgbuff[bandoff], &RAWBandImgbuff[rawoff], this->SpecHeader.pixelsize);
				};
			};
			delete[] RAWBandImgbuff;
			return 0;
		};
		// band sequential
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long bandsize = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize;
			char* RAWBandImgbuff = new char[bandsize];
			unsigned long long startpos = (unsigned long long)this->SpecHeader.headsize + (unsigned long long)z * bandsize;
			ifs.seekg(startpos);
			ifs.read(RAWBandImgbuff, bandsize);
			ifs.close();
			// Bild umsortieren auf vereinbartes Standardformat
			for (unsigned long long j = 0; j < this->SpecHeader.imgsize[2]; j++) //y
			{
				for (unsigned long long i = 0; i < this->SpecHeader.imgsize[0]; i++) //x
				{
					unsigned long long rawoff = (i + j * this->SpecHeader.imgsize[0]) * this->SpecHeader.pixelsize;
					unsigned long long bandoff = (j + i * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize;
					std::memmove(&BandImgbuff[bandoff], &RAWBandImgbuff[rawoff], this->SpecHeader.pixelsize);
				};
			};
			delete[] RAWBandImgbuff;
			return 0;
		};
		// band interleaved by pixel
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			for (unsigned long long j = 0; j < this->SpecHeader.imgsize[2]; j++)
			{
				for (unsigned long long i = 0; i < this->SpecHeader.imgsize[0]; i++)
				{
					unsigned long long fileoff = (unsigned long long)this->SpecHeader.headsize + ((unsigned long long)z + (i + j * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[1])* this->SpecHeader.pixelsize;
					unsigned long long bandoff = (j + i * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize;
					ifs.seekg(fileoff);
					ifs.read(&BandImgbuff[bandoff], this->SpecHeader.pixelsize);
				};
			};
			ifs.close();
			return 0;
		};
	};
	// Err
	this->ErrorMsgLog("In SpecIL_Base::getPlane_RAW_Frame(): Invalid Parameter(s) !");
	return -1;
};
//
int SpecIL_Base::getPlane_Frame_NCWF(void* plane, int x, int y, int z)
{
	char* FrameImgbuff = static_cast<char*>(plane);
	// Daten vollstaendig im Speicher
	if (this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);
		// band sequential
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long frameoff = 0;
			unsigned long long cubeoff = 0;
			unsigned long long framestart = 0;
			for (int j = 0; j < this->SpecHeader.imgsize[1]; j++)
			{
				framestart = ((unsigned long long)y + (unsigned long long)j * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize;
				for (int i = 0; i < this->SpecHeader.imgsize[0]; i++)
				{
					cubeoff = framestart + ((unsigned long long)i * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize;
					std::memmove(&FrameImgbuff[frameoff], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
					frameoff = frameoff + this->SpecHeader.pixelsize;
				};
			};
			return 0;
		};
		// band interleaved by line
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			this->ErrorMsgLog("In SpecIL_Base::getPlane_NCWF_Frame(): band interleaved by line is not supported!");
			return -1;
		};
		// band interleaved by pixel
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			this->ErrorMsgLog("In SpecIL_Base::getPlane_NCWF_Frame(): band interleaved by pixel is not supported!");
			return -1;
		};
	};
	// Daten auf HDD
	// oder von/auf HDD arbeiten?
	if (this->SpecHeader.type == 2)
	{
		std::ifstream ifs(this->SpecHeader.filename, std::fstream::binary);
		// band sequential
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{

			unsigned long long frameoff = 0;
			unsigned long long fileoff = 0;
			unsigned long long framestart = 0;
			for (int j = 0; j < this->SpecHeader.imgsize[1]; j++)
			{
				framestart = ((unsigned long long)y + (unsigned long long)j * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize + this->SpecHeader.headsize;
				for (int i = 0; i < this->SpecHeader.imgsize[0]; i++)
				{
					fileoff = framestart + ((unsigned long long)i * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize;
					ifs.seekg(fileoff);
					ifs.read(&FrameImgbuff[frameoff], this->SpecHeader.pixelsize);
					frameoff = frameoff + this->SpecHeader.pixelsize;
				};
			};
			return 0;
		};
		// band interleaved by line
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			this->ErrorMsgLog("In SpecIL_Base::getPlane_NCWF_Frame(): band interleaved by line is not supported!");
			return -1;
		};
		// band interleaved by pixel
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			this->ErrorMsgLog("In SpecIL_Base::getPlane_NCWF_Frame(): band interleaved by pixel is not supported!");
			return -1;
		};
	};
	// Err
	this->ErrorMsgLog("In SpecIL_Base::getPlane_NCWF_Frame(): Invalid parameters!");
	return -1;
};
//
int SpecIL_Base::getPlane_Sample_NCWF(void* plane, int x, int y, int z)
{
	char* SampleImgbuff = static_cast<char*>(plane);
	// Daten vollstaendig im Speicher
	if (this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);
		// band sequential
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long samplestart = 0;
			unsigned long long cubeoff = 0;
			unsigned long long sampleoff = 0;
			for (int i = 0; i < this->SpecHeader.imgsize[2]; i++) // y
			{
				samplestart = (i + (unsigned long long)x * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize;
				for (int j = 0; j < this->SpecHeader.imgsize[1]; j++) // z
				{
					cubeoff = samplestart + ((unsigned long long)j * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize;
					std::memmove(&SampleImgbuff[sampleoff], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
					sampleoff = sampleoff + this->SpecHeader.pixelsize;
				};
			};
			return 0;
		};
		// band interleaved by line
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			// Err
			this->ErrorMsgLog("In SpecIL_Base::getPlane_NCWF_Sample(): band interleaved by line is not supported!");
			return -1;
		};
		// band interleaved by pixel
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			this->ErrorMsgLog("In SpecIL_Base::getPlane_NCWF_Sample(): band interleaved by pixel is not supported!");
			return -1;
		};
	};
	// Daten auf HDD
	// oder von/auf HDD arbeiten?
	if (this->SpecHeader.type == 2)
	{
		std::ifstream ifs(this->SpecHeader.filename, std::fstream::binary);
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);
		// band sequential
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long samplestart = 0;
			unsigned long long fileoff = 0;
			unsigned long long sampleoff = 0;


			for (int i = 0; i < this->SpecHeader.imgsize[2]; i++) // y
			{
				samplestart = (i + (unsigned long long)x * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize;

				for (int j = 0; j < this->SpecHeader.imgsize[1]; j++) // z
				{
					fileoff = samplestart + ((unsigned long long)j * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize + this->SpecHeader.headsize;
					ifs.seekg(fileoff);
					ifs.read(&SampleImgbuff[sampleoff], this->SpecHeader.pixelsize);
					sampleoff = sampleoff + this->SpecHeader.pixelsize;
				};
			};
			return 0;
		};
		// band interleaved by line
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			// Err
			this->ErrorMsgLog("In SpecIL_Base::getPlane_NCWF_Sample(): band interleaved by line is not supported!");
			return -1;
		};
		// band interleaved by pixel
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			this->ErrorMsgLog("In SpecIL_Base::getPlane_NCWF_Sample(): band interleaved by pixel is not supported!");
			return -1;
		};
	};
	// Err
	this->ErrorMsgLog("In SpecIL_Base::getPlane_NCWF_Sample(): Invalid parameters!");
	return -1;
};
//
int SpecIL_Base::getVector(void* vector, int x, int y, int z)
{
	// x - Vektor
	if(x < 0 && y < this->SpecHeader.imgsize[2] && z < this->SpecHeader.imgsize[1])
	{
		this->getVector_X(vector, y, z);
		return 0;
	};
	// y - Vektor
	if(x < this->SpecHeader.imgsize[0] && y < 0 && z < this->SpecHeader.imgsize[1])
	{
		this->getVector_Y(vector, x, z);
		return 0;
	};
	// z - Vektor
	if(x < this->SpecHeader.imgsize[0] && y < this->SpecHeader.imgsize[2] && z < 0)
	{
		this->getVector_Z(vector, x, y);
		return 0;
	};
	//Err
	this->ErrorMsgLog("In SpecIL_Base::getVector(): invalid parameters x, y, z, interleave or type");
	return -1;
};
//
int SpecIL_Base::getVector_X(void* vector, int y, int z)
{
	char* xVecbuff = static_cast< char* >(vector);
	if(this->SpecHeader.type == 1)
	{
		unsigned long long cubeoff;
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			cubeoff = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * ( (unsigned long long)z + this->SpecHeader.imgsize[1] * (unsigned long long)y );
			std::memmove(xVecbuff, &Cubebuff[cubeoff], this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0]);
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			cubeoff = (((unsigned long long)z * this->SpecHeader.imgsize[2] + (unsigned long long)y) * this->SpecHeader.imgsize[0]) * this->SpecHeader.pixelsize;
			std::memmove(xVecbuff, &Cubebuff[cubeoff], this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0]);
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			cubeoff = ((unsigned long long)z + (unsigned long long)y * this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[0]) * this->SpecHeader.pixelsize;
			unsigned long long jump = this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
			for(unsigned long long i = 0; i < this->SpecHeader.imgsize[0]; i++)
			{
				std::memmove(&xVecbuff[this->SpecHeader.pixelsize * i], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
				cubeoff = cubeoff + jump;
			};
		};
		return 0;
	};

	if(this->SpecHeader.type == 2)
	{
		std::ifstream ifs( this->SpecHeader.filename, std::fstream::binary);
		unsigned long long fileoff;
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			fileoff = (unsigned long long)this->SpecHeader.headsize + this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * ( (unsigned long long)z + this->SpecHeader.imgsize[1] * (unsigned long long)y );
			ifs.seekg(fileoff);
			ifs.read(xVecbuff, this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0]);
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			fileoff = (unsigned long long)this->SpecHeader.headsize + (((unsigned long long)z * this->SpecHeader.imgsize[2] + (unsigned long long)y) * this->SpecHeader.imgsize[0]) * this->SpecHeader.pixelsize;
			ifs.seekg(fileoff);
			ifs.read(xVecbuff, this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0]);
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			fileoff = (unsigned long long)this->SpecHeader.headsize + ((unsigned long long)z + (unsigned long long)y * this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[0]) * this->SpecHeader.pixelsize;
			unsigned long long jump = this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
			for(unsigned long long i = 0; i < this->SpecHeader.imgsize[0]; i++)
			{
				ifs.seekg(fileoff);
				ifs.read(&xVecbuff[this->SpecHeader.pixelsize * i], this->SpecHeader.pixelsize);
				fileoff = fileoff + jump;
			};
		};
		ifs.close();
		return 0;
	};
	//Err
	this->ErrorMsgLog("In SpecIL_Base::getVector_X(): invalid parameters x, y, z, interleave or type");
	return -1;
};
//
int SpecIL_Base::getVector_Y(void* vector, int x, int z)
{
	char* yVecbuff = static_cast< char* >(vector);
	unsigned long long jump;

	if(this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);
		unsigned long long cubeoff;
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			cubeoff = this->SpecHeader.pixelsize * (this->SpecHeader.imgsize[0] * (unsigned long long)z + (unsigned long long)x);
			jump = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1];
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			cubeoff = (this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * (unsigned long long)z + (unsigned long long)x) * this->SpecHeader.pixelsize;
			jump =  this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			cubeoff = (this->SpecHeader.imgsize[1] * (unsigned long long)x + (unsigned long long)z) * this->SpecHeader.pixelsize;
			jump = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
		};
		for(unsigned long long i = 0; i < this->SpecHeader.imgsize[2]; i++)
		{
			std::memmove(&yVecbuff[i * this->SpecHeader.pixelsize], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
			cubeoff = cubeoff + jump;
		};
		return 0;
	};

	if(this->SpecHeader.type == 2)
	{
		std::ifstream ifs( this->SpecHeader.filename, std::fstream::binary);
		unsigned long long fileoff;
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			fileoff = (unsigned long long)this->SpecHeader.headsize + this->SpecHeader.pixelsize * (this->SpecHeader.imgsize[0] * (unsigned long long)z + (unsigned long long)x);
			jump = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1];
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			fileoff = (unsigned long long)this->SpecHeader.headsize + (this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * (unsigned long long)z + (unsigned long long)x) * this->SpecHeader.pixelsize;
			jump =  this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			fileoff = (unsigned long long)this->SpecHeader.headsize + (this->SpecHeader.imgsize[1] * (unsigned long long)x + (unsigned long long)z) * this->SpecHeader.pixelsize;
			jump = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
		};
		for(unsigned long long i = 0; i < this->SpecHeader.imgsize[2]; i++)
		{
			ifs.seekg(fileoff);
			ifs.read(&yVecbuff[i * this->SpecHeader.pixelsize], this->SpecHeader.pixelsize);
			fileoff = fileoff + jump;
		};
		ifs.close();
		return 0;
	};
	//Err
	this->ErrorMsgLog("In SpecIL_Base::getVector_Y(): invalid parameter");
	return -1;
};
//
int SpecIL_Base::getVector_Z(void* vector, int x, int y)
{
	char* zVecbuff = static_cast< char* >(vector);
	unsigned long long jump;
	if(this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);
		unsigned long long cubeoff;
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			cubeoff = ( this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * (unsigned long long)y + (unsigned long long)x ) * this->SpecHeader.pixelsize;
			jump = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0];
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			cubeoff = ( this->SpecHeader.imgsize[0] * (unsigned long long)y + (unsigned long long)x ) * this->SpecHeader.pixelsize;
			jump = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize;
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			cubeoff = ( (unsigned long long)x * this->SpecHeader.imgsize[1] + (unsigned long long)y * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1]) * this->SpecHeader.pixelsize;
			std::memmove(zVecbuff, &Cubebuff[cubeoff], this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize);
			return 0;			
		};
		for(unsigned long long i = 0; i < this->SpecHeader.imgsize[1]; i++)
		{
			std::memmove(&zVecbuff[i * this->SpecHeader.pixelsize], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
			cubeoff = cubeoff + jump;
		};
		return 0;
	};
	if(this->SpecHeader.type == 2)
	{
		std::ifstream ifs( this->SpecHeader.filename, std::fstream::binary);
		unsigned long long fileoff;
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			fileoff = (unsigned long long)this->SpecHeader.headsize + ( this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * (unsigned long long)y + (unsigned long long)x ) * this->SpecHeader.pixelsize;
			jump = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0];
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			fileoff = (unsigned long long)this->SpecHeader.headsize + ( this->SpecHeader.imgsize[0] * (unsigned long long)y + (unsigned long long)x ) * this->SpecHeader.pixelsize;
			jump = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize;
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			fileoff = (unsigned long long)this->SpecHeader.headsize + ((unsigned long long)x * this->SpecHeader.imgsize[1] + (unsigned long long)y * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1]) * this->SpecHeader.pixelsize;

			ifs.seekg(fileoff);
			ifs.read(zVecbuff, this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize);

			ifs.close();
			return 0;
		};
		for(unsigned long long i = 0; i < this->SpecHeader.imgsize[1]; i++)
		{
			ifs.seekg(fileoff);
			ifs.read(&zVecbuff[i * this->SpecHeader.pixelsize], this->SpecHeader.pixelsize);
			fileoff = fileoff + jump;
		};
		ifs.close();
		return 0;
	};
	//Err
	this->ErrorMsgLog("In SpecIL_Base::getVector_Z(): invalid parameter");
	return -1;
};
//
int SpecIL_Base::getVector_NX(void* vector, int y, int z)
{
	char* xVecbuff = static_cast< char* >(vector);
	if (this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			for (unsigned long long i = 0; i <this->SpecHeader.imgsize[0]; i++)
			{
				unsigned long long cubeoff = (((unsigned long long)z * this->SpecHeader.imgsize[0] + i) * this->SpecHeader.imgsize[2] + (unsigned long long)y) * this->SpecHeader.pixelsize;
				std::memmove(&xVecbuff[i*this->SpecHeader.pixelsize], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
			};
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			this->ErrorMsgLog("In SpecIL_Base::getVector_NX(): band interleaved by line is not supported!");
			return -1;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			this->ErrorMsgLog("In SpecIL_Base::getVector_NX(): band interleaved by pixel is not supported!");
			return -1;
		};
	};

	if (this->SpecHeader.type == 2)
	{
		std::ifstream ifs(this->SpecHeader.filename, std::fstream::binary);
		unsigned long long fileoff;
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			for (unsigned long long i = 0; i < this->SpecHeader.imgsize[0]; i++)
			{
				fileoff = (((unsigned long long)z * this->SpecHeader.imgsize[0] + i) * this->SpecHeader.imgsize[2] + (unsigned long long)y) * this->SpecHeader.pixelsize + this->SpecHeader.headsize;
				ifs.seekg(fileoff);
				ifs.read(&xVecbuff[i * this->SpecHeader.pixelsize], this->SpecHeader.pixelsize);
			};
			ifs.close();
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			ifs.close();
			this->ErrorMsgLog("In SpecIL_Base::getVector_NX(): band interleaved by line is not supported!");
			return -1;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			ifs.close();
			this->ErrorMsgLog("In SpecIL_Base::getVector_NX(): band interleaved by pixel is not supported!");
			return -1;
		};
	};
	//Err
	this->ErrorMsgLog("In SpecIL_Base::getVector_NX(): invalid parameter");
	return -1;
};
//
int SpecIL_Base::getVector_NY(void* vector, int x, int z)
{
	char* yVecbuff = static_cast< char* >(vector);

	if (this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);

		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long cubeoff = ((unsigned long long)x + (unsigned long long)z * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize;
			std::memmove(yVecbuff, &Cubebuff[cubeoff], this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize);
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			this->ErrorMsgLog("In SpecIL_Base::getVector_NY(): band interleaved by line is not supported!");
			return -1;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			this->ErrorMsgLog("In SpecIL_Base::getVector_NY(): band interleaved by pixel is not supported!");
			return -1;
		};
	};

	if (this->SpecHeader.type == 2)
	{
		std::ifstream ifs(this->SpecHeader.filename, std::fstream::binary);
		unsigned long long fileoff;
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			fileoff = ((unsigned long long)x + (unsigned long long)z * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize + this->SpecHeader.headsize;
			ifs.seekg(fileoff);
			ifs.read(yVecbuff, this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize);
			ifs.close();
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			ifs.close();
			this->ErrorMsgLog("In SpecIL_Base::getVector_NY(): band interleaved by line is not supported!");
			return -1;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			ifs.close();
			this->ErrorMsgLog("In SpecIL_Base::getVector_NY(): band interleaved by pixel is not supported!");
			return -1;
		};
	};
	//Err
	this->ErrorMsgLog("In SpecIL_Base::getVector_NY(): invalid parameter");
	return -1;
};
//
int SpecIL_Base::getVector_NZ(void* vector, int x, int y)
{
	char* zVecbuff = static_cast< char* >(vector);
	if (this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			for (unsigned long long i = 0; i <this->SpecHeader.imgsize[1]; i++)
			{
				unsigned long long cubeoff = ((unsigned long long)y + ((unsigned long long)x + i * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize;
				std::memmove(&zVecbuff[i*this->SpecHeader.pixelsize], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
			};
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			this->ErrorMsgLog("In SpecIL_Base::getVector_NZ(): band interleaved by line is not supported!");
			return -1;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			this->ErrorMsgLog("In SpecIL_Base::getVector_NZ(): band interleaved by pixel is not supported!");
			return -1;
		};
	};
	if (this->SpecHeader.type == 2)
	{
		std::ifstream ifs(this->SpecHeader.filename, std::fstream::binary);
		unsigned long long fileoff;
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			for (unsigned long long i = 0; i <this->SpecHeader.imgsize[1]; i++)
			{
				fileoff = ((unsigned long long)y + ((unsigned long long)x + i * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize + this->SpecHeader.headsize;
				ifs.seekg(fileoff);
				ifs.read(&zVecbuff[i*this->SpecHeader.pixelsize], this->SpecHeader.pixelsize);
			};
			ifs.close();
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			ifs.close();
			this->ErrorMsgLog("In SpecIL_Base::getVector_NZ(): band interleaved by line is not supported!");
			return -1;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			ifs.close();
			this->ErrorMsgLog("In SpecIL_Base::getVector_NZ(): band interleaved by pixel is not supported!");
			return -1;
		};
	};
	//Err
	this->ErrorMsgLog("In SpecIL_Base::getVector_NZ(): invalid parameter");
	return -1;
};
//
int SpecIL_Base::getPoint(void* point, int x, int y, int z)
{
	// Zu den Profilen: Fuer die HySpex Daten ist das Profil egal, nur fuer die Nuance Vertauschung nicht....
	unsigned long long offset;
	char* Point = static_cast< char* >(point);
	if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
	{
		offset = (this->SpecHeader.imgsize[0] * (this->SpecHeader.imgsize[1] * (unsigned long long)y + (unsigned long long)z) + (unsigned long long)x) * this->SpecHeader.pixelsize;
	};
	if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
	{
		offset = ((unsigned long long)x + ((unsigned long long)y + (unsigned long long)z * this->SpecHeader.imgsize[2]) * this->SpecHeader.imgsize[0]) * this->SpecHeader.pixelsize;
	};
	if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
	{
		offset = ((unsigned long long)z + ((unsigned long long)x + (unsigned long long)y * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[1])* this->SpecHeader.pixelsize;
	};
	if (this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);
		std::memmove(Point, &Cubebuff[offset], this->SpecHeader.pixelsize);
		return 0;
	};
	if (this->SpecHeader.type == 2)
	{
		std::ifstream ifs(this->SpecHeader.filename, std::fstream::binary);
		ifs.seekg(offset + (unsigned long long)this->SpecHeader.headsize);
		ifs.read(Point, this->SpecHeader.pixelsize);
		ifs.close();
		return 0;
	};
	//Err
	this->ErrorMsgLog("In SpecIL_Base::getPoint(): invalid parameter");
	return -1;
};
//
int SpecIL_Base::getPoint_N(void* point, int x, int y, int z)
{
	char* Pointbuff = static_cast< char* >(point);
	if (this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long cubeoff = ((unsigned long long)y + ((unsigned long long)x + (unsigned long long)z * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize;
			std::memmove(Pointbuff, &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			this->ErrorMsgLog("In SpecIL_Base::getPoint_N(): band interleaved by line is not supported!");
			return -1;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			this->ErrorMsgLog("In SpecIL_Base::getPoint_N(): band interleaved by pixel is not supported!");
			return -1;
		};
	};
	if (this->SpecHeader.type == 2)
	{
		std::ifstream ifs(this->SpecHeader.filename, std::fstream::binary);
		unsigned long long fileoff;
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			fileoff = ((unsigned long long)y + ((unsigned long long)x + (unsigned long long)z * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[2]) * this->SpecHeader.pixelsize + this->SpecHeader.headsize;
			ifs.seekg(fileoff);
			ifs.read(Pointbuff, this->SpecHeader.pixelsize);
			ifs.close();
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			ifs.close();
			this->ErrorMsgLog("In SpecIL_Base::getPoint_N(): band interleaved by line is not supported!");
			return -1;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			ifs.close();
			this->ErrorMsgLog("In SpecIL_Base::getPoint_N(): band interleaved by pixel is not supported!");
			return -1;
		};
	};
	//Err
	this->ErrorMsgLog("In SpecIL_Base::getPoint_N(): invalid parameter");
	return -1;
};
//
void SpecIL_Base::setDataType(t_SpecHead::t_data_type dt)
{
	this->SpecHeader.data_type = dt;
	if (this->SpecHeader.data_type == t_SpecHead::DT_8_BYTE)
	{
		this->SpecHeader.pixelsize = 1;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_16_SINT || this->SpecHeader.data_type == t_SpecHead::DT_16_UINT)
	{
		this->SpecHeader.pixelsize = 2;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_32_SLONG || this->SpecHeader.data_type == t_SpecHead::DT_32_FLOAT || this->SpecHeader.data_type == t_SpecHead::DT_32_ULONG)
	{
		this->SpecHeader.pixelsize = 4;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_64_DOUBLE || this->SpecHeader.data_type == t_SpecHead::DT_2x32_COMPLEX || this->SpecHeader.data_type == t_SpecHead::DT_64_SLONG || this->SpecHeader.data_type == t_SpecHead::DT_64_ULONG)
	{
		this->SpecHeader.pixelsize = 8;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_2x64_COMPLEX)
	{
		this->SpecHeader.pixelsize = 16;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_UNKNOWN)
	{
		this->SpecHeader.pixelsize = 0;
	};

	this->setDataTypeMaxMin();
};
//
void SpecIL_Base::setImageSize(unsigned int width, unsigned int height, unsigned int planes)
{
	this->SpecHeader.imgsize[0] = width;
	this->SpecHeader.imgsize[1] = planes;
	this->SpecHeader.imgsize[2] = height;
};
//
int SpecIL_Base::writeTGDmetaFile(std::string outTGDmetaFile)
{
	std::fstream fsMetaOutFile;
	fsMetaOutFile.open(outTGDmetaFile, std::fstream::out | std::fstream::binary);

	if (fsMetaOutFile.fail() == false)
	{
		fsMetaOutFile << "datafilename = " << this->SpecHeader.filename.substr(this->SpecHeader.filename.find_last_of("/") + 1) << std::endl;

		// leere Zeile
		fsMetaOutFile << std::endl << std::endl;

		// Modul
		fsMetaOutFile << "[SpecILfile]" << std::endl;

		//cameraname
		fsMetaOutFile << "cameraname=" << this->SpecHeader.ID << std::endl;
		//exposure
		fsMetaOutFile << "exposure=" << this->SpecHeader.Integration_time << std::endl;
		//planes
		fsMetaOutFile << "planes=" << this->SpecHeader.imgsize[1] << std::endl;
		//sensor
		//fsMetaOutFile << "sensor=" << << std::endl;
		//sensorheight
		fsMetaOutFile << "sensorheight=" << this->SpecHeader.imgsize[2] << std::endl;
		//sensorwidth
		fsMetaOutFile << "sensorwidth=" << this->SpecHeader.imgsize[0] << std::endl;
		
		if (this->SpecHeader.wavelen.size() > 0)
		{
			//wavelengthhigh = 950
			fsMetaOutFile << "wavelengthhigh=" << *(this->SpecHeader.wavelen.begin()) << std::endl;
			//wavelengthlow = 450
			fsMetaOutFile << "wavelengthlow=" << *(this->SpecHeader.wavelen.end()-1) << std::endl;

			//wavelengths = "450 460 470 480 490 500 510 520 530 540 550 560 570 580 590 600 610 620 630 640 650 660 670 680 690 700 710 720 730 740 750 760 770 780 790 800 810 820 830 840 850 860 870 880 890 900 910 920 930 940 950"
			fsMetaOutFile << "wavelengths=\"";
			std::vector<float>::iterator ite = this->SpecHeader.wavelen.begin();
			while (ite != this->SpecHeader.wavelen.end())
			{
				fsMetaOutFile << *ite << " ";
				ite++;
			};
			fsMetaOutFile << "\"";

			//wavelengthstep = 10
		};

		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			fsMetaOutFile << "interleave=bsq" << std::endl;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			fsMetaOutFile << "interleave=bip" << std::endl;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			fsMetaOutFile << "interleave=bil" << std::endl;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_UNKNOWN)
		{
			fsMetaOutFile << "interleave=unknown" << std::endl;
		};

		fsMetaOutFile.close();

		return 0;
	};

	this->ErrorMsgLog("Error in SpecIL_Base::writeTGDmetaFile(): Error");
	return -1;
}
//
void SpecIL_Base::close()
{
	this->~SpecIL_Base();
};
//
int SpecIL_Base::write()
{
	// Daten in die Zieldatei schreiben
/*	if (this->writeDataToHySpexFile(this->SpecHeader.filename) == 0)
	{
		// .hdr Datei schreiben
		std::string outhdrfile = this->SpecHeader.filename.substr(0, this->SpecHeader.filename.find_last_of("."));
		outhdrfile = outhdrfile + ".hdr";
		this->writeENVIhdr(outhdrfile);

		// temp datei loeschen
		std::remove(this->tempOutFileName.c_str());
		return 0;
	}*/

	std::string outfile = this->SpecHeader.filename.substr(0, this->SpecHeader.filename.find_last_of("."));
	std::string endung = this->SpecHeader.filename.substr(this->SpecHeader.filename.find_last_of("."), std::string::npos);

	if (endung == ".img")
	{
		this->writeDataToHySpexFile(this->SpecHeader.filename);

		std::string outhdrfile = outfile + ".hdr";
		this->writeENVIhdr(outhdrfile);

		// temp datei loeschen
		std::remove(this->tempOutFileName.c_str());
		return 0;
	};

	if (endung == ".tgd")
	{
		this->writeDataToTGDfile(this->SpecHeader.filename);

		std::string outhdrfile = outfile + ".tgd.hdr";
		this->writeENVIhdr(outhdrfile);

		// tgsd meta
		std::string outtgdmetafile = outfile + ".tgd.meta";
		this->writeTGDmetaFile(outtgdmetafile);
		// temp datei loeschen
		std::remove(this->tempOutFileName.c_str());
		return 0;
	};

	this->ErrorMsgLog("In SpecIL_Base::write(): Destination file format is not supported");
	return -1;
};
//
int SpecIL_Base::setPlane(void* plane, int x, int y, int z)
{
	if (this->SpecHeader.data_type == t_SpecHead::t_data_type::DT_UNKNOWN)
	{
		// Err
		this->ErrorMsgLog("In SpecIL_Base::setPlane(): SpecHeader.data_type == DT_UNKNOWN -> use setDataType");
		return -1;
	};

	if (this->NewFileData == 0)
	{
		this->initNewFileCube();
	};

	// Ein Band setzen
	if (x < 0 && y < 0 && z < this->SpecHeader.imgsize[1])
	{
		this->setPlane_Band(plane, z);

		return 0;
	};

	// Ein Frame setzen
	if (x < 0 && z < 0 && y < this->SpecHeader.imgsize[2])
	{
		this->setPlane_Frame(plane,y);

		return 0;
	};

	// Ein Samplebild setzen
	if (y < 0 && z < 0 && x < this->SpecHeader.imgsize[0])
	{
		this->setPlane_Sample(plane, x);
		return 0;
	};

	// Err
	this->ErrorMsgLog("In SpecIL_Base::setPlane(): invalid parameters");
	return -1;
};
//
int SpecIL_Base::setPlane_Band(void* plane, int z)
{
	char* buffer = static_cast<char*>(plane);

	std::fstream fsOut;
	fsOut.open(this->tempOutFileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);//geht
	if (fsOut.fail() == false)
	{
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{

			unsigned long long bandsize = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize;

			long pos = fsOut.tellp();
			std::streampos fsPos = this->SpecHeader.headsize + bandsize * (unsigned long long)z;
			fsOut.seekp(fsPos, std::ios_base::beg);
			fsOut.write(buffer, bandsize);
			fsOut.close();
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			unsigned long long fileoff = (unsigned long long)this->SpecHeader.headsize + this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize * (unsigned long long)z;
			// Zeilegroessegroesse
			unsigned long long linesize = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0];
			// Sprungweite zur naechsten Zeile
			unsigned long long jump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize * this->SpecHeader.imgsize[1];
			// Bild zusammenbauen
			for (unsigned long long i = 0; i < this->SpecHeader.imgsize[2]; i++)
			{
				fsOut.seekp(fileoff, std::ios_base::beg);
				fsOut.write(&buffer[i * linesize], linesize);
				fileoff = fileoff + jump;
			};
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			unsigned long long fileoff = 0;
			unsigned long long bandoff = 0;

			for (unsigned long long j = 0; j < this->SpecHeader.imgsize[2]; j++) //y
			{
				fileoff = (unsigned long long)this->SpecHeader.headsize + ((unsigned long long)z + j * this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[0]) * this->SpecHeader.pixelsize;

				for (unsigned long long i = 0; i < this->SpecHeader.imgsize[0]; i++) //x
				{
					fsOut.seekg(fileoff);
					fsOut.write(&buffer[bandoff], this->SpecHeader.pixelsize);

					bandoff += this->SpecHeader.pixelsize;
					fileoff += this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
				};
			};

			fsOut.close();
			return 0;
		};
	};
	fsOut.close();
	// Err
	this->ErrorMsgLog("In SpecIL_Base::setPlane_Band(): invalid parameters");
	return -1;


/*	// Noch nicht getestet
	std::fstream fsOut;
	fsOut.open(this->tempOutFileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);
	if (fsOut.fail() == false)
	{
		switch (this->SpecHeader.interleave)
		{
		case t_SpecHead::IL_BSQ:
			unsigned long long bandsize = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize;
			long pos = fsOut.tellp();
			std::streampos fsPos = this->SpecHeader.headsize + bandsize * (unsigned long long)z;
			fsOut.seekp(fsPos, std::ios_base::beg);
			fsOut.write(buffer, bandsize);
			break;
		case t_SpecHead::IL_BIL:
			unsigned long long fileoff = (unsigned long long)this->SpecHeader.headsize + this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize * (unsigned long long)z;
			// Zeilegroessegroesse
			unsigned long long linesize = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0];
			// Sprungweite zur naechsten Zeile
			unsigned long long jump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize * this->SpecHeader.imgsize[1];
			// Bild zusammenbauen
			for (unsigned long long i = 0; i < this->SpecHeader.imgsize[2]; i++)
			{
				fsOut.seekp(fileoff, std::ios_base::beg);
				fsOut.write(&buffer[i * linesize], linesize);
				fileoff = fileoff + jump;
			};
			break;
		case t_SpecHead::IL_BIP:
		case t_SpecHead::IL_UNKNOWN:
			// Err
			fsOut.close();
			this->ErrorMsgLog("In SpecIL_Base::setPlane_Band(): Interleave is not supported for writing.");
			return -1;
		};
	};
	fsOut.close();
	return 0;*/
};
//
int SpecIL_Base::initNewFile()
{
	// Header ist in der temporaeren Datei immer 8Byte
	this->SpecHeader.headsize = 8;

	this->SpecHeader.interleave = t_SpecHead::IL_BSQ;//vorerst BSQ

	this->NewFileData = 0;
	std::ofstream ofFile;
	ofFile.open(this->tempOutFileName.c_str(), std::ios_base::trunc | std::ios_base::binary);
	if (ofFile.fail() == false)
	{
		char buffer8[8] = { 'S', 'P', 'E', 'C', 'I', 'L', 0x00, 0x00 };
		ofFile.write(buffer8, 8);
		return 0;
	}
	ofFile.close();
	this->ErrorMsgLog("In SpecIL_Base::initNewFile(): invalid parameters");
	return -1;
};
//
void SpecIL_Base::setFileMode(unsigned int fm)
{
	this->FileMode = fm;
	if (fm == 1)
	{
	//	this->tempOutFileName = this->SpecHeader.filename + ".temp";

		// testen auf E:
		this->tempOutFileName = "C:\\specil.temp";
	};
};
//
int SpecIL_Base::initNewFileCube()
{
	std::ofstream ofFile;

	ofFile.open(this->tempOutFileName.c_str(), std::ofstream::binary | std::ofstream::app);

	if (ofFile.fail() == false)
	{
		ofFile.seekp(std::ios_base::end);
		unsigned long long bandsize = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize;

		char* buffer = new char[bandsize];

		for (unsigned long long z = 0; z < this->SpecHeader.imgsize[1]; z++)
		{
			ofFile.write(buffer, bandsize);
		};

		ofFile.close();
		delete[] buffer;
		buffer = NULL;
		this->NewFileData = 1;
		return 0;
	}
	ofFile.close();
	this->ErrorMsgLog("In SpecIL_Base::initNewFileCube(): invalid parameters");
	return -1;
};
//
int SpecIL_Base::setVector(void* vector, int x, int y, int z)
{
	if (this->SpecHeader.data_type == t_SpecHead::t_data_type::DT_UNKNOWN)
	{
		// Err
		this->ErrorMsgLog("In SpecIL_Base::setPlane(): SpecHeader.data_type == DT_UNKNOWN -> use setDataType");
		return -1;
	};

	if (this->NewFileData == 0)
	{
		this->initNewFileCube();
	};

	// x vector
	if (x < 0 && y < this->SpecHeader.imgsize[2] && z < this->SpecHeader.imgsize[1])
	{
		this->setVector_X(vector, y, z);
		return 0;
	};

	// y - Vektor
	if (x < this->SpecHeader.imgsize[0] && y < 0 && z < this->SpecHeader.imgsize[1])
	{
		this->setVector_Y(vector, x, z);
		return 0;
	};

	// z - Vektor
	if (x < this->SpecHeader.imgsize[0] && y < this->SpecHeader.imgsize[2] && z < 0)
	{
		this->setVector_Z(vector, x, y);
		return 0;
	};

	this->ErrorMsgLog("In SpecIL_Base::setVector(): invalid parameters");
	return -1;
};
//
int SpecIL_Base::setVector_X(void* vector, int y, int z)
{
	unsigned long long fileoff;

	if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
	{
		std::fstream fsOut;
		fsOut.open(this->tempOutFileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);
		if (fsOut.fail() == false)
		{
			char* buffer = static_cast<char*>(vector);

			unsigned long long vecsize = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;

			fileoff = this->SpecHeader.headsize + (((unsigned long long)z * this->SpecHeader.imgsize[2] + (unsigned long long)y) * this->SpecHeader.imgsize[0])* this->SpecHeader.pixelsize;

			fsOut.seekp(fileoff);
			fsOut.write(buffer, vecsize);

			fsOut.close();
			return 0;
		};
		fsOut.close();
	};

	if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
	{
		std::fstream fsOut;
		fsOut.open(this->tempOutFileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);
		if (fsOut.fail() == false)
		{
			char* buffer = static_cast<char*>(vector);

			unsigned long long vecsize = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;

			fileoff = (unsigned long long)this->SpecHeader.headsize + this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * ((unsigned long long)z + this->SpecHeader.imgsize[1] * (unsigned long long)y);

			fsOut.seekp(fileoff);
			fsOut.write(buffer, vecsize);

			fsOut.close();
			return 0;
		};
		fsOut.close();
	};

	this->ErrorMsgLog("In SpecIL_Base::getVector_X(): invalid parameters");
	return -1;
};
//
int SpecIL_Base::setVector_Y(void* vector, int x, int z)
{
	char* yVecbuff = static_cast< char* >(vector);

	unsigned long long fileoff;
	unsigned long long jump;

	if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
	{
		std::fstream fsOut;
		fsOut.open(this->tempOutFileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);
		if (fsOut.fail() == false)
		{
			fileoff = this->SpecHeader.headsize + (this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * (unsigned long long)z + (unsigned long long)x) * this->SpecHeader.pixelsize;
			jump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;

			for (unsigned long long i = 0; i < this->SpecHeader.imgsize[2]; i++)
			{	
				fsOut.seekp(fileoff);
				fsOut.write(&yVecbuff[i * this->SpecHeader.pixelsize], this->SpecHeader.pixelsize);
				fileoff = fileoff + jump;
			};

			fsOut.close();
			return 0;
		};
		fsOut.close();
	};

	if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
	{
		std::fstream fsOut;
		fsOut.open(this->tempOutFileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);
		if (fsOut.fail() == false)
		{
			fileoff = (unsigned long long)this->SpecHeader.headsize + this->SpecHeader.pixelsize * (this->SpecHeader.imgsize[0] * (unsigned long long)z + (unsigned long long)x);
			jump = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1];

			for (unsigned long long i = 0; i < this->SpecHeader.imgsize[2]; i++)
			{
				fsOut.seekp(fileoff);
				fsOut.write(&yVecbuff[i * this->SpecHeader.pixelsize], this->SpecHeader.pixelsize);
				fileoff = fileoff + jump;
			};

			fsOut.close();
			return 0;
		};
		fsOut.close();
	};

	this->ErrorMsgLog("In SpecIL_Base::getVector_Y(): invalid parameters");
	return -1;
};
//
int SpecIL_Base::setVector_Z(void* vector, int x, int y)
{
	char* zVecbuff = static_cast< char* >(vector);
	unsigned long long jump;
	unsigned long long fileoff;

	std::fstream fsOut;
	fsOut.open(this->tempOutFileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);


	if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
	{
		fileoff = this->SpecHeader.headsize + (this->SpecHeader.imgsize[0] * (unsigned long long)y + (unsigned long long)x) * this->SpecHeader.pixelsize;
		jump = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize;

		for (unsigned long long i = 0; i < this->SpecHeader.imgsize[1]; i++)
		{
			fsOut.seekp(fileoff);
			fsOut.write(&zVecbuff[i * this->SpecHeader.pixelsize], this->SpecHeader.pixelsize);
			fileoff = fileoff + jump;
		};

		fsOut.close();
		return 0;
	};

	if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
	{
		fileoff = (unsigned long long)this->SpecHeader.headsize + (this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * (unsigned long long)y + (unsigned long long)x) * this->SpecHeader.pixelsize;
		jump = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0];

		for (unsigned long long i = 0; i < this->SpecHeader.imgsize[1]; i++)
		{
			fsOut.seekp(fileoff);
			fsOut.write(&zVecbuff[i * this->SpecHeader.pixelsize], this->SpecHeader.pixelsize);
			fileoff = fileoff + jump;
		};

		fsOut.close();
		return 0;
	};

	if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
	{
		fileoff = (unsigned long long)this->SpecHeader.headsize + ((unsigned long long)x * this->SpecHeader.imgsize[1] + (unsigned long long)y * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1]) * this->SpecHeader.pixelsize;

		fsOut.seekg(fileoff);
		fsOut.write(zVecbuff, this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize);

		fsOut.close();
		return 0;
	};

	this->ErrorMsgLog("In SpecIL_Base::setVector_Z(): invalid parameters");
	fsOut.close();
	return -1;
};
//
int SpecIL_Base::setPoint(void* point, int x, int y, int z)
{
	unsigned long long fileoff;

	char* Point = static_cast< char* >(point);

	if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
	{
		fileoff = this->SpecHeader.headsize + ((unsigned long long)x + ((unsigned long long)y + (unsigned long long)z * this->SpecHeader.imgsize[2]) * this->SpecHeader.imgsize[0]) * this->SpecHeader.pixelsize;
		
		std::fstream fsOut;
		fsOut.open(this->tempOutFileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);

		fsOut.seekp(fileoff);
		fsOut.write(Point, this->SpecHeader.pixelsize);

		fsOut.close();
		return 0;
	};

	//Err
	this->ErrorMsgLog("In SpecIL_Base::setPoint(): Interleave is not supported for writing.");
	return -1;


/*	// Noch nciht getestet
	switch (this->SpecHeader.interleave)
	{
	case t_SpecHead::IL_BSQ:
		fileoff = this->SpecHeader.headsize + ((unsigned long long)x + ((unsigned long long)y + (unsigned long long)z * this->SpecHeader.imgsize[2]) * this->SpecHeader.imgsize[0]) * this->SpecHeader.pixelsize;
		break;
	case t_SpecHead::IL_BIL:
		fileoff = this->SpecHeader.headsize + ((unsigned long long)z + ((unsigned long long)x + (unsigned long long)y * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[1])* this->SpecHeader.pixelsize;
		break;
	case t_SpecHead::IL_BIP: // Noch implementieren?
	case t_SpecHead::IL_UNKNOWN:
		//Err
		this->ErrorMsgLog("In SpecIL_Base::setPoint(): Interleave is not supported for writing.");
		return -1;
	};

	std::fstream fsOut;
	fsOut.open(this->tempOutFileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);

	fsOut.seekp(fileoff);
	fsOut.write(Point, this->SpecHeader.pixelsize);

	fsOut.close();
	return 0;*/
};
//
int SpecIL_Base::setPlane_Frame(void* plane, int y)
{
	char* FrameImgbuff = static_cast<char*>(plane);

	if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
	{
		std::fstream fsOut;
		fsOut.open(this->tempOutFileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);

		if (fsOut.fail() == false)
		{
			unsigned long long frameRowSize = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;

			unsigned long long jump = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize;

			unsigned long long fileoff = this->SpecHeader.headsize + (unsigned long long)y * frameRowSize;

			for (unsigned long long i = 0; i < this->SpecHeader.imgsize[1]; i++) //z
			{
				fsOut.seekp(fileoff);

				fsOut.write(&FrameImgbuff[frameRowSize*i], frameRowSize);

				fileoff = fileoff + jump;
			};

			fsOut.close();
			return 0;
		};
		fsOut.close();
	};
	if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
	{
		// to do...
	};
	// Err
	this->ErrorMsgLog("In SpecIL_Base::setPlane_Frame(): invalid parameters");
	return -1;
};
//
int SpecIL_Base::setPlane_Sample(void* plane, int x)
{
	char* SampleImgbuff = static_cast<char*>(plane);

	if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
	{
		std::fstream fsOut;
		fsOut.open(this->tempOutFileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);

		if (fsOut.fail() == false)
		{
			unsigned long long sampleoff = 0;
			unsigned long long frameRowjump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
			unsigned long long bandjump = this->SpecHeader.imgsize[2] * frameRowjump;

			unsigned long long startfileoff = this->SpecHeader.headsize + (unsigned long long)x * this->SpecHeader.pixelsize;
			
			for (unsigned long long j = 0; j < this->SpecHeader.imgsize[2]; j++)
			{
				unsigned long long fileoff = startfileoff + j * frameRowjump;

				for (unsigned long long i = 0; i < this->SpecHeader.imgsize[1]; i++)
				{
					fsOut.seekp(fileoff);
					fsOut.write(&SampleImgbuff[sampleoff], this->SpecHeader.pixelsize);
					sampleoff = sampleoff + this->SpecHeader.pixelsize;
					fileoff = fileoff + bandjump;
				};
			};

			fsOut.close();
			return 0;
		};
		fsOut.close();
	};

	if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
	{
		std::fstream fsOut;
		fsOut.open(this->tempOutFileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);

		if (fsOut.fail() == false)
		{
			unsigned long long fileoff = (unsigned long long)this->SpecHeader.headsize + ((unsigned long long)x * this->SpecHeader.pixelsize);
			unsigned long long jump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
			unsigned long long max = this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[2];
			for (unsigned long long i = 0; i < max; i++)
			{
				fsOut.seekp(fileoff);

				fsOut.write(&SampleImgbuff[i * this->SpecHeader.pixelsize], this->SpecHeader.pixelsize);
				fileoff = fileoff + jump;
			};
			fsOut.close();
			return 0;

		};
		fsOut.close();
	};
	// Err
	this->ErrorMsgLog("In SpecIL_Base::setPlane_Sample(): invalid parameters");
	return -1;
};
//
void SpecIL_Base::setInterleave(t_SpecHead::t_interleave il)
{
	this->SpecHeader.interleave = il;
};
//
int SpecIL_Base::getOpenCVDatatype()
{
	if (this->SpecHeader.data_type == t_SpecHead::DT_64_SLONG ||
		this->SpecHeader.data_type == t_SpecHead::DT_64_ULONG ||
		this->SpecHeader.data_type == t_SpecHead::DT_2x32_COMPLEX ||
		this->SpecHeader.data_type == t_SpecHead::DT_2x64_COMPLEX
		)
	{
		this->ErrorMsgLog("In SpecIL_Base::getOpenCVDatatype(): This datatyp is not supported");
		return -1;
	};

	// TGD Daten sind immer 4Byte gross
	std::string endung = this->SpecHeader.filename.substr(this->SpecHeader.filename.find_last_of("."));
	if (0 == endung.compare(".tgd"))
	{
		if (this->SpecHeader.data_type == t_SpecHead::DT_8_BYTE ||
			this->SpecHeader.data_type == t_SpecHead::DT_16_SINT ||
			this->SpecHeader.data_type == t_SpecHead::DT_32_SLONG)
		{
			return 4; // CV_32S;
		};

		if (this->SpecHeader.data_type == t_SpecHead::DT_16_UINT ||
			this->SpecHeader.data_type == t_SpecHead::DT_32_ULONG)
		{
			//		return CV_32U; // gibt es nicht in OpenCV!
			//		this->ErrorMsgLog("In SpecIL_Base::getOpenCVDatatype(): This datatyp is not supported");
			//		return -1;
			return 4; // CV_32S;
		};

		if (this->SpecHeader.data_type == t_SpecHead::DT_32_FLOAT)
		{
			return 5; // CV_32F;
		};
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_8_BYTE)
	{
		return 0; // CV_8U;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_16_SINT)
	{
		return 3; // CV_16S;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_16_UINT)
	{
		return 2; // CV_16U;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_32_SLONG)
	{
		return 4; // CV_32S;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_32_ULONG)
	{
		//		return CV_32U; // gibt es nicht in OpenCV!
		//		this->ErrorMsgLog("In SpecIL_Base::getOpenCVDatatype(): This datatyp is not supported");
		//		return -1;
		return 4; // CV_32S;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_32_FLOAT)
	{
		return 5; // CV_32F;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_64_DOUBLE)
	{
		return 6; // CV_64F;
	};

	this->ErrorMsgLog("In SpecIL_Base::getOpenCVDatatype(): This datatyp is not supported");
	return -1;
};
//
void SpecIL_Base::setCubeMaxSize(unsigned long long cms)
{
	this->cubemaxsize = cms;
};
//
void SpecIL_Base::setHeadersize(unsigned int hs)
{
	this->SpecHeader.headsize = hs;
};
//
void SpecIL_Base::EnableErrorLog()
{
	this->UsingErrorLog = true;
};
//
void SpecIL_Base::DisableErrorLog()
{
	this->UsingErrorLog = false;
};
//
void SpecIL_Base::setDataTypeMaxMin()
{
	if (this->SpecHeader.data_type == t_SpecHead::DT_8_BYTE)
	{
		this->SpecHeader.data_type_maxval = 255.0;
		this->SpecHeader.data_type_minval = 0.0;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_16_SINT)
	{
		this->SpecHeader.data_type_maxval = pow(2, 15) - 1.0;
		this->SpecHeader.data_type_minval = pow(2, 15);
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_16_UINT)
	{
		this->SpecHeader.data_type_maxval = pow(2, 16) - 1.0;
		this->SpecHeader.data_type_minval = 0.0;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_32_SLONG)
	{
		this->SpecHeader.data_type_maxval = pow(2, 31) - 1.0;
		this->SpecHeader.data_type_minval = pow(2, 31);
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_32_FLOAT || this->SpecHeader.data_type == t_SpecHead::DT_2x32_COMPLEX)
	{
		this->SpecHeader.data_type_maxval = FLT_MAX;
		this->SpecHeader.data_type_minval = FLT_MIN;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_32_ULONG)
	{
		this->SpecHeader.data_type_maxval = pow(2, 32) - 1.0;
		this->SpecHeader.data_type_minval = 0.0;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_64_DOUBLE || this->SpecHeader.data_type == t_SpecHead::DT_2x64_COMPLEX)
	{
		this->SpecHeader.data_type_maxval = DBL_MAX;
		this->SpecHeader.data_type_minval = DBL_MIN;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_64_SLONG)
	{
		this->SpecHeader.data_type_maxval = pow(2, 63) - 1.0;
		this->SpecHeader.data_type_minval = pow(2, 63);
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_64_ULONG)
	{
		this->SpecHeader.data_type_maxval = pow(2, 64) - 1.0;
		this->SpecHeader.data_type_minval = 0.0;
	};

	if (this->SpecHeader.data_type == t_SpecHead::DT_UNKNOWN)
	{
		this->SpecHeader.data_type_maxval = 0.0;
		this->SpecHeader.data_type_minval = 0.0;
	};
};

/*//---------------------------------------------------------
//---------------------------------------------------------
int SpecIL_Base::getPlane_Sample(void* plane, int x, int y, int z)
{
	char* SampleImgbuff = static_cast<char*>(plane);
	if (this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			unsigned long long cubeoff = (unsigned long long)x * this->SpecHeader.pixelsize;
			unsigned long long jump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
			unsigned long long maxlines = this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[2];
			for (unsigned long long i = 0; i < maxlines; i++)
			{
				std::memmove(&SampleImgbuff[i * this->SpecHeader.pixelsize], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
				cubeoff = cubeoff + jump;
			};
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long sampleoff = 0;
			unsigned long long framejump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
			unsigned long long bandjump = this->SpecHeader.imgsize[2] * framejump;
			unsigned long long startrawoff = (unsigned long long)x * this->SpecHeader.pixelsize;
			for (unsigned long long j = 0; j < this->SpecHeader.imgsize[2]; j++)
			{
				unsigned long long cubeoff = startrawoff + j * framejump;
				for (unsigned long long i = 0; i < this->SpecHeader.imgsize[1]; i++)
				{
					std::memmove(&SampleImgbuff[sampleoff], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
					sampleoff = sampleoff + this->SpecHeader.pixelsize;
					cubeoff = cubeoff + bandjump;
				};
			};
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			for (unsigned long long k = 0; k < this->SpecHeader.imgsize[1]; k++)		//z
			{
				for (unsigned long long i = 0; i < this->SpecHeader.imgsize[2]; i++)	//y
				{
					unsigned long long cubeoff = (k + ((unsigned long long)x + i * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[1]) * this->SpecHeader.pixelsize;
					unsigned long long sampleoff = (k + i * this->SpecHeader.imgsize[1]) *this->SpecHeader.pixelsize;
					std::memmove(&SampleImgbuff[sampleoff], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
				};
			};
			return 0;
		};
	};
	if (this->SpecHeader.type == 2)
	{
		std::ifstream ifs(this->SpecHeader.filename, std::fstream::binary);
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			unsigned long long fileoff = (unsigned long long)this->SpecHeader.headsize + ((unsigned long long)x * this->SpecHeader.pixelsize);
			unsigned long long jump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
			unsigned long long maxlines = this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[2];
			for (unsigned long long i = 0; i < maxlines; i++)
			{
				ifs.seekg(fileoff);
				ifs.read(&SampleImgbuff[i * this->SpecHeader.pixelsize], this->SpecHeader.pixelsize);
				fileoff = fileoff + jump;
			};
			ifs.close();
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long sampleoff = 0;
			unsigned long long framejump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
			unsigned long long bandjump = this->SpecHeader.imgsize[2] * framejump;
			unsigned long long startfileoff = (unsigned long long)this->SpecHeader.headsize + (unsigned long long)x * this->SpecHeader.pixelsize;
			for (unsigned long long j = 0; j < this->SpecHeader.imgsize[2]; j++)
			{
				unsigned long long fileoff = startfileoff + j * framejump;
				for (unsigned long long i = 0; i < this->SpecHeader.imgsize[1]; i++)
				{
					ifs.seekg(fileoff);
					ifs.read(&SampleImgbuff[sampleoff], this->SpecHeader.pixelsize);
					sampleoff = sampleoff + this->SpecHeader.pixelsize;
					fileoff = fileoff + bandjump;
				};
			};
			ifs.close();
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			for (unsigned long long k = 0; k < this->SpecHeader.imgsize[1]; k++)		//z
			{
				for (unsigned long long i = 0; i < this->SpecHeader.imgsize[2]; i++)	//y
				{
					unsigned long long fileoff = (unsigned long long)this->SpecHeader.headsize + (k + ((unsigned long long)x + i * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[1]) * this->SpecHeader.pixelsize;
					unsigned long long sampleoff = (k + i * this->SpecHeader.imgsize[1]) *this->SpecHeader.pixelsize;
					ifs.seekg(fileoff);
					ifs.read(&SampleImgbuff[sampleoff], this->SpecHeader.pixelsize);
				};
			};
			ifs.close();
			return 0;
		};
	};
	//Err
	this->ErrorMsgLog("In SpecIL_Base::getPlane_RAW_Sample(): invalid parameters");
	return -1;
};
int SpecIL_Base::getPlane_Sample(void* plane, int x, int y, int z)
{
	char* SampleImgbuff = static_cast<char*>(plane);
	if(this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			unsigned long long cubeoff = (unsigned long long)x * this->SpecHeader.pixelsize;
			unsigned long long jump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
			unsigned long long maxlines = this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[2];
			for(unsigned long long i = 0; i < maxlines; i++)
			{
				std::memmove(&SampleImgbuff[i * this->SpecHeader.pixelsize], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
				cubeoff = cubeoff + jump;
			};
			return 0;
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long sampleoff = 0;
			unsigned long long framejump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
			unsigned long long bandjump = this->SpecHeader.imgsize[2] * framejump;
			unsigned long long startrawoff = (unsigned long long)x * this->SpecHeader.pixelsize;
			for(unsigned long long j = 0; j < this->SpecHeader.imgsize[2]; j++)
			{
				unsigned long long cubeoff = startrawoff + j * framejump;
				for(unsigned long long i = 0; i < this->SpecHeader.imgsize[1]; i++)
				{
					std::memmove(&SampleImgbuff[sampleoff], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
					sampleoff = sampleoff + this->SpecHeader.pixelsize;
					cubeoff = cubeoff + bandjump;
				};
			};
			return 0;
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{		
			for(unsigned long long k = 0; k < this->SpecHeader.imgsize[1]; k++)		//z
			{
				for(unsigned long long i = 0; i < this->SpecHeader.imgsize[2]; i++)	//y
				{
					unsigned long long cubeoff = (k + ((unsigned long long)x + i * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[1]) * this->SpecHeader.pixelsize;
					unsigned long long sampleoff = (k + i * this->SpecHeader.imgsize[1]) *this->SpecHeader.pixelsize;
					std::memmove(&SampleImgbuff[sampleoff], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
				};
			};
			return 0;
		};
	};
	if(this->SpecHeader.type == 2)
	{
		std::ifstream ifs( this->SpecHeader.filename, std::fstream::binary);
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			unsigned long long fileoff = (unsigned long long)this->SpecHeader.headsize + ((unsigned long long)x * this->SpecHeader.pixelsize);
			unsigned long long jump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
			unsigned long long maxlines = this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[2];
			for(unsigned long long i = 0; i < maxlines; i++)
			{
				ifs.seekg(fileoff);
				ifs.read(&SampleImgbuff[i * this->SpecHeader.pixelsize], this->SpecHeader.pixelsize);
				fileoff = fileoff + jump;
			};
			ifs.close();
			return 0;
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long sampleoff = 0;
			unsigned long long framejump = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
			unsigned long long bandjump = this->SpecHeader.imgsize[2] * framejump;
			unsigned long long startfileoff = (unsigned long long)this->SpecHeader.headsize + (unsigned long long)x * this->SpecHeader.pixelsize;
			for(unsigned long long j = 0; j < this->SpecHeader.imgsize[2]; j++)
			{
				unsigned long long fileoff = startfileoff + j * framejump;
				for(unsigned long long i = 0; i < this->SpecHeader.imgsize[1]; i++)
				{
					ifs.seekg(fileoff);
					ifs.read(&SampleImgbuff[sampleoff], this->SpecHeader.pixelsize);
					sampleoff = sampleoff + this->SpecHeader.pixelsize;
					fileoff = fileoff + bandjump;
				};
			};
			ifs.close();
			return 0;
		};
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			for(unsigned long long k = 0; k < this->SpecHeader.imgsize[1]; k++)		//z
			{
				for(unsigned long long i = 0; i < this->SpecHeader.imgsize[2]; i++)	//y
				{
					unsigned long long fileoff = (unsigned long long)this->SpecHeader.headsize + (k + ((unsigned long long)x + i * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[1]) * this->SpecHeader.pixelsize;
					unsigned long long sampleoff = (k + i * this->SpecHeader.imgsize[1]) *this->SpecHeader.pixelsize;
					ifs.seekg(fileoff);
					ifs.read(&SampleImgbuff[sampleoff], this->SpecHeader.pixelsize);
				};
			};
			ifs.close();
			return 0;
		};
	};
	//Err
	this->ErrorMsgLog("In SpecIL_Base::getPlane_RAW_Sample(): invalid parameters");
	return -1;
};
int SpecIL_Base::getPlane_Frame(void* plane, int x, int y, int z)
{
	char* FrameImgbuff = static_cast<char*>(plane);
	if (this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			unsigned long long cubeoff = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize * this->SpecHeader.imgsize[1] * (unsigned long long)y;
			unsigned long long framesize = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1];
			std::memmove(FrameImgbuff, &Cubebuff[cubeoff], framesize);
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long framesize = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
			unsigned long long cubeoff = (unsigned long long)y * framesize;
			unsigned long long jump = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize;
			for (unsigned long long i = 0; i < this->SpecHeader.imgsize[1]; i++) //z
			{
				std::memmove(&FrameImgbuff[framesize*i], &Cubebuff[cubeoff], framesize);
				cubeoff = cubeoff + jump;
			};
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			for (unsigned long long i = 0; i < this->SpecHeader.imgsize[0]; i++)		// x
			{
				for (unsigned long long k = 0; k < this->SpecHeader.imgsize[1]; k++)		// z
				{
					unsigned long long cubeoff = (k + (i + (unsigned long long)y * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[1]) * this->SpecHeader.pixelsize;
					unsigned long long frameoff = (i + k * this->SpecHeader.imgsize[0]) *this->SpecHeader.pixelsize;
					std::memmove(&FrameImgbuff[frameoff], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
				};
			};
			return 0;
		};
	};
	if (this->SpecHeader.type == 2)
	{
		std::ifstream ifs(this->SpecHeader.filename, std::fstream::binary);
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			unsigned long long fileoff = (unsigned long long)this->SpecHeader.headsize + this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize * this->SpecHeader.imgsize[1] * (unsigned long long)y;
			unsigned long long framesize = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1];
			ifs.seekg(fileoff);
			ifs.read(FrameImgbuff, framesize);
			ifs.close();
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long framesize = this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
			unsigned long long fileoff = (unsigned long long)this->SpecHeader.headsize + (unsigned long long)y * framesize;
			unsigned long long jump = this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize;
			for (unsigned long long i = 0; i < this->SpecHeader.imgsize[1]; i++) //z
			{
				ifs.seekg(fileoff);
				ifs.read(&FrameImgbuff[framesize*i], framesize);
				fileoff = fileoff + jump;
			};
			ifs.close();
			return 0;
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			for (unsigned long long i = 0; i < this->SpecHeader.imgsize[0]; i++)		// x
			{
				for (unsigned long long k = 0; k < this->SpecHeader.imgsize[1]; k++)		// z
				{
					unsigned long long fileoff = (unsigned long long)this->SpecHeader.headsize + (k + (i + (unsigned long long)y * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[1]) * this->SpecHeader.pixelsize;
					unsigned long long frameoff = (i + k * this->SpecHeader.imgsize[0]) *this->SpecHeader.pixelsize;
					ifs.seekg(fileoff);
					ifs.read(&FrameImgbuff[frameoff], this->SpecHeader.pixelsize);
				};
			};
			ifs.close();
			return 0;
		};
	};
	//Err
	this->ErrorMsgLog("In SpecIL_Base::getPlane_RAW_Frame(): invalid parameters");
	return -1;
};
int SpecIL_Base::getPlane_Band(void* plane, int *x, int *y, int z)
{
	char* BandImgbuff = static_cast<char*>(plane);

	unsigned long long diff_x = (unsigned long long)(x[1] - x[0]);
	unsigned long long diff_y = (unsigned long long)(y[1] - y[0]);

	unsigned long long start_x = (unsigned long long)x[0];
	unsigned long long start_y = (unsigned long long)y[0];

	// Daten vollstaendig im Speicher
	if(this->SpecHeader.type == 1)
	{
		char* Cubebuff = static_cast<char*>(this->SpecHeader.imgcube);

		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			unsigned long long cutoutlinesize = this->SpecHeader.pixelsize * diff_x;
			unsigned long long cubeoff = 0;

			for (unsigned long long j = 0; j < diff_y; j++)
			{
				cubeoff = (((unsigned long long)z + (j + start_y) * this->SpecHeader.imgsize[1]) * this->SpecHeader.imgsize[0]  + start_x) * this->SpecHeader.pixelsize;
				std::memmove(&BandImgbuff[cutoutlinesize * j], &Cubebuff[cubeoff], cutoutlinesize);
			};
			return 0;
		};

		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long bandsize = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2];
			unsigned long long cubeoff = (unsigned long long)z * bandsize;
			unsigned long long cutoutsize = this->SpecHeader.pixelsize * diff_x * diff_y;
			if (bandsize != cutoutsize)
			{
				unsigned long long cutoutlinesize = diff_x * this->SpecHeader.pixelsize;
				cubeoff += (x[0] + y[0] * this->SpecHeader.imgsize[0])* this->SpecHeader.pixelsize;
				for (unsigned long long i = 0; i < diff_y; i++)
				{
					std::memmove(&BandImgbuff[cutoutlinesize * i], &Cubebuff[cubeoff], cutoutlinesize);
					cubeoff += this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
				};
			}
			else
			{
				std::memmove(BandImgbuff, &Cubebuff[cubeoff], bandsize);
			};
			return 0;
		};

		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			unsigned long long cubeoff = 0;
			unsigned long long bandoff = 0;

			unsigned long long pixelmax = diff_x + diff_y;

			for (unsigned long long j = 0; j < diff_y; j++) //y
			{
				cubeoff = ((unsigned long long)z + start_x * this->SpecHeader.imgsize[1] + (start_y+j) * this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[0]) * this->SpecHeader.pixelsize;
				for (unsigned long long i = 0; i < diff_x; i++) //x
				{
					std::memmove(&BandImgbuff[bandoff], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
					bandoff += this->SpecHeader.pixelsize;
					cubeoff += this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
				};
			};
			return 0;
		};

		/* old:
		// band interleaved by line
		if(this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			unsigned long long linesize = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0];
			// Bild zusammenbauen und umsortieren auf vereinbartes Standardformat
			for(unsigned long long j = 0; j < this->SpecHeader.imgsize[2]; j++) //y
			{
				unsigned long long cubeoff = ( (this->SpecHeader.imgsize[1] * j + (unsigned long long)z) * this->SpecHeader.imgsize[0]) * this->SpecHeader.pixelsize;
				unsigned long long bandoff = linesize * j;
				// Kopieren
				std::memmove(&BandImgbuff[bandoff], &Cubebuff[cubeoff], linesize);
			};
			return 0;
		};
		// band sequential
		if(this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long bandsize = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2];
			unsigned long long cubeoff = (unsigned long long)z * bandsize;
			std::memmove(BandImgbuff, &Cubebuff[cubeoff], bandsize);
			return 0;
		};
		// band interleaved by pixel
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			for (unsigned long long j = 0; j < this->SpecHeader.imgsize[2]; j++) //y
			{
				for (unsigned long long i = 0; i < this->SpecHeader.imgsize[0]; i++) //x
				{
					unsigned long long cubeoff = ((unsigned long long)z + (i + j * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[1])* this->SpecHeader.pixelsize;
					unsigned long long bandoff = (i + j * this->SpecHeader.imgsize[0]) *this->SpecHeader.pixelsize;
					std::memmove(&BandImgbuff[bandoff], &Cubebuff[cubeoff], this->SpecHeader.pixelsize);
				};
			};
			return 0;
		};
	};
	// Daten auf HDD
	// oder von/auf HDD arbeiten?
	if (this->SpecHeader.type == 2)
	{
		std::ifstream ifs(this->SpecHeader.filename, std::fstream::binary);
		// band interleaved by line
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
		{
			unsigned long long fileoff = 0;
			unsigned long long cutoutlinesize = this->SpecHeader.pixelsize * diff_x;

			// Bild zusammenbauen
			for (unsigned long long i = 0; i < diff_y; i++)
			{
				fileoff = (unsigned long long)this->SpecHeader.headsize + (((unsigned long long)z + (i + start_y) * this->SpecHeader.imgsize[1]) * this->SpecHeader.imgsize[0] + start_x) * this->SpecHeader.pixelsize;;
				ifs.seekg(fileoff);
				ifs.read(&BandImgbuff[i * cutoutlinesize], cutoutlinesize);
			};
			ifs.close();
			return 0;
		};
		// band sequential
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			unsigned long long bandsize = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2];
			unsigned long long cutoutsize = this->SpecHeader.pixelsize * diff_x * diff_y;
			unsigned long long startpos = (unsigned long long)this->SpecHeader.headsize + (unsigned long long)z * bandsize;

			if (bandsize != cutoutsize)
			{
				unsigned long long cutoutlinesize = diff_x * this->SpecHeader.pixelsize;
				startpos += (x[0] + y[0] * this->SpecHeader.imgsize[0])* this->SpecHeader.pixelsize;

				for (unsigned long long i = 0; i < diff_y; i++)
				{
					ifs.seekg(startpos);
					ifs.read(&BandImgbuff[cutoutlinesize * i], cutoutlinesize);
					startpos += this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
				};
			}
			else
			{
				ifs.seekg(startpos);
				ifs.read(BandImgbuff, bandsize);
			};
			ifs.close();
			return 0;
		};
		// band interleaved by pixel
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{

			unsigned long long fileoff = 0;
			unsigned long long bandoff = 0;

			unsigned long long pixelmax = diff_x + diff_y;

			for (unsigned long long j = 0; j < diff_y; j++) //y
			{
				fileoff = (unsigned long long)this->SpecHeader.headsize + ((unsigned long long)z + start_x * this->SpecHeader.imgsize[1] + (start_y + j) * this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[0]) * this->SpecHeader.pixelsize;
				for (unsigned long long i = 0; i < diff_x; i++) //x
				{
					ifs.seekg(fileoff);
					ifs.read(&BandImgbuff[bandoff], this->SpecHeader.pixelsize);

					bandoff += this->SpecHeader.pixelsize;
					fileoff += this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
				};
			};

			ifs.close();
			return 0;
		};
	};
	// Err
	this->ErrorMsgLog("In SpecIL_Base::getPlane_Band(): Invalid Parameter(s) !");
	return -1;
};
//---------------------------------------------------------*/