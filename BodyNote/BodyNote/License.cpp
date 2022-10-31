#include "StdAfx.h"
#include "License.h"

CLicense::CLicense(void)
{
}

CLicense::CLicense(CLicense& license)
{
	*this = license;
}

CLicense::~CLicense(void)
{
}

CLicense& CLicense::operator =(CLicense& license)
{
	m_Owner = license.m_Owner;
	m_StartDate = license.m_StartDate;
	m_EndDate = license.m_EndDate;
	m_EULA = license.m_EULA;
	m_ShortDescription = license.m_ShortDescription;
	m_Version = license.m_Version;

	m_Software = license.m_Software;

	m_ID = license.m_ID;
	m_ProtectionCode = license.m_ProtectionCode;
		
	return *this;
}

BOOL CLicense::ToFile(CString filePath)
{
	if (filePath.IsEmpty())
		return FALSE;

	DeleteFile(filePath);

	WritePrivateProfileString("LicenseData", "Owner", m_Owner, filePath);
	WritePrivateProfileString("LicenseData", "StartDate", m_StartDate, filePath);
	WritePrivateProfileString("LicenseData", "EndDate", m_EndDate, filePath);
	WritePrivateProfileString("LicenseData", "EULA", m_EULA, filePath);
	WritePrivateProfileString("LicenseData", "ShortDescription", m_ShortDescription, filePath);
	WritePrivateProfileString("LicenseData", "Version", m_Version, filePath);
	WritePrivateProfileString("LicenseData", "Software", m_Software, filePath);
	WritePrivateProfileString("LicenseData", "ID", m_ID, filePath);
	WritePrivateProfileString("LicenseData", "ProtectionCode", m_ProtectionCode, filePath);
	
	return TRUE;
}

BOOL CLicense::FromFile(CString filePath)
{
	if (filePath.IsEmpty())
		return FALSE;

	char buf[4096];
	GetPrivateProfileString("LicenseData", "Owner", "", buf, 4096, filePath);
	m_Owner = buf;
	GetPrivateProfileString("LicenseData", "StartDate", "", buf, 4096, filePath);
	m_StartDate = buf;
	GetPrivateProfileString("LicenseData", "EndDate", "", buf, 4096, filePath);
	m_EndDate = buf;
	GetPrivateProfileString("LicenseData", "EULA", "", buf, 4096, filePath);
	m_EULA = buf;
	GetPrivateProfileString("LicenseData", "ShortDescription", "", buf, 4096, filePath);
	m_ShortDescription = buf;
	GetPrivateProfileString("LicenseData", "Version", "", buf, 4096, filePath);
	m_Version = buf;
	GetPrivateProfileString("LicenseData", "Software", "", buf, 4096, filePath);
	m_Software = buf;
	GetPrivateProfileString("LicenseData", "ID", "", buf, 4096, filePath);
	m_ID = buf;
	GetPrivateProfileString("LicenseData", "ProtectionCode", "", buf, 4096, filePath);
	m_ProtectionCode = buf;

	return TRUE;
}