// BackupProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BodyNote.h"
#include "BackupProgressDlg.h"
#include "afxdialogex.h"


// CBackupProgressDlg dialog

IMPLEMENT_DYNAMIC(CBackupProgressDlg, CDialogEx)

CBackupProgressDlg::CBackupProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBackupProgressDlg::IDD, pParent)
{

}

CBackupProgressDlg::~CBackupProgressDlg()
{
}

void CBackupProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_BACK, m_Progress_Ctrl);
}


BEGIN_MESSAGE_MAP(CBackupProgressDlg, CDialogEx)
END_MESSAGE_MAP()


// CBackupProgressDlg message handlers
