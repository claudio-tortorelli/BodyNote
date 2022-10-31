#pragma once
#include "cv.h"
#include "highgui.h"

#define TIMER_DISSOLVE_TEXT 1000

#ifndef _min
#define _min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef _max
#define _max(a, b) (((a) > (b)) ? (a) : (b))
#endif

// CPreviewWnd
/*
	ver 1.4 Mediscan, corretta inizializzazione
	ver 1.3 RTBundler, no flickerio
	Ver 1.2	SiteManager, supporta opencv 211
	Ver 1.1	Z-Map
	Ver 1.0 DarkLight
*/

class CPreviewWnd : public CStatic
{
	DECLARE_DYNAMIC(CPreviewWnd)

public:
	CPreviewWnd();
	virtual ~CPreviewWnd();

public:
	CString			GetImagePath(){return m_ImagePath;}
	
	BOOL			SetImage(CString path, CvScalar* pRectangleColor = NULL, int rectangleThickness = 9, CvScalar* pCrossColor = NULL, int crossThickness = 9);
	BOOL			SetImage(IplImage* pIplLoad = NULL, CvScalar* pRectangleColor = NULL, int rectangleThickness = 9, CvScalar* pCrossColor = NULL, int crossThickness = 9);
	
	void			SetEnableZoom(BOOL bVal = TRUE){m_bEnableZoom = bVal;}
	BOOL			IsZoomEnabled(){return m_bEnableZoom;}

	BOOL			UpdateView(IplImage* pIplUpd);
		
	BOOL			SaveImage(CString path);
	BOOL			SaveOrigImage(CString path);

	BOOL			FitImageToClient(IplImage* pIplLoad = NULL);
	void			ResetZoom();

	void			SetBackground(COLORREF color){m_Background = color;}
	COLORREF		GetBackground(){return m_Background;}

	IplImage *		GetDrawIpl() {return m_pIplToDraw;}
	IplImage *		GetOrigIpl() {return m_pIplOrig;}

protected:
	CvPoint			ScalePtToPicture(CvPoint pt);
	CvPoint			ScalePtToClient(CvPoint pt);

	CvPoint2D32f	ScalePtToPicture(CvPoint2D32f pt);
	CvPoint2D32f	ScalePtToClient(CvPoint2D32f pt);

	CRect			GetCurrentDisplayedArea(){return m_CurrentDispArea;} // pixel

	virtual void	DrawToHDC(HDC hDC = NULL, const IplImage* pIplToDraw = NULL);

	void			DoZoom();
	
/////////////
public:

protected:
	CString		m_ImagePath;

	IplImage*	m_pIplToDraw;
	IplImage*	m_pIplOrig;
	IplImage*	m_pIplZoomed;

	CRect		m_CurrentDispArea;
	
	CRect		m_FrameRect;
	CvRect		m_AligmentROI;

	double		m_FrameScale;

	BOOL		m_bCreateHistograms;
	BOOL		m_bEnableZoom;

	CPoint*		m_pZoomPt1;
	CPoint*		m_pZoomPt2;

	CPoint		m_CurMousePt;
	CPoint		m_PrevMousePt;

	CPoint		m_AbsoluteTL;

	int			m_DissolveCounter;
	int			m_ZoomPer;

	HBITMAP		m_hBitmap;

	BOOL		m_bDrawingToHDC;
	CBrush		m_Brush;

	COLORREF	m_Background;

	CvScalar *	m_pRectangleColor;
	int			m_RectangleThickness;

	CvScalar *	m_pCrossColor;
	int			m_CrossThickness;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


