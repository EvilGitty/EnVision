/********************************************************************************
** Form generated from reading UI file 'image_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGE_WIDGET_H
#define UI_IMAGE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_EnVision_imageUI
{
public:
    QAction *actionAttach;
    QAction *actionDetach;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget_image;
    QWidget *tab_image;
    QGridLayout *gridLayout_2;
    QMdiArea *mdiArea;
    QWidget *subwindow;
    QGridLayout *gridLayout_4;
    QCustomPlot *imageplot;
    QGridLayout *gridLayout_3;
    QGraphicsView *image;
    QWidget *addTab_image;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout;
    QLabel *label_gamma;
    QSlider *hSlider_gamma;
    QLabel *label_contrast;
    QSlider *hSlider_contrast;
    QLabel *label_brightness;
    QSlider *hSlider_brightness;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_resetZoom;
    QPushButton *pushButton_startPos;
    QSlider *hSlider_channel;
    QMenuBar *menubar;
    QMenu *menuattach;
    QStatusBar *statusbar;
    QDockWidget *dockWidget_thumbnail;
    QWidget *dockWidgetContents_3;
    QGridLayout *gridLayout_7;
    QTabWidget *tabWidget;
    QWidget *SpectralPos;
    QGridLayout *gridLayout_9;
    QListWidget *listWidget_spectralIndex;
    QPushButton *pushButton_thumbnailFolder;
    QDockWidget *dockWidget_operation;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_resetBrightness;
    QCheckBox *checkBox_saturation;
    QCheckBox *checkBox_negative;
    QCheckBox *checkBox_imgLoadSelect;
    QComboBox *comboBox_ImageColormap;
    QComboBox *comboBox_plotGeometry;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox;
    QSpinBox *spinBox;
    QRadioButton *radioButton_draw;
    QRadioButton *radioButton_scroll;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QSlider *hSlider_range_128_255;
    QSpinBox *spinBox_hstep;
    QSpinBox *spinBox_vstep;
    QSlider *hSlider_range_0_127;
    QButtonGroup *buttonGroup_mouseInteraction;

    void setupUi(QMainWindow *EnVision_imageUI)
    {
        if (EnVision_imageUI->objectName().isEmpty())
            EnVision_imageUI->setObjectName(QStringLiteral("EnVision_imageUI"));
        EnVision_imageUI->resize(2000, 964);
        actionAttach = new QAction(EnVision_imageUI);
        actionAttach->setObjectName(QStringLiteral("actionAttach"));
        actionDetach = new QAction(EnVision_imageUI);
        actionDetach->setObjectName(QStringLiteral("actionDetach"));
        centralwidget = new QWidget(EnVision_imageUI);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget_image = new QTabWidget(centralwidget);
        tabWidget_image->setObjectName(QStringLiteral("tabWidget_image"));
        tabWidget_image->setTabPosition(QTabWidget::South);
        tabWidget_image->setTabShape(QTabWidget::Rounded);
        tabWidget_image->setDocumentMode(true);
        tabWidget_image->setTabsClosable(true);
        tabWidget_image->setMovable(true);
        tabWidget_image->setTabBarAutoHide(false);
        tab_image = new QWidget();
        tab_image->setObjectName(QStringLiteral("tab_image"));
        gridLayout_2 = new QGridLayout(tab_image);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        mdiArea = new QMdiArea(tab_image);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));
        mdiArea->setLineWidth(0);
        mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        mdiArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        mdiArea->setBackground(brush);
        mdiArea->setViewMode(QMdiArea::SubWindowView);
        mdiArea->setDocumentMode(true);
        mdiArea->setTabsClosable(false);
        mdiArea->setTabShape(QTabWidget::Triangular);
        subwindow = new QWidget();
        subwindow->setObjectName(QStringLiteral("subwindow"));
        gridLayout_4 = new QGridLayout(subwindow);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        imageplot = new QCustomPlot(subwindow);
        imageplot->setObjectName(QStringLiteral("imageplot"));
        imageplot->setMinimumSize(QSize(50, 50));
        gridLayout_3 = new QGridLayout(imageplot);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(16, 0, 0, 16);
        image = new QGraphicsView(imageplot);
        image->setObjectName(QStringLiteral("image"));
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
        image->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing|QGraphicsView::DontSavePainterState);

        gridLayout_3->addWidget(image, 0, 0, 1, 1);


        gridLayout_4->addWidget(imageplot, 0, 0, 1, 1);

        mdiArea->addSubWindow(subwindow);

        gridLayout_2->addWidget(mdiArea, 0, 0, 1, 1);

        tabWidget_image->addTab(tab_image, QString());
        addTab_image = new QWidget();
        addTab_image->setObjectName(QStringLiteral("addTab_image"));
        gridLayout_5 = new QGridLayout(addTab_image);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        tabWidget_image->addTab(addTab_image, QString());

        gridLayout->addWidget(tabWidget_image, 1, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_gamma = new QLabel(centralwidget);
        label_gamma->setObjectName(QStringLiteral("label_gamma"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_gamma->sizePolicy().hasHeightForWidth());
        label_gamma->setSizePolicy(sizePolicy);
        label_gamma->setMinimumSize(QSize(20, 10));
        label_gamma->setMaximumSize(QSize(30, 30));
        label_gamma->setScaledContents(true);

        verticalLayout->addWidget(label_gamma);

        hSlider_gamma = new QSlider(centralwidget);
        hSlider_gamma->setObjectName(QStringLiteral("hSlider_gamma"));
        sizePolicy.setHeightForWidth(hSlider_gamma->sizePolicy().hasHeightForWidth());
        hSlider_gamma->setSizePolicy(sizePolicy);
        hSlider_gamma->setMinimumSize(QSize(20, 0));
        hSlider_gamma->setMaximumSize(QSize(20, 16777215));
        hSlider_gamma->setMaximum(100);
        hSlider_gamma->setValue(100);
        hSlider_gamma->setOrientation(Qt::Vertical);
        hSlider_gamma->setInvertedAppearance(false);
        hSlider_gamma->setInvertedControls(false);

        verticalLayout->addWidget(hSlider_gamma);

        label_contrast = new QLabel(centralwidget);
        label_contrast->setObjectName(QStringLiteral("label_contrast"));
        label_contrast->setMinimumSize(QSize(20, 0));
        label_contrast->setMaximumSize(QSize(20, 30));
        label_contrast->setScaledContents(true);

        verticalLayout->addWidget(label_contrast);

        hSlider_contrast = new QSlider(centralwidget);
        hSlider_contrast->setObjectName(QStringLiteral("hSlider_contrast"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(hSlider_contrast->sizePolicy().hasHeightForWidth());
        hSlider_contrast->setSizePolicy(sizePolicy1);
        hSlider_contrast->setMinimumSize(QSize(20, 20));
        hSlider_contrast->setMaximumSize(QSize(20, 16777215));
        hSlider_contrast->setMinimum(-100);
        hSlider_contrast->setMaximum(100);
        hSlider_contrast->setOrientation(Qt::Vertical);
        hSlider_contrast->setTickPosition(QSlider::NoTicks);
        hSlider_contrast->setTickInterval(20);

        verticalLayout->addWidget(hSlider_contrast);

        label_brightness = new QLabel(centralwidget);
        label_brightness->setObjectName(QStringLiteral("label_brightness"));
        label_brightness->setMinimumSize(QSize(20, 0));
        label_brightness->setMaximumSize(QSize(20, 30));
        label_brightness->setScaledContents(true);

        verticalLayout->addWidget(label_brightness);

        hSlider_brightness = new QSlider(centralwidget);
        hSlider_brightness->setObjectName(QStringLiteral("hSlider_brightness"));
        sizePolicy1.setHeightForWidth(hSlider_brightness->sizePolicy().hasHeightForWidth());
        hSlider_brightness->setSizePolicy(sizePolicy1);
        hSlider_brightness->setMinimumSize(QSize(20, 0));
        hSlider_brightness->setMaximumSize(QSize(20, 16777215));
        hSlider_brightness->setMinimum(-100);
        hSlider_brightness->setMaximum(100);
        hSlider_brightness->setOrientation(Qt::Vertical);
        hSlider_brightness->setTickPosition(QSlider::NoTicks);
        hSlider_brightness->setTickInterval(20);

        verticalLayout->addWidget(hSlider_brightness);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_resetZoom = new QPushButton(centralwidget);
        pushButton_resetZoom->setObjectName(QStringLiteral("pushButton_resetZoom"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_resetZoom->sizePolicy().hasHeightForWidth());
        pushButton_resetZoom->setSizePolicy(sizePolicy2);
        pushButton_resetZoom->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(pushButton_resetZoom);

        pushButton_startPos = new QPushButton(centralwidget);
        pushButton_startPos->setObjectName(QStringLiteral("pushButton_startPos"));
        sizePolicy2.setHeightForWidth(pushButton_startPos->sizePolicy().hasHeightForWidth());
        pushButton_startPos->setSizePolicy(sizePolicy2);
        pushButton_startPos->setMaximumSize(QSize(30, 16777215));
        pushButton_startPos->setCheckable(true);

        horizontalLayout->addWidget(pushButton_startPos);

        hSlider_channel = new QSlider(centralwidget);
        hSlider_channel->setObjectName(QStringLiteral("hSlider_channel"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(hSlider_channel->sizePolicy().hasHeightForWidth());
        hSlider_channel->setSizePolicy(sizePolicy3);
        hSlider_channel->setMinimumSize(QSize(0, 20));
        hSlider_channel->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(hSlider_channel);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 3);

        EnVision_imageUI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EnVision_imageUI);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 2000, 21));
        menuattach = new QMenu(menubar);
        menuattach->setObjectName(QStringLiteral("menuattach"));
        EnVision_imageUI->setMenuBar(menubar);
        statusbar = new QStatusBar(EnVision_imageUI);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        EnVision_imageUI->setStatusBar(statusbar);
        dockWidget_thumbnail = new QDockWidget(EnVision_imageUI);
        dockWidget_thumbnail->setObjectName(QStringLiteral("dockWidget_thumbnail"));
        sizePolicy.setHeightForWidth(dockWidget_thumbnail->sizePolicy().hasHeightForWidth());
        dockWidget_thumbnail->setSizePolicy(sizePolicy);
        dockWidget_thumbnail->setMinimumSize(QSize(322, 415));
        dockWidget_thumbnail->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidget_thumbnail->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        gridLayout_7 = new QGridLayout(dockWidgetContents_3);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        tabWidget = new QTabWidget(dockWidgetContents_3);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setTabPosition(QTabWidget::South);
        SpectralPos = new QWidget();
        SpectralPos->setObjectName(QStringLiteral("SpectralPos"));
        gridLayout_9 = new QGridLayout(SpectralPos);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        listWidget_spectralIndex = new QListWidget(SpectralPos);
        listWidget_spectralIndex->setObjectName(QStringLiteral("listWidget_spectralIndex"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(listWidget_spectralIndex->sizePolicy().hasHeightForWidth());
        listWidget_spectralIndex->setSizePolicy(sizePolicy4);
        listWidget_spectralIndex->setLineWidth(0);
        listWidget_spectralIndex->setEditTriggers(QAbstractItemView::DoubleClicked);
        listWidget_spectralIndex->setProperty("showDropIndicator", QVariant(false));
        listWidget_spectralIndex->setIconSize(QSize(200, 200));
        listWidget_spectralIndex->setViewMode(QListView::IconMode);
        listWidget_spectralIndex->setModelColumn(0);
        listWidget_spectralIndex->setSortingEnabled(false);

        gridLayout_9->addWidget(listWidget_spectralIndex, 0, 0, 1, 1);

        tabWidget->addTab(SpectralPos, QString());

        gridLayout_7->addWidget(tabWidget, 1, 0, 1, 1);

        pushButton_thumbnailFolder = new QPushButton(dockWidgetContents_3);
        pushButton_thumbnailFolder->setObjectName(QStringLiteral("pushButton_thumbnailFolder"));

        gridLayout_7->addWidget(pushButton_thumbnailFolder, 0, 0, 1, 1);

        dockWidget_thumbnail->setWidget(dockWidgetContents_3);
        EnVision_imageUI->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_thumbnail);
        dockWidget_operation = new QDockWidget(EnVision_imageUI);
        dockWidget_operation->setObjectName(QStringLiteral("dockWidget_operation"));
        sizePolicy.setHeightForWidth(dockWidget_operation->sizePolicy().hasHeightForWidth());
        dockWidget_operation->setSizePolicy(sizePolicy);
        dockWidget_operation->setMinimumSize(QSize(790, 119));
        dockWidget_operation->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidget_operation->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout_6 = new QGridLayout(dockWidgetContents);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_resetBrightness = new QPushButton(dockWidgetContents);
        pushButton_resetBrightness->setObjectName(QStringLiteral("pushButton_resetBrightness"));
        pushButton_resetBrightness->setAutoDefault(false);
        pushButton_resetBrightness->setFlat(false);

        horizontalLayout_2->addWidget(pushButton_resetBrightness);

        checkBox_saturation = new QCheckBox(dockWidgetContents);
        checkBox_saturation->setObjectName(QStringLiteral("checkBox_saturation"));
        checkBox_saturation->setChecked(true);

        horizontalLayout_2->addWidget(checkBox_saturation);

        checkBox_negative = new QCheckBox(dockWidgetContents);
        checkBox_negative->setObjectName(QStringLiteral("checkBox_negative"));

        horizontalLayout_2->addWidget(checkBox_negative);

        checkBox_imgLoadSelect = new QCheckBox(dockWidgetContents);
        checkBox_imgLoadSelect->setObjectName(QStringLiteral("checkBox_imgLoadSelect"));

        horizontalLayout_2->addWidget(checkBox_imgLoadSelect);

        comboBox_ImageColormap = new QComboBox(dockWidgetContents);
        comboBox_ImageColormap->setObjectName(QStringLiteral("comboBox_ImageColormap"));
        comboBox_ImageColormap->setMaxVisibleItems(15);
        comboBox_ImageColormap->setMaxCount(150);
        comboBox_ImageColormap->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        comboBox_ImageColormap->setFrame(false);

        horizontalLayout_2->addWidget(comboBox_ImageColormap);

        comboBox_plotGeometry = new QComboBox(dockWidgetContents);
        comboBox_plotGeometry->setObjectName(QStringLiteral("comboBox_plotGeometry"));
        comboBox_plotGeometry->setMaximumSize(QSize(16777215, 16777215));
        comboBox_plotGeometry->setMaxVisibleItems(15);
        comboBox_plotGeometry->setMaxCount(150);
        comboBox_plotGeometry->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        comboBox_plotGeometry->setFrame(false);

        horizontalLayout_2->addWidget(comboBox_plotGeometry);


        gridLayout_6->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        checkBox = new QCheckBox(dockWidgetContents);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy5);

        horizontalLayout_3->addWidget(checkBox);

        spinBox = new QSpinBox(dockWidgetContents);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setMaximum(5);

        horizontalLayout_3->addWidget(spinBox);

        radioButton_draw = new QRadioButton(dockWidgetContents);
        buttonGroup_mouseInteraction = new QButtonGroup(EnVision_imageUI);
        buttonGroup_mouseInteraction->setObjectName(QStringLiteral("buttonGroup_mouseInteraction"));
        buttonGroup_mouseInteraction->addButton(radioButton_draw);
        radioButton_draw->setObjectName(QStringLiteral("radioButton_draw"));
        radioButton_draw->setChecked(false);

        horizontalLayout_3->addWidget(radioButton_draw);

        radioButton_scroll = new QRadioButton(dockWidgetContents);
        buttonGroup_mouseInteraction->addButton(radioButton_scroll);
        radioButton_scroll->setObjectName(QStringLiteral("radioButton_scroll"));
        radioButton_scroll->setChecked(true);

        horizontalLayout_3->addWidget(radioButton_scroll);

        checkBox_2 = new QCheckBox(dockWidgetContents);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        horizontalLayout_3->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(dockWidgetContents);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        sizePolicy5.setHeightForWidth(checkBox_3->sizePolicy().hasHeightForWidth());
        checkBox_3->setSizePolicy(sizePolicy5);

        horizontalLayout_3->addWidget(checkBox_3);

        hSlider_range_128_255 = new QSlider(dockWidgetContents);
        hSlider_range_128_255->setObjectName(QStringLiteral("hSlider_range_128_255"));
        sizePolicy5.setHeightForWidth(hSlider_range_128_255->sizePolicy().hasHeightForWidth());
        hSlider_range_128_255->setSizePolicy(sizePolicy5);
        hSlider_range_128_255->setMaximumSize(QSize(16777215, 16777215));
        hSlider_range_128_255->setMinimum(128);
        hSlider_range_128_255->setMaximum(255);
        hSlider_range_128_255->setValue(255);
        hSlider_range_128_255->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(hSlider_range_128_255);

        spinBox_hstep = new QSpinBox(dockWidgetContents);
        spinBox_hstep->setObjectName(QStringLiteral("spinBox_hstep"));
        sizePolicy2.setHeightForWidth(spinBox_hstep->sizePolicy().hasHeightForWidth());
        spinBox_hstep->setSizePolicy(sizePolicy2);
        spinBox_hstep->setMaximumSize(QSize(40, 16777215));
        spinBox_hstep->setFrame(false);
        spinBox_hstep->setMinimum(1);
        spinBox_hstep->setMaximum(100);
        spinBox_hstep->setValue(10);

        horizontalLayout_3->addWidget(spinBox_hstep);

        spinBox_vstep = new QSpinBox(dockWidgetContents);
        spinBox_vstep->setObjectName(QStringLiteral("spinBox_vstep"));
        spinBox_vstep->setMaximumSize(QSize(40, 16777215));
        spinBox_vstep->setFrame(false);
        spinBox_vstep->setMinimum(1);
        spinBox_vstep->setMaximum(100);
        spinBox_vstep->setValue(10);

        horizontalLayout_3->addWidget(spinBox_vstep);

        hSlider_range_0_127 = new QSlider(dockWidgetContents);
        hSlider_range_0_127->setObjectName(QStringLiteral("hSlider_range_0_127"));
        sizePolicy5.setHeightForWidth(hSlider_range_0_127->sizePolicy().hasHeightForWidth());
        hSlider_range_0_127->setSizePolicy(sizePolicy5);
        hSlider_range_0_127->setMaximumSize(QSize(16777215, 16777215));
        hSlider_range_0_127->setMaximum(127);
        hSlider_range_0_127->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(hSlider_range_0_127);


        gridLayout_6->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        dockWidget_operation->setWidget(dockWidgetContents);
        EnVision_imageUI->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidget_operation);

        menubar->addAction(menuattach->menuAction());
        menuattach->addAction(actionAttach);
        menuattach->addAction(actionDetach);

        retranslateUi(EnVision_imageUI);

        tabWidget_image->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);
        pushButton_resetBrightness->setDefault(false);


        QMetaObject::connectSlotsByName(EnVision_imageUI);
    } // setupUi

    void retranslateUi(QMainWindow *EnVision_imageUI)
    {
        EnVision_imageUI->setWindowTitle(QApplication::translate("EnVision_imageUI", "Image", nullptr));
        actionAttach->setText(QApplication::translate("EnVision_imageUI", "Attach", nullptr));
        actionDetach->setText(QApplication::translate("EnVision_imageUI", "Detach", nullptr));
        subwindow->setWindowTitle(QApplication::translate("EnVision_imageUI", "Subwindow", nullptr));
        tabWidget_image->setTabText(tabWidget_image->indexOf(tab_image), QApplication::translate("EnVision_imageUI", "1", nullptr));
        tabWidget_image->setTabText(tabWidget_image->indexOf(addTab_image), QApplication::translate("EnVision_imageUI", "+", nullptr));
        label_gamma->setText(QApplication::translate("EnVision_imageUI", "0", nullptr));
        label_contrast->setText(QApplication::translate("EnVision_imageUI", "0", nullptr));
        label_brightness->setText(QApplication::translate("EnVision_imageUI", "0", nullptr));
        pushButton_resetZoom->setText(QApplication::translate("EnVision_imageUI", "X", nullptr));
        pushButton_startPos->setText(QApplication::translate("EnVision_imageUI", "0", nullptr));
        menuattach->setTitle(QApplication::translate("EnVision_imageUI", "Window", nullptr));
        dockWidget_thumbnail->setWindowTitle(QApplication::translate("EnVision_imageUI", "1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(SpectralPos), QApplication::translate("EnVision_imageUI", "Spectral", nullptr));
        pushButton_thumbnailFolder->setText(QApplication::translate("EnVision_imageUI", "Open Folder", nullptr));
        dockWidget_operation->setWindowTitle(QApplication::translate("EnVision_imageUI", "2", nullptr));
        pushButton_resetBrightness->setText(QApplication::translate("EnVision_imageUI", "Reset", nullptr));
        checkBox_saturation->setText(QApplication::translate("EnVision_imageUI", "Saturation", nullptr));
        checkBox_negative->setText(QApplication::translate("EnVision_imageUI", "invert", nullptr));
        checkBox_imgLoadSelect->setText(QApplication::translate("EnVision_imageUI", "load into new tab", nullptr));
        checkBox->setText(QApplication::translate("EnVision_imageUI", "Channel 1", nullptr));
        spinBox->setSuffix(QApplication::translate("EnVision_imageUI", " time", nullptr));
        spinBox->setPrefix(QApplication::translate("EnVision_imageUI", "open", nullptr));
        radioButton_draw->setText(QApplication::translate("EnVision_imageUI", "Draw", nullptr));
        radioButton_scroll->setText(QApplication::translate("EnVision_imageUI", "Scroll", nullptr));
        checkBox_2->setText(QApplication::translate("EnVision_imageUI", "Channel 2", nullptr));
        checkBox_3->setText(QApplication::translate("EnVision_imageUI", "Channel 3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EnVision_imageUI: public Ui_EnVision_imageUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGE_WIDGET_H
