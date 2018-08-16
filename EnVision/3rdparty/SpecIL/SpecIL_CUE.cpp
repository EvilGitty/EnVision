#include "SpecIL_CUE.h"

SpecIL_CUE::~SpecIL_CUE()
{
};
//
SpecIL_CUE::SpecIL_CUE()
{
};
int SpecIL_CUE::read()
{
	// Datei oeffnen testen
	std::ifstream ifs(this->SpecHeader.filename.c_str(), std::ifstream::in | std::ifstream::binary);
	if (ifs.is_open() == false)
	{
		std::string emsg;
		emsg = "Error in SpecIL_CUE::read():Cant open " + this->SpecHeader.filename;
		this->ErrorMsgLog(emsg);
		ifs.close();
		return -1;
	};
	ifs.close();

	if (this->ENVIhdrLoaded == false)
	{
		if (this->readENVIhdr() != 0)
		{
			// ENVI Informationen werden gebraucht!
			this->ErrorMsgLog("Error in SpecIL_CUE::read(): Cant open .hdr");
			return -1;
		};
	};

	this->setDataTypeMaxMin();

	if (this->FileDataLoaded == 0)
	{
		if (this->readImageData() != 0)
		{
			return -1;
		};
	};

	return 0;
};
int SpecIL_CUE::readImageData()
{
	std::ifstream ifs(this->SpecHeader.filename.c_str(), std::ifstream::in | std::ifstream::binary);
	if (ifs.is_open() == false)
	{
		this->ErrorMsgLog("Error in SpecIL_CUE::readImageData: Cant open file.");
		ifs.close();
		return -1;
	};
	
	if (this->FileDataLoaded == 0)
	{
		// Groesse der Datei ermitteln
		ifs.seekg(0, ifs.end);
		unsigned long long filesize = ifs.tellg();
		ifs.seekg(0, ifs.beg);

		if (((filesize - ((unsigned long long)this->SpecHeader.headsize)) < this->cubemaxsize) && this->ReadOnlyFromHDD == 0)
		{
			unsigned long long imagedatesize = this->SpecHeader.pixelsize * this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[2];

			// Buffer allokieren
			try{
				this->SpecHeader.imgcube = static_cast<void*>(new char[imagedatesize]);
			}
			catch (const std::bad_alloc&)
			{
				ifs.close();
				this->ErrorMsgLog(std::string("Error in SpecIL_CUE::readImageData(): std::bad_alloc"));

				this->SpecHeader.imgcube = NULL;
				this->SpecHeader.type = 2;

				return -1;
			};

			// Vom Filestream in der Buffer schreiben
			ifs.seekg(this->SpecHeader.headsize, ifs.beg);
			ifs.read(static_cast< char* >(this->SpecHeader.imgcube), imagedatesize);

			// Check Failbits
			if (ifs.eof())
			{
				this->ErrorMsgLog(std::string("Error in SpecIL_CUE::readImageData(): ifs.eof() == true ! -> End-of-File reached on input operation"));
				ifs.close();
				delete[] this->SpecHeader.imgcube;
				return -1;
			};
			if (ifs.bad())
			{
				this->ErrorMsgLog(std::string("Error in SpecIL_CUE::readImageData(): ifs.bad() == true ! -> Read-writing error on i-o operation or Logical error on i-o operation !"));
				ifs.close();
				delete[] this->SpecHeader.imgcube;
				return -1;
			};

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

	this->ErrorMsgLog("Error in SpecIL_CUE::readImageData:");
	ifs.close();
	return -1;
};