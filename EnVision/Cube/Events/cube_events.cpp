#include "Cube/initCube.h"
#include "Base/envision.h"

//==============================================================================
// void GLWidget_cube::horzScrollBarChanged(int value)
//------------------------------------------------------------------------------
//==============================================================================
void GLWidget_cube::horzScrollBarChanged(int value)
{
		hScroll = this->ui_cube->hScrollBar->value();
		if (initOk == 1){
			this->update();

		}
	return;
}


//==============================================================================
// void GLWidget_cube::vertScrollBarChanged(int value)
//------------------------------------------------------------------------------
//==============================================================================
void GLWidget_cube::vertScrollBarChanged(int value)
{
		vScroll = this->ui_cube->vScrollBar->value();
		if (initOk == 1){
			this->update();
		}
	return;
}

//==============================================================================
// void GLWidget_cube::mousePressEvent(QMouseEvent *e)
//------------------------------------------------------------------------------
//==============================================================================
void GLWidget_cube::mousePressEvent(QMouseEvent *e)
{
		// Save mouse press position
		mousePressPosition = QVector2D(e->localPos());
	return;
}

//==============================================================================
// void GLWidget_cube::mouseReleaseEvent(QMouseEvent *e)
//------------------------------------------------------------------------------
//==============================================================================
void GLWidget_cube::mouseReleaseEvent(QMouseEvent *e)
{
		// Mouse release position - mouse press position
		QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

		// Rotation axis is perpendicular to the mouse position difference
		// vector
		QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

		// Accelerate angular speed relative to the length of the mouse sweep
		qreal acc = diff.length() / 100.0;

		// Calculate new rotation axis as weighted sum
		rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

		// Increase angular speed
		angularSpeed += acc;	
	return;
}

//==============================================================================
// void GLWidget_cube::timerEvent(QTimerEvent *)
//------------------------------------------------------------------------------
//==============================================================================
void GLWidget_cube::timerEvent(QTimerEvent* e)
{
		// Decrease angular speed (friction)
		angularSpeed *= 0.97;

		// Stop rotation when speed goes below threshold
		if (angularSpeed < 0.98) {
			angularSpeed = 0.0;
		}
		else {
			// Update rotation
			rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

			//update faces
			//loadTextures();

			// Request an update
			this->update();
			return;
		}

		//put back into else branch if too heavy on performance
		//update faces
		loadTextures();

		// Request an update
		this->update();
		//cout << "angularSpeed " << angularSpeed << endl;
	return;
}


//==============================================================================
// void GLWidget_cube::mouseMoveEvent(QMouseEvent *ev)
//------------------------------------------------------------------------------
//==============================================================================
void GLWidget_cube::mouseMoveEvent(QMouseEvent *e)
{
		/*
		QMouseEvent* ev = (QMouseEvent*)e;

		if (ev->buttons() == Qt::LeftButton){

			// Mouse release position - mouse press position
			QVector2D diff = QVector2D(e->localPos()); // - mousePressPosition;

			// Rotation axis is perpendicular to the mouse position difference
			// vector
			QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

			// Accelerate angular speed relative to the length of the mouse sweep
			qreal acc = diff.length() / 100.0;

			// Calculate new rotation axis as weighted sum
			rotationAxis = (rotationAxis * angularSpeed + n * 1).normalized();

			// Increase angular speed
			angularSpeed += acc;
		}
		*/
	return;
}

//==============================================================================
// void GLWidget_cube::wheelEvent(QWheelEvent *event)
//------------------------------------------------------------------------------
//==============================================================================
void GLWidget_cube::wheelEvent(QWheelEvent *event)
{
		int w = this->width();
		int h = this->height();
		xPos = this->mapFromGlobal(QCursor::pos()).x();
		yPos = this->mapFromGlobal(QCursor::pos()).y();

		QPoint numDegrees = event->angleDelta();
		if (numDegrees.y() < 0){
			zPos = (double)zPos / 1.1;
		}

		if (numDegrees.y() > 0){
			zPos = (double)zPos*1.1;
		}

		this->update();

		//  std::cout <<  std::setprecision (5) << zPos << " xPos:" << xPos << " yPos:" << yPos << std::endl;
		//std::cout << xPos << " " << this->width() / 2 << endl;
	return;
}
