#include "Base/envision.h"

//==============================================================================
// void EnVision::handleEventFilter(bool val, QObject *o)
//------------------------------------------------------------------------------
//==============================================================================
void EnVision::handleEventFilter(bool val, QObject *o)
{
		if (val == 0){
			o->removeEventFilter(this);
		}
		if (val == 1){
			o->installEventFilter(this);
		}
	return;
}

//==============================================================================
// bool EnVision::eventFilter(QObject *o, QEvent *e)
//------------------------------------------------------------------------------
//==============================================================================
bool EnVision::eventFilter(QObject *o, QEvent *e)
{
	return 0;
}


//==============================================================================
// void EnVision::dragEnterEvent(QDragEnterEvent *ev)
//------------------------------------------------------------------------------
//==============================================================================
void EnVision::dragEnterEvent(QDragEnterEvent *ev)
{
		ev->accept();
	return;
}

//==============================================================================
// void EnVision::dropEvent(QDropEvent *event)
//------------------------------------------------------------------------------
// This signal is handled in the filemanager
// as ist calls a slot that is dealing with files
//==============================================================================
void EnVision::dropEvent(QDropEvent *event)
{
		emit callFilemanager(event);
	return;
}

//==============================================================================
// void EnVision::closeEvent(QCloseEvent *event)
//------------------------------------------------------------------------------
//==============================================================================
void EnVision::closeEvent(QCloseEvent *event)
{

	//not working until we figure out to 
	//put the Message Box on top of another currently
	//active windows.

	/*
		QMessageBox *msgBox = new QMessageBox;
		msgBox->raise();
		QMessageBox::StandardButton resBtn =
		msgBox->question(this, "Warning",
		tr("Close Program?\n"),
		QMessageBox::No | QMessageBox::Yes,
		QMessageBox::Yes);
		if (resBtn != QMessageBox::Yes) {
		event->ignore();
		} else {
		event->accept();
		qApp->closeAllWindows();
		}
	*/

	return;
}


//==============================================================================
// void Image::mouseWheel(QWheelEvent* e)
//------------------------------------------------------------------------------
//==============================================================================
void EnVision::mouseWheel(QWheelEvent* e)
{
		//no singal found yet
		//cout << " !!!" << endl;
		//ui_base->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		//ui_base->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


	

	//ui_base->mdiArea->verticalScrollBar()->blockSignals(false);
	//ui_image->mdiArea->horizontalScrollBar()->blockSignals(false);


	return;
}
