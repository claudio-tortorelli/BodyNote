// SelectPatientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BodyNote.h"
#include "SelectPatientDlg.h"


// CSelectPatientDlg dialog

IMPLEMENT_DYNAMIC(CSelectPatientDlg, CDialog)

CSelectPatientDlg::CSelectPatientDlg(CArray<patientIndex, patientIndex>* pRecords, CWnd* pParent /*=NULL*/)
	: CDialog(CSelectPatientDlg::IDD, pParent)
{	
	m_pPatients = pRecords;
	m_bInitialized = FALSE;
}

CSelectPatientDlg::~CSelectPatientDlg()
{
}

void CSelectPatientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PATIENTS, m_ListPatient_Ctrl);
	DDX_Control(pDX, IDC_STATIC_RECORDFOUND, m_StaticRecordFound_Ctrl);
	DDX_Control(pDX, IDC_EDIT_SEARCH, m_EditSearch_Ctrl);
}


BEGIN_MESSAGE_MAP(CSelectPatientDlg, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PATIENTS, &CSelectPatientDlg::OnNMDblclkListPatients)
	ON_BN_CLICKED(IDOK, &CSelectPatientDlg::OnBnClickedOk)
	ON_EN_SETFOCUS(IDC_EDIT_SEARCH, &CSelectPatientDlg::OnEnSetfocusEditSearch)
	ON_EN_CHANGE(IDC_EDIT_SEARCH, &CSelectPatientDlg::OnEnChangeEditSearch)
END_MESSAGE_MAP()


// CSelectPatientDlg message handlers

BOOL CSelectPatientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!m_pPatients)
	{
		EndDialog(IDCANCEL);
		return TRUE;
	}

	CRect listRect;
	m_ListPatient_Ctrl.GetClientRect(&listRect);
	m_ListPatient_Ctrl.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	CString headers;
	headers.Format("Nome,%d;Creazione,%d;ID,%d", (int)(listRect.Width()*0.6), (int)(listRect.Width()*0.4), 0);
	m_ListPatient_Ctrl.SetHeadings( headers );

	CString itemID;

	int nPatients = m_pPatients->GetCount();
	for (int iPat = 0; iPat < nPatients; iPat++)
	{
		patientIndex curP = m_pPatients->GetAt(iPat);
		itemID.Format("%ld", curP.id);

		CString aaaa = curP.creation.Right(4);
		CString mm =  m_pPatients->GetAt(iPat).creation.Mid(3,2);
		CString dd =  m_pPatients->GetAt(iPat).creation.Left(2);
		CString cDate;
		cDate.Format("%s-%s-%s", aaaa, mm, dd);

		CString patName;
		patName.Format("%s %s", curP.surname, curP.name);

		m_ListPatient_Ctrl.AddItem( patName, cDate, itemID );
	}

	CString msg;
	msg.Format("%d record caricati nel workspace corrente", nPatients);
	m_StaticRecordFound_Ctrl.SetWindowText(msg);
	
	m_EditSearch_Ctrl.SetWindowText("Cerca...");

	m_bInitialized = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectPatientDlg::OnNMDblclkListPatients(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iItem = m_ListPatient_Ctrl.GetSelectionMark();
	if (iItem < 0)
		return;
	CString id = m_ListPatient_Ctrl.GetItemText(iItem,2);
	int idPat = atoi(id);

	int nPatients = m_pPatients->GetCount();
	for (int iPat = 0; iPat < nPatients; iPat++)
	{
		if (m_pPatients->GetAt(iPat).id == idPat)
		{
			m_SelectedRecord = m_pPatients->GetAt(iPat);
			break;
		}
	}
	CDialog::OnOK();
}

void CSelectPatientDlg::OnBnClickedOk()
{
	int iItem = m_ListPatient_Ctrl.GetSelectionMark();
	if (iItem < 0)
		return;
	CString id = m_ListPatient_Ctrl.GetItemText(iItem,2);
	int idPat = atoi(id);

	int nPatients = m_pPatients->GetCount();
	for (int iPat = 0; iPat < nPatients; iPat++)
	{
		if (m_pPatients->GetAt(iPat).id == idPat)
		{
			m_SelectedRecord = m_pPatients->GetAt(iPat);
			break;
		}
	}
	CDialog::OnOK();
}



void CSelectPatientDlg::OnEnSetfocusEditSearch()
{
	CString text;
	m_EditSearch_Ctrl.GetWindowText(text);
	if (text.Compare("Cerca...") == 0)
		m_EditSearch_Ctrl.SetWindowText("");
}


void CSelectPatientDlg::OnEnChangeEditSearch()
{
	if (!m_bInitialized)
		return;

	CString text;
	m_EditSearch_Ctrl.GetWindowText(text);
	
	text.MakeLower();

	m_ListPatient_Ctrl.DeleteAllItems();

	int nPatients = m_pPatients->GetCount();
	for (int iPat = 0; iPat < nPatients; iPat++)
	{
		patientIndex curP = m_pPatients->GetAt(iPat);
		CString itemID;
		itemID.Format("%ld", curP.id);

		CString aaaa = curP.creation.Right(4);
		CString mm =  m_pPatients->GetAt(iPat).creation.Mid(3,2);
		CString dd =  m_pPatients->GetAt(iPat).creation.Left(2);
		CString cDate;
		cDate.Format("%s-%s-%s", aaaa, mm, dd);

		CString patName;
		patName.Format("%s %s", curP.surname, curP.name);

		BOOL bMatch = FALSE;
		CString matchDate(cDate);
		CString matchName(patName);
		matchName.MakeLower();
		if ((matchDate.Find(text) < 0) && (matchName.Find(text) < 0) && !text.IsEmpty())
			continue;

		m_ListPatient_Ctrl.AddItem( patName, cDate, itemID );
	}
}
