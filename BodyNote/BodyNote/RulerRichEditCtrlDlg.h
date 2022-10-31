// RulerRichEditCtrlDlg.h : header file
//

#if !defined(AFX_RulerRichEditCtrlDlg_H__DB95D038_618F_4D3B_94A2_FCF4AF7D79A1__INCLUDED_)
#define AFX_RulerRichEditCtrlDlg_H__DB95D038_618F_4D3B_94A2_FCF4AF7D79A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RulerRichEditCtrl/RulerRichEditCtrl.h"
#include "PatientRecord.h"

/////////////////////////////////////////////////////////////////////////////
// CRulerRichEditCtrlDlg dialog

class CRulerRichEditCtrlDlg : public CDialog
{
// Construction
public:
	CRulerRichEditCtrlDlg(CPatientRecord* pPatient, CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRulerRichEditCtrlDlg)
	enum { IDD = IDD_RULERRICHEDITCTRLDEMO_DIALOG };

public:
	CButton	m_toolbar;
	CButton	m_ruler;
	CButton	m_new;
	CButton	m_save;
	CButton	m_load;
	CButton	m_ok;
	CStatic	m_placement;
	BOOL	m_showRuler;
	BOOL	m_showToolbar;
	BOOL	m_readOnly;
	//}}AFX_DATA

private:
	CRulerRichEditCtrl	m_rtf;
	CPatientRecord*		m_pPatientRecord;
	HICON m_hIcon;


	//{{AFX_VIRTUAL(CRulerRichEditCtrlDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	//{{AFX_MSG(CRulerRichEditCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonSave();
	afx_msg void OnButtonLoad();
	virtual void OnCancel();
	afx_msg void OnButtonNew();
	afx_msg void OnCheckShowRuler();
	afx_msg void OnCheckShowToolbar();
	afx_msg void OnCheckReadonly();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RulerRichEditCtrlDlg_H__DB95D038_618F_4D3B_94A2_FCF4AF7D79A1__INCLUDED_)
