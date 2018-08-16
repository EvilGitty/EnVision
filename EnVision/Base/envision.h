#ifndef ENVISION_H
#define ENVISION_H

#include <iostream>

#include <QtWidgets/QMainWindow>
#include <QTabWidget>
#include <QInputDialog>

// QpenCV
#include <opencv2/core/core.hpp>       
#include <opencv2/highgui/highgui.hpp>  
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>  

//-----------------------------------
// class Terminal
#include "terminal.h"
//-----------------------------------
// class TabHandling
#include "tabhandling.h"
//-----------------------------------
// class TableWidget
#include "Base/Widgets/tableWidget.h"
//-----------------------------------
// class PlotterWidget
#include "Base/Widgets/plotterWidget.h"
//-----------------------------------
//class CubeWidget
#include "Base/Widgets/cubeWidget.h"
//-----------------------------------
// class ImageWidget
#include "Base/Widgets/imageWidget.h"
//-----------------------------------
// class ImageGui
#include "Gui/gui_master.h"
//-----------------------------------
// class Plot
#include "Plotter/plot_master.h"
//-----------------------------------
// class Filemanager
#include "Filemanager/filemanager.h"
//-----------------------------------
#include "makros.h"

//-----------------------------------
// forms
#include "ui_envision.h"
#include "ui_table_widget.h"
#include "ui_plot_widget.h"
#include "ui_cube_widget.h"
#include "ui_image_widget.h"

#define RECENTFILES "/data/recentFiles/recentFiles.txt"
#define TEMPFILE "/data/recentFiles/temp.txt"

using namespace std;
using namespace cv;

namespace Ui {
	class EnVision_baseUI;
	class EnVision_tableUI;
	class EnVision_plotUI;
	class EnVision_cubeUI;
	class EnVision_imageUI;
}

class EnVision : public QMainWindow, public Ui::EnVision_imageUI, public ImageAttribute, public PlotAttribute, public Gui, public ImageGui, public PlotGui, public Terminal
{
	Q_OBJECT

public:
	EnVision(QStringList inputArguments, QStringList inputFiles, QString execPath, QWidget *parent = 0);
	~EnVision();

	Ui::EnVision_baseUI* getBaseUI(void);
	Ui::EnVision_tableUI* getTableUI(void);
	Ui::EnVision_plotUI* getPlotUI(void);
	Ui::EnVision_cubeUI* getCubeUI(void);
	Ui::EnVision_imageUI* getImageUI(void);
	TabHandling* tabhand;

	//-----------------------------------
	// a new image triggers this
	int activateNewImage(void);
	int activateCurrentImage(int index);

private:
	Ui::EnVision_baseUI* ui_base;
	Ui::EnVision_tableUI* ui_table;
	Ui::EnVision_plotUI* ui_plot;
	Ui::EnVision_cubeUI* ui_cube;
	Ui::EnVision_imageUI* ui_image;

	TableWidget*	newTable;
	PlotterWidget*  newPlot;
	CubeWidget*		newCube;
	ImageWidget*	newImage;

	Filemanager* filemanager;
	QFileDialog *fdialog;

	QStringList imgLoad1;
	QStringList imgLoad2;

public:

	QString execPath;
	QMdiSubWindow* activeSubWin;

private:
	int cascadeOrTile_status = 0;

public slots:
	
	void handleDockWidget03(int tabindex);
	void tileOrCascadeSubWindows(void);

	void createFileDialog(QFileDialog* openfdialog);
	void acceptFileDialog(void);
	void rejectFileDialog(void);

	void handleLeftSidebar(void);

	/*
	void setWorkingGuiState();
	void setIdleGuiState();
	void resetGui();
	*/

	QMdiSubWindow*  subWindowActivate(QMdiSubWindow* subwin);
	void attachWidget(QWidget* w, QString windowTitle);
	void detachWidget();

private slots:
	void saveWindowStatus();
	void reloadWindowStatus();

	//-----------------------------------
	// events
	void handleEventFilter(bool val, QObject* o);
	void dragEnterEvent(QDragEnterEvent* ev);
	void dropEvent(QDropEvent* event);
	void closeEvent(QCloseEvent* event);
	bool eventFilter(QObject* obj, QEvent *event);
	void mouseWheel(QWheelEvent* e);


signals: 
	void callFilemanager(QDropEvent* ev);

};

#endif // ENVISION_H