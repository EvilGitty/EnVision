#ifndef IMG_GEOMETRIES_H
#define IMG_GEOMETRIES_H

#include <iostream>
#include <QString>
#include <QStringList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsObject>

//-----------------------------------
// class ImageAttribute
#include "Image/image_master.h"
//-----------------------------------
// class Terminal
#include "Base/terminal.h"
//-----------------------------------
// class Plot Widget
#include "ui_plot_widget.h"
//-----------------------------------
// class Image Widget
#include "ui_image_widget.h"
//-----------------------------------

class EnVision;

class ImageGeometries : public QGraphicsScene
{
public:

	ImageGeometries(EnVision* main);
	~ImageGeometries();

	void guiAccess();
	void rectangle(double x, double y);
private:

	EnVision* main;
	Ui::EnVision_baseUI* ui_base;
	Ui::EnVision_plotUI* ui_plot;
	Ui::EnVision_imageUI* ui_image;

};

#endif //IMG_GEOMETRIES_H
