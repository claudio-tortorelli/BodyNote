// CTLib.h : main header file for the CTLib DLL
// Claudio Tortorelli menci


#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

//////////////////////////////// dll version
#define	DLL_VER	"1.9.5"

/**
 * change log : <Major Changes>.<Minor Changes>.<Maintenance Changes>
 ********************************************************************
 1.9.5	13-aug-2015	Added: CT_IntToString()
 1.9.4	20-apr-2015	Added: CT_TranslatePath takes an empty ext too
 1.9.3	09-apr-2015	Added: CT_FindRibbonElement as MFC UI tool
 1.9.2	08-feb-2015	Added: (not USED) twofish encryption algorithm class 	
 1.9.1	17-may-2014 Added: Convex hull monotonechain and graham scan 
 1.9.0	27-mar-2014	Added blowfish encryption methods
 1.8.0	30-jan-2013	Project file restruvtured (moved header and cpp to right position, CTLib files isolated)
					Introduced sprintf_s in DeleteDirectory
					Added CT_GetRandomPoint2D() and CT_GetVoronoiDiagram()
					Added MSTPT2D and MSTPT3D geometrical structs
					Extended CT_IsPolygonContainPoint() to MSTPT2D
					Added CT_ArePolygonsOverlapping()
 1.7.4	24-jan-2013 CT_StringToDouble(), CT_StringToBoolean(), CT_StringToInt() extended to std string
					CT_StringToDouble(), CT_StringToBoolean(), CT_StringToInt() from CString* to CString
 1.7.3	22-jan-2013 CT_ParseString() extended to std string and char*
 1.7.2	14-jan-2013 Updated CT_SendMail() to include the smtp port
 1.7.1	07-jan-2013 Updated CT_GetOSInfo() to include windows 8 informations
					Updated CT_DeleteDirectory(), no set permissions on folder
 1.7.0	17-dec-2012 CT_ParseString() extended to std vectors
					CT_StringToDouble(), CT_StringToInt(), CT_StringToBoolean() extended to CString input
					Support for vs 2012, vc110
					Support for 32 and 64 bit
 1.6.10	10-nov-2012	removed CT_GetCPUNumber(); CT_GetCPUSpeed(); CT_GetCPUSerial(); CT_GetCPUID(); CT_GetCPUVendorID(); because no supported by 64 bit architecture
					Support to 64bit
 1.6.9	24-oct-2012 Added CT_Shuffle()
 1.6.8	04-oct-2012	CT_GetFileDate() and CT_GetFileTime return CString instead of int (problem with int sequence starting with 0)
 1.6.7	21-sep-2012	Added CT_IsValidFileName
 1.6.6	03-set-2012 Added CT_CaptureWindow()
 1.6.5	27-jul-2012	Added CT_InstallDeviceDriver()
 1.6.4  23-jul-2012 Added CT_CopyDirectory()
 1.6.3	05-jul-2012	Added HTML report in CReportBuilder, CT_ReportSetHTMLReportData() and CT_ReportBuild()
					CT_GetFileDate(), accept the type of date
					CT_GetFileTime(), accept the type of time
					In some case "Debug" config CT_ParseString() crashes, put it in "Release" !
 1.6.2	16-jun-2012	Fix string in QueryTotalRAM()
					CT_SendEmail2() ... working on			
					removed CT_ReportSetHTMLPath
					added CT_ReportSetHTMLReportData
 1.6.1	10-may-2012	Fix format of CT_GetFreeRam
 1.6.0	09-may-2012	Added MD5 methods
 1.5.1  03-feb-2012 Added CT_GetDisplayAdaptersList()
 1.5.0	19-dec-2011 Added report methods and classes
 1.4.4	19-dec-2011	Changed some string tag for system queries (eg RAM, CPU...)
 1.4.3  05-dec-2011 Removed CT_GetElapsedMsecFromSpan and CT_GetElapsedMsecFromStart
					Fixed CT_GetElapsedTime()
 1.4.2  25-nov-2011 Fixed second value in CT_GetElapsedTime()
 1.4.1  27-oct-2011 Some bug fix Ram query methods
 1.4.0  26-oct-2011 Added MST OS/HW Queries methods
					Check methods comments
 1.3.3  13-oct-2011 CT_ParseString support CStringArray
 1.3.2	04-aug-2011	Added CT_GetFileSize()
					Added CT_GetModuleFileDate()	
					Edited CT_GetFileDate() and CT_GetFileTime()
 1.3.1	19-jul-2011 Added CT_GetActiveProcessNumber
					Renamed CT_FindProcessId() in CT_GetProcessId()
 1.3.0	18-jul-2011 Reorganized queries to OS and HW, SysInfoDefs renamed in HWInfo and SystemInfo in OSInfo. Logical methods are separed
					Added CT_GetDriveTotalSpace()
					Added CT_GetDriveUsedSpace()
					Added CT_GetDriveFreeSpace()
					Added CT_GetDriveSerial()
					Added CT_GetDriveFileSystem()
					Added CT_GetDriveType()
 1.2.6	07-jul-2011	CT_PickFolderPath() accept the initial folder 
 1.2.5	09-jun-2011 CT_WaitforSingleObject modified to accept file parameters
 1.2.4	25-may-2011	_MAX_PROCESSES, _PI, _NaN in place of MAX_PROCESSES, PI, NaN
 1.2.3	27-apr-2011	Removed CT_SplitString() specialized in CT_SplitStringByParts() and CT_SplitStringByChars()
 1.2.2	13-apr-2011 Added CStringArray other than CArray<CString, LPCSTR> in CT_GetExifData()
					OpenCV definitively removed
					Correct a bug in CT_ShellExecute()
 1.2.1	07-apr-2011 Added CTLib VC100 to Apis
 1.2.0	01-apr-2011 Added CT_OpenTaskManager()
 					Added CT_OpenDeviceManager()
					Added CT_OpenServiceManager()
					Added CT_OpenStartupManager()
					Updated CT_Shutdown()
					Removed DTWinver because obsolete, added SystemInfo classes
					Added CT_GetOSInfo()
					Added CT_IsOS32Bit()
					Added CT_IsOS64Bit()
					Added CT_GetOSVersionName()
					Updated CT_ShellExecute(), optional shell show
 1.1.5	25-mar-2011 Added CT_ShowSplashScreen()
 1.1.4	09-mar-2011 Added CT_ReadReportResult()
					Added CT_WriteReportResult() 
					Added CT_DeleteReport()
					Added CT_IsReportPresent()
					Added CT_PickFolderPath()
					Added CT_GetRandomInt()
					Added CT_Shutdown()
 1.1.3	07-mar-2011 CT_GetVersionInfo(), admits hModule = NULL
					Changed CT_ prefix with CT_
 1.1.2  01-mar-2011 CT_ShellExecute hides the console window
					Added CT_GetScreenSize
 1.1.1	25-feb-2011	Added CT_ProcessKill, need taskkill.exe
					Added CT_SendEmail, need bmail.exe
 1.1.0	15-feb-2011	Added Timer functionalities:
					CT_StartTimer()
					CT_ResetTimer()
					CT_GetElapsedMsecFromStart()
					CT_GetElapsedMsecFromSpan()
					CT_GetElapsedTime()
					Modified CT_ShellExecute()
					Added CT_MakeFilterPair()
					Added CT_FindProcessId()
 1.0.6	08-feb-2011	Added CT_WaitForSingleObject()
 1.0.5	22-jan-2011	Update some functions interfaces
					_min, _max and other common operators put into header file
					OpenCV is not supported yet (but still present)
					visual studio 2003 vc70 version support
 1.0.4	12-jan-2011	Changed bCreateFolder and bAppendAppName to CT_GetSpecialFolder()
					OpenCV functions needs two versions of library: remove support??? <----------
 1.0.3	08-jan-2011 Added CT_ prefix to functions
 1.0.2	06-jan-2011 Added tutorial first version and code comments
					Added NaN macro
					Added the Creative Common License
					Added GetFileTime() function
					Added Radial2Degree() and DegreeToRadial() functions
					Added <time.h> support
					Added support to (win) System Info Define queries
					Added CheckFreeRam()
					Some interface parameters was renamed, some default values added
					Add some start prerequisites to some functions
 1.0.1	29-dec-2010	Open cv211 library support added, with USE_OPENCV preprocessor
					GetVersionInfo() modified: now return string contains . instead of ,
					GetCurrentSysTime() and GetCurrentSysDate() added
 1.0.0	18-dec-2010	Start
 */

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Sections of functions
/////////////// DLL versioning
/////////////// General Informations
/////////////// File system and special folders (windows), path management
/////////////// String management
/////////////// Mathematical and geometrical functions
/////////////// Application tools
/////////////// System Tools
/////////////// System Info
/////////////// Image tools
/////////////// Messages and thread tools
/////////////// Timer
/////////////// Report
/////////////// Application report system
/////////////// Hash 
/////////////// Encryption
/////////////// MFC UI tools

#include "ReportBuilder.h"
#include "VoronoiDiagramGenerator.h"
#include <list>
#include <vector>
#include "ConvexHull.h"
#include "afxribbonbar.h"
using namespace std;

/////////////////////////////// external dependencies - start
#pragma comment(lib, "version.lib")
#pragma comment( lib, "psapi.lib")
/////////////////////////////// external dependencies - end

//////////////////////////////// common define - start
#ifndef _max
	#define _max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef _min
	#define _min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
	#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
	#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef _NaN
	#define _NaN -99999999
#endif

#ifndef _PI
	#define _PI 3.1415926535897932384626433832795
#endif

#ifndef _MAX_PROCESSES
	#define _MAX_PROCESSES 1024 
#endif

#ifndef MSTPT2D
	typedef struct MSTPT2D
	{
		double x;
		double y;
	}
	MSTPT2D;
#endif

#ifndef MSTPT3D
	typedef struct MSTPT3D
	{
		double x;
		double y;
		double z;
	}
	MSTPT3D;
#endif



//////////////////////////////// common define - end

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

#define CTLIB __declspec(dllexport)

class CCTLibApp : public CWinApp
{
public:
	CCTLibApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

public:
	CReportBuilder	m_ReportBuilder;
};

///////////////
/////////////// DLL versioning
///////////////
/*
 * return version of CTLib dll 
 */
CTLIB CString	CT_GetCTLibVersion(); 

///////////////
/////////////// General Informations
///////////////
/*
 * return current system time in hours:minutes:seconds format 
 */
CTLIB CString	CT_GetCurrentSysTime();
/*
 * return current system time in day-month-year format 
 */
CTLIB CString	CT_GetCurrentSysDate(); 
/*
 * return horizontal and vertical size of desktop, in pixel 
 */
CTLIB void		CT_GetScreenSize(int& cx, int& cy); 
/*
 * return names of display adapters found on system and their number
 */
CTLIB int		CT_GetDisplayAdaptersList(CArray<CString,LPCSTR>* pDisplayNames); 

///////////////
/////////////// File system and special folders (windows), path management
///////////////
/*
 * get the special folder path in windows file system, based on required ID 
 * CSIDL_APPDATA : C:\Documents and Settings\username\Application Data
 * CSIDL_COMMON_APPDATA : C:\Documents and Settings\All Users\Application Data
 * CSIDL_LOCAL_APPDATA : C:\Documents and Settings\username\Local Settings\Application Data
 * CSIDL_PERSONAL : C:\Documents and Settings\username\My Documents
 * CSIDL_PROFILE : C:\Users\username
 * CSIDL_SYSTEM : C:\Windows\system32
 */
CTLIB BOOL		CT_GetSpecialFolder(char* pPath, int size, UINT specialFolderID, BOOL bAppendAppName = FALSE, BOOL bCreateFolder = FALSE); 
/*
 * get the special folder path in the system, based on required ID 
 */
CTLIB CString	CT_GetSpecialFolder(UINT specialFolderID, BOOL bAppendAppName = FALSE, BOOL bCreateFolder = FALSE); 
/*
 * make relative an absolute path 
 */
CTLIB BOOL		CT_GetRelativePath(char* pFrom, BOOL bIsFromDir, char* pTo, BOOL bIsToDir, char* pRelativePath, int pathSize); 
/*
 * make relative an absolute path 
 */
CTLIB BOOL		CT_GetRelativePath(CString from, BOOL bIsFromDir, CString to, BOOL bIsToDir, CString& relativePath);  
/*
 * make absolute a relative path 
 */
CTLIB BOOL		CT_GetAbsolutePath(char* pFrom, BOOL bIsFromDir, char* pTo, BOOL bIsToDir, char* pAbsolutePath, int absPathSize); 
/*
 * make absolute a relative path 
 */
CTLIB BOOL		CT_GetAbsolutePath(CString from, BOOL bIsFromDir, CString to, BOOL bIsToDir, CString& absolutePath); 
/*
 * read last browsed path from user profile 
 */
CTLIB CString	CT_GetLastBrowsedPath(); 
/*
 * store last browsed path into user profile 
 */
CTLIB void		CT_SetLastBrowsedPath(CString path, BOOL bIsFile = TRUE); 
/*
 * change the original path name into a similar one with different file format 
 */
CTLIB CString	CT_TranslatePath(CString basePath, CString ext = "", CString fileNamePrefix = "", CString fileNamePostfix = ""); 
/*
 * return  a randomic file path that isn't already existing into the folder 
 */
CTLIB BOOL		CT_GetRandomFilePath(char* pFolder, char* pExt, char* pRandomFilePath, int randomFilePathSize); 
/*
 * return  a randomic file path that isn't already existing into the folder 
 */
CTLIB CString	CT_GetRandomFilePath(CString folder, CString ext); 
/*
 * get the file date expressed in aaaammyy integer format or "" if an error occurred 
 * dateType = 0, creation date
 * dateType = 1, access date
 * dateType = 2, write date
 */
CTLIB CString	CT_GetFileDate(CString filePath, int dateType = 0); 
/*
 * get the file time expressed in hhmmss integer format or "" if an error occurred 
 * timeType = 0, creation time
 * timeType = 1, access time
 * timeType = 2, write time
 */
CTLIB CString	CT_GetFileTime(CString filePath, int timeType = 0); 
/*
 * return the file length in byte or -1 if an error occurred 
 */
CTLIB long		CT_GetFileSize(CString filePath); 
/*
 * optimize the path removing multiple '\' instance and adding the final one if requested 
 */
CTLIB CString	CT_OptimizePath(CString originalPath, BOOL bFinalSlash); 
/*
 * Pick a folder path, through default tree dialog 
 */
CTLIB CString	CT_PickFolderPath(const char* pCaption, const char* pInitialFolder = NULL, HWND hOwner = NULL);
/*
 * pFrom is a string pointer of the source paths separated by '\0' and terminated by '\0\0'.
 * pTo is a string pointer of the destination paths separated by '\0' and terminated by '\0\0'.
 * Recursive Copy
 */
CTLIB BOOL		CT_CopyDirectory(CString from, CString to, BOOL bSilent = FALSE);
CTLIB BOOL		CT_CopyDirectory(char* pFrom, char* pTo, BOOL bSilent = FALSE);

CTLIB BOOL		CT_DeleteDirectory(CString folder);

/*
 * Ensure a file name is legal.
 * Parameters
 * pFileName	The file name to check. This must be only the file name.
 *  			If a full path is passed, the check will fail.
 * Returns Zero on success.
 * Non-Zero on failure.
 */
CTLIB int		CT_IsValidFileName(const char *pFileName);
CTLIB int		CT_IsValidFileName(const wchar_t *pFileName);

///////////////
/////////////// String management
///////////////
/*
 * return the array of substrings splitted using the separator 
 */
CTLIB int		CT_ParseString(CString pattern, char separator, CArray<CString,LPCSTR>* pParsed); 
/*
 * return the array of substrings splitted using the separator 
 */
CTLIB int		CT_ParseString(CString pattern, char separator, CStringArray* pParsed); 
/*
 * return the array of substrings splitted using the separator 
 */
CTLIB int CT_ParseString(CString pattern, char separator, std::vector<std::string>* pParsed);
/*
 * return the array of substrings splitted using the separator 
 */
CTLIB int		CT_ParseString(std::string pattern, char separator, CArray<CString,LPCSTR>* pParsed); 
/*
 * return the array of substrings splitted using the separator 
 */
CTLIB int		CT_ParseString(std::string pattern, char separator, CStringArray* pParsed); 
/*
 * return the array of substrings splitted using the separator 
 */
CTLIB int CT_ParseString(std::string pattern, char separator, std::vector<std::string>* pParsed);
/*
 * return the array of substrings splitted using the separator 
 */
CTLIB int CT_ParseString(char* pattern, char separator, CArray<CString,LPCSTR>* pParsed); 
/*
 * return the array of substrings splitted using the separator 
 */
CTLIB int CT_ParseString(char* pattern, char separator, CStringArray* pParsed); 
/*
 * return the array of substrings splitted using the separator 
 */
CTLIB int CT_ParseString(char* pattern, char separator, std::vector<std::string>* pParsed);
/*
 * return the array of substrings  
 */
CTLIB int		CT_SplitStringByParts(CString strIn, int nPart, CStringArray* pSplitted); 
/*
 * return the array of substrings of the given length 
 */
CTLIB int		CT_SplitStringByChars(CString str, int splitSize, CStringArray* pSplitted); 
/*
 * return the double value of the string 
 */
CTLIB BOOL		CT_StringToDouble(char* pStrIn, double* pRetValue); 
/*
 * return the double value of the string 
 */
CTLIB BOOL		CT_StringToDouble(CString StrIn, double* pRetValue); 
/*
 * return the double value of the string 
 */
CTLIB BOOL		CT_StringToDouble(string StrIn, double* pRetValue);
/*
 * return the string value of the double 
 */
CTLIB BOOL		CT_DoubleToString(double retValue, int precision, char* pStrOut, int strOutSize); 
/*
 * return the boolean value of the string 
 */
CTLIB BOOL		CT_StringToBoolean(char* pStrIn, BOOL* pRetValue); 
/*
 * return the boolean value of the string 
 */
CTLIB BOOL		CT_StringToBoolean(CString StrIn, BOOL* pRetValue); 
/*
 * return the boolean value of the string 
 */
CTLIB BOOL		CT_StringToBoolean(string StrIn, BOOL* pRetValue); 
/*
 * return the integer value of the string 
 */
CTLIB BOOL		CT_StringToInt(char* pStrIn, int* pRetValue);
/*
 * return the integer value of the string 
 */
CTLIB BOOL		CT_StringToInt(CString StrIn, int* pRetValue);
/*
 * return the integer value of the string 
 */
CTLIB BOOL		CT_StringToInt(string StrIn, int* pRetValue);
/*
 * return the string from integer value  
 */
CTLIB BOOL		CT_IntToString(int inValue, CString& StrOut);
CTLIB BOOL		CT_IntToString(int inValue, char* pStrOut, int strOutSize);

/*
 * remove string leading and trailing empty spaces if present 
 */
CTLIB CString	CT_RemoveStartAndEndSpaces(CString strIn); 
/*
 * Make a string valid for filter into a CFileDialog 
 */
CTLIB void		CT_MakeFilterPair(const char* filter, int filterSize, char* fibuf); 

///////////////
/////////////// Mathematical and geometrical functions
///////////////
/*
 * make the angle value (radial) normalized between 0 and 2PI 
 */
CTLIB double	CT_NormalizeAngle(double radialAngle); 
/*
 * convert a radial angle to 0-360 degree value 
 */
CTLIB double	CT_Radial2Degree(double angle); 
/*
 * convert a degree angle to 0-2PI value 
 */
CTLIB double	CT_DegreeToRadial(double degreeAngle); 
/*
 * evaluate if a 2d point is inside a 2d polygon, given by a set of points 
 */
CTLIB int		CT_IsPolygonContainPoint(CArray<POINT, POINT>* pPoints, POINT Pnt); 
/*
 * evaluate if a 2d point is inside a 2d polygon, given by a set of points 
 */
CTLIB int		CT_IsPolygonContainPoint(CArray<MSTPT2D, MSTPT2D>* pPoints, MSTPT2D Pnt); 
/*
 * Create an array of nElem items and return the shuffled indexes
 */
CTLIB void		CT_Shuffle(int nElem, vector<int>& shuffledElemIndexes);
/*
 * Build a Voronoi diagram. Based on Fortune algorithm. 
 * input: source points and boundaries
 * output: array of polygon point 
 * returns the number of polygons, 0 if failed
 */
CTLIB int		CT_GetVoronoiDiagram(vector<VoronoiSourcePoint> srcPoints, VoronoiInParams params, vector<vector<VPoint>>* pOutPolygons);
/*
 * Generate a random 2D point
 */
CTLIB BOOL		CT_GetRandomPoint2D(long minX, long maxX, long minY, long maxY, long* pX, long* pY);
/*
 * Generate a random 2D point
 */
CTLIB BOOL		CT_GetRandomPoint2D(double minX, double maxX, double minY, double maxY, double* pX, double* pY);
/*
 * Test if two 2D polygons are overlapped
 */
CTLIB BOOL		CT_ArePolygonsOverlapping(CArray<MSTPT2D, MSTPT2D>* pPolygon1, CArray<MSTPT2D, MSTPT2D>* pPolygon2);
/*
 * evaluate convex hull with MonotoneChain algorithm
 */
CTLIB vector<CHPoint>	CT_ConvexHullMonotone(vector<CHPoint> Points);
/*
 * evaluate convex hull with GrahamScan algorithm
 */
CTLIB stack<CHPoint> CT_ConvexHullGraham(vector<CHPoint> Points);


///////////////
/////////////// Application tools
///////////////
/*
 * return current software version, taken from resources 
 */
CTLIB BOOL		CT_GetVersionInfo(HMODULE hModule, CString& ProductVersion, CString& FileVersion); 
/*
 * get the user profile ini file path, inside the user folder 
 */
CTLIB CString	CT_GetUserProfilePath(); 
/*
 * load a string value from the user profile 
 */
CTLIB DWORD	CT_GetUserProfileString(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpDefault, LPSTR lpReturnedString, DWORD nSize); 
/*
 * store a string value into the user profile 
 */
CTLIB BOOL		CT_WriteUserProfileString(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpStringToWrite); 
/*
 * in MDI application call OnSaveDocument for each document currently open and terminate  
 */
CTLIB void		CT_SaveBeforeEnd(CMultiDocTemplate* pTemplate, CString message); 
/*
 * return the number of open documents 
 */
CTLIB int		CT_GetOpenDocumentNumber(CMultiDocTemplate* pTemplate); 
/*
 * Get a random int between 0 and maxRndVal - 1  
 */
CTLIB int		CT_GetRandomInt(int maxRndVal); 
/*
 * show a splash screen: the bmp must be included into the project as resource 
 */
CTLIB void		CT_ShowSplashScreen(UINT bmpResourceId, int showingMillisec); 
/*
 * return a string with module last save time (and optional integer aaaammdd hhmmss) 
 */
CTLIB CString	CT_GetModuleFileDate(int* pAaaammdd = NULL, int* pHhmmss = NULL); 

///////////////
/////////////// System Tools
///////////////
/*
 * shutdown the pc, need to be administrator (or Domain Admin) 
 */ 
CTLIB BOOL		CT_Shutdown(int nSecDelay = 30, BOOL bAbort = FALSE, BOOL bRemote = FALSE, CString remoteUsername = "", CString remotePw = "", CString remotePCName = ""); 
/*
 * open Windows task manager (taskmgr.exe) 
 */
CTLIB BOOL		CT_OpenTaskManager(); 
/*
 * open Windows device manager (devmgmt.msc) 
 */
CTLIB BOOL		CT_OpenDeviceManager(); 
/*
 * open Windows service manager (services.msc)
 */
CTLIB BOOL		CT_OpenServiceManager(); 
/*
 * open Windows config manager (msconfig)
 */
CTLIB BOOL		CT_OpenStartupManager(); 
/*
 * use pnputil Windows tool to setup inf driver
 */
CTLIB BOOL		CT_InstallDeviceDriver(CString infPath); 
/*
 * use pnputil Windows tool to remove inf driver
 */
CTLIB BOOL CT_UninstallDeviceDriver(CString infOEMName);

///////////////
/////////////// System Info
///////////////
/*
 * return a string with version, edition, build nr, service pack, bit num
 */ 
CTLIB CString	CT_GetOSInfo(); 
/*
 * true if 32 bit os
 */
CTLIB BOOL		CT_IsOS32Bit(); 
/*
 * true if 64 bit os 
 */
CTLIB BOOL		CT_IsOS64Bit(); 
/*
 * return a string with version name 
 */
CTLIB CString	CT_GetOSVersionName(); 
/* 
 * get current free RAM on system 
 */
CTLIB CString	CT_GetFreeRam(); 
/*
 * get total drive space in MB. driveLetter = "c:\\" or empty. If empty all system drive will be examinated. If unable to get info an empty string is returned 
 */
CTLIB CString	CT_GetDriveTotalSpace(CString driveLetter = ""); 
/*
 * get used drive space in MB. driveLetter = "c:\\" or empty. If empty all system drive will be examinated. If unable to get info an empty string is returned 
 */
CTLIB CString	CT_GetDriveUsedSpace(CString driveLetter = ""); 
/*
 * get free drive space in MB. driveLetter = "c:\\" or empty. If empty all system drive will be examinated. If unable to get info an empty string is returned
 */
CTLIB CString	CT_GetDriveFreeSpace(CString driveLetter = ""); 
/*
 * get drive serial number. driveLetter = "c:" or empty. If empty all system drive will be examinated. If unable to get info an empty string is returned
 */
CTLIB CString	CT_GetDriveSerial(CString driveLetter); 
/*
 * get drive FS type. driveLetter = "c:" or empty. If empty all system drive will be examinated. If unable to get info an empty string is returned 
 */
CTLIB CString	CT_GetDriveFileSystem(CString driveLetter); 
/*
 * return a string with drive type (fixed, removable, ecc.) or empty if no type is found. 
 */
CTLIB CString	CT_GetDriveType(CString driveLetter); 
/*
 * get cd drive letter
 */
CTLIB CString	CT_GetCDDriveLetter(); 
/*
 * get system RAM status
 */
CTLIB CString	CT_GetRAMInfo(); 
/*
 * get current system username
 */
CTLIB CString	CT_GetUserName(); 
/*
 * get system computer name
 */
CTLIB CString	CT_GetComputerName(); 
/*
 * get current screen resolution
 */
CTLIB CString  CT_GetResolution(); 
/*
 * get current screen pixel depth
 */
CTLIB CString  CT_GetPixelDepth(); 
/*
 * get curren lan IP address
 */
CTLIB CString  CT_GetLocalIPAddress(); 

///////////////
/////////////// Image tools
///////////////
/*
 * get a random RGB color
 */
CTLIB COLORREF	CT_GetRandomColor(); 
/*
 * return a string with all main image EXIF data: file name, dimension, color, exposure time, iso, aperture, exposure value, focal length, camera model, shot time, flash used, file date
 */
CTLIB BOOL		CT_GetExifData(CString imageFilePath, CArray<CString, LPCSTR>* pDataRead); 
/*
 * return a string with all main image EXIF data: file name, dimension, color, exposure time, iso, aperture, exposure value, focal length, camera model, shot time, flash used, file date
 */
CTLIB BOOL		CT_GetExifData(CString imageFilePath, CStringArray* pDataRead); 
/*
 * get a bmp file from current window
 */
CTLIB BOOL		CT_CaptureWindow(CWnd* pWnd, CString szFile);
CTLIB BOOL		CT_CaptureWindow(CDC* pDC, CString szFile); 

///////////////
/////////////// Messages and thread tools
///////////////
/*
 * dispatch application and system messages avoiding UI deadlock
 */
CTLIB void			CT_PumpMessages(); 
/* 
 * launch a sub process on given executable and optional parameters
 */
CTLIB BOOL			CT_WaitForSingleObject(CString exeFilePath, CString params = ""); 
/* 
 * do a shellexecute system command, opening a file in a new window
 */
CTLIB HINSTANCE	CT_ShellExecute(CString filePath, CString params = "", CString operation = "open", int showShell = SW_SHOW); 
/* 
 * return the process id by process name
 */
CTLIB DWORD		CT_GetProcessId(LPCTSTR lpcszFileName);
/* 
 * return the number of active processes by process name
 */
CTLIB int			CT_GetActiveProcessNumber(LPCTSTR lpcszFileName); 
/* 
 * Kill all process named processName by using the system command line tool taskkill.exe
 */
CTLIB BOOL			CT_ProcessKill(CString processName); 
/* 
 * Send an email using the command line tool bmail.exe (from must be a dummy or real email address!)  
 */
CTLIB BOOL			CT_SendEmail(CString smtpServerAddress, CString to, CString fromAddress, CString subject = "", CString body = "", CString attachmentPath = "", CString smtpPort = ""); // Send an email using the command line tool bmail.exe (from must be a dummy or real email address!)
/**
 * Send an email using the command line tool mailsend.exe - multi receiver not admitted (send more than email)
 * mailsend -to <to> -f <fromAddress> -smtp <smtpServerAddress> -port <smtpPort> -ssl -auth-login -user <username> -pass <password> -sub <subject> 
 */
CTLIB BOOL			CT_SendEmail2(CString smtpServerAddress, CString smtpPort, CString to, CString fromName, CString subject, CString body = "", BOOL bSSL = FALSE, CString username = "", CString password = "", CString txtAttachmentPath = "");

///////////////
/////////////// Timer
///////////////
/*
 * start the timer 
 */
CTLIB BOOL		CT_StartTimer(); 
/*
 * reset timer variables
 */
CTLIB void		CT_ResetTimer(); 
/*
 * return a string hh::mm:ss, related to timer previously started
 */
CTLIB CString	CT_GetElapsedTime(); 

///////////////
/////////////// Report
///////////////
/*
 * Reset the report builder
 */
CTLIB void	CT_ReportReset(); 

/*
 * Fill current report with common header data
 */
CTLIB void CT_ReportFillCommonHeader();

/*
 * Fill current report with common data such as OS info, RAM, etc.
 */
CTLIB void CT_ReportFillCommonData();

/*
 * Add value to the report
 */
CTLIB void CT_ReportAddValue(CString key, CString value);

/*
 * Add value to the report
 */
CTLIB void CT_ReportAddValue(CString key, int value);

/*
 * Add value to the report
 */
CTLIB void CT_ReportAddValue(CString key, double value, int precision);

/*
 * Add value to the report
 *
 */
CTLIB void CT_ReportAddValue(CString key, CArray<CString, LPCSTR>* pValues);

/*
 * Add report title or subtitle
 *
 */
CTLIB void CT_ReportAddTitle(CString title);

/*
 * Set TXT report path
 *
 */
CTLIB void CT_ReportSetTXTPath(CString txtPath);

/*
 * Set HTML report 
 */
CTLIB BOOL CT_ReportSetHTMLReportData(HTMLReportData data);

/*
 * Build current reports
 */
CTLIB BOOL CT_ReportBuild();

///////////////
/////////////// Application report system
///////////////
/*
 * write a report result code (customized by app) to a report path (default = report.out in the same dir of executable)
 */
CTLIB BOOL		CT_WriteReportResult(int outCode, CString reportPath = ""); 
/*
 * read the report result code previously wrote by an app in the report file. Return -1 if no code is found. exePath = path of executable that generated the report 
 */
CTLIB int		CT_ReadReportResult(CString reportPath = "", CString exePath = ""); 
/*
 * delete current report file 
 */
CTLIB void		CT_DeleteReport(CString reportPath = "", CString exePath = ""); 
/*
 * check if report was wrote 
 */
CTLIB BOOL		CT_IsReportPresent(CString reportPath = "", CString exePath = ""); 

///////////////
/////////////// Hash 
///////////////
/*
 * Get hash code from string
 */
CTLIB BOOL		CT_MD5FromString(char* strIn, char* hashOut, int hashOutSize);

/*
 * Get hash code from file
 */
CTLIB BOOL		CT_MD5FromFile(char* filePath, char* hashOut, int hashOutSize);

///////////////
/////////////// Encryption
///////////////
CTLIB BOOL		CT_DoCrypt(const char* filePathIn, const char* filePathOut); 
CTLIB BOOL		CT_DoCrypt(char* pFromMemory, int fromSize, char* pToMemory, int toSize); 
CTLIB BOOL		CT_DoCrypt(const char* filePathIn, char* pToMemory, int toSize); 
CTLIB BOOL		CT_DoCrypt(char* pFromMemory, int fromSize, const char* filePathOut); 

CTLIB BOOL		CT_DoDecrypt(const char* filePathIn, const char* filePathOut); 
CTLIB BOOL		CT_DoDecrypt(char* pFromMemory, int fromSize, char* pToMemory, int toSize); 
CTLIB BOOL		CT_DoDecrypt(const char* filePathIn, char* pToMemory, int toSize); 
CTLIB BOOL		CT_DoDecrypt(char* pFromMemory, int fromSize, const char* filePathOut); 

CTLIB 	void	CT_SetDefaultKey(int iKey);
CTLIB 	void	CT_SetCustomKey(const char* customKey);

CTLIB 	int		CT_GetPairBufferSize(int curBufferSize);


///////////////
/////////////// MFC UI tools
///////////////
CTLIB 	CMFCRibbonBaseElement* CT_FindRibbonElement(CMFCRibbonBar wndRibbon, UINT elementId);
