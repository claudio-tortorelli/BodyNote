// BodyNoteDlg.cpp : file di implementazione
//

#include "stdafx.h"
#include "BodyNote.h"
#include "BodyNoteDlg.h"
#include "SelectPatientDlg.h"
#include "cv.h"
#include "highgui.h"
#include "SettingsDlg.h"
#include "Mmsystem.h"
#include "afxwin.h"
#include "MoreDataDlg.h"
#include "AddDocumentDlg.h"
#include "OpenDocDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_INIT 0
// finestra di dialogo CAboutDlg utilizzata per visualizzare le informazioni sull'applicazione.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dati della finestra di dialogo
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // supporto DDX/DDV

// Implementazione
protected:
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_StaticVer_Ctrl;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString fileVer, prodVer;
	CT_GetVersionInfo(NULL, prodVer, fileVer);
	CString ver;
	ver.Format("BodyNote - ver. %s", prodVer);
	m_StaticVer_Ctrl.SetWindowText(ver);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VER, m_StaticVer_Ctrl);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()





// finestra di dialogo CBodyNoteDlg
CBodyNoteDlg::CBodyNoteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBodyNoteDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bStopWebCam = FALSE;
	m_CurCameraIndex = -1;
	m_pIplBlack = cvCreateImage(cvSize(100,100), IPL_DEPTH_8U, 1);
	cvZero(m_pIplBlack);

	m_picIndex = -1;

	m_bNewRec = FALSE;

#ifdef SETTINGS_LOCATION_EXEC
	CString iniPath;
	iniPath.Format("%s\\BodyNote.ini", theApp.GetExecFolder());
#endif


	char curFolder[4096];
#ifdef SETTINGS_LOCATION_EXEC
	GetPrivateProfileString("BodyNoteSettings", "WorkSpace", CT_GetSpecialFolder(CSIDL_COMMON_APPDATA, TRUE, TRUE), curFolder, 4096, iniPath);	
#else
	CT_GetUserProfileString("BodyNoteSettings", "WorkSpace",  CT_GetSpecialFolder(CSIDL_COMMON_APPDATA, TRUE, TRUE), curFolder, 4096);
#endif
 	theApp.m_WorkSpaceFolder = CString(curFolder);
	m_GlobalID = theApp.GetGlobalID();

	///
	// backup
	CTime now = CTime::GetCurrentTime();

	BOOL bBackupByTimeEnabled = false;
	
	char weekback[8];
	char lastBackDate[1024];
#ifdef SETTINGS_LOCATION_EXEC
	GetPrivateProfileString("BodyNoteSettings", "WeekBackup",  "0", weekback, 8, iniPath);	
	GetPrivateProfileString("BodyNoteSettings", "LastWeekBackup", "", lastBackDate, 1024, iniPath);	
#else
	CT_GetUserProfileString("BodyNoteSettings", "WeekBackup",  "0", weekback, 8);
	CT_GetUserProfileString("BodyNoteSettings", "LastWeekBackup", "", lastBackDate, 1024);
#endif

	if (atoi(weekback) == 1 && bBackupByTimeEnabled)
	{
		if (strlen(lastBackDate) == 0)
		{
			if (theApp.DoWSBackup())
			{
#ifdef SETTINGS_LOCATION_EXEC
				WritePrivateProfileString("BodyNoteSettings", "LastWeekBackup", CT_GetCurrentSysDate(), iniPath);	
#else
				CT_WriteUserProfileString("BodyNoteSettings", "LastWeekBackup", CT_GetCurrentSysDate());
#endif
			}
		}
		else
		{
			int y = atoi(CString(lastBackDate).Right(4));
			int m = atoi(CString(lastBackDate).Mid(3,2));
			int d = atoi(CString(lastBackDate).Left(2));
			CTime lastDate(y,m,d,0,0,0);
			CTimeSpan elapsedTime = now - lastDate;
			if (elapsedTime.GetDays() > 7)
			{
				if (theApp.DoWSBackup())
#ifdef SETTINGS_LOCATION_EXEC
				WritePrivateProfileString("BodyNoteSettings", "LastWeekBackup", CT_GetCurrentSysDate(), iniPath);	
#else
				CT_WriteUserProfileString("BodyNoteSettings", "LastWeekBackup", CT_GetCurrentSysDate());
#endif
			}
		}
	}///
	
	m_hExit[0] = AfxGetApp()->LoadIcon(IDI_ICON_EXIT);
	m_hExit[1] = AfxGetApp()->LoadIcon(IDI_ICON_EXITG);
	m_hShot[0] = AfxGetApp()->LoadIcon(IDI_ICON_SHOT);
	m_hShot[1] = AfxGetApp()->LoadIcon(IDI_ICON_SHOTG);
	m_hStart[0] = AfxGetApp()->LoadIcon(IDI_ICON_START);
	m_hStart[1] = AfxGetApp()->LoadIcon(IDI_ICON_STARTG);
	m_hStop[0] = AfxGetApp()->LoadIcon(IDI_ICON_STOP);
	m_hStop[1] = AfxGetApp()->LoadIcon(IDI_ICON_STOPG);
	m_hInfo[0] = AfxGetApp()->LoadIcon(IDI_ICON_ABOUT);
	m_hInfo[1] = AfxGetApp()->LoadIcon(IDI_ICON_ABOUTG);
	m_hSettings[0] = AfxGetApp()->LoadIcon(IDI_ICON_SETTINGS);
	m_hSettings[1] = AfxGetApp()->LoadIcon(IDI_ICON_SETTINGSG);
	m_hAdd[0] = AfxGetApp()->LoadIcon(IDI_ICON_ADD);
	m_hAdd[1] = AfxGetApp()->LoadIcon(IDI_ICON_ADDG);
	m_hRemove[0] = AfxGetApp()->LoadIcon(IDI_ICON_REMOVE);
	m_hRemove[1] = AfxGetApp()->LoadIcon(IDI_ICON_REMOVEG);
	m_hLoad[0] = AfxGetApp()->LoadIcon(IDI_ICON_LOAD);
	m_hLoad[1] = AfxGetApp()->LoadIcon(IDI_ICON_LOADG);
	m_hDetail[0] = AfxGetApp()->LoadIcon(IDI_ICON_DETAIL);
	m_hDetail[1] = AfxGetApp()->LoadIcon(IDI_ICON_DETAILG);
	m_hAddDoc[0] = AfxGetApp()->LoadIcon(IDI_ICON_ADDDOC);
	m_hAddDoc[1] = AfxGetApp()->LoadIcon(IDI_ICON_ADDDOCG);
	m_hViewDoc[0] = AfxGetApp()->LoadIcon(IDI_ICON_VIEWDOC);
	m_hViewDoc[1] = AfxGetApp()->LoadIcon(IDI_ICON_VIEWDOCG);
	
	m_bDirty = FALSE;
}

CBodyNoteDlg::~CBodyNoteDlg()
{
	if (m_pIplBlack)
		cvReleaseImage(&m_pIplBlack);

	DestroyIcon(m_hExit[0]);
	DestroyIcon(m_hExit[1]);
	DestroyIcon(m_hShot[0]);
	DestroyIcon(m_hShot[1]);
	DestroyIcon(m_hStart[0]);
	DestroyIcon(m_hStart[1]);
	DestroyIcon(m_hStop[0]);
	DestroyIcon(m_hStop[1]);
	DestroyIcon(m_hInfo[0]);
	DestroyIcon(m_hInfo[1]);
	DestroyIcon(m_hSettings[0]);
	DestroyIcon(m_hSettings[1]);
	DestroyIcon(m_hAdd[0]);
	DestroyIcon(m_hAdd[1]);
	DestroyIcon(m_hRemove[0]);
	DestroyIcon(m_hRemove[1]);
	DestroyIcon(m_hLoad[0]);
	DestroyIcon(m_hLoad[1]);
	DestroyIcon(m_hDetail[0]);
	DestroyIcon(m_hDetail[1]);
	DestroyIcon(m_hAddDoc[0]);
	DestroyIcon(m_hAddDoc[1]);
	DestroyIcon(m_hViewDoc[0]);
	DestroyIcon(m_hViewDoc[1]);
}

void CBodyNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CAM1, m_StaticCam_Ctrl[0]);
	DDX_Control(pDX, IDC_STATIC_CAM2, m_StaticCam_Ctrl[1]);
	DDX_Control(pDX, IDC_STATIC_CAM3, m_StaticCam_Ctrl[2]);
	DDX_Control(pDX, IDC_STATIC_CURCAMPIC, m_StaticCurCam_Ctrl);
	DDX_Control(pDX, IDC_CHECK_CAM1, m_CheckCam1_Ctrl);
	DDX_Control(pDX, IDC_CHECK_CAM2, m_CheckCam2_Ctrl);
	DDX_Control(pDX, IDC_CHECK_CAM3, m_CheckCam3_Ctrl);
	DDX_Control(pDX, IDC_BUTTON_STARTWEBCAM, m_ButtonStartWebCam_Ctrl);
	DDX_Control(pDX, IDC_BUTTON_STOPWEBCAM, m_ButtonStopWebCam_Ctrl);
	DDX_Control(pDX, IDOK, m_ButtonExit_Ctrl);
	DDX_Control(pDX, IDC_STATIC_CURCAMTITLE, m_StaticCurCamTitle_Ctrl);
	DDX_Control(pDX, IDC_BUTTON_SHOT, m_ButtonShot_Ctrl);
	DDX_Control(pDX, IDC_BUTTON_ABOUT, m_ButtonInfo_Ctrl);
	DDX_Control(pDX, IDC_EDIT_NAME, m_EditName_Ctrl);
	DDX_Control(pDX, IDC_EDIT_SURNAME, m_EditSurname_Ctrl);
	DDX_Control(pDX, IDC_EDIT_PHONE, m_EditPhone_Ctrl);
	DDX_Control(pDX, IDC_EDIT_EMAIL, m_EditEmail_Ctrl);
	DDX_Control(pDX, IDC_EDIT_AGE, m_EditAge_Ctrl);
	DDX_Control(pDX, IDC_COMBO_PICTURES, m_ComboPictures_Ctrl);
	DDX_Control(pDX, IDC_EDIT_COMMENT, m_EditComment_Ctrl);
	DDX_Control(pDX, IDC_CHECK_EDITDATA, m_CheckEditData_Ctrl);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_ButtonNewPatient_Ctrl);
	DDX_Control(pDX, IDC_BUTTON_LOAD, m_ButtonLoadPatient_Ctrl);
	DDX_Control(pDX, IDC_BUTTON_OPENPATIENTFOLDER, m_ButtonOpenPatientFolder_Ctrl);
	DDX_Control(pDX, IDC_BUTTON_DELETEPICTURE, m_ButtonDeletePictures_Ctrl);
	DDX_Control(pDX, IDC_EDIT_BIRTHDATE, m_BirthDate_Ctrl);	
	DDX_Control(pDX, IDC_BUTTON_DELPATIENT, m_ButtonDeleteCurPatient_Ctrl);
	DDX_Control(pDX, IDC_BUTTON_SETTINGS, m_ButtonSettings_Ctrl);
	DDX_Control(pDX, IDC_BUTTON_MOREDETAILS, m_ButtonDetails_Ctrl);
	DDX_Control(pDX, IDC_BUTTON_CARICADOC, m_ButtonCaricaDoc_Ctrl);
	DDX_Control(pDX, IDC_BUTTON_VEDIDOC, m_ButtonVediDoc_Ctrl);
	DDX_Control(pDX, IDC_PROGRESS_LOADARCHIVE, m_ProgressArchive_Ctrl);
}

BEGIN_MESSAGE_MAP(CBodyNoteDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CBodyNoteDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_STARTWEBCAM, &CBodyNoteDlg::OnBnClickedButtonStartwebcam)
	ON_BN_CLICKED(IDC_BUTTON_STOPWEBCAM, &CBodyNoteDlg::OnBnClickedButtonStopwebcam)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SHOT, &CBodyNoteDlg::OnBnClickedButtonShot)
	ON_BN_CLICKED(IDC_CHECK_CAM1, &CBodyNoteDlg::OnBnClickedCheckCam1)
	ON_BN_CLICKED(IDC_CHECK_CAM2, &CBodyNoteDlg::OnBnClickedCheckCam2)
	ON_BN_CLICKED(IDC_CHECK_CAM3, &CBodyNoteDlg::OnBnClickedCheckCam3)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, &CBodyNoteDlg::OnBnClickedButtonAbout)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CBodyNoteDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CBodyNoteDlg::OnBnClickedButtonNew)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CBodyNoteDlg::OnEnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_SURNAME, &CBodyNoteDlg::OnEnChangeEditSurname)
	ON_EN_CHANGE(IDC_EDIT_PHONE, &CBodyNoteDlg::OnEnChangeEditPhone)
	ON_EN_CHANGE(IDC_EDIT_EMAIL, &CBodyNoteDlg::OnEnChangeEditEmail)
	ON_EN_CHANGE(IDC_EDIT_VISITCAUSE, &CBodyNoteDlg::OnEnChangeEditVisitcause)
	ON_EN_CHANGE(IDC_EDIT_DIAGNOSIS, &CBodyNoteDlg::OnEnChangeEditDiagnosis)
	ON_EN_CHANGE(IDC_EDIT_COMMENT, &CBodyNoteDlg::OnEnChangeEditComment)
	ON_BN_CLICKED(IDC_CHECK_EDITDATA, &CBodyNoteDlg::OnBnClickedCheckEditdata)
	ON_BN_CLICKED(IDC_BUTTON_DELETEPICTURE, &CBodyNoteDlg::OnBnClickedButtonDeletepicture)
	ON_CBN_SELCHANGE(IDC_COMBO_PICTURES, &CBodyNoteDlg::OnCbnSelchangeComboPictures)
	ON_BN_CLICKED(IDC_BUTTON_OPENPATIENTFOLDER, &CBodyNoteDlg::OnBnClickedButtonOpenpatientfolder)
	ON_BN_CLICKED(IDC_BUTTON_DELPATIENT, &CBodyNoteDlg::OnBnClickedButtonDelpatient)
	ON_BN_CLICKED(IDC_BUTTON_SETTINGS, &CBodyNoteDlg::OnBnClickedButtonSettings)
	ON_COMMAND(ID_INPUT_INPUTDATA, &CBodyNoteDlg::OnInputInputdata)
	ON_BN_CLICKED(IDC_BUTTON_MOREDETAILS, &CBodyNoteDlg::OnBnClickedButtonMoredetails)
	ON_BN_CLICKED(IDC_BUTTON_CARICADOC, &CBodyNoteDlg::OnBnClickedButtonCaricadoc)
	ON_BN_CLICKED(IDC_BUTTON_VEDIDOC, &CBodyNoteDlg::OnBnClickedButtonVedidoc)
	ON_UPDATE_COMMAND_UI(ID_INPUT_INPUTDATA, &CBodyNoteDlg::OnUpdateInputInputdata)
	ON_UPDATE_COMMAND_UI(ID_INPUT_BACKUPARCHIVIO, &CBodyNoteDlg::OnUpdateInputBackuparchivio)
	ON_COMMAND(ID_INPUT_BACKUPARCHIVIO, &CBodyNoteDlg::OnInputBackuparchivio)
	ON_COMMAND(ID_DBTOOLS_AGGIORNADB, &CBodyNoteDlg::OnDbtoolsAggiornadb)
END_MESSAGE_MAP()


// gestori di messaggi di CBodyNoteDlg

BOOL CBodyNoteDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// IDM_ABOUTBOX deve trovarsi tra i comandi di sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Impostare l'icona per questa finestra di dialogo. Il framework non esegue questa operazione automaticamente
	//  se la finestra principale dell'applicazione non è una finestra di dialogo.
	SetIcon(m_hIcon, TRUE);			// Impostare icona grande.
	SetIcon(m_hIcon, FALSE);		// Impostare icona piccola.

	char buf[256];
#ifdef SETTINGS_LOCATION_EXEC
	CString iniPath;
	iniPath.Format("%s\\BodyNote.ini", theApp.GetExecFolder());
	GetPrivateProfileString("CameraEnabled", "Cam1", "1", buf, 256, iniPath);	
#else
	CT_GetUserProfileString("CameraEnabled", "Cam1", "1", buf, 256);
#endif
	if (atoi(buf))
		m_CheckCam1_Ctrl.SetCheck(BST_CHECKED);
	else
		m_CheckCam1_Ctrl.SetCheck(BST_UNCHECKED);

#ifdef SETTINGS_LOCATION_EXEC
	GetPrivateProfileString("CameraEnabled", "Cam2", "1", buf, 256, iniPath);	
#else
	CT_GetUserProfileString("CameraEnabled", "Cam2", "1", buf, 256);
#endif
	if (atoi(buf))
		m_CheckCam2_Ctrl.SetCheck(BST_CHECKED);
	else
		m_CheckCam2_Ctrl.SetCheck(BST_UNCHECKED);

#ifdef SETTINGS_LOCATION_EXEC
	GetPrivateProfileString("CameraEnabled", "Cam3", "1", buf, 256, iniPath);	
#else
	CT_GetUserProfileString("CameraEnabled", "Cam3", "1", buf, 256);
#endif
	if (atoi(buf))
		m_CheckCam3_Ctrl.SetCheck(BST_CHECKED);
	else
		m_CheckCam3_Ctrl.SetCheck(BST_UNCHECKED);

	m_ButtonStopWebCam_Ctrl.EnableWindow(FALSE);
	m_ButtonShot_Ctrl.EnableWindow(FALSE);

	m_ButtonShot_Ctrl.SetIcon(m_hShot[0], m_hShot[1]);
	m_ButtonExit_Ctrl.SetIcon(m_hExit[0], m_hExit[1]);
	m_ButtonStartWebCam_Ctrl.SetIcon(m_hStart[0], m_hStart[1]);
	m_ButtonStopWebCam_Ctrl.SetIcon(m_hStop[0], m_hStop[1]);
	m_ButtonInfo_Ctrl.SetIcon(m_hInfo[0], m_hInfo[1]);
	m_ButtonSettings_Ctrl.SetIcon(m_hSettings[0], m_hSettings[1]);
	m_ButtonNewPatient_Ctrl.SetIcon(m_hAdd[0], m_hAdd[1]);
	m_ButtonDeleteCurPatient_Ctrl.SetIcon(m_hRemove[0], m_hRemove[1]);
	m_ButtonLoadPatient_Ctrl.SetIcon(m_hLoad[0], m_hLoad[1]);
	m_ButtonDetails_Ctrl.SetIcon(m_hDetail[0], m_hDetail[1]);
	m_ButtonCaricaDoc_Ctrl.SetIcon(m_hAddDoc[0], m_hAddDoc[1]);
	m_ButtonVediDoc_Ctrl.SetIcon(m_hViewDoc[0], m_hViewDoc[1]);

	m_ButtonOpenPatientFolder_Ctrl.EnableWindow(FALSE);
	m_ButtonDeletePictures_Ctrl.EnableWindow(FALSE);
	m_ComboPictures_Ctrl.EnableWindow(FALSE);

	m_StaticCurCam_Ctrl.SetEnableZoom(TRUE);

	CString prodVer, fileVer;
	CT_GetVersionInfo(NULL, prodVer, fileVer);

	CString caption;
	caption.Format("BodyNote - ver. %s - Scriba (c) - Gambini/Tortorelli", prodVer);
	SetWindowText(caption);

	SetTimer(TIMER_INIT, 200, NULL);
	return TRUE;  // restituisce TRUE a meno che non venga impostato lo stato attivo su un controllo.
}

void CBodyNoteDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Se si aggiunge alla finestra di dialogo un pulsante di riduzione a icona, per trascinare l'icona sarà necessario
//  il codice sottostante. Per le applicazioni MFC che utilizzano il modello documento/visualizzazione,
//  questa operazione viene eseguita automaticamente dal framework.

void CBodyNoteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contesto di dispositivo per il disegno

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrare l'icona nel rettangolo client.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Disegnare l'icona
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Il sistema chiama questa funzione per ottenere la visualizzazione del cursore durante il trascinamento
//  della finestra ridotta a icona.
HCURSOR CBodyNoteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBodyNoteDlg::OnBnClickedOk()
{
	BOOL bEdit = (m_CheckEditData_Ctrl.GetCheck() == BST_CHECKED);
	if (!bEdit)
		CDialog::OnOK();
}

BOOL CBodyNoteDlg::StartWebCam()
{
	CvCapture* pCvCap[nCam];
	for (int iCam = 0; iCam < nCam; iCam++)
		pCvCap[iCam] = NULL;

	m_CurCameraIndex = -1;
	BeginWaitCursor();
	if (m_CheckCam1_Ctrl.GetCheck() == BST_CHECKED)
	{
		pCvCap[0] = cvCaptureFromCAM(0);
		if (pCvCap[0] && m_CurCameraIndex < 0)
			m_CurCameraIndex = 0;
	}
	if (m_CheckCam2_Ctrl.GetCheck() == BST_CHECKED)
	{
		pCvCap[1] = cvCaptureFromCAM(1);
		if (pCvCap[1] && m_CurCameraIndex < 0)
			m_CurCameraIndex = 1;
	}
	if (m_CheckCam3_Ctrl.GetCheck() == BST_CHECKED)
	{
		pCvCap[2] = cvCaptureFromCAM(2);
		if (pCvCap[2] && m_CurCameraIndex < 0)
			m_CurCameraIndex = 2;
	}
	EndWaitCursor();
	
	if (!pCvCap[0] && !pCvCap[1] && !pCvCap[2])
		return FALSE;
	
	IplImage* pIplWebcam[nCam];
	for (int iCam = 0; iCam < nCam; iCam++)
		pIplWebcam[iCam] = NULL;
	
	CString title;
	title.Format("Camera Corrente: %02d", m_CurCameraIndex+1);
	m_StaticCurCamTitle_Ctrl.SetWindowText(title);
	
	int nFrameRate = 40;
	int iFrame = 0;
	for(;;) 
	{
		if(m_bStopWebCam)
			break; // if ESC, break and quit

		CT_PumpMessages();
		if (iFrame%nFrameRate == 0)
		{
			for (int iCam = 0; iCam < nCam; iCam++)
			{
				if (!pCvCap[iCam])
					continue;
				pIplWebcam[iCam] = cvQueryFrame(pCvCap[iCam]); // get frame
				if(pIplWebcam[iCam] != 0)
					m_StaticCam_Ctrl[iCam].SetImage(pIplWebcam[iCam]);				
			}
		}
		iFrame++;

		if (m_CurCameraIndex >= 0 && pCvCap[m_CurCameraIndex])
		{
			pIplWebcam[m_CurCameraIndex] = cvQueryFrame(pCvCap[m_CurCameraIndex]); // get frame		
			m_StaticCurCam_Ctrl.SetImage(pIplWebcam[m_CurCameraIndex]);
		}
		else
			m_StaticCurCam_Ctrl.SetImage(m_pIplBlack);
		
		if(m_bStopWebCam)
			break; // if ESC, break and quit
	}
	/* clean up */
	for (int iCam = 0; iCam < nCam; iCam++)
	{
		if (pCvCap[iCam])
			cvReleaseCapture( &pCvCap[iCam]);
	}
	
	for (int iCam = 0; iCam < nCam; iCam++)
		m_StaticCam_Ctrl[iCam].SetImage(m_pIplBlack);
	m_StaticCurCam_Ctrl.SetImage(m_pIplBlack);

	LoadComboPics(m_CurPatient);
	
	return TRUE;
}

void CBodyNoteDlg::OnBnClickedButtonStartwebcam()
{
	if (!m_CurPatient.IsValid())
	{
		AfxMessageBox("Caricare un paziente o crearne uno nuovo", MB_ICONINFORMATION);
		return;
	}

	m_StaticCurCam_Ctrl.SetEnableZoom(FALSE);

	m_bStopWebCam = FALSE;
	LockUI(TRUE);
	StartWebCam();
}

void CBodyNoteDlg::OnBnClickedButtonStopwebcam()
{
	m_bStopWebCam = TRUE;
	LockUI(FALSE);	
}

void CBodyNoteDlg::LockUI(BOOL bLock)
{
	m_CheckCam1_Ctrl.EnableWindow(!bLock);
	m_CheckCam2_Ctrl.EnableWindow(!bLock);
	m_CheckCam3_Ctrl.EnableWindow(!bLock);

	m_ButtonExit_Ctrl.EnableWindow(!bLock);
	m_ButtonStartWebCam_Ctrl.EnableWindow(!bLock);
	m_ButtonStopWebCam_Ctrl.EnableWindow(bLock);
	m_ButtonShot_Ctrl.EnableWindow(bLock);
	m_ButtonSettings_Ctrl.EnableWindow(!bLock);

	m_ButtonDeletePictures_Ctrl.EnableWindow(!bLock);
	m_ComboPictures_Ctrl.EnableWindow(!bLock);
	
	m_CheckEditData_Ctrl.EnableWindow(!bLock);

	m_ButtonDeleteCurPatient_Ctrl.EnableWindow(!bLock);	
	m_ButtonNewPatient_Ctrl.EnableWindow(!bLock);
	m_ButtonLoadPatient_Ctrl.EnableWindow(!bLock);	
}

void CBodyNoteDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	for (int iCam = 0; iCam < nCam; iCam++)
	{
		CRect winRect;
		m_StaticCam_Ctrl[iCam].GetWindowRect(&winRect);
		ScreenToClient(&winRect);
		if (winRect.PtInRect(point))
		{
			m_CurCameraIndex = iCam;
			break;
		}
	}
	if (!m_ButtonStartWebCam_Ctrl.IsWindowEnabled())
	{
		CString title;
		title.Format("Camera Corrente: %02d", m_CurCameraIndex+1);
		m_StaticCurCamTitle_Ctrl.SetWindowText(title);
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CBodyNoteDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
		case TIMER_INIT:
		{
			KillTimer(0);
			for (int iCam = 0; iCam < nCam; iCam++)
				m_StaticCam_Ctrl[iCam].SetImage(m_pIplBlack);
			m_StaticCurCam_Ctrl.SetImage(m_pIplBlack);
			break;
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CBodyNoteDlg::OnBnClickedButtonShot()
{
	CString patientFolder;
	patientFolder.Format("%s\\%ld", theApp.m_WorkSpaceFolder, m_CurPatient.m_ID);
	patientFolder = CT_OptimizePath(patientFolder, TRUE);
	CreateDirectory(patientFolder, NULL);
	
	CString imgName;
	int imgCount = 1;
	CString patientPicPath;
		
	BOOL bFound = TRUE;
	while (bFound)
	{
		imgName.Format("%s_%d.jpg", CT_GetCurrentSysDate(), imgCount++);
		
		patientPicPath.Format("%s%s", patientFolder, imgName);
		patientPicPath = CT_OptimizePath(patientPicPath, FALSE);
		CFileFind ff;
		bFound = ff.FindFile(patientPicPath);
		ff.Close();
	}
	m_StaticCurCam_Ctrl.SaveOrigImage(patientPicPath);
		
	theApp.CryptDecryptFile(patientPicPath, TRUE);

	char shotSound[8];
#ifdef SETTINGS_LOCATION_EXEC
	CString iniPath;
	iniPath.Format("%s\\BodyNote.ini", theApp.GetExecFolder());
	GetPrivateProfileString("BodyNoteSettings", "ShotSound",  "1", shotSound, 8, iniPath);	
#else
	CT_GetUserProfileString("BodyNoteSettings", "ShotSound",  "1", shotSound, 8);
#endif
	
	if (atoi(shotSound))
	{
		char drive[8];
		char path[4096];
		char appName[4096];
		GetModuleFileName(NULL, appName, 4096);
		_splitpath_s(appName, drive, 8,  path, 4096, NULL, 0, NULL, 0);
		char clickPath[4096];
		_makepath_s(clickPath, 4096, drive, path, "camera1", ".wav");
		PlaySound(TEXT(clickPath), NULL, SND_FILENAME);
	}	
}

void CBodyNoteDlg::OnBnClickedCheckCam1()
{
	BOOL bCheck = (BST_CHECKED == m_CheckCam1_Ctrl.GetCheck());

#ifdef SETTINGS_LOCATION_EXEC
	CString iniPath;
	iniPath.Format("%s\\BodyNote.ini", theApp.GetExecFolder());
	if (bCheck)
		WritePrivateProfileString("CameraEnabled", "Cam1", "1", iniPath);
	else
		WritePrivateProfileString("CameraEnabled", "Cam1", "0", iniPath);
#else
	if (bCheck)
		CT_WriteUserProfileString("CameraEnabled", "Cam1", "1");
	else
		CT_WriteUserProfileString("CameraEnabled", "Cam1", "0");
#endif
}

void CBodyNoteDlg::OnBnClickedCheckCam2()
{
	BOOL bCheck = (BST_CHECKED == m_CheckCam2_Ctrl.GetCheck());
#ifdef SETTINGS_LOCATION_EXEC
	CString iniPath;
	iniPath.Format("%s\\BodyNote.ini", theApp.GetExecFolder());
	if (bCheck)
		WritePrivateProfileString("CameraEnabled", "Cam2", "1", iniPath);
	else
		WritePrivateProfileString("CameraEnabled", "Cam2", "0", iniPath);
#else
	if (bCheck)
		CT_WriteUserProfileString("CameraEnabled", "Cam2", "1");
	else
		CT_WriteUserProfileString("CameraEnabled", "Cam2", "0");
#endif
}

void CBodyNoteDlg::OnBnClickedCheckCam3()
{
	BOOL bCheck = (BST_CHECKED == m_CheckCam3_Ctrl.GetCheck());
#ifdef SETTINGS_LOCATION_EXEC
	CString iniPath;
	iniPath.Format("%s\\BodyNote.ini", theApp.GetExecFolder());
	if (bCheck)
		WritePrivateProfileString("CameraEnabled", "Cam3", "1", iniPath);
	else
		WritePrivateProfileString("CameraEnabled", "Cam3", "0", iniPath);
#else
	if (bCheck)
		CT_WriteUserProfileString("CameraEnabled", "Cam3", "1");
	else
		CT_WriteUserProfileString("CameraEnabled", "Cam3", "0");
#endif
}

void CBodyNoteDlg::OnBnClickedButtonAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

BOOL CBodyNoteDlg::SaveCurRecordToFile()
{
	BOOL bRet = TRUE;

	try
	{
		CString patientFolder;
		patientFolder.Format("%s\\%ld", theApp.m_WorkSpaceFolder, m_CurPatient.m_ID);
		patientFolder = CT_OptimizePath(patientFolder, TRUE);
		CreateDirectory(patientFolder, NULL);

		CString patientFilePath;
		patientFilePath.Format("%sdata.ini", patientFolder);
		patientFilePath = CT_OptimizePath(patientFilePath, FALSE);

		m_CurPatient.ToFile(patientFilePath);
		bRet = theApp.CryptDecryptFile(patientFilePath, TRUE);

		m_bDirty = FALSE;
	}
	catch (std::exception* e)
	{		
		e = NULL;
		return FALSE;
	}

	return bRet;
}

void CBodyNoteDlg::OnBnClickedButtonLoad()
{
	if (m_bDirty)
	{
		if (IDNO == AfxMessageBox("I dati del paziente corrente non sono salvati.\nSi vuol procedere comunque?", MB_ICONINFORMATION|MB_YESNO))
			return;
	}
	
	CArray<patientIndex, patientIndex> records;
	theApp.LoadPatientIndex(theApp.m_WorkSpaceFolder, &records, &m_ProgressArchive_Ctrl);

	CSelectPatientDlg dlg(&records);
	if (IDCANCEL == dlg.DoModal())
		return;
	
	m_bNewRec = FALSE;

	if (theApp.LoadPatient(dlg.GetSelectedPatient(), m_CurPatient))
	{
		UpdateUIByRecord(m_CurPatient);
		m_CheckEditData_Ctrl.EnableWindow(TRUE);
		m_ButtonDeleteCurPatient_Ctrl.EnableWindow(TRUE);
		m_ButtonStartWebCam_Ctrl.EnableWindow(TRUE);
		m_bDirty = FALSE;
	}
	else
		AfxMessageBox("Impossibile caricare i dati del paziente", MB_ICONERROR);
}

void CBodyNoteDlg::OnBnClickedButtonNew()
{
	if (m_bDirty)
	{
		if (IDNO == AfxMessageBox("I dati del paziente corrente non sono salvati.\nSi vuol procedere comunque?", MB_ICONINFORMATION|MB_YESNO))
			return;
	}
	m_bDirty = FALSE;

	m_CurPatient.Empty();

	m_GlobalID++;
	m_CurPatient.m_ID = m_GlobalID;
	m_CurPatient.m_DataCreazione = CT_GetCurrentSysDate();	
	
	UpdateUIByRecord(m_CurPatient);

	m_CheckEditData_Ctrl.EnableWindow(TRUE);
	m_CheckEditData_Ctrl.SetCheck(BST_CHECKED);
	m_ButtonStartWebCam_Ctrl.EnableWindow(TRUE);

	m_bNewRec = TRUE;

	LockUIByEdit(TRUE);
}

void CBodyNoteDlg::UpdateUIByRecord(CPatientRecord record)
{
	m_EditName_Ctrl.SetWindowText(record.m_Nome);
	m_EditSurname_Ctrl.SetWindowText(record.m_Cognome);
	m_EditPhone_Ctrl.SetWindowText(record.m_Telefono);
	m_EditEmail_Ctrl.SetWindowText(record.m_Email);
	m_BirthDate_Ctrl.SetWindowText(record.m_DataNascita);
	
	/*
	if (record.m_DataNascita.IsEmpty())
		m_EditAge_Ctrl.SetWindowText("");
	else
		m_EditAge_Ctrl.SetWindowText(EvaluateAge(record.m_DataNascita));
	*/
	LoadComboPics(record);
}

void CBodyNoteDlg::UpdateRecordByUI(CPatientRecord& record)
{
	m_EditName_Ctrl.GetWindowText(m_CurPatient.m_Nome);
	m_CurPatient.m_Nome.Trim();
	m_EditSurname_Ctrl.GetWindowText(m_CurPatient.m_Cognome);
	m_CurPatient.m_Cognome.Trim();
	m_EditPhone_Ctrl.GetWindowText(m_CurPatient.m_Telefono);
	m_CurPatient.m_Telefono.Trim();
	m_EditEmail_Ctrl.GetWindowText(m_CurPatient.m_Email);
	m_CurPatient.m_Email.Trim();
	m_BirthDate_Ctrl.GetWindowText(m_CurPatient.m_DataNascita);
	m_CurPatient.m_DataNascita.Remove('/');
	
	StorePicComment(m_CurPatient, m_picIndex);
}

BOOL CBodyNoteDlg::StorePicComment(CPatientRecord record, int picIndex)
{
	if (!record.IsValid())
		return FALSE;
	if (picIndex < 0 || picIndex >= m_ComboPictures_Ctrl.GetCount())
		return FALSE;

	CString comment;
	m_EditComment_Ctrl.GetWindowText(comment);
			
	if (comment.IsEmpty())
		return TRUE;

	CString picName;
	m_ComboPictures_Ctrl.GetLBText(picIndex, picName);
	
	CString commentPath;
	commentPath.Format("%s\\%ld\\%s.txt", theApp.m_WorkSpaceFolder, record.m_ID, picName);
	commentPath = CT_OptimizePath(commentPath, FALSE);

	CStdioFile file;
	if(file.Open(commentPath, CFile::modeCreate|CFile::modeWrite))
		file.WriteString(comment);
	else 
		return FALSE;
	file.Close();

	theApp.CryptDecryptFile(commentPath, TRUE);
	return TRUE;
}

BOOL CBodyNoteDlg::ReadPicComment(CPatientRecord record, int picIndex)
{
	if (!record.IsValid())
		return FALSE;
	if (picIndex < 0 || picIndex >= m_ComboPictures_Ctrl.GetCount())
		return FALSE;

	CString picName;
	m_ComboPictures_Ctrl.GetLBText(picIndex, picName);
	
	CString commentPath;
	commentPath.Format("%s\\%ld\\%s.txt", theApp.m_WorkSpaceFolder, record.m_ID, picName);
	commentPath = CT_OptimizePath(commentPath, FALSE);

	theApp.CryptDecryptFile(commentPath, FALSE);

	FILE* pFile = NULL;
	fopen_s(&pFile, commentPath, "r");
	if (!pFile)
	{
		m_EditComment_Ctrl.SetWindowText("");
		return FALSE;
	}
	
	CString comment;

	char buf[1024];
	while (!feof(pFile))
	{
		if ( fgets (buf, 1024, pFile) != NULL )
			comment += CString(buf);
	}
	fclose(pFile);

	theApp.CryptDecryptFile(commentPath, TRUE);

	m_EditComment_Ctrl.SetWindowText(comment);
	return TRUE;
}

CString CBodyNoteDlg::EvaluateAge(CString birthDate)
{
	CString aaaa = birthDate.Right(4);
	CString mm = birthDate.Mid(2,2);
	CString dd = birthDate.Left(2);

	int a = atoi(aaaa);
	int m = atoi(mm);
	int d = atoi(dd);

	if (a <= 1970 || m <= 0 || m > 12 || d <= 0 || d > 31)
		return "";

	CTime tsRec( a, m, d,0,0,0);

	CString curSysDate = CT_GetCurrentSysDate();
	curSysDate.Remove('-');
	aaaa = curSysDate.Right(4);
	mm = curSysDate.Mid(2,2);
	dd = curSysDate.Left(2);

	CTime tsCur(atoi(aaaa), atoi(mm), atoi(dd),0,0,0);

	CTimeSpan ts = tsCur - tsRec;

	int age = (ts.GetDays()/365);
	CString AgeStr;
	AgeStr.Format("%d", age);
	return AgeStr;
}

void CBodyNoteDlg::OnEnChangeEditName()
{
	m_bDirty = TRUE;
}

void CBodyNoteDlg::OnEnChangeEditSurname()
{
	m_bDirty = TRUE;
}

void CBodyNoteDlg::OnEnChangeEditPhone()
{
	m_bDirty = TRUE;
}

void CBodyNoteDlg::OnEnChangeEditEmail()
{
	m_bDirty = TRUE;
}

void CBodyNoteDlg::OnEnChangeEditVisitcause()
{
	m_bDirty = TRUE;
}

void CBodyNoteDlg::OnEnChangeEditDiagnosis()
{
	m_bDirty = TRUE;
}

void CBodyNoteDlg::OnEnChangeEditComment()
{
	m_bDirty = TRUE;
}

void CBodyNoteDlg::OnCancel()
{
	BOOL bWeb = !m_ButtonStartWebCam_Ctrl.IsWindowEnabled();
	BOOL bEdit = (m_CheckEditData_Ctrl.GetCheck() == BST_CHECKED);
	if (!bWeb && !bEdit)
		CDialog::OnCancel();
}

void CBodyNoteDlg::OnOK()
{
	BOOL bEdit = (m_CheckEditData_Ctrl.GetCheck() == BST_CHECKED);
	if (!bEdit)
		CDialog::OnOK();
}

void CBodyNoteDlg::OnBnClickedCheckEditdata()
{
	BOOL bEdit = (m_CheckEditData_Ctrl.GetCheck() == BST_CHECKED);

	LockUIByEdit(bEdit);
	UpdateRecordByUI(m_CurPatient);
	if (!bEdit && m_CurPatient.IsValid())
	{
		if (!SaveCurRecordToFile())
			AfxMessageBox("Errore durante il salvataggio dei dati del paziente", MB_ICONINFORMATION);
		
		m_ButtonDeleteCurPatient_Ctrl.EnableWindow(TRUE);
		if (m_bNewRec)
		{
			theApp.UpdatePatientIndex(theApp.m_WorkSpaceFolder, &m_ProgressArchive_Ctrl);
			m_bNewRec = FALSE;
		}
	}	
}

void CBodyNoteDlg::LockUIByEdit(BOOL bEdit)
{
	//for (int iCam = 0; iCam < nCam; iCam++)
	//	m_StaticCam_Ctrl[nCam].EnableWindow(!bEdit);
	
	m_EditName_Ctrl.SetReadOnly(!bEdit);
	m_EditSurname_Ctrl.SetReadOnly(!bEdit);
	m_EditPhone_Ctrl.SetReadOnly(!bEdit);
	m_EditEmail_Ctrl.SetReadOnly(!bEdit);
	m_BirthDate_Ctrl.SetReadOnly(!bEdit);

	m_ButtonDetails_Ctrl.EnableWindow(bEdit);

	m_CheckCam1_Ctrl.EnableWindow(!bEdit);
	m_CheckCam2_Ctrl.EnableWindow(!bEdit);
	m_CheckCam3_Ctrl.EnableWindow(!bEdit);
	m_ButtonStartWebCam_Ctrl.EnableWindow(!bEdit);
	//m_ButtonStopWebCam_Ctrl.EnableWindow(!bEdit);
	//m_ButtonShot_Ctrl.EnableWindow(!bEdit);
	m_ButtonSettings_Ctrl.EnableWindow(!bEdit);
	m_ButtonExit_Ctrl.EnableWindow(!bEdit);
	m_ButtonNewPatient_Ctrl.EnableWindow(!bEdit);
	m_ButtonLoadPatient_Ctrl.EnableWindow(!bEdit);
	m_ButtonDeleteCurPatient_Ctrl.EnableWindow(!bEdit);
	m_ButtonOpenPatientFolder_Ctrl.EnableWindow(bEdit);
	m_ButtonCaricaDoc_Ctrl.EnableWindow(bEdit);
	m_ButtonVediDoc_Ctrl.EnableWindow(bEdit);

	if (m_ComboPictures_Ctrl.GetCount() > 0)
	{
		m_ComboPictures_Ctrl.EnableWindow(bEdit);
		m_ButtonDeletePictures_Ctrl.EnableWindow(bEdit);
	}
	else
	{
		m_ComboPictures_Ctrl.EnableWindow(FALSE);
		m_ButtonDeletePictures_Ctrl.EnableWindow(FALSE);
	}
	m_EditComment_Ctrl.SetReadOnly(!bEdit);
	if (!bEdit)
		m_StaticCurCam_Ctrl.SetImage(NULL);
}

void CBodyNoteDlg::OnBnClickedButtonDeletepicture()
{
	int nImg = m_ComboPictures_Ctrl.GetCount();
	if (nImg == 0)
		return;

	if (IDNO == AfxMessageBox("Si vuol veramente eliminare quest'immagine?", MB_YESNO|MB_ICONQUESTION))
		return;

	CString picName;
	m_ComboPictures_Ctrl.GetLBText(m_ComboPictures_Ctrl.GetCurSel(), picName);
	
	CString commentPath;
	commentPath.Format("%s\\%ld\\%s.txt", theApp.m_WorkSpaceFolder, m_CurPatient.m_ID, picName);
	commentPath = CT_OptimizePath(commentPath, FALSE);

	DeleteFile(commentPath);

	CString imgPath;
	imgPath.Format("%s\\%ld\\%s.jpg", theApp.m_WorkSpaceFolder, m_CurPatient.m_ID, picName);
	imgPath = CT_OptimizePath(imgPath, FALSE);

	DeleteFile(imgPath);

	LoadComboPics(m_CurPatient);
}

void CBodyNoteDlg::OnCbnSelchangeComboPictures()
{
	// store cur comment before
	StorePicComment(m_CurPatient, m_picIndex);
	m_picIndex = m_ComboPictures_Ctrl.GetCurSel();
	SelectPicture(m_CurPatient, m_picIndex);
}

int CBodyNoteDlg::LoadComboPics(CPatientRecord record)
{
	if (theApp.m_WorkSpaceFolder.IsEmpty())
	{
		m_ComboPictures_Ctrl.SetCurSel(-1);
		m_ComboPictures_Ctrl.EnableWindow(FALSE);
		return 0;
	}

	m_ComboPictures_Ctrl.ResetContent();
	m_picIndex = -1;

	CString searchPath;
	searchPath.Format("%s\\%ld\\*.jpg", theApp.m_WorkSpaceFolder, record.m_ID);
	searchPath = CT_OptimizePath(searchPath, FALSE);

	CFileFind ff;
	BOOL bFound = ff.FindFile(searchPath);
	while (bFound)
	{
		bFound = ff.FindNextFile();
		m_ComboPictures_Ctrl.AddString(ff.GetFileTitle());
	}
	ff.Close();

	int nPic = m_ComboPictures_Ctrl.GetCount();
	if (nPic > 0)
	{
		m_picIndex = nPic-1;
		
		m_ButtonDeletePictures_Ctrl.EnableWindow(TRUE);
		m_ComboPictures_Ctrl.EnableWindow(TRUE);
		m_ComboPictures_Ctrl.SetCurSel(m_picIndex);
		m_EditComment_Ctrl.EnableWindow(TRUE);
		SelectPicture(record, m_picIndex);
		m_StaticCurCam_Ctrl.SetEnableZoom(TRUE);
	}
	else
	{
		m_ButtonDeletePictures_Ctrl.EnableWindow(FALSE);
		m_ComboPictures_Ctrl.EnableWindow(FALSE);
		m_EditComment_Ctrl.SetWindowText("");
		m_EditComment_Ctrl.EnableWindow(FALSE);
		m_StaticCurCam_Ctrl.SetImage(m_pIplBlack);
		
		CString title;
		title.Format("Current Camera: %02d", m_CurCameraIndex+1);
		m_StaticCurCamTitle_Ctrl.SetWindowText(title);
	}

	return nPic;
}

void CBodyNoteDlg::SelectPicture(CPatientRecord record, int picIndex)
{
	if (picIndex < 0 || picIndex >= m_ComboPictures_Ctrl.GetCount())
	{
		m_EditComment_Ctrl.SetWindowText("");
		return;
	}
	
	CString fileName; 
	m_ComboPictures_Ctrl.GetLBText(picIndex, fileName);

	CString imgPath;
	imgPath.Format("%s\\%ld\\%s.jpg", theApp.m_WorkSpaceFolder, record.m_ID, fileName);
	imgPath = CT_OptimizePath(imgPath, FALSE);

	theApp.CryptDecryptFile(imgPath, FALSE, FALSE);
	IplImage* pIpl = cvLoadImage(imgPath);
	if (pIpl)
	{
		m_StaticCurCam_Ctrl.SetImage(pIpl);
		cvReleaseImage(&pIpl);

		CString msg;
		msg.Format("%s - click pulsante sinistro apre zoom - click pulsante destro reset zoom", fileName);
		m_StaticCurCamTitle_Ctrl.SetWindowText(msg);
	}
	else
		m_StaticCurCam_Ctrl.SetImage(m_pIplBlack);
	theApp.CryptDecryptFile(imgPath, TRUE);
	
	ReadPicComment(record, picIndex);
}

void CBodyNoteDlg::OnBnClickedButtonOpenpatientfolder()
{
	if (!m_CurPatient.IsValid())
		return;

	CString patientFolder;
	patientFolder.Format("%s\\%ld", theApp.m_WorkSpaceFolder, m_CurPatient.m_ID);
	patientFolder = CT_OptimizePath(patientFolder, TRUE);
	
	ShellExecute(GetSafeHwnd(), NULL, patientFolder, "", NULL, SW_SHOWNORMAL);
}

void CBodyNoteDlg::OnBnClickedButtonDelpatient()
{
	if (theApp.m_WorkSpaceFolder.IsEmpty() || !m_CurPatient.IsValid())
		return;

	if (IDNO == AfxMessageBox("Si vuol veramente eliminare questo paziente? Tutti i dati associati saranno cancellati dall'archivio", MB_YESNO|MB_ICONQUESTION))
		return;

	CString patientFolder;
	patientFolder.Format("%s\\%ld", theApp.m_WorkSpaceFolder, m_CurPatient.m_ID);
	patientFolder = CT_OptimizePath(patientFolder, TRUE);

	CString searchPath;
	searchPath.Format("%s*.*", patientFolder);
	CFileFind ff;
	BOOL bFound = ff.FindFile(searchPath);
	while(bFound)
	{
		bFound = ff.FindNextFile();
		if (ff.IsDots() || ff.IsDirectory())
			continue;
		
		DeleteFile(ff.GetFilePath());
	}
	ff.Close();
	RemoveDirectory(patientFolder);

	CString indexPath;
	indexPath.Format("%s\\dbIndex.txt", theApp.m_WorkSpaceFolder);
	CString indexPathTmp;
	indexPathTmp.Format("%s\\dbIndexTmp.txt", theApp.m_WorkSpaceFolder);
	
	if (theApp.UpdatePatientIndex(theApp.m_WorkSpaceFolder, &m_ProgressArchive_Ctrl))
		DeleteFile(indexPathTmp);
	else
	{
		rename(indexPathTmp, indexPath);
		AfxMessageBox("Impossibile completare l'operazione di eliminazione del paziente", MB_ICONINFORMATION);
	}
	m_CurPatient.Empty();
	m_ButtonDeleteCurPatient_Ctrl.EnableWindow(FALSE);
	m_ButtonStartWebCam_Ctrl.EnableWindow(FALSE);
	m_CheckEditData_Ctrl.EnableWindow(FALSE);
	m_StaticCurCam_Ctrl.SetImage(m_pIplBlack);
	UpdateUIByRecord(m_CurPatient);
	m_bDirty = FALSE;
	m_bNewRec = FALSE;
}

void CBodyNoteDlg::OnBnClickedButtonSettings()
{
	CSettingsDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		char curFolder[4096];
#ifdef SETTINGS_LOCATION_EXEC
		CString iniPath;
		iniPath.Format("%s\\BodyNote.ini", theApp.GetExecFolder());
		GetPrivateProfileString("BodyNoteSettings", "WorkSpace",  CT_GetSpecialFolder(CSIDL_COMMON_APPDATA, TRUE, TRUE), curFolder, 4096, iniPath);	
#else
		CT_GetUserProfileString("BodyNoteSettings", "WorkSpace",  CT_GetSpecialFolder(CSIDL_COMMON_APPDATA, TRUE, TRUE), curFolder, 4096);
#endif
		theApp.m_WorkSpaceFolder = CString(curFolder);
	}
}

void CBodyNoteDlg::OnInputInputdata()
{
	if (IDNO == AfxMessageBox("Attenzione: eseguire il backup del workspace PRIMA di eseguire questa procedura.\nSi vuol proseguire?", MB_YESNO|MB_ICONWARNING))
		return;

	char initFolder[4096];
#ifdef SETTINGS_LOCATION_EXEC
	CString iniPath;
	iniPath.Format("%s\\BodyNote.ini", theApp.GetExecFolder());
	GetPrivateProfileString("BodyNoteSettings", "InputFolder",  "", initFolder, 4096, iniPath);	
#else
	CT_GetUserProfileString("BodyNoteSettings", "InputFolder",  "", initFolder, 4096);
#endif
		
	CString inputdataFolder = CT_PickFolderPath("Selezionare la cartella workspace da importare", initFolder);
	if (inputdataFolder.IsEmpty())
		return;
#ifdef SETTINGS_LOCATION_EXEC
	WritePrivateProfileString("BodyNoteSettings", "InputFolder", inputdataFolder, iniPath);	
#else
	CT_WriteUserProfileString("BodyNoteSettings", "InputFolder", inputdataFolder);
#endif

	CArray<CPatientRecord,CPatientRecord> patientToImport;
	int nPatient = theApp.GetPatientDB(inputdataFolder, &patientToImport, NULL);
	if (nPatient == 0)
	{
		AfxMessageBox("Non sono stati trovati dati relativi a pazienti nella cartella!", MB_ICONEXCLAMATION);
		return;
	}

	BeginWaitCursor();

	CPatientRecord addedPatient;
	int nPatSkipped = 0;
	int nPicImported = 0;
	int nCommentImported = 0;
	for (int iPat = 0; iPat < nPatient; iPat++)
	{
		if (!patientToImport[iPat].IsValid(FALSE))
		{
			nPatSkipped++;
			continue;
		}
		addedPatient = patientToImport[iPat];
		m_GlobalID++;
		addedPatient.m_ID = m_GlobalID;
		if (addedPatient.m_DataCreazione.IsEmpty())
			addedPatient.m_DataCreazione = CT_GetCurrentSysDate();
		
		CString patientFolder;
		patientFolder.Format("%s\\%ld", theApp.m_WorkSpaceFolder, addedPatient.m_ID);
		patientFolder = CT_OptimizePath(patientFolder, TRUE);
		CreateDirectory(patientFolder, NULL);

		CString patientFilePath;
		patientFilePath.Format("%sdata.ini", patientFolder);
		patientFilePath = CT_OptimizePath(patientFilePath, FALSE);

		addedPatient.ToFile(patientFilePath);
		theApp.CryptDecryptFile(patientFilePath, TRUE);

		// copy related file

		CString origDataPath;
		origDataPath.Format("%s\\%ld\\data.ini", inputdataFolder, patientToImport[iPat].m_ID);
		CPatientRecord testPatient;
		testPatient.FromFile(origDataPath);
		BOOL bNotCrypted = testPatient.IsValid(FALSE); // check if patient data are readable without crypt (old version)
		
		CString RelatedFiles;
		RelatedFiles.Format("%s\\%ld_%s_%s\\*.*", inputdataFolder, patientToImport[iPat].m_ID, patientToImport[iPat].m_Nome, patientToImport[iPat].m_Cognome);
		
		char destPath[4096];
		char drive[8];
		char path[4096];
		char fname[1024];
		char ext[8];
				
		CFileFind ff;
		BOOL bFound = ff.FindFile(RelatedFiles);
		while (bFound)
		{
			bFound = ff.FindNextFile();
			if (ff.IsDirectory() || ff.IsDots())
				continue;
			if (ff.GetFilePath().CompareNoCase(origDataPath) == 0)
				continue;
			CString curFile = ff.GetFilePath();
			_splitpath_s(curFile, drive, 8, path, 4096, fname, 1024, ext, 8);
			_splitpath_s(patientFilePath, drive, 8, path, 4096, NULL, 0, NULL, 0);
			_makepath_s(destPath, 4096, drive, path, fname, ext);

			if (!CopyFile(curFile, destPath, FALSE))
				nPatSkipped++;		
			if (bNotCrypted)
				theApp.CryptDecryptFile(destPath, TRUE);
		}		
		ff.Close();
	}

	CString idStr;
	idStr.Format("%ld", m_GlobalID);
#ifdef SETTINGS_LOCATION_EXEC
	WritePrivateProfileString("BodyNoteSettings", "GlobalID", idStr, iniPath);	
#else
	CT_WriteUserProfileString("BodyNoteSettings", "GlobalID", idStr);
#endif

	EndWaitCursor();

	CArray<CPatientRecord,CPatientRecord> dbPatients;
	int nPatientDB = theApp.GetPatientDB(theApp.m_WorkSpaceFolder, &dbPatients, NULL);

	CString reportMsg;
	reportMsg.Format("- %d pazienti trovati\n- %d pazienti non importati\n- %d pazienti totali nel workspace", nPatient, nPatSkipped, nPatientDB);
	AfxMessageBox(reportMsg, MB_ICONINFORMATION);	
}

void CBodyNoteDlg::OnBnClickedButtonMoredetails()
{
	CMoreDataDlg dlg(&m_CurPatient);
	if (dlg.DoModal() == IDOK)
	{
		if (!SaveCurRecordToFile())
			AfxMessageBox("Errore durante il salvataggio dei dati del paziente", MB_ICONINFORMATION);
	}
}

void CBodyNoteDlg::OnBnClickedButtonCaricadoc()
{
	CAddDocumentDlg dlg;
	if (IDOK != dlg.DoModal())
		return;

	if (!SaveCurRecordToFile())
	{
		AfxMessageBox("Errore durante il salvataggio dei dati del paziente", MB_ICONINFORMATION);
		return;
	}

	try
	{
		CString selectedPath = dlg.m_SelectedPath;
		CString fileName = dlg.m_NewName;
		fileName.Replace('_', '-');

		CString creationDate = dlg.m_CreationDate;

		CString patientFolder;
		patientFolder.Format("%s\\%ld", theApp.m_WorkSpaceFolder, m_CurPatient.m_ID);
	
		CString importFolder;
		importFolder.Format("%s\\imported", patientFolder);
		importFolder = CT_OptimizePath(importFolder, TRUE);

		CreateDirectory(importFolder, NULL);

		char ext[8];
		_splitpath_s(selectedPath, NULL, 0, NULL, 0, NULL, 0, ext, 8);

		CString importedFilePath;
		importedFilePath.Format("%s%s_%s_%s%s", importFolder, CT_GetCurrentSysDate(), creationDate, fileName, ext);
		importedFilePath.Remove(' ');
		importedFilePath.Remove('*');
		importedFilePath.Remove('\n');
		importedFilePath.Remove(',');
		importedFilePath.Replace('/', '-');

		if (!CT_IsValidFileName(importedFilePath))
		{
			AfxMessageBox("Nome del file non valido!", MB_ICONINFORMATION);
			return;
		}

		CFileFind ff;
		BOOL bFound = ff.FindFile(importedFilePath);
		ff.Close();

		if (bFound)
		{
			if (IDNO == AfxMessageBox("Il file importato è già presente in archivio. Si vuol sovrascrivere il file precedente?", MB_YESNO|MB_ICONQUESTION))
				return;
		}

		if (!CopyFile(selectedPath, importedFilePath, FALSE)) 
		{
			CString err;
			err.Format("Si è verificato un errore durante l'importazione del file");
			AfxMessageBox(err, MB_ICONEXCLAMATION);
		} 
	}
	catch (std::exception* e)
	{
		e = NULL;

		CString err;
		err.Format("Si è verificato un errore durante l'importazione del file");
		AfxMessageBox(err, MB_ICONEXCLAMATION);
	}
}

void CBodyNoteDlg::OnBnClickedButtonVedidoc()
{
	CString patientFolder;
	patientFolder.Format("%s\\%ld", theApp.m_WorkSpaceFolder, m_CurPatient.m_ID);
	
	CString importFolder;
	importFolder.Format("%s\\imported", patientFolder);
	importFolder = CT_OptimizePath(importFolder, TRUE);

	COpenDocDlg dlg(importFolder);
	dlg.DoModal();
}

void CBodyNoteDlg::OnUpdateInputInputdata(CCmdUI *pCmdUI)
{
	BOOL bEdit = (m_CheckEditData_Ctrl.GetCheck() == BST_CHECKED);
	pCmdUI->Enable(!bEdit);
}

void CBodyNoteDlg::OnUpdateInputBackuparchivio(CCmdUI *pCmdUI)
{
	BOOL bEdit = (m_CheckEditData_Ctrl.GetCheck() == BST_CHECKED);
	pCmdUI->Enable(!bEdit);
}

void CBodyNoteDlg::OnInputBackuparchivio()
{
	if (theApp.m_WorkSpaceFolder.IsEmpty())
	{
		AfxMessageBox("Nessun workspace selezionato!");
		return;
	}

	char drive[8];
	char path[4096];
	char appName[4096];
	GetModuleFileName(NULL, appName, 4096);
	_splitpath_s(appName, drive, 8,  path, 4096, NULL, 0, NULL, 0);
	strcat_s(path, 4096, "Backup\\");
	char defBackupFolder[4096];
	_makepath_s(defBackupFolder, 4096, drive, path, NULL, NULL);
	CreateDirectory(defBackupFolder, NULL);

	CString newFolderRoot = CT_PickFolderPath("Selezionare la cartella di backup", defBackupFolder, m_hWnd);
	if (newFolderRoot.IsEmpty())
		return;

	if (theApp.m_WorkSpaceFolder.Find(newFolderRoot) >= 0)
	{
		AfxMessageBox("La cartella di backup non può risiedere all'interno del workspace corrente!");
		return;
	}
	
	//std::vector<string> paths;
	//theApp.RecursiveFileList(theApp.m_WorkSpaceFolder, paths);
	//int nFile = paths.size();
	//if (nFile == 0)
	//	return;

	CString backFolder;
	CString time;
	time = CT_GetCurrentSysTime();
	time.Replace(':', '-');
	backFolder.Format("%s\\workspace_%s_%s\\", newFolderRoot, CT_GetCurrentSysDate(), time);
	CreateDirectory(backFolder, NULL);
	backFolder = backFolder.Left(backFolder.GetLength()-1);

	std::string source = theApp.m_WorkSpaceFolder;
	source.append(1, '\0');
	
	std::string dest = backFolder;
	dest.append(1, '\0');

	char title[4096];
	sprintf_s(title, 4096, "Copia di backup\0");

	/*
	_SHFILEOPSTRUCT {
	  HWND         hwnd;
	  UINT         wFunc;
	  PCZZTSTR     pFrom;
	  PCZZTSTR     pTo;
	  FILEOP_FLAGS fFlags;
	  BOOL         fAnyOperationsAborted;
	  LPVOID       hNameMappings;
	  PCTSTR       lpszProgressTitle;
	} SHFILEOPSTRUCT, *LPSHFILEOPSTRUCT;
	*/
	SHFILEOPSTRUCT fileOp;
	fileOp.hwnd = NULL;
	fileOp.wFunc = FO_COPY;	
	fileOp.pFrom = source.c_str();
	fileOp.pTo = dest.c_str();
	fileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_SIMPLEPROGRESS | FOF_MULTIDESTFILES;
	fileOp.lpszProgressTitle = title;

	if (0 != SHFileOperation(&fileOp))
	{
		DWORD err = GetLastError();
		AfxMessageBox("Impossibile completare la copia di backup del workspace", MB_ICONERROR);		
	}
}


void CBodyNoteDlg::OnDbtoolsAggiornadb()
{
	if (IDNO == AfxMessageBox("Attenzione! La seguente procedura DEVE essere utilizzata solo quando necessario. Può compromettere l'archivio dati. Procedere?", MB_ICONEXCLAMATION|MB_YESNO))
		return;

	CString msg;
	msg.Format("Il seguente archivio sarà aggiornato:\n%s\nSi consiglia di procedere ad un backup di sicurezza.\nProcedere con l'aggiornamento?", theApp.m_WorkSpaceFolder);
	if (IDNO == AfxMessageBox(msg, MB_YESNO|MB_ICONQUESTION))
		return;
	
	int maxId = 0;
	vector<CString> duplicatePath;
	CString filter;
	filter.Format("%s\\*.*", theApp.m_WorkSpaceFolder);
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

		CString path2(path);
		int iUnder = path2.Find("_");
		if (iUnder < 0)
			continue;
		path2 = path2.Left(iUnder);

		char newFolder[4096];
		_makepath_s(newFolder, 4096, drive, path2, NULL, NULL);
		if (rename(dirPath, newFolder) != 0)
			duplicatePath.push_back(dirPath);

		CString nFold(newFolder);
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

	maxId++;

	// handle duplicates
	for (size_t iD = 0; iD < duplicatePath.size(); iD++)
	{
		char drive[8];
		char path[2048];
		_splitpath_s(duplicatePath[iD], drive, 8, path, 2048, NULL, 0, NULL, 0);

		CString curPath(path);
		if (curPath[curPath.GetLength()-1] == '\\')
			curPath = curPath.Left(curPath.GetLength()-1);

		for (int i = curPath.GetLength()-1; i >= 0; i--)
		{
			char c = curPath[i];
			if (c == '\\')
			{
				CString idS;
				idS.Format("\\%d\\", maxId++);
				curPath = curPath.Left(i);
				curPath += idS;
				break;
			}
		}

		char newFolder[4096];
		_makepath_s(newFolder, 4096, drive, curPath, NULL, NULL);
		rename(duplicatePath[iD], newFolder);
	}

	// update dbIndex
	CString indexPath;
	indexPath.Format("%s\\dbIndex.txt", theApp.m_WorkSpaceFolder);
	CString indexPathTmp;
	indexPathTmp.Format("%s\\dbIndexTmp.txt", theApp.m_WorkSpaceFolder);

	rename(indexPath, indexPathTmp);
	if (theApp.UpdatePatientIndex(theApp.m_WorkSpaceFolder, &m_ProgressArchive_Ctrl))
		DeleteFile(indexPathTmp);

	AfxMessageBox("Aggiornamento terminato", MB_ICONINFORMATION);
}
