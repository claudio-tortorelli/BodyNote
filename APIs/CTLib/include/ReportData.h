#pragma once

// CReportData command target

class CReportData : public CObject
{
public:
	CReportData();
	CReportData(CReportData& data);
	virtual ~CReportData();

public:
	void	Reset();

public:
	int						m_OrderIndex;
	CString					m_Key;
	CString					m_Value;
	CArray<CString, LPCSTR>	m_Values;
	BOOL					m_bIsTitle;

public:
	virtual CReportData& operator= (CReportData& data);

};


