#include "image_thread.h"
#include "Image/initImage.h"
#include "Base/Envision.h"

using namespace cv;

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
ImagetileThread::ImagetileThread(EnVision *main, Imageclass *img) : main(main), img(img)
{
		this->main = main;
		this->img = img;

		qRegisterMetaType<_QVector_block>("_QVector_block");
		qRegisterMetaType<cv::Mat>("MyMat");
		qRegisterMetaType<QImage>("_QImage");

		connect(this, &ImagetileThread::resultIsReady, img, &Imageclass::showCubeFace01, Qt::AutoConnection);
}



//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
ImagetileThread::~ImagetileThread()
{

}

//==============================================================================
// int ImagetileThread::loadCubeFace01(QVector<int> param, int channel)
//------------------------------------------------------------------------------
//==============================================================================
int ImagetileThread::loadCubeFace01(QVector<int> param, int channel)
{
		QVector<int> blockstart = (QVector<int>(2));
		QVector<int> blockend = (QVector<int>(2));

		long limitX = ImageAttribute::Record[_imgIndex].tile_x[param[1]].limit;
		long limitY = ImageAttribute::Record[_imgIndex].tile_y[param[3]].limit;

		buffer = new unsigned char[limitX * limitY * _pixelsize];

		int tileindex = 0;

		for (size_t countTiles_y = param[2]; countTiles_y < param[3]; ++countTiles_y){

			blockstart.replace(0, ImageAttribute::Record[_imgIndex].tile_y[countTiles_y].start);
			blockend.replace(0, ImageAttribute::Record[_imgIndex].tile_y[countTiles_y].limit);

			for (size_t countTiles_x = param[0]; countTiles_x < param[1]; ++countTiles_x){
				blockstart.replace(1, ImageAttribute::Record[_imgIndex].tile_x[countTiles_x].start);
				blockend.replace(1, ImageAttribute::Record[_imgIndex].tile_x[countTiles_x].limit);
				convertToImage(_imgIndex, tileindex, blockstart, blockend, channel);

				++tileindex;
			}
		}
		delete[] buffer;
		
	return 0;
}

//==============================================================================
// cv::Mat ImagetileThread::convertToImage(int imgIndex, QVector<int> blockstart, QVector<int> blockend, int channel)
//------------------------------------------------------------------------------
//==============================================================================
void ImagetileThread::convertToImage(int imgIndex, int tileindex, QVector<int> blockstart, QVector<int> blockend, int channel)
{
		long dimPlane[6];
		dimPlane[0] = blockstart[0];
		dimPlane[1] = blockend[0];
		dimPlane[2] = blockstart[1];
		dimPlane[3] = blockend[1];
		dimPlane[4] = channel;
		dimPlane[5] = -1;
		

		
		cout << dimPlane[0] << " " << dimPlane[1] << " " << dimPlane[2] << " " << dimPlane[3] << " " << dimPlane[4] << " " << dimPlane[5] << endl;

		this->LoadLib_SpecIL(imgIndex, buffer, "Plane", dimPlane, 0, 0);

		/*
		cv::Mat rawPlane = cv::Mat(blockend[1] - blockstart[1], blockend[0] - blockstart[0], ImageAttribute::Record[imgIndex].opencvDataType, buffer).t();
		cv::Mat normalizedImg(rawPlane.cols, rawPlane.rows, CV_8UC1, Scalar(0, 0, 0));

		double tempmin, tempmax;
		int minInd, maxInd;
		cv::minMaxIdx(rawPlane, &tempmin, &tempmax, &minInd, &maxInd, Mat());
		
		if (tempmin < 	ImageAttribute::Record[imgIndex].contrastStretchDynamic_min) {
			ImageAttribute::Record[imgIndex].contrastStretchDynamic_min = tempmin;
		} else {
			tempmin = ImageAttribute::Record[imgIndex].contrastStretchDynamic_min;
		}
		if (tempmax >= ImageAttribute::Record[imgIndex].contrastStretchDynamic_max) {
			ImageAttribute::Record[0].contrastStretchDynamic_max = tempmax;
		} else {
			tempmax = ImageAttribute::Record[imgIndex].contrastStretchDynamic_max;
		}

		cvtColor(rawPlane, rawPlane, CV_GRAY2RGB);

		rawPlane.convertTo(normalizedImg, CV_8UC3, 255.0 / (tempmax - tempmin +0.001));

		emit resultIsReady(tileindex, blockstart, blockend, normalizedImg);
		*/
	return;
}

void process()
{



}

//==============================================================================
// int Imageclass::LoadLib_SpecIL(int imgIndex, void* buffer, std::string geometry, long *dimPlane, long *dimVector, long *dimPoint)
//------------------------------------------------------------------------------
//==============================================================================
int ImagetileThread::LoadLib_SpecIL(int imgIndex, void* buffer, std::string geometry, long *dimPlane, long *dimVector, long *dimPoint)
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
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, y, z);
					break;
				case 11: //tgd::hyspex SWIR384	
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, y, z);
					break;
				case 12: //tgd::hyspex VNIR1600	
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, y, z);
					break;
				case 13: //tgd::hyspex VNIR1800	
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, y, z);
					break;
				case 14: //tgd::hyspex Mjolnir	
					//no testdata yet
					break;
				case 15://tgd::copter David
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, y, z);
					break;
				case 16: //tgd::nuance
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, y, z);
					break;
				case 17: //tgd::kinect I
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, z, y);
					break;
				case 18: //tgd::kinect II
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, z, y);
					break;
				}
				break;
			case 2: //uncalibrated hyspex (*.hyspex)
				switch (subimgNumber) {
				case 20: //SWIR320me	
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, y, z);
					break;
				case 21: //SWIR384
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, y, z);
					break;
				case 22: //VNIR1600
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, y, z);
					break;
				case 23: //VNIR1800
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, y, z);
					break;
				case 24://UVA_Mjolnir
					//no testdata yet
					break;
				}
				break;
			case 3: //calibrated hyspex (*.img)
				switch (subimgNumber) {
				case 30: //SWIR320me
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, y, z);
					break;
				case 31: //SWIR384
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, y, z);
					break;
				case 32: //VNIR1600
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, y, z);
					break;
				case 33: //VNIR1800
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, y, z);
					break;
				case 34: //UVA_Mjolnir
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, y, z);
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
					ImageAttribute::Record[0].SpecData->getPlane(buffer, x, y, z);
					break;
				}
				break;
			}
			return 1;
		}

	return 1;
}