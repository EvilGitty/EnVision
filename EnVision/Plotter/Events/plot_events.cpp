#include "Image/initImage.h"
#include "Base/envision.h"

//==============================================================================
// void Plot::dragEnterEvent(QDragEnterEvent *ev)
//------------------------------------------------------------------------------
//==============================================================================
void Plot::dragEnterEvent(QDragEnterEvent *ev)
{
	return;
}

//==============================================================================
// void Plot::dropEvent(QDropEvent *event)
//------------------------------------------------------------------------------
//==============================================================================
void Plot::dropEvent(QDropEvent *event)
{
	return;
}


//==============================================================================
// void Plot::mouseWheel(QWheelEvent* e)
//------------------------------------------------------------------------------
//==============================================================================
void Plot::mouseWheel(QWheelEvent* e)
{

	return;
}


//==============================================================================
// void Plot::horzScrollBarChanged(int value)
//------------------------------------------------------------------------------
//==============================================================================
void Plot::horzScrollBarChanged(int value)
{
		if (qAbs(ui_plot->plot->xAxis->range().center() - value / 100.0) > 0.01){
			ui_plot->plot->xAxis->setRange(value / 100.0, ui_plot->plot->xAxis->range().size(), Qt::AlignCenter);
			ui_plot->plot->replot();
		}

	return;
}


//==============================================================================
// void Plot::vertScrollBarChanged(int value)
//------------------------------------------------------------------------------
//==============================================================================
void Plot::vertScrollBarChanged(int value)
	{
		if (qAbs(ui_plot->plot->yAxis->range().center() + value / 100.0) > 0.01){
			ui_plot->plot->yAxis->setRange(value / 100.0, ui_plot->plot->yAxis->range().size(), Qt::AlignCenter);
			ui_plot->plot->replot();
		}

	return;
}

//==============================================================================
// void Plot::xAxisChanged(QCPRange rangeNew, QCPRange rangeOld)
//------------------------------------------------------------------------------
//==============================================================================
void Plot::xAxisChanged(QCPRange rangeNew, QCPRange rangeOld)
{
		ui_plot->hScrollBar->setValue(qRound(rangeNew.center()*100.0)); // adjust position of scroll bar slider
		ui_plot->hScrollBar->setPageStep(qRound(rangeNew.size()*100.0)); // adjust size of scroll bar slider
		ui_plot->hScrollBar->setSingleStep(qRound(rangeNew.size()*10)); // adjust size of scroll bar slider

	return;
}

//==============================================================================
//void Plot::yAxisChanged(QCPRange rangeNew, QCPRange rangeOld)
//------------------------------------------------------------------------------
//==============================================================================
void Plot::yAxisChanged(QCPRange rangeNew, QCPRange rangeOld)
{
		ui_plot->vScrollBar->setValue(qRound(rangeNew.center()*100.0)); // adjust position of scroll bar slider
		ui_plot->vScrollBar->setPageStep(qRound(rangeNew.size()*100.0)); // adjust size of scroll bar slider
		ui_plot->vScrollBar->setSingleStep(qRound(rangeNew.size()*10)); // adjust size of scroll bar slider
	return;
}

//==============================================================================
// void Plot::resizeEvent(QResizeEvent *event)
//------------------------------------------------------------------------------
// Reimplementation of the windows reize event
//==============================================================================
void Plot::resizeEvent(QResizeEvent *event)
{

	return;
}

//==============================================================================
// bool Plot::eventFilter(QObject *o, QEvent *e)
//------------------------------------------------------------------------------
//==============================================================================
bool Plot::eventFilter(QObject *o, QEvent *e)
{

	return 0;
}
