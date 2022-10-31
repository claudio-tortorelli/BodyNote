// PatientRecord.cpp : implementation file
//

#include "stdafx.h"
#include "BodyNote.h"
#include "PatientRecord.h"


// CPatientRecord

CPatientRecord::CPatientRecord()
{
	m_ID = -1;
}

CPatientRecord::CPatientRecord(CPatientRecord& record)
{
	*this = record;
}

CPatientRecord::~CPatientRecord()
{
}

// CPatientRecord member functions
CPatientRecord& CPatientRecord::operator =(CPatientRecord& record)
{
	m_ID = record.m_ID; 
	m_DataCreazione = record.m_DataCreazione;
	m_Nome = record.m_Nome;
	m_Cognome = record.m_Cognome;
	m_Telefono = record.m_Telefono;
	m_Email = record.m_Email;
	m_DataNascita = record.m_DataNascita;

	m_MotivoConsulto = record.m_MotivoConsulto;
	m_TempoInsorgenzaSintomi = record.m_TempoInsorgenzaSintomi;
	m_CausaScatenante = record.m_CausaScatenante;
	m_CaratteristicheSintomo = record.m_CaratteristicheSintomo;
	m_TerapiePrecedenti = record.m_TerapiePrecedenti;
	m_FunzionalitaCardioRespiratorio = record.m_FunzionalitaCardioRespiratorio;
	m_FunzionalitaCardioIntestinale = record.m_FunzionalitaCardioIntestinale;
	m_FunzionalitaUroGenitale = record.m_FunzionalitaUroGenitale;
	m_FunzionalitaRespiratorio = record.m_FunzionalitaRespiratorio;
	m_FunzionalitaPelle = record.m_FunzionalitaPelle;
	m_Altro = record.m_Altro;

	m_EsamiDiagnosticiSpecialistici = record.m_EsamiDiagnosticiSpecialistici;
	m_UsoFarmaci = record.m_UsoFarmaci;
	m_Alimentazione = record.m_Alimentazione;
	m_VariazionePeso = record.m_VariazionePeso;
	m_RitmoSonno = record.m_RitmoSonno;
	m_Cefalee = record.m_Cefalee;
	m_Traumatismi = record.m_Traumatismi;
	m_InterventiChirurgici = record.m_InterventiChirurgici;
	m_Gravidanze = record.m_Gravidanze;
	m_MalattieImportanti = record.m_MalattieImportanti;
	m_ValutazioneFamiliare = record.m_ValutazioneFamiliare;
	m_Professione = record.m_Professione;
	m_Hobby = record.m_Hobby;
	
	m_ValVista = record.m_ValVista;
	m_ValApparatoStomatognatico = record.m_ValApparatoStomatognatico;
	m_ValCicatriciPatologiche = record.m_ValCicatriciPatologiche;
	m_MicroGalvanismi = record.m_MicroGalvanismi;
	m_ValBilancioPosturale = record.m_ValBilancioPosturale;
	m_ValTestChinesiologici = record.m_ValTestChinesiologici;
	m_ValAltro = record.m_ValAltro;

	m_Diagnosi = record.m_Diagnosi;

	m_VisitPictures.RemoveAll();
	int nRec = record.m_VisitPictures.GetSize();
	for (int i = 0; i < nRec; i++)
		m_VisitPictures.Add(record.m_VisitPictures[i]);

	m_PicComments.RemoveAll();
	nRec = record.m_PicComments.GetSize();
	for (int i = 0; i < nRec; i++)
		m_PicComments.Add(record.m_PicComments[i]);

	return *this;
}

void CPatientRecord::ToFile(CString path)
{
	if (path.IsEmpty())
		return;

	DeleteFile(path);

	CString tmp;
	tmp.Format("%ld", m_ID);
	WritePrivateProfileString("PatientData", "ID", tmp, path);
	WritePrivateProfileString("PatientData", "CreationDate", m_DataCreazione, path);	
	WritePrivateProfileString("PatientData", "Name", m_Nome, path);
	WritePrivateProfileString("PatientData", "Surname", m_Cognome, path);
	WritePrivateProfileString("PatientData", "Phone", m_Telefono, path);
	WritePrivateProfileString("PatientData", "Email", m_Email, path);
	WritePrivateProfileString("PatientData", "BirthDate", m_DataNascita, path); 
	WritePrivateProfileString("PatientData", "VisitCause", m_MotivoConsulto, path);
	WritePrivateProfileString("PatientData", "Diagnosis", m_Diagnosi, path);

	WritePrivateProfileString("PatientData", "TempoInsorgenzaSintomi", m_TempoInsorgenzaSintomi, path);
	WritePrivateProfileString("PatientData", "CausaScatenante", m_CausaScatenante, path);
	WritePrivateProfileString("PatientData", "CaratteristicheSintomo", m_CaratteristicheSintomo, path);	
	WritePrivateProfileString("PatientData", "TerapiePrecedenti", m_TerapiePrecedenti, path);
	WritePrivateProfileString("PatientData", "FunzionalitaCardioRespiratorio", m_FunzionalitaCardioRespiratorio, path);
	WritePrivateProfileString("PatientData", "FunzionalitaCardioIntestinale", m_FunzionalitaCardioIntestinale, path);
	WritePrivateProfileString("PatientData", "FunzionalitaUroGenitale", m_FunzionalitaUroGenitale, path);
	WritePrivateProfileString("PatientData", "FunzionalitaRespiratorio", m_FunzionalitaRespiratorio, path);
	WritePrivateProfileString("PatientData", "FunzionalitaPelle", m_FunzionalitaPelle, path);
	WritePrivateProfileString("PatientData", "Altro", m_Altro, path);

	WritePrivateProfileString("PatientData", "EsamiDiagnosticiSpecialistici", m_EsamiDiagnosticiSpecialistici, path);
	WritePrivateProfileString("PatientData", "UsoFarmaci", m_UsoFarmaci, path);
	WritePrivateProfileString("PatientData", "Alimentazione", m_Alimentazione, path);
	WritePrivateProfileString("PatientData", "VariazionePeso", m_VariazionePeso, path);
	WritePrivateProfileString("PatientData", "RitmoSonno", m_RitmoSonno, path);
	WritePrivateProfileString("PatientData", "Cefalee", m_Cefalee, path);
	WritePrivateProfileString("PatientData", "Traumatismi", m_Traumatismi, path);
	WritePrivateProfileString("PatientData", "InterventiChirurgici", m_InterventiChirurgici, path);
	WritePrivateProfileString("PatientData", "Gravidanze", m_Gravidanze, path);
	WritePrivateProfileString("PatientData", "MalattieImportanti", m_MalattieImportanti, path);
	WritePrivateProfileString("PatientData", "ValutazioneFamiliare", m_ValutazioneFamiliare, path);
	WritePrivateProfileString("PatientData", "Professione", m_Professione, path);
	WritePrivateProfileString("PatientData", "Hobby", m_Hobby, path);

	WritePrivateProfileString("PatientData", "ValVista", m_ValVista, path);
	WritePrivateProfileString("PatientData", "ValApparatoStomatognatico", m_ValApparatoStomatognatico, path);
	WritePrivateProfileString("PatientData", "ValCicatriciPatologiche", m_ValCicatriciPatologiche, path);
	WritePrivateProfileString("PatientData", "MicroGalvanismi", m_MicroGalvanismi, path);
	WritePrivateProfileString("PatientData", "ValBilancioPosturale", m_ValBilancioPosturale, path);
	WritePrivateProfileString("PatientData", "ValTestChinesiologici", m_ValTestChinesiologici, path);
	WritePrivateProfileString("PatientData", "ValAltro", m_ValAltro, path);
}

BOOL CPatientRecord::FromFile(CString path)
{
	if (path.IsEmpty())
		return FALSE;

	char buf[4096];
	GetPrivateProfileString("PatientData", "ID", "-1", buf, 4096, path);
	m_ID = atoi(buf);

	GetPrivateProfileString("PatientData", "CreationDate", "", buf, 4096, path);
	m_DataCreazione = CString(buf);	
	GetPrivateProfileString("PatientData", "Name", "", buf, 4096, path);
	m_Nome = CString(buf);
	GetPrivateProfileString("PatientData", "Surname", "", buf, 4096, path);
	m_Cognome = CString(buf);
	GetPrivateProfileString("PatientData", "Phone", "", buf, 4096, path);
	m_Telefono = CString(buf);
	GetPrivateProfileString("PatientData", "Email", "", buf, 4096, path);
	m_Email = CString(buf);
	GetPrivateProfileString("PatientData", "BirthDate", "", buf, 4096, path); 
	m_DataNascita = CString(buf);
	GetPrivateProfileString("PatientData", "VisitCause", "", buf, 4096, path);
	m_MotivoConsulto = CString(buf);
	GetPrivateProfileString("PatientData", "Diagnosis", "", buf, 4096, path);
	m_Diagnosi = CString(buf);
	
	GetPrivateProfileString("PatientData", "TempoInsorgenzaSintomi", "", buf, 4096, path);
	m_TempoInsorgenzaSintomi = CString(buf);
	GetPrivateProfileString("PatientData", "CausaScatenante", "", buf, 4096, path);
	m_CausaScatenante = CString(buf);
	GetPrivateProfileString("PatientData", "CaratteristicheSintomo", "", buf, 4096, path);
	m_CaratteristicheSintomo = CString(buf);
	GetPrivateProfileString("PatientData", "TerapiePrecedenti", "", buf, 4096, path);
	m_TerapiePrecedenti = CString(buf);
	GetPrivateProfileString("PatientData", "FunzionalitaCardioRespiratorio", "", buf, 4096, path);
	m_FunzionalitaCardioRespiratorio = CString(buf);
	GetPrivateProfileString("PatientData", "FunzionalitaCardioIntestinale", "", buf, 4096, path);
	m_FunzionalitaCardioIntestinale = CString(buf);
	GetPrivateProfileString("PatientData", "FunzionalitaUroGenitale", "", buf, 4096, path);
	m_FunzionalitaUroGenitale = CString(buf);
	GetPrivateProfileString("PatientData", "FunzionalitaRespiratorio", "", buf, 4096, path);
	m_FunzionalitaRespiratorio = CString(buf);
	GetPrivateProfileString("PatientData", "FunzionalitaPelle", "", buf, 4096, path);
	m_FunzionalitaPelle = CString(buf);
	GetPrivateProfileString("PatientData", "Altro", "", buf, 4096, path);
	m_Altro = CString(buf);

	GetPrivateProfileString("PatientData", "EsamiDiagnosticiSpecialistici", "", buf, 4096, path);
	m_EsamiDiagnosticiSpecialistici = CString(buf);
	GetPrivateProfileString("PatientData", "UsoFarmaci", "", buf, 4096, path);
	m_UsoFarmaci = CString(buf);
	GetPrivateProfileString("PatientData", "Alimentazione", "", buf, 4096, path);
	m_Alimentazione = CString(buf);
	GetPrivateProfileString("PatientData", "VariazionePeso", "", buf, 4096, path);
	m_VariazionePeso = CString(buf);
	GetPrivateProfileString("PatientData", "RitmoSonno", "", buf, 4096, path);
	m_RitmoSonno = CString(buf);
	GetPrivateProfileString("PatientData", "Cefalee", "", buf, 4096, path);
	m_Cefalee = CString(buf);
	GetPrivateProfileString("PatientData", "Traumatismi", "", buf, 4096, path);
	m_Traumatismi = CString(buf);
	GetPrivateProfileString("PatientData", "InterventiChirurgici", "", buf, 4096, path);
	m_InterventiChirurgici = CString(buf);
	GetPrivateProfileString("PatientData", "Gravidanze", "", buf, 4096, path);
	m_Gravidanze = CString(buf);
	GetPrivateProfileString("PatientData", "MalattieImportanti", "", buf, 4096, path);
	m_MalattieImportanti = CString(buf);
	GetPrivateProfileString("PatientData", "ValutazioneFamiliare", "", buf, 4096, path);
	m_ValutazioneFamiliare = CString(buf);
	GetPrivateProfileString("PatientData", "Professione", "", buf, 4096, path);
	m_Professione = CString(buf);
	GetPrivateProfileString("PatientData", "Hobby", "", buf, 4096, path);
	m_Hobby = CString(buf);
	
	GetPrivateProfileString("PatientData", "ValVista", "", buf, 4096, path);
	m_ValVista = CString(buf);
	GetPrivateProfileString("PatientData", "ValApparatoStomatognatico", "", buf, 4096, path);
	m_ValApparatoStomatognatico = CString(buf);
	GetPrivateProfileString("PatientData", "ValCicatriciPatologiche", "", buf, 4096, path);
	m_ValCicatriciPatologiche = CString(buf);
	GetPrivateProfileString("PatientData", "MicroGalvanismi", "", buf, 4096, path);
	m_MicroGalvanismi = CString(buf);
	GetPrivateProfileString("PatientData", "ValBilancioPosturale", "", buf, 4096, path);
	m_ValBilancioPosturale = CString(buf);
	GetPrivateProfileString("PatientData", "ValTestChinesiologici", "", buf, 4096, path);
	m_ValTestChinesiologici = CString(buf);
	GetPrivateProfileString("PatientData", "ValAltro", "", buf, 4096, path);
	m_ValAltro = CString(buf);

	return TRUE;
}

BOOL CPatientRecord::IsValid(BOOL bTestCreationDate)
{
	if (m_ID < 0)
		return FALSE;

	if (bTestCreationDate && m_DataCreazione.IsEmpty())
		return FALSE;

	if (m_Nome.IsEmpty() || m_Cognome.IsEmpty())
		return FALSE;

	return TRUE;
}

void CPatientRecord::Empty()
{
	m_Nome.Empty();
	m_DataCreazione.Empty();
	m_Cognome.Empty();
	m_Telefono.Empty();
	m_Email.Empty();
	m_DataNascita.Empty();
	m_MotivoConsulto.Empty();
	m_Diagnosi.Empty();
	
	m_TempoInsorgenzaSintomi.Empty();
	m_CausaScatenante.Empty();
	m_CaratteristicheSintomo.Empty();
	m_TerapiePrecedenti.Empty();
	m_FunzionalitaCardioRespiratorio.Empty();
	m_FunzionalitaCardioIntestinale.Empty();
	m_FunzionalitaUroGenitale.Empty();
	m_FunzionalitaRespiratorio.Empty();
	m_FunzionalitaPelle.Empty();
	m_Altro.Empty();
	m_EsamiDiagnosticiSpecialistici.Empty();
	m_UsoFarmaci.Empty();
	m_Alimentazione.Empty();
	m_VariazionePeso.Empty();
	m_RitmoSonno.Empty();
	m_Cefalee.Empty();
	m_Traumatismi.Empty();
	m_InterventiChirurgici.Empty();
	m_Gravidanze.Empty();
	m_MalattieImportanti.Empty();
	m_ValutazioneFamiliare.Empty();
	m_Professione.Empty();
	m_Hobby.Empty();

	m_ValVista.Empty();
	m_ValApparatoStomatognatico.Empty();
	m_ValCicatriciPatologiche.Empty();
	m_MicroGalvanismi.Empty();
	m_ValBilancioPosturale.Empty();
	m_ValTestChinesiologici.Empty();
	m_ValAltro.Empty();

	m_VisitPictures.RemoveAll();
	m_PicComments.RemoveAll();
}