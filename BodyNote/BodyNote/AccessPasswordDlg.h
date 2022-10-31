#pragma once
#include "afxwin.h"


// CAccessPasswordDlg dialog

class CAccessPasswordDlg : public CDialog
{
	DECLARE_DYNAMIC(CAccessPasswordDlg)

public:
	CAccessPasswordDlg(CString psw, CWnd* pParent = NULL);   // standard constructor
	virtual ~CAccessPasswordDlg();

public:
	CEdit		m_EditPsw_Ctrl;

protected:
	CString		m_CurPsw;

// Dialog Data
	enum { IDD = IDD_DIALOG_ACCESSPSW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
};
