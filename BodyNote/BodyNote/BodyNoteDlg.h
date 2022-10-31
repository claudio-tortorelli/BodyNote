// BodyNoteDlg.h : file di intestazione
//

#pragma once
#include "afxwin.h"
#include "PreviewWnd.h"
#include "BtnST.h"
#include "PatientRecord.h"
#include "afxdtctl.h"
#include "afxcmn.h"

static const int nCam = 3;


// finestra di dialogo CBodyNoteDlg
class CBodyNoteDlg : public CDialog
{
// Costruzione
public:
	CBodyNoteDlg(CWnd* pParent = NULL);	// costruttore standard
	virtual ~CBodyNoteDlg();

// Dati della finestra di dialogo
	enum { IDD = IDD_BODYNOTE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// supporto DDX/DDV

public:
	BOOL			StartWebCam();
	void			LockUI(BOOL bLock);
	void			LockUIByEdit(BOOL bEdit);

	int				LoadComboPics(CPatientRecord record);
	void			SelectPicture(CPatientRecord record, int picIndex);

	void			UpdateUIByRecord(CPatientRecord record);
	void			UpdateRecordByUI(CPatientRecord& record);

	CString			EvaluateAge(CString birthDate);
	BOOL			SaveCurRecordToFile();

	BOOL			StorePicComment(CPatientRecord record, int picIndex);
	BOOL			ReadPicComment(CPatientRecord record, int picIndex);

public:
	CPreviewWnd		m_StaticCam_Ctrl[nCam];
	CPreviewWnd		m_StaticCurCam_Ctrl;
	CStatic			m_StaticCurCamTitle_Ctrl;
	CEdit			m_EditName_Ctrl;
	CEdit			m_EditSurname_Ctrl;
	CEdit			m_EditPhone_Ctrl;
	CEdit			m_EditEmail_Ctrl;
	CEdit			m_EditAge_Ctrl;
	CComboBox		m_ComboPictures_Ctrl;
	CEdit			m_EditComment_Ctrl;
	CEdit			m_BirthDate_Ctrl;
	CProgressCtrl	m_ProgressArchive_Ctrl;

	CButton			m_CheckCam1_Ctrl;
	CButton			m_CheckCam2_Ctrl;
	CButton			m_CheckCam3_Ctrl;

	CButton			m_CheckEditData_Ctrl;

	CButtonST		m_ButtonStartWebCam_Ctrl;
	CButtonST		m_ButtonStopWebCam_Ctrl;
	CButtonST		m_ButtonExit_Ctrl;
	CButtonST		m_ButtonShot_Ctrl;
	CButtonST		m_ButtonInfo_Ctrl;
	CButtonST		m_ButtonSettings_Ctrl;
	CButtonST		m_ButtonOpenPatientFolder_Ctrl;
	CButtonST		m_ButtonDeleteCurPatient_Ctrl;
	CButtonST		m_ButtonNewPatient_Ctrl;
	CButtonST		m_ButtonLoadPatient_Ctrl;	
	CButtonST		m_ButtonDetails_Ctrl;
	CButtonST		m_ButtonCaricaDoc_Ctrl;
	CButtonST		m_ButtonVediDoc_Ctrl;
	
	CButton			m_ButtonDeletePictures_Ctrl;

protected:
	HICON			m_hIcon;

	BOOL			m_bStopWebCam;
	int				m_CurCameraIndex;
	IplImage*		m_pIplBlack;

	HICON			m_hExit[2];
	HICON			m_hShot[2];
	HICON			m_hStart[2];
	HICON			m_hStop[2];
	HICON			m_hInfo[2];
	HICON			m_hSettings[2];
	HICON			m_hAdd[2];
	HICON			m_hRemove[2];
	HICON			m_hLoad[2];
	HICON			m_hDetail[2];
	HICON			m_hAddDoc[2];
	HICON			m_hViewDoc[2];

	long			m_GlobalID;
	int				m_picIndex;

	BOOL			m_bNewRec;
	BOOL			m_bDirty;
	
	CPatientRecord	m_CurPatient;
	
// Implementazione
protected:
	// Funzioni generate per la mappa dei messaggi
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonStartwebcam();
	afx_msg void OnBnClickedButtonStopwebcam();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonShot();
	afx_msg void OnBnClickedCheckCam1();
	afx_msg void OnBnClickedCheckCam2();
	afx_msg void OnBnClickedCheckCam3();
	afx_msg void OnBnClickedButtonAbout();	
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnEnChangeEditName();
	afx_msg void OnEnChangeEditSurname();
	afx_msg void OnEnChangeEditPhone();
	afx_msg void OnEnChangeEditEmail();
	afx_msg void OnEnChangeEditVisitcause();
	afx_msg void OnEnChangeEditDiagnosis();
	afx_msg void OnEnChangeEditComment();
	afx_msg void OnBnClickedCheckEditdata();
	afx_msg void OnBnClickedButtonDeletepicture();
	afx_msg void OnCbnSelchangeComboPictures();
	afx_msg void OnBnClickedButtonOpenpatientfolder();
	afx_msg void OnBnClickedButtonDelpatient();
	afx_msg void OnBnClickedButtonSettings();	
	afx_msg void OnInputInputdata();
	afx_msg void OnBnClickedButtonMoredetails();	
	afx_msg void OnBnClickedButtonCaricadoc();
	afx_msg void OnBnClickedButtonVedidoc();
	afx_msg void OnUpdateInputInputdata(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInputBackuparchivio(CCmdUI *pCmdUI);
	afx_msg void OnInputBackuparchivio();	
	afx_msg void OnDbtoolsAggiornadb();
};
