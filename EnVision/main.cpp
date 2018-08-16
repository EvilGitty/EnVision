#include "Base/envision.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	app.setApplicationVersion("2.0");
	app.setApplicationName("EnVision " + app.applicationVersion());
	app.setOrganizationName("myorg");
	app.setOrganizationDomain("myorg.com");


	//alternate library paths: QCoreApplication::addLibraryPath("C:/some/other/path");

	QStringList imgLoad1;
	QStringList imgLoad2;;
	QDir d = QFileInfo(app.applicationFilePath()).absoluteDir();
	QString execPath = d.absolutePath();

	EnVision mainWindow(imgLoad1, imgLoad2, execPath);
	mainWindow.show();
	return app.exec();
}
