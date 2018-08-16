#include "SpecIL_Interface.h"
#include "SpecIL_Base.h"

// Unterstuetzte Datentypen
#include "SpecIL_HySpex.h"
#include "SpecIL_Nuance.h"
#include "SpecIL_TGD.h"
#include "SpecIL_CUE.h"
#include "SpecIL_TIFF.h"

#include "SpecIL_MAT.h"

#include <string>
#include <fstream>

SpecIL_Interface* SpecIL_Interface::open(const char* mode, const char* cstr_filename)
{
	std::string filename(cstr_filename);
	std::string Mode(mode);

	std::string endung = filename.substr(filename.find_last_of("."));

	unsigned int filemode = 0;
	if (Mode.find("r") == 0)
	{
		filemode = 0;
	};

	if (Mode.find("w") == 0)
	{
		filemode = 1;
	};

	if (Mode.find("rw") == 0 || Mode.find("wr") == 0)
	{
		filemode = 2;

		// modus wird noch nicht unterstuetzt!
		size_t len = filename.find_last_of(".");
		std::string logfile = filename.substr(0, len);
		logfile = logfile + "_SpecIL_ERROR_LOG" + ".txt";
		std::fstream fsError(logfile, std::fstream::out | std::fstream::app);
		fsError << "Mode rw is not supported by SpecIL!" << std::endl;
		fsError.close();
		return false;
	};

	if (0 == endung.compare(".img") || 0 == endung.compare(".bin") || 0 == endung.compare(".hyspex"))
	{
		// HySpex
		SpecIL_HySpex* SpecData = new SpecIL_HySpex;
		SpecData->getHeaderPointer()->filename = filename;
		SpecData->setFileMode(filemode);
		if (filemode == 0)
		{
			SpecData->readFileHeader();
		};
		if (filemode == 1)
		{
			SpecData->initNewFile();
		};

		return SpecData;
	};

	if (0 == endung.compare(".tgd"))
	{
		SpecIL_TGD* SpecData = new SpecIL_TGD;
		SpecData->getHeaderPointer()->filename = filename;
		SpecData->setFileMode(filemode);
		if (filemode == 0)
		{
			SpecData->readFileHeader();
		};
		if (filemode == 1)
		{
			SpecData->initNewFile();
		};

		return SpecData;
	};

	if (filemode == 0)
	{
		if (0 == endung.compare(".im3"))// Nuance
		{
			SpecIL_Nuance* SpecData = new SpecIL_Nuance;
			SpecData->getHeaderPointer()->filename = filename;
			SpecData->readFileHeader();

			return SpecData;
		};

		if (0 == endung.compare(".cue"))
		{
			SpecIL_CUE* SpecData = new SpecIL_CUE;
			SpecData->getHeaderPointer()->filename = filename;
			SpecData->readENVIhdr();

			return SpecData;
		};

		if (0 == endung.compare(".tiff") || 0 == endung.compare(".tif"))
		{
			SpecIL_TIFF* SpecData = new SpecIL_TIFF;
			SpecData->getHeaderPointer()->filename = filename;
			SpecData->readFileHeader();
			return SpecData;
		};

		// Entwicklung
	/*	if (0 == endung.compare(".cub"))
		{
			SpecIL_CUB* SpecData = new SpecIL_CUB;
			SpecData->getHeaderPointer()->filename = filename;
			return SpecData;
		};//*/

		if (0 == endung.compare(".mat"))// Matlab Datei
		{
				SpecIL_MAT* SpecData = new SpecIL_MAT;
				SpecData->getHeaderPointer()->filename = filename;
				SpecData->readFileHeader();
				return SpecData;		
		};
	};

	// Fehler: Dateiendung nicht kompatibel
	// Logdatei
	size_t len = filename.find_last_of(".");
	std::string logfile = filename.substr(0, len);
	logfile = logfile + "_SpecIL_ERROR_LOG" + ".txt";
	std::fstream fsError(logfile, std::fstream::out | std::fstream::app);
	fsError << "The Fileformat " << endung << " is not supported by SpecIL!" << std::endl;
	fsError.close();
	return false;
};