// RulerRichEditCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BodyNote.h"
#include "RulerRichEditCtrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRulerRichEditCtrlDlg dialog

CRulerRichEditCtrlDlg::CRulerRichEditCtrlDlg(CPatientRecord* pPatient, CWnd* pParent /*=NULL*/)
	: CDialog(CRulerRichEditCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRulerRichEditCtrlDlg)
	m_showRuler = FALSE;
	m_showToolbar = FALSE;
	m_readOnly = FALSE;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pPatientRecord = pPatient;
}

void CRulerRichEditCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRulerRichEditCtrlDlg)
	DDX_Control(pDX, IDC_CHECK_SHOW_TOOLBAR, m_toolbar);
	DDX_Control(pDX, IDC_CHECK_SHOW_RULER, m_ruler);
	DDX_Control(pDX, IDC_BUTTON_NEWRTF, m_new);
	DDX_Control(pDX, IDC_BUTTON_SAVERTF, m_save);
	DDX_Control(pDX, IDC_BUTTON_LOADRTF, m_load);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_STATIC_PLACEMENT, m_placement);
	DDX_Check(pDX, IDC_CHECK_SHOW_RULER, m_showRuler);
	DDX_Check(pDX, IDC_CHECK_SHOW_TOOLBAR, m_showToolbar);
	DDX_Check(pDX, IDC_CHECK_READONLY, m_readOnly);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRulerRichEditCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CRulerRichEditCtrlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
	ON_BN_CLICKED(IDC_CHECK_SHOW_RULER, OnCheckShowRuler)
	ON_BN_CLICKED(IDC_CHECK_SHOW_TOOLBAR, OnCheckShowToolbar)
	ON_BN_CLICKED(IDC_CHECK_READONLY, OnCheckReadonly)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CRulerRichEditCtrlDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRulerRichEditCtrlDlg message handlers

BOOL CRulerRichEditCtrlDlg::OnInitDialog()
{
	m_showRuler = TRUE;
	m_showToolbar = TRUE;

	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	
	CRect rect;
	m_placement.GetWindowRect( rect );
	ScreenToClient( rect );
	m_rtf.Create( WS_TABSTOP | WS_CHILD | WS_VISIBLE, rect, this, 100, TRUE );

	if (!m_pPatientRecord)
	{
		EndDialog(IDCANCEL);
		return TRUE;
	}

	CString diaryPath;
	diaryPath.Format("%s\\%ld\\diary.txt", theApp.m_WorkSpaceFolder, m_pPatientRecord->m_ID);
	diaryPath = CT_OptimizePath(diaryPath, FALSE);

	CFileFind ff;
	BOOL bFound = ff.FindFile(diaryPath);
	ff.Close();

	if (bFound)
	{
		theApp.CryptDecryptFile(diaryPath, FALSE);
		m_rtf.Load(diaryPath);
		theApp.CryptDecryptFile(diaryPath, TRUE);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRulerRichEditCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRulerRichEditCtrlDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRulerRichEditCtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRulerRichEditCtrlDlg::OnSize(UINT nType, int cx, int cy) 
{

	CDialog::OnSize(nType, cx, cy);
	
	// Move or resize controls
	if( m_rtf.m_hWnd )
	{
		int margin = 4;
		CRect rect;
		m_ok.GetWindowRect( rect );
		ScreenToClient( rect );
		m_ok.SetWindowPos( NULL, rect.left, cy - ( rect.Height() + 4 ), 0, 0, SWP_NOZORDER | SWP_NOSIZE );
		
		m_new.GetWindowRect( rect );
		ScreenToClient( rect );
		m_new.SetWindowPos( NULL, rect.left, cy - ( rect.Height() + 4 ), 0, 0, SWP_NOZORDER | SWP_NOSIZE );

		m_ruler.GetWindowRect( rect );
		ScreenToClient( rect );
		m_ruler.SetWindowPos( NULL, rect.left, cy - ( rect.Height() + 4 ), 0, 0, SWP_NOZORDER | SWP_NOSIZE );

		m_toolbar.GetWindowRect( rect );
		ScreenToClient( rect );
		m_toolbar.SetWindowPos( NULL, rect.left, cy - ( rect.Height() + 4 ), 0, 0, SWP_NOZORDER | SWP_NOSIZE );

		m_load.GetWindowRect( rect );
		ScreenToClient( rect );
		m_load.SetWindowPos( NULL, rect.left, cy - ( rect.Height() + 4 ), 0, 0, SWP_NOZORDER | SWP_NOSIZE );

		m_save.GetWindowRect( rect );
		ScreenToClient( rect );
		m_save.SetWindowPos( NULL, rect.left, cy - ( rect.Height() + 4 ), 0, 0, SWP_NOZORDER | SWP_NOSIZE );

		m_rtf.SetWindowPos( NULL, margin, margin, cx - margin * 2, cy - 8 - ( rect.Height() + 8 ), SWP_NOZORDER );

	}
	
}

/////////////////////////////////////////////////////////////////////////////
// CRulerRichEditCtrlDlg button handlers

void CRulerRichEditCtrlDlg::OnButtonSave() 
{

	CString filename;
	m_rtf.Save( filename );
	
}

void CRulerRichEditCtrlDlg::OnButtonLoad() 
{

	CString filename;
	m_rtf.Load( filename );
	
}

void CRulerRichEditCtrlDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CRulerRichEditCtrlDlg::OnButtonNew() 
{

	m_rtf.GetRichEditCtrl().SetWindowText( _T( "" ) );
	
}

void CRulerRichEditCtrlDlg::OnCheckShowRuler() 
{

	UpdateData();
	m_rtf.ShowRuler( m_showRuler );

}

void CRulerRichEditCtrlDlg::OnCheckShowToolbar() 
{

	UpdateData();
	m_rtf.ShowToolbar( m_showToolbar );
	
}


void CRulerRichEditCtrlDlg::OnCheckReadonly() 
{

	UpdateData();
	m_rtf.SetReadOnly( m_readOnly )	;

}


void CRulerRichEditCtrlDlg::OnBnClickedOk()
{
	CString patientFolder;
	patientFolder.Format("%s\\%ld", theApp.m_WorkSpaceFolder, m_pPatientRecord->m_ID);
	patientFolder = CT_OptimizePath(patientFolder, TRUE);
	CreateDirectory(patientFolder, NULL);

	CString diaryPath;
	diaryPath.Format("%s\\diary.txt", patientFolder);
	diaryPath = CT_OptimizePath(diaryPath, FALSE);

	m_rtf.Save(diaryPath);
	theApp.CryptDecryptFile(diaryPath, TRUE);
	OnOK();
}
