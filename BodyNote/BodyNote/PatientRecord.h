#pragma once

// CPatientRecord command target

class CPatientRecord : public CObject
{
public:
	CPatientRecord();
	CPatientRecord(CPatientRecord& record);

	virtual ~CPatientRecord();
	
public:
	virtual CPatientRecord&	operator =(CPatientRecord& record);

	void	ToFile(CString path);
	BOOL	FromFile(CString path);
	BOOL	IsValid(BOOL bTestCreationDate = TRUE);

	void	Empty();

public:
	long			m_ID; 
	CString			m_DataCreazione;
	CString			m_Nome;
	CString			m_Cognome;
	CString			m_Telefono;
	CString			m_Email;
	CString			m_DataNascita;

	CString			m_MotivoConsulto;
	CString			m_TempoInsorgenzaSintomi;
	CString			m_CausaScatenante;
	CString			m_CaratteristicheSintomo;
	CString			m_TerapiePrecedenti;
	CString			m_FunzionalitaCardioRespiratorio;
	CString			m_FunzionalitaCardioIntestinale;
	CString			m_FunzionalitaUroGenitale;
	CString			m_FunzionalitaRespiratorio;
	CString			m_FunzionalitaPelle;
	CString			m_EsamiDiagnosticiSpecialistici;
	CString			m_UsoFarmaci;
	CString			m_Alimentazione;
	CString			m_VariazionePeso;
	CString			m_RitmoSonno;
	CString			m_Cefalee;
	CString			m_Traumatismi;
	CString			m_InterventiChirurgici;
	CString			m_Gravidanze;
	CString			m_MalattieImportanti;
	CString			m_ValutazioneFamiliare;
	CString			m_Professione;
	CString			m_Hobby;
	CString			m_Altro;

	CString			m_ValVista;
	CString			m_ValApparatoStomatognatico;
	CString			m_ValCicatriciPatologiche;
	CString			m_MicroGalvanismi;
	CString			m_ValBilancioPosturale;
	CString			m_ValTestChinesiologici;
	CString			m_ValAltro;

	CString			m_Diagnosi;
	CStringArray	m_VisitPictures;
	CStringArray	m_PicComments;
};


