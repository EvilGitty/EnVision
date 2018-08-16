/********************************************************************************
** Form generated from reading UI file 'plot_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOT_WIDGET_H
#define UI_PLOT_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_EnVision_plotUI
{
public:
    QAction *actionAttach;
    QAction *actionDetach;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QScrollBar *vScrollBar;
    QHBoxLayout *horizontalLayout;
    QScrollBar *hScrollBar;
    QPushButton *pushButton_resetZoom;
    QTabWidget *tabWidget_plotter;
    QWidget *tab_plot;
    QGridLayout *gridLayout_2;
    QMdiArea *mdiArea;
    QWidget *subwindow;
    QGridLayout *gridLayout_5;
    QCustomPlot *plot;
    QGridLayout *gridLayout_4;
    QWidget *addTab_plot;
    QGridLayout *gridLayout_3;
    QCheckBox *checkBox_graphPreview;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_17;
    QRadioButton *radioButtonX01;
    QRadioButton *radioButtonX02;
    QCheckBox *checkBox_dynamicRescaleSpectralX;
    QFrame *line;
    QCheckBox *checkBox_clearPreviewGraphs;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_7;
    QRadioButton *radioButtonB;
    QRadioButton *radioButtonY;
    QRadioButton *radioButtonG;
    QRadioButton *radioButtonR;
    QRadioButton *radioButtonC;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_6;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_3;
    QHBoxLayout *horizontalLayout_12;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_19;
    QRadioButton *radioButtonY01;
    QFrame *line_8;
    QCheckBox *checkBox_dynamicRescaleSpectralY;
    QCheckBox *checkBox_limitOverflow;
    QRadioButton *radioButtonY02;
    QMenuBar *menubar;
    QMenu *menuWindow;
    QMenu *menuOptions;
    QStatusBar *statusbar;
    QButtonGroup *buttonGroup_scaleXaxis;
    QButtonGroup *buttonGroup_scaleYaxis;

    void setupUi(QMainWindow *EnVision_plotUI)
    {
        if (EnVision_plotUI->objectName().isEmpty())
            EnVision_plotUI->setObjectName(QStringLiteral("EnVision_plotUI"));
        EnVision_plotUI->resize(781, 665);
        actionAttach = new QAction(EnVision_plotUI);
        actionAttach->setObjectName(QStringLiteral("actionAttach"));
        actionDetach = new QAction(EnVision_plotUI);
        actionDetach->setObjectName(QStringLiteral("actionDetach"));
        centralwidget = new QWidget(EnVision_plotUI);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        vScrollBar = new QScrollBar(centralwidget);
        vScrollBar->setObjectName(QStringLiteral("vScrollBar"));
        vScrollBar->setOrientation(Qt::Vertical);
        vScrollBar->setInvertedAppearance(true);
        vScrollBar->setInvertedControls(false);

        verticalLayout_2->addWidget(vScrollBar);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        hScrollBar = new QScrollBar(centralwidget);
        hScrollBar->setObjectName(QStringLiteral("hScrollBar"));
        hScrollBar->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(hScrollBar);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);

        pushButton_resetZoom = new QPushButton(centralwidget);
        pushButton_resetZoom->setObjectName(QStringLiteral("pushButton_resetZoom"));
        pushButton_resetZoom->setMaximumSize(QSize(30, 30));

        gridLayout->addWidget(pushButton_resetZoom, 1, 0, 1, 1);

        tabWidget_plotter = new QTabWidget(centralwidget);
        tabWidget_plotter->setObjectName(QStringLiteral("tabWidget_plotter"));
        tabWidget_plotter->setTabPosition(QTabWidget::South);
        tabWidget_plotter->setDocumentMode(true);
        tabWidget_plotter->setTabsClosable(true);
        tabWidget_plotter->setMovable(true);
        tab_plot = new QWidget();
        tab_plot->setObjectName(QStringLiteral("tab_plot"));
        gridLayout_2 = new QGridLayout(tab_plot);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        mdiArea = new QMdiArea(tab_plot);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));
        subwindow = new QWidget();
        subwindow->setObjectName(QStringLiteral("subwindow"));
        gridLayout_5 = new QGridLayout(subwindow);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        plot = new QCustomPlot(subwindow);
        plot->setObjectName(QStringLiteral("plot"));
        plot->setMinimumSize(QSize(0, 0));
        gridLayout_4 = new QGridLayout(plot);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);

        gridLayout_5->addWidget(plot, 0, 0, 1, 1);

        mdiArea->addSubWindow(subwindow);

        gridLayout_2->addWidget(mdiArea, 0, 0, 1, 1);

        tabWidget_plotter->addTab(tab_plot, QString());
        addTab_plot = new QWidget();
        addTab_plot->setObjectName(QStringLiteral("addTab_plot"));
        gridLayout_3 = new QGridLayout(addTab_plot);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tabWidget_plotter->addTab(addTab_plot, QString());

        gridLayout->addWidget(tabWidget_plotter, 0, 1, 1, 1);

        checkBox_graphPreview = new QCheckBox(centralwidget);
        checkBox_graphPreview->setObjectName(QStringLiteral("checkBox_graphPreview"));
        checkBox_graphPreview->setChecked(true);

        gridLayout->addWidget(checkBox_graphPreview, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        groupBox_4->setFont(font);
        groupBox_4->setAlignment(Qt::AlignCenter);
        gridLayout_17 = new QGridLayout(groupBox_4);
        gridLayout_17->setObjectName(QStringLiteral("gridLayout_17"));
        radioButtonX01 = new QRadioButton(groupBox_4);
        buttonGroup_scaleXaxis = new QButtonGroup(EnVision_plotUI);
        buttonGroup_scaleXaxis->setObjectName(QStringLiteral("buttonGroup_scaleXaxis"));
        buttonGroup_scaleXaxis->addButton(radioButtonX01);
        radioButtonX01->setObjectName(QStringLiteral("radioButtonX01"));
        radioButtonX01->setMinimumSize(QSize(0, 30));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        radioButtonX01->setFont(font1);

        gridLayout_17->addWidget(radioButtonX01, 0, 0, 1, 1);

        radioButtonX02 = new QRadioButton(groupBox_4);
        buttonGroup_scaleXaxis->addButton(radioButtonX02);
        radioButtonX02->setObjectName(QStringLiteral("radioButtonX02"));
        radioButtonX02->setMinimumSize(QSize(0, 30));
        radioButtonX02->setFont(font1);
        radioButtonX02->setChecked(true);

        gridLayout_17->addWidget(radioButtonX02, 0, 1, 1, 1);

        checkBox_dynamicRescaleSpectralX = new QCheckBox(groupBox_4);
        checkBox_dynamicRescaleSpectralX->setObjectName(QStringLiteral("checkBox_dynamicRescaleSpectralX"));
        checkBox_dynamicRescaleSpectralX->setFont(font1);

        gridLayout_17->addWidget(checkBox_dynamicRescaleSpectralX, 2, 0, 1, 1);

        line = new QFrame(groupBox_4);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_17->addWidget(line, 1, 0, 1, 2);


        horizontalLayout_3->addWidget(groupBox_4);


        gridLayout->addLayout(horizontalLayout_3, 5, 0, 1, 1);

        checkBox_clearPreviewGraphs = new QCheckBox(centralwidget);
        checkBox_clearPreviewGraphs->setObjectName(QStringLiteral("checkBox_clearPreviewGraphs"));
        checkBox_clearPreviewGraphs->setMinimumSize(QSize(0, 0));
        checkBox_clearPreviewGraphs->setFont(font1);
        checkBox_clearPreviewGraphs->setChecked(true);

        gridLayout->addWidget(checkBox_clearPreviewGraphs, 4, 0, 1, 1);

        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy);
        groupBox_5->setMaximumSize(QSize(16777215, 50));
        groupBox_5->setFont(font);
        groupBox_5->setAlignment(Qt::AlignCenter);
        horizontalLayout_7 = new QHBoxLayout(groupBox_5);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        radioButtonB = new QRadioButton(groupBox_5);
        radioButtonB->setObjectName(QStringLiteral("radioButtonB"));
        radioButtonB->setEnabled(true);
        radioButtonB->setMinimumSize(QSize(0, 30));
        radioButtonB->setFont(font1);
        radioButtonB->setChecked(true);

        horizontalLayout_7->addWidget(radioButtonB);

        radioButtonY = new QRadioButton(groupBox_5);
        radioButtonY->setObjectName(QStringLiteral("radioButtonY"));
        radioButtonY->setMinimumSize(QSize(0, 30));
        radioButtonY->setFont(font1);

        horizontalLayout_7->addWidget(radioButtonY);

        radioButtonG = new QRadioButton(groupBox_5);
        radioButtonG->setObjectName(QStringLiteral("radioButtonG"));
        radioButtonG->setEnabled(true);
        radioButtonG->setMinimumSize(QSize(0, 30));
        radioButtonG->setFont(font1);

        horizontalLayout_7->addWidget(radioButtonG);

        radioButtonR = new QRadioButton(groupBox_5);
        radioButtonR->setObjectName(QStringLiteral("radioButtonR"));
        radioButtonR->setEnabled(true);
        radioButtonR->setMinimumSize(QSize(0, 30));
        radioButtonR->setFont(font1);

        horizontalLayout_7->addWidget(radioButtonR);

        radioButtonC = new QRadioButton(groupBox_5);
        radioButtonC->setObjectName(QStringLiteral("radioButtonC"));
        radioButtonC->setEnabled(true);
        radioButtonC->setMinimumSize(QSize(0, 30));
        radioButtonC->setFont(font1);
        radioButtonC->setCheckable(true);
        radioButtonC->setChecked(false);

        horizontalLayout_7->addWidget(radioButtonC);


        gridLayout->addWidget(groupBox_5, 2, 1, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_6 = new QGridLayout(groupBox);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setMinimumSize(QSize(0, 30));
        radioButton_2->setFont(font1);
        radioButton_2->setChecked(true);

        gridLayout_6->addWidget(radioButton_2, 0, 0, 2, 3);

        radioButton_4 = new QRadioButton(groupBox);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setMinimumSize(QSize(0, 30));
        radioButton_4->setFont(font1);

        gridLayout_6->addWidget(radioButton_4, 1, 1, 1, 1);

        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setMinimumSize(QSize(0, 30));
        radioButton_3->setFont(font1);

        gridLayout_6->addWidget(radioButton_3, 1, 2, 1, 1);


        gridLayout->addWidget(groupBox, 4, 1, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(16777215, 16777215));
        groupBox_3->setFont(font);
        groupBox_3->setAlignment(Qt::AlignCenter);
        gridLayout_19 = new QGridLayout(groupBox_3);
        gridLayout_19->setObjectName(QStringLiteral("gridLayout_19"));
        radioButtonY01 = new QRadioButton(groupBox_3);
        buttonGroup_scaleYaxis = new QButtonGroup(EnVision_plotUI);
        buttonGroup_scaleYaxis->setObjectName(QStringLiteral("buttonGroup_scaleYaxis"));
        buttonGroup_scaleYaxis->addButton(radioButtonY01);
        radioButtonY01->setObjectName(QStringLiteral("radioButtonY01"));
        radioButtonY01->setMinimumSize(QSize(0, 30));
        radioButtonY01->setFont(font1);
        radioButtonY01->setChecked(true);

        gridLayout_19->addWidget(radioButtonY01, 0, 0, 1, 1);

        line_8 = new QFrame(groupBox_3);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);

        gridLayout_19->addWidget(line_8, 1, 0, 1, 3);

        checkBox_dynamicRescaleSpectralY = new QCheckBox(groupBox_3);
        checkBox_dynamicRescaleSpectralY->setObjectName(QStringLiteral("checkBox_dynamicRescaleSpectralY"));
        checkBox_dynamicRescaleSpectralY->setEnabled(true);
        checkBox_dynamicRescaleSpectralY->setMinimumSize(QSize(0, 30));
        checkBox_dynamicRescaleSpectralY->setFont(font1);
        checkBox_dynamicRescaleSpectralY->setChecked(true);

        gridLayout_19->addWidget(checkBox_dynamicRescaleSpectralY, 2, 0, 1, 1);

        checkBox_limitOverflow = new QCheckBox(groupBox_3);
        checkBox_limitOverflow->setObjectName(QStringLiteral("checkBox_limitOverflow"));
        checkBox_limitOverflow->setMinimumSize(QSize(0, 30));
        checkBox_limitOverflow->setFont(font1);
        checkBox_limitOverflow->setChecked(true);

        gridLayout_19->addWidget(checkBox_limitOverflow, 2, 1, 1, 1);

        radioButtonY02 = new QRadioButton(groupBox_3);
        buttonGroup_scaleYaxis->addButton(radioButtonY02);
        radioButtonY02->setObjectName(QStringLiteral("radioButtonY02"));
        radioButtonY02->setMinimumSize(QSize(0, 30));
        QFont font2;
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        radioButtonY02->setFont(font2);
        radioButtonY02->setChecked(false);

        gridLayout_19->addWidget(radioButtonY02, 0, 1, 1, 1);


        horizontalLayout_12->addWidget(groupBox_3);


        gridLayout->addLayout(horizontalLayout_12, 5, 1, 1, 1);

        EnVision_plotUI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EnVision_plotUI);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 781, 21));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        EnVision_plotUI->setMenuBar(menubar);
        statusbar = new QStatusBar(EnVision_plotUI);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        EnVision_plotUI->setStatusBar(statusbar);

        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menuWindow->addAction(actionAttach);
        menuWindow->addAction(actionDetach);

        retranslateUi(EnVision_plotUI);

        tabWidget_plotter->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EnVision_plotUI);
    } // setupUi

    void retranslateUi(QMainWindow *EnVision_plotUI)
    {
        EnVision_plotUI->setWindowTitle(QApplication::translate("EnVision_plotUI", "Plotter", nullptr));
        actionAttach->setText(QApplication::translate("EnVision_plotUI", "Attach", nullptr));
        actionDetach->setText(QApplication::translate("EnVision_plotUI", "Detach", nullptr));
        pushButton_resetZoom->setText(QApplication::translate("EnVision_plotUI", "X", nullptr));
        subwindow->setWindowTitle(QApplication::translate("EnVision_plotUI", "Subwindow", nullptr));
        tabWidget_plotter->setTabText(tabWidget_plotter->indexOf(tab_plot), QApplication::translate("EnVision_plotUI", "1", nullptr));
        tabWidget_plotter->setTabText(tabWidget_plotter->indexOf(addTab_plot), QApplication::translate("EnVision_plotUI", "+", nullptr));
        checkBox_graphPreview->setText(QApplication::translate("EnVision_plotUI", "Live Plot", nullptr));
        groupBox_4->setTitle(QApplication::translate("EnVision_plotUI", "x", nullptr));
        radioButtonX01->setText(QApplication::translate("EnVision_plotUI", "ordinal", nullptr));
        radioButtonX02->setText(QApplication::translate("EnVision_plotUI", "unit", nullptr));
        checkBox_dynamicRescaleSpectralX->setText(QApplication::translate("EnVision_plotUI", "dynamic rescale", nullptr));
        checkBox_clearPreviewGraphs->setText(QApplication::translate("EnVision_plotUI", "auto clear", nullptr));
        groupBox_5->setTitle(QString());
        radioButtonB->setText(QApplication::translate("EnVision_plotUI", "blue", nullptr));
        radioButtonY->setText(QApplication::translate("EnVision_plotUI", "yellow", nullptr));
        radioButtonG->setText(QApplication::translate("EnVision_plotUI", "green", nullptr));
        radioButtonR->setText(QApplication::translate("EnVision_plotUI", "red", nullptr));
        radioButtonC->setText(QApplication::translate("EnVision_plotUI", "cycling", nullptr));
        groupBox->setTitle(QString());
        radioButton_2->setText(QApplication::translate("EnVision_plotUI", "plus", nullptr));
        radioButton_4->setText(QApplication::translate("EnVision_plotUI", "square", nullptr));
        radioButton_3->setText(QApplication::translate("EnVision_plotUI", "circle", nullptr));
        groupBox_3->setTitle(QApplication::translate("EnVision_plotUI", "y", nullptr));
        radioButtonY01->setText(QApplication::translate("EnVision_plotUI", "[0,1]", nullptr));
        checkBox_dynamicRescaleSpectralY->setText(QApplication::translate("EnVision_plotUI", "dynamic rescale", nullptr));
        checkBox_limitOverflow->setText(QApplication::translate("EnVision_plotUI", "limit overflow", nullptr));
        radioButtonY02->setText(QApplication::translate("EnVision_plotUI", "[0,max]", nullptr));
        menuWindow->setTitle(QApplication::translate("EnVision_plotUI", "Window", nullptr));
        menuOptions->setTitle(QApplication::translate("EnVision_plotUI", "Options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EnVision_plotUI: public Ui_EnVision_plotUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOT_WIDGET_H
