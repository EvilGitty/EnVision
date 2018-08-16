/********************************************************************************
** Form generated from reading UI file 'table_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLE_WIDGET_H
#define UI_TABLE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EnVision_tableUI
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget_table;
    QWidget *tab_table;
    QGridLayout *gridLayout_2;
    QTableWidget *table;
    QWidget *addTab_table;
    QGridLayout *gridLayout_3;

    void setupUi(QWidget *EnVision_tableUI)
    {
        if (EnVision_tableUI->objectName().isEmpty())
            EnVision_tableUI->setObjectName(QStringLiteral("EnVision_tableUI"));
        EnVision_tableUI->resize(640, 480);
        gridLayout = new QGridLayout(EnVision_tableUI);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget_table = new QTabWidget(EnVision_tableUI);
        tabWidget_table->setObjectName(QStringLiteral("tabWidget_table"));
        tabWidget_table->setTabPosition(QTabWidget::South);
        tabWidget_table->setDocumentMode(true);
        tabWidget_table->setTabsClosable(true);
        tabWidget_table->setMovable(true);
        tab_table = new QWidget();
        tab_table->setObjectName(QStringLiteral("tab_table"));
        gridLayout_2 = new QGridLayout(tab_table);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        table = new QTableWidget(tab_table);
        if (table->columnCount() < 1000)
            table->setColumnCount(1000);
        if (table->rowCount() < 1000)
            table->setRowCount(1000);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table->setItem(0, 0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        table->setItem(0, 1, __qtablewidgetitem1);
        table->setObjectName(QStringLiteral("table"));
        table->setLineWidth(0);
        table->setGridStyle(Qt::SolidLine);
        table->setRowCount(1000);
        table->setColumnCount(1000);
        table->horizontalHeader()->setVisible(true);
        table->horizontalHeader()->setHighlightSections(true);
        table->verticalHeader()->setVisible(true);
        table->verticalHeader()->setHighlightSections(true);
        table->verticalHeader()->setStretchLastSection(false);

        gridLayout_2->addWidget(table, 0, 0, 1, 1);

        tabWidget_table->addTab(tab_table, QString());
        addTab_table = new QWidget();
        addTab_table->setObjectName(QStringLiteral("addTab_table"));
        gridLayout_3 = new QGridLayout(addTab_table);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tabWidget_table->addTab(addTab_table, QString());

        gridLayout->addWidget(tabWidget_table, 0, 0, 1, 1);


        retranslateUi(EnVision_tableUI);

        tabWidget_table->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EnVision_tableUI);
    } // setupUi

    void retranslateUi(QWidget *EnVision_tableUI)
    {
        EnVision_tableUI->setWindowTitle(QApplication::translate("EnVision_tableUI", "Data", nullptr));

        const bool __sortingEnabled = table->isSortingEnabled();
        table->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem = table->item(0, 0);
        ___qtablewidgetitem->setText(QApplication::translate("EnVision_tableUI", "ID_Labelname", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = table->item(0, 1);
        ___qtablewidgetitem1->setText(QApplication::translate("EnVision_tableUI", "ID_Number", nullptr));
        table->setSortingEnabled(__sortingEnabled);

        tabWidget_table->setTabText(tabWidget_table->indexOf(tab_table), QApplication::translate("EnVision_tableUI", "1", nullptr));
        tabWidget_table->setTabText(tabWidget_table->indexOf(addTab_table), QApplication::translate("EnVision_tableUI", "+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EnVision_tableUI: public Ui_EnVision_tableUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLE_WIDGET_H
