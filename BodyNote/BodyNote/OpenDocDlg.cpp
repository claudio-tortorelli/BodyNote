// OpenDocDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BodyNote.h"
#include "OpenDocDlg.h"


// COpenDocDlg dialog

IMPLEMENT_DYNAMIC(COpenDocDlg, CDialog)

COpenDocDlg::COpenDocDlg(CString patientFolder, CWnd* pParent /*=NULL*/)
	: CDialog(COpenDocDlg::IDD, pParent)
{	
	m_PatientFolder = patientFolder;
}

COpenDocDlg::~COpenDocDlg()
{
}

void COpenDocDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PATIENTS, m_ListDoc_Ctrl);
	DDX_Control(pDX, IDC_STATIC_RECORDFOUND, m_StaticRecordFound_Ctrl);
}


BEGIN_MESSAGE_MAP(COpenDocDlg, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PATIENTS, &COpenDocDlg::OnNMDblclkListPatients)
	ON_BN_CLICKED(IDOK, &COpenDocDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &COpenDocDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &COpenDocDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// COpenDocDlg message handlers

BOOL COpenDocDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect listRect;
	m_ListDoc_Ctrl.GetClientRect(&listRect);
	m_ListDoc_Ctrl.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	CString headers;
	headers.Format("Nome,%d;Creazione,%d;Importazione,%d;Tipo,%d", (int)(listRect.Width()*0.275), (int)(listRect.Width()*0.275), (int)(listRect.Width()*0.275), (int)(listRect.Width()*0.2));
	m_ListDoc_Ctrl.SetHeadings( headers );

	CString itemID;

	CString fileFilter;
	fileFilter.Format("%s*.*", m_PatientFolder);
	CFileFind ff;
	BOOL bFound = ff.FindFile(fileFilter);
	while (bFound)
	{
		bFound = ff.FindNextFile();

		if (ff.IsDots() || ff.IsDirectory())
			continue;

		char fname[1024];
		char ext[8];
		CString fullPath = ff.GetFilePath();
		_splitpath_s(fullPath, NULL, 0, NULL, 0, fname, 1024, ext, 8);

		CStringArray parsed;
		CString composite(fname);
		int iF = CT_ParseString(composite, '_', &parsed);
		if (iF != 3)
			continue;

		CString name = parsed[2];
		CString creation = parsed[1];
		CString import = parsed[0];

		int iItem = m_ListDoc_Ctrl.AddItem( name, creation, import, ext );

		char* pPath = new char[2048];
		strcpy_s(pPath, 2048, fullPath);
		m_ListDoc_Ctrl.SetItemData(iItem, (DWORD)pPath);
	}
	ff.Close();

	CString msg;
	msg.Format("%d documenti caricati", m_ListDoc_Ctrl.GetItemCount());
	m_StaticRecordFound_Ctrl.SetWindowText(msg);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void COpenDocDlg::OnNMDblclkListPatients(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iItem = m_ListDoc_Ctrl.GetSelectionMark();
	if (iItem < 0)
		return;
	char* pFullPath = (char*)m_ListDoc_Ctrl.GetItemData(iItem);	
	CT_ShellExecute(pFullPath);
}

void COpenDocDlg::OnBnClickedOk()
{	
	int nItem = m_ListDoc_Ctrl.GetItemCount();
	for (int iItem = 0; iItem < nItem; iItem++)
	{
		char* pFullPath = (char*)m_ListDoc_Ctrl.GetItemData(iItem);
		if (pFullPath)
			delete pFullPath;
		pFullPath = NULL;
	}
	CDialog::OnOK();
}


void COpenDocDlg::OnBnClickedButtonOpen()
{
	int iItem = m_ListDoc_Ctrl.GetSelectionMark();
	if (iItem < 0)
		return;
	char* pFullPath = (char*)m_ListDoc_Ctrl.GetItemData(iItem);	
	//theApp.CryptDecryptFile(pFullPath, FALSE);
	CT_ShellExecute(pFullPath);
	//theApp.CryptDecryptFile(pFullPath, TRUE);
}

void COpenDocDlg::OnBnClickedButtonDelete()
{
	int iItem = m_ListDoc_Ctrl.GetSelectionMark();
	if (iItem < 0)
		return;
	if (IDNO == AfxMessageBox("Si vuol veramente ELIMINARE il documento corrente?", MB_ICONQUESTION|MB_YESNO))
		return;
	char* pFullPath = (char*)m_ListDoc_Ctrl.GetItemData(iItem);	
	DeleteFile(pFullPath);

	delete pFullPath;
	pFullPath = NULL;
	m_ListDoc_Ctrl.DeleteItem(iItem);
}
