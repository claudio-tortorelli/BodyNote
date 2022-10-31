// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BodyNote.h"
#include "SettingsDlg.h"

// CSettingsDlg dialog

IMPLEMENT_DYNAMIC(CSettingsDlg, CDialog)

CSettingsDlg::CSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingsDlg::IDD, pParent)
{

}

CSettingsDlg::~CSettingsDlg()
{
}

void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_WROKSPACEFOLDER, m_EditWorkspaceFolder_Ctrl);
	DDX_Control(pDX, IDC_EDIT_PW1, m_EditPsw1_Ctrl);
	DDX_Control(pDX, IDC_EDIT_PW2, m_EditPsw2_Ctrl);
	DDX_Control(pDX, IDC_CHECK_SHOTSOUND, m_CheckPlayShotSound_Ctrl);
	DDX_Control(pDX, IDC_CHECK_BACKWEEK, m_CheckWeek_Ctrl);
	DDX_Control(pDX, IDC_CHECK_BACKMONTH, m_CheckMonth_Ctrl);
}


BEGIN_MESSAGE_MAP(CSettingsDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PICKFOLDER, &CSettingsDlg::OnBnClickedButtonPickfolder)
	ON_BN_CLICKED(IDOK, &CSettingsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_BACKWEEK, &CSettingsDlg::OnBnClickedCheckBackweek)
	ON_BN_CLICKED(IDC_CHECK_BACKMONTH, &CSettingsDlg::OnBnClickedCheckBackmonth)
END_MESSAGE_MAP()


// CSettingsDlg message handlers

BOOL CSettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	char curFolder[4096];

#ifdef SETTINGS_LOCATION_EXEC
	CString iniPath;
	iniPath.Format("%s\\BodyNote.ini", theApp.GetExecFolder());
	GetPrivateProfileString("BodyNoteSettings", "WorkSpace",  CT_GetSpecialFolder(CSIDL_COMMON_APPDATA, TRUE, TRUE), curFolder, 4096, iniPath);	
#else
	CT_GetUserProfileString("BodyNoteSettings", "WorkSpace",  CT_GetSpecialFolder(CSIDL_COMMON_APPDATA, TRUE, TRUE), curFolder, 4096);
#endif
	m_CurWsFolder = CString(curFolder);	
	m_EditWorkspaceFolder_Ctrl.SetWindowText(m_CurWsFolder);

	char shotSound[8];
#ifdef SETTINGS_LOCATION_EXEC
	GetPrivateProfileString("BodyNoteSettings", "ShotSound",  "1", shotSound, 8, iniPath);	
#else
	CT_GetUserProfileString("BodyNoteSettings", "ShotSound",  "1", shotSound, 8);
#endif
	m_CheckPlayShotSound_Ctrl.SetCheck(atoi(shotSound));

	char weekback[8];
#ifdef SETTINGS_LOCATION_EXEC
	GetPrivateProfileString("BodyNoteSettings", "WeekBackup",  "1", weekback, 8, iniPath);	
#else
	CT_GetUserProfileString("BodyNoteSettings", "WeekBackup",  "1", weekback, 8);
#endif
	m_CheckWeek_Ctrl.SetCheck(atoi(weekback));

	char monthback[8];
#ifdef SETTINGS_LOCATION_EXEC
	GetPrivateProfileString("BodyNoteSettings", "MonthBackup",  "1", monthback, 8, iniPath);	
#else
	CT_GetUserProfileString("BodyNoteSettings", "MonthBackup",  "1", monthback, 8);
#endif
	m_CheckMonth_Ctrl.SetCheck(atoi(monthback));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingsDlg::OnBnClickedButtonPickfolder()
{
	char curFolder[4096];
#ifdef SETTINGS_LOCATION_EXEC
	CString iniPath;
	iniPath.Format("%s\\BodyNote.ini", theApp.GetExecFolder());
	GetPrivateProfileString("BodyNoteSettings", "WorkSpace",  CT_GetSpecialFolder(CSIDL_COMMON_APPDATA, TRUE, TRUE), curFolder, 4096, iniPath);	
#else
	CT_GetUserProfileString("BodyNoteSettings", "WorkSpace",  CT_GetSpecialFolder(CSIDL_COMMON_APPDATA, TRUE, TRUE), curFolder, 4096);
#endif
	CString newFolder = CT_PickFolderPath("Selezionare la cartella di Workspace", curFolder, this->m_hWnd);
	if (newFolder.IsEmpty())
		return;
	m_EditWorkspaceFolder_Ctrl.SetWindowText(newFolder);
}

void CSettingsDlg::OnBnClickedOk()
{
	CString folder;
	m_EditWorkspaceFolder_Ctrl.GetWindowText(folder);
	if (folder.IsEmpty())
	{
		AfxMessageBox("Selezionare una cartella per il workspace!");
		return;
	}
	CString psw1;
	CString psw2;
	m_EditPsw1_Ctrl.GetWindowText(psw1);
	m_EditPsw2_Ctrl.GetWindowText(psw2);
	if (!psw1.IsEmpty() && !psw2.IsEmpty())
	{
		if (psw1.Compare(psw2) != 0)
		{
			AfxMessageBox("Verificare la password", MB_ICONEXCLAMATION);
			return;
		}
	}
	else if ((psw1.IsEmpty() && !psw2.IsEmpty()) || (!psw1.IsEmpty() && psw2.IsEmpty()))
	{
		AfxMessageBox("Inserire la password due volte", MB_ICONEXCLAMATION);
		return;
	}

	if (m_CurWsFolder.CompareNoCase(folder) != 0)
	{
		if (IDNO == AfxMessageBox("Attenzione: selezionando un'altra cartella di workspace, i dati relativi al precedente workspace non saranno più visibili.\nSi vuol proseguire?", MB_YESNO))
			return;
	}

#ifdef SETTINGS_LOCATION_EXEC
	CString iniPath;
	iniPath.Format("%s\\BodyNote.ini", theApp.GetExecFolder());
	WritePrivateProfileString("BodyNoteSettings", "WorkSpace", folder, iniPath);	
#else
	CT_WriteUserProfileString("BodyNoteSettings", "WorkSpace", folder);
#endif

	if (!psw1.IsEmpty())
	{
		char drive[8];
		char path[2048];
		char modFname[4096];
		GetModuleFileName(NULL, modFname, 4096);
		_splitpath_s(modFname, drive, 8, path, 2048, NULL, 0, NULL, 0);

		char secretPath[4096];
		_makepath_s(secretPath, 4096, drive, path, "secret", ".txt");

		FILE* pFile = NULL;
		fopen_s(&pFile, secretPath, "w+");
		if (!pFile)
		{
			AfxMessageBox("Impossibile aggiornare la password!");
		}
		else
		{
			fputs(psw1, pFile);
			fclose(pFile);
			theApp.CryptDecryptFile(secretPath);
		}
	}

	BOOL bShotSound = (m_CheckPlayShotSound_Ctrl.GetCheck() == BST_CHECKED);
#ifdef SETTINGS_LOCATION_EXEC
	if (bShotSound)
		WritePrivateProfileString("BodyNoteSettings", "ShotSound", "1", iniPath);	
	else
		WritePrivateProfileString("BodyNoteSettings", "ShotSound", "0", iniPath);
#else
	if (bShotSound)
		CT_WriteUserProfileString("BodyNoteSettings", "ShotSound", "1");
	else
		CT_WriteUserProfileString("BodyNoteSettings", "ShotSound", "0");
#endif
	
	OnOK();
}


void CSettingsDlg::OnBnClickedCheckBackweek()
{
	BOOL bCheck = (m_CheckWeek_Ctrl.GetCheck() == BST_CHECKED);
#ifdef SETTINGS_LOCATION_EXEC
	CString iniPath;
	iniPath.Format("%s\\BodyNote.ini", theApp.GetExecFolder());
	
	if (bCheck)
		WritePrivateProfileString("BodyNoteSettings", "WeekBackup", "1", iniPath);	
	else
		WritePrivateProfileString("BodyNoteSettings", "WeekBackup", "0", iniPath);
#else
	if (bShotSound)
		CT_WriteUserProfileString("BodyNoteSettings", "WeekBackup", "1");
	else
		CT_WriteUserProfileString("BodyNoteSettings", "WeekBackup", "0");
#endif
}


void CSettingsDlg::OnBnClickedCheckBackmonth()
{
	BOOL bCheck = (m_CheckMonth_Ctrl.GetCheck() == BST_CHECKED);
#ifdef SETTINGS_LOCATION_EXEC
	CString iniPath;
	iniPath.Format("%s\\BodyNote.ini", theApp.GetExecFolder());
	
	if (bCheck)
		WritePrivateProfileString("BodyNoteSettings", "MonthBackup", "1", iniPath);	
	else
		WritePrivateProfileString("BodyNoteSettings", "MonthBackup", "0", iniPath);
#else
	if (bShotSound)
		CT_WriteUserProfileString("BodyNoteSettings", "MonthBackup", "1");
	else
		CT_WriteUserProfileString("BodyNoteSettings", "MonthBackup", "0");
#endif
}
