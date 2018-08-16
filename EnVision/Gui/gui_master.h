#ifndef GUIMASTER_H
#define GUIMASTER_H

#include <iostream>

#include <QSharedPointer>
#include <QString>
#include <QDirIterator>
#include <QAction>
#include <QMessageBox>
#include "qcustomplot.h" 

//-----------------------------------
// QpenCV
#include <opencv2/core/core.hpp>       
#include <opencv2/highgui/highgui.hpp>  
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>  
//-----------------------------------

using namespace std;
using namespace cv;

class Gui
{

public:

	//-----------------------------------
	//general tab and widget status variables
	struct _tabsettings{

		int tableIndex = 0;
		int plotIndex = 0;
		int cubeIndex = 0;
		int imgIndex = 0;

		bool tableWidget_attached = 0;
		bool plotWidget_attached = 0;
		bool cubeWidget_attached = 0;
		bool imageWidget_attached = 0;
		/*
		bool tableWidgetTab_attached = 0;
		bool plotWidgetTab_attached = 0;
		bool cubeWidgetTab_attached = 0;
		bool imageWidgetTab_attached = 0;
		*/
		QTableWidget* currentTable = {0};
		QCustomPlot *currentPlot = { 0 };
		QCustomPlot *currentCube = { 0 };
		//QCustomPlot *currentImageplot = {0};
		QGraphicsView *currentImage = { 0 };

		QSize size_tableWidget;
		QSize size_plotWidget;
		QSize size_cubeWidget;
		QSize size_imageWidget;
	}tabRecord;
};

//-----------------------------------
//Plot gui
class PlotGui
{
public:

	struct _settings
	{

	}record;
	static QVector<_settings> Record;

	void addGuisettings()
	{
		Record.push_back(record);
		return;
	}

	void removeGuisettings(int index)
	{
		Record.remove(index);
		return;
	}
};

//-----------------------------------
//Image gui
class ImageGui
{
public:

	//-----------------------------------
	//gui status variables
	struct _settings{

		struct _scrollbars
		{
			int val_vScrollBar = 0;
			int val_hScrollBar = 0;

			int max_vScrollBar = 0;
			int max_hScrollBar = 0;

			int min_vScrollBar = 0;
			int min_hScrollBar = 0;

		}scrollbars;

		int channel = 0;

		struct _imgColormap
		{
			int listindex = 0;
			int colorID = -1;
			enum colorIDs	{ Gray = 0, HSV = 1, Jet = 2, Bone = 3, Rainbow = 4, Ocean = 0, Spring = 1, Summer = 2, Autumn = 3, Winter = 4,
								Cool = 1, Hot = 2, Pink = 3, Parula = 4 };
			QStringList strings = QStringList() << "Gray" << "HSV" << "Jet" << "Bone" <<
												"Rainbow" << "Ocean" << "Spring" << "Summer" <<
												"Autumn" << "Winter" << "Cool" << "Hot" << "Pink" <<
												"Parula";
		}imgColormap;
		int imgcolor = _imgColormap::colorIDs::Gray;

		struct _imggeometry
		{
			int listindex = 0;
			enum plotGeometry	{ singlePoint = 0, rectangle = 1, circle = 2, xProfile = 3, yprofile = 4 };
			QStringList strings = QStringList() << "Single Point" << "Rectangle" << "Ellipse" << "Polygon" << "Line" << "xProfile" << "yProfile" << "Text";
		}imgGeometry;
		int pixelgeometry = _imggeometry::plotGeometry::singlePoint;

		struct _visuals
		{
			enum negative { neg_on = 1, neg_off = 0 };
			enum saturation { sat_on = 1, sat_off = 0 };
			double contrast = 0;
			double brightness = 0;
		}visuals;

		int negative = _visuals::negative::neg_off;
		int saturation = _visuals::saturation::sat_on;

		struct _mouseBehaviour
		{
			enum scroll { scroll_on = 1, scroll_off = 0 };
			enum draw { draw_on = 1, draw_off = 0 };
		}mouseBehaviour;
		int scroll = _mouseBehaviour::scroll::scroll_on;
		int draw = _mouseBehaviour::draw::draw_off;

		/*
		struct Viewport_plot
		{
		QList <double> lower_x;
		QList <double> upper_x;
		QList <double> lower_y;
		QList <double> upper_y;
		enum test { up = 1, down = 0 };
		} view;

		struct Mechanics
		{
		enum mouseWheel { up = 1, down = 0, neutral = -1 };
		enum y_bound { hit = 1, miss = 0 };
		enum mousePos { inside = 1, outside = 0 };
		enum resizeWidget { yes = 1, no = 0 };
		} x;

		struct pixel_coordinates { double x; double y; double z; };

		int mWheel = Mechanics::mouseWheel::down;
		int y_zoom = Mechanics::y_bound::miss;
		int mouse = Mechanics::mousePos::outside;
		int resizeWidget = Mechanics::resizeWidget::yes;
		*/

	}record;
	static QVector<_settings> Record;

	void addGuisettings()
	{
			Record.push_back(record);
		return;
	}

	void removeGuisettings(int index)
	{
			Record.remove(index);
		return; 
	}


};

#endif GUIMASTER_H