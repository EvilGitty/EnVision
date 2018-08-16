#ifndef IMAGETILETHREAD_H
#define IMAGETILETHREAD_H

#include <QThread>
#include <qtconcurrentrun.h>

#include <opencv2/core/core.hpp>       
#include <opencv2/highgui/highgui.hpp>  
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>   

#include "Image/image_master.h"
#include "Image/initImage.h"

using namespace std;

class EnVision;
class Imageclass;

typedef QVector<int> _QVector_block;
typedef QImage _QImage;
typedef cv::Mat MyMat;

class ImagetileThread : public QThread, public ImageAttribute
{
	Q_OBJECT;
public:
	ImagetileThread(EnVision *main, Imageclass *img);
	ImagetileThread::~ImagetileThread();
private:

	unsigned char* buffer;

	EnVision *main;
	Imageclass *img;

public slots :
	int loadCubeFace01(QVector<int> param, int channel);
	void convertToImage(int index, int tileindex, QVector<int> blockstart, QVector<int> blockend, int channel);
	int LoadLib_SpecIL(int imgIndex, void* buffer, std::string geometry, long *dimPlane, long *dimVector, long *dimPoint);

signals:
	void resultIsReady(const int tileindex, const _QVector_block blockstart, const _QVector_block blockend, const MyMat mat);
};

#endif //IMAGETILETHREAD_H


