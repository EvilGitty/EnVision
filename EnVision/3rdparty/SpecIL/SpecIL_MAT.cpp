#include "SpecIL_MAT.h"
#include <iostream>

SpecIL_MAT::~SpecIL_MAT()
{
	//this->CleanMemory();
};
//
SpecIL_MAT::SpecIL_MAT()
{
	this->MATinit();
};
//
void SpecIL_MAT::MATinit()
{
	this->SpecHeader.ID = "Matlab file";
	
	this->pixelsize = 0;

	this->hyspec_imgsize[0] = 0;
	this->hyspec_imgsize[1] = 0;
	this->hyspec_imgsize[2] = 0;
	this->hyspec_dataorder = "undef";
	this->hyspec_headsize = 0;
	this->hyspec_saturated = 0;
	//this->header_wavelen.clear();	
	this->hyspec_imgcube_datatyp = 0;
	this->hyspec_flag_normwhite = 0;

	this->lab_colormap = "";

};
//
int SpecIL_MAT::readFileHeader()
{
	const char *fn = this->SpecHeader.filename.c_str();
	mat_t* matfp;
	matfp = Mat_Open(fn, MAT_ACC_RDONLY);
	if (matfp != NULL)
	{
		const char *var_data = ("data");
		matvar_t* matvar_data;
		matvar_data = Mat_VarReadInfo(matfp, var_data); // function reads the information for the variable
		if (matvar_data != NULL)
		{
			const char* fieldname = "hyspec";
			matvar_t* matvar_data_hyspec;
			matvar_data_hyspec = Mat_VarGetStructFieldByName(matvar_data, fieldname, 0);
			std::cout << std::endl << fieldname << ":" << std::endl;
			if (matvar_data_hyspec != NULL)
			{
				unsigned int hyspec_NumFileds = Mat_VarGetNumberOfFields(matvar_data_hyspec);
				std::cout << "hyspec_NumFileds = " << hyspec_NumFileds << std::endl;
				matvar_t* matvar_hyspec_var;
				for (size_t i = 0; i < hyspec_NumFileds; i++)
				{
					matvar_hyspec_var = Mat_VarGetStructFieldByIndex(matvar_data_hyspec, i, 0);
					std::cout << "i = " << i << " => " << matvar_hyspec_var->name << std::endl;
				};

				fieldname = "filename";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_filename;
				field_filename = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_filename != NULL)
				{
					if (field_filename->data_type == MAT_T_UINT8)
					{
						unsigned long field_size = Mat_VarGetSize(field_filename);
						std::cout << "field_size = " << field_size << std::endl;
						if (field_size > NULL)
						{
							std::cout << "reading this field is not implemented" << std::endl;
							/*

							char* filename_buffer = new char[field_size];

							int start_filename[2];
							start_filename[0] = 0;
							start_filename[1] = 0;

							int stride_filename[2];
							stride_filename[0] = 1;
							stride_filename[1] = 1;

							int edge_filename[2];
							edge_filename[0] = field_filename->dims[0];
							edge_filename[1] = field_filename->dims[1];

							Mat_VarReadData(matfp, field_filename, filename_buffer, start_filename, stride_filename, edge_filename);

							std::cout << "filename_buffer = " << std::string(filename_buffer) << std::endl;

							// irgendwo speichern?


							delete[] filename_buffer;
							*/
						}
						else
						{
							std::cout << "Warning: field filename is empty" << std::endl;
							this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning: field filename is empty");
						};
					}
					else
					{
						std::cout << "Warning: datatyp of filename is not supported" << std::endl;
						this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning: datatyp of filename is not supported");
					};
				}
				else
				{
					std::cout << "Warning: no field filename" << std::endl;
					this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, no field filename");
				};

				fieldname = "file";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_file;
				field_file = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_file != NULL)
				{
					if (field_file->data_type == MAT_T_DOUBLE)
					{
						unsigned long field_size = Mat_VarGetSize(field_file);
						std::cout << "field_size = " << field_size << std::endl;
						if (field_size > NULL)
						{
							std::cout << "reading this field is not implemented" << std::endl;
							/*

							double* file_buffer = (double*)new char[field_size];

							int start_file[2];
							start_file[0] = 0;
							start_file[1] = 0;

							int stride_file[2];
							stride_file[0] = 1;
							stride_file[1] = 1;

							int edge_file[2];
							edge_file[0] = field_file->dims[0];
							edge_file[1] = field_file->dims[1];

							Mat_VarReadData(matfp, field_file, file_buffer, start_file, stride_file, edge_file);

							// irgendwo speichern?

							delete[] file_buffer;
							*/
						}
						else
						{
							std::cout << "Warning: field file is empty" << std::endl;
							this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning: field file is empty");
						};
					}
					else
					{
						std::cout << "Warning: datatyp of file is not supported" << std::endl;
						this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning: datatyp of file is not supported");
					};
				}
				else
				{
					std::cout << "Warning: no field file" << std::endl;
					this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, no field file");
				};

				// Datentyp und Daten holen
				fieldname = "imgcube";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_imgcube;
				field_imgcube = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_imgcube != NULL)
				{
					this->hyspec_imgcube_datatyp = field_imgcube->data_type;

					//8-bit signed integer
					if (field_imgcube->data_type == MAT_T_INT8)
					{
						this->SpecHeader.data_type = t_SpecHead::DT_8_BYTE;
						this->SpecHeader.data_type_str = "8bit signed integer";
						this->SpecHeader.pixelsize = 1;
					};
					//8-bit unsigned integer
					if (field_imgcube->data_type == MAT_T_UINT8)
					{
						this->SpecHeader.data_type = t_SpecHead::DT_8_BYTE;
						this->SpecHeader.data_type_str = "8bit unsinged integer";
						this->SpecHeader.pixelsize = 1;
					};
					//16-bit signed integer
					if (field_imgcube->data_type == MAT_T_INT16)
					{
						this->SpecHeader.data_type = t_SpecHead::DT_16_SINT;
						this->SpecHeader.data_type_str = "16bit signed integer";
						this->SpecHeader.pixelsize = 2;
					};
					//16-bit unsigned integer
					if (field_imgcube->data_type == MAT_T_UINT16)
					{
						this->SpecHeader.data_type = t_SpecHead::DT_16_UINT;
						this->SpecHeader.data_type_str = "16bit unsigned integer";
						this->SpecHeader.pixelsize = 2;
					};
					//32-bit signed integer
					if (field_imgcube->data_type == MAT_T_INT32)
					{
						this->SpecHeader.data_type = t_SpecHead::DT_32_SLONG;
						this->SpecHeader.data_type_str = "32bit signed integer";
						this->SpecHeader.pixelsize = 4;
					};
					//32-bit unsigned integer
					if (field_imgcube->data_type == MAT_T_UINT32)
					{
						this->SpecHeader.data_type = t_SpecHead::DT_32_ULONG;
						this->SpecHeader.data_type_str = "32bit unsigned integer";
						this->SpecHeader.pixelsize = 4;
					};
					//IEEE 754 single precision
					if (field_imgcube->data_type == MAT_T_SINGLE)
					{
						this->SpecHeader.data_type = t_SpecHead::DT_32_FLOAT;
						this->SpecHeader.data_type_str = "32bit IEEE 754 single precision";
						this->SpecHeader.pixelsize = 4;
					};
					//IEEE 754 double precision
					if (field_imgcube->data_type == MAT_T_DOUBLE)
					{
						this->SpecHeader.data_type = t_SpecHead::DT_64_DOUBLE;
						this->SpecHeader.data_type_str = "64bit IEEE 754 double precision";
						this->SpecHeader.pixelsize = 8;
					};
					//64-bit signed integer
					if (field_imgcube->data_type == MAT_T_INT64)
					{
						this->SpecHeader.data_type = t_SpecHead::DT_64_SLONG;
						this->SpecHeader.data_type_str = "64bit signed integer";
						this->SpecHeader.pixelsize = 8;
					};
					//64-bit unsigned integer
					if (field_imgcube->data_type == MAT_T_UINT64)
					{
						this->SpecHeader.data_type = t_SpecHead::DT_64_ULONG;
						this->SpecHeader.data_type_str = "64bit unsigned integer";
						this->SpecHeader.pixelsize = 8;
					};

					// unsupported formats
					if (field_imgcube->data_type == MAT_T_MATRIX || field_imgcube->data_type == MAT_T_COMPRESSED || field_imgcube->data_type == MAT_T_UTF8
						|| field_imgcube->data_type == MAT_T_UTF16 || field_imgcube->data_type == MAT_T_UTF32
						|| field_imgcube->data_type == MAT_T_STRING || field_imgcube->data_type == MAT_T_CELL
						|| field_imgcube->data_type == MAT_T_STRUCT || field_imgcube->data_type == MAT_T_ARRAY
						|| field_imgcube->data_type == MAT_T_FUNCTION)
					{
						/*
						MAT_T_MATRIX = 14,    /**< @brief matrix data type
						MAT_T_COMPRESSED = 15,    /**< @brief compressed data type
						MAT_T_UTF8 = 16,    /**< @brief 8-bit unicode text data type
						MAT_T_UTF16 = 17,    /**< @brief 16-bit unicode text data type
						MAT_T_UTF32 = 18,    /**< @brief 32-bit unicode text data type

						MAT_T_STRING = 20,    /**< @brief String data type
						MAT_T_CELL = 21,    /**< @brief Cell array data type
						MAT_T_STRUCT = 22,    /**< @brief Structure data type
						MAT_T_ARRAY = 23,    Array data type
						MAT_T_FUNCTION = 24     Function data type
						*/

						std::cout << "err: wrong matio datatype" << std::endl;

						// Error
						std::string emsg;
						emsg = "In SpecIL_MAT::readFileHeader(): Error while reading image information. File format is not supported!";
						this->ErrorMsgLog(emsg);
						//Mat_Close(matfp);
						//return -1;
					};
					std::cout << "datatype = " << this->SpecHeader.data_type_str << std::endl;
				};

				fieldname = "wavelen";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_wavelen;
				field_wavelen = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_wavelen != NULL)
				{
					if (field_wavelen->data_type == MAT_T_DOUBLE)
					{
						unsigned long field_size = Mat_VarGetSize(field_wavelen) * sizeof(unsigned char);
						std::cout << "field_size = " << field_size << std::endl;
						if (field_size > 0)
						{
							double* data_wavelen = (double*)new char[field_size];

							int start_wavelen[2];
							start_wavelen[0] = 0;
							start_wavelen[1] = 0;

							int stride_wavelen[2];
							stride_wavelen[0] = 1;
							stride_wavelen[1] = 1;

							int edge_wavelen[2];
							edge_wavelen[0] = field_wavelen->dims[0];
							edge_wavelen[1] = field_wavelen->dims[1];

							Mat_VarReadData(matfp, field_wavelen, data_wavelen, start_wavelen, stride_wavelen, edge_wavelen);

							for (size_t i = 0; i < edge_wavelen[1]; i++)
							{
								this->SpecHeader.wavelen.push_back((float)(data_wavelen[i]));
							};

							this->SpecHeader.wavelenunit = "nm";

							delete[] data_wavelen;

							std::cout << "wavelen loaded..." << std::endl;
						}
						else
						{
							std::cout << "Warning, field dataorder is empty" << std::endl;
							this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, field dataorder is empty");
						};
					}
					else
					{
						std::cout << "Warning, datatyp of dataorder is not supported" << std::endl;
						this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, datatyp of dataorder is not supported");
					};
				}
				else
				{
					std::cout << "Warning, no field dataorder" << std::endl;
					this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, no field dataorder");
				};

				fieldname = "imgsize";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_imgsize;
				field_imgsize = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_imgsize != NULL)
				{
					if (field_imgsize->data_type == MAT_T_DOUBLE)
					{
						unsigned long field_size = Mat_VarGetSize(field_imgsize);
						std::cout << "field_size = " << field_size << std::endl;
						if (field_size > NULL)
						{

							//		double* data_imgsize = (double *)malloc(field_size*(sizeof(unsigned char)));
							//		double* data_imgsize = new double[field_size];
							double* data_imgsize = (double*)new char[field_size];

							int start_imgsize[2];
							start_imgsize[0] = 0;
							start_imgsize[1] = 0;

							int stride_imgsize[2];
							stride_imgsize[0] = 1;
							stride_imgsize[1] = 1;

							int edge_imgsize[2];
							edge_imgsize[0] = field_imgsize->dims[0];
							edge_imgsize[1] = field_imgsize->dims[1];

							Mat_VarReadData(matfp, field_imgsize, data_imgsize, start_imgsize, stride_imgsize, edge_imgsize);

							this->hyspec_imgsize[0] = (unsigned long long) data_imgsize[0]; // samples
							this->hyspec_imgsize[1] = (unsigned long long) data_imgsize[1]; // bands
							this->hyspec_imgsize[2] = (unsigned long long) data_imgsize[2]; // lines

							std::cout << "data_imgsize[0] = " << data_imgsize[0] << std::endl;
							std::cout << "data_imgsize[1] = " << data_imgsize[1] << std::endl;
							std::cout << "data_imgsize[2] = " << data_imgsize[2] << std::endl;

							delete[] data_imgsize;
						}
						else
						{
							std::cout << "Error: field imgsize is empty" << std::endl;
							this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Error: field imgsize is empty");
						};
					}
					else
					{
						std::cout << "Error: datatyp of imgsize is not supported" << std::endl;
						this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Error: datatyp of imgsize is not supported");
						return -1;
					};
				}
				else
				{
					std::cout << "Error: no field imgsize" << std::endl;
					this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Error, no field imgsize");
					return -1;
				};

				fieldname = "dataorder";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_dataorder;
				field_dataorder = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_dataorder != NULL)
				{
					if (field_dataorder->data_type == MAT_T_DOUBLE)
					{
						unsigned long field_size = Mat_VarGetSize(field_dataorder);
						std::cout << "field_size = " << field_size << std::endl;
						if (field_size > 0)
						{
							// noch nicht getestet, da keine passende Terstdatei vorhanden ist..
							// Der Datentyp des Feldes muss auch vorher noch abgefragt werden !
							std::cout << "reading this field is not implemented" << std::endl;
							/*


							unsigned long field_size = Mat_VarGetSize(field_dataorder);
							char* data_dataorder = new char[field_size];


							int start_dataorder[2];
							start_dataorder[0] = 0;
							start_dataorder[1] = 0;

							int stride_dataorder[2];
							stride_dataorder[0] = 1;
							stride_dataorder[1] = 1;

							int edge_dataorder[2];
							edge_dataorder[0] = field_dataorder->dims[0];
							edge_dataorder[1] = field_dataorder->dims[1];


							Mat_VarReadData(matfp, field_dataorder, data_dataorder, start_dataorder, stride_dataorder, edge_dataorder);

							if (data_dataorder == "bil")
							{
								this->SpecHeader.interleave = t_SpecHead::IL_BIL;
								std::cout << "dataorder = bil" << std::endl;
							}
							else if (data_dataorder == "bsq")
							{
								this->SpecHeader.interleave = t_SpecHead::IL_BSQ;
								std::cout << "dataorder = bsq" << std::endl;
							}
							else if (data_dataorder == "bip")
							{
								this->SpecHeader.interleave = t_SpecHead::IL_BIP;
								std::cout << "dataorder = bip" << std::endl;
							}
							else
							{
								this->SpecHeader.interleave = t_SpecHead::IL_UNKNOWN;
								std::cout << "WARNING: dataorder = UNKNOWN" << std::endl;
								this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, unknown dataorder");
							};

							*/
						}
						else
						{
							std::cout << "Warning, field dataorder is empty" << std::endl;
							this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, field dataorder is empty");
						};
					}
					else
					{
						std::cout << "Warning, datatyp of dataorder is not supported" << std::endl;
						this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, datatyp of dataorder is not supported");
					};
				}
				else
				{
					std::cout << "Warning, no field dataorder" << std::endl;
					this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, no field dataorder");
				};

				fieldname = "fid";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_fid;
				field_fid = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_fid != NULL)
				{
					if (field_fid->data_type == MAT_T_DOUBLE)
					{
						unsigned long field_size = Mat_VarGetSize(field_fid);
						std::cout << "field_size = " << field_size << std::endl;
						if (field_size > 0)
						{
							std::cout << "reading this field is not implemented" << std::endl;
							/*

							double* data_fid = (double*)new char[field_size];

							int start_fid[2];
							start_fid[0] = 0;
							start_fid[1] = 0;

							int stride_fid[2];
							stride_fid[0] = 1;
							stride_fid[1] = 1;

							int edge_fid[2];
							edge_fid[0] = field_fid->dims[0];
							edge_fid[1] = field_fid->dims[1];

							Mat_VarReadData(matfp, field_fid, data_fid, start_fid, stride_fid, edge_fid);

							// irgendwo speichern?


							delete[] data_fid;

							*/
						}
						else
						{
							std::cout << "Warning, field fid is empty" << std::endl;
							this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, field fid is empty");
						};
					}
					else
					{
						std::cout << "Warning, datatyp of fid is not supported" << std::endl;
						this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, datatyp of fid is not supported");
					};
				}
				else
				{
					std::cout << "Warning, no field fid" << std::endl;
					this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, no field fid");
				};

				fieldname = "headsize";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_headsize;
				field_headsize = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_headsize != NULL)
				{
					if (field_headsize->data_type == MAT_T_DOUBLE)
					{
						unsigned long field_size = Mat_VarGetSize(field_headsize);
						std::cout << "field_size = " << field_size << std::endl;
						if (field_size > 0)
						{
							std::cout << "reading this field is not implemented" << std::endl;
							/*

							double* data_headsize = (double*)new char[field_size];

							int start_headsize[2];
							start_headsize[0] = 0;
							start_headsize[1] = 0;

							int stride_headsize[2];
							stride_headsize[0] = 1;
							stride_headsize[1] = 1;

							int edge_headsize[2];
							edge_headsize[0] = field_headsize->dims[0];
							edge_headsize[1] = field_headsize->dims[1];

							Mat_VarReadData(matfp, field_headsize, data_headsize, start_headsize, stride_headsize, edge_headsize);

							this->hyspec_headsize = (unsigned long long) data_headsize[0]; // samples

							std::cout << "hyspec_headsize = " << data_headsize[0] << std::endl;

							delete[] data_headsize;
							*/
						}
						else
						{
							std::cout << "Warning, field headsize is empty" << std::endl;
							this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, field headsize is empty");
						};
					}
					else
					{
						std::cout << "Warning, datatyp of headsize is not supported" << std::endl;
						this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, datatyp of headsize is not supported");
					};
				}
				else
				{
					std::cout << "Warning, no field headsize" << std::endl;
					this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, no field headsize");
				};

				fieldname = "flag_normwhite";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_flag_normwhite;
				field_flag_normwhite = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_flag_normwhite != NULL)
				{
					if (field_flag_normwhite->data_type == MAT_T_DOUBLE)
					{
						unsigned long field_size = Mat_VarGetSize(field_flag_normwhite);
						std::cout << "field_size = " << field_size << std::endl;
						if (field_size > 0)
						{
							double* data_flag_normwhite = new double[1];

							int start_flag_normwhite[2];
							start_flag_normwhite[0] = 0;
							start_flag_normwhite[1] = 0;

							int stride_flag_normwhite[2];
							stride_flag_normwhite[0] = 1;
							stride_flag_normwhite[1] = 1;

							int edge_flag_normwhite[2];
							edge_flag_normwhite[0] = field_flag_normwhite->dims[0];
							edge_flag_normwhite[1] = field_flag_normwhite->dims[1];

							Mat_VarReadData(matfp, field_headsize, data_flag_normwhite, start_flag_normwhite, stride_flag_normwhite, edge_flag_normwhite);

							std::cout << "data_flag_normwhite = " << data_flag_normwhite[0] << std::endl;

							this->hyspec_flag_normwhite = data_flag_normwhite[0];

							delete[] data_flag_normwhite;
						}
						else
						{
							std::cout << "Warning, field headsize is empty" << std::endl;
							this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, field headsize is empty");
						};
					}
					else
					{
						std::cout << "Warning, datatyp of headsize is not supported" << std::endl;
						this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, datatyp of headsize is not supported");
					};
				}
				else
				{
					std::cout << "Warning, no field headsize" << std::endl;
					this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, no field headsize");
				};

				fieldname = "saturated";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_saturated;
				field_saturated = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_saturated != NULL)
				{
					if (field_saturated->data_type == MAT_T_DOUBLE)
					{
						unsigned long field_size = Mat_VarGetSize(field_saturated);
						std::cout << "field_size = " << field_size << std::endl;
						if (field_size > 0)
						{
							double* data_saturated = (double*)new char[field_size];

							int start_saturated[2];
							start_saturated[0] = 0;
							start_saturated[1] = 0;

							int stride_saturated[2];
							stride_saturated[0] = 1;
							stride_saturated[1] = 1;

							int edge_saturated[2];
							edge_saturated[0] = field_saturated->dims[0];
							edge_saturated[1] = field_saturated->dims[1];

							Mat_VarReadData(matfp, field_saturated, data_saturated, start_saturated, stride_saturated, edge_saturated);

							this->hyspec_saturated = (unsigned long long) data_saturated[0]; // samples

							std::cout << "data_saturated = " << data_saturated[0] << std::endl;

							delete[] data_saturated;
						}
						else
						{
							std::cout << "Warning, field saturated is empty" << std::endl;
							this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, field saturated is empty");
						};
					}
					else
					{
						std::cout << "Warning, datatyp of saturated is not supported" << std::endl;
						this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, datatyp of saturated is not supported");
					};
				}
				else
				{
					std::cout << "Warning, no field saturated" << std::endl;
					this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, no field saturated");
				};
			};//field hyspec

			// lab
			fieldname = "lab";
			matvar_t* matvar_data_lab;
			matvar_data_lab = Mat_VarGetStructFieldByName(matvar_data, fieldname, 0);
			std::cout << std::endl << fieldname << ":" << std::endl;
			unsigned int lab_NumFileds = Mat_VarGetNumberOfFields(matvar_data_lab);
			std::cout << "lab_NumFileds = " << lab_NumFileds << std::endl;
			matvar_t* matvar_lab_var;
			for (size_t i = 0; i < lab_NumFileds; i++)
			{
				matvar_lab_var = Mat_VarGetStructFieldByIndex(matvar_data_lab, i, 0);
				std::cout << "i = " << i << " => " << matvar_lab_var->name << std::endl;
			};
			if (matvar_data_lab != NULL)
			{
				fieldname = "valimg";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_valimg;
				field_valimg = Mat_VarGetStructFieldByName(matvar_data_lab, fieldname, 0);
				if (field_valimg != NULL)
				{
					if (field_valimg->data_type == MAT_T_DOUBLE)
					{
						unsigned long field_size = Mat_VarGetSize(field_valimg);
						std::cout << "field_size = " << field_size << std::endl;
						if (field_size > 0)
						{
							std::cout << "reading this field is not implemented" << std::endl;
							/*

							char* data_valimg = new char[field_size];

							int start_valimg[3];
							start_valimg[0] = 0;
							start_valimg[1] = 0;
							start_valimg[2] = 0;

							int stride_valimg[3];
							stride_valimg[0] = 1;
							stride_valimg[1] = 1;
							stride_valimg[2] = 1;

							int edge_valimg[3];
							edge_valimg[0] = field_valimg->dims[0];
							edge_valimg[1] = field_valimg->dims[1];
							edge_valimg[2] = field_valimg->dims[1];

							Mat_VarReadData(matfp, field_valimg, data_valimg, start_valimg, stride_valimg, edge_valimg);

							std::cout << "loading lab.valimg done.." << std::endl;
							delete[] data_valimg;
							*/
						}
						else
						{
							std::cout << "Warning, field valimg is empty" << std::endl;
							this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, field valimg is empty");
						};
					}
					else
					{
						std::cout << "Warning, datatyp of valimg is not supported" << std::endl;
						this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, datatyp of valimg is not supported");
					};
				}
				else
				{
					std::cout << "Warning, no field valimg" << std::endl;
					this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, no field valimg");
				};

				fieldname = "rgbimg";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_rgbimg;
				field_rgbimg = Mat_VarGetStructFieldByName(matvar_data_lab, fieldname, 0);
				if (field_rgbimg != NULL)
				{
					if (field_rgbimg->data_type == MAT_T_DOUBLE)
					{
						unsigned long field_size = Mat_VarGetSize(field_rgbimg);
						std::cout << "field_size = " << field_size << std::endl;
						if (field_size > 0)
						{
							std::cout << "reading this field is not implemented" << std::endl;
							/*

							char* data_rgbimg = new char[field_size];

							int start_rgbimg[3];
							start_rgbimg[0] = 0;
							start_rgbimg[1] = 0;
							start_rgbimg[2] = 0;

							int stride_rgbimg[3];
							stride_rgbimg[0] = 1;
							stride_rgbimg[1] = 1;
							stride_rgbimg[2] = 1;

							int edge_rgbimg[3];
							edge_rgbimg[0] = field_rgbimg->dims[0];
							edge_rgbimg[1] = field_rgbimg->dims[1];
							edge_rgbimg[2] = field_rgbimg->dims[1];

							Mat_VarReadData(matfp, field_rgbimg, data_rgbimg, start_rgbimg, stride_rgbimg, edge_rgbimg);

							std::cout << "loading lab.rgbimg done.." << std::endl;
							delete[] data_rgbimg;
							*/
						}
						else
						{
							std::cout << "Warning, field rgbimg is empty" << std::endl;
							this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, field rgbimg is empty");
						};
					}
					else
					{
						std::cout << "Warning, datatyp of rgbimg is not supported" << std::endl;
						this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, datatyp of rgbimg is not supported");
					};
				}
				else
				{
					std::cout << "Warning, no field valimg" << std::endl;
					this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, no field valimg");
				};

				fieldname = "lablist";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_lablist;
				field_lablist = Mat_VarGetStructFieldByName(matvar_data_lab, fieldname, 0);
				if (field_lablist != NULL)
				{
					if (field_lablist->data_type == MAT_T_CELL)
					{
						unsigned long field_size = Mat_VarGetSize(field_lablist);
						std::cout << "field_size = " << field_size << std::endl;
						if (field_size > 0)
						{
							std::cout << "reading this field is not implemented" << std::endl;
						}
						else
						{
							std::cout << "Warning, field rgbimg is empty" << std::endl;
							this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, field rgbimg is empty");
						};
					}
					else
					{
						std::cout << "Warning, datatyp of lablist is not supported" << std::endl;
						this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, datatyp of lablist is not supported");
					};
				}
				else
				{
					std::cout << "Warning, no field lablist" << std::endl;
					this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, no field lablist");
				};

				fieldname = "colormap";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_colormap;
				field_colormap = Mat_VarGetStructFieldByName(matvar_data_lab, fieldname, 0);
				if (field_colormap != NULL)
				{
					if (field_colormap->data_type == MAT_T_UINT8)
					{
						unsigned long field_size = Mat_VarGetSize(field_colormap);
						std::cout << "field_size = " << field_size << std::endl;
						if (field_size > 0)
						{
							std::cout << "reading this field is not implemented" << std::endl;
							/*
							unsigned long field_size = Mat_VarGetSize(field_colormap);
							char* data_colormap = new char[field_size];


							int start_colormap[1];
							start_colormap[0] = 0;
						//	start_colormap[1] = 0;

							int stride_colormap[1];
							stride_colormap[0] = 1;
						//	stride_colormap[1] = 1;

							int edge_colormap[1];
							edge_colormap[0] = field_colormap->dims[0];
						//	edge_colormap[1] = field_colormap->dims[1];


							Mat_VarReadData(matfp, field_colormap, data_colormap, start_colormap, stride_colormap, edge_colormap);

							if (data_colormap == "jet")
							{
								this->lab_colormap = "jet";
								std::cout << "colormap = jet" << std::endl;
							}
							else
							{
								std::cout << "WARNING: unknown colormap " << std::string(data_colormap) << std::endl;
								this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, unknown colormap");
							};

							delete[] data_colormap;
							*/

						}
						else
						{
							std::cout << "Warning, field colormap is empty" << std::endl;
							this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, field colormap is empty");
						};
					}
					else
					{
						std::cout << "Warning, datatyp of colormap is not supported" << std::endl;
						this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, datatyp of colormap is not supported");
					};
				}
				else
				{
					std::cout << "Warning, no field colormap" << std::endl;
					this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Warning, no field colormap");
				};
			};// field lab

			// roi
			fieldname = "roi";
			matvar_t* matvar_data_roi;
			matvar_data_roi = Mat_VarGetStructFieldByName(matvar_data, fieldname, 0);
			std::cout << std::endl << fieldname << ":" << std::endl;
			unsigned int roi_NumFileds = Mat_VarGetNumberOfFields(matvar_data_roi);
			std::cout << "roi_NumFileds = " << roi_NumFileds << std::endl;
			matvar_t* matvar_roi_var;
			for (size_t i = 0; i < roi_NumFileds; i++)
			{
				matvar_roi_var = Mat_VarGetStructFieldByIndex(matvar_data_roi, i, 0);
				std::cout << "i = " << i << " => " << matvar_roi_var->name << std::endl;
			};
			if (matvar_data_roi != NULL)
			{
				std::cout << "reading this field is not implemented" << std::endl;
			}
			else
			{
				std::cout << "field is empty" << std::endl;
			};// field roi

			// unmixing
			fieldname = "unmixing";
			matvar_t* matvar_data_unmixing;
			matvar_data_unmixing = Mat_VarGetStructFieldByName(matvar_data, fieldname, 0);
			std::cout << std::endl << fieldname << ":" << std::endl;
			
			if (matvar_data_unmixing != NULL)
			{
				unsigned int unmixing_NumFileds = Mat_VarGetNumberOfFields(matvar_data_unmixing);
				std::cout << "unmixing_NumFileds = " << unmixing_NumFileds << std::endl;
				matvar_t* matvar_unmixing_var;
				for (size_t i = 0; i < unmixing_NumFileds; i++)
				{
					matvar_unmixing_var = Mat_VarGetStructFieldByIndex(matvar_data_unmixing, i, 0);
					std::cout << "i = " << i << " => " << matvar_unmixing_var->name << std::endl;
				};
				std::cout << "reading this field is not implemented" << std::endl;
			}
			else
			{
				std::cout << "field is empty" << std::endl;
			};// field unmixing

			// sample
			fieldname = "sample";
			matvar_t* matvar_data_sample;
			matvar_data_sample = Mat_VarGetStructFieldByName(matvar_data, fieldname, 0);
			std::cout << std::endl << fieldname << ":" << std::endl;
			if (matvar_data_sample != NULL)
			{
				unsigned int sample_NumFileds = Mat_VarGetNumberOfFields(matvar_data_sample);
				std::cout << "sample_NumFileds = " << sample_NumFileds << std::endl;
				matvar_t* matvar_sample_var;
				for (size_t i = 0; i < sample_NumFileds; i++)
				{
					matvar_sample_var = Mat_VarGetStructFieldByIndex(matvar_data_sample, i, 0);
					std::cout << "i = " << i << " => " << matvar_sample_var->name << std::endl;
				};

				fieldname = "val";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_val;
				field_val = Mat_VarGetStructFieldByName(matvar_data_sample, fieldname, 0);
				if (field_val != NULL)
				{
					std::cout << "reading this field is not implemented" << std::endl;
				}
				else
				{
					std::cout << "field is empty" << std::endl;
				};

				fieldname = "target";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_target;
				field_target = Mat_VarGetStructFieldByName(matvar_data_sample, fieldname, 0);
				if (field_target != NULL)
				{
					std::cout << "reading this field is not implemented" << std::endl;
				}
				else
				{
					std::cout << "field is empty" << std::endl;
				};

				fieldname = "pos";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_pos;
				field_pos = Mat_VarGetStructFieldByName(matvar_data_sample, fieldname, 0);
				if (field_pos != NULL)
				{
					std::cout << "reading this field is not implemented" << std::endl;
				}
				else
				{
					std::cout << "field is empty" << std::endl;
				};

				fieldname = "lab";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_lab;
				field_lab = Mat_VarGetStructFieldByName(matvar_data_sample, fieldname, 0);
				if (field_lab != NULL)
				{
					std::cout << "reading this field is not implemented" << std::endl;
				}
				else
				{
					std::cout << "field is empty" << std::endl;
				};

				fieldname = "clab";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_clab;
				field_clab = Mat_VarGetStructFieldByName(matvar_data_sample, fieldname, 0);
				if (field_clab != NULL)
				{
					std::cout << "reading this field is not implemented" << std::endl;
				}
				else
				{
					std::cout << "field is empty" << std::endl;
				};

				fieldname = "names";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_names;
				field_names = Mat_VarGetStructFieldByName(matvar_data_sample, fieldname, 0);
				if (field_names != NULL)
				{
					std::cout << "reading this field is not implemented" << std::endl;
				}
				else
				{
					std::cout << "field is empty" << std::endl;
				};

				fieldname = "cnames";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_cnames;
				field_cnames = Mat_VarGetStructFieldByName(matvar_data_sample, fieldname, 0);
				if (field_cnames != NULL)
				{
					std::cout << "reading this field is not implemented" << std::endl;
				}
				else
				{
					std::cout << "field is empty" << std::endl;
				};

				fieldname = "white";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_white;
				field_white = Mat_VarGetStructFieldByName(matvar_data_sample, fieldname, 0);
				if (field_white != NULL)
				{
					std::cout << "reading this field is not implemented" << std::endl;
				}
				else
				{
					std::cout << "field is empty" << std::endl;
				};

				fieldname = "white_type";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_white_type;
				field_white_type = Mat_VarGetStructFieldByName(matvar_data_sample, fieldname, 0);
				if (field_white_type != NULL)
				{
					std::cout << "reading this field is not implemented" << std::endl;
				}
				else
				{
					std::cout << "field is empty" << std::endl;
				};

				fieldname = "chipsens";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_chipsens;
				field_chipsens = Mat_VarGetStructFieldByName(matvar_data_sample, fieldname, 0);
				if (field_chipsens != NULL)
				{
					std::cout << "reading this field is not implemented" << std::endl;
				}
				else
				{
					std::cout << "field is empty" << std::endl;
				};

				fieldname = "chipsens_type";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_chipsens_type;
				field_chipsens_type = Mat_VarGetStructFieldByName(matvar_data_sample, fieldname, 0);
				if (field_chipsens_type != NULL)
				{
					std::cout << "reading this field is not implemented" << std::endl;
				}
				else
				{
					std::cout << "field is empty" << std::endl;
				};

				fieldname = "wavelen";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_wavelen;
				field_wavelen = Mat_VarGetStructFieldByName(matvar_data_sample, fieldname, 0);
				if (field_wavelen != NULL)
				{
					std::cout << "reading this field is not implemented" << std::endl;
				}
				else
				{
					std::cout << "field is empty" << std::endl;
				};

				fieldname = "flag_normwhite";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_flag_normwhite;
				field_flag_normwhite = Mat_VarGetStructFieldByName(matvar_data_sample, fieldname, 0);
				if (field_flag_normwhite != NULL)
				{
					std::cout << "reading this field is not implemented" << std::endl;
				}
				else
				{
					std::cout << "field is empty" << std::endl;
				};

				fieldname = "collectdsname";
				std::cout << std::endl << fieldname << ":" << std::endl;
				matvar_t* field_collectdsname;
				field_collectdsname = Mat_VarGetStructFieldByName(matvar_data_sample, fieldname, 0);
				if (field_collectdsname != NULL)
				{
					std::cout << "reading this field is not implemented" << std::endl;
				}
				else
				{
					std::cout << "field is empty" << std::endl;
				};
			};// field sample

			// obj
			fieldname = "obj";
			matvar_t* matvar_data_obj;
			matvar_data_obj = Mat_VarGetStructFieldByName(matvar_data, fieldname, 0);
			std::cout << std::endl << fieldname << ":" << std::endl;
			if (matvar_data_obj != NULL)
			{
				unsigned int obj_NumFileds = Mat_VarGetNumberOfFields(matvar_data_obj);
				std::cout << "obj_NumFileds = " << obj_NumFileds << std::endl;
				matvar_t* matvar_obj_var;
				for (size_t i = 0; i < obj_NumFileds; i++)
				{
					matvar_obj_var = Mat_VarGetStructFieldByIndex(matvar_data_obj, i, 0);
					std::cout << "i = " << i << " => " << matvar_obj_var->name << std::endl;
				};
				std::cout << "reading this field is not implemented" << std::endl;
			};// field obj

			// Header Informationen geladen
			this->FileHeaderLoaded = 1;
			Mat_VarFree(matvar_data);
		};
		Mat_Close(matfp);
		return 0;
	};
	this->ErrorMsgLog("In SpecIL_MAT::readFileHeader(): Error while reading image information");
	return -1;
};
//
int SpecIL_MAT::readImageData()
{
	const char *fn = this->SpecHeader.filename.c_str();
	mat_t* matfp;
	matfp = Mat_Open(fn, MAT_ACC_RDONLY);
	if (matfp != NULL)
	{
		const char *var_data = ("data");
		matvar_t* matvar_data;
		matvar_data = Mat_VarReadInfo(matfp, var_data); // function reads the information for the variable
		if (matvar_data != NULL)
		{
			const char* fieldname = "hyspec";
			matvar_t* matvar_data_hyspec;
			matvar_data_hyspec = Mat_VarGetStructFieldByName(matvar_data, fieldname, 0);
			if (matvar_data_hyspec != NULL)
			{
				fieldname = "imgcube";
				matvar_t* field_imgcube;
				field_imgcube = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_imgcube != NULL)
				{
					unsigned long field_size = Mat_VarGetSize(field_imgcube);
					if (field_size < this->cubemaxsize && this->ReadOnlyFromHDD == 0)
					{
						try{
							this->SpecHeader.imgcube = static_cast<void*>(new char[field_size]);
						}
						catch (const std::bad_alloc&)
						{
							delete[] this->SpecHeader.imgcube;
							this->ErrorMsgLog(std::string("Warning in SpecIL_MAT::readImageData(): std::bad_alloc -> Working on HDD"));
							this->SpecHeader.type = 2;
							this->FileDataLoaded = 1;
							Mat_VarFree(field_imgcube);
							Mat_VarFree(matvar_data_hyspec);
							Mat_VarFree(matvar_data);
							Mat_Close(matfp);
							return 0;
						};

						// Daten von Datei in den Buffer lesen
						int start_data[3];
						start_data[0] = 0;
						start_data[1] = 0;
						start_data[2] = 0;

						int stride_data[3];
						stride_data[0] = 1;
						stride_data[1] = 1;
						stride_data[2] = 1;

						int edge_data[3];
						edge_data[0] = field_imgcube->dims[0];
						edge_data[1] = field_imgcube->dims[1];
						edge_data[2] = field_imgcube->dims[2];

						Mat_VarReadData(matfp, field_imgcube, this->SpecHeader.imgcube, start_data, stride_data, edge_data);

						this->SpecHeader.type = 1;
						std::cout << "imgcube is loaded into RAM" << std::endl;
					}
					else
					{
						// Cube nicht geladen
						this->SpecHeader.type = 2;
					};

					this->FileDataLoaded = 1;
				};
			};
			Mat_VarFree(matvar_data);
		};
		Mat_Close(matfp);
		return 0;
	};
	//std::cout << "error while reading imgcube" << std::endl;
	this->ErrorMsgLog("In SpecIL_MAT::readImageData(): Error while loading image data");
	return -1;
};
//
int SpecIL_MAT::read()
{
	if (this->FileHeaderLoaded != 1)
	{
		if (this->readFileHeader() != 0)
		{
			this->ErrorMsgLog("In SpecIL_MAT::read(): Failed to read file header!");
			return -1;
		};
	};

	// Anordnung annhemen, wenn keine Information im Header zu finden war
	if (this->SpecHeader.interleave == t_SpecHead::IL_UNKNOWN)
	{
		// Hochstwahrscheinlich BIL
		this->SpecHeader.interleave = t_SpecHead::IL_BIL;
	};

	this->SpecHeader.imgsize[0] = this->hyspec_imgsize[0];
	this->SpecHeader.imgsize[1] = this->hyspec_imgsize[1];
	this->SpecHeader.imgsize[2] = this->hyspec_imgsize[2];

	// Datentyp und Pixelgroesse werden schon in readHeader gesetzt, weil dort besser....

	// Bilddaten oeffnen und lesen
	if (this->FileDataLoaded == 0)
	{
		if (this->readImageData() != 0)
		{
			this->ErrorMsgLog("In SpecIL_MAT::read(): Failed to load .mat image data!");
			return -1;
		};
	};

	return 0;
};
//
int SpecIL_MAT::getPlane(void* plane, int x, int y, int z)
{
	// wurde read() ausgefuehrt ?
	if (this->SpecHeader.type == 0)
	{
		// Err
		this->ErrorMsgLog("In SpecIL_MAT::getPlane(): SpecHeader.type == 0, Data was not read! Run read()!");
		return -1;
	};
	if (this->SpecHeader.type == 1)
	{
		this->SpecIL_Base::getPlane(plane, x, y, z);
		return 0;
	}
	else if (this->SpecHeader.type == 2)
	{
		int array_x[2];
		int array_y[2];
		int array_z[2];

		// Ein Band ausgeben
		if (x < 0 && y < 0 && z < this->SpecHeader.imgsize[1])
		{
			array_x[0] = 0;
			array_x[1] = this->SpecHeader.imgsize[0];

			array_y[0] = 0;
			array_y[1] = this->SpecHeader.imgsize[2];

			this->getPlane_BandHDD(plane, array_x, array_y, z);

			return 0;
		};
		// Einen Frame ausgeben
		if (x < 0 && z < 0 && y < this->SpecHeader.imgsize[2])
		{
			array_x[0] = 0;
			array_x[1] = this->SpecHeader.imgsize[0];

			array_z[0] = 0;
			array_z[1] = this->SpecHeader.imgsize[1];

			this->getPlane_FrameHDD(plane, array_x, y, array_z);
			return 0;
		};
		// Ein Samplebild ausgeben
		if (y < 0 && z < 0 && x < this->SpecHeader.imgsize[0])
		{
			array_y[0] = 0;
			array_y[1] = this->SpecHeader.imgsize[2];

			array_z[0] = 0;
			array_z[1] = this->SpecHeader.imgsize[1];

			this->getPlane_SampleHDD(plane, x, array_y, array_z);
			return 0;
		};
	};
	//Err
	this->ErrorMsgLog("In SpecIL_MAT::getPlane(): invalid parameters");
	return -1;
};
//
int SpecIL_MAT::getPlane(void* plane, int *x, int *y, int *z)
{
	if (this->SpecHeader.type == 0)
	{
		// Err
		this->ErrorMsgLog("In SpecIL_MAT::getPlane(): SpecHeader.type == 0, Data was not read! Run read()!");
		return -1;
	};

	if (this->SpecHeader.type == 1)
	{
		this->SpecIL_Base::getPlane(plane, x, y, z);
		return 0;
	}
	else
	{
		// Ein Bandausschnitt ausgeben
		if (z[1] < 0 && z[0] < this->SpecHeader.imgsize[1] &&
			y[0] >= 0 && y[1] < this->SpecHeader.imgsize[2] &&
			x[0] >= 0 && x[1] < this->SpecHeader.imgsize[0])
		{
			this->getPlane_BandHDD(plane, x, y, z[0]);
			return 0;
		};

		// Frameausschnitt
		if (y[1] < 0 && y[0] < this->SpecHeader.imgsize[2] &&
			x[0] >= 0 && x[1] < this->SpecHeader.imgsize[0] &&
			z[0] >= 0 && z[1] < this->SpecHeader.imgsize[1])
		{
			this->getPlane_FrameHDD(plane, x, y[0], z);
			return 0;
		};

		// Samplebildausschnitt
		if (x[1] < 0 && x[0] < this->SpecHeader.imgsize[0] &&
			z[0] >= 0 && z[1] < this->SpecHeader.imgsize[1] &&
			y[0] >= 0 && y[1] < this->SpecHeader.imgsize[2])
		{
			this->getPlane_SampleHDD(plane, x[0], y, z);
			return 0;
		};
	};
	//Err
	this->ErrorMsgLog("In SpecIL_MAT::getPlane(): invalid parameters");
	return -1;
};
//
int SpecIL_MAT::getPlane_BandHDD(void* plane, int *x, int *y, int z)
{
	const char *fn = this->SpecHeader.filename.c_str();
	mat_t* matfp;
	matfp = Mat_Open(fn, MAT_ACC_RDONLY);
	if (matfp != NULL)
	{
		const char *var_data = ("data");
		matvar_t* matvar_data;
		matvar_data = Mat_VarReadInfo(matfp, var_data);
		if (matvar_data != NULL)
		{
			const char* fieldname = "hyspec";
			matvar_t* matvar_data_hyspec;
			matvar_data_hyspec = Mat_VarGetStructFieldByName(matvar_data, fieldname, 0);
			if (matvar_data_hyspec != NULL)
			{
				fieldname = "imgcube";
				matvar_t* field_imgcube;
				field_imgcube = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_imgcube != NULL)
				{
					unsigned long field_size = Mat_VarGetSize(field_imgcube);
				
					char* BandImgbuff = static_cast<char*>(plane);

					unsigned long long diff_x = (unsigned long long)(x[1] - x[0]);
					unsigned long long diff_y = (unsigned long long)(y[1] - y[0]);

					unsigned long long start_x = (unsigned long long)x[0];
					unsigned long long start_y = (unsigned long long)y[0];

					int start_data[3];
					int stride_data[3];
					int edge_data[3];

					unsigned long long imgsize = diff_x * diff_y * this->SpecHeader.pixelsize;
					char* buffer = new char[this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize];
					if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
					{
						start_data[0] = 0;//x
						start_data[1] = z;//z
						start_data[2] = 0;//y

						stride_data[0] = 1;
						stride_data[1] = field_imgcube->dims[1];
						stride_data[2] = 1;

						edge_data[0] = field_imgcube->dims[0];
						edge_data[1] = 1;
						edge_data[2] = field_imgcube->dims[2];

				//		Mat_VarReadData(matfp, field_imgcube, buffer, start_data, stride_data, edge_data);
						/*// Ausschnitt holen
				//		if (diff_x == this->SpecHeader.imgsize[0] && diff_y == this->SpecHeader.imgsize[2])
						if (true)
						{
							unsigned long long copysize = diff_x * this->SpecHeader.pixelsize;
							unsigned long long pos = (start_x + start_y * this->SpecHeader.imgsize[0])* this->SpecHeader.pixelsize;
							for (unsigned long long j = 0; j < diff_y; j++)
							{
								std::memmove(&BandImgbuff[copysize * j], static_cast<void*>(&buffer[pos]), copysize);
								pos = pos + this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
							};
						}
						else
						{
							std::memmove(plane, static_cast<void*>(buffer), imgsize);
						};*/
					};

					if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
					{
						// Noch nicht getestet, ob das passt

						start_data[0] = 0;//x
						start_data[1] = 0;//y
						start_data[2] = z;//z

						stride_data[0] = 1;
						stride_data[1] = 1;
						stride_data[2] = field_imgcube->dims[2];

						edge_data[0] = field_imgcube->dims[0];
						edge_data[1] = field_imgcube->dims[1];
						edge_data[2] = 1;
					};

					if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
					{
						// Noch nicht getestet, ob das passt

						start_data[0] = z;//z
						start_data[1] = 0;//x
						start_data[2] = 0;//y

						stride_data[0] = field_imgcube->dims[0];
						stride_data[1] = 1;
						stride_data[2] = 1;

						edge_data[0] = 1;
						edge_data[1] = field_imgcube->dims[1];
						edge_data[2] = field_imgcube->dims[2];
					};

					Mat_VarReadData(matfp, field_imgcube, buffer, start_data, stride_data, edge_data);

					// Ausschnitt holen
					if (diff_x == this->SpecHeader.imgsize[0] && diff_y == this->SpecHeader.imgsize[2])
					{
						unsigned long long copysize = diff_x * this->SpecHeader.pixelsize;
						unsigned long long pos = (start_x + start_y * this->SpecHeader.imgsize[0])* this->SpecHeader.pixelsize;
						for (unsigned long long j = 0; j < diff_y; j++)
						{
							std::memmove(&BandImgbuff[copysize * j], static_cast<void*>(&buffer[pos]), copysize);
							pos = pos + this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
						};
					}
					else
					{
						std::memmove(plane, static_cast<void*>(buffer), imgsize);
					};

					delete[] buffer;
				};
			};
			Mat_VarFree(matvar_data);
		};
		Mat_Close(matfp);
		return 0;
	};
	this->ErrorMsgLog("In SpecIL_MAT::getPlane_BandHDD(): Error while reading file");
	return -1;
};
//
int SpecIL_MAT::getPlane_FrameHDD(void* plane, int *x, int y, int *z)
{
	const char *fn = this->SpecHeader.filename.c_str();
	mat_t* matfp;
	matfp = Mat_Open(fn, MAT_ACC_RDONLY);
	if (matfp != NULL)
	{
		const char *var_data = ("data");
		matvar_t* matvar_data;
		matvar_data = Mat_VarReadInfo(matfp, var_data);
		if (matvar_data != NULL)
		{
			const char* fieldname = "hyspec";
			matvar_t* matvar_data_hyspec;
			matvar_data_hyspec = Mat_VarGetStructFieldByName(matvar_data, fieldname, 0);
			if (matvar_data_hyspec != NULL)
			{
				fieldname = "imgcube";
				matvar_t* field_imgcube;
				field_imgcube = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_imgcube != NULL)
				{
					unsigned long field_size = Mat_VarGetSize(field_imgcube);

					char* BandImgbuff = static_cast<char*>(plane);

					unsigned long long diff_x = (unsigned long long)(x[1] - x[0]);
					unsigned long long diff_z = (unsigned long long)(z[1] - z[0]);

					unsigned long long start_x = (unsigned long long)x[0];
					unsigned long long start_z = (unsigned long long)z[0];

					int start_data[3];
					int stride_data[3];
					int edge_data[3];

					unsigned long long imgsize = diff_x * diff_z * this->SpecHeader.pixelsize;
					char* buffer = new char[this->SpecHeader.imgsize[0] * this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize];

					if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
					{
						start_data[0] = 0;//x
						start_data[1] = 0;//z
						start_data[2] = y;//y

						stride_data[0] = 1;
						stride_data[1] = 1;
						stride_data[2] = field_imgcube->dims[2];

						edge_data[0] = field_imgcube->dims[0];
						edge_data[1] = field_imgcube->dims[1];
						edge_data[2] = 1;

					//	Mat_VarReadData(matfp, field_imgcube, buffer, start_data, stride_data, edge_data);
					};

					if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
					{
						// Noch nicht getestet, ob das passt

						start_data[0] = 0;//x
						start_data[1] = y;//y
						start_data[2] = 0;//z

						stride_data[0] = 1;
						stride_data[1] = field_imgcube->dims[1];
						stride_data[2] = 1;

						edge_data[0] = field_imgcube->dims[0];
						edge_data[1] = 1;
						edge_data[2] = field_imgcube->dims[2];
					};

					if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
					{
						// Noch nicht getestet, ob das passt

						start_data[0] = 0;//z
						start_data[1] = 0;//x
						start_data[2] = y;//y

						stride_data[0] = 1;
						stride_data[1] = 1;
						stride_data[2] = field_imgcube->dims[2];

						edge_data[0] = field_imgcube->dims[0];
						edge_data[1] = field_imgcube->dims[1];
						edge_data[2] = 1;
					};

					Mat_VarReadData(matfp, field_imgcube, buffer, start_data, stride_data, edge_data);

					// Ausschnitt holen
					if (diff_x == this->SpecHeader.imgsize[0] && diff_z == this->SpecHeader.imgsize[1])
					{
						unsigned long long pos = (start_x + start_z *this->SpecHeader.imgsize[0])* this->SpecHeader.pixelsize;
						unsigned long long copysize = diff_x * this->SpecHeader.pixelsize;

						for (unsigned long long j = 0; j < diff_z; j++)
						{
							std::memmove(&BandImgbuff[copysize * j], static_cast<void*>(&buffer[pos]), copysize);
							pos = pos + this->SpecHeader.imgsize[0] * this->SpecHeader.pixelsize;
						};
					}
					else
					{
						std::memmove(plane, static_cast<void*>(buffer), imgsize);
					};

					delete[] buffer;
				};
			};
			Mat_VarFree(matvar_data);
		};
		Mat_Close(matfp);
		return 0;
	};
	this->ErrorMsgLog("In SpecIL_MAT::getPlane_FrameHDD(): Error while reading file");
	return -1;
};
//
int SpecIL_MAT::getPlane_SampleHDD(void* plane, int x, int *y, int *z)
{
	const char *fn = this->SpecHeader.filename.c_str();
	mat_t* matfp;
	matfp = Mat_Open(fn, MAT_ACC_RDONLY);
	if (matfp != NULL)
	{
		const char *var_data = ("data");
		matvar_t* matvar_data;
		matvar_data = Mat_VarReadInfo(matfp, var_data);
		if (matvar_data != NULL)
		{
			const char* fieldname = "hyspec";
			matvar_t* matvar_data_hyspec;
			matvar_data_hyspec = Mat_VarGetStructFieldByName(matvar_data, fieldname, 0);
			if (matvar_data_hyspec != NULL)
			{
				fieldname = "imgcube";
				matvar_t* field_imgcube;
				field_imgcube = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_imgcube != NULL)
				{
					unsigned long field_size = Mat_VarGetSize(field_imgcube);

					char* BandImgbuff = static_cast<char*>(plane);

					unsigned long long diff_y = (unsigned long long)(y[1] - y[0]);
					unsigned long long diff_z = (unsigned long long)(z[1] - z[0]);

					unsigned long long start_y = (unsigned long long)y[0];
					unsigned long long start_z = (unsigned long long)z[0];

					int start_data[3];
					int stride_data[3];
					int edge_data[3];

					unsigned long long imgsize = diff_y * diff_z * this->SpecHeader.pixelsize;
					char* buffer = new char[this->SpecHeader.imgsize[1] * this->SpecHeader.imgsize[2] * this->SpecHeader.pixelsize];

					if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
					{
						start_data[0] = x;//x
						start_data[1] = 0;//z
						start_data[2] = 0;//y

						stride_data[0] = field_imgcube->dims[0];
						stride_data[1] = 1;
						stride_data[2] = 1;

						edge_data[0] = 1;
						edge_data[1] = field_imgcube->dims[1];
						edge_data[2] = field_imgcube->dims[2];
					};

					if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
					{
						// Noch nicht getestet, ob das passt

						start_data[0] = x;//x
						start_data[1] = 0;//y
						start_data[2] = 0;//z

						stride_data[0] = field_imgcube->dims[0];
						stride_data[1] = 1;
						stride_data[2] = 1;

						edge_data[0] = 1;
						edge_data[1] = field_imgcube->dims[1];
						edge_data[2] = field_imgcube->dims[2];
					};

					if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
					{
						// Noch nicht getestet, ob das passt

						start_data[0] = 0;//z
						start_data[1] = x;//x
						start_data[2] = 0;//y

						stride_data[0] = 1;
						stride_data[1] = field_imgcube->dims[1];
						stride_data[2] = 1;

						edge_data[0] = field_imgcube->dims[0];
						edge_data[1] = 1;
						edge_data[2] = field_imgcube->dims[2];
					};

					Mat_VarReadData(matfp, field_imgcube, buffer, start_data, stride_data, edge_data);

					// Ausschnitt holen
					if (diff_y == this->SpecHeader.imgsize[2] && diff_z == this->SpecHeader.imgsize[1])
					{
						unsigned long long pos = (start_z + start_y *this->SpecHeader.imgsize[1])* this->SpecHeader.pixelsize;
						unsigned long long copysize = diff_z * this->SpecHeader.pixelsize;
						for (unsigned long long j = 0; j < diff_y; j++)
						{
							std::memmove(&BandImgbuff[copysize * j], static_cast<void*>(&buffer[pos]), copysize);
							pos = pos + this->SpecHeader.imgsize[1] * this->SpecHeader.pixelsize;
						};
					}
					else
					{
						std::memmove(plane, static_cast<void*>(buffer), imgsize);
					};

					delete[] buffer;
				};
			};
			Mat_VarFree(matvar_data);
		};
		Mat_Close(matfp);
		return 0;
	};
	this->ErrorMsgLog("In SpecIL_MAT::getPlane_SampleHDD(): Error while reading file");
	return -1;
};
//
int SpecIL_MAT::getPoint(void* point, int x, int y, int z)
{
	if (this->SpecHeader.type == 0)
	{
		this->ErrorMsgLog("In SpecIL_MAT::getPoint(): SpecHeader.type == 0, Data was not read! Run read()!");
		return -1;
	};
	if (this->SpecHeader.type == 1)
	{
		this->SpecIL_Base::getPoint(point, x, y, z);
		return 0;
	};
	if (this->SpecHeader.type == 2)
	{
		char* Point = static_cast< char* >(point);
		const char *fn = this->SpecHeader.filename.c_str();
		mat_t* matfp;
		matfp = Mat_Open(fn, MAT_ACC_RDONLY);
		if (matfp != NULL)
		{
			const char *var_data = ("data");
			matvar_t* matvar_data;
			matvar_data = Mat_VarReadInfo(matfp, var_data);
			if (matvar_data != NULL)
			{
				const char* fieldname = "hyspec";
				matvar_t* matvar_data_hyspec;
				matvar_data_hyspec = Mat_VarGetStructFieldByName(matvar_data, fieldname, 0);
				if (matvar_data_hyspec != NULL)
				{
					fieldname = "imgcube";
					matvar_t* field_imgcube;
					field_imgcube = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
					if (field_imgcube != NULL)
					{
						unsigned long field_size = Mat_VarGetSize(field_imgcube);

						int start_data[3];
						int stride_data[3];
						int edge_data[3];

						if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
						{
							start_data[0] = x;//x
							start_data[1] = z;//z
							start_data[2] = y;//y

							stride_data[0] = field_imgcube->dims[0];
							stride_data[1] = field_imgcube->dims[1];
							stride_data[2] = field_imgcube->dims[2];

							edge_data[0] = 1;
							edge_data[1] = 1;
							edge_data[2] = 1;

						//	Mat_VarReadData(matfp, field_imgcube, point, start_data, stride_data, edge_data);
						};

						if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
						{
							// Noch nicht getestet, ob das passt

							start_data[0] = x;//x
							start_data[1] = y;//y
							start_data[2] = z;//z

							stride_data[0] = field_imgcube->dims[0];
							stride_data[1] = field_imgcube->dims[1];
							stride_data[2] = field_imgcube->dims[2];

							edge_data[0] = 1;
							edge_data[1] = 1;
							edge_data[2] = 1;
						};

						if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
						{
							// Noch nicht getestet, ob das passt

							start_data[0] = z;//z
							start_data[1] = x;//x
							start_data[2] = y;//y

							stride_data[0] = field_imgcube->dims[0];
							stride_data[1] = field_imgcube->dims[1];
							stride_data[2] = field_imgcube->dims[2];

							edge_data[0] = 1;
							edge_data[1] = 1;
							edge_data[2] = 1;
						};

						Mat_VarReadData(matfp, field_imgcube, point, start_data, stride_data, edge_data);
					};
				};
				Mat_VarFree(matvar_data);
			};
			Mat_Close(matfp);
			return 0;
		};
		this->ErrorMsgLog("In SpecIL_MAT::getPoint(): Error while loading image data");
		return -1;
	};
	//Err
	this->ErrorMsgLog("In SpecIL_MAT::getPoint(): invalid parameter");
	return -1;
};
//
int SpecIL_MAT::getVector(void* vector, int x, int y, int z)
{
	if (this->SpecHeader.type == 0)
	{
		this->ErrorMsgLog("In SpecIL_MAT::getVector(): SpecHeader.type == 0, Data was not read! Run read()!");
		return -1;
	};
	if (this->SpecHeader.type == 1)
	{
		this->SpecIL_Base::getVector(vector, x, y, z);
		return 0;
	};
	if (this->SpecHeader.type == 2)
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
	};
	this->ErrorMsgLog("In SpecIL_MAT::getVector(): invalid parameters x, y, z, interleave or type");
	return -1;
};
//
int SpecIL_MAT::getVector_X(void* vector, int y, int z)
{
	const char *fn = this->SpecHeader.filename.c_str();
	mat_t* matfp;
	matfp = Mat_Open(fn, MAT_ACC_RDONLY);
	if (matfp != NULL)
	{
		const char *var_data = ("data");
		matvar_t* matvar_data;
		matvar_data = Mat_VarReadInfo(matfp, var_data);
		if (matvar_data != NULL)
		{
			const char* fieldname = "hyspec";
			matvar_t* matvar_data_hyspec;
			matvar_data_hyspec = Mat_VarGetStructFieldByName(matvar_data, fieldname, 0);
			if (matvar_data_hyspec != NULL)
			{
				fieldname = "imgcube";
				matvar_t* field_imgcube;
				field_imgcube = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_imgcube != NULL)
				{
					unsigned long field_size = Mat_VarGetSize(field_imgcube);

					int start_data[3];
					int stride_data[3];
					int edge_data[3];

					if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
					{
						start_data[0] = 0;//x
						start_data[1] = z;//z
						start_data[2] = y;//y

						stride_data[0] = 1;
						stride_data[1] = field_imgcube->dims[1];
						stride_data[2] = field_imgcube->dims[2];

						edge_data[0] = field_imgcube->dims[0];
						edge_data[1] = 1;
						edge_data[2] = 1;
					};

					if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
					{
						// Noch nicht getestet, ob das passt

						start_data[0] = 0;//x
						start_data[1] = y;//y
						start_data[2] = z;//z

						stride_data[0] = 1;
						stride_data[1] = field_imgcube->dims[1];
						stride_data[2] = field_imgcube->dims[2];

						edge_data[0] = field_imgcube->dims[0];
						edge_data[1] = 1;
						edge_data[2] = 1;
					};

					if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
					{
						// Noch nicht getestet, ob das passt

						start_data[0] = z;//z
						start_data[1] = 0;//x
						start_data[2] = z;//y

						stride_data[0] = field_imgcube->dims[0];
						stride_data[1] = 1;
						stride_data[2] = field_imgcube->dims[2];

						edge_data[0] = 1;
						edge_data[1] = field_imgcube->dims[1];
						edge_data[2] = 1;
					};

					Mat_VarReadData(matfp, field_imgcube, vector, start_data, stride_data, edge_data);
				};
			};
			Mat_VarFree(matvar_data);
		};
		Mat_Close(matfp);
		return 0;
	};
	this->ErrorMsgLog("In SpecIL_MAT::getVector_X(): invalid parameters");
	return -1;
};
//
int SpecIL_MAT::getVector_Y(void* vector, int x, int z)
{
	const char *fn = this->SpecHeader.filename.c_str();
	mat_t* matfp;
	matfp = Mat_Open(fn, MAT_ACC_RDONLY);
	if (matfp != NULL)
	{
		const char *var_data = ("data");
		matvar_t* matvar_data;
		matvar_data = Mat_VarReadInfo(matfp, var_data);
		if (matvar_data != NULL)
		{
			const char* fieldname = "hyspec";
			matvar_t* matvar_data_hyspec;
			matvar_data_hyspec = Mat_VarGetStructFieldByName(matvar_data, fieldname, 0);
			if (matvar_data_hyspec != NULL)
			{
				fieldname = "imgcube";
				matvar_t* field_imgcube;
				field_imgcube = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_imgcube != NULL)
				{
					unsigned long field_size = Mat_VarGetSize(field_imgcube);

					int start_data[3];
					int stride_data[3];
					int edge_data[3];

					if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
					{
						start_data[0] = x;//x
						start_data[1] = z;//z
						start_data[2] = 0;//y

						stride_data[0] = field_imgcube->dims[0];
						stride_data[1] = field_imgcube->dims[1];
						stride_data[2] = 1;

						edge_data[0] = 1;
						edge_data[1] = 1;
						edge_data[2] = field_imgcube->dims[2];
					};

					if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
					{
						// Noch nicht getestet, ob das passt

						start_data[0] = x;//x
						start_data[1] = 0;//y
						start_data[2] = z;//z

						stride_data[0] = field_imgcube->dims[0];
						stride_data[1] = 1;
						stride_data[2] = field_imgcube->dims[2];

						edge_data[0] = 1;
						edge_data[1] = 1;
						edge_data[2] = field_imgcube->dims[2];
					};

					if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
					{
						// Noch nicht getestet, ob das passt

						start_data[0] = z;//z
						start_data[1] = x;//x
						start_data[2] = 0;//y

						stride_data[0] = field_imgcube->dims[0];
						stride_data[1] = field_imgcube->dims[1];
						stride_data[2] = 1;

						edge_data[0] = 1;
						edge_data[1] = 1;
						edge_data[2] = field_imgcube->dims[2];
					};

					Mat_VarReadData(matfp, field_imgcube, vector, start_data, stride_data, edge_data);
				};
			};
			Mat_VarFree(matvar_data);
		};
		Mat_Close(matfp);
		return 0;
	};
	this->ErrorMsgLog("In SpecIL_MAT::getVector_Y(): invalid parameters");
	return -1;
};
//
int SpecIL_MAT::getVector_Z(void* vector, int x, int y)
{
	const char *fn = this->SpecHeader.filename.c_str();
	mat_t* matfp;
	matfp = Mat_Open(fn, MAT_ACC_RDONLY);
	if (matfp != NULL)
	{
		const char *var_data = ("data");
		matvar_t* matvar_data;
		matvar_data = Mat_VarReadInfo(matfp, var_data);
		if (matvar_data != NULL)
		{
			const char* fieldname = "hyspec";
			matvar_t* matvar_data_hyspec;
			matvar_data_hyspec = Mat_VarGetStructFieldByName(matvar_data, fieldname, 0);
			if (matvar_data_hyspec != NULL)
			{
				fieldname = "imgcube";
				matvar_t* field_imgcube;
				field_imgcube = Mat_VarGetStructFieldByName(matvar_data_hyspec, fieldname, 0);
				if (field_imgcube != NULL)
				{
					unsigned long field_size = Mat_VarGetSize(field_imgcube);

					int start_data[3];
					int stride_data[3];
					int edge_data[3];

					if (this->SpecHeader.interleave == t_SpecHead::IL_BIL)
					{
						start_data[0] = x;//x
						start_data[1] = 0;//z
						start_data[2] = y;//y

						stride_data[0] = field_imgcube->dims[0];
						stride_data[1] = 1;
						stride_data[2] = field_imgcube->dims[2];

						edge_data[0] = 1;
						edge_data[1] = field_imgcube->dims[1];
						edge_data[2] = 1;
					};

					if (this->SpecHeader.interleave == t_SpecHead::IL_BSQ)
					{
						// Noch nicht getestet, ob das passt

						start_data[0] = x;//x
						start_data[1] = y;//y
						start_data[2] = 0;//z

						stride_data[0] = field_imgcube->dims[0];
						stride_data[1] = field_imgcube->dims[1];
						stride_data[2] = 1;

						edge_data[0] = 1;
						edge_data[1] = 1;
						edge_data[2] = field_imgcube->dims[2];
					};

					if (this->SpecHeader.interleave == t_SpecHead::IL_BIP)
					{
						// Noch nicht getestet, ob das passt

						start_data[0] = 0;//z
						start_data[1] = x;//x
						start_data[2] = y;//y

						stride_data[0] = 1;
						stride_data[1] = field_imgcube->dims[1];
						stride_data[2] = field_imgcube->dims[2];

						edge_data[0] = field_imgcube->dims[0];
						edge_data[1] = 1;
						edge_data[2] = 1;
					};

					Mat_VarReadData(matfp, field_imgcube, vector, start_data, stride_data, edge_data);
				};
			};
			Mat_VarFree(matvar_data);
		};
		Mat_Close(matfp);
		return 0;
	};
	this->ErrorMsgLog("In SpecIL_MAT::getVector_Y(): invalid parameters");
	return -1;
};