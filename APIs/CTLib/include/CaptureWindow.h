#pragma once

class CCaptureWindow
{
public:
	CCaptureWindow(void);
	virtual ~CCaptureWindow(void);

	BOOL	WndToBmp(CDC *pDC, CString szFile);
	HANDLE	DDBToDIB(CBitmap &bitmap, DWORD dwCompression, CPalette *pPal);
};
