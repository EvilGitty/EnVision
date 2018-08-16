/********************************************************************************
** Form generated from reading UI file 'cube_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUBE_WIDGET_H
#define UI_CUBE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EnVision_cubeUI
{
public:
    QAction *actionAttach;
    QAction *actionDetach;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab_cube;
    QGridLayout *gridLayout_2;
    QGridLayout *cube;
    QScrollBar *hScrollBar;
    QScrollBar *vScrollBar;
    QSlider *hSlider_z;
    QSlider *hSlider_y;
    QSlider *hSlider_x;
    QComboBox *comboBox_face;
    QMenuBar *menubar;
    QMenu *menuWindow;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EnVision_cubeUI)
    {
        if (EnVision_cubeUI->objectName().isEmpty())
            EnVision_cubeUI->setObjectName(QStringLiteral("EnVision_cubeUI"));
        EnVision_cubeUI->resize(907, 620);
        EnVision_cubeUI->setMouseTracking(true);
        EnVision_cubeUI->setFocusPolicy(Qt::WheelFocus);
        actionAttach = new QAction(EnVision_cubeUI);
        actionAttach->setObjectName(QStringLiteral("actionAttach"));
        actionDetach = new QAction(EnVision_cubeUI);
        actionDetach->setObjectName(QStringLiteral("actionDetach"));
        centralwidget = new QWidget(EnVision_cubeUI);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::South);
        tabWidget->setDocumentMode(true);
        tabWidget->setTabsClosable(false);
        tabWidget->setTabBarAutoHide(true);
        tab_cube = new QWidget();
        tab_cube->setObjectName(QStringLiteral("tab_cube"));
        gridLayout_2 = new QGridLayout(tab_cube);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        cube = new QGridLayout();
        cube->setObjectName(QStringLiteral("cube"));

        gridLayout_2->addLayout(cube, 0, 1, 1, 1);

        hScrollBar = new QScrollBar(tab_cube);
        hScrollBar->setObjectName(QStringLiteral("hScrollBar"));
        hScrollBar->setMinimum(-99);
        hScrollBar->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(hScrollBar, 1, 1, 1, 1);

        vScrollBar = new QScrollBar(tab_cube);
        vScrollBar->setObjectName(QStringLiteral("vScrollBar"));
        vScrollBar->setMinimum(-99);
        vScrollBar->setMaximum(99);
        vScrollBar->setOrientation(Qt::Vertical);
        vScrollBar->setInvertedAppearance(true);

        gridLayout_2->addWidget(vScrollBar, 0, 0, 1, 1);

        tabWidget->addTab(tab_cube, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);

        hSlider_z = new QSlider(centralwidget);
        hSlider_z->setObjectName(QStringLiteral("hSlider_z"));
        hSlider_z->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(hSlider_z, 3, 1, 1, 1);

        hSlider_y = new QSlider(centralwidget);
        hSlider_y->setObjectName(QStringLiteral("hSlider_y"));
        hSlider_y->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(hSlider_y, 2, 1, 1, 1);

        hSlider_x = new QSlider(centralwidget);
        hSlider_x->setObjectName(QStringLiteral("hSlider_x"));
        hSlider_x->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(hSlider_x, 1, 1, 1, 1);

        comboBox_face = new QComboBox(centralwidget);
        comboBox_face->setObjectName(QStringLiteral("comboBox_face"));
        comboBox_face->setMaxCount(25);
        comboBox_face->setFrame(false);

        gridLayout->addWidget(comboBox_face, 4, 1, 1, 1);

        EnVision_cubeUI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EnVision_cubeUI);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 907, 21));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        EnVision_cubeUI->setMenuBar(menubar);
        statusbar = new QStatusBar(EnVision_cubeUI);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        EnVision_cubeUI->setStatusBar(statusbar);

        menubar->addAction(menuWindow->menuAction());
        menuWindow->addAction(actionAttach);
        menuWindow->addAction(actionDetach);

        retranslateUi(EnVision_cubeUI);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EnVision_cubeUI);
    } // setupUi

    void retranslateUi(QMainWindow *EnVision_cubeUI)
    {
        EnVision_cubeUI->setWindowTitle(QApplication::translate("EnVision_cubeUI", "Cube", nullptr));
        actionAttach->setText(QApplication::translate("EnVision_cubeUI", "Attach", nullptr));
        actionDetach->setText(QApplication::translate("EnVision_cubeUI", "Detach", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_cube), QApplication::translate("EnVision_cubeUI", "1", nullptr));
        comboBox_face->setCurrentText(QString());
        menuWindow->setTitle(QApplication::translate("EnVision_cubeUI", "Window", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EnVision_cubeUI: public Ui_EnVision_cubeUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUBE_WIDGET_H
