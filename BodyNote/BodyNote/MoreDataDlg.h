#pragma once
#include "afxwin.h"
#include "PatientRecord.h"

// CMoreDataDlg dialog

class CMoreDataDlg : public CDialog
{
	DECLARE_DYNAMIC(CMoreDataDlg)

public:
	CMoreDataDlg(CPatientRecord* pRecord, CWnd* pParent = NULL);   // standard constructor
	virtual ~CMoreDataDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_MOREDATA };

public:
	CEdit m_EditMotivoConsulto_Ctrl;
	CEdit m_EditInsorgenzaSintomi_Ctrl;
	CEdit m_EditCausaScatenante_Ctrl;
	CEdit m_EditTerapiePrecedenti_Ctrl;
	CEdit m_EditCardioresporatorio_Ctrl;
	CEdit m_EditCardiointestinale_Ctrl;
	CEdit m_EditUrogenitale_Ctrl;
	CEdit m_EditRespiratorio_Ctrl;
	CEdit m_EditEsamiDiagnostici_Ctrl;
	CEdit m_EditUsoFarmaci_Ctrl;
	CEdit m_EditAlimentazione_Ctrl;
	CEdit m_EditVariazionePeso_Ctrl;
	CEdit m_EditSonnoSveglia_Ctrl;
	CEdit m_EditCefalee_Ctrl;
	CEdit m_EditTraumatismi_Ctrl;
	CEdit m_EditInterventi_Ctrl;
	CEdit m_EditGravidanze_Ctrl;
	CEdit m_EditMalattieImportanti_Ctrl;
	CEdit m_EditValutazioneFamiliare_Ctrl;
	CEdit m_EditProfessione_Ctrl;
	CEdit m_EditHobby_Ctrl;
	CEdit m_EditVista_Ctrl;
	CEdit m_EditStomatognatico_Ctrl;
	CEdit m_EditCicatrici_Ctrl;
	CEdit m_EditMicrogalvanismi_Ctrl;
	CEdit m_EditBilancioPosturale_Ctrl;
	CEdit m_EditChinesiologici_Ctrl;
	CEdit m_EditDiagnosi_Ctrl;
	CEdit m_EditCaratteristicheSintomo_Ctrl;
	CEdit m_EditPelle_Ctrl;
	CEdit m_EditAltro_Ctrl;

	CPatientRecord* m_pPatientRecord;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();		
	afx_msg void OnBnClickedButtonDiario();
	
};
