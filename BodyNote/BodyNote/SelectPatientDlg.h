#pragma once
#include "afxcmn.h"
#include "SortListCtrl.h"
#include "PatientRecord.h"
#include "afxwin.h"


// CSelectPatientDlg dialog

class CSelectPatientDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectPatientDlg)

public:
	CSelectPatientDlg(CArray<patientIndex, patientIndex>* pRecords, CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectPatientDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_LOADRECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	patientIndex	GetSelectedPatient(){return m_SelectedRecord;}

public:
	CStatic			m_StaticRecordFound_Ctrl;
	CSortListCtrl	m_ListPatient_Ctrl;	
	CEdit			m_EditSearch_Ctrl;
	
protected:
	patientIndex						m_SelectedRecord;
	CArray<patientIndex, patientIndex>* m_pPatients;
	BOOL								m_bInitialized;

public:
	afx_msg void OnNMDblclkListPatients(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();	
	afx_msg void OnEnSetfocusEditSearch();
	afx_msg void OnEnChangeEditSearch();
};
