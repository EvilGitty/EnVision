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
// cv::Mat ImageColormap::image_setBrightnessContrast(cv::Mat Img, bool saturation)
//------------------------------------------------------------------------------
//==============================================================================
cv::Mat ImageColormap::image_setBrightnessContrast(cv::Mat Img, bool saturation)
{
		double alpha = ui_image->hSlider_contrast->value();
		double beta = ui_image->hSlider_brightness->value();
		double gamma = ui_image->hSlider_gamma->value();

		cv::Vec3b mask_color = cv::Vec3b(0, 0, 0);

		ui_image->label_contrast->setText((QString::number((alpha) / ui_image->hSlider_contrast->maximum() * 100) + "%"));
		ui_image->label_brightness->setText((QString::number((beta / ui_image->hSlider_brightness->maximum()) * 100) + "%"));
		ui_image->label_gamma->setText((QString::number((gamma / ui_image->hSlider_gamma->maximum()) * 100) + "%"));
	
		//Gamma
		Mat lut_matrix(1, 256, CV_8UC1);
		uchar * ptr = lut_matrix.ptr();
		for (int i = 0; i < 256; i++){
			ptr[i] = (int)(pow((double)i / 255.0, (gamma + 0.5) / ui_image->hSlider_gamma->maximum()) * 255.0);
		}
		LUT(Img, lut_matrix, Img);
		//imshow("Gamma", Img);
		
		//Brightness and Contrast
		Img.convertTo(Img, CV_8UC3, ((alpha + 10) / ui_image->hSlider_contrast->maximum() * 10), beta);
		//imshow("Contrast + Brightness", Img);
		
		cv::Mat mask1 = cv::Mat(Img.rows, Img.cols, CV_8UC1, 255);
		//cv::Mat mask2 = Mat::zeros(Img.rows, Img.cols, CV_8UC1);
		//cv::Mat mask3 = Mat::zeros(Img.rows, Img.cols, CV_8UC1);

		vector<Mat> channels(3);
		split(Img, channels);

		//saturation
		if (saturation == 1){
			mask_color = sat_color;
			threshold(channels[0], mask1, 254, 255, cv::THRESH_BINARY_INV);
		//	threshold(channels[1], mask2, 50, 255, cv::THRESH_BINARY);
		//	threshold(channels[2], mask3, 50, 255, cv::THRESH_BINARY);

		//	imshow("thresh0", mask1);
		//	imshow("thresh1", mask2);
		//	imshow("thresh2", mask3);
		}

		image_changeColormap();

		//Gray
		if (colorID == -1) {

			std::vector<cv::Mat> array_to_merge;
			array_to_merge.push_back(channels[0]);
			array_to_merge.push_back(channels[0]);
			array_to_merge.push_back(channels[0]);
			cv::merge(array_to_merge, Img);
		}
		//Color
		if (colorID >-1) {
			applyColorMap(Img, Img, colorID);
		}

		cvtColor(Img, Img, CV_BGR2RGB);
		
		cv::Mat out(Img.size(), Img.type(), mask_color);
		Img.copyTo(out, mask1);
		
	return out;
}




/* determine background


int main(int argc, char** argv) {
Mat img = imread("binary image");
Mat nonZeroCoordinates;
findNonZero(img, nonZeroCoordinates);
for (int i = 0; i < nonZeroCoordinates.total(); i++ ) {
cout << "Zero#" << i << ": " << nonZeroCoordinates.at<Point>(i).x << ", " << nonZeroCoordinates.at<Point>(i).y << endl;
}
return 0;
}

*/

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
