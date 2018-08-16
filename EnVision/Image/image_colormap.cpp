#include "image_colormap.h"
#include "Base/envision.h"

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
ImageColormap::ImageColormap(EnVision* main)
{
	this->main = main;
	this->ui_image = main->getImageUI();
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
ImageColormap::~ImageColormap()
{
}

//==============================================================================
// cv::Mat ImageColormap::Image_setBrightnessContrast(cv::Mat Img, cv::Mat Img_ConvertedTile)
//------------------------------------------------------------------------------
//==============================================================================
cv::Mat ImageColormap::image_setBrightnessContrast(cv::Mat Img, int colorId, bool saturation)
{
		double alpha = ui_image->hSlider_contrast->value();
		double beta = ui_image->hSlider_brightness->value();

		mask1 = Mat::zeros(Img.rows, Img.cols, CV_8UC3);
		mask2 = Mat::zeros(Img.rows, Img.cols, CV_8UC1);

		cv::Vec3b mask_color = cv::Vec3b(0, 0, 0);
	
		ui_image->label_contrast->setText((QString::number((alpha) / ui_image->hSlider_contrast->maximum() * 100) + "%"));
		ui_image->label_brightness->setText((QString::number((beta / ui_image->hSlider_brightness->maximum()) * 100) + "%"));


		/*
		if ((ui_image->checkBox_saturation->isChecked() == 1)){
			cv::Vec3b val = sat_color;
		}
		*/

		for (int y = 0; y < Img.rows; y++){
			for (int x = 0; x < Img.cols; x++){

				//brightness and contrast
				for (int c = 0; c < 3; c++){
					Img.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((alpha + 10) / 10 * (Img.at<Vec3b>(y, x)[c]) + beta);
				}

				//saturation
				if (saturation == 1){
					if (Img.at<Vec3b>(y, x)[0] == 255) {
						//mask1.at< cv::Vec3b >(y, x) = sat_color;

						mask_color = sat_color;

						//cout << "! " << (int)mask1.at< cv::Vec3b >(y, x)[0] << " " << (int)mask1.at< cv::Vec3b >(y, x)[1] << " " << (int)mask1.at< cv::Vec3b >(y, x)[2] << endl;
					}else{
						mask2.at< char >(y, x) = 255;
					}
				} else{
					mask2.at< char >(y, x) = 255;
				}
				
			}
		}

		Img = image_setChannels(Img, colorId);
		cv::Mat res(Img.size(), Img.type(), mask_color);
		Img.copyTo(res, mask2);

	return res;
}

//==============================================================================
// cv::Mat ImageColormap::image_setInversion(cv::Mat img)
//------------------------------------------------------------------------------
//==============================================================================
cv::Mat ImageColormap::image_setInversion(cv::Mat img)
{
		if (ui_image->checkBox_negative->isChecked() == 1){
			bitwise_not(img, img);
		}
	return img;
}

//==============================================================================
// cv::Mat ImageColormap::image_setChannels(cv::Mat Img, int colorID)
//------------------------------------------------------------------------------
//==============================================================================
cv::Mat ImageColormap::image_setChannels(cv::Mat Img, int colorID)
{
		cv::Mat Img_Converted;
		cv::Mat Img2;
		//cout << "channels: " << Img.channels() << endl;
		if (colorID == -1) {

			vector<Mat> channels(3);
			split(Img, channels);
			std::vector<cv::Mat> array_to_merge;
			array_to_merge.push_back(channels[0]);
			array_to_merge.push_back(channels[0]);
			array_to_merge.push_back(channels[0]);
			cv::merge(array_to_merge, Img2);
			cvtColor(Img2, Img_Converted, CV_BGR2RGB);
		}
		else if (colorID < 13) {
			applyColorMap(Img, Img2, colorID);
			cvtColor(Img2, Img_Converted, CV_BGR2RGB);
		}
		else if (colorID > 99){
			//future
		}

	return Img_Converted;
}

//==============================================================================
// int ImageColormap::image_changeColormap()
//------------------------------------------------------------------------------
//==============================================================================
int ImageColormap::image_changeColormap()
{

		//enable all items again
		QStandardItemModel *model = dynamic_cast< QStandardItemModel * >(ui_image->comboBox_ImageColormap->model());
		int itemIndex = 0;

		while (itemIndex < ui_image->comboBox_ImageColormap->count()){
			QStandardItem *item = model->item(itemIndex, 0);
			item->setEnabled(true);
			++itemIndex;
		}
		
		QString textCombobox = ui_image->comboBox_ImageColormap->currentText();

		if (textCombobox.compare("Gray") == 0) {
			colorID = -1;
			icon = QIcon("./Resources/ImageColormap_gray.png");
			sat_color = cv::Vec3b(255, 0, 0);
		}
		if ((textCombobox.compare("HSV") == 0))  {
			colorID = 9;
			icon = QIcon("./Resources/ImageColormap_hsv.png");
			sat_color = cv::Vec3b(0, 0, 0);
		}
		if ((textCombobox.compare("Jet") == 0)) {
			colorID = 2;
			icon = QIcon("./Resources/ImageColormap_jet.png");
			sat_color = cv::Vec3b(0, 0, 0);
		}
		if ((textCombobox.compare("Bone") == 0)) {
			colorID = 1;
			icon = QIcon("./Resources/ImageColormap_bone.png");
			sat_color = cv::Vec3b(0, 0, 0);
		}
		if ((textCombobox.compare("Rainbow") == 0)) {
			colorID = 4;
			icon = QIcon("./Resources/ImageColormap_rainbow.png");
			sat_color = cv::Vec3b(0, 0, 0);
		}
		if ((textCombobox.compare("Ocean") == 0)) {
			colorID = 5;
			icon = QIcon("./Resources/ImageColormap_ocean.png");
			sat_color = cv::Vec3b(0, 0, 0);
		}
		if ((textCombobox.compare("Spring") == 0)) {
			colorID = 7;
			icon = QIcon("./Resources/ImageColormap_spring.png");
			sat_color = cv::Vec3b(0, 0, 0);
		}
		if ((textCombobox.compare("Summer") == 0)) {
			colorID = 6;
			icon = QIcon("./Resources/ImageColormap_summer.png");
			sat_color = cv::Vec3b(0, 0, 0);
		}
		if ((textCombobox.compare("Autumn") == 0)) {
			colorID = 0;
			icon = QIcon("./Resources/ImageColormap_autumn.png");
			sat_color = cv::Vec3b(0, 0, 0);
		}
		if ((textCombobox.compare("Winter") == 0)) {
			colorID = 3;
			icon = QIcon("./Resources/ImageColormap_winter.png");
			sat_color = cv::Vec3b(0, 0, 0);
		}
		if ((textCombobox.compare("Cool") == 0)) {
			colorID = 8;
			icon = QIcon("./Resources/ImageColormap_cool.png");
			sat_color = cv::Vec3b(0, 0, 0);
		}
		if ((textCombobox.compare("Hot") == 0)) {
			colorID = 11;
			icon = QIcon("./Resources/ImageColormap_hot.png");
			sat_color = cv::Vec3b(0, 0, 0);
		}
		if ((textCombobox.compare("Pink") == 0)) {
			colorID = 10;
			icon = QIcon("./Resources/ImageColormap_pink.png");
			sat_color = cv::Vec3b(0, 0, 0);
		}
		if ((textCombobox.compare("Parula") == 0)) {
			colorID = 12;
			icon = QIcon("./Resources/ImageColormap_parula.png");
			sat_color = cv::Vec3b(0, 0, 0);
		}
		
		itemIndex = ui_image->comboBox_ImageColormap->currentIndex();
		QStandardItem *item = model->item(itemIndex, 0);
		item->setEnabled(false);
		
	return colorID;
}
