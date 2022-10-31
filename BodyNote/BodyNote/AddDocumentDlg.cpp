// AddDocumentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BodyNote.h"
#include "AddDocumentDlg.h"


// CAddDocumentDlg dialog

IMPLEMENT_DYNAMIC(CAddDocumentDlg, CDialog)

CAddDocumentDlg::CAddDocumentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDocumentDlg::IDD, pParent)
{

}

CAddDocumentDlg::~CAddDocumentDlg()
{
}

void CAddDocumentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SELECTEDPATH, m_EditSelPath_Ctrl);
	DDX_Control(pDX, IDC_EDIT_NEWNAME, m_EditNewName_Ctrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_Date);
}


BEGIN_MESSAGE_MAP(CAddDocumentDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CAddDocumentDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDOK, &CAddDocumentDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddDocumentDlg message handlers

void CAddDocumentDlg::OnBnClickedButtonAdd()
{
	char strFilter[] = { "All Files (*.*)|*.*||" };
	CFileDialog fileDlg(TRUE, "*.doc", NULL, 0, strFilter);
	if (fileDlg.DoModal() != IDOK)
		return;

	m_EditSelPath_Ctrl.SetWindowText(fileDlg.GetPathName());

	char fileName[2048];
	_splitpath_s(fileDlg.GetPathName(), NULL, 0, NULL, 0, fileName, 2048, NULL, 0);
	m_EditNewName_Ctrl.SetWindowText(fileName);
}

void CAddDocumentDlg::OnBnClickedOk()
{
	m_EditSelPath_Ctrl.GetWindowText(m_SelectedPath);
	if (m_SelectedPath.IsEmpty())
	{
		AfxMessageBox("Selezionare un documento da aggiungere in archivio", MB_ICONINFORMATION);
		return;
	}
	m_EditNewName_Ctrl.GetWindowText(m_NewName);	
	m_Date.GetWindowText(m_CreationDate);
	OnOK();
}
