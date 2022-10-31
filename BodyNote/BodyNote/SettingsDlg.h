#pragma once
#include "afxwin.h"


// CSettingsDlg dialog

class CSettingsDlg : public CDialog
{
	DECLARE_DYNAMIC(CSettingsDlg)

public:
	CSettingsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSettingsDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_SETTINGS };

public:
	CEdit m_EditWorkspaceFolder_Ctrl;
	CEdit m_EditPsw1_Ctrl;
	CEdit m_EditPsw2_Ctrl;
	CButton m_CheckPlayShotSound_Ctrl;
	CButton m_CheckWeek_Ctrl;
	CButton m_CheckMonth_Ctrl;

protected:
	CString m_CurWsFolder;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPickfolder();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheckBackweek();
	afx_msg void OnBnClickedCheckBackmonth();
};
