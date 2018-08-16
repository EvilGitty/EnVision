/********************************************************************************
** Form generated from reading UI file 'envision.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENVISION_H
#define UI_ENVISION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EnVision_baseUI
{
public:
    QAction *actionCascade;
    QAction *actionTile;
    QAction *actionOverview;
    QAction *actionColorma;
    QAction *actionRotate;
    QAction *actionZoom;
    QAction *actionPan;
    QAction *actionExit;
    QAction *actionSave_state;
    QAction *actionSwitchTileOrCascade;
    QAction *actionToggleDockWidget03;
    QAction *actionToggleDockWidget02;
    QAction *actionToggleDockWidget01;
    QAction *actionToggleImageWidget;
    QAction *actionToggleTableWidget;
    QAction *actionTogglePlotWidget;
    QAction *actionReload_state;
    QAction *actionToggleCubeWidget;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page_Maintenance;
    QGridLayout *gridLayout_9;
    QWidget *page_Data;
    QGridLayout *gridLayout_2;
    QMdiArea *mdiArea;
    QWidget *Plotter;
    QGridLayout *gridLayout_3;
    QWidget *Data;
    QGridLayout *gridLayout_4;
    QWidget *Cube;
    QGridLayout *gridLayout_8;
    QWidget *Image;
    QGridLayout *gridLayout_11;
    QMenuBar *menuBar;
    QMenu *menuImport;
    QMenu *menuExport;
    QMenu *menuView;
    QMenu *menuWork_on;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QDockWidget *dockWidget_01;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_5;
    QDockWidget *dockWidget_02;
    QWidget *dockWidgetContents_2;
    QGridLayout *gridLayout_10;
    QDockWidget *dockWidget_03;
    QWidget *dockWidgetContents_3;
    QGridLayout *gridLayout_6;
    QTabWidget *tabWidget_filedialog;
    QWidget *tab_2;
    QGridLayout *gridLayout_7;
    QSplitter *splitter;
    QTextBrowser *textBrowser;
    QListWidget *listWidget_term;

    void setupUi(QMainWindow *EnVision_baseUI)
    {
        if (EnVision_baseUI->objectName().isEmpty())
            EnVision_baseUI->setObjectName(QStringLiteral("EnVision_baseUI"));
        EnVision_baseUI->resize(1347, 1206);
        EnVision_baseUI->setDocumentMode(true);
        EnVision_baseUI->setDockNestingEnabled(true);
        actionCascade = new QAction(EnVision_baseUI);
        actionCascade->setObjectName(QStringLiteral("actionCascade"));
        actionTile = new QAction(EnVision_baseUI);
        actionTile->setObjectName(QStringLiteral("actionTile"));
        actionOverview = new QAction(EnVision_baseUI);
        actionOverview->setObjectName(QStringLiteral("actionOverview"));
        actionColorma = new QAction(EnVision_baseUI);
        actionColorma->setObjectName(QStringLiteral("actionColorma"));
        actionRotate = new QAction(EnVision_baseUI);
        actionRotate->setObjectName(QStringLiteral("actionRotate"));
        actionZoom = new QAction(EnVision_baseUI);
        actionZoom->setObjectName(QStringLiteral("actionZoom"));
        actionPan = new QAction(EnVision_baseUI);
        actionPan->setObjectName(QStringLiteral("actionPan"));
        actionExit = new QAction(EnVision_baseUI);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSave_state = new QAction(EnVision_baseUI);
        actionSave_state->setObjectName(QStringLiteral("actionSave_state"));
        actionSwitchTileOrCascade = new QAction(EnVision_baseUI);
        actionSwitchTileOrCascade->setObjectName(QStringLiteral("actionSwitchTileOrCascade"));
        actionSwitchTileOrCascade->setCheckable(false);
        actionSwitchTileOrCascade->setChecked(false);
        actionToggleDockWidget03 = new QAction(EnVision_baseUI);
        actionToggleDockWidget03->setObjectName(QStringLiteral("actionToggleDockWidget03"));
        actionToggleDockWidget03->setCheckable(true);
        actionToggleDockWidget03->setChecked(true);
        actionToggleDockWidget02 = new QAction(EnVision_baseUI);
        actionToggleDockWidget02->setObjectName(QStringLiteral("actionToggleDockWidget02"));
        actionToggleDockWidget02->setCheckable(true);
        actionToggleDockWidget02->setChecked(true);
        actionToggleDockWidget01 = new QAction(EnVision_baseUI);
        actionToggleDockWidget01->setObjectName(QStringLiteral("actionToggleDockWidget01"));
        actionToggleDockWidget01->setCheckable(true);
        actionToggleDockWidget01->setChecked(true);
        actionToggleImageWidget = new QAction(EnVision_baseUI);
        actionToggleImageWidget->setObjectName(QStringLiteral("actionToggleImageWidget"));
        actionToggleImageWidget->setCheckable(true);
        actionToggleTableWidget = new QAction(EnVision_baseUI);
        actionToggleTableWidget->setObjectName(QStringLiteral("actionToggleTableWidget"));
        actionToggleTableWidget->setCheckable(true);
        actionToggleTableWidget->setChecked(true);
        actionTogglePlotWidget = new QAction(EnVision_baseUI);
        actionTogglePlotWidget->setObjectName(QStringLiteral("actionTogglePlotWidget"));
        actionTogglePlotWidget->setCheckable(true);
        actionTogglePlotWidget->setChecked(true);
        actionReload_state = new QAction(EnVision_baseUI);
        actionReload_state->setObjectName(QStringLiteral("actionReload_state"));
        actionToggleCubeWidget = new QAction(EnVision_baseUI);
        actionToggleCubeWidget->setObjectName(QStringLiteral("actionToggleCubeWidget"));
        actionToggleCubeWidget->setCheckable(true);
        actionToggleCubeWidget->setChecked(true);
        centralWidget = new QWidget(EnVision_baseUI);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setLineWidth(0);
        page_Maintenance = new QWidget();
        page_Maintenance->setObjectName(QStringLiteral("page_Maintenance"));
        gridLayout_9 = new QGridLayout(page_Maintenance);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        stackedWidget->addWidget(page_Maintenance);
        page_Data = new QWidget();
        page_Data->setObjectName(QStringLiteral("page_Data"));
        gridLayout_2 = new QGridLayout(page_Data);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        mdiArea = new QMdiArea(page_Data);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));
        mdiArea->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
        mdiArea->setLineWidth(0);
        mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mdiArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        mdiArea->setBackground(brush);
        mdiArea->setViewMode(QMdiArea::TabbedView);
        mdiArea->setDocumentMode(true);
        mdiArea->setTabsMovable(true);
        mdiArea->setTabShape(QTabWidget::Triangular);
        Plotter = new QWidget();
        Plotter->setObjectName(QStringLiteral("Plotter"));
        gridLayout_3 = new QGridLayout(Plotter);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        mdiArea->addSubWindow(Plotter);
        Data = new QWidget();
        Data->setObjectName(QStringLiteral("Data"));
        gridLayout_4 = new QGridLayout(Data);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        mdiArea->addSubWindow(Data);
        Cube = new QWidget();
        Cube->setObjectName(QStringLiteral("Cube"));
        gridLayout_8 = new QGridLayout(Cube);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        mdiArea->addSubWindow(Cube);
        Image = new QWidget();
        Image->setObjectName(QStringLiteral("Image"));
        gridLayout_11 = new QGridLayout(Image);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        mdiArea->addSubWindow(Image);

        gridLayout_2->addWidget(mdiArea, 0, 0, 1, 1);

        stackedWidget->addWidget(page_Data);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);

        EnVision_baseUI->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EnVision_baseUI);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1347, 21));
        menuImport = new QMenu(menuBar);
        menuImport->setObjectName(QStringLiteral("menuImport"));
        menuExport = new QMenu(menuBar);
        menuExport->setObjectName(QStringLiteral("menuExport"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuWork_on = new QMenu(menuBar);
        menuWork_on->setObjectName(QStringLiteral("menuWork_on"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        EnVision_baseUI->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EnVision_baseUI);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        EnVision_baseUI->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(EnVision_baseUI);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EnVision_baseUI->setStatusBar(statusBar);
        toolBar = new QToolBar(EnVision_baseUI);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        EnVision_baseUI->addToolBar(Qt::LeftToolBarArea, toolBar);
        dockWidget_01 = new QDockWidget(EnVision_baseUI);
        dockWidget_01->setObjectName(QStringLiteral("dockWidget_01"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout_5 = new QGridLayout(dockWidgetContents);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        dockWidget_01->setWidget(dockWidgetContents);
        EnVision_baseUI->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_01);
        dockWidget_02 = new QDockWidget(EnVision_baseUI);
        dockWidget_02->setObjectName(QStringLiteral("dockWidget_02"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        gridLayout_10 = new QGridLayout(dockWidgetContents_2);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        dockWidget_02->setWidget(dockWidgetContents_2);
        EnVision_baseUI->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_02);
        dockWidget_03 = new QDockWidget(EnVision_baseUI);
        dockWidget_03->setObjectName(QStringLiteral("dockWidget_03"));
        dockWidget_03->setMinimumSize(QSize(191, 390));
        dockWidget_03->setAutoFillBackground(false);
        dockWidget_03->setFloating(false);
        dockWidget_03->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        gridLayout_6 = new QGridLayout(dockWidgetContents_3);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        tabWidget_filedialog = new QTabWidget(dockWidgetContents_3);
        tabWidget_filedialog->setObjectName(QStringLiteral("tabWidget_filedialog"));
        tabWidget_filedialog->setTabPosition(QTabWidget::South);
        tabWidget_filedialog->setTabShape(QTabWidget::Rounded);
        tabWidget_filedialog->setDocumentMode(true);
        tabWidget_filedialog->setTabBarAutoHide(false);
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_7 = new QGridLayout(tab_2);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        splitter = new QSplitter(tab_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        textBrowser = new QTextBrowser(splitter);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse|Qt::TextBrowserInteraction|Qt::TextEditable|Qt::TextEditorInteraction|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        splitter->addWidget(textBrowser);
        listWidget_term = new QListWidget(splitter);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget_term);
        __qlistwidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        listWidget_term->setObjectName(QStringLiteral("listWidget_term"));
        listWidget_term->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        listWidget_term->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        listWidget_term->setAlternatingRowColors(true);
        listWidget_term->setModelColumn(0);
        listWidget_term->setUniformItemSizes(false);
        listWidget_term->setSelectionRectVisible(true);
        splitter->addWidget(listWidget_term);

        gridLayout_7->addWidget(splitter, 0, 0, 1, 1);

        tabWidget_filedialog->addTab(tab_2, QString());

        gridLayout_6->addWidget(tabWidget_filedialog, 1, 0, 1, 1);

        dockWidget_03->setWidget(dockWidgetContents_3);
        EnVision_baseUI->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_03);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuImport->menuAction());
        menuBar->addAction(menuExport->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuWork_on->menuAction());
        menuView->addSeparator();
        menuView->addAction(actionCascade);
        menuView->addAction(actionTile);
        menuView->addAction(actionOverview);
        menuWork_on->addAction(actionColorma);
        menuWork_on->addAction(actionRotate);
        menuWork_on->addAction(actionZoom);
        menuWork_on->addAction(actionPan);
        menuFile->addAction(actionSave_state);
        menuFile->addAction(actionReload_state);
        menuFile->addAction(actionExit);
        toolBar->addAction(actionSwitchTileOrCascade);
        toolBar->addSeparator();
        toolBar->addAction(actionToggleDockWidget03);
        toolBar->addAction(actionToggleDockWidget02);
        toolBar->addAction(actionToggleDockWidget01);
        toolBar->addSeparator();
        toolBar->addAction(actionToggleTableWidget);
        toolBar->addAction(actionTogglePlotWidget);
        toolBar->addAction(actionToggleImageWidget);
        toolBar->addAction(actionToggleCubeWidget);
        toolBar->addSeparator();

        retranslateUi(EnVision_baseUI);

        stackedWidget->setCurrentIndex(1);
        tabWidget_filedialog->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EnVision_baseUI);
    } // setupUi

    void retranslateUi(QMainWindow *EnVision_baseUI)
    {
        EnVision_baseUI->setWindowTitle(QApplication::translate("EnVision_baseUI", "EnVision", nullptr));
        actionCascade->setText(QApplication::translate("EnVision_baseUI", "Cascade", nullptr));
        actionTile->setText(QApplication::translate("EnVision_baseUI", "Tile", nullptr));
        actionOverview->setText(QApplication::translate("EnVision_baseUI", "Overview", nullptr));
        actionColorma->setText(QApplication::translate("EnVision_baseUI", "Overlay", nullptr));
        actionRotate->setText(QApplication::translate("EnVision_baseUI", "Rotate", nullptr));
        actionZoom->setText(QApplication::translate("EnVision_baseUI", "Zoom", nullptr));
        actionPan->setText(QApplication::translate("EnVision_baseUI", "Pan", nullptr));
        actionExit->setText(QApplication::translate("EnVision_baseUI", "Exit", nullptr));
        actionSave_state->setText(QApplication::translate("EnVision_baseUI", "Save state", nullptr));
        actionSwitchTileOrCascade->setText(QApplication::translate("EnVision_baseUI", "Tab Layout", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSwitchTileOrCascade->setToolTip(QApplication::translate("EnVision_baseUI", "CTRL+T: Change Tab Layout", nullptr));
#endif // QT_NO_TOOLTIP
        actionToggleDockWidget03->setText(QApplication::translate("EnVision_baseUI", "File Explorer", nullptr));
#ifndef QT_NO_TOOLTIP
        actionToggleDockWidget03->setToolTip(QApplication::translate("EnVision_baseUI", "Hide/Show File Dialog", nullptr));
#endif // QT_NO_TOOLTIP
        actionToggleDockWidget02->setText(QApplication::translate("EnVision_baseUI", "DockWidget02", nullptr));
#ifndef QT_NO_TOOLTIP
        actionToggleDockWidget02->setToolTip(QApplication::translate("EnVision_baseUI", "Hide/Show Widget02", nullptr));
#endif // QT_NO_TOOLTIP
        actionToggleDockWidget01->setText(QApplication::translate("EnVision_baseUI", "DockWidget01", nullptr));
#ifndef QT_NO_TOOLTIP
        actionToggleDockWidget01->setToolTip(QApplication::translate("EnVision_baseUI", "Hide/Show Widget01", nullptr));
#endif // QT_NO_TOOLTIP
        actionToggleImageWidget->setText(QApplication::translate("EnVision_baseUI", "Show Image", nullptr));
#ifndef QT_NO_TOOLTIP
        actionToggleImageWidget->setToolTip(QApplication::translate("EnVision_baseUI", "Hide/Show Image", nullptr));
#endif // QT_NO_TOOLTIP
        actionToggleTableWidget->setText(QApplication::translate("EnVision_baseUI", "Show Data", nullptr));
#ifndef QT_NO_TOOLTIP
        actionToggleTableWidget->setToolTip(QApplication::translate("EnVision_baseUI", "Hide/Show Table", nullptr));
#endif // QT_NO_TOOLTIP
        actionTogglePlotWidget->setText(QApplication::translate("EnVision_baseUI", "Show Plotter", nullptr));
#ifndef QT_NO_TOOLTIP
        actionTogglePlotWidget->setToolTip(QApplication::translate("EnVision_baseUI", "Hide/Show Plot", nullptr));
#endif // QT_NO_TOOLTIP
        actionReload_state->setText(QApplication::translate("EnVision_baseUI", "Reload state", nullptr));
        actionToggleCubeWidget->setText(QApplication::translate("EnVision_baseUI", "Show Cube", nullptr));
#ifndef QT_NO_TOOLTIP
        actionToggleCubeWidget->setToolTip(QApplication::translate("EnVision_baseUI", "Hide/Show Cube", nullptr));
#endif // QT_NO_TOOLTIP
        Plotter->setWindowTitle(QApplication::translate("EnVision_baseUI", "Plotter", nullptr));
        Data->setWindowTitle(QApplication::translate("EnVision_baseUI", "Data", nullptr));
        Cube->setWindowTitle(QApplication::translate("EnVision_baseUI", "Cube", nullptr));
        Image->setWindowTitle(QApplication::translate("EnVision_baseUI", "Image", nullptr));
        menuImport->setTitle(QApplication::translate("EnVision_baseUI", "Import", nullptr));
        menuExport->setTitle(QApplication::translate("EnVision_baseUI", "Export", nullptr));
        menuView->setTitle(QApplication::translate("EnVision_baseUI", "View", nullptr));
        menuWork_on->setTitle(QApplication::translate("EnVision_baseUI", "Work on", nullptr));
        menuFile->setTitle(QApplication::translate("EnVision_baseUI", "File", nullptr));
        mainToolBar->setWindowTitle(QApplication::translate("EnVision_baseUI", "menuBar_01", nullptr));
        toolBar->setWindowTitle(QApplication::translate("EnVision_baseUI", "toolBar_Left", nullptr));
        dockWidget_01->setWindowTitle(QApplication::translate("EnVision_baseUI", "DockWidget01", nullptr));
        dockWidget_02->setWindowTitle(QApplication::translate("EnVision_baseUI", "DockWidget02", nullptr));
#ifndef QT_NO_ACCESSIBILITY
        dockWidget_03->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        dockWidget_03->setWindowTitle(QApplication::translate("EnVision_baseUI", "File Explorer", nullptr));
        textBrowser->setDocumentTitle(QApplication::translate("EnVision_baseUI", "THIS IS A TEST", nullptr));
        textBrowser->setPlaceholderText(QApplication::translate("EnVision_baseUI", "LOL", nullptr));

        const bool __sortingEnabled = listWidget_term->isSortingEnabled();
        listWidget_term->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_term->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("EnVision_baseUI", "gwegwgwe", nullptr));
        listWidget_term->setSortingEnabled(__sortingEnabled);

        tabWidget_filedialog->setTabText(tabWidget_filedialog->indexOf(tab_2), QApplication::translate("EnVision_baseUI", "Terminal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EnVision_baseUI: public Ui_EnVision_baseUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENVISION_H
