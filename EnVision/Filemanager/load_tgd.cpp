#include "Filemanager/filemanager.h"

//==============================================================================
// bool FileManager::load_tgd( QStringList::Iterator &it )
//------------------------------------------------------------------------------
//==============================================================================
	bool Filemanager::load_tgd(QStringList::Iterator &it)
	{
			bool ret = 1;

			QFileInfo fi(*it);
			ImageAttribute::record.imgFilename = it->toStdString();
			ImageAttribute::record.imgFilename_s = QString(fi.fileName()).toStdString();
			ImageAttribute::record.suffix = fi.suffix().toStdString();
			QDir dir = QFileInfo(*it).absoluteDir();
			ImageAttribute::record.path = dir.absolutePath().toStdString();
			//cout << " suffix: " << suffix << " thispath:" << path << " short: " << ImageAttribute::record.imgFilename_s << endl;

			 ImageAttribute::record.imgNumber = 1;

			 ImageAttribute::record.ID =			 ImageAttribute::record.SpecData->getHeaderPointer()->ID;
			 ImageAttribute::record.wavelenunit = ImageAttribute::record.SpecData->getHeaderPointer()->wavelenunit;

			 if (ImageAttribute::record.wavelenunit.size() == 0){
				 ImageAttribute::record.wavelenunit = "nm";
			 }

			//dimensions
			unsigned long long samples	=  ImageAttribute::record.SpecData->getHeaderPointer()->imgsize[ 0];		//samples	
			unsigned long long channels = ImageAttribute::record.SpecData->getHeaderPointer()->imgsize[1];		//channels
			unsigned long long lines = ImageAttribute::record.SpecData->getHeaderPointer()->imgsize[2];		//lines

			ImageAttribute::record.numdim = ImageAttribute::record.SpecData->getHeaderPointer()->numdim;

			 ImageAttribute::record.data_type =  ImageAttribute::record.SpecData->getHeaderPointer()->data_type;
			 ImageAttribute::record.data_type_str =  ImageAttribute::record.SpecData->getHeaderPointer()->data_type_str;
			 ImageAttribute::record.interleave =  ImageAttribute::record.SpecData->getHeaderPointer()->interleave;
			 ImageAttribute::record.headersize =  ImageAttribute::record.SpecData->getHeaderPointer()->headsize;
			 ImageAttribute::record.pixelsize =  ImageAttribute::record.SpecData->getHeaderPointer()->pixelsize;
			 ImageAttribute::record.byte_order =  ImageAttribute::record.SpecData->getHeaderPointer()->byte_order;

			 ImageAttribute::record.opencvDataType =  ImageAttribute::record.SpecData->getOpenCVDatatype();

			 ImageAttribute::record.data_type_minval = ImageAttribute::record.SpecData->getHeaderPointer()->data_type_minval;
			 ImageAttribute::record.data_type_maxval =  ImageAttribute::record.SpecData->getHeaderPointer()->data_type_maxval;

			//could be a SWIR 320me
			if ( ( samples == 320 ) && ( channels == 256 ) ) {
				//override
				 ImageAttribute::record.subimgNumber = 10;
				 ImageAttribute::record.opencvDataType = 5;
				 ImageAttribute::record.data_type_maxval = 65535.0;
				 ImageAttribute::record.data_type_minval = 0.0;
				 ImageAttribute::record.datatype = "float";

				 ImageAttribute::record.cubeDim[ 0 ] = samples;	
				 ImageAttribute::record.cubeDim[ 1 ] = lines;	
				 ImageAttribute::record.cubeDim[ 2 ] = channels;

				int basewavelength = 900;
				for ( int bandnum = 0; bandnum < channels ; bandnum++ ) {
					double wavelength = basewavelength + bandnum * 5.9;
					 ImageAttribute::record.wavelength.push_back( wavelength );
				}
				ret = 0;
			}

			//could be a SWIR384
			if ( ( samples == 384 ) && ( channels == 288 ) ) {
				//override
				cout << " LOL " << endl;
				 ImageAttribute::record.subimgNumber = 11;
				 ImageAttribute::record.opencvDataType = 5;
				 ImageAttribute::record.data_type_maxval = 65535.0;
				 ImageAttribute::record.data_type_minval = 0.0;
				 ImageAttribute::record.datatype = "ushort";

				 ImageAttribute::record.cubeDim[ 0 ] = samples;
				 ImageAttribute::record.cubeDim[ 1 ] = lines;
				 ImageAttribute::record.cubeDim[ 2 ] = channels;

				int basewavelength = 900;
				for ( int bandnum = 0; bandnum < channels; bandnum++ ) {
					double wavelength = basewavelength + bandnum * 5.45;
					 ImageAttribute::record.wavelength.push_back( wavelength );
				}
				ret = 0;
			}

			/*
			
			//could be a SWIR384
			if ( ( samples == 384 ) && ( channels == 288 ) ) {
				//override
				 Imagefile::imageRecord.subimgNumber = 11;
				// Imagefile::imageRecord.opencvDataType = 5;
				 Imagefile::imageRecord.data_type_maxval = 65535;
				 Imagefile::imageRecord.data_type_minval = 0;
				 Imagefile::imageRecord.flag_conversion = "ushort";

				 Imagefile::imageRecord.cubeDim[ 0 ] = samples;
				 Imagefile::imageRecord.cubeDim[ 1 ] = lines;
				 Imagefile::imageRecord.cubeDim[ 2 ] = channels;

				 Imagefile::imageRecord.transposeDisplay = 1;
	
				int basewavelength = 900;
				for ( int bandnum = 0; bandnum < channels; bandnum++ ) {
					double wavelength = basewavelength + bandnum * 5.45;
					 Imagefile::imageRecord.wavelength.push_back( wavelength );
				}
				ret = 0;
			}
			*/
			//could be a VNIR1600
			if ( ( samples == 1600 ) && ( channels == 160 ) ) {
				//override
				 ImageAttribute::record.subimgNumber = 12;
				 ImageAttribute::record.opencvDataType = 5;
				 ImageAttribute::record.data_type_maxval = 65535.0;
				 ImageAttribute::record.data_type_minval = 0.0;
				 ImageAttribute::record.datatype = "float";

				 ImageAttribute::record.cubeDim[0] = samples;
				 ImageAttribute::record.cubeDim[1] = lines;
				 ImageAttribute::record.cubeDim[2] = channels;

				int basewavelength = 400;
				for ( int bandnum = 0; bandnum < channels; bandnum++ ) {
					double wavelength = basewavelength + bandnum * 3.7;
					 ImageAttribute::record.wavelength.push_back( wavelength );
				}
				ret = 0;
			}

			//could be a VNIR1800
			if ( ( samples == 1800 ) && ( channels == 182 ) ) {

				 ImageAttribute::record.subimgNumber = 13;
				 ImageAttribute::record.opencvDataType = 5;
				 ImageAttribute::record.data_type_maxval = 65535.0;
				 ImageAttribute::record.data_type_minval = 0.0;
				 ImageAttribute::record.datatype = "float";

				 ImageAttribute::record.cubeDim[0] = samples;
				 ImageAttribute::record.cubeDim[1] = lines;
				 ImageAttribute::record.cubeDim[2] = channels;

				int basewavelength = 400;
				for ( int bandnum = 0; bandnum < channels; bandnum++ ) {
					double wavelength = basewavelength + bandnum * 3.26;
					 ImageAttribute::record.wavelength.push_back( wavelength );
				}
				ret = 0;
			}

			/*
			//could be HySpex Mjolnir
			if ( (  ImageAttribute::record.cubeDim[ 0 ] == 1024 ) 
			&& (  ImageAttribute::record.cubeDim[ 2 ] == 200 ) ) {
				//temp override
				 ImageAttribute::record.subimgNumber = 14;
				 ImageAttribute::record.opencvDataType = 5;
				 ImageAttribute::record.data_type_maxval = 65535;
				 ImageAttribute::record.data_type_minval = 0;
				 ImageAttribute::record.datatype = "float";

				 ImageAttribute::record.cubeDim[0] = lines;
				 ImageAttribute::record.cubeDim[1] = samples;
				 ImageAttribute::record.cubeDim[2] = channels;

				int basewavelength = 400;
				for ( int bandnum = 0; bandnum <  ImageAttribute::record.cubeDim[ 2 ]; bandnum++ ) {
				double wavelength = basewavelength + bandnum * 3;
				 ImageAttribute::record.wavelength.push_back( wavelength );
				}
			
				//not implemented yet
				ret = 0;
			}
			*/

			//could be Davids Copter
			if ( channels == 138 ) {
	
				 ImageAttribute::record.subimgNumber = 15;
				 ImageAttribute::record.opencvDataType = 5;
				 ImageAttribute::record.data_type_maxval = 65535.0;
				 ImageAttribute::record.data_type_minval = 0.0;
				 ImageAttribute::record.datatype = "float";
				 
				 ImageAttribute::record.cubeDim[0] = samples;
				 ImageAttribute::record.cubeDim[1] = lines;
				 ImageAttribute::record.cubeDim[2] = channels;

				int basewavelength = 400;
				for ( int bandnum = 0; bandnum < channels; bandnum++ ) {
					double wavelength = basewavelength + bandnum * 3.7;
					 ImageAttribute::record.wavelength.push_back( wavelength );
				}
				ret = 0;
			}

			//could be the Nuance
			if ((samples == 1392) && (channels == 51)) {

				ImageAttribute::record.subimgNumber = 16;
				ImageAttribute::record.opencvDataType = 4;
				ImageAttribute::record.data_type_maxval = 4095.0;
				ImageAttribute::record.data_type_minval = 0.0;
				ImageAttribute::record.datatype = "uint";

				ImageAttribute::record.cubeDim[0] = samples;
				ImageAttribute::record.cubeDim[2] = channels;
				ImageAttribute::record.cubeDim[1] = lines;

				int basewavelength = 450;
				for (int bandnum = 0; bandnum < channels; bandnum++) {
					double wavelength = basewavelength + bandnum * 10;
					ImageAttribute::record.wavelength.push_back(wavelength);
				}

				ret = 0;
			}

			//could be Kinect I
			if ( ( samples == 512 ) && ( channels == 484 ) ) {

				 ImageAttribute::record.subimgNumber = 17;
				 ImageAttribute::record.opencvDataType = 4;
				 ImageAttribute::record.data_type_maxval = 65535.0;
				 ImageAttribute::record.data_type_minval = 0.0;
				 ImageAttribute::record.datatype = "uint";

				 ImageAttribute::record.cubeDim[0] = samples;
				 ImageAttribute::record.cubeDim[1] = channels;
				 ImageAttribute::record.cubeDim[2] = lines;

				 ImageAttribute::record.wavelength.push_back( 0 );
				
				ret = 0;
			}

			//could be Kinect II
			if ( ( samples  == 1920) && ( channels == 1080) ) {
		
				 ImageAttribute::record.subimgNumber = 18;
				 ImageAttribute::record.opencvDataType = 4;
				 ImageAttribute::record.data_type_maxval = 65535.0;
				 ImageAttribute::record.data_type_minval = 0.0;
				 ImageAttribute::record.datatype = "kinect";

				 ImageAttribute::record.cubeDim[0] = samples;
				 ImageAttribute::record.cubeDim[1] = channels;
				 ImageAttribute::record.cubeDim[2] = lines;

				 ImageAttribute::record.wavelength.push_back( 0 );

				ret = 0;
			}

			/*
			//could be HySpex ODIN
			if (( ImageAttribute::record.cubeDim[0] == 1024)
				&& ( ImageAttribute::record.cubeDim[2] == 427)) {

				 ImageAttribute::record.subimgNumber = 18;

				//not implemented yet
				ret = 0;
			}
			*/

			/*
			//could be HySpex Mjolnir
			if (( ImageAttribute::record.cubeDim[0] == 6251)
			&& ( ImageAttribute::record.cubeDim[2] == 200)) {

			 ImageAttribute::record.subimgNumber = 14;

			//not implemented yet
			ret = 0;
			}
			*/

			ImageAttribute::record.blocksize_x = lines;
			ImageAttribute::record.blocksize_y = samples;

		return ret;
	}

