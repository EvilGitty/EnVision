#include "tableWidget.h"
#include "Base/envision.h"

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
TableWidget::TableWidget(EnVision *main) : QWidget(), ui_table(new Ui::EnVision_tableUI)
{
			ui_table->setupUi(this);
			this->main = main;

			TabHandling *tabhand = new TabHandling(main);
			tabhand->guiAccess();

			tab_x = 0;

			QObject::connect(ui_table->tabWidget_table, SIGNAL(currentChanged(int)), this, SLOT(getCurrentTabIndex(int)), Qt::UniqueConnection);
			QObject::connect(ui_table->tabWidget_table, SIGNAL(tabBarClicked(int)), this, SLOT(activateTab(int)), Qt::UniqueConnection);
			QObject::connect(ui_table->tabWidget_table->tabBar(), SIGNAL(tabMoved(int, int)), this, SLOT(moveTab(int, int)), Qt::UniqueConnection);
			QObject::connect(ui_table->tabWidget_table, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)), Qt::UniqueConnection);

			QObject::connect(this, SIGNAL(activeTab_Signal(QWidget*, QObject*, QString, QVector<int>)), main->tabhand, SLOT(addWidget_table(QWidget*, QObject*, QString, QVector<int>)), Qt::UniqueConnection);
			QObject::connect(this, SIGNAL(activeTab_Signal(QWidget*, QObject*, QString, QVector<int>)), main->tabhand, SLOT(closeWidget_table(QWidget*, QObject*, QString, QVector<int>)), Qt::UniqueConnection);
			QObject::connect(this, SIGNAL(activeTab_Signal(QWidget*, QObject*, QString, QVector<int>)), main->tabhand, SLOT(moveWidget_table(QWidget*, QObject*, QString, QVector<int>)), Qt::UniqueConnection);

			QObject::connect(this, SIGNAL(attachWidget_Signal(QWidget*, QString)), main, SLOT(attachWidget(QWidget*, QString)), Qt::UniqueConnection);

			QTabBar *t = qobject_cast<QTabBar*>(ui_table->tabWidget_table->findChild<QTabBar *>());
			t->tabButton(0, QTabBar::RightSide)->hide();
			t->tabButton(1, QTabBar::RightSide)->hide();
			t->installEventFilter(this);

			//
			//it's probably still a widget, thats why this is still here
			QMenuBar* menuBar = new QMenuBar();
			QMenu *fileMenu = new QMenu("Menu");
			menuBar->addMenu(fileMenu);
			attach = fileMenu->addAction("Attach");
			detach = fileMenu->addAction("Detach");
			this->layout()->setMenuBar(menuBar);
			//
			QObject::connect(attach, SIGNAL(triggered()), this, SLOT(attachWidget()));
			QObject::connect(detach, SIGNAL(triggered()), this, SLOT(detachWidget()));
			
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
TableWidget::~TableWidget()
{

}

//==============================================================================
// Ui::EnVision_baseUI* TableWidget::getBaseUI(void)
//------------------------------------------------------------------------------
//==============================================================================
Ui::EnVision_tableUI* TableWidget::getTableUI(void)
{
	return ui_table;
}

//==============================================================================
// int TableWidget::getCurrentTabIndex()
//------------------------------------------------------------------------------
//==============================================================================
int TableWidget::getCurrentTabIndex(int ind)
{
	return ui_table->tabWidget_table->currentIndex();
}

//==============================================================================
// int TableWidget::missingTabIndex()
//------------------------------------------------------------------------------
// To calculate the next tab index
//==============================================================================
int TableWidget::missingTabIndex()
{
		int n = 0;
		// The sorted vector that contains the tab positions is 
		//searched for missing//deleted tabs - the resulting value
		//will be the next distinct "Object name" for the widget
		//to clearly identify it
		QVector<int> sort = TabHandling::orderTabs_Table;
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
// QWidget* TableWidget::constructWorksheet(void)
//------------------------------------------------------------------------------
//==============================================================================
QWidget* TableWidget::constructWorksheet(void)
{
		tab_x = new QWidget();
		tab_x->setObjectName(QStringLiteral("tab_table"));
		QGridLayout* gridLayout = new QGridLayout(tab_x);
		gridLayout->setSpacing(6);
		gridLayout->setContentsMargins(11, 11, 11, 11);
		gridLayout->setObjectName(QStringLiteral("gridLayout"));

		workspaceTableWidget = new QTableWidget(tab_x);
		if (workspaceTableWidget->columnCount() < 1000){
			workspaceTableWidget->setColumnCount(1000);
		}
		if (workspaceTableWidget->rowCount() < 1000){
			workspaceTableWidget->setRowCount(1000);
		}

		QTableWidgetItem* __qtablewidgetitem = new QTableWidgetItem();
		workspaceTableWidget->setItem(0, 0, __qtablewidgetitem);
		QTableWidgetItem* __qtablewidgetitem1 = new QTableWidgetItem();
		workspaceTableWidget->setItem(0, 1, __qtablewidgetitem1);

		//the next tab number is calculated to build an object name
		main->tabhand->missingIndexTab_Table = missingTabIndex();
		workspaceTableWidget->setObjectName("table" + QString::number(main->tabhand->missingIndexTab_Table + 1));

		workspaceTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		workspaceTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		workspaceTableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
		workspaceTableWidget->setGridStyle(Qt::SolidLine);
		workspaceTableWidget->setRowCount(1000);
		workspaceTableWidget->setColumnCount(1000);
		workspaceTableWidget->horizontalHeader()->setVisible(true);
		workspaceTableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
		workspaceTableWidget->horizontalHeader()->setStretchLastSection(false);
		workspaceTableWidget->verticalHeader()->setCascadingSectionResizes(false);
		gridLayout->addWidget(workspaceTableWidget, 0, 0, 1, 1);

		QTableWidgetItem* ___qtablewidgetitem = workspaceTableWidget->item(0, 0);
		___qtablewidgetitem->setText(QApplication::translate("EnVision_baseUI", "ID_Labelname", 0));
		QTableWidgetItem* ___qtablewidgetitem1 = workspaceTableWidget->item(0, 1);
		___qtablewidgetitem1->setText(QApplication::translate("EnVision_baseUI", "ID_Number", 0));

		//make this the currently active widget
		ui_table->tabWidget_table->setCurrentWidget(workspaceTableWidget);
		main->Gui::tabRecord.currentTable = workspaceTableWidget;

	return tab_x;
}

//==============================================================================
// void TableWidget::reserveTable()
//------------------------------------------------------------------------------
//==============================================================================
void TableWidget::reserveTable()
{
	return;
}

//==============================================================================
// void TableWidget::activateTab(int index)
//------------------------------------------------------------------------------
//==============================================================================
void TableWidget::activateTab(int index)
{
		if (index > -1){
			//=============================================================================
			//debug
			//cout << "index: " << index << endl;
			//cout << "count: " << ui_table->tabWidget_table->count() << endl;
			//cout << "currentIndex: " << ui_table->tabWidget_table->currentIndex() << endl;

			tab_x = ui_table->tabWidget_table->widget(index);

			if (index == (ui_table->tabWidget_table->count() - 1)){
				tab_x = constructWorksheet();
				reserveTable();
			}

			QVector<int> i;
			i.push_back(index);

			emit activeTab_Signal(tab_x, ui_table->tabWidget_table, "add", i);

			index = TabHandling::orderTabs_Table[index];

			//get pointer to the QCustomPlot related to the current tab widget
			QList<QTableWidget *> list_tables1 = ui_table->tabWidget_table->findChildren<QTableWidget *>("table" + QString::number(index));
			main->Gui::tabRecord.currentTable = list_tables1[0];
			main->Gui::tabRecord.tableIndex = index - 1;

			/*
			cout << " # " << endl;
			weakConnect(this, &TableWidget::sig, this, &TableWidget::slo);
			emit TableWidget::sig(2);
			emit TableWidget::sig(3);
			emit TableWidget::sig(4);
			emit TableWidget::sig(5);
			*/
		}
	return;
}

//==============================================================================
// void TableWidget::closeTab(int index)
//------------------------------------------------------------------------------
//==============================================================================
void TableWidget::closeTab(int index)
{
		QVector<int> i;
		i.push_back(index);

		emit activeTab_Signal(NULL, ui_table->tabWidget_table, "close", i);

	return;
}

//==============================================================================
//void TableWidget::moveTab(int to, int from)
//------------------------------------------------------------------------------
//==============================================================================
void TableWidget::moveTab(int to, int from)
{
		QVector<int> i;
		i.push_back(to);
		i.push_back(from);
		i.push_back(to);

		emit activeTab_Signal(NULL, ui_table->tabWidget_table, "move", i);

	return;
}

//==============================================================================
// void TableWidget::attachWidget()
//------------------------------------------------------------------------------
//==============================================================================
void TableWidget::attachWidget()
{
		emit attachWidget_Signal(this, "Data");	
	return;
}

//==============================================================================
// void TableWidget::detachWidget()
//------------------------------------------------------------------------------
//==============================================================================
void TableWidget::detachWidget()
{
		main->detachWidget();
	return;
}

//==============================================================================
// bool TableWidget::eventFilter(QObject *o, QEvent *e)
//------------------------------------------------------------------------------
//==============================================================================
bool TableWidget::eventFilter(QObject *o, QEvent *e)
{
		//this is just blocking an annoying wheel event on the tabbar
		//that causes a switching of tabs
		if (e->type() == QEvent::Wheel)
		{
			//qDebug() << "Wheel event blocked";
			return true;
		}
	return 0;
}
