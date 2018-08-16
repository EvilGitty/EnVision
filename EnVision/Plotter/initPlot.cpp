#include "initPlot.h"
#include "Base/envision.h"

QVector<PlotAttribute::_plot> PlotAttribute::Record;

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
Plot::Plot(EnVision *main)
{
		this->main = main;

		watcher = 0;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
Plot::~Plot()
{


}

//==============================================================================
// void Plot::guiAccess()
//------------------------------------------------------------------------------
//==============================================================================
void Plot::guiAccess()
{
		this->ui_base = main->getBaseUI();
		this->ui_plot = main->getPlotUI();
		this->ui_image = main->getImageUI();
		
	return;
}

//==============================================================================
// void Plot::resetZoom()
//------------------------------------------------------------------------------
//==============================================================================
void Plot::resetZoom()
{
		//reset qcustomplot range
	//set all axes and define range
		ui_plot->hScrollBar->setRange((-150) * (int)_channels, (15) * (int)_channels);
		ui_plot->vScrollBar->setRange((-10) * (int)_maxDataVal, (15) * (int)_maxDataVal);
		ui_plot->plot->xAxis->setRange(0, (double)_channels);
		ui_plot->plot->yAxis->setRange(0, (double)_maxDataVal);
	return;
}

//==============================================================================
// void Plot::init()
//------------------------------------------------------------------------------
//==============================================================================
void Plot::init()
{
		//get access to other guis
		guiAccess();

		ui_plot->mdiArea->currentSubWindow()->setWindowTitle(QString::fromStdString(_filename));

		//now that the first image is succesfully loaded, proceed with installing all necessary connections
		ui_plot->plot->installEventFilter(this);
		ui_plot->plot->installEventFilter(ui_image->image);
		ui_plot->plot->setAcceptDrops(ui_image->image);

		QObject::connect(ui_plot->plot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel(QWheelEvent*)), Qt::UniqueConnection);
		QObject::connect(ui_plot->hScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)), Qt::UniqueConnection);
		QObject::connect(ui_plot->vScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)), Qt::UniqueConnection);
		QObject::connect(ui_plot->plot->xAxis, SIGNAL(rangeChanged(QCPRange, QCPRange)), this, SLOT(xAxisChanged(QCPRange, QCPRange)), Qt::UniqueConnection);
		QObject::connect(ui_plot->plot->yAxis, SIGNAL(rangeChanged(QCPRange, QCPRange)), this, SLOT(yAxisChanged(QCPRange, QCPRange)), Qt::UniqueConnection);
		QObject::connect(ui_plot->pushButton_resetZoom, SIGNAL(clicked()), this, SLOT(resetZoom()), Qt::UniqueConnection);
		//X-Axis
		QObject::connect(ui_plot->radioButtonX01, SIGNAL(clicked()), this, SLOT(displayPlot()), Qt::UniqueConnection);
		QObject::connect(ui_plot->radioButtonX02, SIGNAL(clicked()), this, SLOT(displayPlot()), Qt::UniqueConnection);

		//Y-Axis
		QObject::connect(ui_plot->radioButtonY01, SIGNAL(clicked()), this, SLOT(displayPlot()), Qt::UniqueConnection);
		QObject::connect(ui_plot->radioButtonY02, SIGNAL(clicked()), this, SLOT(displayPlot()), Qt::UniqueConnection);

		displayPlot();

	return;
}

//==============================================================================
// void Plot::displayPlot()
//------------------------------------------------------------------------------
//==============================================================================
void Plot::displayPlot()
{
		//set all axes and define range
		resetZoom();
		ui_plot->radioButtonY02->setText("[0," + QString::number(_maxDataVal) + "]");
		ui_plot->plot->setInteractions(QCP::iSelectPlottables | QCP::iSelectLegend | QCP::iRangeDrag | QCP::iRangeZoom);
		xAxis(ui_plot->buttonGroup_scaleXaxis->checkedButton()->text(), _channels);
		yAxis(ui_plot->buttonGroup_scaleYaxis->checkedButton()->text(), _channels);


	return;
}

//==============================================================================
// void Image::finished()
//------------------------------------------------------------------------------
//==============================================================================
void Plot::finished()
{
		//cout << " finished " << endl;
		
		ui_image->image->viewport()->update();
		if ((watcher != 0)){
			if (watcher->isRunning()){
			//	watcher->cancel();
				watcher->waitForFinished();
				delete data;
			}
		}

		ui_plot->plot->replot();
	
	return;
}

//==============================================================================
// int Plot::plotPixel()
//------------------------------------------------------------------------------
//==============================================================================
int Plot::plotPixel()
{
		/*
		QThread *thread = new QThread();
		watcher = new QFutureWatcher<int>();
		data = new PixelareaThread(main, this);
		QObject::connect(data, &PixelareaThread::finished, thread, &QObject::deleteLater, Qt::UniqueConnection);
		QObject::connect(data, &PixelareaThread::finished, data, &QObject::deleteLater, Qt::UniqueConnection);
		QObject::connect(watcher, SIGNAL(finished()), this, SLOT(finished()), Qt::UniqueConnection);
		watcher->setFuture(QtConcurrent::run(data, &PixelareaThread::loadSinglePixel,
			int(_imgIndex), QVector<double>(xVector), QVector<ImageAttribute::_image::pixel_coordinates>( ImageAttribute::Record[_imgIndex].pixel_list)));
		*/
	return 0;
}


//==============================================================================
// void Plot::updatePlot(int x, int y, QString str)
//------------------------------------------------------------------------------
//==============================================================================
void Plot::updatePlot(const QVector<double> xVector, const QVector<double> yVector, const int x, const int y, const QString str, const int listsize, const int listindex)
{

	QVector<QCPGraphData>;

	ui_plot->plot->setNoAntialiasingOnDrag(true);
		//-------------------------------------
		// Preview methods
		if (str.compare("showSingle Point") == 0) {
			ui_plot->plot->removeGraph(ui_plot->plot->graphCount() - 1);
			ui_plot->plot->addGraph();
			ui_plot->plot->graph(ui_plot->plot->graphCount() - 1)->setPen(QPen(Qt::GlobalColor(7)));
			ui_plot->plot->graph()->setData(xVector, yVector, true);
		}

		if (str.compare("showRectangle") == 0) {

			if (ui_plot->plot->graphCount() < (listsize)){
				ui_plot->plot->addGraph();
			//	cout << " ! " << listindex << " " << listsize <<endl;
				ui_plot->plot->graph(listindex)->setPen(QPen(Qt::GlobalColor(7)));
				ui_plot->plot->graph(listindex)->setData(xVector, yVector, true);
			}else{
				ui_plot->plot->removeGraph(ui_plot->plot->graphCount() - (listsize-1));
			}
		}

		if (str.compare("showEllipse") == 0) {
			ui_plot->plot->addGraph();
			ui_plot->plot->graph(ui_plot->plot->graphCount() - 1)->setPen(QPen(Qt::GlobalColor(7)));
			ui_plot->plot->graph()->setData(xVector, yVector, true);
		}

		if (str.compare("showPolygon") == 0) {
			ui_plot->plot->addGraph();
			ui_plot->plot->graph(ui_plot->plot->graphCount() - 2)->setPen(QPen(7));
			ui_plot->plot->graph()->setData(xVector, yVector, true);
		}

		if (str.compare("showXProfile") == 0) {
			ui_plot->plot->removeGraph(ui_plot->plot->graphCount() - 1);
			ui_plot->plot->addGraph();
			ui_plot->plot->graph(ui_plot->plot->graphCount() - 1)->setPen(QPen(Qt::GlobalColor(7)));
			ui_plot->plot->graph()->setData(xVector, yVector, true);
		}

		if (str.compare("showYProfile") == 0) {
			ui_plot->plot->removeGraph(ui_plot->plot->graphCount() - 1);
			ui_plot->plot->addGraph();
			ui_plot->plot->graph(ui_plot->plot->graphCount() - 1)->setPen(QPen(Qt::GlobalColor(7)));
			ui_plot->plot->graph()->setData(xVectorVertProfile, yVectorVertProfile, true);
		}

		//-------------------------------------
		// Drawing methods
		if (str.compare("drawSingle Point") == 0) {
			ui_plot->plot->addGraph();
			ui_plot->plot->graph(ui_plot->plot->graphCount() - 2)->setPen(QPen(7));
			ui_plot->plot->graph()->setData(xVector, yVector, true);
		}

		if (str.compare("drawRectangle") == 0) {
			ui_plot->plot->addGraph();
			ui_plot->plot->graph(ui_plot->plot->graphCount() - 2)->setPen(QPen(7));
			ui_plot->plot->graph()->setData(xVector, yVector, true);
		}

		if (str.compare("drawCircle") == 0) {
			ui_plot->plot->addGraph();
			ui_plot->plot->graph(ui_plot->plot->graphCount() - 2)->setPen(QPen(7));
			ui_plot->plot->graph()->setData(xVector, yVector, true);
		}

		if (str.compare("drawPolygon") == 0) {
			ui_plot->plot->addGraph();
			ui_plot->plot->graph(ui_plot->plot->graphCount() - 2)->setPen(QPen(7));
			ui_plot->plot->graph()->setData(xVector, yVector, true);
		}

		if (str.compare("drawXProfile") == 0) {
			ui_plot->plot->addGraph();
			ui_plot->plot->graph(ui_plot->plot->graphCount() - 2)->setPen(QPen(7));
			ui_plot->plot->graph()->setData(xVector, yVector, true);
		}

		if (str.compare("drawYProfile") == 0) {
			ui_plot->plot->addGraph();
			ui_plot->plot->graph(ui_plot->plot->graphCount() - 2)->setPen(QPen(7));
			ui_plot->plot->graph()->setData(xVector, yVector, true);
		}

	return;
}

//==============================================================================
// int Image::getData(int imgIndex, void* buffer, std::string geometry, long *dimPlane, long *dimVector, long *dimPoint)
//------------------------------------------------------------------------------
//==============================================================================
int Plot::getData(int imgIndex, void* buffer, std::string geometry, long *dimPlane, long *dimVector, long *dimPoint)
{
	int imgNumber = ImageAttribute::Record[imgIndex].imgNumber;
	int subimgNumber = ImageAttribute::Record[imgIndex].subimgNumber;

	if (geometry.compare("Plane") == 0) {
		int x[2] = { static_cast<int>(*(dimPlane)), static_cast<int>(*(dimPlane + 1) - 1) };		//-1 at the end because the dimensions start at 0
		int y[2] = { static_cast<int>(*(dimPlane + 2)), static_cast<int>(*(dimPlane + 3) - 1) };	//-1 at the end because the dimensions start at 0
		int z[2] = { static_cast<int>(*(dimPlane + 4)), static_cast<int>(*(dimPlane + 5)) };		//*(dimPlane + 5) is -1 for channel-specific visualization 

		switch (imgNumber) {
		case 1: //tapsansi (*.tgd)
			switch (subimgNumber) {
			case 10: //tgd::hyspex SWIR320
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
				break;
			case 11: //tgd::hyspex SWIR384	
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
				break;
			case 12: //tgd::hyspex VNIR1600	
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
				break;
			case 13: //tgd::hyspex VNIR1800	
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
				break;
			case 14: //tgd::hyspex Mjolnir	
				//no testdata yet
				break;
			case 15://tgd::copter David
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
				break;
			case 16: //tgd::nuance
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
				break;
			case 17: //tgd::kinect I
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, z, y);
				break;
			case 18: //tgd::kinect II
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, z, y);
				break;
			}
			break;
		case 2: //uncalibrated hyspex (*.hyspex)
			switch (subimgNumber) {
			case 20: //SWIR320me	
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
				break;
			case 21: //SWIR384
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
				break;
			case 22: //VNIR1600
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
				break;
			case 23: //VNIR1800
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
				break;
			case 24://UVA_Mjolnir
				//no testdata yet
				break;
			}
			break;
		case 3: //calibrated hyspex (*.img)
			switch (subimgNumber) {
			case 30: //SWIR320me
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
				break;
			case 31: //SWIR384
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
				break;
			case 32: //VNIR1600
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
				break;
			case 33: //VNIR1800
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
				break;
			case 34: //UVA_Mjolnir
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
				break;
			}
			break;
		case 4:
			switch (subimgNumber) {
			case 40: //mat 5.3
				//?
				break;
			case 41: //mat 7.3
				//?
				break;
			case 42: //mat 7.4
				//?
				break;
			}
			break;
		case 5:
			switch (subimgNumber) {
			case 50: //Nuance
				ImageAttribute::Record[imgIndex].SpecData->getPlane(buffer, x, y, z);
				break;
			}
			break;
		}
		return 1;
	}


	return 1;
}