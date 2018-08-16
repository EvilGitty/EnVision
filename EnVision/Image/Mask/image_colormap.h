#ifndef IMG_COLORMAP_H
#define IMG_COLORMAP_H

#include <iostream>
#include <QString>
#include <QStringList>

#include "Gui/gui_master.h"
#include "ui_image_widget.h"

class EnVision;

class ImageColormap
{
	public:
	
		ImageColormap(EnVision* main);
		~ImageColormap();

		cv::Mat image_setBrightnessContrast(cv::Mat Img, bool saturation);

		// convert to negative
		cv::Mat image_setInversion(cv::Mat img);

		//ImageColormap
		int image_changeColormap();

		cv::Mat mask2;

	private:

		QIcon icon;
		int colorID = -1;

		cv::Vec3b sat_color = cv::Vec3b(0, 0, 0);

		EnVision* main;
		Ui::EnVision_imageUI* ui_image;
};

#endif //IMG_COLORMAP_H
