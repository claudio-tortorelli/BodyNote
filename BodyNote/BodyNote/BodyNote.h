// BodyNote.h : file di intestazione principale per l'applicazione PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "includere 'stdafx.h' prima di includere questo file per PCH"
#endif

#include "resource.h"		// simboli principali
#include "PatientRecord.h"

#define	SETTINGS_LOCATION_EXEC	1 // executable folder

typedef struct patientIndex
{
	int id;
	CString name;
	CString surname;
	CString creation;
}patientIndex;

class CBodyNoteApp : public CWinApp
{
public:
	CBodyNoteApp();

// Override
public:
	virtual BOOL	InitInstance();
	void			Initkey();

	BOOL			CryptDecryptFile(CString filePath, BOOL bCrypt = TRUE, BOOL doBackup = TRUE);
	int				GetPatientDB(CString workSpaceFolder, CArray<CPatientRecord, CPatientRecord>* pDBPatients, CProgressCtrl* pProgress, BOOL bForceCrypt = FALSE);

	void			RecursiveFileList(CString rootFolder, std::vector<string>& paths);

	CString			GetExecFolder();

	BOOL			UpdatePatientIndex(CString workSpaceFolder, CProgressCtrl* pProgress);
	int				LoadPatientIndex(CString workSpaceFolder, CArray<patientIndex, patientIndex>* pDBPatients, CProgressCtrl* pProgress);

	BOOL			LoadPatient(patientIndex pat, CPatientRecord& patient);

	int				GetGlobalID();

	CString			GetLastErrorString(DWORD errCode = -1);

	BOOL			DoWSBackup();

	BOOL			MakeBackup(CString filePath);

	BOOL			IsIndexCrypted(CString indexPath);

public:
	CString			m_WorkSpaceFolder;
	
protected:
	char			m_keyCrypt[16];
// Implementazione

	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();
};

extern CBodyNoteApp theApp;