#include "tabhandling.h"
#include "envision.h"

int TabHandling::lastIndexTab_Table = 0;
int TabHandling::lastIndexTab_Plot = 0;
int TabHandling::lastIndexTab_Image = 0;

int TabHandling::missingIndexTab_Table =  1;
int TabHandling::missingIndexTab_Plot = 1;
int TabHandling::missingIndexTab_Image = 1;

QVector<int> TabHandling::orderTabs_Table;
QVector<int> TabHandling::orderTabs_Plot;
QVector<int> TabHandling::orderTabs_Image;

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

TabHandling::TabHandling(EnVision *main)
{
		this->main = main;

		guiAccess();
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
TabHandling::~TabHandling()
{

}

//==============================================================================
// void TabHandling::guiAccess()
//------------------------------------------------------------------------------
//==============================================================================
void TabHandling::guiAccess()
{
	this->ui_base = main->getBaseUI();
	this->ui_table = main->getTableUI();
	this->ui_plot = main->getPlotUI();
	this->ui_image = main->getImageUI();
}

//==============================================================================
// void TabHandling::handleTabCloseButtons(QTabBar *t,  int ind_hide, int ind_show)
//------------------------------------------------------------------------------
//==============================================================================
void TabHandling::handleTabCloseButtons(QTabBar *t,  int ind_hide, int ind_show)
{

		//hide all
		int i = 0;
		while (i < t->count()){
			t->tabButton(i, QTabBar::RightSide)->hide();
			i++;
		}

		//hide only one button
		//if (ind_hide > -1){
			//t->tabButton(ind_hide, QTabBar::RightSide)->hide();
		//}

		//show only button
		if (ind_show > -1){
			t->tabButton(ind_show, QTabBar::RightSide)->show();
		}
	return;
}

//==============================================================================
// void TabHandling::addWidget_table(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
//------------------------------------------------------------------------------
//==============================================================================
void TabHandling::addWidget_table(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
{

		if ((obj == ui_table->tabWidget_table) && QString::compare(msg, "add") == 0) {

			QString tabtext = ui_table->tabWidget_table->tabText(index[0]);
			QTabBar *t = qobject_cast<QTabBar*>(ui_table->tabWidget_table->findChild<QTabBar *>());

			if (QString::compare(tabtext, "+") == 0) {

				int tabcount = ui_table->tabWidget_table->count();
				//first insert a new tab widget and place it before left of the "+" tab
				ui_table->tabWidget_table->insertTab(tabcount - 1, widget, QString::number(missingIndexTab_Table + 1));
				//make sure this tabs is visible/active, Qt is picky with this sometimes
				ui_table->tabWidget_table->setCurrentIndex(tabcount - 1);

				//add this tab to our custom vector orderTabs_Table that keeps tack of al tab positions, movements, deletions etc.
				TabHandling::orderTabs_Table = toTab.add(missingIndexTab_Table + 1, TabHandling::orderTabs_Table);

				//handle the visibility of the close button
				//"lastIndexTab_Table" just recalls the active tab before the current one so we 
				//know on which (no longer active) tab the close button can be hidden again
				handleTabCloseButtons(t, tabcount - 2, ui_table->tabWidget_table->currentIndex());
				handleTabCloseButtons(t, lastIndexTab_Table, -1);

				//for the sake of accesibility of this tab position from other classes.
				main->Gui::tabRecord.tableIndex = ui_table->tabWidget_table->currentIndex();
				lastIndexTab_Table = ui_table->tabWidget_table->currentIndex();
			}
			else{
				if (ui_table->tabWidget_table->count() > 2){
					handleTabCloseButtons(t, ui_table->tabWidget_table->currentIndex(), index[0]);
				}else {
					main->Gui::tabRecord.tableIndex = ui_table->tabWidget_table->currentIndex();
				}
				lastIndexTab_Table = ui_table->tabWidget_table->currentIndex();
			}
		}

	return;
}

//==============================================================================
// void TabHandling::addWidget_plot(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
//------------------------------------------------------------------------------
//==============================================================================
void TabHandling::addWidget_plot(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
{
		if ((obj == ui_plot->tabWidget_plotter) && QString::compare(msg, "add") == 0) {

			QString tabtext = ui_plot->tabWidget_plotter->tabText(index[0]);
			QTabBar *t = qobject_cast<QTabBar*>(ui_plot->tabWidget_plotter->findChild<QTabBar *>());

			if (QString::compare(tabtext, "+") == 0) {

				lastIndexTab_Plot = ui_plot->tabWidget_plotter->currentIndex();

				int tabcount = ui_plot->tabWidget_plotter->count();
				//first insert a new tab widget and place it before left of the "+" tab
				ui_plot->tabWidget_plotter->insertTab(tabcount - 1, widget, QString::number(missingIndexTab_Plot+1));
				//make sure this tabs is visible/active, Qt is picky with this sometimes
				ui_plot->tabWidget_plotter->setCurrentIndex(tabcount - 1);

				//add this tab to our custom vector orderTabs_Plot that keeps tack of al tab positions, movements, deletions etc.
				TabHandling::orderTabs_Plot = toTab.add(missingIndexTab_Plot+1, TabHandling::orderTabs_Plot);
				main->PlotGui::addGuisettings();
				main->PlotAttribute::addVector();
				
				//handle the visibility of the close button
				//"lastIndexTab_Plot" just recalls the active tab before the current one so we 
				//know on which (no longer active) tab the close button can be hidden again
				handleTabCloseButtons(t, tabcount - 2, ui_plot->tabWidget_plotter->currentIndex());
				handleTabCloseButtons(t, lastIndexTab_Plot, -1);

				//for the sake of accesibility of this tab position from other classes.
				main->Gui::tabRecord.plotIndex = ui_plot->tabWidget_plotter->currentIndex();
			}else{
				if (ui_plot->tabWidget_plotter->count() > 2){
					handleTabCloseButtons(t, ui_plot->tabWidget_plotter->currentIndex(), index[0]);
				}
				main->Gui::tabRecord.plotIndex = ui_plot->tabWidget_plotter->currentIndex();
				lastIndexTab_Plot = ui_plot->tabWidget_plotter->currentIndex();
			}
		}

	return;
}

//==============================================================================
// void TabHandling::addWidget_image(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
//------------------------------------------------------------------------------
//==============================================================================
void TabHandling::addWidget_image(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
{

		if ((obj == ui_image->tabWidget_image) && QString::compare(msg, "add") == 0) {

			QString tabtext = ui_image->tabWidget_image->tabText(index[0]);
			QTabBar *t = qobject_cast<QTabBar*>(ui_image->tabWidget_image->findChild<QTabBar *>());

			if (QString::compare(tabtext, "+") == 0) {
				lastIndexTab_Image = ui_image->tabWidget_image->currentIndex();

				int tabcount = ui_image->tabWidget_image->count();
				//first insert a new tab widget and place it before left of the "+" tab
				ui_image->tabWidget_image->insertTab(tabcount - 1, widget, QString::number(missingIndexTab_Image + 1));
				//make sure this tabs is visible/active, Qt is picky with this sometimes
				ui_image->tabWidget_image->setCurrentIndex(tabcount - 1);

				//add this tab to our custom vector orderTabs_Image that keeps tack of al tab positions, movements, deletions etc.
				TabHandling::orderTabs_Image = toTab.add(missingIndexTab_Image + 1, TabHandling::orderTabs_Image);
				main->ImageGui::addGuisettings();
				main->ImageAttribute::addVector();
			
				//handle the visibility of the close button
				//"lastIndexTab_Image" just recalls the active tab before the current one so we 
				//know on which (no longer active) tab the close button can be hidden again
				handleTabCloseButtons(t, tabcount - 2, ui_image->tabWidget_image->currentIndex());
				handleTabCloseButtons(t, lastIndexTab_Image, -1);

				//for the sake of accesibility of this tab position from other classes.
				main->Gui::tabRecord.imgIndex = ui_image->tabWidget_image->currentIndex();
			}else{
				if (ui_image->tabWidget_image->count() > 2){
					handleTabCloseButtons(t, ui_image->tabWidget_image->currentIndex(), index[0]);
				}
		
				main->Gui::tabRecord.imgIndex = ui_image->tabWidget_image->currentIndex();
				lastIndexTab_Image = ui_image->tabWidget_image->currentIndex();
			}

		}

	return;
}

//==============================================================================
// void TabHandling::closeWidget_table(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
//------------------------------------------------------------------------------
//==============================================================================
void TabHandling::closeWidget_table(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
{
		//sender()->disconnect();
		if ((obj == ui_table->tabWidget_table) && QString::compare(msg, "close") == 0) {
			QString title = ui_table->tabWidget_table->tabText(index[0]);
			QTabBar *t = qobject_cast<QTabBar*>(ui_table->tabWidget_table->findChild<QTabBar *>());
			if (QString::compare(title, "+") == 0) {
				return;
			}else{

				//delete ui_table->tabWidget_table->widget(index[0]);
			
				//remove tab at position index[0] and store in orderTabs_Table
				ui_table->tabWidget_table->removeTab(index[0]);
				TabHandling::orderTabs_Table = toTab.sub(index[0], TabHandling::orderTabs_Table);
				ui_table->tabWidget_table->setCurrentIndex(index[0]-1);

				if (ui_table->tabWidget_table->count() == 2){
					handleTabCloseButtons(t, ui_table->tabWidget_table->currentIndex(), -1);
					main->Gui::tabRecord.tableIndex = ui_table->tabWidget_table->currentIndex();
				}else{
					handleTabCloseButtons(t, -1, ui_table->tabWidget_table->currentIndex());
					lastIndexTab_Table = ui_table->tabWidget_table->currentIndex();
					main->Gui::tabRecord.tableIndex = lastIndexTab_Table;
				}
			}
		}
	
	return;
}

//==============================================================================
// void TabHandling::closeWidget_plot(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
//------------------------------------------------------------------------------
//==============================================================================
void TabHandling::closeWidget_plot(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
{
		//sender()->disconnect();
		if ((obj == ui_plot->tabWidget_plotter) && QString::compare(msg, "close") == 0) {
			QString title = ui_plot->tabWidget_plotter->tabText(index[0]);
			QTabBar *t = qobject_cast<QTabBar*>(ui_plot->tabWidget_plotter->findChild<QTabBar *>());
			if (QString::compare(title, "+") == 0) {
				return;
			}else{
				//Qt is picky with this, so we make sure we operate exactly on the tabs(read: widgets) we want to 
				ui_plot->tabWidget_plotter->setCurrentIndex(index[0]);
				ui_plot->tabWidget_plotter->removeTab(index[0]);
				ui_plot->tabWidget_plotter->setCurrentIndex(index[0] - 1);

				//update our state vectors
				TabHandling::orderTabs_Plot = toTab.sub(index[0], TabHandling::orderTabs_Plot);
				main->PlotGui::removeGuisettings(index[0]);
				main->PlotAttribute::removeVector(index[0]);

				//Button handling
				if (ui_plot->tabWidget_plotter->count() == 2){
					handleTabCloseButtons(t, ui_plot->tabWidget_plotter->currentIndex(), -1);
					main->Gui::tabRecord.plotIndex = ui_plot->tabWidget_plotter->currentIndex();
				}else{
					handleTabCloseButtons(t, -1, ui_plot->tabWidget_plotter->currentIndex());
					lastIndexTab_Plot = ui_plot->tabWidget_plotter->currentIndex();
					main->Gui::tabRecord.plotIndex = lastIndexTab_Plot;
				}
			}
		}

	return;
}

//==============================================================================
// void TabHandling::closeWidget_image(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
//------------------------------------------------------------------------------
//==============================================================================
void TabHandling::closeWidget_image(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
{

		if ((obj == ui_image->tabWidget_image) && QString::compare(msg, "close") == 0) {
			QString title = ui_image->tabWidget_image->tabText(index[0]);
			QTabBar *t = qobject_cast<QTabBar*>(ui_image->tabWidget_image->findChild<QTabBar *>());
			if (QString::compare(title, "+") == 0) {
				return;
			}
			else{
				//Qt is picky with this, so we make sure we operate exactly on the tabs(read: widgets) we want to 
				ui_image->tabWidget_image->setCurrentIndex(index[0]);
				ui_image->tabWidget_image->removeTab(index[0]);
				ui_image->tabWidget_image->setCurrentIndex(index[0] - 1);

				//update our state vectors
				TabHandling::orderTabs_Image = toTab.sub(index[0], TabHandling::orderTabs_Image);
				main->ImageGui::removeGuisettings(index[0]);
				main->ImageAttribute::removeVector(index[0]);

				//Button handling
				if (ui_image->tabWidget_image->count() == 2){
					handleTabCloseButtons(t, ui_image->tabWidget_image->currentIndex(), -1);
					main->Gui::tabRecord.imgIndex = ui_image->tabWidget_image->currentIndex();
				}
				else{
					handleTabCloseButtons(t, -1, ui_image->tabWidget_image->currentIndex());
					lastIndexTab_Image = ui_image->tabWidget_image->currentIndex();
					main->Gui::tabRecord.imgIndex = lastIndexTab_Image;
				}
			}

		}

	return;
}

//==============================================================================
// void TabHandling::moveWidget_table(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
//------------------------------------------------------------------------------
//==============================================================================
void TabHandling::moveWidget_table(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
{
		ind_tab_movedTo = index[0];
		ind_tab_movedFrom = index[1];

		if ((obj == ui_table->tabWidget_table) && QString::compare(msg, "move") == 0) {
			QTabBar *t = qobject_cast<QTabBar*>(ui_table->tabWidget_table->findChild<QTabBar *>());
			// we don't wat to switch places with the "+" tab

			if (ind_tab_movedTo >= ui_table->tabWidget_table->count() -1){		
				ui_table->tabWidget_table->tabBar()->blockSignals(true);
				ui_table->tabWidget_table->tabBar()->moveTab(ind_tab_movedFrom, ind_tab_movedTo);
				ui_table->tabWidget_table->tabBar()->blockSignals(false);
				main->Gui::tabRecord.tableIndex = ind_tab_movedFrom;

			} else {
				//swap tabs at ind_tab_movedFrom/ind_tab_movedTo and store in orderTabs_Table
				TabHandling::orderTabs_Table = toTab.swap(ind_tab_movedTo, ind_tab_movedFrom, TabHandling::orderTabs_Table);
				handleTabCloseButtons(t, ind_tab_movedFrom, ind_tab_movedTo);
				lastIndexTab_Table = index[2];
				main->Gui::tabRecord.tableIndex = ind_tab_movedTo;
			}

			//ui_table->tabWidget_table->currentWidget()->show();
			//auto wgt = ui_table->tabWidget_table->currentWidget();
			//wgt->show();
			
			/*
			int ii = 0;
			while (ii < orderTabs_Table.size()){
				cout << orderTabs_Table[ii] << endl;
				ii++;
			}
			cout << " ---------- " << endl;
			*/
			
		}
	return;
}

//==============================================================================
// void TabHandling::moveWidget_plot(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
//------------------------------------------------------------------------------
//==============================================================================
void TabHandling::moveWidget_plot(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
{
		ind_tab_movedTo = index[0];
		ind_tab_movedFrom = index[1];

		if ((obj == ui_plot->tabWidget_plotter) && QString::compare(msg, "move") == 0) {
			QTabBar *t = qobject_cast<QTabBar*>(ui_plot->tabWidget_plotter->findChild<QTabBar *>());
			// we don't wat to switch places with the "+" tab
			if (ind_tab_movedTo >= ui_plot->tabWidget_plotter->count() - 1){
				ui_plot->tabWidget_plotter->tabBar()->blockSignals(true);
				ui_plot->tabWidget_plotter->tabBar()->moveTab(ind_tab_movedFrom, ind_tab_movedTo);
				ui_plot->tabWidget_plotter->tabBar()->blockSignals(false);
				main->Gui::tabRecord.plotIndex = ind_tab_movedFrom;
			} else {
				lastIndexTab_Plot = ind_tab_movedTo;
				main->Gui::tabRecord.plotIndex = ind_tab_movedFrom;
				//swap tabs at ind_tab_movedFrom/ind_tab_movedTo and store in orderTabs_Plot
				TabHandling::orderTabs_Plot = toTab.swap(ind_tab_movedTo, ind_tab_movedFrom, TabHandling::orderTabs_Plot);
				handleTabCloseButtons(t, ind_tab_movedFrom, ind_tab_movedTo);
			}
		}

	return;
}

//==============================================================================
// void TabHandling::moveWidget_image(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
//------------------------------------------------------------------------------
//==============================================================================
void TabHandling::moveWidget_image(QWidget* widget, QObject* obj, QString msg, QVector<int> index)
{
		ind_tab_movedTo = index[0];
		ind_tab_movedFrom = index[1];
	
		if ((obj == ui_image->tabWidget_image) && QString::compare(msg, "move") == 0) {
			QTabBar *t = qobject_cast<QTabBar*>(ui_image->tabWidget_image->findChild<QTabBar *>());
			// we don't wat to switch places with the "+" tab
			if (ind_tab_movedTo >= ui_image->tabWidget_image->count() - 1){
				ui_image->tabWidget_image->tabBar()->blockSignals(true);
				ui_image->tabWidget_image->tabBar()->moveTab(ind_tab_movedFrom, ind_tab_movedTo);
				ui_image->tabWidget_image->tabBar()->blockSignals(false);
				main->Gui::tabRecord.imgIndex = ind_tab_movedFrom;
			} else {
				lastIndexTab_Image = ind_tab_movedTo;
				main->Gui::tabRecord.imgIndex = ind_tab_movedFrom;
				//swap tabs at ind_tab_movedFrom/ind_tab_movedTo and store in orderTabs_Image
				TabHandling::orderTabs_Image = toTab.swap(ind_tab_movedTo, ind_tab_movedFrom, TabHandling::orderTabs_Image);
				handleTabCloseButtons(t, ind_tab_movedFrom, ind_tab_movedTo);
			}

		}
	return;
}
