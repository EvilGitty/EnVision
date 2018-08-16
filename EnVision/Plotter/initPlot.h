#ifndef PLOTTERCLASS_H
#define PLOTTERCLASS_H

#include <QWheelEvent>
#include <QWidget>
#include <QMetaType>
#include <QDataStream>

//-----------------------------------
// class ImageAttribute
#include "Image/image_master.h"
//-----------------------------------
// class Terminal
#include "Base/terminal.h"
//-----------------------------------
// class Pixel Thread
#include "Thread/pixel_thread.h"
//-----------------------------------
// class Plot Widget
#include "ui_plot_widget.h"
//-----------------------------------
// class Image Widget
#include "ui_image_widget.h"
//-----------------------------------

#include "makros.h"

/*
#define  _imgIndex (main->Gui::tabRecord.imgIndex)
#define _samples (ImageAttribute::Record[_imgIndex].cubeDim[0])
#define _lines (ImageAttribute::Record[_imgIndex].cubeDim[1])
#define _channels (ImageAttribute::Record[_imgIndex].cubeDim[2])
#define _opencvDataType (ImageAttribute::Record[_imgIndex].opencvDataType)
#define _transpose (ImageAttribute::Record[_imgIndex].transposeDisplay)
#define _pixelsize (ImageAttribute::Record[_imgIndex].pixelsize)
#define _filename (ImageAttribute::Record[_imgIndex].imgFilename_s)
#define _maxDataVal (ImageAttribute::Record[_imgIndex].data_type_maxval)
#define _datatype (ImageAttribute::Record[_imgIndex].datatype)
*/

class EnVision;
class PixelareaThread;

class Plot : public QObject
{
	Q_OBJECT

public:
	Plot(EnVision* main);
	~Plot();

	void guiAccess();
	void init();

	void updatePlot(const QVector<double> xVector, const QVector<double> yVector, const int x, const int y, const QString str, const int listsize, const int listindex);

	QVector< double > xVector;
	//QVector< double > yVector;
	QVector< double > xProfile;
	QVector< double > yProfile;
	QVector< double > xVectorVertProfile;
	QVector< double > yVectorVertProfile;

	unsigned long normalize = 1;

private:

	EnVision* main;
	Ui::EnVision_baseUI* ui_base;
	Ui::EnVision_plotUI* ui_plot;
	Ui::EnVision_imageUI* ui_image;

public : 
	void xAxis(QString selection, int size_x);
	void yAxis(QString selection, int size_y);

	protected slots :
	void resetZoom();
	void dropEvent(QDropEvent *ev);
	void dragEnterEvent(QDragEnterEvent *ev);
	void resizeEvent(QResizeEvent *event);
	virtual bool eventFilter(QObject *o, QEvent *e);
	void mouseWheel(QWheelEvent* e);
	void horzScrollBarChanged(int value);
	void vertScrollBarChanged(int value);
	void xAxisChanged(QCPRange rangeNew, QCPRange rangeOld);
	void yAxisChanged(QCPRange rangeNew, QCPRange rangeOld);

public slots:
	int getData(int imgIndex, void* buffer, std::string geometry, long *dimPlane, long *dimVector, long *dimPoint);
	int plotPixel();
	void displayPlot();
	void finished();

public:
	QFutureWatcher<int> *watcher;
	PixelareaThread* data;
};


#endif //PLOTTERCLASS_H