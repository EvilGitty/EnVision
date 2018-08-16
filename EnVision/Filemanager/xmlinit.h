#ifndef XMLinit_H
#define XMLinit_H

#include <QtWidgets/QMainWindow>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
//#include <QtXML>
#include <QFile>
#include <QTextDocument>
#include <QFileDialog>
#include <QFileInfo>
#include <Windows.h>
#include <iostream> // for standard I/O
#include <string>   // for strings
#include <fstream>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion

using namespace std;

	class Xmlinit : public QMainWindow
	{
			Q_OBJECT

				public:
					Xmlinit(QWidget *parent = 0);
					~Xmlinit();

					QXmlStreamReader xml;
					QStringList xmldata;
					void writeinitFile( QString file, QString target );
					QStringList readXmlproperty(QString file, QString xmlproperty);
				private slots: 

				QStringList process(QString xmlproperty);

	};

#endif // XMLinit_H
