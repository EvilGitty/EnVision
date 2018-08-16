#ifndef CubeWidget_H
#define CubeWidget_H

#include <iostream>

#include <QWidget>
#include <QDialog>
#include <QtCore>
#include <QtGui>

#include <QSurfaceFormat>
#include <QOpenGLWidget>
#include <QDesktopWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLContext>

//#include "Cube/geometryengine.h"

#include "ui_cube_widget.h"
#include "Gui/gui_master.h"

class EnVision;
class GLWidget_cube;

namespace Ui {
	class CubeWidget;
}

class CubeWidget : public QMainWindow, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	CubeWidget(EnVision *main, QWidget *parent = 0);
	~CubeWidget();

	Ui::EnVision_cubeUI* getCubeUI(void);

signals :
	void activeTab_Signal(QWidget* widget, QObject* object, QString msg, QVector<int> index);
	void attachWidget_Signal(QWidget* widget, QString winTitle);

private:

	QAction* attach;
	QAction* detach;

private slots:
	void attachWidget();
	void detachWidget();

private:
	GLWidget_cube *widget;
	EnVision *main;
	Ui::EnVision_cubeUI *ui_cube;
};

#endif // CubeWidget_H