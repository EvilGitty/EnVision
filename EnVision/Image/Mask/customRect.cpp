#include "image_mask.h"
#include "Base/envision.h"

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
CustomRect::CustomRect()
{

}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
CustomRect::~CustomRect()
{

}

//==============================================================================
// void CustomRect::add(QGraphicsScene *scene, int x, int y)
//------------------------------------------------------------------------------
//==============================================================================
void CustomRect::add(QGraphicsScene *scene, QRectF rect)
{
		QPen outlinePen(Qt::red);
		outlinePen.setWidth(1);

		rectangle = new QGraphicsRectItem();
		rectangle->setRect(rect.x() - outlinePen.width() / 2, rect.y() - outlinePen.width() / 2, rect.width() + outlinePen.width(), rect.height() + outlinePen.width());
		rectangle = scene->addRect(rect, outlinePen);
	return;
}
