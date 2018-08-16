#include "image_thumbnail.h"
#include "Base/envision.h"


//==============================================================================
// void Imageclass::initThumbnail()
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::initThumbnail()
{
		//populaste thumbnail list with empty dummy items. Advantage of the dummy items:
		//real items can later be inserted in a sorted order rather than just added.
		int row = 0;
		while (row < _channels){
			ui_image->listWidget_spectralIndex->addItem(new QListWidgetItem(QIcon(""), ""));
			ui_image->listWidget_spectralIndex->item(ui_image->listWidget_spectralIndex->count() - 1)->setHidden(1);
			//ui_image->listWidget_spectralIndex->currentItem()->setHidden(1);
			++row;
		}
	return;
}
//==============================================================================
// void Imageclass::activateThumbnail(QListWidgetItem*)
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::activateThumbnail(QListWidgetItem* item)
{
		QString str = item->text();
		int	row = ui_image->listWidget_spectralIndex->row(item);
		cout << " row " <<  row << endl;
		if ((row > -1) && (row <= _channels)){
			ui_image->hSlider_channel->setValue(row);

		}
	return;
}


//==============================================================================
// void Imageclass::updateThumbnail(QPixmap smallPixmap)
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::updateThumbnail(QPixmap smallPixmap)
{

		if (ImageAttribute::Record[_imgIndex].imgade_Loaded == 1){
			QObject* obj = sender();
			if (obj == ui_image->hSlider_channel) {
				cout << " YES ! " << endl;

			}
			else{
				cout << " NO ! " << endl;

			}

			QString filename = CHANNELFOLDER + QString::fromStdString(ImageAttribute::Record[_imgIndex].imgFilename_s) + "//";

			QString ImageColormap = ui_image->comboBox_ImageColormap->currentText();
			QString channel = QString::number(ui_image->hSlider_channel->value());

			QString description = "#" + channel + "_" + ImageColormap;

			//ui_image->listWidget_spectralIndex->setViewMode(QListWidget::IconMode);
			ui_image->listWidget_spectralIndex->setIconSize(QSize(200, 200));
			//ui_image->listWidget_spectralIndex->setResizeMode(QListWidget::Adjust);

			//populaste thumbnail list with real item replacing the dummy items from initialization.
			QList<QListWidgetItem*> list = ui_image->listWidget_spectralIndex->findItems(description, Qt::MatchExactly);
			if (list.size() > 0){
				//delete old item
				ui_image->listWidget_spectralIndex->removeItemWidget(list[0]);
				//insert new item
				list[0] = new QListWidgetItem(QIcon(smallPixmap), description);
			}
			else {
				//add new item
				ui_image->listWidget_spectralIndex->insertItem(ui_image->hSlider_channel->value(), new QListWidgetItem(QIcon(smallPixmap), description));
				ui_image->listWidget_spectralIndex->setCurrentRow(ui_image->hSlider_channel->value());
				ui_image->listWidget_spectralIndex->currentItem()->setHidden(0);
			}
		}
	return;
}
