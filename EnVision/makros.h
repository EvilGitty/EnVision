

#define  _imgIndex (main->Gui::tabRecord.imgIndex)
#define _samples (ImageAttribute::Record[0].cubeDim[0])
#define _lines (ImageAttribute::Record[0].cubeDim[1])
#define _channels (ImageAttribute::Record[0].cubeDim[2])
#define _opencvDataType (ImageAttribute::Record[0].opencvDataType)
#define _transpose (ImageAttribute::Record[0].transposeDisplay)
#define _pixelsize (ImageAttribute::Record[0].pixelsize)

#define _numberOfTiles_x (ImageAttribute::Record[0].imgtile.numberOfTiles_x)
#define _numberOfTiles_y (ImageAttribute::Record[0].imgtile.numberOfTiles_y)

#define _filename (ImageAttribute::Record[_imgIndex].imgFilename_s)
#define _maxDataVal (ImageAttribute::Record[_imgIndex].data_type_maxval)
#define _datatype (ImageAttribute::Record[_imgIndex].datatype)