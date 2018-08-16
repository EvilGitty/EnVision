#include "initImage.h"
#include "makros.h"
#include "Base/envision.h"

//render
QVector<ImageAttribute::_image> ImageAttribute::Record;

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
Imageclass::Imageclass(EnVision *main)
{
		this->main = main;
		color = 0;
		shape = 0;
		pixel = 0;
		watcher = 0;
		data = 0;
		zoom = 0;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
Imageclass::~Imageclass()
{
		//watcher->cancel();
		//watcher->waitForFinished();
}

//==============================================================================
// void Imageclass::openExplorer()
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::openExplorer()
{
		QDir dir = CHANNELFOLDER + QString::fromStdString(ImageAttribute::Record[_imgIndex].imgFilename_s) + "//";
		//cout << "absolute path " << dir.absolutePath().toStdString() << endl;
		//QString filename = CHANNELFOLDER + QString::fromStdString(ImageAttribute::Record[_imgIndex].imgFilename_s) + "//";
		QProcess::startDetached(QString("explorer /select, \"%1\"").arg(QDir::toNativeSeparators(dir.absolutePath())));

	return;
}

//==============================================================================
// void Imageclass::guiAccess()
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::guiAccess()
{
		this->ui_base = main->getBaseUI();
		this->ui_plot = main->getPlotUI();
		this->ui_image = main->getImageUI();
	return;
}

//==============================================================================
// void Imageclass::init(ImageAttribute::image record)
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::init(ImageAttribute::_image record)
{
		cout << "! init !" << endl;
		
		//get access to other guis
		this->guiAccess();

		std::cout << " .... " << " samples: " << record.cubeDim[0] << endl;
		std::cout << " .... " << " lines: " << record.cubeDim[1] << endl;
		std::cout << " .... " << " bands: " << record.cubeDim[2] << endl;
		std::cout << " .... " << " OpenCVDataType " << record.opencvDataType << endl;

		out.Log(ui_base, QString(" .... samples: " + QString::number(record.cubeDim[0])));
		out.Log(ui_base, QString(" .... lines: " + QString::number(record.cubeDim[1])));
		out.Log(ui_base, QString(" .... bands: " + QString::number(record.cubeDim[2])));

		ImageAttribute::Record[_imgIndex] = record;

		cvface01 = cv::Mat(_samples, _lines, CV_8UC3, Scalar(0, 0, 0));
		cvface01.copyTo(ImageAttribute::Record[_imgIndex].cvface01);
		ImageAttribute::Record[_imgIndex].imgade_Loaded = 1;

		//------------------------------------------------------------------------
		//define shapes
		shape = new ImageMask(main, ui_image->image);
		shape->updateItem(shape->spoint, QRect(0, 0, 1, 1), QPolygonF());
		shape->updateItem(shape->rectangle, QRect(0, 0, 1, 1), QPolygonF());
		shape->updateItem(shape->ellipse, QRect(0, 0, 1, 1), QPolygonF());
		QPolygonF polygon; polygon << QPointF(0, 50) << QPointF(20, 80);
		shape->updateItem(shape->polygon, QRect(), polygon);

		ImageAttribute::Record[_imgIndex].visual.shape = shape;														//ImageMask 

		//------------------------------------------------------------------------
		//define plot
		pixel = new Plot(main);
		ImageAttribute::Record[_imgIndex].pixel_list.push_back({ 0, 0, 0, "show", "Single Point" });
		main->ImageGui::Record[_imgIndex].scroll = 1;
		pixel->init();
		pixel->displayPlot();
		//ImageAttribute::Record[_imgIndex].visual.pixel = pixel;														//Plot 

		//------------------------------------------------------------------------
		//define colormap
		color = new ImageColormap(main);

		ImageAttribute::Record[_imgIndex].visual.color = color;														//Plot 

		//------------------------------------------------------------------------
		//load zoom capability
		zoom = new Graphics_view_zoom(ui_image->image);

		ImageAttribute::Record[_imgIndex].visual.zoom = zoom;														//Plot 

		//------------------------------------------------------------------------
		//change ImageColormap
		QObject::connect(ui_image->comboBox_ImageColormap, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::activated),
			[=](const QString &text){ updateImage(); Qt::UniqueConnection; });

		//------------------------------------------------------------------------
		//change Geometry
		QObject::connect(ui_image->comboBox_plotGeometry, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::activated),
			[=](const QString &text){ handleGeometryCombobox(); Qt::UniqueConnection; });


		//image_setInversion(cv::Mat img)
		QObject::connect(ui_image->checkBox_negative, &QCheckBox::stateChanged, [this](int state){ updateImage(); Qt::UniqueConnection; });

		//image_setInversion(cv::Mat img)
		QObject::connect(ui_image->checkBox_saturation, &QCheckBox::stateChanged, [this](int state){ updateImage(); Qt::UniqueConnection; });

		//------------------------------------------------------------------------
		//change brightness
		QObject::connect(ui_image->hSlider_brightness, &QSlider::valueChanged, [=]{
			updateImage(); Qt::UniqueConnection; });

		//------------------------------------------------------------------------
		//change contrast
		QObject::connect(ui_image->hSlider_contrast, &QSlider::valueChanged, [=]{
			updateImage(); Qt::UniqueConnection; });

		//------------------------------------------------------------------------
		//change gamma
		QObject::connect(ui_image->hSlider_gamma, &QSlider::valueChanged, [=]{
			updateImage(); Qt::UniqueConnection; });

		//------------------------------------------------------------------------
		//change gamma
		QObject::connect(ui_image->buttonGroup_mouseInteraction, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), [=](int id) {
			mouseBehavior(id); Qt::UniqueConnection; });

		//------------------------------------------------------------------------
		//reset brightness and contrast
		QObject::connect(ui_image->pushButton_resetBrightness, &QPushButton::clicked, [=]{
		ui_image->hSlider_brightness->setValue(0);
		ui_image->hSlider_contrast->setValue(0);
		ui_image->hSlider_gamma->setValue(100); Qt::UniqueConnection; });

		//------------------------------------------------------------------------
		//switch channel
		QObject::connect(ui_image->hSlider_channel, &QSlider::valueChanged, [this](int channel) { 	getChannel(channel); Qt::UniqueConnection; });

		//QObject::connect(ui_image->pushButton_startPos, SIGNAL(clicked()), this, SLOT(zoomIn()), Qt::UniqueConnection);
		//QObject::connect(ui_image->pushButton_resetZoom, SIGNAL(clicked()), this, SLOT(resetZoom()), Qt::UniqueConnection);

		QObject::connect(ui_image->pushButton_thumbnailFolder, SIGNAL(clicked()), this, SLOT(openExplorer()), Qt::UniqueConnection);
		QObject::connect(ui_image->listWidget_spectralIndex, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(activateThumbnail(QListWidgetItem*)), Qt::UniqueConnection);

		QImage dummyimg = QImage(_samples, _samples, QImage::Format_RGB888);
		ImageAttribute::Record[_imgIndex].qface01 = dummyimg;
		displayImage(dummyimg);

		getChannel(ui_image->hSlider_channel->value());
		//initThumbnail();

		ui_image->hSlider_channel->installEventFilter(this);
		ui_image->hSlider_gamma->installEventFilter(this);
		ui_image->hSlider_contrast->installEventFilter(this);
		ui_image->hSlider_brightness->installEventFilter(this);
	return;
}

//==============================================================================
// void Imageclass::displayImage(QImage image )
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::displayImage(QImage image)
{
		if (ImageAttribute::Record[_imgIndex].imgade_Loaded == 1){

			//specify the grid representing the image
			buildMap(100, 100);

			//set all axes and define range
			ui_image->hSlider_channel->setRange(0, (int)_channels - 1);
	
			//update a shape item
			handleGeometryCombobox();
			//how to resize https://stackoverflow.com/questions/32192607/how-to-use-itemchange-from-qgraphicsitem-in-qt
	}
	return;
}

//==============================================================================
// void Imageclass::finished()
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::finishedTiles()
{
		//shape->scene->setSceneRect(shape->scene->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents

		//QPixmap pix = shape->pixmapitem->pixmap();
		//image = pix.toImage();

		//ImageAttribute::Record[_imgIndex].qface01 = image;
		ImageAttribute::Record[_imgIndex].cvface01 = cvface01;
		//cout << image.width() << " " << image.height() << endl;

		//delete tiles for perfomance
		/*
		int tileindex = 1;
		while (tileindex < shape->imageTileList.size()){
			shape->scene->removeItem(shape->imageTileList[tileindex]);
			++tileindex;
		}
		//QImage img = QImage((const uchar*)cvface01.data, cvface01.cols, cvface01.rows, cvface01.step, QImage::Format_RGB888); //Format_RGB888
		//shape->imageTileList[0]->setPixmap(QPixmap::fromImage(img));
		//shape->imageTileList[0]->setZValue(11);
		*/



		/*
		//display all items on the scene
		QList<QGraphicsItem *> li;
		li.clear();
		QList<QGraphicsItem *> listing = shape->scene->items();
		cout << " listing " << listing.size() << endl;
		for (int o = 0; o<listing.size(); o++) {
			cout << listing[o] << endl;
		}
		*/


		//saveChannel();

		//watcher = new QFutureWatcher<int>();
		//data = new ImagetileThread(main, this);

		/*
		if ((watcher != 0)){
			if (watcher->isRunning()){
				watcher->cancel();
				delete watcher;
				if (data != 0){
					delete data;
				}
			}
		}
		*/

	return;
}

//==============================================================================
// void Imageclass::showCubeFace01(const int tileindex, const QVector<int> blockstart, const QVector<int> blockend, cv::Mat mat)
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::showCubeFace01(const int tileindex, const QVector<int> blockstart, const QVector<int> blockend, cv::Mat mat)
{
		//this is the original tile that should stay untouched
		mat.copyTo(cvface01(Rect(int(blockstart[1]), int(blockstart[0]), (mat).cols, (mat).rows)));


		//with immediate updates
		cv::Mat Img_Converted = color->image_setBrightnessContrast(mat, saturation);
		color->image_setInversion(Img_Converted);
		QImage img = QImage((const uchar*)Img_Converted.data, Img_Converted.cols, Img_Converted.rows, Img_Converted.step, QImage::Format_RGB888); //Format_RGB888

		//without immidiate updatess
		//QImage img = QImage((const uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888); //Format_RGB888

		if ((_numberOfTiles_x * _numberOfTiles_y) <= (shape->imageTileList.size())){
			//cout << " SIZE 1 " << (_numberOfTiles_x * _numberOfTiles_y) << " " << (shape->imageTileList.size()) << endl;
			shape->scene->removeItem(shape->imageTileList[tileindex]);
			shape->updatePixmap(img, blockstart[1], blockstart[0]);
			shape->imageTileList.replace(tileindex, shape->pixmapitem);
		}else{
			//cout << " SIZE 2 " << (_numberOfTiles_x * _numberOfTiles_y) << " " << (shape->imageTileList.size()) << endl;
			shape->updatePixmap(img, blockstart[1], blockstart[0]);
			shape->imageTileList.append(shape->pixmapitem);
		}
		//cout << "shape->imageTileList.size(): "  << shape->imageTileList.size() << endl;
	return;
}

//==============================================================================
// void Imageclass::getChannel(int channel)
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::getChannel(int channel)
{
		//cout << " channel: " << channel << endl;
		if ((channel < 0) || (channel > _channels)){
			channel = ui_image->hSlider_channel->value();
		}

		
		int indexTab = ui_image->tabWidget_image->currentIndex();
		_imgIndex = indexTab;

		/*
		ImageAttribute::Record[_imgIndex].visual.shape = shape;														//ImageMask 
		//ImageAttribute::Record[_imgIndex].visual.pixel = pixel;													//Plot 
		ImageAttribute::Record[_imgIndex].visual.color = color;														//color 
		ImageAttribute::Record[_imgIndex].visual.zoom = zoom;														//zoom 
		*/

		ImageAttribute::Record[_imgIndex].cvface01.copyTo(cvface01);
		image = ImageAttribute::Record[_imgIndex].qface01;

		if ((this->watcher != 0)){
			if (watcher->isFinished()==false){
				return;
			}
		}

		this->watcher = new QFutureWatcher<int>();
		this->data = new ImagetileThread(main, this);

		//uncommenting updateUpdate discouraged because of peformance
		QObject::connect(this->data, &ImagetileThread::finished, this->data, &QObject::deleteLater);
		QObject::connect(watcher, &QFutureWatcher<int>::finished, [=]{
			finishedTiles(); /*updateImage();*/ Qt::UniqueConnection; });

		QVector<int> param1;
		//start x
		param1.push_back(0);
		//limit x
		param1.push_back(_numberOfTiles_x);
		//start y
		param1.push_back(0);
		//limit y
		param1.push_back(_numberOfTiles_y);

		watcher->setFuture(QtConcurrent::run(this->data, &ImagetileThread::loadCubeFace01,
			QVector<int>(param1),
			int(channel)));
		
		//debug
		/* 
		cout << "numberOfTiles_x: "<<  numberOfTiles_x << " oddTile_x:" << oddTile_x << endl;
		cout << "0: " << 0 << " " << "floor(numberOfTiles_x/2): " << floor(numberOfTiles_x/2)  <<  endl;
		cout << "floor(numberOfTiles_x/2): " << floor(numberOfTiles_x / 2) << " " << "(numberOfTiles_x-1): " << (numberOfTiles_x - 1) << endl;
		*/
	return;
}

//==============================================================================
// void Imageclass::buildMap(QVector<long> blocksize, QVector<int> param)
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::buildMap(int blocksize_x, int blocksize_y)
{
		//set blocksize in y
		blocksize_y = floor(blocksize_y);
		//calculate the maximum number of tiles in y
		size_t numberOfTiles_y = floor(_samples / (blocksize_y));

		//set blocksize in x
		blocksize_x = floor(blocksize_x);
		//calculate the maximum number of tiles in x
		size_t numberOfTiles_x = floor(_lines / (blocksize_x));

		size_t oddTile_y = (_samples %  blocksize_y);
		//the image can't divided in equal parts, so one piece is added
		if (oddTile_y > 0){
			numberOfTiles_y = numberOfTiles_y + 1;
		}
		else{
			oddTile_y = blocksize_y;
		}
		ImageAttribute::Record[_imgIndex].imgtile.numberOfTiles_y = numberOfTiles_y;

		size_t oddTile_x = (_lines % blocksize_x);
		if (oddTile_x > 0){
			numberOfTiles_x = numberOfTiles_x + 1;
		}
		else{
			oddTile_x = blocksize_x;
		}
		ImageAttribute::Record[_imgIndex].imgtile.numberOfTiles_x = numberOfTiles_x;

		ImageAttribute::Record[_imgIndex].tile_x.resize(numberOfTiles_x);
		ImageAttribute::Record[_imgIndex].tile_y.resize(numberOfTiles_y);
		long start_y = 0;
		long limit_y = 0;
		long start_x = 0;
		long limit_x = 0;

		for (size_t countTiles_y = 0; countTiles_y < numberOfTiles_y; ++countTiles_y){

			start_y = countTiles_y*blocksize_y;						//start y
			//reaching the final odd data: the blockend is truncated
			if (countTiles_y == (numberOfTiles_y - 1)){
				limit_y = start_y + oddTile_y;
			} else {
				limit_y = start_y + blocksize_y;					//blocksize y
			}

			ImageAttribute::Record[_imgIndex].imgtile.start = start_y;
			ImageAttribute::Record[_imgIndex].imgtile.limit = limit_y;
			ImageAttribute::Record[_imgIndex].tile_y[countTiles_y] = ImageAttribute::Record[_imgIndex].imgtile;

			for (size_t countTiles_x = 0; countTiles_x <numberOfTiles_x; ++countTiles_x){

				start_x = countTiles_x*blocksize_x;					//start x
				//reaching the final odd data: the blockend is truncated
				if (countTiles_x == (numberOfTiles_x - 1)){
					limit_x = start_x + oddTile_x;
				} else {
					limit_x = start_x + blocksize_x;				//blocksize x
				}

				ImageAttribute::Record[_imgIndex].imgtile.start = start_x;
				ImageAttribute::Record[_imgIndex].imgtile.limit = limit_x;
				ImageAttribute::Record[_imgIndex].tile_x[countTiles_x] = ImageAttribute::Record[_imgIndex].imgtile;
			}
		}

		shape->imageTileList.reserve(numberOfTiles_x + numberOfTiles_y + 10);


	return;
}

//==============================================================================
// void Imageclass::getPixel(int x, int y, int z)
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::getPixel()
{
		pixel->plotPixel();
	return;
}

//==============================================================================
// void Imageclass::updateImage()
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::updateImage()
{
	if (ImageAttribute::Record[_imgIndex].imgade_Loaded == 1){

		cv::Mat tempMat;

		ImageAttribute::Record[_imgIndex].cvface01.copyTo(tempMat);


		/*
		watcher = new QFutureWatcher<int>();
		data = new ImagetileThread(main, this);

		QObject::connect(data, &ImagetileThread::finished, data, &QObject::deleteLater);
		QObject::connect(watcher, &QFutureWatcher<int>::finished, [=]{
		finished(); Qt::UniqueConnection;});


			QVector<int> param1;
			//start x
			param1.push_back(0);
			//limit x
			param1.push_back(_numberOfTiles_x);
			//start y
			param1.push_back(0);
			//limit y
			param1.push_back(_numberOfTiles_y);

			watcher->setFuture(QtConcurrent::run(data, &ImagetileThread::loadCubeFace01,
				QVector<int>(param1),
				int(channel)));

		*/


		
		saturation = ui_image->checkBox_saturation->isChecked();

		cv::Mat Img_Converted = color->image_setBrightnessContrast(tempMat, saturation);

		color->image_setInversion(Img_Converted);

		QImage img((const uchar*)Img_Converted.data, Img_Converted.cols, Img_Converted.rows, Img_Converted.step, QImage::Format_RGB888);

		if (img.isNull() == 1){ return;}

		//delete tiles for perfomance
		/*
		int tileindex = shape->imageTileList.size()-1;
		if (shape->imageTileList.size() > 1){
			while (tileindex > 0){
				shape->scene->removeItem(shape->imageTileList[tileindex]);
				shape->imageTileList.removeAt(tileindex);
				--tileindex;
			}
		}
		*/
		//cout << "shape->imageTileList.size() : "<< shape->imageTileList.size() << endl;

		shape->imageTileList[0]->setPixmap(QPixmap::fromImage(img));
		shape->imageTileList[0]->setZValue(11);
	}

	return;
}

//==============================================================================
// void Imageclass::saveChannel()
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::saveChannel()
	{
		/*
		if (ImageAttribute::Record[_imgIndex].imgade_Loaded == 1){
		QString filename = QString::fromStdString(ImageAttribute::Record[_imgIndex].imgFilename_s) + "//";

		if (QDir(CHANNELFOLDER + filename).exists() == false) {
		QDir().mkdir(CHANNELFOLDER + filename);
		}

		QString ImageColormap = ui_image->comboBox_ImageColormap->currentText();
		QString channel = QString::number(ui_image->hSlider_channel->value());

		QFile file(QString(CHANNELFOLDER) + filename + "#" + channel + "_" + ImageColormap + ".jpg");
		file.open(QIODevice::WriteOnly);

		//QPixmap fullPixmap = spareImg->pixmap();
		QPixmap fullPixmap = spareImage;
		QPixmap smallPixmap = fullPixmap.copy((double)zoomIn_startPos, 0, 100, _samples);

		fullPixmap.save(&file, "JPG");
		updateThumbnail(smallPixmap);
		}
		*/
	return;
}

//==============================================================================
// void Imageclass::loadChannel()
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::loadChannel()
{
		QString filename = "yourFile.jpg";
		QPixmap pixmap;
		pixmap.load(QString(CHANNELFOLDER) + filename);

	return;
}

//==============================================================================
// inline cv::Mat QImageToCvMat(const QImage &inImage, bool inCloneImageData)
//------------------------------------------------------------------------------
//==============================================================================
inline cv::Mat QImageToCvMat(const QImage &inImage, bool inCloneImageData)
{
		switch (inImage.format())
		{
			// 8-bit, 4 channel
		case QImage::Format_ARGB32:
		case QImage::Format_ARGB32_Premultiplied:
		{
			cv::Mat  mat(inImage.height(), inImage.width(),
			CV_8UC4,
			const_cast<uchar*>(inImage.bits()),
			static_cast<size_t>(inImage.bytesPerLine())
			);
			return (inCloneImageData ? mat.clone() : mat);
		}

			// 8-bit, 3 channel
		case QImage::Format_RGB32:
		case QImage::Format_RGB888:
		{
		if (!inCloneImageData){
			qWarning() << "ASM::QImageToCvMat() - Conversion requires cloning because we use a temporary QImage";
		 }

		QImage   swapped = inImage;
		if (inImage.format() == QImage::Format_RGB32){
			swapped = swapped.convertToFormat(QImage::Format_RGB888);
		}
		swapped = swapped.rgbSwapped();
			return cv::Mat(swapped.height(), swapped.width(),
			CV_8UC3, const_cast<uchar*>(swapped.bits()),
			static_cast<size_t>(swapped.bytesPerLine())).clone();
		}

			// 8-bit, 1 channel
		case QImage::Format_Indexed8:
		{
			cv::Mat  mat(inImage.height(), inImage.width(),
			CV_8UC1, const_cast<uchar*>(inImage.bits()),
			static_cast<size_t>(inImage.bytesPerLine())
			);
			return (inCloneImageData ? mat.clone() : mat);
		}

		default:
			qWarning() << "ASM::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
			break;
		}

	return cv::Mat();
}

//==============================================================================
// void Imageclass::mouseBehavior(int id)
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::mouseBehavior(int id)
{
		//ids are automatically assigned by Qt
		//cout << id << endl;
		if (id == -2){	//draw
			main->ImageGui::Record[_imgIndex].scroll = 0;
			main->ImageGui::Record[_imgIndex].draw = 1;
		}
		if (id == -3){ //scroll
			main->ImageGui::Record[_imgIndex].scroll = 1;
			main->ImageGui::Record[_imgIndex].draw = 0;
		}
	return;
}
//==============================================================================
// void Imageclass::setGeometryCombobox()
//------------------------------------------------------------------------------
//==============================================================================
void Imageclass::handleGeometryCombobox()
{
		//enable all items again
		QStandardItemModel *model = dynamic_cast< QStandardItemModel * >(ui_image->comboBox_plotGeometry->model());
		int itemIndex = 0;

		while (itemIndex < ui_image->comboBox_plotGeometry->count()){
			QStandardItem *item = model->item(itemIndex, 0);
			item->setEnabled(true);
			++itemIndex;
		}

		QString geometry = ui_image->comboBox_plotGeometry->currentText();

		if (geometry.compare("Single Point") == 0) {
			shape->updateItem(shape->spoint, QRect(shape->pos_currentItem.x(), shape->pos_currentItem.y(), 1, 1), QPolygonF());
			QRectF bound = shape->spoint->boundingRect();
			ImageAttribute::Record[_imgIndex].pixel_list.resize(1);
		}
		if (geometry.compare("Rectangle") == 0) {
			shape->updateItem(shape->rectangle, QRect(shape->pos_currentItem.x(), shape->pos_currentItem.y(), 10, 10), QPolygonF());
		}
		if (geometry.compare("Ellipse") == 0) {
			shape->updateItem(shape->ellipse, QRect(shape->pos_currentItem.x(), shape->pos_currentItem.y(), 13, 25), QPolygonF());
		}
		if (geometry.compare("Polygon") == 0) {
			shape->updateItem(shape->polygon, QRect(shape->pos_currentItem.x(), shape->pos_currentItem.y(), 0, 0), QPolygonF());
		}

		itemIndex = ui_image->comboBox_plotGeometry->currentIndex();
		QStandardItem *item = model->item(itemIndex, 0);
		item->setEnabled(false);

		return;
}
