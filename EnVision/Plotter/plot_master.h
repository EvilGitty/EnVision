#ifndef PLOTMASTER_H
#define PLOTMASTER_H

#include <iostream>

#include <QString>
#include <QDirIterator>
#include <QAction>
#include <QMessageBox>
#include "qcustomplot.h" 

//-----------------------------------
// SpecIL
#include "SpecIL_Interface.h"

//-----------------------------------
// QpenCV
#include <opencv2/core/core.hpp>       
#include <opencv2/highgui/highgui.hpp>  
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>  
//-----------------------------------

using namespace std;
using namespace cv;

class PlotAttribute
{
public:

	//------------------------------------------------------------------------------
	struct _plot{

	} record;
	static QVector<_plot> Record;

	void addVector()
	{
		Record.push_back(record);
		return;
	}

	void removeVector(int index)
	{
		Record.remove(index);
		return;
	}
};


#endif //PLOTMASTER_H

