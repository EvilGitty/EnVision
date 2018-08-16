#include "image_mask.h"
#include "Base/envision.h"

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
CustomPolygon::CustomPolygon()
{

}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
CustomPolygon::~CustomPolygon()
{

}

//==============================================================================
// void CustomPolygon::add(QGraphicsScene *scene, QVector<QPointF> seg)
//------------------------------------------------------------------------------
//==============================================================================
void CustomPolygon::add(QGraphicsScene *scene, QRectF rect, QPolygonF poly)
{
		QPen outlinePen(Qt::red);
		outlinePen.setWidth(1);

		polygon = new QGraphicsPolygonItem();
		polygon->setPolygon(poly);
		polygon->setPos(rect.x(), rect.y());
		polygon = scene->addPolygon(poly, outlinePen);
	return;
}
