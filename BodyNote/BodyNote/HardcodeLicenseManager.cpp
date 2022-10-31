#include "StdAfx.h"
#include "BodyNote.h"
#include "HardcodeLicenseManager.h"

CHardcodeLicenseManager::CHardcodeLicenseManager(char key[16])
{
	m_LicExt = CString("lic");
	sprintf_s(m_key, 16, key);
}

CHardcodeLicenseManager::~CHardcodeLicenseManager(void)
{
}

int	CHardcodeLicenseManager::LoadLicenses(CString licFolder)
{
	m_LicLoaded.RemoveAll();

	char appName[4096];
	char drive[8];
	char path[4096];

	if (licFolder.IsEmpty())
	{
		GetModuleFileName(NULL, appName, 4096);
		_splitpath_s(appName, drive, 8, path, 4096, NULL, 0, NULL, 0);
	}
	else
		_splitpath_s(CT_OptimizePath(licFolder,TRUE), drive, 8, path, 4096, NULL, 0, NULL, 0);

	char licPath[4096];
	_makepath_s(licPath, 4096, drive, path, "*", m_LicExt);


	char newlicPath[4096];
	_makepath_s(newlicPath, 4096, drive, path, "nuova_licenza", "txt");


	CLicense curLic;		
	//if (GetKeyState(VK_SHIFT) & 0x8000)
	CFileFind ff;
	BOOL bFound = ff.FindFile(newlicPath);
	if (bFound)
	{
		curLic.m_ProtectionCode = CT_GetDriveSerial(drive);
		curLic.m_Owner = "Test Test";
		curLic.m_StartDate = "20141105";
		curLic.m_EndDate = "";
		curLic.m_Version = "3.0";
		curLic.m_ID = "LIC_001";

		CString licPath;
		licPath.Format("%s\\%s\\%s\\%s.%s",	drive, path, licFolder, curLic.m_ID, m_LicExt);
		licPath = CT_OptimizePath(licPath, FALSE);
		curLic.ToFile(licPath);
		theApp.CryptDecryptFile(licPath, TRUE, FALSE);

		DeleteFile(newlicPath);
	}
	bFound = ff.FindFile(licPath);
	while (bFound)
	{
		bFound = ff.FindNextFile();
		if (ff.IsDots() || ff.IsDirectory())
			continue;
		CString pathl = ff.GetFilePath();
		if (pathl.IsEmpty())
			continue;
		theApp.CryptDecryptFile(pathl, FALSE, FALSE);
		if (curLic.FromFile(pathl))
			m_LicLoaded.Add(curLic);
		theApp.CryptDecryptFile(pathl, TRUE, FALSE);
	}
	ff.Close();
	return m_LicLoaded.GetSize();
}

BOOL CHardcodeLicenseManager::GetLicense(CLicense& Lic, CString licId)
{
	if (m_LicLoaded.GetSize() == 0)
		return FALSE;
	BOOL bFound = FALSE;
	if (!licId.IsEmpty())
	{
		for (int iLic = 0; iLic < m_LicLoaded.GetSize(); iLic++)
		{
			Lic = m_LicLoaded[iLic];
			if (Lic.m_ID.Compare(licId) == 0)
			{
				bFound = TRUE;
				break;
			}
		}
		if (!bFound)
			return FALSE;
	}
	else
		Lic = m_LicLoaded[0];
	return TRUE;
}

BOOL CHardcodeLicenseManager::CheckProtectionCode(CString code, CString licId)
{
	if (m_LicLoaded.GetSize() == 0)
		return FALSE;
	CLicense Lic;
	if (!GetLicense(Lic, licId))
		return FALSE;
	if (Lic.m_ProtectionCode.Compare(code) == 0)
		return TRUE;
	return FALSE;
}

BOOL CHardcodeLicenseManager::IsLicenseFree(CString licId)
{
	if (m_LicLoaded.GetSize() == 0)
		return FALSE;
	CLicense Lic;
	if (!GetLicense(Lic, licId))
		return FALSE;
	return Lic.m_ProtectionCode.IsEmpty();
}

BOOL CHardcodeLicenseManager::IsExpired(CString licId)
{
	return FALSE;
}

CString CHardcodeLicenseManager::GetOwner(CString licId)
{
	if (m_LicLoaded.GetSize() == 0)
		return "";
	CLicense Lic;
	if (!GetLicense(Lic, licId))
		return "";
	return Lic.m_Owner;
}

CString CHardcodeLicenseManager::GetStartDate(CString licId)
{
	if (m_LicLoaded.GetSize() == 0)
		return "";
	CLicense Lic;
	if (!GetLicense(Lic, licId))
		return "";
	return Lic.m_StartDate;
}

CString CHardcodeLicenseManager::GetEndDate(CString licId)
{
	if (m_LicLoaded.GetSize() == 0)
		return "";
	CLicense Lic;
	if (!GetLicense(Lic, licId))
		return "";
	return Lic.m_EndDate;
}

CString CHardcodeLicenseManager::GetEula(CString licId)
{
	if (m_LicLoaded.GetSize() == 0)
		return "";
	CLicense Lic;
	if (!GetLicense(Lic, licId))
		return "";
	return Lic.m_EULA;
}

CString CHardcodeLicenseManager::GetShortDescription(CString licId)
{
	if (m_LicLoaded.GetSize() == 0)
		return "";
	CLicense Lic;
	if (!GetLicense(Lic, licId))
		return "";
	return Lic.m_ShortDescription;
}

CString CHardcodeLicenseManager::GetVersion(CString licId)
{
	if (m_LicLoaded.GetSize() == 0)
		return "";
	CLicense Lic;
	if (!GetLicense(Lic, licId))
		return "";
	return Lic.m_Version;
}

CString CHardcodeLicenseManager::GetSoftware(CString licId)
{
	if (m_LicLoaded.GetSize() == 0)
		return "";
	CLicense Lic;
	if (!GetLicense(Lic, licId))
		return "";
	return Lic.m_Software;
}

CString CHardcodeLicenseManager::GetID(int licIndex)
{
	if (licIndex < 0 || licIndex >= m_LicLoaded.GetCount())
		return "";
	return m_LicLoaded[licIndex].m_ID;
}