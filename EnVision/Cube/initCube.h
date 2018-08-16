#ifndef cubeGLWidget_H
#define cubeGLWidget_H

#include <iostream>
#include <iomanip>
#include <iostream>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QString>

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

//-----------------------------------
// class cubeWidget
#include "Base/Widgets/cubeWidget.h"
//-----------------------------------
// class ImageAttribute
#include "Image/image_master.h"
//-----------------------------------
// class Image
#include "Image/initImage.h"
//-----------------------------------
// class Image Widget
#include "ui_cube_widget.h"
//-----------------------------------

using std::cout;
using std::endl;
using std::setprecision;

class EnVision;

namespace Ui {
	class GLWidget_cube;
	class EnVision_cubeUI;
}

class GLWidget_cube : public QOpenGLWidget, protected QOpenGLFunctions, public ImageAttribute
{
	Q_OBJECT

public:
	explicit GLWidget_cube(EnVision* main, Ui::EnVision_cubeUI* ui_cube, QWidget *parent = 0);
	~GLWidget_cube();

	double xPos = 0;
	double yPos = 0;
	double zPos = 1;

	void guiAccess();

private:

	EnVision *main;
	Ui::EnVision_baseUI* ui_base;
	Ui::EnVision_plotUI* ui_plot;
	Ui::EnVision_cubeUI *ui_cube;
	Ui::EnVision_imageUI* ui_image;

	bool initOk = 0;

	int hScroll = 0;
	int vScroll = 0;

	QImage qface01;
	QImage face02;
	QImage face03;
	QImage face04;
	QImage face05;
	QImage face06;

	QOpenGLBuffer vbo;

	QBasicTimer timer;
	QOpenGLShaderProgram* program;
	//GeometryEngine *geometries;

	QOpenGLTexture *texture01;
	QOpenGLTexture *texture02;

	QOpenGLTexture *textures[6];

	QMatrix4x4 projection;

	QVector2D mousePressPosition;
	QVector3D rotationAxis;
	qreal angularSpeed;
	QQuaternion rotation;

protected:
	void makeObject();
	void mouseMoveEvent(QMouseEvent *e) override;
	void mousePressEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;
	void timerEvent(QTimerEvent *e) override;

	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

	int initShaders();
	void initTextures();
	void loadTextures();

	public slots:
	void wheelEvent(QWheelEvent *event);
	void horzScrollBarChanged(int value);
	void vertScrollBarChanged(int value);

};

#endif // cubeGLWidget_H
