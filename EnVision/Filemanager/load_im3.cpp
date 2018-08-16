#include "Filemanager/filemanager.h"

//==============================================================================
// bool FileManager::load_im3( QStringList::Iterator &it )
//------------------------------------------------------------------------------
//==============================================================================
	bool Filemanager::load_im3(QStringList::Iterator &it)
	{
			bool ret = 0;

			QFileInfo fi(*it);
			ImageAttribute::record.imgFilename = it->toStdString();
			ImageAttribute::record.imgFilename_s = QString(fi.fileName()).toStdString();
			ImageAttribute::record.suffix = fi.suffix().toStdString();
			QDir dir = QFileInfo(*it).absoluteDir();
			ImageAttribute::record.path = dir.absolutePath().toStdString();
			//cout << " suffix: " << suffix << " thispath:" << path << " short: " << ImageAttribute::record.imgFilename_s << endl;

			ImageAttribute::record.imgNumber = 5;
			ImageAttribute::record.subimgNumber = 50;

			ImageAttribute::record.ID =				ImageAttribute::record.SpecData->getHeaderPointer()->ID;
			ImageAttribute::record.wavelenunit =  ImageAttribute::record.SpecData->getHeaderPointer()->wavelenunit;

			if (ImageAttribute::record.wavelenunit.size() == 0){
				ImageAttribute::record.wavelenunit = "nm";
			}

			//dimensions
			ImageAttribute::record.cubeDim[0] =  ImageAttribute::record.SpecData->getHeaderPointer()->imgsize[ 2 ];	//lines
			ImageAttribute::record.cubeDim[1] =  ImageAttribute::record.SpecData->getHeaderPointer()->imgsize[ 0 ];	//samples
			ImageAttribute::record.cubeDim[2] =  ImageAttribute::record.SpecData->getHeaderPointer()->imgsize[ 1 ];	//channels

			ImageAttribute::record.numdim		= ImageAttribute::record.SpecData->getHeaderPointer()->numdim;

			ImageAttribute::record.data_type	=  ImageAttribute::record.SpecData->getHeaderPointer()->data_type;
			ImageAttribute::record.data_type_str =  ImageAttribute::record.SpecData->getHeaderPointer()->data_type_str;
			ImageAttribute::record.interleave =  ImageAttribute::record.SpecData->getHeaderPointer()->interleave;
			ImageAttribute::record.headersize =  ImageAttribute::record.SpecData->getHeaderPointer()->headsize;
			ImageAttribute::record.pixelsize =  ImageAttribute::record.SpecData->getHeaderPointer()->pixelsize;
			ImageAttribute::record.byte_order =  ImageAttribute::record.SpecData->getHeaderPointer()->byte_order;

			ImageAttribute::record.opencvDataType =  ImageAttribute::record.SpecData->getOpenCVDatatype();

			ImageAttribute::record.data_type_minval = ImageAttribute::record.SpecData->getHeaderPointer()->data_type_minval;
			ImageAttribute::record.data_type_maxval =  ImageAttribute::record.SpecData->getHeaderPointer()->data_type_maxval;

			ImageAttribute::record.datatype = "12Bit-to16";

			//convert float to double
			std::vector< double > doubleVec(  ImageAttribute::record.SpecData->getHeaderPointer()->wavelen.begin(),
			ImageAttribute::record.SpecData->getHeaderPointer()->wavelen.end() );
			ImageAttribute::record.wavelength = doubleVec;

			ImageAttribute::record.blocksize_x = ImageAttribute::record.cubeDim[1];

		return ret;
	}
