// MoreDataDlt.cpp : implementation file
//

#include "stdafx.h"
#include "BodyNote.h"
#include "MoreDataDlg.h"
#include "RulerRichEditCtrlDlg.h"

// CMoreDataDlg dialog

IMPLEMENT_DYNAMIC(CMoreDataDlg, CDialog)

CMoreDataDlg::CMoreDataDlg(CPatientRecord* pRecord, CWnd* pParent /*=NULL*/)
	: CDialog(CMoreDataDlg::IDD, pParent)
{
	m_pPatientRecord = pRecord;
}

CMoreDataDlg::~CMoreDataDlg()
{
}

void CMoreDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MOTIVOCONSULTO, m_EditMotivoConsulto_Ctrl);
	DDX_Control(pDX, IDC_EDIT_INSORGENZASINTOMI, m_EditInsorgenzaSintomi_Ctrl);
	DDX_Control(pDX, IDC_EDIT_CAUSASCATENANTE, m_EditCausaScatenante_Ctrl);
	DDX_Control(pDX, IDC_EDIT_TERAPIEPRECEDENTI, m_EditTerapiePrecedenti_Ctrl);
	DDX_Control(pDX, IDC_EDIT_CARDIORESPIRATORIO, m_EditCardioresporatorio_Ctrl);
	DDX_Control(pDX, IDC_EDIT_CARDIOINTESTINALE, m_EditCardiointestinale_Ctrl);
	DDX_Control(pDX, IDC_EDIT_UROGENITALE, m_EditUrogenitale_Ctrl);
	DDX_Control(pDX, IDC_EDIT_RESPIRATORIO, m_EditRespiratorio_Ctrl);
	DDX_Control(pDX, IDC_EDIT_ESAMIDIAGNOSTICI, m_EditEsamiDiagnostici_Ctrl);
	DDX_Control(pDX, IDC_EDIT_USOFARMACI, m_EditUsoFarmaci_Ctrl);
	DDX_Control(pDX, IDC_EDIT_ALIMENTAZIONE, m_EditAlimentazione_Ctrl);
	DDX_Control(pDX, IDC_EDIT_VARIAZIONEPESO, m_EditVariazionePeso_Ctrl);
	DDX_Control(pDX, IDC_EDIT_SONNOSVEGLIA, m_EditSonnoSveglia_Ctrl);
	DDX_Control(pDX, IDC_EDIT_CEFALEE, m_EditCefalee_Ctrl);
	DDX_Control(pDX, IDC_EDIT_TRAUMATISMI, m_EditTraumatismi_Ctrl);
	DDX_Control(pDX, IDC_EDIT_INTERVENTI, m_EditInterventi_Ctrl);
	DDX_Control(pDX, IDC_EDIT_GRAVIDANZE, m_EditGravidanze_Ctrl);
	DDX_Control(pDX, IDC_EDIT_MALATTIEIMPORTANTI, m_EditMalattieImportanti_Ctrl);
	DDX_Control(pDX, IDC_EDIT_VALUTAZIONEFAMILIARE, m_EditValutazioneFamiliare_Ctrl);
	DDX_Control(pDX, IDC_EDIT_PROFESSIONE, m_EditProfessione_Ctrl);
	DDX_Control(pDX, IDC_EDIT_HOBBY, m_EditHobby_Ctrl);
	DDX_Control(pDX, IDC_EDIT_VISTA, m_EditVista_Ctrl);
	DDX_Control(pDX, IDC_EDIT_STOMATOGNATICO, m_EditStomatognatico_Ctrl);
	DDX_Control(pDX, IDC_EDIT_CICATRICI, m_EditCicatrici_Ctrl);
	DDX_Control(pDX, IDC_EDIT_MICROGALVANISMI, m_EditMicrogalvanismi_Ctrl);
	DDX_Control(pDX, IDC_EDIT_BILANCIOPOSTURALE, m_EditBilancioPosturale_Ctrl);
	DDX_Control(pDX, IDC_EDIT_CHINESIOLOGICI, m_EditChinesiologici_Ctrl);
	DDX_Control(pDX, IDC_EDIT_DIAGNOSI, m_EditDiagnosi_Ctrl);
	DDX_Control(pDX, IDC_EDIT_CARATTERISTICHESINTOMO, m_EditCaratteristicheSintomo_Ctrl);
	DDX_Control(pDX, IDC_EDIT_PELLE, m_EditPelle_Ctrl);
	DDX_Control(pDX, IDC_EDIT_ALTRO, m_EditAltro_Ctrl);
}


BEGIN_MESSAGE_MAP(CMoreDataDlg, CDialog)
	ON_BN_CLICKED(ID_BUTTON_OK, &CMoreDataDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_DIARIO, &CMoreDataDlg::OnBnClickedButtonDiario)	
END_MESSAGE_MAP()


// CMoreDataDlg message handlers

void CMoreDataDlg::OnCancel()
{
	CDialog::OnCancel();
}

void CMoreDataDlg::OnOK()
{
}

BOOL CMoreDataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!m_pPatientRecord)
	{
		EndDialog(IDCANCEL);
		return TRUE;
	}

	CString caption;
	caption.Format("Informazioni %s %s", m_pPatientRecord->m_Nome, m_pPatientRecord->m_Cognome);
	SetWindowText(caption);

	m_EditMotivoConsulto_Ctrl.SetWindowText(m_pPatientRecord->m_MotivoConsulto);
	m_EditInsorgenzaSintomi_Ctrl.SetWindowText(m_pPatientRecord->m_TempoInsorgenzaSintomi);
	m_EditCausaScatenante_Ctrl.SetWindowText(m_pPatientRecord->m_CausaScatenante);
	m_EditCaratteristicheSintomo_Ctrl.SetWindowText(m_pPatientRecord->m_CaratteristicheSintomo);
	m_EditTerapiePrecedenti_Ctrl.SetWindowText(m_pPatientRecord->m_TerapiePrecedenti);
	m_EditCardioresporatorio_Ctrl.SetWindowText(m_pPatientRecord->m_FunzionalitaCardioRespiratorio);
	m_EditCardiointestinale_Ctrl.SetWindowText(m_pPatientRecord->m_FunzionalitaCardioIntestinale);
	m_EditUrogenitale_Ctrl.SetWindowText(m_pPatientRecord->m_FunzionalitaUroGenitale);
	m_EditRespiratorio_Ctrl.SetWindowText(m_pPatientRecord->m_FunzionalitaRespiratorio);
	m_EditPelle_Ctrl.SetWindowText(m_pPatientRecord->m_FunzionalitaPelle);
	m_EditAltro_Ctrl.SetWindowText(m_pPatientRecord->m_Altro);
	m_EditDiagnosi_Ctrl.SetWindowText(m_pPatientRecord->m_Diagnosi);
	m_EditEsamiDiagnostici_Ctrl.SetWindowText(m_pPatientRecord->m_EsamiDiagnosticiSpecialistici);
	m_EditUsoFarmaci_Ctrl.SetWindowText(m_pPatientRecord->m_UsoFarmaci);
	m_EditAlimentazione_Ctrl.SetWindowText(m_pPatientRecord->m_Alimentazione);
	m_EditVariazionePeso_Ctrl.SetWindowText(m_pPatientRecord->m_VariazionePeso);
	m_EditSonnoSveglia_Ctrl.SetWindowText(m_pPatientRecord->m_RitmoSonno);
	m_EditCefalee_Ctrl.SetWindowText(m_pPatientRecord->m_Cefalee);
	m_EditTraumatismi_Ctrl.SetWindowText(m_pPatientRecord->m_Traumatismi);
	m_EditInterventi_Ctrl.SetWindowText(m_pPatientRecord->m_InterventiChirurgici);
	m_EditGravidanze_Ctrl.SetWindowText(m_pPatientRecord->m_Gravidanze);
	m_EditMalattieImportanti_Ctrl.SetWindowText(m_pPatientRecord->m_MalattieImportanti);
	m_EditValutazioneFamiliare_Ctrl.SetWindowText(m_pPatientRecord->m_ValutazioneFamiliare);
	m_EditProfessione_Ctrl.SetWindowText(m_pPatientRecord->m_Professione);
	m_EditHobby_Ctrl.SetWindowText(m_pPatientRecord->m_Hobby);
	m_EditVista_Ctrl.SetWindowText(m_pPatientRecord->m_ValVista);
	m_EditStomatognatico_Ctrl.SetWindowText(m_pPatientRecord->m_ValApparatoStomatognatico);
	m_EditCicatrici_Ctrl.SetWindowText(m_pPatientRecord->m_ValCicatriciPatologiche);
	m_EditMicrogalvanismi_Ctrl.SetWindowText(m_pPatientRecord->m_MicroGalvanismi);
	m_EditBilancioPosturale_Ctrl.SetWindowText(m_pPatientRecord->m_ValBilancioPosturale);
	m_EditChinesiologici_Ctrl.SetWindowText(m_pPatientRecord->m_ValTestChinesiologici);
	m_EditDiagnosi_Ctrl.SetWindowText(m_pPatientRecord->m_Diagnosi);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CMoreDataDlg::OnBnClickedOk()
{
	if (!m_pPatientRecord)
		return;

	m_EditMotivoConsulto_Ctrl.GetWindowText(m_pPatientRecord->m_MotivoConsulto);
	m_EditInsorgenzaSintomi_Ctrl.GetWindowText(m_pPatientRecord->m_TempoInsorgenzaSintomi);
	m_EditCausaScatenante_Ctrl.GetWindowText(m_pPatientRecord->m_CausaScatenante);
	m_EditCaratteristicheSintomo_Ctrl.GetWindowText(m_pPatientRecord->m_CaratteristicheSintomo);
	m_EditTerapiePrecedenti_Ctrl.GetWindowText(m_pPatientRecord->m_TerapiePrecedenti);
	m_EditCardioresporatorio_Ctrl.GetWindowText(m_pPatientRecord->m_FunzionalitaCardioRespiratorio);
	m_EditCardiointestinale_Ctrl.GetWindowText(m_pPatientRecord->m_FunzionalitaCardioIntestinale);
	m_EditUrogenitale_Ctrl.GetWindowText(m_pPatientRecord->m_FunzionalitaUroGenitale);
	m_EditRespiratorio_Ctrl.GetWindowText(m_pPatientRecord->m_FunzionalitaRespiratorio);
	m_EditPelle_Ctrl.GetWindowText(m_pPatientRecord->m_FunzionalitaPelle);
	m_EditAltro_Ctrl.GetWindowText(m_pPatientRecord->m_Altro);
	m_EditEsamiDiagnostici_Ctrl.GetWindowText(m_pPatientRecord->m_EsamiDiagnosticiSpecialistici);
	m_EditUsoFarmaci_Ctrl.GetWindowText(m_pPatientRecord->m_UsoFarmaci);
	m_EditAlimentazione_Ctrl.GetWindowText(m_pPatientRecord->m_Alimentazione);
	m_EditVariazionePeso_Ctrl.GetWindowText(m_pPatientRecord->m_VariazionePeso);
	m_EditSonnoSveglia_Ctrl.GetWindowText(m_pPatientRecord->m_RitmoSonno);
	m_EditCefalee_Ctrl.GetWindowText(m_pPatientRecord->m_Cefalee);
	m_EditTraumatismi_Ctrl.GetWindowText(m_pPatientRecord->m_Traumatismi);
	m_EditInterventi_Ctrl.GetWindowText(m_pPatientRecord->m_InterventiChirurgici);
	m_EditGravidanze_Ctrl.GetWindowText(m_pPatientRecord->m_Gravidanze);
	m_EditMalattieImportanti_Ctrl.GetWindowText(m_pPatientRecord->m_MalattieImportanti);
	m_EditValutazioneFamiliare_Ctrl.GetWindowText(m_pPatientRecord->m_ValutazioneFamiliare);
	m_EditProfessione_Ctrl.GetWindowText(m_pPatientRecord->m_Professione);
	m_EditHobby_Ctrl.GetWindowText(m_pPatientRecord->m_Hobby);
	m_EditVista_Ctrl.GetWindowText(m_pPatientRecord->m_ValVista);
	m_EditStomatognatico_Ctrl.GetWindowText(m_pPatientRecord->m_ValApparatoStomatognatico);
	m_EditCicatrici_Ctrl.GetWindowText(m_pPatientRecord->m_ValCicatriciPatologiche);
	m_EditMicrogalvanismi_Ctrl.GetWindowText(m_pPatientRecord->m_MicroGalvanismi);
	m_EditBilancioPosturale_Ctrl.GetWindowText(m_pPatientRecord->m_ValBilancioPosturale);
	m_EditChinesiologici_Ctrl.GetWindowText(m_pPatientRecord->m_ValTestChinesiologici);
	m_EditDiagnosi_Ctrl.GetWindowText(m_pPatientRecord->m_Diagnosi);
	
	CDialog::OnOK();
}

void CMoreDataDlg::OnBnClickedButtonDiario()
{
	CRulerRichEditCtrlDlg dlg(m_pPatientRecord);
	dlg.DoModal();
}

