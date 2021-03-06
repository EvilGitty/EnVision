#include "image_mask.h"
#include "Base/envision.h"

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
CustomEllipse::CustomEllipse()
{

}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
CustomEllipse::~CustomEllipse()
{

}

//==============================================================================
// void CustomRect::add(QGraphicsScene *scene, int x, int y)
//------------------------------------------------------------------------------
//==============================================================================
void CustomEllipse::add(QGraphicsScene *scene, QRectF rect)
{
		QPen outlinePen(Qt::red);
		outlinePen.setWidth(1);

		ellipse = new QGraphicsEllipseItem();
		ellipse->setPos(rect.x(), rect.y());
		ellipse = scene->addEllipse(rect, outlinePen);
	return;
}
