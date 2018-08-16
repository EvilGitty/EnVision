#ifndef IMAGECLASS_H
#define IMAGECLASS_H

#include <QWheelEvent>
#include <QWidget>
#include <QtConcurrent>
#include <QFuture>
#include <QMetaType>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsObject>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QPolygonF>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>

//-----------------------------------
// class ImageAttribute
#include "Plotter/initPlot.h"
//-----------------------------------
// class ImageAttribute
#include "Image/image_master.h"
//-----------------------------------
// class Colormap
#include "Mask/image_colormap.h"
//-----------------------------------
// class Terminal
#include "Base/terminal.h"
//-----------------------------------
// class Geometries
#include "Mask/image_mask.h"
//-----------------------------------
// class Image Thread
#include "Thread/image_thread.h"
//-----------------------------------
// class Image Widget
#include "Events/image_zoom.h"
//-----------------------------------
// class Plot Widget
#include "ui_plot_widget.h"
//-----------------------------------
// class Image Widget
#include "ui_image_widget.h"
//-----------------------------------

#define CHANNELFOLDER "Data//"

class EnVision;
class ImagetileThread;

inline cv::Mat QImageToCvMat(const QImage &inImage, bool inCloneImageData);

class Imageclass : public QGraphicsView
{
	Q_OBJECT

public:
	Imageclass(EnVision* main);
	~Imageclass();

	void guiAccess();

	QImage image;
	int colorId;
	bool saturation;
	int save_channel;

private:

	EnVision* main;
	Ui::EnVision_baseUI* ui_base;
	Ui::EnVision_plotUI* ui_plot;
	Ui::EnVision_imageUI* ui_image;

	ImageColormap *color;
	ImageMask *shape;
	Plot* pixel;
	Terminal out;

	Graphics_view_zoom* zoom;

private:

	QPoint oldMousePos;

	cv::Mat cvface01;

public: 
	void displayImage(QImage image);
	void updateImage();
	void updateThumbnail(QPixmap smallPixmap);
	void initThumbnail();
	void buildMap(int blocksize_x, int blocksize_y);

protected:
	void dropEvent(QDropEvent *ev);
	void dragEnterEvent(QDragEnterEvent *ev);
	void resizeEvent(QResizeEvent *event);
	virtual bool eventFilter(QObject *o, QEvent *e);
	void mouseWheel(QWheelEvent* e);

public slots:
	void mouseBehavior(int id);
	void saveChannel();
	void loadChannel();
	void handleGeometryCombobox();
	void openExplorer();

	void horzScrollBarChanged(int value);
	void vertScrollBarChanged(int value);
	void xAxisChanged(QCPRange rangeNew, QCPRange rangeOld);
	void yAxisChanged(QCPRange rangeNew, QCPRange rangeOld);

	void init(ImageAttribute::_image record);
	void activateThumbnail(QListWidgetItem* item);


protected:
	void paintEvent(QPaintEvent *pe) Q_DECL_OVERRIDE;
signals:

	public Q_SLOTS :

	void showCubeFace01(const int tileindex, const QVector<int> blockstart, const QVector<int> blockend, cv::Mat mat);

	void finishedTiles();

private:
	void getPixel();
	void getChannel(int channel);

public:
	QFutureWatcher<int> *watcher;
	QList<	QFutureWatcher<int>*> watcherList;
	ImagetileThread* data;

};


#endif //IMAGECLASS_H
