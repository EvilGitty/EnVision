#include "pixel_thread.h"
#include "Plotter/initPlot.h"
#include "Base/Envision.h"

using namespace cv;

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
PixelareaThread::PixelareaThread(EnVision *main, Plot *plot) : main(main), plot(plot)
{
		this->main = main;
		this->plot = plot;

		qRegisterMetaType<_QVector>("_QVector");

		connect(this, &PixelareaThread::resultIsReady, plot, &Plot::updatePlot, Qt::AutoConnection);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
PixelareaThread::~PixelareaThread()
{

}

//==============================================================================
// void PixelareaThread::loadSinglePixel(int imgIndex)
//------------------------------------------------------------------------------
//==============================================================================
int PixelareaThread::loadSinglePixel(int imgIndex, QVector<double> xVector, QVector<ImageAttribute::_image::pixel_coordinates> pixel_list)
{
	/*
	int x_pos = pixel_list[0].x;
	int y_pos = pixel_list[0].y;
	int z_pos = pixel_list[0].z;

	int x_limit = pixel_list[1].x;
	int y_limit = pixel_list[1].y;
	int z_limit = pixel_list[1].z;
	
	QString geometry = pixel_list[0].geometry;
	QString display = pixel_list[0].display;

	QVector<int> blockstart;
	QVector<int> blockend;
	blockstart.push_back(y_pos);
	blockstart.push_back(x_pos);
	blockend.push_back(y_limit-1);
	blockend.push_back(x_limit-1);
	int channel = 51;
	long dimPlane[6];
	dimPlane[0] = blockstart[0];
	dimPlane[1] = blockend[0];
	dimPlane[2] = blockstart[1];
	dimPlane[3] = blockend[1];
	dimPlane[4] = channel;
	dimPlane[5] = -1;

	//cout <<"! " <<dimPlane[0] << " " << dimPlane[1] << " " << dimPlane[2] << " " << dimPlane[3] << " " << dimPlane[4] << " " << dimPlane[5] << endl;

	double factor = plot->normalize / (double)_maxDataVal;
	//cv::Mat out = cv::Mat(_channels*100 * 110, 1, CV_8UC3, Scalar(0, 0, 0));
	cv::Mat out;
	QVector<double> yVector(_channels);
	//cout << " size yVector:" << yVector.size() << endl;
	buffer = new unsigned char[(100) * (100) * _pixelsize];

	for (int i = 0; i < _channels; ++i){

		this->LoadLib_SpecIL(imgIndex, buffer, "Plane", dimPlane, 0, 0);
		cv::Mat rawPlane((blockend[0] - blockstart[0]) * (blockend[1] - blockstart[1]), 1, _opencvDataType, buffer);
		cv::Mat normalizedImg(rawPlane.rows * rawPlane.cols, 1, CV_8UC1);
	//	cvtColor(rawPlane, rawPlane, CV_GRAY2RGB);
		rawPlane.convertTo(normalizedImg, CV_8UC1, 255.0 / (0.5));


		//cout << " size " << normalizedImg.rows << " " << normalizedImg.cols << " " << out.rows << " " << out.cols << endl;
		//normalizedImg.copyTo(out(Rect(i, 0, 100 * 110, 1)));
		//mat.copyTo(cvface01(Rect(int(blockstart[1]), int(blockstart[0]), (mat).cols, (mat).rows)));
		//normalizedImg.copyTo(out(Rect(0, i, 100 * 110, 1)));

		//normalizedImg = normalizedImg.reshape(110 * 100,1);
		out.push_back(normalizedImg);//   A.push_back(normalizedImg.reshape(0, 1))
		//	cout << " size " << normalizedImg.rows << " " << normalizedImg.cols << endl;
		//int listsize = rawPlane.rows*rawPlane.cols;
		//for (int listindex = 0; listindex < listsize; ++listindex) {
		//}
		cout << " size " << normalizedImg.rows << " " << normalizedImg.cols << " " << out.rows << " " << out.cols << endl;


		//cout << "i: " << out.at<ushort>(i) << endl;
	}

	//cout << " size "  << out.rows << " " << out.cols << endl;
	//imshow("longimga", out);

	delete[] buffer;

	
	int listsize = out.rows /_channels;
//	cout << listsize << endl;
	int raw_step = 0;
	for (int listindex = 0; listindex < listsize; ++listindex) {
		
		raw_step = 0;
		ushort* _raw = out.ptr<ushort>(raw_step);
		for (int channel = 0; channel < _channels; ++channel) {
			double value = _raw[channel];
			yVector[channel] = value *factor;
		}
		if (raw_step == 0){
			emit resultIsReady(xVector, yVector, 0, 0, display + geometry, listsize, listindex);
		}

		raw_step += _channels;
		//cout << yVector.size() << endl;
	}
	*/
	//cout << raw_step << endl;
	
	
	

	
	
		if (ImageAttribute::Record[imgIndex].imgade_Loaded == 1){

			int x_ind;
			int y_ind;
			int z_ind;

			int x_pos = x_ind = pixel_list[0].x;
			int y_pos = y_ind = pixel_list[0].y;
			int z_pos = z_ind = pixel_list[0].z;

			int x_limit = pixel_list[1].x;
			int y_limit = pixel_list[1].y;
			int z_limit = pixel_list[1].z;

			int cols = x_limit - x_pos;
			int rows = y_limit - y_pos;

			int listsize = (rows)* (cols);
			if (listsize < 1){
				return 0;
			}

			long dimVector[3];
			double X_val_min = _maxDataVal;
			double X_val_max = 0;
			double Y_val_min = _maxDataVal;
			double Y_val_max = 0;

			//factor for scaling between 0..maxVal and 0..1
			double factor = plot->normalize / (double)_maxDataVal;

			//cout << factor << endl;
			QString geometry = pixel_list[0].geometry;
			QString display = pixel_list[0].display;			
			cv::Mat rawVector = cv::Mat(_channels, 1, _opencvDataType);
	
			QVector<double> yVector(rawVector.rows);

			buffer = new unsigned char[_channels* _pixelsize];

			for (int listindex = 0; listindex < listsize; ++listindex) {

//				cout << "listindex" << listindex << " listsize:" << listsize << endl;
				//spectral plot
				if (((geometry.compare("Single Point") == 0) ||
					(geometry.compare("Rectangle") == 0) ||
					(geometry.compare("Ellipse") == 0) ||
					(geometry.compare("Polygon") == 0)
					)) {

					y_ind = y_pos + listindex / (cols);
					x_ind = x_pos + listindex % (cols);
					z_ind = -1;
					dimVector[0] = x_ind; dimVector[1] = y_ind; dimVector[2] = z_pos = z_ind;
				}

				LoadLib_SpecIL(_imgIndex, buffer, "Vector", 0, dimVector, 0);
				rawVector = cv::Mat(_channels, 1, _opencvDataType, buffer);

				cout << "_datatype "<<_datatype << endl;
				double value;
				void* _raw = rawVector.ptr<void>(0);

				for (int channel = 0; channel < rawVector.rows; ++channel) {
					if (_datatype.compare("float") == 0) {
						float* _rawptr = reinterpret_cast<float*>(_raw);
						value = _rawptr[channel];
					}
					if (_datatype.compare("ushort") == 0) {
						ushort* _rawptr = reinterpret_cast<ushort*>(_raw);
						value = _rawptr[channel];
					}
					if (_datatype.compare("uint") == 0) {
						uint* _rawptr = reinterpret_cast<uint*>(_raw);
						value = _rawptr[channel];
					}
					if (_datatype.compare("kinect") == 0) {
						value = rawVector.at<uchar>(channel);
					}

					if ((geometry.compare("Single Point") == 0) || (geometry.compare("Rectangle") == 0)) {
						yVector[channel] = value *factor;
					}
					if (geometry.compare("xProfile") == 0) {
						//xProfile << value;
					}
					if (geometry.compare("yProfile") == 0) {
						//yProfile.prepend(value);		//prepend because y-axis is flipped
					}
				}

				//cout << "xVecor: " << xVector.size() << " yVecor: " << yVector.size() << endl;
				
				if (geometry.compare("Single Point") == 0) {
					//if (ui_plot->checkBox_graphPreview->isChecked() == 1) {
					emit resultIsReady(xVector, yVector, x_ind, _samples - y_ind, display + geometry, listsize, listindex);
					//}
				}

				if (geometry.compare("Rectangle") == 0) {
					//if (ui_plot->checkBox_graphPreview->isChecked() == 1) {
					emit resultIsReady(xVector, yVector, x_ind, _samples - y_ind, display + geometry, listsize, listindex);
					//}
				}
				
			}
			
			
			delete[] buffer;
		}
		
	
	return 0;
}

//==============================================================================
// int Image::LoadLib_SpecIL(int imgIndex, void* buffer, std::string geometry, long *dimPlane, long *dimVector, long *dimPoint)
//------------------------------------------------------------------------------
//==============================================================================
int PixelareaThread::LoadLib_SpecIL(int imgIndex, void* buffer, std::string geometry, long *dimPlane, long *dimVector, long *dimPoint)
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

	if (geometry.compare("Vector") == 0) {

		int x = *(dimVector);
		int y = *(dimVector + 1);
		int z = *(dimVector + 2);
		switch (imgNumber) {

		case 1: //tapsansi (*.tgd)
			switch (subimgNumber) {
			case 10: //tgd::hyspex SWIR320
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, x, z);
				break;
			case 11: //tgd::hyspex SWIR384
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, x, z);
				break;
			case 12: //tgd::hyspex VNIR1600
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, x, z);
				break;
			case 13: //tgd::hyspex VNIR1800
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, x, z);
				break;
			case 14: //tgd::hyspex Mjolnir
				//no testdata yet
				break;
			case 15://tgd::copter David
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, x, z);
				break;
			case 16: //tgd::nuance
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, x, z);
				break;
			case 17: //tgd::kinect I
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, z, x);
				break;
			case 18: //tgd::kinect II
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, z, x);
				break;
			}
			break;
		case 2: //uncalibrated hyspex (*.hyspex)
			switch (subimgNumber) {
			case 20: //SWIR320me
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, x, z);
				break;
			case 21: //SWIR384
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, x, z);
				break;
			case 22: //VNIR1600
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, x, z);
				break;
			case 23: //VNIR1800
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, x, z);
				break;
			case 24://UVA_Mjolnir
				//no testdata yet
				break;
			}
			break;
		case 3: //calibrated hyspex (*.img)
			switch (subimgNumber) {
			case 30: //SWIR320me
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, x, z);
				break;
			case 31: //SWIR384
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, x, z);
				break;
			case 32: //VNIR1600
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, x, z);
				break;
			case 33: //VNIR1800
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, x, z);
				break;
			case 34: //UVA_Mjolnir
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, x, z);
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
				ImageAttribute::Record[imgIndex].SpecData->getVector(buffer, y, x, z);
				break;
			}
			break;
		}
	}

	return 1;
}



