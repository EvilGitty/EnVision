#include "Filemanager/filemanager.h"

//==============================================================================
// inline int checkHyspexHeaderfile( std::string key, std::string header )
//------------------------------------------------------------------------------
// Just a quick check if an associated header file headerfile ".hdr" is present
//==============================================================================
	inline int checkHyspexHeaderfile( std::string key, std::string header )
	{
		std::size_t found = header.rfind( key );
		if (found != std::string::npos) {
			header.replace(found, key.length(), ".hdr");

			QFileInfo checkThisfile(QString::fromStdString(header));
			if ((checkThisfile.exists() == 0) || (checkThisfile.isFile() == 0)) {
				//apparantly the file was not found or it is not a file
				QMessageBox msgBox;
				msgBox.setWindowTitle("Missing header file!");
				msgBox.setText(QString::fromStdString(header));
				msgBox.exec();
				return 1;
			}
		}
		return 0;
	}

//==============================================================================
// bool FileManager::load_hySpex_img( QStringList::Iterator &it, int select )
//------------------------------------------------------------------------------
//==============================================================================
	bool Filemanager::load_hySpex_img( QStringList::Iterator &it, int select )
	{
			bool ret = 1;
			
			if ( select == 0 ) {
				if (checkHyspexHeaderfile( ".hyspex", it->toStdString() ) == 1 ) {
					return 1;
				}

				QFileInfo fi(*it);
				ImageAttribute::record.imgFilename = it->toStdString();
				ImageAttribute::record.imgFilename_s = QString(fi.fileName()).toStdString();
				ImageAttribute::record.suffix = fi.suffix().toStdString();
				QDir dir = QFileInfo(*it).absoluteDir();
				ImageAttribute::record.path = dir.absolutePath().toStdString();
				//cout << " suffix: " << suffix << " thispath:" << path << " short: " << ImageAttribute::record.imgFilename_s << endl;

				ImageAttribute::record.imgNumber = 2;

				ImageAttribute::record.ID = ImageAttribute::record.SpecData->getHeaderPointer()->ID;
				ImageAttribute::record.wavelenunit = ImageAttribute::record.SpecData->getHeaderPointer()->wavelenunit;

				if (ImageAttribute::record.wavelenunit.size() == 0){
					ImageAttribute::record.wavelenunit = "nm";
				}

				//dimensions
				unsigned long samples = ImageAttribute::record.SpecData->getHeaderPointer()->imgsize[0];		//samples	
				unsigned long channels = ImageAttribute::record.SpecData->getHeaderPointer()->imgsize[1];		//channels
				unsigned long lines = ImageAttribute::record.SpecData->getHeaderPointer()->imgsize[2];			//lines

				ImageAttribute::record.numdim = ImageAttribute::record.SpecData->getHeaderPointer()->numdim;

				ImageAttribute::record.data_type = ImageAttribute::record.SpecData->getHeaderPointer()->data_type;
				ImageAttribute::record.data_type_str = ImageAttribute::record.SpecData->getHeaderPointer()->data_type_str;
				ImageAttribute::record.interleave = ImageAttribute::record.SpecData->getHeaderPointer()->interleave;
				ImageAttribute::record.headersize = ImageAttribute::record.SpecData->getHeaderPointer()->headsize;
				ImageAttribute::record.pixelsize = ImageAttribute::record.SpecData->getHeaderPointer()->pixelsize;
				ImageAttribute::record.byte_order = ImageAttribute::record.SpecData->getHeaderPointer()->byte_order;

				ImageAttribute::record.opencvDataType = ImageAttribute::record.SpecData->getOpenCVDatatype();

				ImageAttribute::record.data_type_minval = ImageAttribute::record.SpecData->getHeaderPointer()->data_type_minval;
				ImageAttribute::record.data_type_maxval = ImageAttribute::record.SpecData->getHeaderPointer()->data_type_maxval;

				if (ImageAttribute::record.ID.find("SWIR_320") != std::string::npos) {
					ImageAttribute::record.subimgNumber = 20;
					ImageAttribute::record.data_type_maxval = 16383;
					ImageAttribute::record.data_type_minval = 0;
					ImageAttribute::record.datatype = "ushort";

					ImageAttribute::record.cubeDim[0] = samples;
					ImageAttribute::record.cubeDim[1] = lines;
					ImageAttribute::record.cubeDim[2] = channels;
				}

				if (ImageAttribute::record.ID.find("SWIR_384") != std::string::npos) {
					ImageAttribute::record.subimgNumber = 21;
					ImageAttribute::record.data_type_maxval = 65535;
					ImageAttribute::record.data_type_minval = 0;
					ImageAttribute::record.datatype = "ushort";

					ImageAttribute::record.cubeDim[0] = samples;
					ImageAttribute::record.cubeDim[1] = lines;
					ImageAttribute::record.cubeDim[2] = channels;
				}

				if (ImageAttribute::record.ID.find("VNIR_1600") != std::string::npos) {
					ImageAttribute::record.subimgNumber = 22;
					ImageAttribute::record.data_type_maxval = 4095;
					ImageAttribute::record.data_type_minval = 0;
					ImageAttribute::record.datatype = "ushort";

					ImageAttribute::record.cubeDim[0] = samples;
					ImageAttribute::record.cubeDim[1] = lines;
					ImageAttribute::record.cubeDim[2] = channels;
				}

				if (ImageAttribute::record.ID.find("VNIR_1800") != std::string::npos) {
					ImageAttribute::record.subimgNumber = 23;
					ImageAttribute::record.data_type_maxval = 65535;
					ImageAttribute::record.data_type_minval = 0;
					ImageAttribute::record.datatype = "ushort";

					ImageAttribute::record.cubeDim[0] = samples;
					ImageAttribute::record.cubeDim[1] = lines;
					ImageAttribute::record.cubeDim[2] = channels;
				}

				if (ImageAttribute::record.ID.find("UAV_Mjolnir") != std::string::npos) {
					ImageAttribute::record.subimgNumber = 24;
					ImageAttribute::record.data_type_maxval = 4095;
					ImageAttribute::record.data_type_minval = 0;

					ImageAttribute::record.cubeDim[0] = samples;
					ImageAttribute::record.cubeDim[1] = lines;
					ImageAttribute::record.cubeDim[2] = channels;
				}

				/*
				if (ImageAttribute::record.ID.find(" ?? ODIN ?? ") != std::string::npos) {
				ImageAttribute::record.subimgNumber = 35;
				ImageAttribute::record.data_type_maxval = 65535;	//?????
				ImageAttribute::record.data_type_minval = 0;
				}
				*/

				std::vector< double > doubleVec(ImageAttribute::record.SpecData->getHeaderPointer()->wavelen.begin(),
									ImageAttribute::record.SpecData->getHeaderPointer()->wavelen.end());
				ImageAttribute::record.wavelength = doubleVec;
	
				ImageAttribute::record.blocksize_x = lines;

				ret = 0;
			}

			if ( select == 1 ) {

				if ( checkHyspexHeaderfile( ".img", it->toStdString() ) == 1 ) {
					return 1;
				}

				QFileInfo fi(*it);
				ImageAttribute::record.imgFilename = it->toStdString();
				ImageAttribute::record.imgFilename_s = QString(fi.fileName()).toStdString();
				ImageAttribute::record.suffix = fi.suffix().toStdString();
				QDir dir = QFileInfo(*it).absoluteDir();
				ImageAttribute::record.path = dir.absolutePath().toStdString();

				ImageAttribute::record.imgNumber = 3;

				ImageAttribute::record.ID = ImageAttribute::record.SpecData->getHeaderPointer()->ID;
				ImageAttribute::record.wavelenunit = ImageAttribute::record.SpecData->getHeaderPointer()->wavelenunit;

				//dimensions
				unsigned long long samples = ImageAttribute::record.SpecData->getHeaderPointer()->imgsize[0];		//samples	
				unsigned long long channels = ImageAttribute::record.SpecData->getHeaderPointer()->imgsize[1];		//channels
				unsigned long long lines = ImageAttribute::record.SpecData->getHeaderPointer()->imgsize[2];		//lines

				ImageAttribute::record.numdim = ImageAttribute::record.SpecData->getHeaderPointer()->numdim;

				ImageAttribute::record.data_type = ImageAttribute::record.SpecData->getHeaderPointer()->data_type;
				ImageAttribute::record.data_type_str = ImageAttribute::record.SpecData->getHeaderPointer()->data_type_str;
				ImageAttribute::record.interleave = ImageAttribute::record.SpecData->getHeaderPointer()->interleave;
				ImageAttribute::record.headersize = ImageAttribute::record.SpecData->getHeaderPointer()->headsize;
				ImageAttribute::record.pixelsize = ImageAttribute::record.SpecData->getHeaderPointer()->pixelsize;
				ImageAttribute::record.byte_order = ImageAttribute::record.SpecData->getHeaderPointer()->byte_order;

				ImageAttribute::record.opencvDataType = ImageAttribute::record.SpecData->getOpenCVDatatype();

				ImageAttribute::record.data_type_minval = ImageAttribute::record.SpecData->getHeaderPointer()->data_type_minval;
				ImageAttribute::record.data_type_maxval = ImageAttribute::record.SpecData->getHeaderPointer()->data_type_maxval;

				if (ImageAttribute::record.ID.find("SWIR_320") != std::string::npos) {
					ImageAttribute::record.subimgNumber = 30;
					ImageAttribute::record.data_type_maxval = 65535;
					ImageAttribute::record.data_type_minval = 0;
					ImageAttribute::record.datatype = "ushort";

					ImageAttribute::record.cubeDim[0] = samples;
					ImageAttribute::record.cubeDim[1] = lines;
					ImageAttribute::record.cubeDim[2] = channels;
				}

				if (ImageAttribute::record.ID.find("SWIR_384") != std::string::npos) {
					ImageAttribute::record.subimgNumber = 31;
					ImageAttribute::record.data_type_maxval = 65535;
					ImageAttribute::record.data_type_minval = 0;
					ImageAttribute::record.datatype = "ushort";

					ImageAttribute::record.cubeDim[0] = samples;
					ImageAttribute::record.cubeDim[1] = lines;
					ImageAttribute::record.cubeDim[2] = channels;
				}

				if (ImageAttribute::record.ID.find("VNIR_1600") != std::string::npos) {
					ImageAttribute::record.subimgNumber = 32;
					ImageAttribute::record.data_type_maxval = 65535;
					ImageAttribute::record.data_type_minval = 0;
					ImageAttribute::record.datatype = "ushort";

					ImageAttribute::record.cubeDim[0] = samples;
					ImageAttribute::record.cubeDim[1] = lines;
					ImageAttribute::record.cubeDim[2] = channels;
				}

				if (ImageAttribute::record.ID.find("VNIR_1800") != std::string::npos) {
					ImageAttribute::record.subimgNumber = 33;
					ImageAttribute::record.data_type_maxval = 65535;
					ImageAttribute::record.data_type_minval = 0;
					ImageAttribute::record.datatype = "ushort";

					ImageAttribute::record.cubeDim[0] = samples;
					ImageAttribute::record.cubeDim[1] = lines;
					ImageAttribute::record.cubeDim[2] = channels;
				}

				if (ImageAttribute::record.ID.find("UAV_Mjolnir") != std::string::npos) {
					ImageAttribute::record.subimgNumber = 34;
					ImageAttribute::record.data_type_maxval = 65535;
					ImageAttribute::record.data_type_minval = 0;
					ImageAttribute::record.datatype = "float";

					ImageAttribute::record.cubeDim[0] = samples;
					ImageAttribute::record.cubeDim[1] = lines;
					ImageAttribute::record.cubeDim[2] = channels;
				}

				/*
				if (ImageAttribute::record.ID.find(" ?? ODIN ?? ") != std::string::npos) {
					ImageAttribute::record.subimgNumber = 35;
					ImageAttribute::record.data_type_maxval = 65535;	//?????
					ImageAttribute::record.data_type_minval = 0;
				}
				*/

				std::vector< double > doubleVec( ImageAttribute::record.SpecData->getHeaderPointer()->wavelen.begin(),
												ImageAttribute::record.SpecData->getHeaderPointer()->wavelen.end() );
				ImageAttribute::record.wavelength = doubleVec;

				ImageAttribute::record.blocksize_x = lines;
			
				ret = 0;
			}


			//full header for information only..
			/*
			ImageAttribute::record.frameperiod = main->hyspex->Record.frameperiod;
			ImageAttribute::record.integration_time = main->hyspex->Record.integration_time;
			ImageAttribute::record.binning = main->hyspex->Record.binning;
			ImageAttribute::record.numberOfFrames = main->hyspex->Record.numberOfFrames;
			ImageAttribute::record.aperture_size = main->hyspex->Record.aperture_size;
			ImageAttribute::record.lens = main->hyspex->Record.lens;
			ImageAttribute::record.number_of_background = main->hyspex->Record.number_of_background;
			ImageAttribute::record.pixelsize_x = main->hyspex->Record.pixelsize_x;
			ImageAttribute::record.pixelsize_y = main->hyspex->Record.pixelsize_y;
			ImageAttribute::record.ID = main->hyspex->Record.ID;
			ImageAttribute::record.comment = main->hyspex->Record.comment;
			ImageAttribute::record.serialnumber = main->hyspex->Record.serialnumber;
			ImageAttribute::record.scaling = main->hyspex->Record.scaling;
			ImageAttribute::record.cubeDim[0] = main->hyspex->Record.samples;
			ImageAttribute::record.cubeDim[1] = main->hyspex->Record.lines;
			ImageAttribute::record.cubeDim[2] = main->hyspex->Record.bands;
			ImageAttribute::record.header_offset = main->hyspex->Record.header_offset;
			ImageAttribute::record.acquisition_date = main->hyspex->Record.acquisition_date;
			ImageAttribute::record.acquisition_start_time = main->hyspex->Record.acquisition_start_time;
			ImageAttribute::record.data_type = main->hyspex->Record.data_type;
			ImageAttribute::record.interleave = main->hyspex->Record.interleave;
			ImageAttribute::record.default_bands = main->hyspex->Record.default_bands;
			ImageAttribute::record.byte_order = main->hyspex->Record.byte_order;
			ImageAttribute::record.wavelength = main->hyspex->Record.wavelength;
			ImageAttribute::record.startBand = main->hyspex->Record.startBand;
			*/
		return ret;
	}