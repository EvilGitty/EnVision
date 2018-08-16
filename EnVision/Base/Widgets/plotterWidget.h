#ifndef PLOTTERWIDGET_H
#define PLOTTERWIDGET_H

#include <iostream>

#include <QWidget>
#include <QDialog>
#include <QtCore>
#include <QtGui>

#include "ui_plot_widget.h"
#include "Base/tabhandling.h"

class EnVision;

namespace Ui {
	class PlotterWidget;
}


class PlotterWidget : public QMainWindow
{
	Q_OBJECT

public:

	PlotterWidget(EnVision *main, QWidget *parent = 0);
	~PlotterWidget();

	Ui::EnVision_plotUI* getPlotUI(void);

signals:
	void activeTab_Signal(QWidget* widget, QObject* object, QString msg, QVector<int> index);
	void attachWidget_Signal(QWidget* widget, QString winTitle);

	public slots :
	int getCurrentTabIndex(int ind);
	int missingTabIndex();
	QWidget* constructTab(void);

	void initElements(int index);
	void resetTab(int index);
	void setTab(int newInd, int lastInd);
	void activateTab(int index);
	void closeTab(int index);
	void moveTab(int to, int from);

	void attachWidget();
	void detachWidget();
	private slots:
	virtual bool eventFilter(QObject *o, QEvent *e);
private:
	QWidget *tab_x;

	EnVision *main;
	Ui::EnVision_plotUI *ui_plot;
};

#endif // PLOTTERWIDGET_H