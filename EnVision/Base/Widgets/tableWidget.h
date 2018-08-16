#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <iostream>

#include <QWidget>
#include <QDialog>
#include <QtCore>
#include <QtGui>

#include "ui_table_widget.h"

class EnVision;


namespace Ui {
	class TableWidget;
}

class TableWidget : public QWidget
{
	Q_OBJECT

public:

	TableWidget(EnVision *main);
	~TableWidget();

	Ui::EnVision_tableUI* getTableUI(void);

private:

	template <typename Func1, typename Func2>
	static inline QMetaObject::Connection weakConnect(
		typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal,
		typename QtPrivate::FunctionPointer<Func2>::Object *receiver, Func2 slot)
	{

		QMetaObject::Connection conn_normal = QObject::connect(sender, signal, receiver, slot);

		QMetaObject::Connection* conn_delete = new QMetaObject::Connection();

		*conn_delete = QObject::connect(sender, signal, [conn_normal, conn_delete](){
			QObject::disconnect(conn_normal);
			QObject::disconnect(*conn_delete);
			delete conn_delete;
		});
		return conn_normal;
	}

	QString signalThatReturnsAString(int _t1)
	{
		QString _t0;
		void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)),
			const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
		QMetaObject::activate(this, &staticMetaObject, 0, _a);
		return _t0;
	}

signals:
	void activeTab_Signal(QWidget* widget, QObject* object, QString msg, QVector<int> index);
	void attachWidget_Signal(QWidget* widget, QString winTitle);
	void sig(int a);

public slots :
	void slo(int a) { qDebug() << " ! ! " << a; }

	int getCurrentTabIndex(int ind);
	int missingTabIndex();
	QWidget* constructWorksheet();
	void reserveTable();
	void activateTab(int index);
	void closeTab(int index);
	void moveTab(int to, int from);


private slots:
	void attachWidget();
	void detachWidget();
	bool eventFilter(QObject *o, QEvent *e);

private:
	QTableWidget* workspaceTableWidget;
	QAction* attach;
	QAction* detach;

	QWidget *tab_x;

	EnVision *main;
	Ui::EnVision_tableUI *ui_table;
};

#endif // TABLEWIDGET_H