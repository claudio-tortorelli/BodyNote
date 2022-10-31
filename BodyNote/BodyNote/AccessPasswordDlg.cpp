// AccessPasswordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BodyNote.h"
#include "AccessPasswordDlg.h"

// CAccessPasswordDlg dialog

IMPLEMENT_DYNAMIC(CAccessPasswordDlg, CDialog)

CAccessPasswordDlg::CAccessPasswordDlg(CString psw, CWnd* pParent /*=NULL*/)
	: CDialog(CAccessPasswordDlg::IDD, pParent)
{
	m_CurPsw = psw;

	if (m_CurPsw.IsEmpty())
	{
		AfxMessageBox("Inserire la password!");
		EndDialog(IDCANCEL);
	}
}

CAccessPasswordDlg::~CAccessPasswordDlg()
{
}

void CAccessPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PSW, m_EditPsw_Ctrl);
}


BEGIN_MESSAGE_MAP(CAccessPasswordDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAccessPasswordDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAccessPasswordDlg message handlers

void CAccessPasswordDlg::OnBnClickedOk()
{
	CString insertedPw;
	m_EditPsw_Ctrl.GetWindowText(insertedPw);
	if (insertedPw.Compare(m_CurPsw) != 0)
	{
		CDialog::OnCancel();
		return;
	}
	CDialog::OnOK();
}
