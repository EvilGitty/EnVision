#include "plotterWidget.h"
#include "Base/envision.h"

QVector<PlotGui::_settings> PlotGui::Record;

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
PlotterWidget::PlotterWidget(EnVision *main, QWidget *parent) : QMainWindow(parent), ui_plot(new Ui::EnVision_plotUI)
{
			ui_plot->setupUi(this);
			this->main = main;

			tab_x = 0;
	
			TabHandling *tabhand = new TabHandling(main);
			tabhand->guiAccess();

			QObject::connect(ui_plot->tabWidget_plotter, SIGNAL(currentChanged(int)), this, SLOT(getCurrentTabIndex(int)), Qt::UniqueConnection);
			QObject::connect(ui_plot->tabWidget_plotter, SIGNAL(tabBarClicked(int)), this, SLOT(activateTab(int)), Qt::UniqueConnection);
			QObject::connect(ui_plot->tabWidget_plotter->tabBar(), SIGNAL(tabMoved(int, int)), this, SLOT(moveTab(int, int)), Qt::UniqueConnection);
			QObject::connect(ui_plot->tabWidget_plotter, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)), Qt::UniqueConnection);

			QObject::connect(this, SIGNAL(activeTab_Signal(QWidget*, QObject*, QString, QVector<int>)), main->tabhand, SLOT(addWidget_plot(QWidget*, QObject*, QString, QVector<int>)), Qt::UniqueConnection);
			QObject::connect(this, SIGNAL(activeTab_Signal(QWidget*, QObject*, QString, QVector<int>)), main->tabhand, SLOT(closeWidget_plot(QWidget*, QObject*, QString, QVector<int>)), Qt::UniqueConnection);
			QObject::connect(this, SIGNAL(activeTab_Signal(QWidget*, QObject*, QString, QVector<int>)), main->tabhand, SLOT(moveWidget_plot(QWidget*, QObject*, QString, QVector<int>)), Qt::UniqueConnection);

			QObject::connect(this, SIGNAL(attachWidget_Signal(QWidget*, QString)), main, SLOT(attachWidget(QWidget*, QString)), Qt::UniqueConnection);

			QObject::connect(ui_plot->actionAttach, SIGNAL(triggered()), this, SLOT(attachWidget()));
			QObject::connect(ui_plot->actionDetach, SIGNAL(triggered()), this, SLOT(detachWidget()));

			QTabBar *t = qobject_cast<QTabBar*>(ui_plot->tabWidget_plotter->findChild<QTabBar *>());
			t->tabButton(0, QTabBar::RightSide)->hide();
			t->tabButton(1, QTabBar::RightSide)->hide();
			t->installEventFilter(this);

}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
PlotterWidget::~PlotterWidget()
{
}

//==============================================================================
// Ui::EnVision_baseUI* PlotterWidget::getPlotUI(void)
//------------------------------------------------------------------------------
//==============================================================================
Ui::EnVision_plotUI* PlotterWidget::getPlotUI(void)
{
	return ui_plot;
}

//==============================================================================
// int PlotterWidget::getCurrentTabIndex(int ind)
//------------------------------------------------------------------------------
//==============================================================================
int PlotterWidget::getCurrentTabIndex(int ind)
{
	return ui_plot->tabWidget_plotter->currentIndex();
}

//==============================================================================
// int PlotterWidget::missingTabIndex()
//------------------------------------------------------------------------------
// To calculate the next tab index
//==============================================================================
int PlotterWidget::missingTabIndex()
{
		int n = 0;
		// The sorted vector that contains the tab positions is 
		//searched for missing//deleted tabs - the resulting value
		//will be the next distinct "Object name" for the widget
		//to clearly identify it
		QVector<int> sort = TabHandling::orderTabs_Plot;
		qSort(sort);
		for (n; n < sort.size() ; n++) {
			//cout << sort[n] << endl;
			//return the missing number
			if ((sort[n] - sort[n - 1]) != 1){
				//cout << " n " << n << endl;
				return n;
			}
		}

	return n;
}

//==============================================================================
// QWidget* PlotterWidget::constructTab(void)
//------------------------------------------------------------------------------
//==============================================================================
QWidget* PlotterWidget::constructTab(void)
{
		tab_x = new QWidget(this);
		tab_x->setObjectName(QStringLiteral("tab_x"));
		QGridLayout* gridLayout = new QGridLayout(tab_x);
		gridLayout->setSpacing(6);
		gridLayout->setContentsMargins(11, 11, 11, 11);
		gridLayout->setObjectName(QStringLiteral("gridLayout"));

		ui_plot->mdiArea = new QMdiArea(tab_x);
		ui_plot->mdiArea->setObjectName(QStringLiteral("mdiArea"));
		ui_plot->mdiArea->setLineWidth(0);
		ui_plot->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		ui_plot->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		ui_plot->mdiArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
		QBrush brush(QColor(0, 0, 0, 255));
		brush.setStyle(Qt::SolidPattern);
		ui_plot->mdiArea->setBackground(brush);
		ui_plot->mdiArea->setViewMode(QMdiArea::SubWindowView);
		ui_plot->mdiArea->setDocumentMode(true);
		ui_plot->mdiArea->setTabsClosable(false);
		ui_plot->mdiArea->setTabShape(QTabWidget::Triangular);

		QWidget *subwindow = new QWidget();
		subwindow->setObjectName(QStringLiteral("subwindow"));
		QGridLayout*  gridLayout_4 = new QGridLayout(subwindow);
		gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));

		//the next tab number is calculated to build an object name
		main->tabhand->missingIndexTab_Plot = missingTabIndex();

		QCustomPlot *workspaceCustomPlot = new QCustomPlot(tab_x);

		//check if QCustomplot already (or still) exists
		QList<QCustomPlot *> list_plots1 = ui_plot->tabWidget_plotter->findChildren<QCustomPlot *>("plot" + QString::number(main->tabhand->missingIndexTab_Plot + 1));
		if (list_plots1.size() == 1){
			//cout << "debug " << main->tabhand->missingIndexTab_Image + 1 << " is already here :" << list_images1[0]->objectName().toStdString() << endl;

			//to prevent a dangling pointers, assign workspaceCustomPlot to ui_image, then delete the old reference
			ui_plot->plot = workspaceCustomPlot;
			delete list_plots1[0];
		}

		workspaceCustomPlot->setObjectName("plot" + QString::number(main->tabhand->missingIndexTab_Plot+1));

		workspaceCustomPlot->setMouseTracking(true);
		QGridLayout* gridLayout_3 = new QGridLayout(workspaceCustomPlot);
		gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));

		//tab_x->setAttribute(Qt::WA_DeleteOnClose);
		gridLayout_4->addWidget(workspaceCustomPlot, 0, 0, 1, 1);

		subwindow->setWindowTitle(QApplication::translate("EnVision_imageUI", "Subwindow", 0));
		ui_plot->mdiArea->addSubWindow(subwindow);

		gridLayout->addWidget(ui_plot->mdiArea, 0, 0, 1, 1);

		//make this the currently active widget
		ui_plot->tabWidget_plotter->setCurrentWidget(workspaceCustomPlot);
		main->Gui::tabRecord.currentPlot = workspaceCustomPlot;

		QList<QMdiSubWindow *> wnd = ui_plot->mdiArea->subWindowList();
		QList<QMdiSubWindow *>::iterator i;
		for (i = wnd.begin(); i != wnd.end(); ++i) {
			(*i)->setWindowFlags(Qt::Widget);
			(*i)->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		}

		ui_plot->mdiArea->tileSubWindows();
		
	return tab_x;
}

//==============================================================================
// void PlotterWidget::initElements(int newInd)
//------------------------------------------------------------------------------
//==============================================================================
void PlotterWidget::initElements(int newInd)
{
		//setup Design
		ui_plot->plot->xAxis->setLabelColor("black");
		ui_plot->plot->xAxis->setBasePen(QPen(Qt::black, 1));
		ui_plot->plot->yAxis->setBasePen(QPen(Qt::black, 1));
		ui_plot->plot->xAxis->setTickPen(QPen(Qt::black, 1));
		ui_plot->plot->yAxis->setTickPen(QPen(Qt::black, 1));
		ui_plot->plot->xAxis->setSubTickPen(QPen(Qt::black, 1));
		ui_plot->plot->yAxis->setSubTickPen(QPen(Qt::black, 1));
		ui_plot->plot->xAxis->setTickLabelColor(Qt::black);
		ui_plot->plot->yAxis->setTickLabelColor(Qt::black);
		ui_plot->plot->xAxis->grid()->setPen(QPen(QColor(50, 50, 50), 1, Qt::DotLine));
		ui_plot->plot->yAxis->grid()->setPen(QPen(QColor(50, 50, 50), 1, Qt::DotLine));
		ui_plot->plot->xAxis->grid()->setSubGridPen(QPen(QColor(200, 200, 200), 1, Qt::DotLine));
		ui_plot->plot->yAxis->grid()->setSubGridPen(QPen(QColor(200, 200, 200), 1, Qt::DotLine));
		ui_plot->plot->xAxis->grid()->setSubGridVisible(true);
		ui_plot->plot->yAxis->grid()->setSubGridVisible(true);
		ui_plot->plot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
		ui_plot->plot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
		ui_plot->plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
		ui_plot->plot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

		QLinearGradient plotGradientSpectral;
		plotGradientSpectral.setStart(0, 0);
		plotGradientSpectral.setFinalStop(0, 350);
		plotGradientSpectral.setColorAt(0, QColor(255, 255, 255));
		plotGradientSpectral.setColorAt(1, QColor(255, 255, 255));
		ui_plot->plot->setBackground(plotGradientSpectral);
		QLinearGradient axisRectGradientSpectral;
		axisRectGradientSpectral.setStart(0, 0);
		axisRectGradientSpectral.setFinalStop(0, 350);
		axisRectGradientSpectral.setColorAt(0, QColor(255, 255, 255));
		axisRectGradientSpectral.setColorAt(1, QColor(255, 255, 255));
		ui_plot->plot->axisRect()->setBackground(axisRectGradientSpectral);


	return;
}

//==============================================================================
// void PlotterWidget::resetTab(int index)
//------------------------------------------------------------------------------
//==============================================================================
void PlotterWidget::resetTab(int index)
{
	return;
}


//==============================================================================
// void PlotterWidget::setTab(int newInd, int lastInd)
//------------------------------------------------------------------------------
//==============================================================================
void PlotterWidget::setTab(int newInd, int lastInd)
{
		//get pointer to the QCustomPlot related to the current tab widget
		QList<QCustomPlot *> list_plots1 = ui_plot->tabWidget_plotter->findChildren<QCustomPlot *>("plot" + QString::number(newInd + 1));
		if (list_plots1.size() != 1){
			return;
		}

		//set new plot
		main->Gui::tabRecord.currentPlot = list_plots1[0];
		ui_plot->plot = list_plots1[0];
	return;
}

//==============================================================================
// void PlotterWidget::activateTab(int index)
//------------------------------------------------------------------------------
//==============================================================================
void PlotterWidget::activateTab(int index)
{
		if (index > -1){
			tab_x = ui_plot->tabWidget_plotter->widget(index);

			if (index == (ui_plot->tabWidget_plotter->count() - 1)){
				tab_x = constructTab();
				initElements(index);
			}

			QVector<int> i;
			i.push_back(index);

			emit activeTab_Signal(tab_x, ui_plot->tabWidget_plotter, "add", i);

			setTab(TabHandling::orderTabs_Plot[index] - 1, TabHandling::orderTabs_Plot[TabHandling::lastIndexTab_Plot] - 1);

			//TabOrder stores tabs beginning with numeber 1 while the lowest tab
			//index returned by Qt is 0 for a valid widget
			//index = TabHandling::orderTabs_Plot[index];

			//get pointer to the QCustomPlot related to the current tab widget
			//QList<QCustomPlot *> list_plots1 = ui_plot->tabWidget_plotter->findChildren<QCustomPlot *>("plot" + QString::number(index));
			//main->Gui::tabRecord.currentPlot = list_plots1[0];
			//main->Gui::tabRecord.plotIndex = index - 1;

			/*
			int g = 0;
			while(g < TabHandling::orderTabs_Plot.size())
			{

			QList<QCustomPlot *> list_plots1 = ui_plot->tabWidget_plotter->findChildren<QCustomPlot *>("plot" + QString::number(TabHandling::orderTabs_Plot[g] ));
			//cout << list_plots1.size() << endl;
			cout << "g: " << g + 1 << " tab:" << TabHandling::orderTabs_Plot[g] << " " << list_plots1[0]->objectName().toStdString() << endl;
			g++;
			}
			cout << " --------------" << endl;
			*/

		}
	return;
}

//==============================================================================
// void PlotterWidget::closeTab(int index)
//------------------------------------------------------------------------------
//==============================================================================
void PlotterWidget::closeTab(int index)
{
		QVector<int> i;
		i.push_back(index);

		emit activeTab_Signal(NULL, ui_plot->tabWidget_plotter, "close", i);

		setTab(TabHandling::orderTabs_Plot[index] - 1, TabHandling::orderTabs_Plot[TabHandling::lastIndexTab_Plot] - 1);
	return;
}

//==============================================================================
// void PlotterWidget::moveTab(int to, int from)
//------------------------------------------------------------------------------
//==============================================================================
void PlotterWidget::moveTab(int to, int from)
{
		QVector<int> i;
		i.push_back(to);
		i.push_back(from);
		i.push_back(to);

		emit activeTab_Signal(NULL, ui_plot->tabWidget_plotter, "move", i);


		setTab(TabHandling::orderTabs_Plot[to] - 1, TabHandling::orderTabs_Plot[TabHandling::lastIndexTab_Plot] - 1);
	return;
}

//==============================================================================
// void PlotterWidget::attachWidget()
//------------------------------------------------------------------------------
//==============================================================================
void PlotterWidget::attachWidget()
{
		emit attachWidget_Signal(this, "Plotter");
	return;
}

//==============================================================================
// void PlotterWidget::detachWidget()
//------------------------------------------------------------------------------
//==============================================================================
void PlotterWidget::detachWidget()
{
		main->detachWidget();
	return;
}

//==============================================================================
// bool PlotterWidget::eventFilter(QObject *o, QEvent *e)
//------------------------------------------------------------------------------
//==============================================================================
bool PlotterWidget::eventFilter(QObject *o, QEvent *e)
{
		//this is just blocking an annoying wheel event on the tabbar
		//that causes a switching of tabs
		if (e->type() == QEvent::Wheel){
			//qDebug() << "Wheel event blocked";
			return true;
		}
	return 0;
}
