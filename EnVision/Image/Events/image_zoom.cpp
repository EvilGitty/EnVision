#include "image_zoom.h"
#include <QMouseEvent>
#include <QApplication>
#include <QScrollBar>
#include <qmath.h>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
Graphics_view_zoom::Graphics_view_zoom(QGraphicsView* view)
: QObject(view), graphicsview(view)
{
		graphicsview->viewport()->installEventFilter(this);
		graphicsview->setMouseTracking(true);
		//keymodifier = Qt::ControlModifier;
		zoom_factor = 1.0025;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
Graphics_view_zoom::~Graphics_view_zoom()
{
}
//==============================================================================
// void Graphics_view_zoom::gentle_zoom(double factor)
//------------------------------------------------------------------------------
//==============================================================================
void Graphics_view_zoom::gentle_zoom(double factor)
{
		graphicsview->scale(factor, factor);
		graphicsview->centerOn(scene_pos);
		QPointF delta_viewport_pos = viewport_pos - QPointF(graphicsview->viewport()->width() / 2.0,
			graphicsview->viewport()->height() / 2.0);
		QPointF viewport_center = graphicsview->mapFromScene(scene_pos) - delta_viewport_pos;
		graphicsview->centerOn(graphicsview->mapToScene(viewport_center.toPoint()));
		emit zoomed();
	return;
}



//==============================================================================
// void Graphics_view_zoom::set_modifiers(Qt::KeyboardModifiers modifiers)
//------------------------------------------------------------------------------
// //1.0055 (max); 1.0025 (medium);  1.0015 (fine,) 1.0001 (min), 1.0000 (no zoom)
//==============================================================================
void Graphics_view_zoom::set_modifiers(double value, Qt::KeyboardModifiers modifiers)
{
		zoom_factor = value;
		keymodifier = modifiers;
	return;
}

//==============================================================================
// bool Graphics_view_zoom::eventFilter(QObject *object, QEvent *event)
//------------------------------------------------------------------------------
//==============================================================================
bool Graphics_view_zoom::eventFilter(QObject *object, QEvent *event)
{
		if (event->type() == QEvent::MouseMove) {
			QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
			QPointF delta = viewport_pos - mouse_event->pos();
			if (qAbs(delta.x()) > 5 || qAbs(delta.y()) > 5) {
				viewport_pos = mouse_event->pos();
				scene_pos = graphicsview->mapToScene(mouse_event->pos());
			}
		}
		else if (event->type() == QEvent::Wheel) {
			QWheelEvent* wheel_event = static_cast<QWheelEvent*>(event);
			if (QApplication::keyboardModifiers() == keymodifier) {
				if (wheel_event->orientation() == Qt::Vertical) {
					double angle = wheel_event->angleDelta().y();
					double factor = qPow(zoom_factor, angle);
					gentle_zoom(factor);
					return true;
				}
			}
		}
		Q_UNUSED(object)
	return false;
}