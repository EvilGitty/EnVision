#ifndef FILEMANAGER_H
#define FILEMANAGER_H

//-----------------------------------
// Qt
#include <QString>
#include <QDirIterator>
#include <QAction>
#include <QMessageBox>



//-----------------------------------
// class Xmlinit
//#include "base/xmlinit.h"
//-----------------------------------
// class EnVision
//#include "Base/enVision.h"
//-----------------------------------
// class ImageAttribute
#include "Image/image_master.h"
//-----------------------------------
// class Image
//#include "init.h"
//-----------------------------------
// SpecIL
#include "SpecIL_Interface.h"
//-----------------------------------
// class GPSfile
//#include "base/gps.h"
//-----------------------------------
// class GPS_Import_xls
//#include "gps/GPS_import_Excel.h"
//-----------------------------------
// class GPS_Import_csv
//#include "gps/GPS_import_CSV.h"

#include "Image/initImage.h"

class EnVision;
class Image;

#include "ui_envision.h"

namespace Ui {
	EnVision_baseUI;
}

class Filemanager : public QObject, public ImageAttribute
{
	Q_OBJECT
	
public:

	Filemanager(EnVision *main);
	~Filemanager();

	EnVision	 *main;
	Ui::EnVision_baseUI *ui_base;

	Imageclass *imgclass;
	QVector<Imageclass*> img_ref;

	//------------------------------------------------------------------------------
	typedef struct init{
	QString DefaultPath;
	QStringList configFiles;
	QStringList imageFiles;

	QStringList gpsraw_files;
	QStringList gpspoi_files;
	QStringList gpsxlsx_files;

	QStringList ImageFormats;

	}Imageinit;
	Imageinit ImageinitRecord;


public slots:

	void droppedFiles(QDropEvent *event);
	void showRecentFiles(QString filename);
	void selectedFiles(QStringList chosenFiles);
	void openRecentFile(void);
private:
	void addRecentFile(QString filename, QString namestring);
	int filterInputFiles(QString extension);



	void processInputArguments(QStringList InputArgFiles);
	void openInputArgFiles(QStringList InputArgFiles);

	//void findFiles(const QString &dir, const QStringList &files, const QString &text);

	void setDefaultDataFolder(void);
	void directoryChanged(QString dir);



signals :
	void sendSignal(_image record);

private:
	//-----------------------------------
	// private methods for construction of the particular file headers:
	// struct record in "Image.h" 
	bool load_tgd(QStringList::Iterator &it);
	bool load_hySpex_img(QStringList::Iterator &it, int select);
	bool load_mat(QStringList::Iterator &it);
	bool load_im3(QStringList::Iterator &it);
	//bool load_asd( QStringList::Iterator &it );
	//bool load_cub( QStringList::Iterator &it );

private:
	//-----------------------------------
	// private methods for construction of the particular gps file structs
	int load_gps(std::string filename);

private:
	bool CheckFileDoubleLoad(QString filename, int val);
	bool ProcessImageFiles(QStringList::Iterator &it);
	bool ProcessGpsFiles(QStringList::Iterator &it);

};

#endif //FILEMANAGER_H

