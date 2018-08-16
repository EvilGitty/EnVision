#ifndef IMG_GEOMETRIES_H
#define IMG_GEOMETRIES_H

#include <iostream>
#include <QString>
#include <QStringList>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>

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

#define  _imgIndex (main->Gui::tabRecord.imgIndex)

class EnVision;
class CustomRect;

class CustomRect : public QGraphicsRectItem
{
public:

	CustomRect();
	~CustomRect();

	QGraphicsRectItem* point;
	QGraphicsRectItem* rectangle;
	void add(QGraphicsScene *scene, QRectF rect);

};


class CustomEllipse : public QGraphicsEllipseItem
{
public:

	CustomEllipse();
	~CustomEllipse();

	QGraphicsEllipseItem* ellipse;
	void add(QGraphicsScene *scene,  QRectF rect);

};

class CustomPolygon : public QGraphicsPolygonItem
{
public:

	CustomPolygon();
	~CustomPolygon();

	QGraphicsPolygonItem* polygon;
	void add(QGraphicsScene *scene, QRectF rect, QPolygonF poly);

};

class CustomLine : public QGraphicsLineItem
{
public:
	CustomLine();
	~CustomLine();

	QGraphicsLineItem* line;
};


class CustomText : public QGraphicsTextItem
{
public:
	CustomText();
	~CustomText();
};

class QGraphicsItemLayer : public QGraphicsItem
{
public:
	virtual QRectF boundingRect()
	{
		return QRectF(0, 0, 0, 0);
	}

	virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
	{
	}
};

class ImageMask : public QGraphicsScene
{

	Q_OBJECT

public:

	ImageMask(EnVision* main, QWidget* parent = 0);
	~ImageMask();

	void guiAccess();
	void updatePixmap(QImage image, int x, int y);
	void updateItemGroup(QString toDo, QGraphicsItem * item, QList<QGraphicsItem*> items);
	void updateItem(QGraphicsItem * item, QRectF rect, QPolygonF poly);
	void remove(QGraphicsItem * item);
	void drawBackground(QPixmap map, const QRectF & rect);


	QList<QGraphicsPixmapItem *> imageTileList;
	QGraphicsPixmapItem* pixmapitem;

	QGraphicsItemGroup *group;
	QGraphicsView *view;
	QGraphicsScene*scene;
	QGraphicsItem* currentItem;
	QPointF pos_currentItem;

	QGraphicsRectItem* spoint;
	QGraphicsRectItem* rectangle;
	QGraphicsEllipseItem* ellipse;
	QGraphicsPolygonItem* polygon;
	QGraphicsLineItem* line;
	QGraphicsTextItem* text;

private:

	EnVision* main;
	Ui::EnVision_baseUI* ui_base;
	Ui::EnVision_plotUI* ui_plot;
	Ui::EnVision_imageUI* ui_image;

	int GRID_STEP = 30; 

	CustomRect* csP;
	CustomRect* cR;
	CustomEllipse* cE;
	CustomPolygon* cP;
	CustomLine* cL;
	CustomText* cT;
};


#endif //IMG_GEOMETRIES_H
