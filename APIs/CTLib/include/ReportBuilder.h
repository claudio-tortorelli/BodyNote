#pragma once

/**
 * ReportBuilder dic-2011
 */

#include "ReportData.h"

typedef struct Tag
{
	CString		m_tag;
	CString		m_valueToSubstitute;
} Tag;

typedef struct imgTag
{
	CString		m_tag;
	BOOL		m_bRelativePath;	
	CString		m_OriginalPath;	
} imgTag;

typedef struct HTMLReportData
{
	CString		m_htmlPath; // destination html
	CString		m_htmlTemplatePath; // original template html (tag included)
	CString		m_cssTemplatePath; // original template css
	CString		m_dataFolderName; // data folder name related to destination html
	Tag*		m_pTag; // es. <!-- title -->, <!-- data -->
	int			m_nTag;
	imgTag*		m_pImgTag;
	int			m_nImages;
} HTMLReportData;


class CReportBuilder : public CObject
{
public:
	CReportBuilder();
	virtual ~CReportBuilder();

public:
	void	AddValue(CString key, CString value);
	void	AddValue(CString key, int value);
	void	AddValue(CString key, double value, int precision = 2);
	void	AddValue(CString key, CArray<CString, LPCSTR>* pValues);
	void	AddTitle(CString title);

	void	SetTXTPath(CString txtPath);
		
	void	ResetReport();

	BOOL	BuildReports();

	void	FillCommonHeader();
	void	FillCommonData();

	/// 
	BOOL	SetHTMLReportData(HTMLReportData data);
	BOOL	IsHTMLReportDataComplete();
	
protected:
	BOOL	BuildHTMLReport();

	int		GetSortedData(CArray<CReportData, CReportData>* pSortedData);

protected:
	int			m_nDataCount;
	CString		m_txtPath;

	CMap<CString, LPCSTR, CReportData, CReportData>	m_RepDataArray;

	///
	HTMLReportData m_HTMLReportData;	
};


