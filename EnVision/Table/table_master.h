#ifndef TABLEMASTER_H
#define TABLEMASTER_H

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

class TableAttribute
{
public:

	//------------------------------------------------------------------------------
	struct _table{

	} record;
	static QVector<_table> Record;

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


#endif //TABLEMASTER_H

