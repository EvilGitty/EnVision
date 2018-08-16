#include "xmlinit.h"

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
Xmlinit::Xmlinit( QWidget *parent ) : QMainWindow( parent )
{
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
Xmlinit::~Xmlinit()
{
}


//==============================================================================
//void Xmlinit::writeinitFile( QString path )
//------------------------------------------------------------------------------
//==============================================================================
	void Xmlinit::writeinitFile( QString text, QString target )
	{
		
		//	qDebug() << "Writing properties to file: " << text;

			QFile file( target );
			file.open(QIODevice::WriteOnly);
			QXmlStreamWriter stream(&file);

			// Making the root element
			QString root = "HyVisioninitDocument";

			QString DefaultDataDirectory = "DefaultDataDirectory";
				QString Text1						= "Text";

			QString DefaultGpcCalibrationDirectory = "DefaultGpcCalibrationDirectory";
				QString Text2						= "Text";

			QString ImageFormats					= "ImageFormats";

				QString Tgd							= "Tgd";
				QString HySpex						= "HySpex";
				QString Img							= "Img";
				QString Mat							= "Mat";
				QString Nuance						= "Nuance";
				QString ASDFieldSpec				= "ASDFieldSpec";

			QString GpsFormats						= "GpsFormats";

			QString GpsPointsOfInterestXls			= "Xls";
			QString GpsPointsOfInterestXlsx			= "Xlsx";
			QString GpsPointsOfInterest				= "GpsPoi";
			QString GpsRaw							= "Gpsraw";
			QString GpsCorrected					= "Gpscorr";



			QString open = "open";
			QString lookat = "LookAt";

			QString longitude = "longitude";
			QString latitude = "latitude";
			QString altitude = "altitude";

			///////////
			QString style = "Style";
			QString iconstyle = "IconStyle";
			QString scale = "scale";
			QString icon = "Icon";
			QString href = "href";

			QString stylemap = "StyleMap";
			QString pair = "Pair";
			QString key = "key";
			QString styleurl = "styleUrl";

			stream.writeStartDocument();
			stream.setAutoFormatting(true);

			stream.writeStartElement(root);

			stream.writeStartElement(DefaultDataDirectory);
				stream.writeTextElement(Text1, text);
			stream.writeEndElement();

			stream.writeStartElement(DefaultGpcCalibrationDirectory);
			stream.writeTextElement(Text2, ".//data//GPS calibration");
			stream.writeEndElement();

			stream.writeStartElement(ImageFormats);
				stream.writeTextElement(Tgd, "*.tgd");
				stream.writeTextElement(HySpex, "*.hyspex");
				stream.writeTextElement(Img, "*.img");
				stream.writeTextElement(Mat, "*.mat");
				stream.writeTextElement(Nuance, "*.im3");
				stream.writeTextElement(ASDFieldSpec, "*.asd");
			stream.writeEndElement();

			stream.writeStartElement(GpsFormats);
				stream.writeTextElement(GpsPointsOfInterestXls, "*.xls");
				stream.writeTextElement(GpsPointsOfInterestXlsx, "*.xlsx");
				stream.writeTextElement(GpsPointsOfInterest, "*.gpspoi");
				stream.writeTextElement(GpsRaw, "*.gpsraw");
				stream.writeTextElement(GpsCorrected, "*.gpscorr");
			stream.writeEndElement();

			stream.writeEndDocument();	//xml


			/*
			stream.writeTextElement(open, QString::number(1));
			stream.writeStartElement(lookat);
			stream.writeTextElement(longitude, QString::number(10.79366990350846));
			stream.writeTextElement(latitude, QString::number(51.16454645068797));
			stream.writeTextElement(altitude, QString::number(0));
			stream.writeEndElement();

			stream.writeStartElement(style); 	stream.writeAttribute("id", "freizeitparks");
			stream.writeStartElement(iconstyle);
			stream.writeStartElement(icon);
			stream.writeTextElement("href", "http://deutschland-panorama.de//img//freizeitpsarks.png");
			stream.writeEndElement();
			stream.writeEndElement();
			stream.writeEndElement();

			stream.writeStartElement(stylemap); 	stream.writeAttribute("id", "msn_freizeitbaeder");
			stream.writeStartElement(pair);
			stream.writeTextElement(key, "normal");
			stream.writeTextElement(styleurl, "#sh_freizeitbaeder");
			stream.writeEndElement();
			stream.writeStartElement(pair);
			stream.writeTextElement(key, "highlight");
			stream.writeTextElement(styleurl, "#sh_freizeitbaeder");
			stream.writeEndElement();
			*/

			//stream.writeEndElement();
			//stream.writeEndElement();

			//stream.writeEndElement();	//document
			//stream.writeEndElement();	//kml

		return;
	}


//==============================================================================
// QStringList Xmlinit::readXmlproperty( QString path, QString xmlproperty ) 
//------------------------------------------------------------------------------
//==============================================================================
	QStringList Xmlinit::readXmlproperty( QString path, QString xmlproperty ) 
	{

			//qDebug() << "Open Xml path: " << path;
			//qDebug() << "Open Xml xmlproperty: " << xmlproperty;

			QFile xmlFile( path );
			xmlFile.open( QIODevice::ReadOnly | QIODevice::Text );
			xml.setDevice( &xmlFile );
			//xml.readNext();
			while ( !xml.atEnd() && !xml.hasError() ) {
				if ( xml.readNextStartElement() && xml.name() == xmlproperty) {
					xmldata = process(xmlproperty);
				}
				// readNextStartElement() leaves the stream in
				// an invalid state at the end. A single readNext()
				// will advance us to EndDocument.

				if ( xml.tokenType() == QXmlStreamReader::Invalid ) {
					xml.readNext();
				}

				if ( xml.hasError() ) {
					xml.raiseError();
				//	qDebug() << "Error reading xml";
				}

			}
	
		return xmldata;
	}

//==============================================================================
// QStringList Xmlinit::process( QString xmlproperty )
//------------------------------------------------------------------------------
//==============================================================================
	QStringList Xmlinit::process( QString xmlproperty )
	{
			if ( !xml.isStartElement() || xml.name() != xmlproperty ) {
				QStringList error;
				error << "//";
				return error;
			}
			while ( xml.readNextStartElement() ) {
				//qDebug() << "xml name: " << xml.name() << xml.readElementText();
				xmldata << xml.readElementText();
			}
		return xmldata;
	}





