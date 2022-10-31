#pragma once

class CLicense
{
public:
	CLicense(void);
	CLicense(CLicense& license);
	virtual ~CLicense(void);

public:
	virtual CLicense&	operator =(CLicense& license);

	BOOL	ToFile(CString filePath);
	BOOL	FromFile(CString filePath);

public:
	CString		m_Owner;
	CString		m_StartDate;
	CString		m_EndDate;
	CString		m_EULA;
	CString		m_ShortDescription;
	CString		m_Version;

	CString		m_Software;

	CString		m_ID;
	CString		m_ProtectionCode;

};
