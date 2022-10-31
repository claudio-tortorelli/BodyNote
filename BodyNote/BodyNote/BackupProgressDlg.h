#pragma once
#include "afxcmn.h"


// CBackupProgressDlg dialog

class CBackupProgressDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBackupProgressDlg)

public:
	CBackupProgressDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBackupProgressDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_BACKUPPROGRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_Progress_Ctrl;
};
