#ifndef PIXELAREATHREAD_H
#define PIXELAREATHREAD_H

#include <QThread>
#include <qtconcurrentrun.h>

#include <opencv2/core/core.hpp>       
#include <opencv2/highgui/highgui.hpp>  
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>   

#include "Image/image_master.h"
#include "Plotter/initPlot.h"

using namespace std;

class EnVision;
class Plot;

typedef QVector<double> _QVector;

class PixelareaThread : public QThread, public ImageAttribute
{
	Q_OBJECT;
public:
	PixelareaThread(EnVision *main, Plot *plot);
	PixelareaThread::~PixelareaThread();
private:

	EnVision *main;
	Plot *plot;

	unsigned char* buffer;

	public slots :
	int loadSinglePixel(int imgIndex, QVector<double> xVector, QVector<ImageAttribute::_image::pixel_coordinates> pixel_list);
	int LoadLib_SpecIL(int imgIndex, void* buffer, std::string geometry, long *dimPlane, long *dimVector, long *dimPoint);

signals:
	void resultIsReady(const _QVector xVector, const _QVector yVector, const int x_pos, const int y_pos, QString string, const int size, const int listindex);

};

#endif //PIXELAREATHREAD_H


