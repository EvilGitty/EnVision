#include "filemanager.h"
#include "Base/enVision.h"

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
Filemanager::Filemanager(EnVision *main)
{
		this->main = main;
		this->ui_base = main->getBaseUI();

		imgclass = 0;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
Filemanager::~Filemanager()
{

}

//==============================================================================
// int Filemanager::filterInputFiles(QString extension)
//------------------------------------------------------------------------------
//==============================================================================
int Filemanager::filterInputFiles(QString extension)
{

	if (((QString::compare(extension, "tgd") == 0)
		|| (QString::compare(extension, "img") == 0)
		|| (QString::compare(extension, "hyspex") == 0)
		|| (QString::compare(extension, "mat") == 0)
		|| (QString::compare(extension, "im3") == 0)
		|| (QString::compare(extension, "asd") == 0)
		|| (QString::compare(extension, "cub") == 0)
		|| (QString::compare(extension, "bsq") == 0)
		)) {
		return 1;
	}
	if (((QString::compare(extension, "csv") == 0)
		|| (QString::compare(extension, "xls ") == 0)
		|| (QString::compare(extension, "xlsx") == 0)
		|| (QString::compare(extension, "gpx") == 0)
		|| (QString::compare(extension, "kml") == 0)
		)) {
		return 2;
	}

	return 0;
}

//==============================================================================
// void Filemanager::selectedFiles(QStringList chosenFiles)
//------------------------------------------------------------------------------
// This method uses the file dialog to open image files
//==============================================================================
void Filemanager::selectedFiles(QStringList chosenFiles)
{
		QStringList::Iterator it_file = chosenFiles.begin();
		while (it_file != chosenFiles.end()) {

			QFileInfo fi(*it_file);
			QString thispath = fi.absoluteFilePath();
			QDir thisdir = QFileInfo(thispath).absoluteDir();

			if (filterInputFiles(fi.suffix()) == 1) {
				cout << " :::  " << fi.suffix().toStdString() <<  endl;
				if (ProcessImageFiles(it_file) == 1) {
					addRecentFile(main->execPath + RECENTFILES, *it_file);
				}
			}
			++it_file;
		}
		//getchar();
	return;
}

//==============================================================================
//void Filemanager::droppedFiles(QDropEvent *event)
//------------------------------------------------------------------------------
// Sses the dropped file event (EnVision::dropEvent(QDropEvent *event)) 
// to hangle image files
//==============================================================================
void Filemanager::droppedFiles(QDropEvent *event)
{
		QList< QUrl > urls = event->mimeData()->urls();
		QStringList chosenFiles;
		foreach(QUrl url, urls) {
			qDebug() << url.toString();
			chosenFiles << (url.toString()).remove("file:///");
		}
		if (!(chosenFiles.isEmpty())) {
			selectedFiles(chosenFiles);
		}

	return;
}

//==============================================================================
// bool Filemanager::ProcessImageFiles(QStringList::Iterator &it_file)
//------------------------------------------------------------------------------
//==============================================================================
bool Filemanager::ProcessImageFiles(QStringList::Iterator &it_file)
{
		bool ret = 0;

		//takes care of less usual characters (Uumlaute etc.)
		QByteArray ba = (*it_file).toLatin1();
		const char *imgfilename = ba.data();

		cout << "imgfilename: "<< imgfilename << endl;

		ImageAttribute::record.SpecData = SpecIL_Interface::open("r", imgfilename);
		ImageAttribute::record.SpecData->EnableErrorLog();
		ImageAttribute::record.SpecData->setCubeMaxSize(500000);
		//	ImageAttribute::Image[ImageAttribute::Image.size() - 1].SpecData->setImageProperties("bla",
		//	512, 424, 300, t_SpecHead::t_interleave::IL_BSQ, t_SpecHead::t_data_type::DT_16_UINT);
		ret = ImageAttribute::record.SpecData->read();

		QFileInfo info(*it_file);
		QString filesuffix = info.suffix();

		if (ret != 0) {
			std::cout << " Error in SpecData->read() . File loading stopped." << endl;
		return 0;
		}

		//------------------------------------------------------------------------
		//Load tapSANSi files
		if ((filesuffix.contains("tgd")) == 1) {
			//main->Log("Loading a TapSansi (" + filesuffix + ") file.\n");
			ret = load_tgd(it_file);
		}
		//Load tapSANSi files
		//------------------------------------------------------------------------

		//------------------------------------------------------------------------
		//Load uncalibrated Hyspex files
		else if ((filesuffix.contains("hyspex")) == 1) {
			//main->Log("Loading HySpex uncalibrated (" + filesuffix + ") file.\n");
			ret = load_hySpex_img(it_file, 0);
		}
		//Load uncalibrated Hyspex files
		//------------------------------------------------------------------------

		//------------------------------------------------------------------------
		//Load calibrated Hyspex files
		if ((filesuffix.contains("img")) == 1) {
			//main->Log("Loading HySpex radiance-calibarated (" + filesuffix + ") file.\n");
			ret = load_hySpex_img(it_file, 1);
		}
		//Load calibrated Hyspex files
		//------------------------------------------------------------------------

		//------------------------------------------------------------------------
		//Load Matlab files
		else if ((filesuffix.contains("mat")) == 1) {
			//main->Log("Loading Matlab (" + filesuffix + ") file.\n");
			ret = load_mat(it_file);
		}
		//Load Matlab files
		//------------------------------------------------------------------------

		//------------------------------------------------------------------------
		//Load Nuance files
		if ((filesuffix.contains("im3")) == 1) {
			//main->Log("Loading Nuance (" + filesuffix + ") file.\n");
			ret = load_im3(it_file);
		}
		//Load Nuance files
		//------------------------------------------------------------------------

		//------------------------------------------------------------------------
		//Load asd files
		//else if ((filesuffix.contains("asd")) == 1) {
		//	main->Log("Loading ASD Fieldspec (" + filesuffix + ") file.\n");
		//	ret = load_asd(it_file);
		//}
		//Load asd files
		//------------------------------------------------------------------------

		//------------------------------------------------------------------------
		//Load cub files
		//else if ((filesuffix.contains("cub")) == 1) {
		//	main->Log("Loading Cubert (" + filesuffix + ") file.\n");
		//	ret = load_cub(it_file);
		//}
		//Load cub files
		//------------------------------------------------------------------------

		//move to image struct to vector 
		if (ret == 0) {
			int ret = main->activateNewImage();
			imgclass = new Imageclass(main);
			imgclass->init(ImageAttribute::record);		
			img_ref.push_back(imgclass);
			return 0;
		} 
	
	return 1;
}



















//==============================================================================
// void Filemanager::setDefaultDataFolder( void )
//------------------------------------------------------------------------------
//==============================================================================
void Filemanager::setDefaultDataFolder(void)
{
	//Xmlinit *xml = new Xmlinit(main);
	//xml->writeinitFile(main->ImageinitRecord.DefaultPath, ".//data//init//init.xml");
	return;
}

//==============================================================================
// void Filemanager::directoryChanged( QString text )
//------------------------------------------------------------------------------
//==============================================================================
void Filemanager::directoryChanged(QString text)
{
	//findFiles(text, QStringList() << "", "");
	//main->ImageinitRecord.DefaultPath = text;		//bei Aktivierung wird jede neue Pfadwahl sofort als Defaultpath angenommen
	return;
}

//==============================================================================
// bool Filemanager::CheckFileDoubleLoad( QString newfilename )
//------------------------------------------------------------------------------
// Check if input file has already been loaded. Prevent another attempt to load the same file
//==============================================================================
bool Filemanager::CheckFileDoubleLoad(QString newfilename, int val)
{
	//the settings prevent multiple loading of the same file 
	/*
	if (val == 1) {
		return 0;
	}
	else{
		foreach(const QString &str, main->filesLoaded){
			if (str.contains(newfilename) == 1){
				return 1;
			}
		}
	}
	*/
	return 0;
}

//==============================================================================
// void Filemanager::processInputArguments( QStringList InputArgFiles )
//------------------------------------------------------------------------------
//==============================================================================
void Filemanager::processInputArguments(QStringList InputArgFiles)
{
	if (InputArgFiles.size() > 0) {

	}
	return;
}

//==============================================================================
// void Filemanager::openInputArgFiles( QStringList InputArgFiles )
//------------------------------------------------------------------------------
//==============================================================================
void Filemanager::openInputArgFiles(QStringList InputArgFiles)
{
	if (InputArgFiles.size() > 0) {
		foreach(const QString &str, InputArgFiles) {
			QFileInfo checkFile(str);
			if (checkFile.exists() && checkFile.isFile()) {
				QString extension = checkFile.suffix();
				int result = filterInputFiles(extension);
				if (result == 1) {
					cout << "Loading from 'load.txt': " << str.toStdString() << endl;
					selectedFiles(QStringList() << str);
				}
				if (result == 0) {
					cout << "Entry from 'load.txt': " << str.toStdString() << " does not have a vaild file extension.\n";
				}
			}
			else {
				cout << "Entry from 'load.txt': " << str.toStdString() << " is either no file or does not exist at all.\n";
			}
		}
	}
	return;
}


//==============================================================================
// inline std::string checkGpsExtension( std::string imgFilename, std::string imgFilesuffix, std::string key )
//------------------------------------------------------------------------------
// Just a quick check if an associated header file headerfile ".hdr" is present
//==============================================================================
inline std::string checkFileExtension(std::string imgFilename, std::string imgFilesuffix, std::string key)
{
		std::string imgfiletemp = imgFilename;
		std::size_t found = imgfiletemp.rfind(imgFilesuffix);

		if (found != std::string::npos) {
			std::string gpsfiletemp = imgfiletemp.replace(found, imgFilesuffix.length(), key);
			std::string gpsfiletemp2 = imgFilename + "." + key;

			//loof for e.g 20160511_120240_Kalibrierung_AK2_North_000.gpsraw
			QFileInfo checkfile(QString::fromStdString(gpsfiletemp));
			if ((checkfile.exists() == 1) || (checkfile.isFile() == 1)) {
				return gpsfiletemp;
			}

			//loof for e.g 20160511_120240_Kalibrierung_AK2_North_000.tgd.gpsraw
			QFileInfo checkfile2(QString::fromStdString(gpsfiletemp2));
			if ((checkfile2.exists() == 1) || (checkfile2.isFile() == 1)) {
				return gpsfiletemp2;
			}
		}
	return "/";
}






//==============================================================================
// Handling of recently loaded files
//------------------------------------------------------------------------------
//==============================================================================

//==============================================================================
// void Filemanager::openRecentFile( void )
//------------------------------------------------------------------------------
//==============================================================================
void Filemanager::openRecentFile(void)
{
		QAction *action = qobject_cast< QAction * >(sender());
		if (action) {
			//std::cout << "print: " << qPrintable(action->data().toString()) << std::endl;
			QString str = action->data().toString();
			QStringList strlist = str.split(" #");

			QFileInfo fi(strlist[0]);
			std::cout << "Reading: " << qPrintable(strlist[0]) << std::endl;
			if (fi.exists() == 1) {
				selectedFiles(QStringList(strlist[0]));
			}else {
				QMessageBox msgBox;
				msgBox.setText("Failed.");
				msgBox.exec();
			}
		}
	return;
}

//==============================================================================
//void Filemanager::addRecentFile( QString filename, QString string )
//------------------------------------------------------------------------------
//==============================================================================
void Filemanager::addRecentFile(QString filename, QString string)
{
		QFile recentFiles(filename);
		//QDateTime local(QDateTime::currentDateTime());
		//QDateTime UTC(local.toUTC());
		//qDebug() << "Local time is:" << local;

		QFile tempFile(main->execPath + TEMPFILE);
		if (tempFile.exists() == true) {
			tempFile.remove();			//delete, otherwise qt will not overwrite it
		}

		if (recentFiles.exists() == true) {
			if (recentFiles.open(QIODevice::WriteOnly | QIODevice::Append)) {
				recentFiles.copy(main->execPath + TEMPFILE);
			}
			recentFiles.close();
			if (recentFiles.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
				if (tempFile.exists() == true) {
					if (tempFile.open(QIODevice::ReadOnly)) {
						QTextStream out(&recentFiles);
						QString timestamp = QDateTime::currentDateTime().toString();
						out << string << " #" << timestamp << endl;
						while (!tempFile.atEnd()) {
							out << tempFile.readLine();
						}
					}
				}
			}
		}
		else {
			if (recentFiles.open(QIODevice::WriteOnly | QIODevice::Append)) {
				QTextStream out(&recentFiles);
				QString timestamp = QDateTime::currentDateTime().toString();
				out << string << " #" << timestamp << endl;
			}
		}

		tempFile.remove();
	return;
}

//==============================================================================
// void Filemanager::showRecentFiles( QString filename )
//------------------------------------------------------------------------------
//==============================================================================
void Filemanager::showRecentFiles(QString filename)
{
		QMenu* submenuA = ui_base->menuFile->addMenu("Recent Files");
		QVector<QString> qvectorfiles;

		QFile recentFiles(filename);
		if (recentFiles.exists() == true) {
			if (recentFiles.open(QIODevice::ReadOnly | QIODevice::Text)) {
				while (!recentFiles.atEnd()) {
					qvectorfiles << recentFiles.readLine();
				}
			}
		}

		int limit = 0;
		enum { MaxRecentFiles = 20 };
		int sizeFileVector = qvectorfiles.size();
		QAction *recentFileString[MaxRecentFiles];

		if (sizeFileVector < MaxRecentFiles) {
			limit = sizeFileVector;
		}
		else { limit = MaxRecentFiles; }

		for (int i = 0; i < limit; ++i) {
			recentFileString[i] = new QAction(this);
			submenuA->addAction(recentFileString[i]);
			QString text = qvectorfiles[i];
			recentFileString[i]->setText(text);
			recentFileString[i]->setData(text);
			connect(recentFileString[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
		}
	return;
}
