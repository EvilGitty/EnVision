#include "cubeWidget.h"
#include "Base/envision.h"
#include "Cube/initCube.h"

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
CubeWidget::CubeWidget(EnVision *main, QWidget *parent) : QMainWindow(parent), ui_cube(new Ui::EnVision_cubeUI)
{
		ui_cube->setupUi(this);
		this->main = main;

		widget = new GLWidget_cube(main, ui_cube);
		ui_cube->cube->addWidget(widget);

		//ERROR: Program and shader are not associated with the same context when detaching windows
		/*
		QObject::connect(this, SIGNAL(attachWidget_Signal(QWidget*, QString)), main, SLOT(attachWidget(QWidget*, QString)), Qt::UniqueConnection);

		QObject::connect(ui_image->actionattach, SIGNAL(triggered()), this, SLOT(attachWidget()));
		QObject::connect(ui_image->actiondetach, SIGNAL(triggered()), this, SLOT(detachWidget()));
		*/

}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
CubeWidget::~CubeWidget()
{

}

//==============================================================================
// Ui::EnVision_cubeUI* CubeWidget::getImageUI(void)
//------------------------------------------------------------------------------
//==============================================================================
Ui::EnVision_cubeUI* CubeWidget::getCubeUI(void)
{
	return ui_cube;
}


//==============================================================================
// void CubeWidget::attachWidget()
//------------------------------------------------------------------------------
//==============================================================================
void CubeWidget::attachWidget()
{
		emit attachWidget_Signal(this, "Cube");
	return;
}

//==============================================================================
// void CubeWidget::detachWidget()
//------------------------------------------------------------------------------
//==============================================================================
void CubeWidget::detachWidget()
{
		main->detachWidget();
	return;
}
