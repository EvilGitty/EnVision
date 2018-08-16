#include "geometries.h"
#include "Base/envision.h"

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
ImageGeometries::ImageGeometries(EnVision* main)
{
	this->main = main;


	guiAccess();



}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
ImageGeometries::~ImageGeometries()
{



}

//==============================================================================
// void Plot::guiAccess()
//------------------------------------------------------------------------------
//==============================================================================
void ImageGeometries::guiAccess()
{
	this->ui_base = main->getBaseUI();
	this->ui_plot = main->getPlotUI();
	this->ui_image = main->getImageUI();

	return;
}

//==============================================================================
// void ImageGeometries::rectangle()
//------------------------------------------------------------------------------
//==============================================================================
void ImageGeometries::rectangle(double x, double y)
{

		QCPItemText *   xInfoText = new QCPItemText(ui_image->image);
		xInfoText->setPositionAlignment(Qt::AlignTop | Qt::AlignLeft);
	//	xInfoText->position->setAxisRect(xRect);
		xInfoText->position->setType(QCPItemPosition::ptAxisRectRatio);
		xInfoText->position->setCoords(x, y);
		xInfoText->setText("IndiText");
	//	xInfoText->setFont(QFont(font().family(), 8));
		xInfoText->setPen(QPen(Qt::transparent));
		xInfoText->setColor(Qt::black);

	//	ui_image->image->addItem(xInfoText);
		
	return;
}