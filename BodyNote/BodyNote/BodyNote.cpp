// BodyNote.cpp : definisce i comportamenti delle classi per l'applicazione.
//

#include "stdafx.h"
#include "BodyNote.h"

#include "BodyNoteDlg.h"
#include "AccessPasswordDlg.h"
#include "HardCodeLicenseManager.h"
#include "BackupProgressDlg.h"
#include "CrashRpt.h"
#include <strsafe.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _DEBUG
	#pragma comment(lib, "CTLibD.lib")

	#pragma comment(lib, "opencv_core248d.lib")
	#pragma comment(lib, "opencv_highgui248d.lib")
	#pragma comment(lib, "opencv_features2d248d.lib")
	#pragma comment(lib, "opencv_imgproc248d.lib")
	#pragma comment(lib, "opencv_calib3d248d.lib")
	#pragma comment(lib, "opencv_video248d.lib")
	#pragma comment(lib, "opencv_legacy248d.lib")
	#pragma comment(lib, "opencv_flann248d.lib")	

	#pragma comment(lib, "CrashRpt1402D.lib")
#else
	#pragma comment(lib, "CTLib.lib")
	
	#pragma comment(lib, "opencv_core248.lib")
	#pragma comment(lib, "opencv_highgui248.lib")
	#pragma comment(lib, "opencv_features2d248.lib")
	#pragma comment(lib, "opencv_imgproc248.lib")
	#pragma comment(lib, "opencv_calib3d248.lib")
	#pragma comment(lib, "opencv_video248.lib")
	#pragma comment(lib, "opencv_legacy248.lib")
	#pragma comment(lib, "opencv_flann248.lib")	

	#pragma comment(lib, "CrashRpt1402.lib")
#endif

// crashRPT
BOOL WINAPI CrashCallback(LPVOID /*lpvState*/)
{  
	CString dateTime;
	dateTime.Format("Crash occurred at %s %s", CT_GetCurrentSysDate(), CT_GetCurrentSysTime());
	
	// Return TRUE to generate error report
	return CR_CB_DODEFAULT;
}

// CBodyNoteApp

BEGIN_MESSAGE_MAP(CBodyNoteApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// costruzione di CBodyNoteApp

CBodyNoteApp::CBodyNoteApp()
{
	// TODO: inserire qui il codice di costruzione.
	// Inserire l'inizializzazione significativa in InitInstance.
}


// L'unico e solo oggetto CBodyNoteApp

CBodyNoteApp theApp;


// Inizializzazione di CBodyNoteApp

BOOL CBodyNoteApp::InitInstance()
{
	// InitCommonControlsEx() è necessario in Windows XP se nel manifesto
	// di un'applicazione è specificato l'utilizzo di ComCtl32.dll versione 6 o successiva per attivare
	// gli stili visuali. In caso contrario, non sarà possibile creare finestre.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Effettuare questa impostazione in modo da includere tutte le classi di controlli comuni da utilizzare
	// nell'applicazione.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Inizializzazione standard
	// Se non si utilizzano queste funzionalità e si desidera ridurre la dimensione
	// dell'eseguibile finale, è necessario rimuovere dal seguente codice
	// le specifiche routine di inizializzazione che non sono necessarie.
	// Modificare la chiave del Registro di sistema in cui sono memorizzate le impostazioni
	// TODO: è necessario modificare questa stringa in modo appropriato,
	// inserendo ad esempio il nome della società o dell'organizzazione.
	SetRegistryKey(_T("BodyNote - Scriba"));

	Initkey();

	/////////////////////////// license
#ifdef BODYNOTE_SOFTKEY
	CHardcodeLicenseManager hcm(m_keyCrypt);
	int nLic = hcm.LoadLicenses();
	if (nLic == 0)
	{
		AfxMessageBox("Nessuna licenza trovata!", MB_ICONERROR);
		return FALSE;
	}

	char appDrive[8];
	char appName[4096];
	GetModuleFileName(NULL, appName, 4096);
	_splitpath_s(appName, appDrive, 8, NULL, 0, NULL, 0, NULL, 0);

	CLicense FirstLic;
	if (!hcm.GetLicense(FirstLic))		
	{
		AfxMessageBox("Licenza non valida!", MB_ICONERROR);
		return FALSE;
	}

	CString serial = CT_GetDriveSerial(appDrive);
	if (FirstLic.m_ProtectionCode.CompareNoCase(serial) != 0)
	{
		AfxMessageBox("Licenza non valida!", MB_ICONERROR);
		return FALSE;
	}

	/////////////////////////// password
	char drive[8];
	char path[2048];
	char modFname[4096];
	GetModuleFileName(NULL, modFname, 4096);
	_splitpath_s(modFname, drive, 8, path, 2048, NULL, 0, NULL, 0);

	char secretPath[4096];
	_makepath_s(secretPath, 4096, drive, path, "secret", ".txt");

	CFileFind ff;
	BOOL bFound = ff.FindFile(secretPath);
	ff.Close();
	if (!bFound)
	{
		AfxMessageBox("Impossibile autenticare l'utente!", MB_ICONERROR);
		return FALSE;
	}

	char curPsw[64];
	memset(curPsw, 0, 64);
	
	CryptDecryptFile(secretPath, FALSE, FALSE);
	FILE* pFileSecret = NULL;
	fopen_s(&pFileSecret, secretPath, "r");
	if (!pFileSecret)
	{
		AfxMessageBox("Impossibile autenticare l'utente!", MB_ICONERROR);
		return FALSE;
	}
	fgets(curPsw, 64, pFileSecret);
	fclose(pFileSecret);
	CryptDecryptFile(secretPath, TRUE, FALSE);

	CAccessPasswordDlg passDlg(curPsw);
	if (passDlg.DoModal() == IDCANCEL)
	{
		AfxMessageBox("Password non valida!", MB_ICONHAND);		
		return FALSE;
	}
#else
#ifndef _DEBUG
	AfxMessageBox("Copia trial di BodyNote. Senza licenza d'uso");
#endif
#endif


/////////////////////////////////////////////////////////////
// CrashRPT - start
/////////////////////////////////////////////////////////////
#ifndef _DEBUG
	// Define CrashRpt configuration parameters
	CR_INSTALL_INFO info;  
	memset(&info, 0, sizeof(CR_INSTALL_INFO));  
	info.cb = sizeof(CR_INSTALL_INFO);    
	info.pszAppName = _T("BodyNote");
	info.pszEmailSubject = _T("BodyNote crash");
	info.pszEmailTo = _T("claudio.tortorelli@gmail.com");
	info.pszSmtpProxy = _T("smtp.gmail.com:587");
	//info.pszSmtpLogin = _T("claudio.tortorelli@gmail.com");
	//char pw[24];
	//ZeroMemory(pw, 24);
	//pw[0] = 'T';
	//pw[1] = 'u';
	//pw[2] = 'r';
	//pw[3] = 'i';
	//pw[4] = 'n';
	//pw[5] = 'g';
	//pw[6] = '1';
	//pw[7] = '9';
	//pw[8] = '7';
	//pw[9] = '8';
	//info.pszSmtpPassword= _T(pw);

	CString prodVer;
	CT_GetVersionInfo(NULL, prodVer, prodVer);
	info.pszAppVersion = prodVer;  
	info.pfnCrashCallback = CrashCallback;   
	// Install all available exception handlers, use HTTP binary transfer encoding (recommended).
#if _MSC_VER >= 1700
	info.dwFlags |= CR_INST_ALL_POSSIBLE_HANDLERS; // 1.4.0
#else
	info.dwFlags |= CR_INST_ALL_EXCEPTION_HANDLERS;
#endif
	info.dwFlags |= CR_INST_HTTP_BINARY_ENCODING; 
	//info.dwFlags |= CR_INST_APP_RESTART; 
	//info.dwFlags |= CR_INST_DONT_SEND_REPORT;
	//info.dwFlags |= CR_INST_SEND_MANDATORY;
	info.dwFlags |= CR_INST_SHOW_ADDITIONAL_INFO_FIELDS;
	//info.dwFlags |= CR_INST_SEND_QUEUED_REPORTS; 
	//info.pszRestartCmdLine = _T("/restart");

	info.uPriorities[CR_SMTP] = 3;  // First try send report over HTTP 
	info.uPriorities[CR_HTTP] = 2;  // Second try send report over SMTP  
	info.uPriorities[CR_SMAPI] = 1; // Third try send report over Simple MAPI  
 
	// Install exception handlers
	int nResult = crInstall(&info);    
	if(nResult!=0)  
	{    
		// Something goes wrong. Get error message.
		TCHAR szErrorMsg[512] = _T("");        
		crGetLastErrorMsg(szErrorMsg, 512);    
		_tprintf_s(_T("%s\n"), szErrorMsg);  
		::MessageBox(NULL, szErrorMsg, "error", MB_ICONERROR);
		return FALSE;
	} 
	crAddScreenshot2(CR_AS_VIRTUAL_SCREEN, 0);
/////////////////////////////////////////////////////////////
// CrashRPT - end
/////////////////////////////////////////////////////////////
		
	//crEmulateCrash(CR_SEH_EXCEPTION);
#endif
	
	CBodyNoteDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: inserire qui il codice per gestire la chiusura della finestra di dialogo 
		//  tramite il pulsante OK.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: inserire qui il codice per gestire la chiusura della finestra di dialogo 
		//  tramite il pulsante Annulla.
	}

	// Poiché la finestra di dialogo è stata chiusa, restituisce FALSE in modo che l'applicazione
	//  venga terminata, anziché avviare il message pump dell'applicazione.
	return FALSE;
}

void CBodyNoteApp::Initkey()
{
	memset(m_keyCrypt, 0, 16);
	m_keyCrypt[0] = 'e';
	m_keyCrypt[1] = 'h';
	m_keyCrypt[2] = '3';
	m_keyCrypt[3] = '2';
	m_keyCrypt[4] = 's';
	m_keyCrypt[5] = 'z';
	m_keyCrypt[6] = 'm';
	//m_keyCrypt[7] = '';
	//m_keyCrypt[8] = '';
	//m_keyCrypt[9] = '';
	//m_keyCrypt[10] = '';
	//m_keyCrypt[11] = '';
	//m_keyCrypt[12] = '';
	//m_keyCrypt[13] = '';
	//m_keyCrypt[13] = '';
	//m_keyCrypt[13] = '';
	//m_keyCrypt[14] = '';
	//m_keyCrypt[15] = '';
}

BOOL CBodyNoteApp::CryptDecryptFile(CString filePath, BOOL bCrypt, BOOL doBackup)
{
	BOOL bRet = FALSE;

	//BOOL isCrypted = IsIndexCrypted(filePath);
	CT_SetCustomKey(m_keyCrypt);
	if (bCrypt)
		bRet = CT_DoCrypt(filePath, filePath);
	else 
	{
		if (doBackup && !MakeBackup(filePath))
			return false;
		bRet = CT_DoDecrypt(filePath, filePath);
	}
	return bRet;
}


int get_file_size(std::string filename) // path to file
{
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(),"rb");
	if (!p_file)
		return 0;
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}

BOOL CBodyNoteApp::UpdatePatientIndex(CString workSpaceFolder, CProgressCtrl* pProgress)
{
	if (workSpaceFolder.IsEmpty())
		return FALSE;

	CString indexPath;
	indexPath.Format("%s\\dbIndex.txt", workSpaceFolder);

	FILE* pIndexFile = NULL;
	fopen_s(&pIndexFile, indexPath, "w+");
	if (!pIndexFile)
		return FALSE;

	CString searchPath;
	searchPath.Format("%s\\*.*", workSpaceFolder);

	BeginWaitCursor();

	CPatientRecord curPatient;

	char drive[8];
	char path[4096];
	char dataPath[4096];

	int recCount = 0;
	CFileFind ff;
	BOOL bFound = ff.FindFile(searchPath);
	while(bFound)
	{
		bFound = ff.FindNextFile();
		if (ff.IsDots())
			continue;
		if (!ff.IsDirectory())
			continue;

		recCount++;
	}

	if (pProgress)
	{
		pProgress->SetRange(0, recCount);
		pProgress->SetPos(0);
	}

	int maxId = 0;

	CTime now = CTime::GetCurrentTime();
	CString dateNow;
	dateNow.Format("%02d-%02d-%04d", now.GetDay(), now.GetMonth(), now.GetYear()); 

	recCount = 0;
	bFound = ff.FindFile(searchPath);
	while(bFound)
	{
		bFound = ff.FindNextFile();
		if (ff.IsDots())
			continue;
		if (!ff.IsDirectory())
			continue;

		recCount++;

		if (pProgress && (recCount%5 == 0))
			pProgress->SetPos(recCount);

		_splitpath_s(CT_OptimizePath(ff.GetFilePath(), TRUE), drive, 8, path, 4096, NULL, 0, NULL, 0);
		_makepath_s(dataPath, 4096, drive, path, "data", ".ini");

		char line[1024];
		if (get_file_size(dataPath) == 0)
		{			
			CString dataTmp = dataPath;
			dataTmp.Replace("data.ini", "");
			dataTmp = dataTmp.TrimRight('\\');
			int slashI = dataTmp.ReverseFind('\\');
			CString rId = dataTmp.Right(dataTmp.GetLength() - slashI - 1);

			// fix data.ini a zero, restore anonymous patient
			sprintf_s(line, "%s|%s|%s|%s\n", rId, "Cognome", "Nome", dateNow);
			fputs(line, pIndexFile);			

			curPatient.m_Nome = "Nome";
			curPatient.m_Cognome = "Cognome";
			curPatient.m_DataCreazione = dateNow;
			curPatient.m_ID = atoi(rId);

			curPatient.ToFile(dataPath);
			CryptDecryptFile(dataPath, TRUE, FALSE);
			continue;
		}

		CryptDecryptFile(dataPath, FALSE); // test decrypt
		if (curPatient.FromFile(dataPath) && curPatient.IsValid(FALSE))
		{
			sprintf_s(line, "%d|%s|%s|%s\n", curPatient.m_ID, curPatient.m_Cognome, curPatient.m_Nome, curPatient.m_DataCreazione);
			fputs(line, pIndexFile);
			CryptDecryptFile(dataPath, TRUE);

			maxId = _max(maxId, curPatient.m_ID);
		}
	}
	ff.Close();
	fclose(pIndexFile);
	
	if (pProgress)
		pProgress->SetPos(0);
	EndWaitCursor();

	if (!CryptDecryptFile(indexPath, TRUE))
		return FALSE;
	return TRUE;
}

BOOL CBodyNoteApp::MakeBackup(CString filePath)
{
	CFileFind ff;
	BOOL bFound = ff.FindFile(filePath);
	ff.Close();
	if (!bFound)
		return FALSE;

	char drive[8];
	char path[2048];
	char name[1024];
	char ext[8];
	_splitpath_s(filePath, drive, 8, path, 2048, name, 1024, ext, 8);

	CTime now = CTime::GetCurrentTime();
	CString dateNow;
	dateNow.Format("%s_%04d-%02d-%02d_%02d", name, now.GetYear(), now.GetMonth(), now.GetDay(), now.GetHour());

	char newPath[4096];
	_makepath_s(newPath, 4096, drive, path, dateNow, ext);

	bFound = ff.FindFile(newPath);
	ff.Close();
	if (!bFound)
		CopyFile(filePath, newPath, false); 
	return TRUE;
}


int CBodyNoteApp::LoadPatientIndex(CString workSpaceFolder, CArray<patientIndex, patientIndex>* pDBPatients, CProgressCtrl* pProgress)
{
	if (workSpaceFolder.IsEmpty() || !pDBPatients)
		return 0;

	pDBPatients->RemoveAll();

	CString indexPath;
	indexPath.Format("%s\\dbIndex.txt", workSpaceFolder);

	CFileFind ff;
	BOOL bFound = ff.FindFile(indexPath);
	ff.Close();
	
	if (!bFound)
	{
		if (!UpdatePatientIndex(workSpaceFolder, pProgress))
			return 0;
	}
	if (!CryptDecryptFile(indexPath, FALSE))
		return 0;
	
	FILE* pIndexFile = NULL;
	fopen_s(&pIndexFile, indexPath, "r");
	if (!pIndexFile)
	{
		CryptDecryptFile(indexPath, TRUE);
		return 0;
	}	

	while (!feof(pIndexFile))
	{
		char line[1024];
		ZeroMemory(line, 1024);
		CStringArray parsed;
		fgets(line, 1024, pIndexFile);
		if (CT_ParseString(line, '|', &parsed) != 4)
			continue;
		patientIndex ptIndex;
		ptIndex.id = atoi(parsed[0]);
		ptIndex.surname = parsed[1];
		ptIndex.name = parsed[2];
		parsed[3].Remove('\n');
		ptIndex.creation = parsed[3];
		pDBPatients->Add(ptIndex);
	}
	fclose(pIndexFile);
	CryptDecryptFile(indexPath, TRUE);
	return pDBPatients->GetSize();
}


int CBodyNoteApp::GetGlobalID()
{
	if (m_WorkSpaceFolder.IsEmpty())
		return 0;

	int maxId = 0;
	CString filter;
	filter.Format("%s\\*.*", m_WorkSpaceFolder);
	CFileFind ff;
	BOOL bFound = ff.FindFile(filter);
	while(bFound)
	{
		bFound = ff.FindNextFile();
		if (ff.IsDots())
			continue;
		if (!ff.IsDirectory())
			continue;

		CString dirPath = CT_OptimizePath(ff.GetFilePath(), TRUE);
		char drive[8];
		char path[2048];
		_splitpath_s(dirPath, drive, 8, path, 2048, NULL, 0, NULL, 0);

		CString nFold(path);
		if (nFold[nFold.GetLength()-1] == '\\')
			nFold = nFold.Left(nFold.GetLength()-1);

		for (int i = nFold.GetLength()-1; i >= 0; i--)
		{
			char c = nFold[i];
			if (c == '\\')
			{
				CString idS = nFold.Right(nFold.GetLength()-i-1);
				maxId = max(maxId, atoi(idS));
				break;
			}
		}
	}
	ff.Close();
	return maxId;
}


int CBodyNoteApp::DoWSBackup()
{
	if (m_WorkSpaceFolder.IsEmpty())
		return 0;

	CString destFolder;
	destFolder.Format("%s\\weekBackup", m_WorkSpaceFolder);
	CString destFolderTmp;
	destFolderTmp.Format("%s\\weekBackupTmp", m_WorkSpaceFolder);
	rename(destFolder, destFolderTmp);

	CreateDirectory(destFolder, NULL);

	CBackupProgressDlg* pProgressDlg = new CBackupProgressDlg();
	pProgressDlg->Create(CBackupProgressDlg::IDD);

	int count = 0;
	CString filter;
	filter.Format("%s\\*.*", m_WorkSpaceFolder);
	CFileFind ff;
	BOOL bFound = ff.FindFile(filter);
	while(bFound)
	{
		bFound = ff.FindNextFile();
		if (ff.IsDots())
			continue;
		if (!ff.IsDirectory())
			continue;
		CString dirPath = CT_OptimizePath(ff.GetFilePath(), TRUE);
		if (dirPath.Find("Backup") >= 0)
			continue;
		count++;
	}
	
	pProgressDlg->m_Progress_Ctrl.SetRange32(0, count);
	pProgressDlg->m_Progress_Ctrl.SetPos(0);
	pProgressDlg->ShowWindow(SW_SHOW);

	int toCopy = count;
	int wellCopied = 0;
	count = 0;
	
	bFound = ff.FindFile(filter);
	while(bFound)
	{
		bFound = ff.FindNextFile();
		if (ff.IsDots())
			continue;
		if (!ff.IsDirectory())
			continue;
		pProgressDlg->m_Progress_Ctrl.SetPos(count++);

		CString dirPath = CT_OptimizePath(ff.GetFilePath(), TRUE);
		if (dirPath.Find("Backup") >= 0)
			continue;

		char drive[8];
		char path[2048];
		_splitpath_s(dirPath, drive, 8, path, 2048, NULL, 0, NULL, 0);

		CString nFold(path);
		if (nFold[nFold.GetLength()-1] == '\\')
			nFold = nFold.Left(nFold.GetLength()-1);

		CString idS;
		for (int i = nFold.GetLength()-1; i >= 0; i--)
		{
			char c = nFold[i];
			if (c == '\\')
			{
				idS = nFold.Right(nFold.GetLength()-i-1);
				break;
			}
		}
		CString backFolder;
		backFolder.Format("%s\\%s", destFolder, idS);
		if (CT_CopyDirectory(dirPath, backFolder, TRUE))
			wellCopied++;
	}
	ff.Close();

	if (pProgressDlg && ::IsWindow(pProgressDlg->GetSafeHwnd()))
		pProgressDlg->DestroyWindow();
	delete pProgressDlg;
	pProgressDlg = NULL;

	CT_DeleteDirectory(destFolderTmp);
	return (wellCopied == toCopy);
}

BOOL CBodyNoteApp::LoadPatient(patientIndex pat, CPatientRecord& patient)
{
	CString dataPath;
	dataPath.Format("%s\\%ld\\data.ini", m_WorkSpaceFolder, pat.id);
	
	CFileFind ff;
	BOOL bFound = ff.FindFile(dataPath);
	ff.Close();

	if (!bFound)
		return FALSE;

	CryptDecryptFile(dataPath, FALSE); 
	if (patient.FromFile(dataPath) && patient.IsValid(FALSE))
		CryptDecryptFile(dataPath, TRUE);
	else
		return FALSE;
	return TRUE;
}

/***
 * deprecata
 */
int CBodyNoteApp::GetPatientDB(CString workSpaceFolder, CArray<CPatientRecord, CPatientRecord>* pDBPatients, CProgressCtrl* pProgress, BOOL bForceCrypt)
{
	if (workSpaceFolder.IsEmpty() || !pDBPatients)
		return 0;

	pDBPatients->RemoveAll();

	CString searchPath;
	searchPath.Format("%s\\*.*", workSpaceFolder);

	BeginWaitCursor();

	CPatientRecord curPatient;

	char drive[8];
	char path[4096];
	char dataPath[4096];

	int recCount = 0;
	CFileFind ff;
	BOOL bFound = ff.FindFile(searchPath);
	while(bFound)
	{
		bFound = ff.FindNextFile();
		if (ff.IsDots())
			continue;
		if (!ff.IsDirectory())
			continue;

		recCount++;
	}

	if (pProgress)
	{
		pProgress->SetRange(0, recCount);
		pProgress->SetPos(0);
	}

	recCount = 0;
	bFound = ff.FindFile(searchPath);
	while(bFound)
	{
		bFound = ff.FindNextFile();
		if (ff.IsDots())
			continue;
		if (!ff.IsDirectory())
			continue;

		if (pProgress)
			pProgress->SetPos(recCount++);

		_splitpath_s(CT_OptimizePath(ff.GetFilePath(), TRUE), drive, 8, path, 4096, NULL, 0, NULL, 0);
		_makepath_s(dataPath, 4096, drive, path, "data", ".ini");

		CryptDecryptFile(dataPath, FALSE); // test decrypt
		if (curPatient.FromFile(dataPath) && curPatient.IsValid(FALSE))
		{
			pDBPatients->Add(curPatient);
			CryptDecryptFile(dataPath, TRUE);
		}
		else
		{
			CryptDecryptFile(dataPath, TRUE); // restore status and try to read
			if (curPatient.FromFile(dataPath) && curPatient.IsValid(FALSE))
			{
				pDBPatients->Add(curPatient);
				if (bForceCrypt)
					CryptDecryptFile(dataPath, TRUE); // put crypt status
			}
		}
	}
	ff.Close();

	if (pProgress)
		pProgress->SetPos(0);

	EndWaitCursor();
	return pDBPatients->GetSize();
}

void CBodyNoteApp::RecursiveFileList(CString rootFolder, std::vector<string>& paths)
{
   CFileFind finder;

   // build a string with wildcards
   CString strWildcard(rootFolder);
   strWildcard += _T("\\*.*");

   // start working for files
   BOOL bWorking = finder.FindFile(strWildcard);

   while (bWorking)
   {
      bWorking = finder.FindNextFile();

      // skip . and .. files; otherwise, we'd 
      // recur infinitely! 

      if (finder.IsDots())
         continue;

      // if it's a directory, recursively search it 

      if (finder.IsDirectory())
      {
         CString str = finder.GetFilePath();
		 std::string curPath = std::string(str);
		 paths.push_back(curPath);
         RecursiveFileList(str, paths);
      }
   }

   finder.Close();
}

CString CBodyNoteApp::GetExecFolder()
{
	char appName[4096];
	GetModuleFileName(NULL, appName, 4096);
	char execFolder[4096];

	char drive[8];
	char path[2048];
	
	_splitpath_s(appName, drive, 8, path, 2048, NULL, 0, NULL, 0);
	_makepath_s(execFolder, 4096, drive, path, NULL, NULL);
	return execFolder;
}

int CBodyNoteApp::ExitInstance()
{
	crUninstall();

	return CWinApp::ExitInstance();
}


CString CBodyNoteApp::GetLastErrorString(DWORD errCode) 
{ 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
	LPTSTR lpszFunction = "";

    DWORD dw = GetLastError(); 
	if (errCode >= 0)
		dw = errCode;

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
		StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 

	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

	CString msg = (LPCTSTR)lpDisplayBuf;

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
	return msg;
}

// not working...
BOOL CBodyNoteApp::IsIndexCrypted(CString indexPath) 
{ 
	FILE* pIndexFile = NULL;
	fopen_s(&pIndexFile, indexPath, "r");
	if (!pIndexFile)
		return FALSE;

	BOOL ret = TRUE;
	try {
		while (!feof(pIndexFile))
		{
			char line[1024];			
			CStringArray parsed;
			fgets(line, 1024, pIndexFile);
			if (CT_ParseString(line, '|', &parsed) != 4)
				continue;
			patientIndex ptIndex;
			ptIndex.id = atoi(parsed[0]);
			ptIndex.surname = parsed[1];
			ptIndex.name = parsed[2];
			parsed[3].Remove('\n');
			ptIndex.creation = parsed[3];
			break;
		}
	} catch (exception ex) {
		ret = FALSE;
	} 
	fclose(pIndexFile);
	return ret;
}