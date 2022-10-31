#pragma once
#include "afxcmn.h"
#include "SortListCtrl.h"
#include "afxwin.h"


// COpenDocDlg dialog

class COpenDocDlg : public CDialog
{
	DECLARE_DYNAMIC(COpenDocDlg)

public:
	COpenDocDlg(CString patientFolder, CWnd* pParent = NULL);   // standard constructor
	virtual ~COpenDocDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_LOADDOC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	CStatic			m_StaticRecordFound_Ctrl;
	CSortListCtrl	m_ListDoc_Ctrl;	
	
protected:
	CString m_PatientFolder;
	
public:
	afx_msg void OnNMDblclkListPatients(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonDelete();
};
