#include "Image/initImage.h"
#include "Base/envision.h"

//==============================================================================
// void Image::dragEnterEvent(QDragEnterEvent *ev)
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::paintEvent(QPaintEvent *pe)
{

}

//==============================================================================
// void Image::dragEnterEvent(QDragEnterEvent *ev)
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::dragEnterEvent(QDragEnterEvent *ev)
{
	return;
}

//==============================================================================
// void Image::dropEvent(QDropEvent *event)
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::dropEvent(QDropEvent *event)
{
	return;
}


//==============================================================================
// void Image::mouseWheel(QWheelEvent* e)
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::mouseWheel(QWheelEvent* e)
{


	cout << " WHEEL EVENT " << endl;
	/*
		const int degrees = e->delta() / 8;
		int steps = degrees / 15;
		if (steps > 0)
		{
			mWheel = Mechanics::mouseWheel::up;
		}
		else{
			mWheel = Mechanics::mouseWheel::down;
		}

		if (y_zoom == Mechanics::y_bound::hit){
			if (mWheel == Mechanics::mouseWheel::up){
				ui_image->image->axisRect()->setRangeZoom(0);
			}
			if (mWheel == Mechanics::mouseWheel::down){
				ui_image->image->axisRect()->setRangeZoom(Qt::Vertical | Qt::Horizontal);
			}
		}

		resizeWidget = Mechanics::resizeWidget::no;
		*/
	return;
}

//==============================================================================
// void Image::horzScrollBarChanged(int value)
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::horzScrollBarChanged(int value)
{
	/*
		if (qAbs(ui_image->image->xAxis->range().center() - value / 100.0) > 0.01){
			ui_image->image->xAxis->setRange(value / 100.0, ui_image->image->xAxis->range().size(), Qt::AlignCenter);
			ui_image->image->replot();
		}
		*/
	return;
}


//==============================================================================
// void Image::vertScrollBarChanged(int value)
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::vertScrollBarChanged(int value)
{
	/*
		if (qAbs(ui_image->image->yAxis->range().center() + value / 100.0) > 0.01){
			ui_image->image->yAxis->setRange(value / 100.0, ui_image->image->yAxis->range().size(), Qt::AlignCenter);
			ui_image->image->replot();
		}
		*/
	return;
}

//==============================================================================
// void Image::xAxisChanged(QCPRange rangeNew, QCPRange rangeOld)
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::xAxisChanged(QCPRange rangeNew, QCPRange rangeOld)
{
		/*
		int imgIndex = (main->Gui::tabRecord.imgIndex);
		//out of bounds?
		if (ui_image->image->xAxis->range().size() < (_lines * 2 / 3)){
			//	y_zoom = Mechanics::y_bound::hit;
			//	return;
		}
		else{
			//	y_zoom = Mechanics::y_bound::miss;
		}

		if (mouse == Mechanics::mousePos::inside){
			if (rangeNew.lower > _lines){
				//loadViewPort();
				return;
			}

			if (rangeNew.upper < 0){
				//loadViewPort();
				return;
			}
		}

		resizeWidget = Mechanics::resizeWidget::no;
		saveViewPort();

		ui_image->hScrollBar->setValue(qRound(rangeNew.center()*100.0)); // adjust position of scroll bar slider
		ui_image->hScrollBar->setPageStep(qRound(rangeNew.size()*100.0)); // adjust size of scroll bar slider
		ui_image->hScrollBar->setSingleStep(qRound(rangeNew.size()*ui_image->spinBox_hstep->value())); // adjust size of scroll bar slider
		*/
	return;
}

//==============================================================================
// void Image::yAxisChanged(QCPRange rangeNew, QCPRange rangeOld)
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::yAxisChanged(QCPRange rangeNew, QCPRange rangeOld)
{
	/*
		int imgIndex = (main->Gui::tabRecord.imgIndex);
		//out of bounds?
		if (ui_image->image->yAxis->range().size() < (_samples * 2 / 3)){
			y_zoom = Mechanics::y_bound::hit;
			return;
		}
		else{
			y_zoom = Mechanics::y_bound::miss;
		}

		//check that mouse is inside the widget
		if (mouse == Mechanics::mousePos::inside){
			if ((rangeNew.upper < 0)) {
				loadViewPort();
				return;
			}

			if ((rangeNew.lower  > _samples)){
				loadViewPort();
				return;
			}
		}

		resizeWidget = Mechanics::resizeWidget::no;
		saveViewPort();

		ui_image->vScrollBar->setValue(qRound(rangeNew.center()*100.0)); // adjust position of scroll bar slider
		ui_image->vScrollBar->setPageStep(qRound(rangeNew.size()*100.0)); // adjust size of scroll bar slider
		ui_image->vScrollBar->setSingleStep(qRound(rangeNew.size()*ui_image->spinBox_vstep->value())); // adjust size of scroll bar slider
		*/
	return;
}

//==============================================================================
// void Image::resizeEvent(QResizeEvent *event)
//------------------------------------------------------------------------------
// Reimplementation of the windows reize event
//==============================================================================
void Imageclass::resizeEvent(QResizeEvent *event)
{

	/*
		int imgIndex = (main->Gui::tabRecord.imgIndex);
		unsigned long block = (double)main->Gui::tabRecord.size_imageWidget.width();

		cout << " view.upper_x[0]  resize 1: " << view.lower_x[0] << " " << view.upper_x[0] << endl;
		double factor = (double)_lines / 900;
		ui_image->image->xAxis->setRange(view.lower_x[0], 0 + factor * block);
		ui_image->image->yAxis->setRange(view.lower_y[0], view.upper_y[0]);
		ui_image->image->replot();

		saveViewPort();
		*/
	return;
}

//==============================================================================
// bool Image::eventFilter(QObject *o, QEvent *e)
//------------------------------------------------------------------------------
//==============================================================================
bool Imageclass::eventFilter(QObject *o, QEvent *e)
{
		QString geometry = ui_image->comboBox_plotGeometry->currentText();

		if ((e->type() == QEvent::MouseButtonPress)){
			QMouseEvent* ev = (QMouseEvent*)e;
			if (ev->buttons() == Qt::LeftButton){
			//	QMessageBox::information(this, "!", "LEFT");
			}
			if (ev->buttons() == Qt::RightButton){
			//	QMessageBox::information(this, "!", "Right");
			}
			ui_image->image->viewport()->setCursor(Qt::BlankCursor);
			//return 0;
		}


		QPoint origin = ui_image->image->mapFromGlobal(QCursor::pos());
		QPointF relativeOrigin = ui_image->image->mapToScene(origin);

		qreal x = relativeOrigin.x();
		qreal y = relativeOrigin.y();
		qreal z = 0;

		cout << "x: " << x << ". y: " << y << endl;

		if (e->type() == QEvent::MouseMove){

			if (main->ImageGui::Record[_imgIndex].scroll == 0){
				ui_image->image->viewport()->setCursor(Qt::CrossCursor);
				ui_image->image->setDragMode(QGraphicsView::NoDrag);
			}else{
				ui_image->image->viewport()->setCursor(Qt::OpenHandCursor);
				ui_image->image->setDragMode(QGraphicsView::ScrollHandDrag);
			}

			if (((x >= 0) && (x < _lines)) && ((y >= 0) && (y < _samples))){

				//check if mouse has move, we don't want to replot the same graph all the time
				if (geometry.compare("Single Point") == 0) {
					if ((oldMousePos.x() != x) && (oldMousePos.y() != y)){
						if (ImageAttribute::Record[_imgIndex].pixel_list.size() < 2){
							ImageAttribute::Record[_imgIndex].pixel_list.resize(2);
						}
						ImageAttribute::Record[_imgIndex].pixel_list[0] = { x, y, 0, "show", geometry };
						ImageAttribute::Record[_imgIndex].pixel_list[1] = { x + 1, y + 1, 0, "show", geometry };

						//ImageAttribute::Record[_imgIndex].pixel_list[0] = { x, y, z, "show", geometry };
						getPixel();
					}
					shape->updateItem(shape->spoint, QRect(x, y, 1, 1), QPolygonF());
				}

				if (geometry.compare("Rectangle") == 0) {

					if ((oldMousePos.x() != x) && (oldMousePos.y() != y)){
						if (ImageAttribute::Record[_imgIndex].pixel_list.size() < 2){
							ImageAttribute::Record[_imgIndex].pixel_list.resize(2);
						}
						QRectF bound = shape->rectangle->boundingRect();
						ImageAttribute::Record[_imgIndex].pixel_list[0] = { x, y, 0, "show", geometry };
						ImageAttribute::Record[_imgIndex].pixel_list[1] = { x + bound.width(), y + bound.height(), 0, "show", geometry };

						getPixel();
					}
					shape->updateItem(shape->rectangle, QRect(x, y, 10, 10), QPolygonF());
				}

				if (geometry.compare("Ellipse") == 0) {
					shape->updateItem(shape->ellipse, QRect(x, y, 13, 25), QPolygonF());
				}

				if (geometry.compare("Polygon") == 0) {
					shape->updateItem(shape->polygon, QRect(x, y, 0, 0), QPolygonF());
				}
				//store current mouse position
				oldMousePos = QPoint(x, y);
			}
			return 0;
		}

		//Zoom
		if (e->type() == QEvent::Wheel) {
			zoom->set_modifiers(1.0025, Qt::NoModifier);  //Qt::ControlModifier
		}
		
		//jumop to arbeitrary scrollbar/slider position
		if (e->type() == QEvent::MouseButtonPress){

			if ((o == ui_image->hSlider_channel) ||
				(o == ui_image->hSlider_gamma) ||
				(o == ui_image->hSlider_contrast) ||
				(o == ui_image->hSlider_brightness)){

				//cout << " Slider Pos: " << ui_image->hSlider_channel->value() << endl;
				QSlider *q = qobject_cast<QSlider*>(o);

				QMouseEvent* ev = (QMouseEvent*)e;
				if ((ev->buttons() == Qt::LeftButton))
				{
					int newVal;
					if (q->orientation() == Qt::Vertical){
						newVal = q->minimum() + ((q->maximum() - q->minimum())
							*(q->height() - ev->y())) / q->height();
					}else{
						newVal = q->minimum() + ((q->maximum() - q->minimum())
							* ev->x()) / q->width();
					};
					q->setValue(newVal);
					e->accept();
				}
			}
		}

	return 0;
}
