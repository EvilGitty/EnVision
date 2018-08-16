#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <iostream>

#include <QWidget>
#include <QDialog>
#include <QtCore>
#include <QtGui>

#include "ui_image_widget.h"
#include "Gui/gui_master.h"

class EnVision;

namespace Ui {
	class ImageWidget;
}


class ImageWidget : public QMainWindow
{
	Q_OBJECT

public:

	ImageWidget(EnVision *main, QWidget *parent = 0);
	~ImageWidget();

	Ui::EnVision_imageUI* getImageUI(void);

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

	QAction *actionAttach;
	QAction *actionDetach;

	QWidget *tab_x;

	EnVision *main;
	Ui::EnVision_imageUI *ui_image;
};

#endif // IMAGEWIDGET_H