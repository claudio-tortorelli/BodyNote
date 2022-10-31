#ifndef _SYS_INFO_DEFS_H_
#define _SYS_INFO_DEFS_H_

#include "ShlObj.h"
#include "LMCONS.H"
#include "windows.h"
#include "shlwapi.h"
#include "math.h"
#include "WinIoCtl.h"
//#include "CPU_Info.h"
#include "Winsock2.h"

#pragma comment(lib,"Ws2_32.lib")
////////////////////////////////////////////////
//////////////    Queries    ///////////////////
#define Q_OS				0
#define Q_COMPUTER_NAME		1
#define Q_IP_ADDRESS		2
#define Q_USER_NAME			3
#define Q_IEXPLORER_VERSION	4
#define Q_RAM_TOTAL			5
#define Q_RAM_FREE			6 
#define Q_HARD_NUMBER		7
#define Q_PARTITIONS		8 
#define Q_HARD_SPACE		9
#define Q_HARD_FREE			10
#define Q_HARD_USED			11
#define Q_HDD_SMART_COMMAND 12
#define Q_CD_DRIVE			13
#define Q_RESOLUTION		14
#define Q_COLOR_DEPTH		15
#define Q_NUM_CPU			16
#define Q_CPU_SPEED			17
#define Q_CPU_ID			18
#define Q_CPU_VENDOR_ID		19
#define Q_OS_DIR			20
#define Q_SYSTEM_DIR		21
#define	Q_DESKTOP_DIR		22
#define Q_COOKIES_DIR		23
#define Q_STARTUP_DIR		24
#define Q_STARTMENU_DIR		25
#define Q_FAVORITES_DIR		26
#define Q_FONTS_DIR			27
#define Q_INET_CACHE_DIR	28
#define Q_LOCAL_APP_DIR		29
#define Q_MY_DOCUMENTS		30
#define Q_PROGRAM_FILES_DIR	31
#define Q_PROGRAM_GROUP_DIR 32
#define Q_RECENT_DIR		33
#define Q_SEND_TO_DIR		34
#define Q_TEMPLATES_DIR		35
#define Q_ADMIN_TOOLS_DIR	36
#define Q_HISTORY_DIR		37
#define Q_NET_HOOD_DIR		38
#define Q_PERSONAL_DIR		39
#define Q_PROFILE_DIR		40
#define Q_COM_STARTUP_DIR	41	//Common Directories
#define Q_COM_PROG_DIR		42	
#define Q_COM_DESKTOP_DIR	43	
#define Q_COM_FAVORITES_DIR	44
#define Q_COM_STARTMENU_DIR	45
#define Q_COM_ADMIN_DIR		46
#define Q_COM_APP_DATA_DIR	47
#define Q_COM_DOCUMENTS_DIR	48
#define Q_COM_TEMPLATES_DIR	49



CString QueryCDDrive();
CString QueryTotalRAM();
CString QueryFreeRAM();
CString QueryUserName();
CString QueryComputerName();
//CString QueryCPUNumber();
//CString QueryCPUName();
//CString QueryCPUSpeed();
//CString QueryCPUSerial();
//CString QueryCPUID();
//CString QueryCPUVendorID();
CString QueryResolution();
CString QueryPixelDepth();
CString QueryLocalIPAddress();
CString QueryPartitions();
CString QueryDirectory(char* sFolder,int iFolder);
CString GetCommandError();

CString QueryHardDisks();
CString QueryHDDSmartCommand();
CString	QueryHardDiskSerialSum(BOOL bFixedOnly = TRUE);
CString	QueryHardDiskSerials();
CString	QueryHardDiskSerial(CString hdLetter);
CString QueryDriveFileSystem(CString hdLetter);
CString QueryDriveType(CString hdLetter);
CString QueryAllDriveSpace();
CString QueryDriveTotalSpace(CString hdLetter = "");
CString QueryDriveUsedSpace(CString hdLetter = "");
CString QueryDriveFreeSpace(CString hdLetter = "");




#define NUM_OF_QUERIES		50

//
// Declare a global structure to help print the data.
// NOTE: Per ATA3 and ATA4 specs, these attribute definitions are defined by the drive vendor
// and hence their attributes may vary between vendors.
//
static PCHAR pAttrNames[]=
{
	"No Attribute Here       ", //0
	"Raw Read Error Rate     ", //1
	"Throughput Performance  ", //2
	"Spin Up Time            ", //3
	"Start/Stop Count        ", //4
	"Reallocated Sector Count", //5
	"Read Channel Margin     ", //6
	"Seek Error Rate         ", //7
	"Seek Time Performance   ", //8
	"Power On Hours Count    ", //9
	"Spin Retry Count        ", //10
	"Calibration Retry Count ", //11
	"Power Cycle Count       ", //12
	"(Unknown attribute)     "
};

#define MAX_KNOWN_ATTRIBUTES	12

static char Query[NUM_OF_QUERIES][50]=
{
	"Operating System (OS)",						//1
	"Computer Name",
	"IP Address",
	"User Name",
	"Internet Explorer Version",					//5
	"Total RAM",
	"Free Memory",
	"Number of Hard Disk Drives",
	"Partitions",
	"Hard Disk Total Space",
	"Hard Disk Free Space",							//11
	"Hard Disk Used Space",
	"Hard Disk Features (S.M.A.R.T.)"
	"CD-ROM Drives",
	"Monitor Resolution",
	"Color Depth",
	"Number of CPUs",								//17
	"CPU Speed",
	"CPU Identifier (ID)",
	"CPU Vendor Identifier (Vendor ID)",
	"Operating System Folder",
	"System Folder",								//22
	"Desktop Folder",
	"Cookies Folder",
	"Startup Folder",
	"Start Menu Folder",
	"Favorites Folder",								//27
	"Fonts Folder",
	"Internet Cache Folder",
	"Local Application Folder",
	"My Documents Folder",
	"Program Files Folder",							//32
	"Program Group Folder",
	"Recent Folder",
	"Send To Folder",
	"Templates Folder",
	"Administrative Tools Folder",
	"History Folder",
	"NetHood Folder",
	"Personal Folder",
	"Profile Folder",
	"Common Startup Folder",						//42
	"Common Programs Folder",
	"Common Desktop Folder",
	"Common Favorites Folder",
	"Common Start Menu Folder",
	"Common Administrative Tools Folder",
	"Common Application Data Folder",
	"Common Documents Folder",
	"Common Templates Folder"						//50
};

#define MAX_OF_HARD_DISKS	24
static char HardDiskLetters[MAX_OF_HARD_DISKS][4]={
	"c:\\",	"d:\\",	"e:\\",	"f:\\",	"g:\\",	"h:\\",
	"i:\\",	"j:\\",	"k:\\",	"l:\\",	"m:\\",	"n:\\",
	"o:\\",	"p:\\",	"q:\\",	"r:\\",	"s:\\",	"t:\\",
	"u:\\",	"v:\\",	"w:\\",	"x:\\",	"y:\\",	"z:\\"
};
#endif //_SYS_INFO_DEFS_H_
