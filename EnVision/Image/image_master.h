#ifndef IMAGEMASTER_H
#define IMAGEMASTER_H

#include <iostream>

#include <QString>
#include <QDirIterator>
#include <QAction>
#include <QMessageBox>
#include "qcustomplot.h" 

//-----------------------------------
// SpecIL
#include "SpecIL_Interface.h"


//-----------------------------------
// QpenCV
#include <opencv2/core/core.hpp>       
#include <opencv2/highgui/highgui.hpp>  
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>  
//-----------------------------------


#include "Mask/image_mask.h"
//#include "Plotter/initPlot.h"
#include "Mask/image_colormap.h"
#include "Events/image_zoom.h"

using namespace std;
using namespace cv;


class ImageMask;
//class Plot;
class ImageColormap;
class Graphics_view_zoom;

class ImageAttribute
{
public:

	//------------------------------------------------------------------------------
	struct _image{

		bool imgade_Loaded = 0;

		SpecIL_Interface* SpecData;

		int imgNumber;
		int subimgNumber;

		std::string imgFilename;
		std::string imgFilename_s;
		std::string suffix;
		std::string path;

		std::string ID;
		std::string wavelenunit;			// 
		unsigned long long cubeDim[3];			//samples, lines, band
		unsigned int numdim;

		/*
		enum t_data_type {					//	ENVI Datentyp
		DT_UNKNOWN = 0,			//		Unbekannt
		DT_8_BYTE = 1,			//		1 Byte
		DT_16_SINT = 2,			//		2 Byte Integer
		DT_32_SLONG = 3,			//		4 Byte Integer
		DT_32_FLOAT = 4,			//		4 Byte Float
		DT_64_DOUBLE = 5,			//		8 Byte Float (Double)
		DT_2x32_COMPLEX = 6,			//	2x	4 Byte Komplex
		DT_2x64_COMPLEX = 9,			//	2x	8 Byte Komplex
		DT_16_UINT = 12,			//		2 Byte Unsigned Integer
		DT_32_ULONG = 13,			//		4 Byte Unsigned Integer
		DT_64_SLONG = 14,			//		8 Byte Integer
		DT_64_ULONG = 15			//		8 Byte Unsigned Integer
		} data_type;
		std::string data_type_str;			//	Den Datentyp als Namen! fuer evtl. Unterscheidungen
		*/
		//	bei z.B. Tapsansi:
		//		byte, bool, char, uchar, short, ushort, int, uint,
		//		long, ulong, float, double
		unsigned int data_type;
		std::string data_type_str;

		/*
		enum t_interleave {			//	interleave:
		//	Achtung! So liegen die Daten in der Datei UND
		//	auch im geladenen Zustand im Speicher (type = 1) !
		IL_UNKNOWN,				//	Unbekannt
		IL_BSQ,					//	BSQ - band sequential
		IL_BIP,					//	BIP - band interleaved by pixel
		IL_BIL					//	BIL - band interleaved by line
		} interleave;				//
		*/
		unsigned int interleave;

		//headersize
		unsigned long long headersize;

		//bytes
		unsigned long long pixelsize;

		/*
		enum{							//	Byte Order
		BO_UNKNOWN = -1,			//
		BO_LSF = 0,					//	least significant byte (Little-endian)
		BO_MSF = 1					//	most significant byte (Big-endian)
		} byte_order;
		*/
		unsigned int byte_order = 1;

		int opencvDataType = 1;

		double data_type_maxval = 1;			// Maximaler Wert den der verwendete Datentyp erreichen kann;
		double data_type_minval = 0;			// Minimaler Wert den der verwendete Datentyp erreichen kann;

		//wavelengths
		std::vector <double> wavelength;

		//----------------------------
		//unused
		//begin of header
		//long frameperiod;
		//long integration_time;
		//int binning;
		//long numberOfFrames;
		//float aperture_size;
		//int lens;
		//int number_of_background;
		//std::string comment;
		//std::string serialnumber;
		//double scaling;
		//long header_offset;
		//std::string acquisition_date;		//filedate
		//std::string acquisition_start_time;
		//int data_type;
		//std::string interleave;
		//std::vector<double> default_bands;
		//int byte_order;
		//std::vector<double> wavelength;
		//end of header
		//----------------------------

		//////////////////////////////////////
		double contrastStretchStatic_min = 0.0;
		double contrastStretchStatic_max = 1.0;
		double contrastStretchDynamic_min = 0.5;
		double contrastStretchDynamic_max = 0.5;


		//tilesize
		unsigned long blocksize_x = 1;
		unsigned long blocksize_y = 1;
		unsigned long blocksize_z = 1;

		std::string datatype;

		struct _imgtile{
			int start;
			int limit;
			int numberOfTiles_x;
			int numberOfTiles_y;
		}imgtile;

		QVector<_imgtile> tile_x;
		QVector<_imgtile> tile_y;

		QImage qface01;
		QImage face02;
		QImage face03;
		QImage face04;
		QImage face05;
		QImage face06;

		//save opencv image
		cv::Mat cvface01;

		
		struct _visual{
			ImageMask* shape;
			//Plot* pixel;
			ImageColormap* color;
			Graphics_view_zoom* zoom;
		}visual;
		

		struct pixel_coordinates { qreal x; qreal y; qreal z; QString display; QString geometry; };
		QVector<pixel_coordinates> pixel_list;
	} record;
	static QVector<_image> Record;

	QImage qface01;

	void addVector()
	{
			Record.push_back(record);
		return;
	}

	void removeVector(int index)
	{
			Record.remove(index);
		return;
	}

	//==============================================================================
	// int Image::getData(int imgIndex, void* buffer, std::string geometry, long *dimPlane, long *dimVector, long *dimPoint)
	//------------------------------------------------------------------------------
	//==============================================================================
	int LoadLib_SpecIL(int imgIndex, void* buffer, std::string geometry, long *dimPlane, long *dimVector, long *dimPoint)
	{
		int imgNumber = ImageAttribute::Record[imgIndex].imgNumber;
		int subimgNumber = ImageAttribute::Record[imgIndex].subimgNumber;

		if (geometry.compare("Plane") == 0) {
			int x[2] = { static_cast<int>(*(dimPlane)), static_cast<int>(*(dimPlane + 1) - 1) };		//-1 at the end because the dimensions start at 0
			int y[2] = { static_cast<int>(*(dimPlane + 2)), static_cast<int>(*(dimPlane + 3) - 1) };	//-1 at the end because the dimensions start at 0
			int z[2] = { static_cast<int>(*(dimPlane + 4)), static_cast<int>(*(dimPlane + 5)) };		//*(dimPlane + 5) is -1 for channel-specific visualization 

			switch (imgNumber) {
			case 1: //tapsansi (*.tgd)
				switch (subimgNumber) {
				case 10: //tgd::hyspex SWIR320
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
					break;
				case 11: //tgd::hyspex SWIR384	
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
					break;
				case 12: //tgd::hyspex VNIR1600	
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
					break;
				case 13: //tgd::hyspex VNIR1800	
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
					break;
				case 14: //tgd::hyspex Mjolnir	
					//no testdata yet
					break;
				case 15://tgd::copter David
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
					break;
				case 16: //tgd::nuance
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
					break;
				case 17: //tgd::kinect I
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, z, y);
					break;
				case 18: //tgd::kinect II
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, z, y);
					break;
				}
				break;
			case 2: //uncalibrated hyspex (*.hyspex)
				switch (subimgNumber) {
				case 20: //SWIR320me	
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
					break;
				case 21: //SWIR384
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
					break;
				case 22: //VNIR1600
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
					break;
				case 23: //VNIR1800
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
					break;
				case 24://UVA_Mjolnir
					//no testdata yet
					break;
				}
				break;
			case 3: //calibrated hyspex (*.img)
				switch (subimgNumber) {
				case 30: //SWIR320me
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
					break;
				case 31: //SWIR384
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
					break;
				case 32: //VNIR1600
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
					break;
				case 33: //VNIR1800
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
					break;
				case 34: //UVA_Mjolnir
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
					break;
				}
				break;
			case 4:
				switch (subimgNumber) {
				case 40: //mat 5.3
					//?
					break;
				case 41: //mat 7.3
					//?
					break;
				case 42: //mat 7.4
					//?
					break;
				}
				break;
			case 5:
				switch (subimgNumber) {
				case 50: //Nuance
					ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
					break;
				}
				break;
			}
			return 1;
		}


		return 1;
	}
};


#endif //IMAGEMASTER_H

