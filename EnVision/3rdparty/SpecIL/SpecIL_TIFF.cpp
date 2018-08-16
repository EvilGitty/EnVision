#include "SpecIL_TIFF.h"

SpecIL_TIFF::~SpecIL_TIFF()
{
	this->CleanMemory();
};
//
SpecIL_TIFF::SpecIL_TIFF()
{
	this->init();
	this->TIFFinit();
};
//
void SpecIL_TIFF::TIFFinit()
{
	this->SpecHeader.ID = "TIFF file";
	this->header_byteorder = 0;

	this->directories = 0;

	this->header_bands = 0;
	this->header_bitdepth = 0;
	this->header_lines = 0;
	this->header_sampleformat = 0;
	this->header_samples = 0;
	this->header_PlanarConfig = 0;
	this->header_PhotometricInterpretation = 0;

	this->IsTiled = false;
	this->CubeSize = 0;

	// Fuer Tiles
	this->TileSize = 0;
	this->NumOfTiles = 0;
	this->header_TileWidth = 0;
	this->header_TileLength = 0;
	this->TilesAcross = 0;
	this->TilesDown = 0;
	this->TilesPerImage = 0;
	this->RestoredCubeOfTilesSize = 0;

	//fuer Strips
	this->NumOfStrips = 0;
	this->StripSize = 0;
	this->RestoredCubeOfStripSize = 0;
	this->RowsPerStrip = 0;

	this->RestoredStripCubeWithPadding = false;
};
//
int SpecIL_TIFF::readFileHeader()
{
	// Datei oeffnen
	std::ifstream ifs(this->SpecHeader.filename.c_str(), std::ifstream::in | std::ifstream::binary);
	if (ifs.fail() != 0)
	{
		ifs.close();
		this->ErrorMsgLog("Error in SpecIL_TIFF::readFileHeader(): Konnte Datei " + this->SpecHeader.filename + " nicht oeffnen");
		return -1;
	};

	ifs.seekg(0, std::ios::beg);

	// ersten 2 Byte: Byte Order
	char ByteOrder[3];
	ifs.read(ByteOrder, 2);
	ByteOrder[2] = '\0';
	if (ByteOrder[0] == 0x49)// little-Endian
	{
		this->header_byteorder = 0;
	};
	if (ByteOrder[0] == 0x4D)// big-Endian
	{
		this->header_byteorder = 1;
	};

	// Versionsnummer
	char VersionNum[2];
	ifs.read(VersionNum, 2);
	unsigned short VerNum = static_cast<unsigned short>(VersionNum[0]);
	ifs.close();

	// Unterstuetzte Versionen 42 (32Bit tiff) und 43 (64Bit tiff)!
	if (VerNum == 42 || VerNum == 43)
	{
		// LibTiff Warnungen in der cmd ausschalten
		TIFFSetWarningHandler(NULL);

		// TIFF oeffnen
		TIFF* tiffimage = TIFFOpen(this->SpecHeader.filename.c_str(), "r");

		// Geht tiff mit libtiff Version?
		if (tiffimage)
		{
			this->directories = 0;
			// Directories zaehlen
			do {
				this->directories++;
			} while (TIFFReadDirectory(tiffimage));

			// Zum ersten Directory gehen
			TIFFSetDirectory(tiffimage, 0);

			// relevante TAGS auslesen:
			// TAG auf Fehler pruefen
			unsigned short CheckTAGreading = 0;

			// samples
			uint32 ImageWidth = 0;
			CheckTAGreading += TIFFGetField(tiffimage, TIFFTAG_IMAGEWIDTH, &ImageWidth);

			// lines
			uint32 ImageLength = 0;
			CheckTAGreading += TIFFGetField(tiffimage, TIFFTAG_IMAGELENGTH, &ImageLength);

			// bands
			//uint32 ImageDepth;
			//TIFFGetField(tiffimage, TIFFTAG_IMAGEDEPTH, &ImageDepth);// steht leider nicht immer was drin....
			uint16 SamplesPerPixel = 0;
			CheckTAGreading += TIFFGetField(tiffimage, TIFFTAG_SAMPLESPERPIXEL, &SamplesPerPixel);

			// BitTiefe
			uint16 BitsPerSample = 0;
			CheckTAGreading += TIFFGetField(tiffimage, TIFFTAG_BITSPERSAMPLE, &BitsPerSample);

			// Datentyp
			uint16 SampleFormat = 0;
			CheckTAGreading += TIFFGetField(tiffimage, TIFFTAG_SAMPLEFORMAT, &SampleFormat);

			// Anordnung der Kanaele
			uint16 PlanarConfig = 0;
			CheckTAGreading += TIFFGetField(tiffimage, TIFFTAG_PLANARCONFIG, &PlanarConfig);

			uint16 PhotometricInterpretation = 0;
			CheckTAGreading += TIFFGetField(tiffimage, TIFFTAG_PHOTOMETRIC, &PhotometricInterpretation);

			// War ein relevanter TAG fehlerhaft?
			if (CheckTAGreading < 4)
			{
				this->ErrorMsgLog("Error in SpecIL_TIFF::readFileHeader(): Error while reading Image TAGs !");
				return -1;
			};

			// Uebernehmen der TAGs
			this->header_samples = ImageWidth;
			this->header_lines = ImageLength;
			this->header_bands = (unsigned int)SamplesPerPixel;
			this->header_bitdepth = (unsigned int)BitsPerSample;
			this->header_sampleformat = (unsigned int)SampleFormat;
			this->header_PlanarConfig = (unsigned short)PlanarConfig;
			this->header_PhotometricInterpretation = (unsigned short) PhotometricInterpretation;

			// Header wurde gelesen.
			this->FileHeaderLoaded = 1;

			// TIFF wieder schliessen
			TIFFClose(tiffimage);

			this->SelectedImgProperties = 0;
			return 0;
		};
	};
	this->ErrorMsgLog("Error in SpecIL_TIFF::readFileHeader(): Not supported file!");
	return -1;
};
//
void SpecIL_TIFF::setImageProperties(const char* id,int width,int height,int planes,t_SpecHead::t_interleave il,t_SpecHead::t_data_type dt)
{
	this->ErrorMsgLog("WARNING! In SpecIL_TIFF::setImageProperties(): Input of manual properties are not supported!");
};
//
int SpecIL_TIFF::readImageData()
{
	// LibTiff Warnungen in der cmd ausschalten
	TIFFSetWarningHandler(NULL);


	// TIFF oeffnen
	TIFF* tiffimage = TIFFOpen(this->SpecHeader.filename.c_str(), "r");
	if (tiffimage)
	{
		// Zum ersten Directory gehen
		TIFFSetDirectory(tiffimage, 0);

		// Tiles oder Strips
		this->IsTiled = TIFFIsTiled(tiffimage);

		// Groesse des Cubes
		this->CubeSize = (unsigned long long)this->header_samples * (unsigned long long)this->header_lines * (unsigned long long)this->header_bands * (unsigned long long)this->SpecHeader.pixelsize;

		if (this->IsTiled)
		{
			//Tiles
			uint32 TileWidth;
			TIFFGetField(tiffimage, 322, &TileWidth);
			this->header_TileWidth = TileWidth;

			uint32 TileLength = 0;
			TIFFGetField(tiffimage, 323, &TileLength);
			this->header_TileLength = TileLength;

			this->NumOfTiles = TIFFNumberOfTiles(tiffimage);
			this->TileSize = TIFFTileSize(tiffimage);

			this->TilesAcross = (this->header_samples + TileWidth - 1) / TileWidth;
			this->TilesDown = (this->header_lines + TileLength - 1) / TileLength;
			this->TilesPerImage = this->TilesAcross * this->TilesDown;


			// Groesse des aller Tiles zusammen
			// Achtung, durch Padding ist der zusammengesetzte Cube groesser als der eigentliche Cube!
			this->RestoredCubeOfTilesSize = (unsigned long long)this->TilesAcross * (unsigned long long)TileWidth * (unsigned long long)this->TilesDown * (unsigned long long)TileLength * (unsigned long long)this->header_bands * (unsigned long long)this->SpecHeader.pixelsize;

			if( (this->CubeSize < this->cubemaxsize) && this->ReadOnlyFromHDD == 0)
			{
				if (SpecHeader.interleave == t_SpecHead::IL_BIP)
				{
					try{
						this->SpecHeader.imgcube = static_cast<void*>(new char[this->CubeSize]);
					}
					catch (const std::bad_alloc&)
					{
						TIFFClose(tiffimage);
						delete[] this->SpecHeader.imgcube;
						this->ErrorMsgLog("Error in SpecIL_TIFF::readImageData(): std::bad_alloc -> Datei zu gro� fuer Speicher");

						this->SpecHeader.imgcube = NULL;
						this->SpecHeader.type = 2;

						return -1;
					};

					tdata_t tilebuffer;
					ttile_t tile = 0;
					tilebuffer = _TIFFmalloc(this->TileSize);

					// Offset im Cube
					unsigned int CubeOff = 0;

					// Dimensionen des zusammengesetzten Bildes ( mit Padding! )
					unsigned int AllTilesImg_Width = this->TilesAcross * this->header_TileWidth;
					unsigned int AllTilesImg_High = this->TilesDown * this->header_TileLength;

					// Padding in der horizontalen entfernen
					unsigned int diff_w = AllTilesImg_Width - this->SpecHeader.imgsize[0];
					// Padding fuer vertikale entfernen
					unsigned int diff_h = AllTilesImg_High - this->SpecHeader.imgsize[2];

					// Tile Position
					unsigned int PositionTile_H = 0;
					unsigned int PositionTile_V = 0;

					unsigned int MaxWidth = 0;// Maximale Breite fuer for Schleife
					unsigned int MaxHigh = 0;// Maximale Hoehe fuer for Schleife

					// Alle tiles durchgehen
					for (tile = 0; tile < this->NumOfTiles; tile++)
					{
						PositionTile_V = (unsigned int)tile / TilesAcross;
						PositionTile_H = (unsigned int)tile - PositionTile_V * TilesAcross;

						// Pixelposition im Tile
						unsigned int tileoff = 0;

						// Tile holen
						TIFFReadEncodedTile(tiffimage, tile, tilebuffer, (tsize_t)-1);

						// Buffer fuer memmove auf char legen
						char* chtilebuffer = static_cast<char*>(tilebuffer);

						// Ausgangspunkt des Tiles im OutImg
						CubeOff = (this->header_TileWidth * PositionTile_H + this->header_TileLength * this->SpecHeader.imgsize[0] * PositionTile_V) * this->SpecHeader.pixelsize;

						if (PositionTile_V == (this->TilesDown - 1))
						{
							MaxHigh = this->header_TileLength - diff_h;
						}
						else
						{
							MaxHigh = this->header_TileLength;
						};
						if (PositionTile_H == (this->TilesAcross - 1))
						{
							MaxWidth = this->header_TileWidth - diff_w;
						}
						else
						{
							MaxWidth = this->header_TileWidth;
						};

						for (unsigned int h = 0; h < MaxHigh; h++)
						{/*
							for (unsigned int w = 0; w < MaxWidth; w++)
							{
								tileoff = ((unsigned int)z + w * (unsigned int)this->SpecHeader.imgsize[1] + h * this->header_TileWidth * (unsigned int)this->SpecHeader.imgsize[1]) * (unsigned int)this->SpecHeader.pixelsize;

								// kopieren
								std::memmove(&BandImgbuff[BandImgOff], &chtilebuffer[tileoff], this->SpecHeader.pixelsize);
								CubeOff = CubeOff + (unsigned int)this->SpecHeader.pixelsize;
							};*/

							tileoff = h * this->header_TileWidth * (unsigned int)this->SpecHeader.imgsize[1] * (unsigned int)this->SpecHeader.pixelsize;

							std::memmove(&static_cast< char* >(this->SpecHeader.imgcube)[CubeOff], &chtilebuffer[tileoff], MaxWidth * (unsigned int)this->SpecHeader.pixelsize);

							CubeOff = CubeOff + MaxWidth * (unsigned int)this->SpecHeader.pixelsize;
							CubeOff = CubeOff + ((unsigned int)this->SpecHeader.imgsize[0] - MaxWidth) * (unsigned int)this->SpecHeader.pixelsize;
						};
					};
					_TIFFfree(tilebuffer);

					// Daten im RAM
					this->SpecHeader.type = 1;
				}
				else
				{
					this->SpecHeader.type = 2;
					// to do....
					this->ErrorMsgLog("Error in SpecIL_TIFF::readImageData(): BSQ and BIL are not supported!");
					return -1;
				};
			}
			else
			{
				// Tiled CubeDaten sind NICHT im RAM!
				// Erstmal werden die Daten nicht in den RAM geladen, weil Tiled Images generell gross sind
				// und weil der Cube zusammengesetzt und die Padding Pixel entfernt werden muss....
				this->SpecHeader.type = 2;
			};
		}
		else//Strips
		{
			this->NumOfStrips = TIFFNumberOfStrips(tiffimage);
			this->StripSize = TIFFStripSize(tiffimage);

			// RowsPerStrip selbst berechnen, da diese Information nach unterschiedlichen Ansaetzen in den tiff Bilder hinterlegt wird
			//long lRowsPerStrip = 0;
			//TIFFGetField(tiffimage, 278, &lRowsPerStrip);
			//this->RowsPerStrip = lRowsPerStrip;
			if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
			{
				// ist fuer den fall, dass StripSize = samples * bands * lines * pixelsize ist
				this->RowsPerStrip = (long)(this->StripSize / (this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize));
			};
			if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
			{
				// Planarcofiguration = 2
				// in einem Strip ist dann immer nur ein Kanal, muss aber nicht immer so sein....
				this->RowsPerStrip = (long)(this->StripSize / (this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize));
			};

			// Pruefen ob CubeSize mit errechneter Cubegroesse aus der Summe der Strips uebereinstimmt, sonst ist Padding vorhanden
			this->RestoredCubeOfStripSize = (unsigned long long)this->StripSize * (unsigned long long)this->NumOfStrips;
			
			if (this->RestoredCubeOfStripSize != this->CubeSize)
			{
				this->RestoredStripCubeWithPadding = true;
			};

			//Cube klein genung fuer RAM?
			if ((this->RestoredCubeOfStripSize < this->cubemaxsize) && this->ReadOnlyFromHDD == 0)
			{
				// Buffer allokieren
				try{
					this->SpecHeader.imgcube = static_cast<void*>(new char[this->RestoredCubeOfStripSize]);
				}
				catch (const std::bad_alloc&)
				{
					TIFFClose(tiffimage);
					delete[] this->SpecHeader.imgcube;
					this->ErrorMsgLog(std::string("Error in SpecIL_TIFF::readImageData(): std::bad_alloc -> Datei zu gro� fuer Speicher"));
					return -1;
				};

				unsigned int cubebuffoff = 0;

				tstrip_t strip;
				tdata_t stripbuffer;
				stripbuffer = _TIFFmalloc(this->StripSize);

				for (strip = 0; strip < this->NumOfStrips; strip++)
				{
					TIFFReadEncodedStrip(tiffimage, strip, stripbuffer, (tsize_t)-1);

					char* chstripbuffer = static_cast<char*>(stripbuffer);

					std::memmove(&static_cast< char* >(this->SpecHeader.imgcube)[cubebuffoff], chstripbuffer, this->StripSize);

					cubebuffoff = cubebuffoff + this->StripSize;
				};

				// Striped CubeDaten im RAM
				this->SpecHeader.type = 1;

				_TIFFfree(stripbuffer);
			}
			else
			{
				// Striped CubeDaten nicht im RAM
				this->SpecHeader.type = 2;
			};
		};

		// readImageData wurde ausgefuehrt
		this->FileDataLoaded = 1;
		// Tiff Imgae schlie�en
		TIFFClose(tiffimage);
		return 0;
	};
	this->ErrorMsgLog("Error in SpecIL_TIFF::readImageData():");
	return -1;
};
//
int SpecIL_TIFF::read()
{
	// .tiff oder .tif Header lesen
	if (this->FileHeaderLoaded != 1)
	{
		if (this->readFileHeader() != 0)
		{
			this->ErrorMsgLog("Error in SpecIL_TIFF::read(): Failed to read file header!");
			return -1;
		};
	};

	// Sind manuell eingegebne Bildinformationen vorhanden?
	// Wenn ja, wird Header und ein meta-file ignoriert!
	if (this->SelectedImgProperties < 1)
	{
		// Interpretation und Zuordnung der Header-Daten
		
		// ByteOrder
		if (this->header_byteorder == 0)// little-Endian
		{
			this->SpecHeader.byte_order = t_SpecHead::BO_LSF;
		};
		if (this->header_byteorder == 1)// big-Endian
		{
			this->SpecHeader.byte_order = t_SpecHead::BO_MSF;
		};

		// Dimensionen
		this->SpecHeader.imgsize[0] = this->header_samples;
		this->SpecHeader.imgsize[1] = this->header_bands;
		this->SpecHeader.imgsize[2] = this->header_lines;


		// Datentyp nach ENVI bestimmen
		if (this->header_bitdepth == 8)
		{
			// Pixelgroesse
			this->SpecHeader.pixelsize = 1;

			this->SpecHeader.data_type = t_SpecHead::DT_8_BYTE;
		};
		if (this->header_bitdepth == 16)
		{
			// Pixelgroesse
			this->SpecHeader.pixelsize = 2;

			if (this->header_sampleformat == 1 || this->header_sampleformat == 0)// unsigned
			{
				this->SpecHeader.data_type = t_SpecHead::DT_16_UINT;
			};
			if (this->header_sampleformat == 2)// signed
			{
				this->SpecHeader.data_type = t_SpecHead::DT_16_SINT;
			};
		};
		if (this->header_bitdepth == 32)
		{
			// Pixelgroesse
			this->SpecHeader.pixelsize = 4;

			if (this->header_sampleformat == 1 || this->header_sampleformat == 0)// unsigned
			{
				this->SpecHeader.data_type = t_SpecHead::DT_32_ULONG;
			};
			if (this->header_sampleformat == 2)// signed
			{
				this->SpecHeader.data_type = t_SpecHead::DT_32_SLONG;
			};
			if (this->header_sampleformat == 3)// IEEE floating point data
			{
				this->SpecHeader.data_type = t_SpecHead::DT_32_FLOAT;
			};
		};
		if (this->header_bitdepth == 64)
		{
			// Pixelgroesse
			this->SpecHeader.pixelsize = 8;

			if (this->header_sampleformat == 1 || this->header_sampleformat == 0)// unsigned
			{
				this->SpecHeader.data_type = t_SpecHead::DT_64_ULONG;
			};
			if (this->header_sampleformat == 2)// signed
			{
				this->SpecHeader.data_type = t_SpecHead::DT_64_SLONG;
			};
			if (this->header_sampleformat == 3)// IEEE floating point data
			{
				this->SpecHeader.data_type = t_SpecHead::DT_64_DOUBLE;
			};
		};
		if (this->header_bitdepth < 8 || this->header_sampleformat == 4)
		{
			// Pixelgroesse
			this->SpecHeader.pixelsize = 0;

			this->SpecHeader.data_type = t_SpecHead::DT_UNKNOWN;
			//	std::string emsg;
			//	emsg = "WARNING! In SpecIL_TIFF::readFileHeader(): unknown data type!";
			//	emsg += " BitsPerSample = " + std::to_string(BitsPerSample);
			//	emsg += " SampleFormat = " + std::to_string(SampleFormat);
			//	this->ErrorMsgLog(emsg);
		};

		//		Anordnung der Daten
		if (this->header_PlanarConfig == 1) // Chunky Format, BIP
		{
			this->SpecHeader.interleave = t_SpecHead::IL_BIP;
		};
		if (this->header_PlanarConfig == 2)// Planar Configuration
		{
			this->SpecHeader.interleave = t_SpecHead::IL_BSQ;
		};
	}
	else
	{
		// Manuelle Werte uebernehmen und rest ignorieren

		// to do....
		this->ErrorMsgLog("Error in SpecIL_TIFF::read(): setImageProperties values are not supported!");
		return -1;
	};

	// Bilddaten lesen und ggf. in den RAM laden
	if (this->FileDataLoaded == 0)
	{
		if (this->readImageData() != 0)
		{
			this->ErrorMsgLog("Error in SpecIL_TIFF::read():  Failed to load .tif, .tiff image data!");
			return -1;
		};
	};
	return 0;
};
//
int SpecIL_TIFF::getPoint(void* point, int x, int y, int z)
{
	if (this->SpecHeader.type == 0)
	{
		this->ErrorMsgLog("Error in SpecIL_TIFF::getPoint(): SpecHeader.type == 0, Data was not read! Run read()!");
		return -1;
	};

	if (this->SpecHeader.type == 1)
	{
		SpecIL_Base::getPoint(point, x, y, z);
		return 0;
	};

	if (this->SpecHeader.type == 2)
	{
		char* Pointbuff = static_cast<char*>(point);

		// LibTiff Warnungen in der cmd ausschalten
		TIFFSetWarningHandler(NULL);

		TIFF* tiffimage = TIFFOpen(this->SpecHeader.filename.c_str(), "r");
		if (tiffimage)
		{
			if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
			{
				if (this->IsTiled == false)
				{
					// striped
					tdata_t stripbuffer;
					stripbuffer = _TIFFmalloc(this->StripSize);

					// welcher stripe?
					tstrip_t  StripeNum = ((unsigned int)y / (unsigned int)RowsPerStrip);
					// y-position im strip
					unsigned int yInStripe = (unsigned int)y % (unsigned int)RowsPerStrip;

					TIFFReadEncodedStrip(tiffimage, StripeNum, stripbuffer, (tsize_t)-1);
					char* chstripbuffer = static_cast<char*>(stripbuffer);

					unsigned int PointPosition = ((unsigned int)z + ((unsigned int)x + (unsigned int)this->SpecHeader.imgsize[0] * yInStripe) * (unsigned int)this->SpecHeader.imgsize[1]) * (unsigned int)this->SpecHeader.pixelsize;

					std::memmove(Pointbuff, &chstripbuffer[PointPosition], this->SpecHeader.pixelsize);

					_TIFFfree(stripbuffer);
				}
				else
				{
					// tiled
					tdata_t tilebuffer;
					tilebuffer = _TIFFmalloc(this->TileSize);

					// Welches Tile?
					ttile_t tile = ((unsigned int)x / this->header_TileWidth) + (this->TilesAcross * ((unsigned int)y / this->header_TileLength));

					// x-Position im Tile
					unsigned int xInTile = (unsigned int)x % this->header_TileWidth;
					// y-Position im Tile
					unsigned int yInTile = (unsigned int)y % this->header_TileLength;

					// Tile laden
					TIFFReadEncodedTile(tiffimage, tile, tilebuffer, (tsize_t)-1);

					// Punkt kopieren
					unsigned int PointPosition = ((yInTile * this->header_TileWidth + xInTile) * this->SpecHeader.imgsize[1] + (unsigned int)z) * this->SpecHeader.pixelsize;
					char* chtilebuffer = static_cast<char*>(tilebuffer);
					std::memmove(Pointbuff, &chtilebuffer[PointPosition], this->SpecHeader.pixelsize);

					_TIFFfree(tilebuffer);
				};
			};
			if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
			{
				TIFFClose(tiffimage);
				this->ErrorMsgLog("Error in SpecIL_TIFF::getPoint(): BSQ is not supported");
				return -1;
			};
			if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
			{
				TIFFClose(tiffimage);
				this->ErrorMsgLog("Error in SpecIL_TIFF::getPoint(): BIL is not supported");
				return -1;
			};
		};
		TIFFClose(tiffimage);
		return 0;
	};
	this->ErrorMsgLog("Error in SpecIL_TIFF::getPoint():");
	return -1;
};
//
int SpecIL_TIFF::getPlane(void* plane, int x, int y, int z)
{
	// wurde read() ausgefuehrt ?
	if (this->SpecHeader.type == 0)
	{
		// Err
		this->ErrorMsgLog("Error in SpecIL_TIFF::getPlane(): SpecHeader.type == 0, Data was not read! Run read()!");
		return -1;
	};

	int array_x[2];
	int array_y[2];
	int array_z[2];

	// Ein Band ausgeben
	if (x < 0 && y < 0 && z < this->SpecHeader.imgsize[1])
	{
		if (this->SpecHeader.type == 1)
		{
			array_x[0] = 0;
			array_x[1] = this->SpecHeader.imgsize[0];

			array_y[0] = 0;
			array_y[1] = this->SpecHeader.imgsize[2];

			this->getPlane_Band(plane, array_x, array_y, z);

			return 0;
		};

		// Daten auf HDD
		if (this->SpecHeader.type == 2 && this->IsTiled == false)
		{
			this->getPlane_Band_striped(plane, z);
			return 0;
		};
		if (this->SpecHeader.type == 2 && this->IsTiled == true)
		{
			this->getPlane_Band_tiled(plane, z);
			return 0;
		};
	};

	// Einen Frame ausgeben
	if (x < 0 && z < 0 && y < this->SpecHeader.imgsize[2])
	{
		if (this->SpecHeader.type == 1)
		{
			array_x[0] = 0;
			array_x[1] = this->SpecHeader.imgsize[0];

			array_z[0] = 0;
			array_z[1] = this->SpecHeader.imgsize[1];

			this->getPlane_Frame(plane, array_x, y, array_z);
			return 0;
		};

		if (this->SpecHeader.type == 2 && this->IsTiled == true)
		{
			this->getPlane_Frame_tiled(plane,y);
			return 0;
		};
		if (this->SpecHeader.type == 2 && this->IsTiled == false)
		{
			this->getPlane_Frame_striped(plane, y);
			return 0;
		};
	};

	// Ein Samplebild ausgeben
	if (y < 0 && z < 0 && x < this->SpecHeader.imgsize[0])
	{
		if (this->SpecHeader.type == 1)
		{
			array_y[0] = 0;
			array_y[1] = this->SpecHeader.imgsize[2];

			array_z[0] = 0;
			array_z[1] = this->SpecHeader.imgsize[1];

			this->getPlane_Sample(plane, x, array_y, array_z);
			return 0;
		};
		if (this->SpecHeader.type == 2 && this->IsTiled == false)
		{
			this->getPlane_Sample_striped(plane, x);
			return 0;
		};
		if (this->SpecHeader.type == 2 && this->IsTiled == true)
		{
			this->getPlane_Sample_tiled(plane, x);
			return 0;
		};
	};
	this->ErrorMsgLog("In SpecIL_TIFF::getPlane(): Invalid parameters");
	return -1;
};
//
int SpecIL_TIFF::getPlane(void* plane, int *x, int *y, int *z)
{
	this->ErrorMsgLog("In SpecIL_TIFF::getPlane(): Feature plane cutouts are not supported.");
	return -1;
};
//
int SpecIL_TIFF::getPlane_Band_tiled(void* plane, int z)
{
	// Methode arbeitet nur auf der HDD
	char* BandImgbuff = static_cast<char*>(plane);
	if (this->SpecHeader.type == 2)
	{
		// band interleaved by pixel
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			// LibTiff Warnungen in der cmd ausschalten
			TIFFSetWarningHandler(NULL);

			TIFF* tiffimage = TIFFOpen(this->SpecHeader.filename.c_str(), "r");
			if (tiffimage)
			{
				// Vorbereiten
				tdata_t tilebuffer;
				ttile_t tile = 0;
				tilebuffer = _TIFFmalloc(this->TileSize);

				// Offset fuer den Buffer von plane
				unsigned int BandImgOff = 0;

				// Dimensionen des zusammengesetzten Bildes ( mit Padding! )
				unsigned int AllTilesImg_Width = this->TilesAcross * this->header_TileWidth;
				unsigned int AllTilesImg_High = this->TilesDown * this->header_TileLength;
				// Anzahl der Bands ist vom Padding nicht betroffen!

				// Padding in der horizontalen entfernen
				unsigned int diff_w = AllTilesImg_Width - this->SpecHeader.imgsize[0];

				// Padding fuer vertikale entfernen
				unsigned int diff_h = AllTilesImg_High - this->SpecHeader.imgsize[2];

				// Tile Position
				unsigned int PositionTile_H = 0;
				unsigned int PositionTile_V = 0;

				unsigned int MaxWidth = 0;// Maximale Breite fuer for Schleife
				unsigned int MaxHigh = 0;// Maximale Hoehe fuer for Schleife

				// Alle tiles durchgehen
				for (tile = 0; tile < this->NumOfTiles; tile++)
				{
					PositionTile_V = (unsigned int)tile / TilesAcross;
					PositionTile_H = (unsigned int)tile - PositionTile_V * TilesAcross;

					// Pixelposition im Tile
					unsigned int tileoff = 0;

					// Tile holen
					TIFFReadEncodedTile(tiffimage, tile, tilebuffer, (tsize_t)-1);

					// Buffer fuer memmove auf char legen
					char* chtilebuffer = static_cast<char*>(tilebuffer);

					// Ausgangspunkt des Tiles im OutImg
					BandImgOff = (this->header_TileWidth * PositionTile_H + this->header_TileLength * this->SpecHeader.imgsize[0] * PositionTile_V) * this->SpecHeader.pixelsize;


					if (PositionTile_V == (this->TilesDown - 1))
					{
						MaxHigh = this->header_TileLength - diff_h;
					}
					else
					{
						MaxHigh = this->header_TileLength;
					};
					if (PositionTile_H == (this->TilesAcross - 1))
					{
						MaxWidth = this->header_TileWidth - diff_w;
					}
					else
					{
						MaxWidth = this->header_TileWidth;
					};

					// Band Pixel raus ziehen
					for (unsigned int h = 0; h < MaxHigh; h++)
					{
						for (unsigned int w = 0; w < MaxWidth; w++)
						{
							tileoff = ((unsigned int)z + w * (unsigned int)this->SpecHeader.imgsize[1] + h * this->header_TileWidth * (unsigned int)this->SpecHeader.imgsize[1]) * (unsigned int)this->SpecHeader.pixelsize;

							// kopieren
							std::memmove(&BandImgbuff[BandImgOff], &chtilebuffer[tileoff], this->SpecHeader.pixelsize);
							BandImgOff = BandImgOff + (unsigned int)this->SpecHeader.pixelsize;
						};
						BandImgOff = BandImgOff + ((unsigned int)this->SpecHeader.imgsize[0] - MaxWidth) * (unsigned int)this->SpecHeader.pixelsize;
					};
				};
				_TIFFfree(tilebuffer);
			};
			// Tiff Imgae schlie�en
			TIFFClose(tiffimage);
			return 0;
		};

		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			// to do...
		};
	};
	this->ErrorMsgLog("Error in SpecIL_TIFF::getPlane_Band_tiled():");
	return -1;
};
//
int SpecIL_TIFF::getPlane_Band_striped(void* plane, int z)
{
	// Methode arbeitet nur auf der HDD
	char* BandImgbuff = static_cast<char*>(plane);
	if (this->SpecHeader.type == 2)
	{
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			// LibTiff Warnungen in der cmd ausschalten
			TIFFSetWarningHandler(NULL);

			TIFF* tiffimage = TIFFOpen(this->SpecHeader.filename.c_str(), "r");
			if (tiffimage)
			{
				tdata_t stripbuffer;
				tstrip_t strip = 0;
				stripbuffer = _TIFFmalloc(this->StripSize);

				unsigned int imgbuffoff = 0;

				for (strip = 0; strip < this->NumOfStrips; strip++)
				{
					unsigned int stipbuffoff = (unsigned int)z * (unsigned int)this->SpecHeader.pixelsize;
					unsigned int AnzPix = this->SpecHeader.imgsize[0] * (unsigned int)this->RowsPerStrip;
					if (strip == (this->NumOfStrips - 1))
					{
						unsigned int fullstrips = this->NumOfStrips - 1;
						unsigned int usedlines = fullstrips * (unsigned int)this->RowsPerStrip;
						unsigned int lastlines = (unsigned int)this->SpecHeader.imgsize[2] - usedlines;
						AnzPix = this->SpecHeader.imgsize[0] * lastlines;
					};
					TIFFReadEncodedStrip(tiffimage, strip, stripbuffer, (tsize_t)-1);
					char* chstripbuffer = static_cast<char*>(stripbuffer);

					for (unsigned int pix = 0; pix < AnzPix; pix++)
					{
						std::memmove(&BandImgbuff[imgbuffoff], &chstripbuffer[stipbuffoff], this->SpecHeader.pixelsize);

						stipbuffoff = stipbuffoff + (unsigned int)this->SpecHeader.pixelsize * (unsigned int)this->SpecHeader.imgsize[1];

						imgbuffoff = imgbuffoff + (unsigned int)this->SpecHeader.pixelsize;

					};
				};

				_TIFFfree(stripbuffer);
				TIFFClose(tiffimage);
				return 0;
			};
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			this->ErrorMsgLog("Error in SpecIL_TIFF::getPlane_Band_striped(): BSQ is not supported");
			return -1;
		};
	};
	this->ErrorMsgLog("Error in SpecIL_TIFF::getPlane_Band_striped():");
	return -1;
};
//
int SpecIL_TIFF::getPlane_Frame_tiled(void* plane, int y)
{
	// Methode arbeitet nur auf der HDD
	char* FrameImgbuff = static_cast<char*>(plane);
	if (this->SpecHeader.type == 2)
	{
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			// LibTiff Warnungen in der cmd ausschalten
			TIFFSetWarningHandler(NULL);

			TIFF* tiffimage = TIFFOpen(this->SpecHeader.filename.c_str(), "r");
			if (tiffimage)
			{
				// Vorbereiten
				tdata_t tilebuffer;
				ttile_t tile = 0;
				tilebuffer = _TIFFmalloc(this->TileSize);

				char* fullpixelbuffer = new char[this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize];

				// Dimensionen des zusammengesetzten Bildes ( mit Padding! )
				unsigned int AllTilesImg_Width = this->TilesAcross * this->header_TileWidth;
				unsigned int AllTilesImg_High = this->TilesDown * this->header_TileLength;
				// Anzahl der Bands ist vom Padding nicht betroffen!

				// Padding in der horizontalen entfernen
				unsigned int diff_w = AllTilesImg_Width - this->SpecHeader.imgsize[0];

				unsigned int MaxWidth = this->header_TileWidth;// Maximale Breite fuer for Schleife

				unsigned int tilestart_y = (unsigned int)y / this->header_TileLength;

				ttile_t tilestart = tilestart_y * this->TilesAcross;

				unsigned int tile_y = (unsigned int)y - tilestart_y * this->header_TileLength;

				for (tile = 0; tile < this->TilesAcross; tile++)
				{
					// Pixelposition im Tile
					unsigned int tileoff = 0;

					// Tile holen
					TIFFReadEncodedTile(tiffimage, tilestart+tile, tilebuffer, (tsize_t)-1);

					// Buffer fuer memmove auf char legen
					char* chtilebuffer = static_cast<char*>(tilebuffer);

					if (tile == (this->TilesAcross - 1))
					{
						MaxWidth = this->header_TileWidth - diff_w;
					};

					// Offset fuer den Buffer von plane
					unsigned int FrameImgOff = 0;
					unsigned int FrameImgOffStart = 0;
					for (unsigned int w = 0; w < MaxWidth; w++)
					{
						tileoff = (w + tile_y * this->header_TileWidth) * this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
						std::memmove(fullpixelbuffer, &chtilebuffer[tileoff], this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize);
						FrameImgOffStart = w + tile * this->header_TileWidth;
						for (unsigned int h = 0; h < this->SpecHeader.imgsize[1]; h++)
						{
							FrameImgOff = ( FrameImgOffStart + h * (unsigned int)this->SpecHeader.imgsize[0] ) * (unsigned int)this->SpecHeader.pixelsize;
							std::memmove(&FrameImgbuff[FrameImgOff], &fullpixelbuffer[h*this->SpecHeader.pixelsize], this->SpecHeader.pixelsize);
						};
					};
				};
				delete[] fullpixelbuffer;
				fullpixelbuffer = NULL;
				_TIFFfree(tilebuffer);
				TIFFClose(tiffimage);
				return 0;
			};
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			this->ErrorMsgLog("Error in SpecIL_TIFF::getPlane_Frame_tiled(): BSQ is not supported");
			return -1;
		};
	};
	this->ErrorMsgLog("Error in SpecIL_TIFF::getPlane_Frame_tiled():");
	return -1;
};
//
int SpecIL_TIFF::getPlane_Frame_striped(void* plane, int y)
{
	// Methode arbeitet nur auf der HDD
	char* FrameImgbuff = static_cast<char*>(plane);
	if (this->SpecHeader.type == 2)
	{
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			// LibTiff Warnungen in der cmd ausschalten
			TIFFSetWarningHandler(NULL);

			TIFF* tiffimage = TIFFOpen(this->SpecHeader.filename.c_str(), "r");
			if (tiffimage)
			{
				tdata_t stripbuffer;
				tstrip_t strip = 0;
				stripbuffer = _TIFFmalloc(this->StripSize);
				char* fullpixelbuffer = new char[this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize];


				strip = (unsigned int)y / (unsigned int)this->RowsPerStrip;
				unsigned int stripe_y = (unsigned int)y % (unsigned int)this->RowsPerStrip;

				unsigned int StripBufferOff = stripe_y * (unsigned int)this->SpecHeader.imgsize[1] * (unsigned int)this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
				unsigned int FrameImgOff = 0;
				
				TIFFReadEncodedStrip(tiffimage, strip, stripbuffer, (tsize_t)-1);
				char* chstripbuffer = static_cast<char*>(stripbuffer);
					

				for (unsigned int w = 0; w < this->SpecHeader.imgsize[0]; w++)
				{
					std::memmove(fullpixelbuffer, &chstripbuffer[StripBufferOff], this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize);
					StripBufferOff = StripBufferOff + this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;

					for (unsigned int h = 0; h < this->SpecHeader.imgsize[1]; h++)
					{
						FrameImgOff = (w + h * (unsigned int)this->SpecHeader.imgsize[0]) * (unsigned int)this->SpecHeader.pixelsize;

						std::memmove(&FrameImgbuff[FrameImgOff], &fullpixelbuffer[h*this->SpecHeader.pixelsize], this->SpecHeader.pixelsize);
					};
				};

				delete[] fullpixelbuffer;
				fullpixelbuffer = NULL;
				_TIFFfree(stripbuffer);
				TIFFClose(tiffimage);
				return 0;
			};
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			this->ErrorMsgLog("Error in SpecIL_TIFF::getPlane_Frame_striped(): BSQ is not supported");
			return -1;
		};
	};
	this->ErrorMsgLog("Error in SpecIL_TIFF::getPlane_Frame_striped():");
	return -1;
};
//
int SpecIL_TIFF::getPlane_Sample_tiled(void* plane, int x)
{
	char* SampleImgbuff = static_cast<char*>(plane);
	if (this->SpecHeader.type == 2)
	{
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			// LibTiff Warnungen in der cmd ausschalten
			TIFFSetWarningHandler(NULL);

			TIFF* tiffimage = TIFFOpen(this->SpecHeader.filename.c_str(), "r");
			if (tiffimage)
			{
				// Vorbereiten
				tdata_t tilebuffer;
				ttile_t tile = 0;
				tilebuffer = _TIFFmalloc(this->TileSize);

				char* fullpixelbuffer = new char[this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize];

				// Dimensionen des zusammengesetzten Bildes ( mit Padding! )
				unsigned int AllTilesImg_Width = this->TilesAcross * this->header_TileWidth;
				unsigned int AllTilesImg_High = this->TilesDown * this->header_TileLength;
				// Anzahl der Bands ist vom Padding nicht betroffen!

				// Padding fuer vertikale entfernen
				unsigned int diff_h = AllTilesImg_High - this->SpecHeader.imgsize[2];

				unsigned int tilestart_x = (unsigned int)x / this->header_TileWidth;
				ttile_t tilestart = tilestart_x;
				unsigned int tile_x = (unsigned int)x - tilestart_x * this->header_TileWidth;

				unsigned int MaxHigh = this->header_TileLength;// Maximale Breite fuer for Schleife

				unsigned int SampleImgOff = 0;
				unsigned int StripBufferOff = 0;
				for (tile = 0; tile < this->TilesDown; tile++)
				{
					TIFFReadEncodedTile(tiffimage, tilestart + tile*this->TilesAcross, tilebuffer, (tsize_t)-1);
					char* chstripbuffer = static_cast<char*>(tilebuffer);

					if (tile == (this->TilesDown - 1))
					{
						MaxHigh = this->header_TileLength - diff_h;
					};

					for (unsigned int h = 0; h < MaxHigh; h++)
					{
						StripBufferOff = (tile_x + h * this->header_TileWidth) * this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
						std::memmove(&SampleImgbuff[SampleImgOff], &chstripbuffer[StripBufferOff], this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize);

						SampleImgOff = SampleImgOff + this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
					};
				};
				delete[] fullpixelbuffer;
				fullpixelbuffer = NULL;
				_TIFFfree(tilebuffer);
				TIFFClose(tiffimage);
				return 0;
			};
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			this->ErrorMsgLog("Error in SpecIL_TIFF::getPlane_Sample_tiled(): BSQ is not supported");
			return -1;
		};
	};
	this->ErrorMsgLog("Error in SpecIL_TIFF::getPlane_Sample_tiled():");
	return -1;
};
//
int SpecIL_TIFF::getPlane_Sample_striped(void* plane, int x)
{
	char* SampleImgbuff = static_cast<char*>(plane);
	if (this->SpecHeader.type == 2)
	{
		if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
		{
			// LibTiff Warnungen in der cmd ausschalten
			TIFFSetWarningHandler(NULL);

			TIFF* tiffimage = TIFFOpen(this->SpecHeader.filename.c_str(), "r");
			if (tiffimage)
			{
				tdata_t stripbuffer;
				tstrip_t strip = 0;
				stripbuffer = _TIFFmalloc(this->StripSize);
				char* fullpixelbuffer = new char[this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize];

				unsigned int var1 = (unsigned int)this->RowsPerStrip * this->NumOfStrips;
				unsigned int var2 = (unsigned int)this->SpecHeader.imgsize[2] - var1;
				unsigned int RowsLastStrip = this->RowsPerStrip - var2;
				unsigned int MaxRows = this->RowsPerStrip;

				unsigned int SampleImgOff = 0;
				unsigned int StripBufferOff = 0;
				for (strip = 0; strip < this->NumOfStrips; strip++)
				{
					TIFFReadEncodedStrip(tiffimage, strip, stripbuffer, (tsize_t)-1);
					char* chstripbuffer = static_cast<char*>(stripbuffer);

					if (strip == (this->NumOfStrips - 1))
					{
						MaxRows = RowsLastStrip;
					};
					
					SampleImgOff = (strip * (unsigned int)this->RowsPerStrip * this->SpecHeader.imgsize[1]) * this->SpecHeader.pixelsize;

					for (unsigned int h = 0; h < MaxRows; h++)
					{

						StripBufferOff = (x + h * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;

						std::memmove(&SampleImgbuff[SampleImgOff], &chstripbuffer[StripBufferOff], this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize);

						SampleImgOff = SampleImgOff + this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
					};
				};
				delete[] fullpixelbuffer;
				fullpixelbuffer = NULL;
				_TIFFfree(stripbuffer);
				TIFFClose(tiffimage);
				return 0;
			};
		};
		if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
		{
			this->ErrorMsgLog("Error in SpecIL_TIFF::getPlane_Sample_striped(): BSQ is not supported");
			return -1;
		};
	};
	this->ErrorMsgLog("Error in SpecIL_TIFF::getPlane_Sample_striped():");
	return -1;
};
//
int SpecIL_TIFF::getVector(void* vector, int x, int y, int z)
{
	if (x < 0 && y < this->SpecHeader.imgsize[2] && z < this->SpecHeader.imgsize[1])
	{
		this->getVector_X(vector, y, z);
		return 0;
	};
	if (x < this->SpecHeader.imgsize[0] && y < 0 && z < this->SpecHeader.imgsize[1])
	{
		this->getVector_Y(vector, x, z);
		return 0;
	};
	if (x < this->SpecHeader.imgsize[0] && y < this->SpecHeader.imgsize[2] && z < 0)
	{
		this->getVector_Z(vector, x, y);
		return 0;
	};
	this->ErrorMsgLog("Error in SpecIL_TIFF::getVector():");
	return -1;
};
//
int SpecIL_TIFF::getVector_X(void* vector, int y, int z)
{
	if (this->SpecHeader.type == 0)
	{
		this->ErrorMsgLog("Error in SpecIL_TIFF::getVector_X(): SpecHeader.type == 0, Data was not read! Run read()!");
		return -1;
	};

	if (this->SpecHeader.type == 1)
	{
		SpecIL_Base::getVector_X(vector, y, z);
		return 0;
	};

	if (this->SpecHeader.type == 2)
	{
		char* Vectorbuff = static_cast<char*>(vector);

		// LibTiff Warnungen in der cmd ausschalten
		TIFFSetWarningHandler(NULL);

		TIFF* tiffimage = TIFFOpen(this->SpecHeader.filename.c_str(), "r");
		if (tiffimage)
		{
			if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
			{
				if (this->IsTiled == false)
				{
					// striped
					tdata_t stripbuffer;
					stripbuffer = _TIFFmalloc(this->StripSize);

					// welcher strip?
					tstrip_t StripeNum = ((unsigned int)y / (unsigned int)RowsPerStrip);
					// y-position im strip
					unsigned int yInStripe = (unsigned int)y % (unsigned int)RowsPerStrip;

					TIFFReadEncodedStrip(tiffimage, StripeNum, stripbuffer, (tsize_t)-1);
					char* chstripbuffer = static_cast<char*>(stripbuffer);

					unsigned int VectorBuffOff = 0;
					unsigned int StripBuffOff;
					unsigned int samples = (unsigned int)this->SpecHeader.imgsize[0];
					unsigned int bands = (unsigned int)this->SpecHeader.imgsize[1];

					for (unsigned int i = 0; i < samples; i++)
					{
						// yInStripe * samples * bands
						// + i * bands
						// + z
						StripBuffOff = (yInStripe * samples * bands	+ i * bands	+ (unsigned int)z)* this->SpecHeader.pixelsize;

						std::memmove(&Vectorbuff[VectorBuffOff], &chstripbuffer[StripBuffOff], this->SpecHeader.pixelsize);
						VectorBuffOff += this->SpecHeader.pixelsize;
					};
					_TIFFfree(stripbuffer);
				}
				else
				{
					// tiled
					
					tdata_t tilebuffer;
					ttile_t tile = 0;
					tilebuffer = _TIFFmalloc(this->TileSize);

					// Dimensionen des zusammengesetzten Bildes ( mit Padding! )
					unsigned int AllTilesImg_Width = this->TilesAcross * this->header_TileWidth;
					unsigned int AllTilesImg_High = this->TilesDown * this->header_TileLength;
					// Anzahl der Bands ist vom Padding nicht betroffen!

					// Padding in der horizontalen entfernen
					unsigned int diff_w = AllTilesImg_Width - this->SpecHeader.imgsize[0];

					unsigned int MaxWidth = this->header_TileWidth;// Maximale Breite fuer for Schleife

					unsigned int tilestart_y = (unsigned int)y / this->header_TileLength;

					ttile_t tilestart = tilestart_y * this->TilesAcross;

					unsigned int tile_y = (unsigned int)y - tilestart_y * this->header_TileLength;
	
					unsigned int VectorOff = 0;
					for (tile = 0; tile < this->TilesAcross; tile++)
					{
						// Pixelposition im Tile
						unsigned int tileoff = 0;

						// Tile holen
						TIFFReadEncodedTile(tiffimage, tilestart + tile, tilebuffer, (tsize_t)-1);

						// Buffer fuer memmove auf char legen
						char* chtilebuffer = static_cast<char*>(tilebuffer);

						if (tile == (this->TilesAcross - 1))
						{
							MaxWidth = this->header_TileWidth - diff_w;
						};

						
						for (unsigned int w = 0; w < MaxWidth; w++)
						{
							tileoff = ((tile_y * this->header_TileWidth + w) * this->SpecHeader.imgsize[1] + (unsigned int)z) * this->SpecHeader.pixelsize;

							std::memmove(&Vectorbuff[VectorOff], &chtilebuffer[tileoff], this->SpecHeader.pixelsize);

							VectorOff += (unsigned int)this->SpecHeader.pixelsize;
						};
					};
					_TIFFfree(tilebuffer);
				};
			};
			if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
			{
				TIFFClose(tiffimage);
				this->ErrorMsgLog("Error in SpecIL_TIFF::getVector_X(): BSQ is not supported");
				return -1;
			};
			if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
			{
				TIFFClose(tiffimage);
				this->ErrorMsgLog("Error in SpecIL_TIFF::getVector_X(): BIL is not supported");
				return -1;
			};
		};
		TIFFClose(tiffimage);
		return 0;
	};
	this->ErrorMsgLog("Error in SpecIL_TIFF::getVector_X():");
	return -1;
};
//
int SpecIL_TIFF::getVector_Y(void* vector, int x, int z)
{
	if (this->SpecHeader.type == 0)
	{
		this->ErrorMsgLog("Error in SpecIL_TIFF::getVector_Y(): SpecHeader.type == 0, Data was not read! Run read()!");
		return -1;
	};

	if (this->SpecHeader.type == 1)
	{
		SpecIL_Base::getVector_Y(vector, x, z);
		return 0;
	};

	if (this->SpecHeader.type == 2)
	{
		char* Vectorbuff = static_cast<char*>(vector);

		// LibTiff Warnungen in der cmd ausschalten
		TIFFSetWarningHandler(NULL);

		TIFF* tiffimage = TIFFOpen(this->SpecHeader.filename.c_str(), "r");
		if (tiffimage)
		{
			if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
			{
				if (this->IsTiled == false)
				{
					// striped
					tdata_t stripbuffer;
					stripbuffer = _TIFFmalloc(this->StripSize);

					tstrip_t strip = 0;

					// Falls Padding vorhanden, dann wird die Anzahl an relevanten lines im letzten strip bestimmt
					unsigned int var1 = (unsigned int)this->RowsPerStrip * this->NumOfStrips;
					unsigned int var2 = (unsigned int)this->SpecHeader.imgsize[2] - var1;
					unsigned int RowsLastStrip = this->RowsPerStrip - var2;
					unsigned int MaxRows = this->RowsPerStrip;

					unsigned int VectorOff = 0;
					

					for (strip = 0; strip < this->NumOfStrips; strip++)
					{
						TIFFReadEncodedStrip(tiffimage, strip, stripbuffer, (tsize_t)-1);
						char* chstripbuffer = static_cast<char*>(stripbuffer);

						if (strip == (this->NumOfStrips - 1))
						{
							MaxRows = RowsLastStrip;
						};
						unsigned int StripBufferOff = 0;
						for (unsigned int h = 0; h < MaxRows; h++)
						{
							StripBufferOff = ( (unsigned int)z + (unsigned int)x * (unsigned int)this->SpecHeader.imgsize[1] + h * (unsigned int)this->SpecHeader.imgsize[0] * (unsigned int)this->SpecHeader.imgsize[1]) * this->SpecHeader.pixelsize;


							std::memmove(&Vectorbuff[VectorOff], &chstripbuffer[StripBufferOff], this->SpecHeader.pixelsize);
							VectorOff += this->SpecHeader.pixelsize;
						};
					};

					_TIFFfree(stripbuffer);
				}
				else
				{
					// tiled

					// Vorbereiten
					tdata_t tilebuffer;
					ttile_t tile = 0;
					tilebuffer = _TIFFmalloc(this->TileSize);

					// Dimensionen des zusammengesetzten Bildes ( mit Padding! )
					unsigned int AllTilesImg_Width = this->TilesAcross * this->header_TileWidth;
					unsigned int AllTilesImg_High = this->TilesDown * this->header_TileLength;
					// Anzahl der Bands ist vom Padding nicht betroffen!

					// Padding fuer vertikale entfernen
					unsigned int diff_h = AllTilesImg_High - this->SpecHeader.imgsize[2];

					unsigned int tilestart_x = (unsigned int)x / this->header_TileWidth;
					ttile_t tilestart = tilestart_x;
					unsigned int tile_x = (unsigned int)x - tilestart_x * this->header_TileWidth;

					unsigned int MaxHigh = this->header_TileLength;// Maximale Breite fuer for Schleife

					unsigned int VectorOff = 0;
					unsigned int StripBufferOff = 0;
					for (tile = 0; tile < this->TilesDown; tile++)
					{
						TIFFReadEncodedTile(tiffimage, tilestart + tile*this->TilesAcross, tilebuffer, (tsize_t)-1);
						char* chtilebuffer = static_cast<char*>(tilebuffer);

						if (tile == (this->TilesDown - 1))
						{
							MaxHigh = this->header_TileLength - diff_h;
						};

						for (unsigned int h = 0; h < MaxHigh; h++)
						{
							StripBufferOff = ( (unsigned int)z + (tile_x + h * this->header_TileWidth) * this->SpecHeader.imgsize[1]) * this->SpecHeader.pixelsize;

							std::memmove(&Vectorbuff[VectorOff], &chtilebuffer[StripBufferOff], this->SpecHeader.pixelsize);

							VectorOff += this->SpecHeader.pixelsize;
						};
					};
					_TIFFfree(tilebuffer);
				};
			};
			if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
			{
				TIFFClose(tiffimage);
				this->ErrorMsgLog("Error in SpecIL_TIFF::getVector_Y(): BSQ is not supported");
				return -1;
			};
			if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
			{
				TIFFClose(tiffimage);
				this->ErrorMsgLog("Error in SpecIL_TIFF::getVector_Y(): BIL is not supported");
				return -1;
			};
		};
		TIFFClose(tiffimage);
		return 0;
	};
	this->ErrorMsgLog("Error in SpecIL_TIFF::getVector_Y():");
	return -1;
};
//
int SpecIL_TIFF::getVector_Z(void* vector, int x, int y)
{
	if (this->SpecHeader.type == 0)
	{
		this->ErrorMsgLog("Error in SpecIL_TIFF::getVector_Z(): SpecHeader.type == 0, Data was not read! Run read()!");
		return -1;
	};

	if (this->SpecHeader.type == 1)
	{
		SpecIL_Base::getVector_Z(vector, x, y);
		return 0;
	};

	if (this->SpecHeader.type == 2)
	{
		char* Vectorbuff = static_cast<char*>(vector);

		// LibTiff Warnungen in der cmd ausschalten
		TIFFSetWarningHandler(NULL);

		TIFF* tiffimage = TIFFOpen(this->SpecHeader.filename.c_str(), "r");
		if (tiffimage)
		{
			if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
			{
				if (this->IsTiled == false)
				{
					// striped
					tdata_t stripbuffer;
					tstrip_t strip = 0;

					stripbuffer = _TIFFmalloc(this->StripSize);
					
					strip = (unsigned int)y / (unsigned int)this->RowsPerStrip;
					unsigned int stripe_y = (unsigned int)y % (unsigned int)this->RowsPerStrip;

					TIFFReadEncodedStrip(tiffimage, strip, stripbuffer, (tsize_t)-1);
					char* chstripbuffer = static_cast<char*>(stripbuffer);
					
					unsigned int StripBufferOff = ((unsigned int)x + stripe_y * this->SpecHeader.imgsize[0]) * this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;

					std::memmove(Vectorbuff, &chstripbuffer[StripBufferOff], this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize);

					_TIFFfree(stripbuffer);
				}
				else
				{
					// tiled

					// Vorbereiten
					tdata_t tilebuffer;
					
					tilebuffer = _TIFFmalloc(this->TileSize);

					// Dimensionen des zusammengesetzten Bildes ( mit Padding! )
					unsigned int AllTilesImg_Width = this->TilesAcross * this->header_TileWidth;
					unsigned int AllTilesImg_High = this->TilesDown * this->header_TileLength;
					// Anzahl der Bands ist vom Padding nicht betroffen!

					// Padding fuer vertikale entfernen
					unsigned int diff_h = AllTilesImg_High - this->SpecHeader.imgsize[2];

					unsigned int tilestart_x = (unsigned int)x / this->header_TileWidth;
					unsigned int tile_x = (unsigned int)x - tilestart_x * this->header_TileWidth;

					unsigned int tilestart_y = (unsigned int)y / this->header_TileLength;
					unsigned int tile_y = (unsigned int)y - tilestart_y * this->header_TileLength;

					ttile_t tile = tilestart_y * this->TilesAcross + tilestart_x;

					TIFFReadEncodedTile(tiffimage, tile, tilebuffer, (tsize_t)-1);

					char* chtilebuffer = static_cast<char*>(tilebuffer);
	
					unsigned int TileBufferOff = ((tile_x + tile_y * this->header_TileWidth) * this->SpecHeader.imgsize[1])* this->SpecHeader.pixelsize;

					std::memmove(Vectorbuff, &chtilebuffer[TileBufferOff], this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize);

					_TIFFfree(tilebuffer);
				};
			};
			if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
			{
				TIFFClose(tiffimage);
				this->ErrorMsgLog("Error in SpecIL_TIFF::getVector_Z(): BSQ is not supported");
				return -1;
			};
			if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
			{
				TIFFClose(tiffimage);
				this->ErrorMsgLog("Error in SpecIL_TIFF::getVector_Z(): BIL is not supported");
				return -1;
			};
		};
		TIFFClose(tiffimage);
		return 0;
	};
	this->ErrorMsgLog("Error in SpecIL_TIFF::getVector_Z():");
	return -1;
};