#ifndef GEOCONVERTER_H
#define GEOCONVERTER_H


#define _USE_MATH_DEFINES

#//include <cmath>			//2010-08-11: was <math.h>	
#include <cstdio>			//2010-08-11: was <stdio.h>	  
#include <cstdlib>			//2010-08-11: was <stdlib.h>  
#include <cstring>			//2010-08-11: was <string.h>  
#include <cctype>			//2010-08-11: was <ctype.h>  
#include <iostream>			//2010-08-11: was <iostream.h>
#include <iomanip>			//2010-08-11: was <iomanip.h> ,

class Geoconverter 
{

public:
	Geoconverter();
	~Geoconverter();

	void Prt(int Fmt);
	void DatumConvert(int dIn, double LatIn, double LongIn, double HtIn, int dTo, double& LatTo, double& LongTo, double& HtTo);
	void LLtoUTM(int eId, double Lat, double Long, double& Northing, double& Easting, int& Zone);
	void UTMtoLL(int eId, double Northing, double Easting, int Zone, double& Lat, double& Long);

};


// LatLong-UTM.c++
// Conversions:  LatLong to UTM;  and UTM to LatLong;
// by Eugene Reimer, ereimer@shaw.ca, 2002-December;
// with LLtoUTM & UTMtoLL routines based on those by Chuck Gantz chuck.gantz@globalstar.com;
// with ellipsoid & datum constants from Peter H Dana website (http://www.colorado.edu/geography/gcraft/notes/datum/edlist.html);
//
// Usage:  see the Usage() routine below;
//
// Copyright © 1995,2002,2010 Eugene Reimer, Peter Dana, Chuck Gantz.  Released under the GPL;  see http://www.gnu.org/licenses/gpl.html
// (Peter Dana's non-commercial clause precludes using the LGPL)

using namespace std;			//2010-08-11: added
#define M_PI_CUSTOM (3.14159265358979323846)
const double deg2rad = M_PI_CUSTOM / 180;
const double rad2deg = 180 / M_PI_CUSTOM;
const double k0 = 0.9996;

class Ellipsoid{
public:
	Ellipsoid(){};
	Ellipsoid(int id, char* name, double radius, double fr){
		Name = name;  EquatorialRadius = radius;  eccSquared = 2 / fr - 1 / (fr*fr);
	}
	char* Name;
	double EquatorialRadius;
	double eccSquared;
};
static Ellipsoid ellip[] = {		//converted from PeterDana website, by Eugene Reimer 2002dec
	//		 eId,  Name,		   EquatorialRadius,    1/flattening;
	Ellipsoid(0, "Airy1830", 6377563.396, 299.3249646),
	Ellipsoid(1, "AiryModified", 6377340.189, 299.3249646),
	Ellipsoid(2, "AustralianNational", 6378160, 298.25),
	Ellipsoid(3, "Bessel1841Namibia", 6377483.865, 299.1528128),
	Ellipsoid(4, "Bessel1841", 6377397.155, 299.1528128),
	Ellipsoid(5, "Clarke1866", 6378206.4, 294.9786982),
	Ellipsoid(6, "Clarke1880", 6378249.145, 293.465),
	Ellipsoid(7, "EverestIndia1830", 6377276.345, 300.8017),
	Ellipsoid(8, "EverestSabahSarawak", 6377298.556, 300.8017),
	Ellipsoid(9, "EverestIndia1956", 6377301.243, 300.8017),
	Ellipsoid(10, "EverestMalaysia1969", 6377295.664, 300.8017),	//Dana has no datum that uses this ellipsoid!
	Ellipsoid(11, "EverestMalay_Sing", 6377304.063, 300.8017),
	Ellipsoid(12, "EverestPakistan", 6377309.613, 300.8017),
	Ellipsoid(13, "Fischer1960Modified", 6378155, 298.3),
	Ellipsoid(14, "Helmert1906", 6378200, 298.3),
	Ellipsoid(15, "Hough1960", 6378270, 297),
	Ellipsoid(16, "Indonesian1974", 6378160, 298.247),
	Ellipsoid(17, "International1924", 6378388, 297),
	Ellipsoid(18, "Krassovsky1940", 6378245, 298.3),
	Ellipsoid(19, "GRS80", 6378137, 298.257222101),
	Ellipsoid(20, "SouthAmerican1969", 6378160, 298.25),
	Ellipsoid(21, "WGS72", 6378135, 298.26),
	Ellipsoid(22, "WGS84", 6378137, 298.257223563)
};


#define	eClarke1866	5		//names for ellipsoidId's
#define	eGRS80		19
#define	eWGS72		21
#define	eWGS84		22

class Datum{
public:
	Datum(){};
	Datum(int id, char* name, int eid, double dx, double dy, double dz){
		Name = name;  eId = eid;  dX = dx;  dY = dy;  dZ = dz;
	}
	char* Name;
	int   eId;
	double dX;
	double dY;
	double dZ;
};
static Datum datum[] = {		//converted from PeterDana website, by Eugene Reimer 2002dec
	//	      Id,  Name,			eId,		dX,	dY,	dZ;	//when & where this datum is applicable
	Datum(0, "NAD27_AK", eClarke1866, -5, 135, 172),	//NAD27 for Alaska Excluding Aleutians
	Datum(1, "NAD27_AK_AleutiansE", eClarke1866, -2, 152, 149),	//NAD27 for Aleutians East of 180W
	Datum(2, "NAD27_AK_AleutiansW", eClarke1866, 2, 204, 105),	//NAD27 for Aleutians West of 180W
	Datum(3, "NAD27_Bahamas", eClarke1866, -4, 154, 178),	//NAD27 for Bahamas Except SanSalvadorIsland
	Datum(4, "NAD27_Bahamas_SanSalv", eClarke1866, 1, 140, 165),	//NAD27 for Bahamas SanSalvadorIsland
	Datum(5, "NAD27_AB_BC", eClarke1866, -7, 162, 188),	//NAD27 for Canada Alberta BritishColumbia
	Datum(6, "NAD27_MB_ON", eClarke1866, -9, 157, 184),	//NAD27 for Canada Manitoba Ontario
	Datum(7, "NAD27_NB_NL_NS_QC", eClarke1866, -22, 160, 190),	//NAD27 for Canada NewBrunswick Newfoundland NovaScotia Quebec
	Datum(8, "NAD27_NT_SK", eClarke1866, 4, 159, 188),	//NAD27 for Canada NorthwestTerritories Saskatchewan
	Datum(9, "NAD27_YT", eClarke1866, -7, 139, 181),	//NAD27 for Canada Yukon
	Datum(10, "NAD27_CanalZone", eClarke1866, 0, 125, 201),	//NAD27 for CanalZone (ER: is that Panama??)
	Datum(11, "NAD27_Cuba", eClarke1866, -9, 152, 178),	//NAD27 for Cuba
	Datum(12, "NAD27_Greenland", eClarke1866, 11, 114, 195),	//NAD27 for Greenland (HayesPeninsula)
	Datum(13, "NAD27_Carribean", eClarke1866, -3, 142, 183),	//NAD27 for Antigua Barbados Barbuda Caicos Cuba DominicanRep GrandCayman Jamaica Turks
	Datum(14, "NAD27_CtrlAmerica", eClarke1866, 0, 125, 194),	//NAD27 for Belize CostaRica ElSalvador Guatemala Honduras Nicaragua
	Datum(15, "NAD27_Canada", eClarke1866, -10, 158, 187),	//NAD27 for Canada
	Datum(16, "NAD27_ConUS", eClarke1866, -8, 160, 176),	//NAD27 for CONUS
	Datum(17, "NAD27_ConUS_East", eClarke1866, -9, 161, 179),	//NAD27 for CONUS East of Mississippi Including Louisiana Missouri Minnesota
	Datum(18, "NAD27_ConUS_West", eClarke1866, -8, 159, 175),	//NAD27 for CONUS West of Mississippi Excluding Louisiana Missouri Minnesota
	Datum(19, "NAD27_Mexico", eClarke1866, -12, 130, 190),	//NAD27 for Mexico
	Datum(20, "NAD83_AK", eGRS80, 0, 0, 0),	//NAD83 for Alaska Excluding Aleutians
	Datum(21, "NAD83_AK_Aleutians", eGRS80, -2, 0, 4),	//NAD83 for Aleutians
	Datum(22, "NAD83_Canada", eGRS80, 0, 0, 0),	//NAD83 for Canada
	Datum(23, "NAD83_ConUS", eGRS80, 0, 0, 0),	//NAD83 for CONUS
	Datum(24, "NAD83_Hawaii", eGRS80, 1, 1, -1),	//NAD83 for Hawaii
	Datum(25, "NAD83_Mexico_CtrlAmerica", eGRS80, 0, 0, 0),	//NAD83 for Mexico CentralAmerica
	Datum(26, "WGS72", eWGS72, 0, 0, 0),	//WGS72 for world
	Datum(27, "WGS84", eWGS84, 0, 0, 0)	//WGS84 for world
};
#define	dNAD27_MB_ON	6		//names for datumId's
#define	dNAD27_Canada	15
#define	dNAD83_Canada	22
#define	dNAD83_ConUS	23
#define	dWGS84		27


#endif // GEOCONVERTER_H
