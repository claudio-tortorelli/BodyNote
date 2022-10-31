#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CAddDocumentDlg dialog

class CAddDocumentDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddDocumentDlg)

public:
	CAddDocumentDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddDocumentDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADDDOCUMENT };

public:
	CEdit			m_EditSelPath_Ctrl;
	CEdit			m_EditNewName_Ctrl;
	CDateTimeCtrl	m_Date;

public:
	CString		m_SelectedPath;
	CString		m_CreationDate;
	CString		m_NewName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedOk();
	
};
