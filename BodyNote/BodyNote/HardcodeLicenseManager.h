#pragma once
#include "License.h"

class CHardcodeLicenseManager
{
public:
	CHardcodeLicenseManager(char key[16]);
	virtual ~CHardcodeLicenseManager(void);

public:
	int		LoadLicenses(CString licFolder = "");
	int		GetLicenseCount(){return m_LicLoaded.GetCount();}

	BOOL	CheckProtectionCode(CString code, CString licId = "");
	BOOL	IsLicenseFree(CString licId = "");
	BOOL	IsExpired(CString licId = "");

	CString GetOwner(CString licId = "");
	CString GetStartDate(CString licId = "");
	CString GetEndDate(CString licId = "");
	CString GetEula(CString licId = "");
	CString GetShortDescription(CString licId = "");
	CString GetVersion(CString licId = "");

	CString GetSoftware(CString licId = "");
	CString GetID(int licIndex = 0);
	BOOL	GetLicense(CLicense& Lic, CString licId = "");

	void	SetLicExt(CString ext){m_LicExt = ext;}

protected:
	CArray<CLicense, CLicense>	m_LicLoaded;
	CString						m_LicExt;

	char						m_key[16];
};
