#include "geoconverter.h"

int Z, Fmt, K; double E, N, Lat, Long;		// global vars for Prt routine
#define fUT4	1							// for Fmt: UTM-4wd-style
#define fLLD	2							// for Fmt: LL-degrees-N|S-E|W
#define fLLDM	4							// for Fmt: LL-degrees:minutes-N|S-E|W
#define fLLDMS	8							// for Fmt: LL-degrees:minutes:seconds-N|S-E|W
#define fUTs	16							// for Fmt: UTM-signed
#define fLLs	32							// for Fmt: LL-degrees-signed
#define fUT3	64							// for Fmt: UTM-3wd-style
#define nbr	atof							// atof: ascii-to-number
#define Nbr	strtod
double  nbN(char*a){ return strchr("Ss", *a) ? atof(a + 1) - 10000000 : strchr("Nn", *a) ? atof(a + 1) : atof(a); }				//Northing
double  nbL(char*a){														//lat|long: [N|E|S|W]d[:m[:s]][N|E|S|W]
	char*p; double R = Nbr(a + !!isalpha(*a), &p); if (*p == ':')R += Nbr(p + 1, &p) / 60; if (*p == ':')R += Nbr(p + 1, &p) / 3600;
	return strchr("SsWw", *a) || (*p&&strchr("SsWw", *p)) ? -R : R;
}
void prtDM(double D){ double M = (D - int(D)) * 60; cout << setprecision(3) << int(D) << ":" << M; }
void prtDMS(double D){ double M = (D - int(D)) * 60; cout << setprecision(1) << int(D) << ":" << int(M) << ":" << (M - int(M)) * 60; }

void ps() { if (K++)cout << " == "; }

/*
void test(int eId, double pLat, double pLong){
Lat = pLat; Long = pLong;
cout << "\nEllipsoid:" << ellip[eId].Name;	cout << "\nStarting Lat,Long position:              "; Prt(fLLs);
LLtoUTM(eId, Lat, Long, N, E, Z);		cout << "\nConverted to UTM-Zone,Easting,Northing:  "; Prt(fUTs);
UTMtoLL(eId, N, E, Z, Lat, Long);		cout << "\nConverted back to Lat,Long:              "; Prt(fLLs);
cout << "\n";
}
void testD(int dIn, double LatIn, double LongIn, double HtIn, int dTo){
cout << "\nDatum:" << datum[dIn].Name << " Ellipsoid:" << ellip[datum[dIn].eId].Name << " To-Datum:" << datum[dTo].Name << " To-Ellipsoid:" << ellip[datum[dTo].eId].Name;
cout << setprecision(9);							//note: Ht (in metres) needs 5-digits less precision than Lat,Long do
double LatTo, LongTo, HtTo;					cout << "\nIN: datum:" << datum[dIn].Name << "\tLat:" << LatIn << " Long:" << LongIn << " Ht:" << HtIn;
DatumConvert(dIn, LatIn, LongIn, HtIn, dTo, LatTo, LongTo, HtTo);	cout << "\nTO: datum:" << datum[dTo].Name << "\tLat:" << LatTo << " Long:" << LongTo << " Ht:" << HtTo;
DatumConvert(dTo, LatTo, LongTo, HtTo, dIn, LatIn, LongIn, HtIn);	cout << "\nTO: datum:" << datum[dIn].Name << "\tLat:" << LatIn << " Long:" << LongIn << " Ht:" << HtIn;
cout << "\n";
}
void Testcases(){
test(eWGS84, 47 + 22.690 / 60, 8 + 13.950 / 60);					//WGS-84,     47:22.690N   8:13.950E    == ChuckGantz-eg  (Swiss Grid: 659879/247637)
test(eWGS84, 30 + 16. / 60 + 28.82 / 3600, -(97 + 44. / 60 + 25.19 / 3600));		//WGS-84,     30:16:28.82N 97:44:25.19W == PeterDana-eg1
test(eClarke1866, 30 + 16. / 60 + 28.03 / 3600, -(97 + 44. / 60 + 24.09 / 3600));		//Clarke1866, 30:16:28.03N 97:44:24.09W == PeterDana-eg2;  recall NAD27 uses Clarke1866
test(eClarke1866, 51.5, -101.5);						//Clarke1866, 51:30N 101:30W == SE-corner of topo-map:62N12
testD(dWGS84, 30 + 16. / 60 + 28.82 / 3600, -(97 + 44. / 60 + 25.19 / 3600), 0, dWGS84);	//test DatumConvert on Dana-eg1 to itself (to see X,Y,Z)
testD(dNAD27_MB_ON, 51.5, -101.5, 0, dNAD83_Canada);			//test DatumConvert on SE-corner of topo-map:62N12;  FROM: dNAD27_Canada | dNAD27_MB_ON
}
void Usage(){
cout << "Usage:";
cout << "\n	LatLong-UTM  [--Outputformat]  Latitude[N|S]  Longitude[E|W]";
cout << "\n	LatLong-UTM  [--Outputformat]  Zone  Easting  Northing";
cout << "\n	LatLong-UTM  [--Outputformat]  Zone  N|S  Easting  Northing";
cout << "\n	LatLong-UTM  [--Outputformat]";
cout << "\nreads from standard-input when no coordinates given on cmdline, where each line is one of:";
cout << "\n	Latitude[N|S]  Longitude[E|W]";
cout << "\n	Zone  Easting  Northing";
cout << "\n	Zone  N|S  Easting  Northing";
cout << "\nLatitude and Longitude are in degrees or degrees:minutes or degrees:minutes:seconds with north and east positive, S and W are alternate minus-signs;";
cout << "\nZone is an integer 1..60;  Easting in metres with origin for zone#N at 500,000m west of longitude N*6-183°;  northing is metres from equator with north positive;";
cout << "\nin the 3-word style, Northing is northing or the letter S followed by northing-plus-ten-million;";
cout << "\nin the 4-word style when 2nd word is S, Northing is northing-plus-ten-million;";
cout << "\nin the signed style, Northing is northing (and sanity prevails, unfortunately that style is not widely used);";
cout << "\nOutputformat is an integer, the sum of one or more of: 1 for UTM-4-word, 2 for LL-degrees, 4 for LL-degrees:minutes, 8 for LL-degrees:minutes:seconds,";
cout << "\n	16 for UTM-signed, 32 for LL-signed, 64 for UTM-3-word;  the default for Outputformat is 7 (which is UTM + LL-degrees + LL-degrees:minutes);";
cout << "\nan input-file can have comments, from '#' to end-of-line, and such comments as well as empty-lines will be echoed to the output;";
cout << "\nno datum conversion is provided, the WGS84 datum is used throughout (WGS84 is identical to GRS80 aka NAD83 to 8 significant digits);";
cout << "\nEXAMPLES:";
cout << "\n	LatLong-UTM  50.26     -96		-- convert Latitude:50.26 Longitude:-96 to UTM";
cout << "\n	LatLong-UTM  50:15.6   -96		-- same as preceding";
cout << "\n	LatLong-UTM  50:15:36  -96		-- same as preceding";
cout << "\n	LatLong-UTM  50:15:36N  96W		-- same as preceding";
cout << "\n	LatLong-UTM  N50:15:36  W96		-- same as preceding";
cout << "\n	LatLong-UTM  -25.0  18.13		-- convert Latitude:-25.0 Longitude:18.13 to UTM";
cout << "\n	LatLong-UTM  14 501000 5678901		-- convert Zone:14 Easting:501000 Northing:5678901 to LatLong";
cout << "\n	LatLong-UTM  14 501000 -5666777		-- convert Zone:14 Easting:501000 Northing:-5666777 to LatLong";
cout << "\n	LatLong-UTM  14 501000 S4333223		-- same as preceding;  Northing as S followed by Northing-plus-ten-million";
cout << "\n	LatLong-UTM  14 S 501000 4333223	-- same as preceding, in the 4-word style";
cout << "\n	LatLong-UTM  --48  <trailpoints-utm.txt	-- convert each line of trailpoints-utm.txt, with Outputformat: UTM-signed + LL-signed";
cout << "\n";
}
*/

/*
int main(int argc, char**argv){							//2010-08-11: was void main(...
char buf[256]; char*p; int L,ac; char*av[129];				//vars for reading stdin
cout<<setiosflags(ios::fixed);						//decided against including ios::showpoint
Fmt=fUT4|fLLD|fLLDM;								//default for Fmt, if not specified by input
--argc; ++argv;								//remove spurious first element of argv array
while(argc && memcmp(argv[0],"--",2)==0){					//handle leading options: --Outputformat, --test, --help
if     (isdigit(argv[0][2]))		Fmt=atoi(argv[0]+2);		//for --<DIGIT>, parse Outputformat into Fmt
else if(strcmp(argv[0],"--test")==0)	{Testcases(); return 0;}	//for --test, run testcases & exit
else					{Usage(); return 0;}		//for --help, show Usage & exit
--argc; ++argv;
}
if(argc==0)  while(cin.getline(buf,256), cin.good()){			//0 args, read stdin converting each line
p=buf; ac=0;
while(1){ while(*p&&strchr(" \t",*p))++p; if(*p==0||*p=='#')break; av[ac++]=p; while(*p&&!strchr(" \t#",*p))++p;}	//break line into whitespace-separated words
if(ac>=2&&ac<=4) CvtLine(ac,av,p);					//line with 2|3|4 words, convert and print
else if(ac==0)   cout<<buf<<"\n";						//line with no words, echo the line (comments)
else             cout<<"==invalid number-of-words: "<<buf<<"\n";		//anything else is invalid, produce errmsg
}
else if(argc>=2&&argc<=4)	CvtLine(argc,argv,"");				//2|3|4 args, convert and print
else				Usage();					//argc other than 0|2|3 is invalid, show Usage
return 0;									//2010-08-11: added when void became illegal
}
*/

Geoconverter::Geoconverter()
{
	/*
	double Lat;
	double Long;
	UTMtoLL(eWGS84, 5451197, 430979, 32, Lat, Long);

	cout << Lat << " " << Long << endl;

	double N;
	double E;
	int Z;
	LLtoUTM(eWGS84, 49.209678, 8.052354, N, E, Z);

	cout << N << " " << E << " " << Z << endl;
	*/
}

Geoconverter::~Geoconverter()
{

}


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

void Geoconverter::Prt(int Fmt)
{														//Prt: print according to Fmt bits
	K = 0;
	if (Fmt&fLLs)  { ps(); cout << setprecision(9) << Lat << " " << Long; }	//LL degrees signed  
	if (Fmt&fLLD)  { ps(); char NS = (Lat<0 ? 'S' : 'N'), EW = (Long<0 ? 'W' : 'E'); cout << setprecision(5) << abs(Lat) << NS << " " << abs(Long) << EW; }	//LL degrees N|S E|W 
	if (Fmt&fLLDM) { ps(); char NS = (Lat<0 ? 'S' : 'N'), EW = (Long<0 ? 'W' : 'E'); prtDM(abs(Lat)); cout << NS << " "; prtDM(abs(Long)); cout << EW; }	//LL  d:m    N|S E|W 
	if (Fmt&fLLDMS){ ps(); char NS = (Lat<0 ? 'S' : 'N'), EW = (Long<0 ? 'W' : 'E'); prtDMS(abs(Lat)); cout << NS << " "; prtDMS(abs(Long)); cout << EW; }	//LL  d:m:s  N|S E|W 
	if (Fmt&fUTs)  { ps(); cout << setprecision(3) << Z << " " << E << " " << N; }	//UTM signed          
	if (Fmt&fUT3)  { ps(); cout << setprecision(0) << Z << " " << E << " ";                  if (N<0)cout << 'S' << N + 10000000; else cout << N; }	//UTM std 3-word S-style
	if (Fmt&fUT4)  { ps(); cout << setprecision(0) << Z << " " << (N<0 ? "S " : "N ") << E << " "; if (N<0)cout << N + 10000000; else cout << N; }	//UTM std 4-word N|S-style
}

void Geoconverter::DatumConvert(int dIn, double LatIn, double LongIn, double HtIn, int dTo, double& LatTo, double& LongTo, double& HtTo)
{
	// converts LatLongHt in datum dIn, to LatLongHt in datum dTo;  2002dec: by Eugene Reimer, from PeterDana equations.
	// Lat and Long params are in degrees;  North latitudes and East longitudes are positive;  Height is in meters;
	// ==This approach to Datum-conversion is a waste of time;  to get acceptable accuracy a large table is needed -- see NADCON, NTv2...
	double a, ee, N, X, Y, Z, EE, p, b, t;

	//--transform to XYZ, using the "In" ellipsoid
	//LongIn += 180;
	a = ellip[datum[dIn].eId].EquatorialRadius;
	ee = ellip[datum[dIn].eId].eccSquared;
	N = a / sqrt(1 - ee*sin(LatIn*deg2rad)*sin(LatIn*deg2rad));
	X = (N + HtIn) * cos(LatIn*deg2rad) * cos(LongIn*deg2rad);
	Y = (N + HtIn) * cos(LatIn*deg2rad) * sin(LongIn*deg2rad);
	Z = (N*(1 - ee) + HtIn) * sin(LatIn*deg2rad);

	//--apply delta-terms dX dY dZ
	//cout<<"\tX:" <<X <<" Y:" <<Y <<" Z:" <<Z;		//==DEBUG
	X += datum[dIn].dX - datum[dTo].dX;
	Y += datum[dIn].dY - datum[dTo].dY;
	Z += datum[dIn].dZ - datum[dTo].dZ;
	//cout<<"\tX:" <<X <<" Y:" <<Y <<" Z:" <<Z;		//==DEBUG

	//--transform back to LatLongHeight, using the "To" ellipsoid
	a = ellip[datum[dTo].eId].EquatorialRadius;
	ee = ellip[datum[dTo].eId].eccSquared;
	EE = ee / (1 - ee);
	p = sqrt(X*X + Y*Y);
	b = a*sqrt(1 - ee);
	t = atan(Z*a / (p*b));
	LatTo = atan((Z + EE*b*sin(t)*sin(t)*sin(t)) / (p - ee*a*cos(t)*cos(t)*cos(t)));
	LongTo = atan(Y / X);
	HtTo = p / cos(LatTo) - a / sqrt(1 - ee*sin(LatTo)*sin(LatTo));
	LatTo *= rad2deg;
	LongTo *= rad2deg;  LongTo -= 180;
	return;
}


void Geoconverter::LLtoUTM(int eId, double Lat, double Long, double& Northing, double& Easting, int& Zone)
{
	// converts LatLong to UTM coords;  3/22/95: by ChuckGantz chuck.gantz@globalstar.com, from USGS Bulletin 1532.
	// Lat and Long are in degrees;  North latitudes and East Longitudes are positive.
	double a = ellip[eId].EquatorialRadius;
	double ee = ellip[eId].eccSquared;
	Long -= int((Long + 180) / 360) * 360;			//ensure longitude within -180.00..179.9
	double N, T, C, A, M;
	double LatRad = Lat*deg2rad;
	double LongRad = Long*deg2rad;

	Zone = int((Long + 186) / 6);
	if (Lat >= 56.0 && Lat < 64.0 && Long >= 3.0 && Long < 12.0)  Zone = 32;
	if (Lat >= 72.0 && Lat < 84.0){			//Special zones for Svalbard
		if (Long >= 0.0  && Long <  9.0)  Zone = 31;
		else if (Long >= 9.0  && Long < 21.0)  Zone = 33;
		else if (Long >= 21.0 && Long < 33.0)  Zone = 35;
		else if (Long >= 33.0 && Long < 42.0)  Zone = 37;
	}
	double LongOrigin = Zone * 6 - 183;			//origin in middle of zone
	double LongOriginRad = LongOrigin * deg2rad;

	double EE = ee / (1 - ee);

	N = a / sqrt(1 - ee*sin(LatRad)*sin(LatRad));
	T = tan(LatRad)*tan(LatRad);
	C = EE*cos(LatRad)*cos(LatRad);
	A = cos(LatRad)*(LongRad - LongOriginRad);

	M = a*((1 - ee / 4 - 3 * ee*ee / 64 - 5 * ee*ee*ee / 256) *LatRad
		- (3 * ee / 8 + 3 * ee*ee / 32 + 45 * ee*ee*ee / 1024) *sin(2 * LatRad)
		+ (15 * ee*ee / 256 + 45 * ee*ee*ee / 1024) *sin(4 * LatRad)
		- (35 * ee*ee*ee / 3072) *sin(6 * LatRad));

	Easting = k0*N*(A + (1 - T + C)*A*A*A / 6 + (5 - 18 * T + T*T + 72 * C - 58 * EE)*A*A*A*A*A / 120) + 500000.0;

	Northing = k0*(M + N*tan(LatRad)*(A*A / 2 + (5 - T + 9 * C + 4 * C*C)*A*A*A*A / 24
		+ (61 - 58 * T + T*T + 600 * C - 330 * EE)*A*A*A*A*A*A / 720));
	return;
}


void Geoconverter::UTMtoLL(int eId, double Northing, double Easting, int Zone, double& Lat, double& Long)
{
	// converts UTM coords to LatLong;  3/22/95: by ChuckGantz chuck.gantz@globalstar.com, from USGS Bulletin 1532.
	// Lat and Long are in degrees;  North latitudes and East Longitudes are positive.
	double a = ellip[eId].EquatorialRadius;
	double ee = ellip[eId].eccSquared;
	double EE = ee / (1 - ee);
	double e1 = (1 - sqrt(1 - ee)) / (1 + sqrt(1 - ee));
	double N1, T1, C1, R1, D, M, mu, phi1Rad;
	double x = Easting - 500000.0;			//remove 500,000 meter offset for longitude
	double y = Northing;
	double LongOrigin = Zone * 6 - 183;			//origin in middle of zone

	M = y / k0;
	mu = M / (a*(1 - ee / 4 - 3 * ee*ee / 64 - 5 * ee*ee*ee / 256));

	phi1Rad = mu + (3 * e1 / 2 - 27 * e1*e1*e1 / 32) *sin(2 * mu)
		+ (21 * e1*e1 / 16 - 55 * e1*e1*e1*e1 / 32) *sin(4 * mu)
		+ (151 * e1*e1*e1 / 96) *sin(6 * mu);
	N1 = a / sqrt(1 - ee*sin(phi1Rad)*sin(phi1Rad));
	T1 = tan(phi1Rad)*tan(phi1Rad);
	C1 = EE*cos(phi1Rad)*cos(phi1Rad);
	R1 = a*(1 - ee) / pow(1 - ee*sin(phi1Rad)*sin(phi1Rad), 1.5);
	D = x / (N1*k0);

	Lat = phi1Rad - (N1*tan(phi1Rad) / R1)*(D*D / 2 - (5 + 3 * T1 + 10 * C1 - 4 * C1*C1 - 9 * EE)*D*D*D*D / 24
		+ (61 + 90 * T1 + 298 * C1 + 45 * T1*T1 - 252 * EE - 3 * C1*C1)*D*D*D*D*D*D / 720);
	Lat *= rad2deg;
	Long = (D - (1 + 2 * T1 + C1)*D*D*D / 6 + (5 - 2 * C1 + 28 * T1 - 3 * C1*C1 + 8 * EE + 24 * T1*T1)*D*D*D*D*D / 120) / cos(phi1Rad);
	Long = LongOrigin + Long*rad2deg;
	return;
}

