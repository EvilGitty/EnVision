//==============================================================================
//
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "envision.h"

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
EnVision::EnVision(QStringList inputArguments, QStringList inputFiles, QString outputPath, QWidget *parent) : QMainWindow(parent),
ui_base(new Ui::EnVision_baseUI),
ui_table(new Ui::EnVision_tableUI),
ui_plot(new Ui::EnVision_plotUI),
ui_cube(new Ui::EnVision_cubeUI),
ui_image(new Ui::EnVision_imageUI)
{
		//------------------------------------------------------------------------
		// setup basics (windows appearance etc..)
		ui_base->setupUi(this);

		//size matters
		this->showMaximized();

		this->setWindowOpacity(qreal(100) / 100);

		//------------------------------------------------------------------------
		// allows dropping files without using the gui menu
		this->setAcceptDrops(true);

		//------------------------------------------------------------------------
		//init  tab handling class and assign the first image to the first tab
		//This relation between image number and tab position is currently updated
		//because it will change when tabs are moves/cloaes
		tabhand = new TabHandling(this);
		TabHandling::orderTabs_Table = tabhand->toTab.add(1, TabHandling::orderTabs_Table);
		TabHandling::orderTabs_Plot = tabhand->toTab.add(1, TabHandling::orderTabs_Plot);
		TabHandling::orderTabs_Image = tabhand->toTab.add(1, TabHandling::orderTabs_Image);

		//------------------------------------------------------------------------
		// handle input arguments
		imgLoad1 = inputArguments;
		imgLoad2 = inputFiles;
		execPath = outputPath;

		//------------------------------------------------------------------------
		// register visible classes

		//------------------------------------------------------------------------
		// prepare tabe widget
		newTable = new TableWidget(this);
		ui_table = newTable->getTableUI();
		//the original widget done with Qt Designer
		ui_table->table->setObjectName("table1");
		//TableAttribute::addVector();
		newTable->activateTab(0);
		newTable->reserveTable();

		//------------------------------------------------------------------------
		// prepare plot widget
		newPlot = new PlotterWidget(this);
		ui_plot = newPlot->getPlotUI();
		//the original widget done with Qt Designer
		ui_plot->plot->setObjectName("plot1");
		PlotGui::addGuisettings();
		PlotAttribute::addVector();
		newPlot->initElements(0);
		newPlot->activateTab(0);

		//------------------------------------------------------------------------
		// prepare 3D cube widget
		/*
		newCube = new CubeWidget(this);
		ui_cube = newCube->getCubeUI();
		//the original widget done with Qt Designer
		ui_cube->cube->setObjectName("cube1");
		*/
		
		//------------------------------------------------------------------------
		// prepare image widget
		newImage = new ImageWidget(this);
		ui_image = newImage->getImageUI();
		//the original widget done with Qt Designer
		ui_image->imageplot->setObjectName("imgplot1");
		ui_image->image->setObjectName("img1");

		ImageGui::addGuisettings();
		ImageAttribute::addVector();
		newImage->initElements(0);
		newImage->activateTab(0);

		//------------------------------------------------------------------------
		// show the widgets
		newTable->show();
		newPlot->show();
		newImage->show();

		//------------------------------------------------------------------------
		// treat the widgets as MDI subwindows
		QList<QMdiSubWindow *> wnd = ui_base->mdiArea->subWindowList();
		QList<QMdiSubWindow *>::iterator i;
		for (i = wnd.begin(); i != wnd.end(); ++i) {
			if (QString::compare("Data", (*i)->windowTitle()) == 0){
				(*i)->setWidget(newTable);
				(*i)->setWindowFlags(Qt::Widget);
				(*i)->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
				activeSubWin = (*i);
				tabRecord.tableWidget_attached = 1;
			}

			if (QString::compare("Plotter", (*i)->windowTitle()) == 0){
				(*i)->setWidget(newPlot);
				(*i)->setWindowFlags(Qt::Widget);
				(*i)->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
				tabRecord.plotWidget_attached = 1;
			}		
			/*
			if (QString::compare("Cube", (*i)->windowTitle()) == 0){
				(*i)->setWidget(newCube);
				(*i)->setWindowFlags(Qt::Widget);
				(*i)->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
				tabRecord.cubeWidget_attached = 1;
			}
			*/

			if (QString::compare("Image", (*i)->windowTitle()) == 0){
				(*i)->setWidget(newImage);
				(*i)->setWindowFlags(Qt::Widget);
				(*i)->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
				tabRecord.imageWidget_attached = 0;
			}

		}

		//newImage->detachWidget();

		//newCube->show();

		//------------------------------------------------------------------------
		// set plot widget appearance
		ui_plot->mdiArea->setViewMode(QMdiArea::SubWindowView);
		ui_plot->mdiArea->tileSubWindows();
		
		//------------------------------------------------------------------------
		// set image widget appearance
		ui_image->mdiArea->setViewMode(QMdiArea::SubWindowView);
		ui_image->mdiArea->tileSubWindows();

		//absolutely needed to get the latest gui updates
		tabhand->guiAccess();

		//------------------------------------------------------------------------
		// check if a subwindow changes focus
		connect(ui_base->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)), this, SLOT(subWindowActivate(QMdiSubWindow *)));

		//------------------------------------------------------------------------
		//arrange subwindows
		ui_base->mdiArea->setViewMode(QMdiArea::TabbedView);
		ui_base->mdiArea->tileSubWindows();
		tileOrCascadeSubWindows();
	
		//------------------------------------------------------------------------
		// create the most basic connections to get started
		QObject::connect(ui_base->actionSave_state, SIGNAL(triggered()), this, SLOT(saveWindowStatus()));
		QObject::connect(ui_base->actionReload_state, SIGNAL(triggered()), this, SLOT(reloadWindowStatus()));
		QObject::connect(ui_base->actionExit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
		//not working QObject::connect(ui_base->centralWidget, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel(QWheelEvent*)));

		//------------------------------------------------------------------------
		// creatre connections for sidebar left
		QObject::connect(ui_base->actionSwitchTileOrCascade, SIGNAL(triggered()), this, SLOT(tileOrCascadeSubWindows()));
		QObject::connect(ui_base->tabWidget_filedialog, SIGNAL(currentChanged(int)), this, SLOT(handleDockWidget03(int)));

		//------------------------------------------------------------------------
		// create shortcuts
		ui_base->actionSwitchTileOrCascade->setShortcut(tr("CTRL+T"));

		//------------------------------------------------------------------------
		// install events
		handleEventFilter(1, ui_table->tabWidget_table->tabBar());
		handleEventFilter(1, ui_plot->tabWidget_plotter->tabBar());
		//handleEventFilter(1, ui_cube->tabWidget_cube->tabBar());
		handleEventFilter(1, ui_image->tabWidget_image->tabBar());

		//------------------------------------------------------------------------
		// Fire up the file manager
		filemanager = new Filemanager(this);

		//------------------------------------------------------------------------
		// Parse the input
		//filemanager->processInputArguments(inputArguments);
		//filemanager->openInputArgFiles(inputFiles);

		//------------------------------------------------------------------------
		// Show a list of the recently loaded files in the menu
		cout << " Executable Path: " << execPath.toStdString() << endl;
		filemanager->showRecentFiles(execPath + RECENTFILES);
		//filemanager->findFiles("", QStringList() << " ", "");

		fdialog = new QFileDialog();
		//------------------------------------------------------------------------
		// signal/slots for the file dialog
		QObject::connect(fdialog, SIGNAL(finished(int)), fdialog, SLOT(open()));
		QObject::connect(fdialog, SIGNAL(accepted()), this, SLOT(acceptFileDialog()));
		QObject::connect(fdialog, SIGNAL(rejected()), this, SLOT(rejectFileDialog()));
		QObject::connect(fdialog, SIGNAL(filesSelected(QStringList)), filemanager, SLOT(selectedFiles(QStringList)));
		QObject::connect(this, &EnVision::callFilemanager, filemanager, &Filemanager::droppedFiles);

		createFileDialog(fdialog);

		//------------------------------------------------------------------------
		// signal/slots for the sidebar
		QObject::connect(ui_base->actionToggleDockWidget03, SIGNAL(triggered()), this, SLOT(handleLeftSidebar()));
		QObject::connect(ui_base->actionToggleDockWidget02, SIGNAL(triggered()), this, SLOT(handleLeftSidebar()));
		QObject::connect(ui_base->actionToggleDockWidget01, SIGNAL(triggered()), this, SLOT(handleLeftSidebar()));
		QObject::connect(ui_base->actionToggleTableWidget, SIGNAL(triggered()), this, SLOT(handleLeftSidebar()));
		QObject::connect(ui_base->actionTogglePlotWidget, SIGNAL(triggered()), this, SLOT(handleLeftSidebar()));
		QObject::connect(ui_base->actionToggleImageWidget, SIGNAL(triggered()), this, SLOT(handleLeftSidebar()));
		QObject::connect(ui_base->actionToggleCubeWidget, SIGNAL(triggered()), this, SLOT(handleLeftSidebar()));


}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
EnVision::~EnVision()
{
}

//==============================================================================
// Ui::EnVision_baseUI* EnVision::getBaseUI(void)
//------------------------------------------------------------------------------
//==============================================================================
Ui::EnVision_baseUI* EnVision::getBaseUI(void)
{
	return ui_base;
}


//==============================================================================
// Ui::EnVision_tableUI* EnVision::getTableUI(void)
//------------------------------------------------------------------------------
//==============================================================================
Ui::EnVision_tableUI* EnVision::getTableUI(void)
{
	return ui_table;
}

//==============================================================================
// Ui::EnVision_baseUI* EnVision::getPlotUI(void)
//------------------------------------------------------------------------------
//==============================================================================
Ui::EnVision_plotUI* EnVision::getPlotUI(void)
{
	return ui_plot;
}

//==============================================================================
// Ui::EnVision_cubeUI* EnVision::getCubeUI(void)
//------------------------------------------------------------------------------
//==============================================================================
Ui::EnVision_cubeUI* EnVision::getCubeUI(void)
{
	return ui_cube;
}


//==============================================================================
// Ui::EnVision_imageUI* EnVision::getImageUI(void)
//------------------------------------------------------------------------------
//==============================================================================
Ui::EnVision_imageUI* EnVision::getImageUI(void)
{
	return ui_image;
}

//==============================================================================
// int EnVision::activateNewImage(void)
//------------------------------------------------------------------------------
//==============================================================================
int EnVision::activateNewImage(void)
{
		int ret = 0;
		//new image will be added onto a new tab
		if (ui_image->checkBox_imgLoadSelect->isChecked() == 1){
			newImage->activateTab(ui_image->tabWidget_image->count() - 1);
			ret = ui_image->tabWidget_image->count() - 1;
		}

		//new image will be added onto the current tab, overwriting the current image
		if (ui_image->checkBox_imgLoadSelect->isChecked() == 0){
			newImage->activateTab(ui_image->tabWidget_image->currentIndex());
			ret = ui_image->tabWidget_image->currentIndex();
		}

	return ret; 
}

//==============================================================================
// int EnVision::activateCurrentImage(int index)
//------------------------------------------------------------------------------
//==============================================================================
int EnVision::activateCurrentImage(int index)
{
		if (filemanager != 0){
			cout << "SIZE FILEMANAGER: " << filemanager->img_ref.size() << endl;
			filemanager->imgclass = filemanager->img_ref[index];
		}
	return index;
}


//==============================================================================
// QMdiSubWindow* EnVision::subWindowActivate(QMdiSubWindow* subwin)
//------------------------------------------------------------------------------
//==============================================================================
QMdiSubWindow* EnVision::subWindowActivate(QMdiSubWindow* subwin)
{
		activeSubWin = NULL;
		//check if subwindow still ecists
		QList<QMdiSubWindow *> wnd = ui_base->mdiArea->subWindowList();
		QList<QMdiSubWindow *>::iterator i;
		for (i = wnd.begin(); i != wnd.end(); ++i) {
			if (subwin == (*i)){
				activeSubWin = subwin;
			}
		}
	
		//cout << "active: " << subwin->windowTitle().toStdString() << endl;
		//cout << " -- " << endl;
	return activeSubWin;
}

//==============================================================================
// void EnVision::attachWidget(QWidget* widget, QString windowTitle)
//------------------------------------------------------------------------------
//==============================================================================
void EnVision::attachWidget(QWidget* widget, QString windowTitle)
{			
		//don't try to attach a window that's already attached
		QList<QMdiSubWindow *> wnd0 = ui_base->mdiArea->subWindowList();
		QList<QMdiSubWindow *>::iterator ii;
		for (ii = wnd0.begin(); ii != wnd0.end(); ++ii) {
			if (QString::compare(windowTitle, (*ii)->windowTitle()) == 0){
				return;
			}
		}
			
		//no subwindow with a known name was fund, create a new one now
		QMdiSubWindow *subWindow = new QMdiSubWindow(ui_base->mdiArea);
		subWindow->setAttribute(Qt::WA_DeleteOnClose);
		subWindow->setWindowTitle(windowTitle);
		ui_base->mdiArea->addSubWindow(subWindow, Qt::Window);
		subWindow->show();

		QList<QMdiSubWindow *> wnd = ui_base->mdiArea->subWindowList();
		QList<QMdiSubWindow *>::iterator i;
		for (i = wnd.begin(); i != wnd.end(); ++i) {	
			if (QString::compare(subWindow->windowTitle(), (*i)->windowTitle()) == 0){
				cout << (*i)->windowTitle().toStdString() << "!" << endl;
				(*i)->setWidget(widget);
				(*i)->setWindowFlags(Qt::Widget);
				(*i)->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
				activeSubWin = (*i);
			}
		}
			
		return;
}

//==============================================================================
// void EnVision::detachWidget(void)
//------------------------------------------------------------------------------
//==============================================================================
void EnVision::detachWidget(void)
{
		if (activeSubWin){
			QMdiSubWindow *sub = ui_base->mdiArea->activeSubWindow();
			QWidget *wid = sub->widget();
			wid->hide();
			sub->deleteLater();
			ui_base->mdiArea->removeSubWindow(wid);
			wid->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
			wid->show();
		}
		
	return; 
}


//==============================================================================
// void EnVision::setWorkingGuiState()
//------------------------------------------------------------------------------
//==============================================================================
//void EnVision::setWorkingGuiState()
//{

//	return;
//}

//==============================================================================
// void EnVision::setIdleGuiState()
//------------------------------------------------------------------------------
//==============================================================================
//void EnVision::setIdleGuiState()
//{

//	return;
//}


//==============================================================================
// void EnVision::resetGui()
//------------------------------------------------------------------------------
//==============================================================================
//void EnVision::resetGui()
//{
//	return;
//}



//==============================================================================
// void EnVision::handleDockWidget03(int tabindex)
//------------------------------------------------------------------------------
//==============================================================================
void EnVision::handleDockWidget03(int tabindex)
{
		QString title = ui_base->tabWidget_filedialog->tabText(ui_base->tabWidget_filedialog->currentIndex());
		ui_base->dockWidget_03->setWindowTitle(title);

	return;
}

//==============================================================================
// void EnVision::createFileDialog(QFileDialog *openfdialog)
//------------------------------------------------------------------------------
// The native QFileDialog is taken and put into a tab widget. Advantage:
// it can be docked/undocked and is always accessible without having to
// resort to Windows Explorer or a custom "Load Files" button. Comapred
// to the classic QDialog, it can be kept visible all the time. 
// Disadvantage: A QDialog is not meant to be used like this, although
// it's derived directly from QWidget.
//==============================================================================
void EnVision::createFileDialog(QFileDialog *openfdialog)
{
		//==============================================================================
		//future: some calendar stuff
		//QDateEdit *de = new QDateEdit();
		//de->setCalendarPopup(true); 
		//de->show();

		const QString DEFAULT_DIR_KEY("default_dir");
		QSettings MySettings; // Will be using application informations

		//Xmlinit *xml = new Xmlinit(main);
		int tabcount = ui_base->tabWidget_filedialog->count();
		ui_base->tabWidget_filedialog->insertTab(tabcount, openfdialog, "Current Folder");
		ui_base->tabWidget_filedialog->setCurrentIndex(tabcount);

		openfdialog->setDirectory(MySettings.value(DEFAULT_DIR_KEY).toString());
		openfdialog->setWindowFlags(Qt::Widget);
		openfdialog->setOption(QFileDialog::ShowDirsOnly);
		openfdialog->setOption(QFileDialog::DontUseNativeDialog, true);
		openfdialog->setStyleSheet("QTreeView {font: 10pt \"Arial\";}");
		openfdialog->setFileMode(QFileDialog::ExistingFiles);
		openfdialog->setAcceptMode(QFileDialog::AcceptOpen);
		openfdialog->setMinimumWidth(5);
		//openfdialog.setNameFilters(QStringList() << xml.readXmlproperty(main.ImageinitRecord.configFiles[0],
		//	"ImageFormats") << "Images (*.tgd *.hyspex *.img *.mat *.im3 *.asd *.cub)" << "Anything (*)");
		//QString filter = tr("Images (*.tgd *.hyspex *.img *.mat *.im3 *.asd *.cub)");
		//openfdialog.selectNameFilter(filter);
		openfdialog->setLabelText(QFileDialog::Accept, "Open selected files");
		openfdialog->setLabelText(QFileDialog::Reject, "Cancel");
		
	return;
}

//==============================================================================
// void EnVision::acceptFileDialog(void)
//------------------------------------------------------------------------------
//==============================================================================
void EnVision::acceptFileDialog(void)
{
		const QString DEFAULT_DIR_KEY("default_dir");
		QSettings MySettings; // Will be using application informations

		QList<QUrl> savedUrls = fdialog->sidebarUrls();
		QStringList chosenFiles = fdialog->selectedFiles();

		//setting new default folder
		QDir NewDir = QFileInfo(chosenFiles[0]).absoluteDir();
		if (chosenFiles.size() > 0) {
			QDir CurrentDir;
			MySettings.setValue(DEFAULT_DIR_KEY,
			CurrentDir.absoluteFilePath(NewDir.absolutePath()));
		}

		foreach(QString str, chosenFiles) {
			QFileInfo fi(str);
			str = fi.absoluteFilePath();
			savedUrls << QUrl::fromLocalFile(str);
			qDebug() << "! " << savedUrls[0].toString() << endl;
		}

		fdialog->setSidebarUrls(savedUrls);

		//bring image window on top
		//newImage->showNormal();

	return;
}

//==============================================================================
// void EnVision::rejectFileDialog(void)
//------------------------------------------------------------------------------
//==============================================================================
void EnVision::rejectFileDialog(void)
{
		//do nothing
	return;
}

//==============================================================================
// void EnVision::tileOrCascadeSubWindows(void)
//------------------------------------------------------------------------------
//==============================================================================
void EnVision::tileOrCascadeSubWindows(void)
{
		ui_base->mdiArea->setViewMode(QMdiArea::TabbedView);

		if (cascadeOrTile_status == 2){
			ui_base->mdiArea->setViewMode(QMdiArea::SubWindowView);
			ui_base->mdiArea->setViewMode(QMdiArea::TabbedView);
			ui_base->actionSwitchTileOrCascade->setText("Cascade View");
			cascadeOrTile_status = 1;
			return;
		}

		if (cascadeOrTile_status == 1){
			ui_base->actionSwitchTileOrCascade->setText("Tile View");
			ui_base->mdiArea->cascadeSubWindows();
			cascadeOrTile_status = 0;
			return;
		}

		if (cascadeOrTile_status == 0){
			ui_base->actionSwitchTileOrCascade->setText("Tab View");
			ui_base->mdiArea->tileSubWindows();
			cascadeOrTile_status = 2;
			return;
		}

	return;
}

//==============================================================================
// void EnVision::handleLeftSidebar(void)
//------------------------------------------------------------------------------
//==============================================================================
void EnVision::handleLeftSidebar(void)
{
		QObject* obj = sender();
		QList<QMdiSubWindow *> wnd = ui_base->mdiArea->subWindowList();
		QList<QMdiSubWindow *>::iterator i;

		//Terminal/File Explorer
		if (obj == ui_base->actionToggleDockWidget03) {
			if (ui_base->actionToggleDockWidget03->isChecked() == 1) {
				if (ui_base->dockWidget_03->isMinimized()){
					ui_base->dockWidget_03->showNormal();
				}
				ui_base->dockWidget_03->show();
			} else {
				ui_base->dockWidget_03->hide();
			}
		}

		//DockWidget02
		if (obj == ui_base->actionToggleDockWidget02) {
			if (ui_base->actionToggleDockWidget02->isChecked() == 1) {
				if (ui_base->dockWidget_02->isMinimized()){
					ui_base->dockWidget_02->showNormal();
				}
				ui_base->dockWidget_02->show();
			} else {
				ui_base->dockWidget_02->hide();
			}
		}

		//DockWidget01
		if (obj == ui_base->actionToggleDockWidget01) {
			if (ui_base->actionToggleDockWidget01->isChecked() == 1) {
				if (ui_base->dockWidget_01->isMinimized()){
					ui_base->dockWidget_01->showNormal();
				}
				ui_base->dockWidget_01->show();
			} else {
				ui_base->dockWidget_01->hide();
			}
		}

		//Table
		if (obj == ui_base->actionToggleTableWidget) {
			for (i = wnd.begin(); i != wnd.end(); ++i) {
				//cout << (*i)->windowTitle().toStdString() << endl;
				if (QString::compare("Data", (*i)->windowTitle()) == 0){
					if (ui_base->actionToggleTableWidget->isChecked() == 1) {
						if ((*i)->isMinimized()){
							(*i)->showNormal();
						}
						(*i)->show();
					} else {
						(*i)->hide();
					}
				}
			}
		}

		//Plotter
		if (obj == ui_base->actionTogglePlotWidget) {
			for (i = wnd.begin(); i != wnd.end(); ++i) {
				//cout << (*i)->windowTitle().toStdString() << endl;
				if (QString::compare("Plotter", (*i)->windowTitle()) == 0){
					if (ui_base->actionTogglePlotWidget->isChecked() == 1) {
						if ((*i)->isMinimized()){
							(*i)->showNormal();
						}
						(*i)->show();
					} else {
						(*i)->hide();
					}
				}
			}
		}

		//Cube
		/*
		if (obj == ui_base->actionToggleCubeWidget) {
			for (i = wnd.begin(); i != wnd.end(); ++i) {
				//cout << (*i)->windowTitle().toStdString() << endl;
				if (QString::compare("Cube", (*i)->windowTitle()) == 0){
					if (ui_base->actionToggleCubeWidget->isChecked() == 1) {
						if ((*i)->isMinimized()){
							(*i)->showNormal();
						}
						(*i)->show();
					}
					else {
						(*i)->hide();
					}
				}
			}
		}
		*/

		//Image
		if (obj == ui_base->actionToggleImageWidget) {
			for (i = wnd.begin(); i != wnd.end(); ++i) {
				//cout << (*i)->windowTitle().toStdString() << endl;
				if (QString::compare("Image", (*i)->windowTitle()) == 0){
					if (ui_base->actionToggleImageWidget->isChecked() == 1) {
						if ((*i)->isMinimized()){
							(*i)->showNormal();
						}
						(*i)->show();
					}
					else {
						(*i)->hide();
					}
				}
			}
		}

	return;
}

//==============================================================================
// void EnVision::saveWindowStatus()
//------------------------------------------------------------------------------
//==============================================================================
void EnVision::saveWindowStatus()
{
		/*
		cout << " save " << endl;
		QSettings settings("MyCompany", "MyApp");
		settings.setValue("geometry", saveGeometry());
		settings.setValue("windowState", saveState(0));
		settings.setValue("pos", pos());
		settings.setValue("size", size());
		settings.setValue("state", saveState());
	

			
		bool ok;
		QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
			tr("Enter name to save settings:"), QLineEdit::Normal,
			QDir::home().dirName(), &ok);
		
		if (ok && !text.isEmpty()){

		} else {
		
		}
		*/
		
	return;
}

//==============================================================================
// void EnVision::reloadWindowStatus()
//------------------------------------------------------------------------------
//==============================================================================
void EnVision::reloadWindowStatus()
{
	/*
		QSettings settings;

		QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
		QSize size = settings.value("size", QSize(400, 400)).toSize();
		QByteArray state = settings.value("state", QByteArray())
			.toByteArray();
		restoreState(state);
		resize(size);
		move(pos);
		*/
	return;
}

