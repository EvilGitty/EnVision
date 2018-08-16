#include "imageWidget.h"
#include "Base/envision.h"

QVector<ImageGui::_settings> ImageGui::Record;

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
ImageWidget::ImageWidget(EnVision *main, QWidget *parent) : QMainWindow(parent), ui_image(new Ui::EnVision_imageUI)
{
			ui_image->setupUi(this);
			this->main = main;

			tab_x = 0;

			TabHandling *tabhand = new TabHandling(main);
			tabhand->guiAccess();

			QObject::connect(ui_image->tabWidget_image, SIGNAL(currentChanged(int)), this, SLOT(getCurrentTabIndex(int)), Qt::UniqueConnection);
			QObject::connect(ui_image->tabWidget_image, SIGNAL(tabBarClicked(int)), this, SLOT(activateTab(int)), Qt::UniqueConnection);
			QObject::connect(ui_image->tabWidget_image->tabBar(), SIGNAL(tabMoved(int, int)), this, SLOT(moveTab(int, int)), Qt::UniqueConnection);
			QObject::connect(ui_image->tabWidget_image, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)), Qt::UniqueConnection);

			QObject::connect(this, SIGNAL(activeTab_Signal(QWidget*, QObject*, QString, QVector<int>)), main->tabhand, SLOT(addWidget_image(QWidget*, QObject*, QString, QVector<int>)), Qt::UniqueConnection);
			QObject::connect(this, SIGNAL(activeTab_Signal(QWidget*, QObject*, QString, QVector<int>)), main->tabhand, SLOT(closeWidget_image(QWidget*, QObject*, QString, QVector<int>)), Qt::UniqueConnection);
			QObject::connect(this, SIGNAL(activeTab_Signal(QWidget*, QObject*, QString, QVector<int>)), main->tabhand, SLOT(moveWidget_image(QWidget*, QObject*, QString, QVector<int>)), Qt::UniqueConnection);

			QObject::connect(this, SIGNAL(attachWidget_Signal(QWidget*, QString)), main, SLOT(attachWidget(QWidget*, QString)), Qt::UniqueConnection);

			QObject::connect(ui_image->actionAttach, SIGNAL(triggered()), this, SLOT(attachWidget()));
			QObject::connect(ui_image->actionDetach, SIGNAL(triggered()), this, SLOT(detachWidget()));

			QTabBar *t = qobject_cast<QTabBar*>(ui_image->tabWidget_image->findChild<QTabBar *>());
			t->tabButton(0, QTabBar::RightSide)->hide();
			t->tabButton(1, QTabBar::RightSide)->hide();
			t->installEventFilter(this);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
ImageWidget::~ImageWidget()
{

}

//==============================================================================
// Ui::EnVision_imageUI* ImageWidget::getBaseUI(void)
//------------------------------------------------------------------------------
//==============================================================================
Ui::EnVision_imageUI* ImageWidget::getImageUI(void)
{
	return ui_image;
}

//==============================================================================
// int ImageWidget::getCurrentTabIndex(int ind)
//------------------------------------------------------------------------------
//==============================================================================
int ImageWidget::getCurrentTabIndex(int ind)
{
	return ui_image->tabWidget_image->currentIndex();
}

//==============================================================================
// int ImageWidget::missingTabIndex()
//------------------------------------------------------------------------------
// To calculate the next tab index
//==============================================================================
int ImageWidget::missingTabIndex()
{
		int n = 0;
		// The sorted vector that contains the tab positions is 
		//searched for missing//deleted tabs - the resulting value
		//will be the next distinct "Object name" for the widget
		//to clearly identify it
		QVector<int> sort = TabHandling::orderTabs_Image;
		qSort(sort);
		for (n; n < sort.size(); n++) {
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
// QWidget* ImageWidget::constructTab(void)
//------------------------------------------------------------------------------
//==============================================================================
QWidget* ImageWidget::constructTab(void)
{
		/*
		tab_x = new QWidget();
		tab_x->setObjectName(QStringLiteral("tab_x"));

		QGridLayout* gridLayout_2 = new QGridLayout(tab_x);
		gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));

		ui_image->mdiArea = new QMdiArea(tab_x);
		ui_image->mdiArea->setObjectName(QStringLiteral("mdiArea"));
		ui_image->mdiArea->setLineWidth(0);
		ui_image->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		ui_image->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		ui_image->mdiArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
		QBrush brush(QColor(0, 0, 0, 255));
		brush.setStyle(Qt::SolidPattern);
		ui_image->mdiArea->setBackground(brush);
		ui_image->mdiArea->setViewMode(QMdiArea::SubWindowView);
		ui_image->mdiArea->setDocumentMode(true);
		ui_image->mdiArea->setTabsClosable(false);
		ui_image->mdiArea->setTabShape(QTabWidget::Triangular);

		QWidget *subwindow = new QWidget();
		subwindow->setObjectName(QStringLiteral("subwindow"));
		QGridLayout*  gridLayout_4 = new QGridLayout(subwindow);
		gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));

		//the next tab number is calculated to build an object name
		main->tabhand->missingIndexTab_Image = missingTabIndex();


		QCustomPlot *workspace = new QCustomPlot(subwindow);
		workspace->setObjectName("img" + QString::number(main->tabhand->missingIndexTab_Image + 1));
		workspace->setMinimumSize(QSize(50, 50));
		QGridLayout* gridLayout_6 = new QGridLayout(workspace);
		gridLayout_6->setSpacing(0);
		gridLayout_6->setObjectName(QStringLiteral("gridLayout_3"));
		gridLayout_6->setContentsMargins(16, 0, 0, 16);


		//check if QCustomplot already (or still) exists
		QList<QCustomPlot *> list_images1 = ui_image->tabWidget_image->findChildren<QCustomPlot *>("img" + QString::number(main->tabhand->missingIndexTab_Image + 1));
		if (list_images1.size() == 1){
			//cout << "debug " << main->tabhand->missingIndexTab_Image + 1 << " is already here :" << list_images1[0]->objectName().toStdString() << endl;
			//to prevent a dangling pointers, assign workspaceCustomPlot to ui_image, then delete the old reference
			ui_image->workspace = workspace;
			delete list_images1[0];
		}

		QGraphicsView *graphicsView = new QGraphicsView(workspace);
		//graphicsView->setObjectName("img" + QString::number(main->tabhand->missingIndexTab_Image + 1));

		QFont font;
		font.setStyleStrategy(QFont::PreferAntialias);
		graphicsView->setFont(font);
		graphicsView->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
		graphicsView->setMouseTracking(true);
		graphicsView->setFrameShape(QFrame::NoFrame);
		graphicsView->setFrameShadow(QFrame::Plain);
		graphicsView->setLineWidth(0);
		graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
		graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
		graphicsView->setCacheMode(QGraphicsView::CacheBackground);
		graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
		graphicsView->setRubberBandSelectionMode(Qt::ContainsItemBoundingRect);
		graphicsView->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing | QGraphicsView::DontClipPainter | QGraphicsView::DontSavePainterState);

		QGridLayout* gridLayout_3 = new QGridLayout(graphicsView);
		gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));

		gridLayout_4->addWidget(graphicsView, 0, 0, 1, 1);

		subwindow->setWindowTitle(QApplication::translate("EnVision_imageUI", "Subwindow", 0));
		ui_image->mdiArea->addSubWindow(subwindow);

		gridLayout_2->addWidget(ui_image->mdiArea, 0, 0, 1, 1);

		ui_image->tabWidget_image->setCurrentWidget(graphicsView);
		main->Gui::tabRecord.currentImage = graphicsView;

		QList<QMdiSubWindow *> wnd = ui_image->mdiArea->subWindowList();
		QList<QMdiSubWindow *>::iterator i;
		for (i = wnd.begin(); i != wnd.end(); ++i) {
			(*i)->setWindowFlags(Qt::Widget);
			(*i)->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		}

		ui_image->mdiArea->tileSubWindows();
		*/
		/////
	/*
		tab_x = new QWidget();
		tab_x->setObjectName(QStringLiteral("tab_x"));

		QGridLayout* gridLayout_2 = new QGridLayout(tab_x);
		gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));

		ui_image->mdiArea = new QMdiArea(tab_x);
		ui_image->mdiArea->setObjectName(QStringLiteral("mdiArea"));
		ui_image->mdiArea->setLineWidth(0);
		ui_image->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		ui_image->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		ui_image->mdiArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
		QBrush brush(QColor(0, 0, 0, 255));
		brush.setStyle(Qt::SolidPattern);
		ui_image->mdiArea->setBackground(brush);
		ui_image->mdiArea->setViewMode(QMdiArea::SubWindowView);
		ui_image->mdiArea->setDocumentMode(true);
		ui_image->mdiArea->setTabsClosable(false);
		ui_image->mdiArea->setTabShape(QTabWidget::Triangular);

		QWidget *subwindow = new QWidget();
		subwindow->setObjectName(QStringLiteral("subwindow"));
		QGridLayout*  gridLayout_4 = new QGridLayout(subwindow);
		gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));

		//the next tab number is calculated to build an object name
		main->tabhand->missingIndexTab_Image = missingTabIndex();

		QCustomPlot *imageplot = new QCustomPlot(subwindow);

		//check if QCustomplot already (or still) exists
		QList<QCustomPlot *> list_images1 = ui_image->tabWidget_image->findChildren<QCustomPlot *>("imgplot1" + QString::number(main->tabhand->missingIndexTab_Image + 1));
		if (list_images1.size() == 1){
			//cout << "debug " << main->tabhand->missingIndexTab_Image + 1 << " is already here :" << list_images1[0]->objectName().toStdString() << endl;

			//to prevent a dangling pointers, assign workspaceCustomPlot to ui_image, then delete the old reference
			ui_image->imageplot = imageplot;
			//delete list_images1[0];
		}

		imageplot->setObjectName("imgplot1" + QString::number(main->tabhand->missingIndexTab_Image + 1));

		QGridLayout* gridLayout_3 = new QGridLayout(imageplot);
		gridLayout_3->setSpacing(0);
		gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
		gridLayout_3->setContentsMargins(16, 0, 0, 16);
		
		QGraphicsView* image = new QGraphicsView(imageplot);
		QFont font;
		font.setStyleStrategy(QFont::PreferAntialias);
		image->setFont(font);
		image->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
		image->setMouseTracking(true);
		image->setFrameShape(QFrame::NoFrame);
		image->setFrameShadow(QFrame::Plain);
		image->setLineWidth(0);
		image->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
		image->setDragMode(QGraphicsView::ScrollHandDrag);
		image->setCacheMode(QGraphicsView::CacheBackground);
		image->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
		image->setRubberBandSelectionMode(Qt::ContainsItemBoundingRect);
		image->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing | QGraphicsView::DontSavePainterState);


		//check if QCustomplot already (or still) exists
		QList<QGraphicsView *> list_images2 = ui_image->tabWidget_image->findChildren<QGraphicsView *>("img" + QString::number(main->tabhand->missingIndexTab_Image + 1));
		if (list_images2.size() == 1){
			//cout << "debug " << main->tabhand->missingIndexTab_Image + 1 << " is already here :" << list_images1[0]->objectName().toStdString() << endl;
			//to prevent a dangling pointers, assign workspaceCustomPlot to ui_image, then delete the old reference
			ui_image->image = image;
			//delete list_images2[0];
		}

		image->setObjectName("img" + QString::number(main->tabhand->missingIndexTab_Image + 1));

		gridLayout_4->addWidget(imageplot, 0, 0, 1, 1);
		gridLayout_3->addWidget(image, 0, 0, 1, 1);

		subwindow->setWindowTitle(QApplication::translate("EnVision_imageUI", "Subwindow", 0));
		ui_image->mdiArea->addSubWindow(subwindow);

		gridLayout_2->addWidget(ui_image->mdiArea, 0, 0, 1, 1);

		ui_image->tabWidget_image->setCurrentWidget(imageplot);
		main->Gui::tabRecord.currentImageplot = imageplot;
		main->Gui::tabRecord.currentImage = image;

		QList<QMdiSubWindow *> wnd = ui_image->mdiArea->subWindowList();
		QList<QMdiSubWindow *>::iterator i;
		for (i = wnd.begin(); i != wnd.end(); ++i) {
			(*i)->setWindowFlags(Qt::Widget);
			(*i)->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		}

		ui_image->mdiArea->tileSubWindows();
		*/
		//////


		main->tabhand->missingIndexTab_Image = missingTabIndex();

		tab_x = new QWidget();
		tab_x->setObjectName(QStringLiteral("tab_x"));

		QGridLayout* gridLayout_2 = new QGridLayout(tab_x);
		gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
		ui_image->mdiArea = new QMdiArea(tab_x);
		ui_image->mdiArea->setObjectName(QStringLiteral("mdiArea"));
		ui_image->mdiArea->setLineWidth(0);
		ui_image->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		ui_image->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		ui_image->mdiArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
		QBrush brush(QColor(0, 0, 0, 255));
		brush.setStyle(Qt::SolidPattern);
		ui_image->mdiArea->setBackground(brush);
		ui_image->mdiArea->setViewMode(QMdiArea::SubWindowView);
		ui_image->mdiArea->setDocumentMode(true);
		ui_image->mdiArea->setTabsClosable(false);
		ui_image->mdiArea->setTabShape(QTabWidget::Triangular);

		QWidget *subwindow = new QWidget();
		subwindow = new QWidget();
		subwindow->setObjectName(QStringLiteral("subwindow"));
		QGridLayout* gridLayout_4 = new QGridLayout(subwindow);
		gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));

		QCustomPlot *imageplot = new QCustomPlot(subwindow);
		imageplot = new QCustomPlot(subwindow);
		imageplot->setMinimumSize(QSize(50, 50));
		QGridLayout* gridLayout_3 = new QGridLayout(imageplot);
		gridLayout_3->setSpacing(0);
		gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
		gridLayout_3->setContentsMargins(16, 0, 0, 16);

		//check if QCustomplot already (or still) exists
		QList<QCustomPlot *> list_images1 = ui_image->tabWidget_image->findChildren<QCustomPlot *>("imgplot" + QString::number(main->tabhand->missingIndexTab_Image + 1));
		if (list_images1.size() == 1){
			//cout << "debug " << main->tabhand->missingIndexTab_Image + 1 << " is already here :" << list_images1[0]->objectName().toStdString() << endl;

			//to prevent a dangling pointers, assign workspaceCustomPlot to ui_image, then delete the old reference
			ui_image->imageplot = imageplot;
			delete list_images1[0];
		}

		imageplot->setObjectName("imgplot" + QString::number(main->tabhand->missingIndexTab_Image + 1));
		

		QGraphicsView* image = new QGraphicsView(imageplot);
		QFont font;
		font.setStyleStrategy(QFont::PreferAntialias);
		image->setFont(font);
		image->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
		image->setMouseTracking(true);
		image->setFrameShape(QFrame::NoFrame);
		image->setFrameShadow(QFrame::Plain);
		image->setLineWidth(0);
		image->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
		image->setDragMode(QGraphicsView::ScrollHandDrag);
		image->setCacheMode(QGraphicsView::CacheBackground);
		image->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
		image->setRubberBandSelectionMode(Qt::ContainsItemBoundingRect);
		image->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing | QGraphicsView::DontSavePainterState);

		QList<QGraphicsView *> list_images2 = ui_image->tabWidget_image->findChildren<QGraphicsView *>("img" + QString::number(main->tabhand->missingIndexTab_Image + 1));
		if (list_images2.size() == 1){
			//cout << "debug " << main->tabhand->missingIndexTab_Image + 1 << " is already here :" << list_images1[0]->objectName().toStdString() << endl;
			//to prevent a dangling pointers, assign workspaceCustomPlot to ui_image, then delete the old reference
			ui_image->image = image;
			delete list_images2[0];
		}

		image->setObjectName("img" + QString::number(main->tabhand->missingIndexTab_Image + 1));

		gridLayout_3->addWidget(image, 0, 0, 1, 1);

		gridLayout_4->addWidget(imageplot, 0, 0, 1, 1);

		ui_image->mdiArea->addSubWindow(subwindow);

		gridLayout_2->addWidget(ui_image->mdiArea, 0, 0, 1, 1);

		ui_image->tabWidget_image->setCurrentWidget(image);
		//main->Gui::tabRecord.currentImageplot = imageplot;
		main->Gui::tabRecord.currentImage = image;

		QList<QMdiSubWindow *> wnd = ui_image->mdiArea->subWindowList();
		QList<QMdiSubWindow *>::iterator i;
		for (i = wnd.begin(); i != wnd.end(); ++i) {
			(*i)->setWindowFlags(Qt::Widget);
			(*i)->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		}

		ui_image->mdiArea->tileSubWindows();
	
	return tab_x;
}

//==============================================================================
// void ImageWidget::initElements(int newInd)
//------------------------------------------------------------------------------
//==============================================================================
void ImageWidget::initElements(int newInd)
{
		//==============================================================================
		// combobox ImageColormap
		//------------------------------------------------------------------------------
		QStandardItemModel *model0 = dynamic_cast< QStandardItemModel * >(ui_image->comboBox_ImageColormap->model());
		int itemIndex0 = 0;
		QStringListIterator javaStyleIterator0(main->ImageGui::record.imgColormap.strings);
		ui_image->comboBox_ImageColormap->setDuplicatesEnabled(false);
		ui_image->comboBox_ImageColormap->clear();
		while (javaStyleIterator0.hasNext()){
			ui_image->comboBox_ImageColormap->addItem(javaStyleIterator0.next().toLocal8Bit().constData());
			QStandardItem *item = model0->item(itemIndex0, 0);
			item->setEnabled(true);
			++itemIndex0;
		}

		//combobox ImageColormap;
		ui_image->comboBox_ImageColormap->setCurrentIndex(0);
		main->ImageGui::Record[newInd].imgColormap.listindex = 0;

		//==============================================================================
		// combobox Geometry
		//------------------------------------------------------------------------------
		QStandardItemModel *model1 = dynamic_cast< QStandardItemModel * >(ui_image->comboBox_plotGeometry->model());
		int itemIndex1 = 0;
		QStringListIterator javaStyleIterator1(main->ImageGui::record.imgGeometry.strings);
		ui_image->comboBox_plotGeometry->setDuplicatesEnabled(false);
		ui_image->comboBox_plotGeometry->clear();
		while (javaStyleIterator1.hasNext()){
			ui_image->comboBox_plotGeometry->addItem(javaStyleIterator1.next().toLocal8Bit().constData());
			QStandardItem *item = model1->item(itemIndex1, 0);
			item->setEnabled(true);
			++itemIndex1;
		}

		//combobox Geometry;
		ui_image->comboBox_plotGeometry->setCurrentIndex(0);
		main->ImageGui::Record[newInd].imgGeometry.listindex = 0;
	
		//negative
		ui_image->checkBox_negative->setChecked(0);

		//saturation
		ui_image->checkBox_saturation->setChecked(1);

		//brightness
		ui_image->hSlider_brightness->setValue(0);

		//contrast
		ui_image->hSlider_contrast->setValue(0);

		//channel
		ui_image->hSlider_channel->setValue(0);

	return;
}

//==============================================================================
// void ImageWidget::resetTab(int index)
//------------------------------------------------------------------------------
//==============================================================================
void ImageWidget::resetTab(int index)
{
	return;
}

//==============================================================================
// void ImageWidget::setTab(int newInd, int lastInd)
//------------------------------------------------------------------------------
//==============================================================================
void ImageWidget::setTab(int newInd, int lastInd)
{
		//get pointer to the QCustomPlot related to the current tab widget
		/*
		QList<QCustomPlot *> list_images1 = ui_image->tabWidget_image->findChildren<QCustomPlot *>("imgplot" + QString::number(newInd + 1));
		if (list_images1.size() != 1){
			return;
		}
		*/
		//check if QCustomplot already (or still) exists
		QList<QGraphicsView *> list_images2 = ui_image->tabWidget_image->findChildren<QGraphicsView *>("img" + QString::number(newInd + 1));
		if (list_images2.size() == 1){
			return;
		}

		//cout << " !!! " << newInd << " " << lastInd << endl;
		//set new plot
		//main->Gui::tabRecord.currentImageplot = list_images1[0];
		main->Gui::tabRecord.currentImage = list_images2[0];
		//ui_image->imageplot = list_images1[0];
		ui_image->image = list_images2[0];

		//combobox ImageColormap
		main->ImageGui::Record[lastInd].imgColormap.listindex = ui_image->comboBox_ImageColormap->currentIndex();
		ui_image->comboBox_ImageColormap->setCurrentIndex(main->ImageGui::Record[newInd].imgColormap.listindex);
		//enable all combobox ImageColormap items
		QStandardItemModel *model = dynamic_cast< QStandardItemModel * >(ui_image->comboBox_ImageColormap->model());
		int itemIndex0 = 0;
		while (itemIndex0 < ui_image->comboBox_ImageColormap->count()){
			QStandardItem *item = model->item(itemIndex0, 0);
			item->setEnabled(true);
			++itemIndex0;
		}
	
		//combobox imageGeometry
		main->ImageGui::Record[lastInd].imgGeometry.listindex = ui_image->comboBox_plotGeometry->currentIndex();
		ui_image->comboBox_plotGeometry->setCurrentIndex(main->ImageGui::Record[newInd].imgGeometry.listindex);
		//enable all combobox imageGeometry items
		QStandardItemModel *model1 = dynamic_cast< QStandardItemModel * >(ui_image->comboBox_plotGeometry->model());
		int itemIndex1 = 0;
		while (itemIndex1 < ui_image->comboBox_plotGeometry->count()){
			QStandardItem *item = model1->item(itemIndex1, 0);
			item->setEnabled(true);
			++itemIndex1;
		}
		
		//negative
		main->ImageGui::Record[lastInd].negative = ui_image->checkBox_negative->isChecked();
		ui_image->checkBox_negative->setChecked(main->ImageGui::Record[newInd].negative);

		//saturation
		main->ImageGui::Record[lastInd].saturation = ui_image->checkBox_saturation->isChecked();
		ui_image->checkBox_saturation->setChecked(main->ImageGui::Record[newInd].saturation);

		//brightness
		main->ImageGui::Record[lastInd].visuals.brightness = ui_image->hSlider_brightness->value();
		ui_image->hSlider_brightness->setValue(main->ImageGui::Record[newInd].visuals.brightness);

		//contrast
		main->ImageGui::Record[lastInd].visuals.contrast = ui_image->hSlider_contrast->value();
		ui_image->hSlider_contrast->setValue(main->ImageGui::Record[newInd].visuals.contrast);

		//channel
		main->ImageGui::Record[lastInd].channel = ui_image->hSlider_channel->value() - 1;
		ui_image->hSlider_channel->setValue(main->ImageGui::Record[newInd].channel);

	return;
}

//==============================================================================
// void ImageWidget::activateTab(int index)
//------------------------------------------------------------------------------
//==============================================================================
void ImageWidget::activateTab(int index)
{
		//	cout << "current tab index: " <<  index << endl;
		if (index > -1){
			tab_x = ui_image->tabWidget_image->widget(index);

			if (index == (ui_image->tabWidget_image->count() - 1)){
				tab_x = constructTab();
				initElements(index);
			}

			QVector<int> i;
			i.push_back(index);
			emit activeTab_Signal(tab_x, ui_image->tabWidget_image, "add", i);

			setTab(TabHandling::orderTabs_Image[index] - 1, TabHandling::orderTabs_Image[TabHandling::lastIndexTab_Image] - 1);
			//main->activateCurrentImage(TabHandling::orderTabs_Image[index] - 1);
			//cout << "IMAGE #1: "   <<TabHandling::orderTabs_Image[index] - 1 << endl;

		}
	return;
}

//==============================================================================
// void ImageWidget::closeTab(int index)
//------------------------------------------------------------------------------
//==============================================================================
void ImageWidget::closeTab(int index)
{
		QVector<int> i;
		i.push_back(index);

		emit activeTab_Signal(NULL, ui_image->tabWidget_image, "close", i);

		setTab(TabHandling::orderTabs_Image[index] - 1, TabHandling::orderTabs_Image[TabHandling::lastIndexTab_Image] - 1);
	return;
}

//==============================================================================
// void ImageWidget::moveTab(int to, int from)
//------------------------------------------------------------------------------
//==============================================================================
void ImageWidget::moveTab(int to, int from)
{
		QVector<int> i;
		i.push_back(to);
		i.push_back(from);
		i.push_back(to);

		emit activeTab_Signal(NULL, ui_image->tabWidget_image, "move", i);

		setTab(TabHandling::orderTabs_Image[to] - 1, TabHandling::orderTabs_Image[TabHandling::lastIndexTab_Image] - 1);
	return;
}

//==============================================================================
// void ImageWidget::attachWidget()
//------------------------------------------------------------------------------
//==============================================================================
void ImageWidget::attachWidget()
{
		emit attachWidget_Signal(this, "Image");
	return;
}

//==============================================================================
// void ImageWidget::detachWidget()
//------------------------------------------------------------------------------
//==============================================================================
void ImageWidget::detachWidget()
{
		main->detachWidget();
	return;
}

//==============================================================================
// bool ImageWidget::eventFilter(QObject *o, QEvent *e)
//------------------------------------------------------------------------------
//==============================================================================
bool ImageWidget::eventFilter(QObject *o, QEvent *e)
{
		//this is just blocking an annoying wheel event on the tabbar
		//that causes a switching of tabs
		if (e->type() == QEvent::Wheel){
			//qDebug() << "Wheel event blocked";
			return true;
		}
	return 0;
}

