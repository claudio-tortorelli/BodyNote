// PreviewWnd.cpp : implementation file
//

#include "stdafx.h"
#include ".\PreviewWnd.h"
#include <math.h>

using namespace std;

// CPreviewWnd

IMPLEMENT_DYNAMIC(CPreviewWnd, CStatic)

CPreviewWnd::CPreviewWnd()
{
	m_FrameScale = 1.0;
	m_bCreateHistograms = TRUE;
	m_pZoomPt1 = NULL;
	m_pZoomPt2 = NULL;
	m_pIplOrig = NULL;
	m_pIplZoomed = NULL;
	m_pIplToDraw  = NULL;
	m_bEnableZoom = TRUE;
	m_AbsoluteTL.x = 0;
	m_AbsoluteTL.y = 0;
	m_DissolveCounter = 0;
	m_ZoomPer = 0;
	m_Background = RGB(0,0,0);
	m_bDrawingToHDC = FALSE;
	
	m_Brush.CreateSolidBrush(RGB(255, 255, 255));

	m_pIplOrig = cvCreateImage(cvSize(100, 100), IPL_DEPTH_8U, 3);
	cvSetZero(m_pIplOrig);

	m_pRectangleColor = NULL;
	m_RectangleThickness = 9;

	m_pCrossColor = NULL;
	m_CrossThickness = 9;
}

CPreviewWnd::~CPreviewWnd()
{
	if (m_pZoomPt1)
		delete m_pZoomPt1;
	m_pZoomPt1 = NULL;

	if (m_pZoomPt2)
		delete m_pZoomPt2;
	m_pZoomPt2 = NULL;

	if (m_pIplOrig)
		cvReleaseImage(&m_pIplOrig);
	m_pIplOrig = NULL;

	if (m_pIplZoomed)
		cvReleaseImage(&m_pIplZoomed);
	m_pIplZoomed = NULL;

	if (m_pIplToDraw)
		cvReleaseImage(&m_pIplToDraw);
	m_pIplToDraw = NULL;	

	m_Brush.DeleteObject();
}


BEGIN_MESSAGE_MAP(CPreviewWnd, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CPreviewWnd message handlers
void CPreviewWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}

BOOL CPreviewWnd::OnEraseBkgnd(CDC* pDC)
{
	//return CStatic::OnEraseBkgnd(pDC);
	DrawToHDC();
	return TRUE;	
}


BOOL CPreviewWnd::SetImage(CString path, CvScalar* pRectangleColor, int rectangleThickness, CvScalar* pCrossColor, int crossThickness)
{
	IplImage* pIplLoad = NULL;
	if (!path.IsEmpty())
		pIplLoad = cvLoadImage(path);

	BOOL bRet = SetImage(pIplLoad, pRectangleColor, rectangleThickness, pCrossColor, crossThickness);

	if (pIplLoad)
		cvReleaseImage(&pIplLoad);

	if (bRet)
		m_ImagePath = path;

	return bRet;
}

BOOL CPreviewWnd::SetImage(IplImage* pIplLoad, CvScalar* pRectangleColor, int rectangleThickness, CvScalar* pCrossColor, int crossThickness)
{
	m_pRectangleColor = pRectangleColor;
	m_RectangleThickness = rectangleThickness;

	m_pCrossColor = pCrossColor;
	m_CrossThickness = crossThickness;

	if (m_pIplToDraw)
		cvReleaseImage(&m_pIplToDraw);
	m_pIplToDraw = NULL;

	if (m_pIplOrig)
		cvReleaseImage(&m_pIplOrig);
	m_pIplOrig = NULL;

	if (m_pIplZoomed)
		cvReleaseImage(&m_pIplZoomed);
	m_pIplZoomed = NULL;

	CRect winRect;
	GetWindowRect(winRect);

	if (!pIplLoad)
	{
		/*m_pIplToDraw = cvCreateImage(cvSize(winRect.Width(), winRect.Height()),IPL_DEPTH_8U, 3);
		cvSetZero(m_pIplToDraw);
		DrawToHDC();*/
		return FALSE;
	}

	BOOL bConverted = FALSE;
	IplImage* pIplPreview = NULL;
	if (pIplLoad->nChannels == 4)
	{
		pIplPreview = cvCreateImage(cvGetSize(pIplLoad), pIplLoad->depth, 3);
		cvCvtColor(pIplLoad, pIplPreview, CV_BGRA2RGB);
		bConverted = TRUE;
	}
	else if (pIplLoad->nChannels == 1)
	{
		pIplPreview = cvCreateImage(cvGetSize(pIplLoad), pIplLoad->depth, 3);
		cvCvtColor(pIplLoad, pIplPreview, CV_GRAY2RGB);
		bConverted = TRUE;
	}
	else
		pIplPreview = pIplLoad;

	if (pIplPreview->depth != IPL_DEPTH_8U)
	{
		IplImage* pTempIpl = cvCreateImage(cvGetSize(pIplPreview), IPL_DEPTH_8U, pIplPreview->nChannels);
		cvCvtScale(pIplPreview, pTempIpl);
		if (bConverted)
			cvReleaseImage(&pIplPreview);
		pIplPreview = pTempIpl;
		bConverted = TRUE;
	}

	if (!FitImageToClient(pIplPreview))
	{
		m_pIplToDraw = cvCreateImage(cvSize(winRect.Width(), winRect.Height()),IPL_DEPTH_8U, 3);
		cvFillImage(m_pIplToDraw, m_Background);
		DrawToHDC();
		return FALSE;
	}
	
	if (m_pIplOrig)
		cvReleaseImage(&m_pIplOrig);
	m_pIplOrig = cvCloneImage(pIplPreview);

	if (m_pIplZoomed)
		cvReleaseImage(&m_pIplZoomed);
	m_pIplZoomed = cvCloneImage(m_pIplOrig);

	if (bConverted)
	{
		cvReleaseImage(&pIplPreview);
		pIplPreview = NULL;
	}

	m_CurrentDispArea.left = 0;
	m_CurrentDispArea.right = m_pIplOrig->width-1;
	m_CurrentDispArea.top = 0;
	m_CurrentDispArea.bottom = m_pIplOrig->height-1;
	
	return TRUE;
}

BOOL CPreviewWnd::FitImageToClient(IplImage* pIplLoad)
{
	if (!pIplLoad)
		pIplLoad = m_pIplOrig;

	if (!pIplLoad)
		return FALSE;

	CRect winRect;
	GetWindowRect(winRect);
	winRect.right = _max(1, winRect.right-5);
	winRect.bottom = _max(1, winRect.bottom-5);

	IplImage* pIpl = cvCreateImage(cvSize(winRect.Width(), winRect.Height()),pIplLoad->depth, pIplLoad->nChannels);
	cvFillImage(pIpl,m_Background);

	int imgW = 0;
	int imgH = 0;
	if (pIplLoad->roi)
	{
		imgW = pIplLoad->roi->width;
		imgH = pIplLoad->roi->height;
	}
	else
	{
		imgW = pIplLoad->width;
		imgH = pIplLoad->height;
	}

	double frameAR = winRect.Width()/(double)winRect.Height();
	double imageAR = imgW/(double)imgH;

	int W = 0, H = 0;
	if(frameAR>imageAR)
	{
		H = winRect.Height();
		W = cvRound(winRect.Height()*imageAR);		
		m_FrameScale = winRect.Height()/(double)imgH;
	}
	else
	{
		W = winRect.Width();
		H = cvRound(winRect.Width()/(double)imageAR);
		m_FrameScale = winRect.Width()/(double)imgW;
	}
	
	IplImage* pIplResize = cvCreateImage(cvSize(W,H),pIplLoad->depth,pIplLoad->nChannels);
	cvResize(pIplLoad, pIplResize);

	m_AligmentROI.x = (winRect.Width()-pIplResize->width)/2;
	m_AligmentROI.y = (winRect.Height()-pIplResize->height)/2;
	m_AligmentROI.width = pIplResize->width;
	m_AligmentROI.height = pIplResize->height;

	cvSetImageROI(pIpl, m_AligmentROI);

	cvCopyImage(pIplResize,pIpl);

	cvResetImageROI(pIpl);

	m_FrameRect.top = 0;
	m_FrameRect.left = 0;
	m_FrameRect.bottom = winRect.Height()+1;
	m_FrameRect.right = winRect.Width()+1;

	if (m_pIplToDraw)
		cvReleaseImage(&m_pIplToDraw);
	m_pIplToDraw = cvCloneImage(pIpl);

	if (m_pRectangleColor)
		cvRectangle(m_pIplToDraw, cvPoint(0, 0), cvPoint(m_pIplToDraw->width-1, m_pIplToDraw->height-1), *m_pRectangleColor, m_RectangleThickness);

	if (m_pCrossColor)
	{
		cvLine(m_pIplToDraw, cvPoint(0, 0), cvPoint(m_pIplToDraw->width-1, m_pIplToDraw->height-1), *m_pCrossColor, m_CrossThickness);
		cvLine(m_pIplToDraw, cvPoint(m_pIplToDraw->width-1, 0), cvPoint(0, m_pIplToDraw->height-1), *m_pCrossColor, m_CrossThickness);
	}
	
	DrawToHDC();
	
	cvReleaseImage(&pIplResize);
	cvReleaseImage(&pIpl);
	
	return TRUE;
}

void CPreviewWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_bEnableZoom || !m_pIplOrig)
		return;

	if (m_DissolveCounter > 0)
		return;

	if (!m_pZoomPt1)
	{
		m_pZoomPt1 = new CPoint();	
		m_pZoomPt1->x = point.x - m_AligmentROI.x;
		m_pZoomPt1->y = point.y - m_AligmentROI.y;
	}
	else if (m_pZoomPt1 && !m_pZoomPt2)
	{
		if (!m_pIplZoomed)
			return;

		m_pZoomPt2 = new CPoint();	
		m_pZoomPt2->x = point.x - m_AligmentROI.x;
		m_pZoomPt2->y = point.y - m_AligmentROI.y;

		DoZoom();
	}

	CStatic::OnLButtonDown(nFlags, point);
}

void CPreviewWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (!m_bEnableZoom)
		return;

	m_DissolveCounter = 0;

	ResetZoom();

	CStatic::OnRButtonDown(nFlags, point);
}

void CPreviewWnd::ResetZoom()
{
	if (m_pZoomPt1 && !m_pZoomPt2)
	{
		if (m_pZoomPt1)
			delete m_pZoomPt1;
		m_pZoomPt1 = NULL;

		DrawToHDC();
		return;
	}

	if (m_pZoomPt1)
		delete m_pZoomPt1;
	m_pZoomPt1 = NULL;

	if (m_pZoomPt2)
		delete m_pZoomPt2;
	m_pZoomPt2 = NULL;

	if (!m_pIplOrig)
	{
		FitImageToClient();
		return;
	}

	m_AbsoluteTL.x = 0;
	m_AbsoluteTL.y = 0;

	int minWidth = 0;
	int maxWidth = m_pIplOrig->width-1;

	int minHeight = 0;
	int maxHeight = m_pIplOrig->height-1;
	
	m_CurrentDispArea.left = minWidth;
	m_CurrentDispArea.right = maxWidth;
	m_CurrentDispArea.top = minHeight;
	m_CurrentDispArea.bottom = maxHeight;

	if (m_pIplZoomed)
		cvReleaseImage(&m_pIplZoomed);
	m_pIplZoomed = cvCloneImage(m_pIplOrig);

	FitImageToClient(m_pIplOrig);
}

void CPreviewWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CStatic::OnLButtonDblClk(nFlags, point);
}

void CPreviewWnd::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CStatic::OnRButtonDblClk(nFlags, point);
}

void CPreviewWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bEnableZoom)
		return;

	m_PrevMousePt = m_CurMousePt;

	m_CurMousePt.x = _min(_max(point.x-1,0),m_FrameRect.Width()-2);
	m_CurMousePt.y = _min(_max(point.y-1,0),m_FrameRect.Height()-2);

	if (m_pZoomPt1)
	{
		CDC* pTempDC = GetDC();
		HDC hDC = pTempDC->m_hDC;

		HPEN hPen = ::CreatePen(PS_DASH, 2, RGB(0,255,0));
		HGDIOBJ hOldPen = ::SelectObject(hDC, (HGDIOBJ)hPen);

		::SetROP2(hDC, R2_XORPEN);

		int l = (int)(_max(m_pZoomPt1->x+m_AligmentROI.x, m_CurMousePt.x));
		int r = (int)(_min(m_pZoomPt1->x+m_AligmentROI.x, m_CurMousePt.x));
		int t = (int)(_max(m_pZoomPt1->y+m_AligmentROI.y, m_CurMousePt.y));
		int b = (int)(_min(m_pZoomPt1->y+m_AligmentROI.y, m_CurMousePt.y));

		::MoveToEx(hDC, l, t, NULL);
		::LineTo(hDC, r, t);
		::LineTo(hDC, r, b);
		::LineTo(hDC, l, b);
		::LineTo(hDC, l, t);

		l = (int)(_max(m_pZoomPt1->x+m_AligmentROI.x, m_PrevMousePt.x));
		r = (int)(_min(m_pZoomPt1->x+m_AligmentROI.x, m_PrevMousePt.x));
		t = (int)(_max(m_pZoomPt1->y+m_AligmentROI.y, m_PrevMousePt.y));
		b = (int)(_min(m_pZoomPt1->y+m_AligmentROI.y, m_PrevMousePt.y));

		::MoveToEx(hDC, l, t, NULL);
		::LineTo(hDC, r, t);
		::LineTo(hDC, r, b);
		::LineTo(hDC, l, b);
		::LineTo(hDC, l, t);

		::SetROP2(hDC, R2_COPYPEN);

		::SelectObject(hDC, hOldPen);
		::DeleteObject((HGDIOBJ)hPen);

		if (pTempDC)
			ReleaseDC(pTempDC);
		pTempDC = NULL;
	}
	
	CStatic::OnMouseMove(nFlags, point);
}

BOOL CPreviewWnd::UpdateView(IplImage* pIplUpd)
{
	if (!pIplUpd || pIplUpd->nChannels != 3)
		return FALSE;

	if (!m_pIplOrig)
		return FALSE;

	if (pIplUpd->width != m_pIplOrig->width)
		return FALSE;

	if (pIplUpd->height != m_pIplOrig->height)
		return FALSE;

	cvReleaseImage(&m_pIplOrig);
	m_pIplOrig = cvCloneImage(pIplUpd);

	if (m_pIplZoomed)
		cvReleaseImage(&m_pIplZoomed);
	
	CvRect ROI;
	ROI.x = m_AbsoluteTL.x ;
	ROI.y = m_AbsoluteTL.y ;
	ROI.width = m_CurrentDispArea.Width();
	ROI.height = m_CurrentDispArea.Height();;	

	cvSetImageROI(m_pIplOrig, ROI);
	m_pIplZoomed = cvCreateImage(cvSize(ROI.width,ROI.height),IPL_DEPTH_8U,3);
	cvCopyImage(m_pIplOrig, m_pIplZoomed);
	cvResetImageROI(m_pIplOrig);

	return FitImageToClient(m_pIplZoomed);
}

void CPreviewWnd::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
		case TIMER_DISSOLVE_TEXT:
		{
			if (m_DissolveCounter >= 0)
			{
				if (m_DissolveCounter == 250)
					Invalidate();
				m_DissolveCounter -= 10;
			}
			else
			{
				KillTimer(TIMER_DISSOLVE_TEXT);
				Invalidate();
			}
			break;
		}

	}

	CStatic::OnTimer(nIDEvent);
}

void CPreviewWnd::DrawToHDC(HDC hDC, const IplImage* pIplToDraw)
{
	if (m_bDrawingToHDC)
		return;

	if (!IsWindowVisible())
		return;

	m_bDrawingToHDC = TRUE;
	
	CDC* pTempDC = NULL;
	if (!hDC)
	{
		pTempDC = GetDC();
		hDC = pTempDC->GetSafeHdc();
	}
	if (!pIplToDraw)
		pIplToDraw = m_pIplToDraw;

	if (!hDC || !pIplToDraw)
	{
		m_bDrawingToHDC = FALSE;
		if (pTempDC)
			ReleaseDC(pTempDC);
		return;
	}

	BITMAPINFO bmpInfo;
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = pIplToDraw->width;
	bmpInfo.bmiHeader.biHeight = -pIplToDraw->height;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biSizeImage = 0;
	bmpInfo.bmiHeader.biBitCount = 24;

	RECT rect;
	GetClientRect(&rect);

	rect.left += 1;
	rect.right -= 1;
	rect.top += 1;
	rect.bottom -= 1;

	//::FillRect(hDC, &rect, (HBRUSH)m_Brush.m_hObject);

	CvRect destRect;
	if (pIplToDraw->width > pIplToDraw->height)
	{
		destRect.x = 1;
		destRect.width = rect.right;
		destRect.height = cvRound((double)(rect.right) * (double)pIplToDraw->height / (double)pIplToDraw->width);
		destRect.y = 1;
	}
	else
	{			
		destRect.y = 1;
		destRect.height = rect.bottom;
		destRect.width = cvRound((double)(m_FrameRect.bottom - 2) * (double)pIplToDraw->width / (double)pIplToDraw->height);
		destRect.x = cvRound((rect.right - destRect.width) / 2.0);
	}
	
	int prevBltMode = ::SetStretchBltMode(hDC, COLORONCOLOR);

	::StretchDIBits(hDC, 
					destRect.x, destRect.y, destRect.width, destRect.height, 
					0, 0, pIplToDraw->width, pIplToDraw->height, 
					pIplToDraw->imageData, &bmpInfo, 
					DIB_RGB_COLORS, SRCCOPY);

	::SetStretchBltMode(hDC, prevBltMode);

	if (m_DissolveCounter > 0)
	{
		//::SetTextColor(hDC, RGB(m_DissolveCounter,m_DissolveCounter,m_DissolveCounter));
		::SetTextColor(hDC, RGB(255,255,255));
		::SetBkColor(hDC, RGB(0,0,0));
		::SetBkMode(hDC, TRANSPARENT);
		
		CString zoomMsg;
		zoomMsg.Format("Zoom %dx", m_ZoomPer);
		
		::TextOut(hDC, 20,20,zoomMsg,zoomMsg.GetLength());	
	}

	if (pTempDC)
		ReleaseDC(pTempDC);

	m_bDrawingToHDC = FALSE;
}

BOOL CPreviewWnd::SaveImage(CString path)
{
	if (!m_pIplToDraw || path.IsEmpty())
		return FALSE;

	cvSaveImage(path, m_pIplToDraw);
	return TRUE;
}

BOOL CPreviewWnd::SaveOrigImage(CString path)
{
	if (!m_pIplOrig || path.IsEmpty())
		return FALSE;

	cvSaveImage(path, m_pIplOrig);
	return TRUE;
}

BOOL CPreviewWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (!m_bEnableZoom)
		return FALSE;

	return TRUE;

	if (zDelta > 0)
	{
		int winSizeX = m_FrameRect.Width() / 4;
		int winSizeY = m_FrameRect.Height() / 4;

		// zoom in
		m_pZoomPt1 = new CPoint();	
		m_pZoomPt1->x = pt.x - m_AligmentROI.x;
		m_pZoomPt1->y = pt.y - m_AligmentROI.y;

		m_pZoomPt1->x = _max(0, m_pZoomPt1->x-winSizeX);
		m_pZoomPt1->y = _max(0, m_pZoomPt1->y-winSizeY);
		
		m_pZoomPt2 = new CPoint();	
		m_pZoomPt2->x = pt.x - m_AligmentROI.x;
		m_pZoomPt2->y = pt.y - m_AligmentROI.y;

		m_pZoomPt2->x = _min(m_FrameRect.Width()-1, m_pZoomPt2->x+winSizeX);
		m_pZoomPt2->y = _min(m_FrameRect.Height()-1, m_pZoomPt2->y+winSizeY);		
	}
	else
	{
		/*
		int winSizeX = m_FrameRect.Width() * 4;
		int winSizeY = m_FrameRect.Height() * 4;

		// zoom out
		m_pZoomPt1 = new CPoint();	
		m_pZoomPt1->x = pt.x - m_AligmentROI.x;
		m_pZoomPt1->y = pt.y - m_AligmentROI.y;

		m_pZoomPt1->x = _max(0, m_pZoomPt1->x-winSizeX);
		m_pZoomPt1->y = _max(0, m_pZoomPt1->y-winSizeY);
		
		m_pZoomPt2 = new CPoint();	
		m_pZoomPt2->x = pt.x - m_AligmentROI.x;
		m_pZoomPt2->y = pt.y - m_AligmentROI.y;

		m_pZoomPt2->x = _min(m_pIplOrig->width-1, m_pZoomPt2->x+winSizeX);
		m_pZoomPt2->y = _min(m_pIplOrig->height-1, m_pZoomPt2->y+winSizeY);		
		*/
		
	}
	DoZoom();

	return CStatic::OnMouseWheel(nFlags, zDelta, pt);
}

void CPreviewWnd::DoZoom()
{
	if (!m_pZoomPt1 || !m_pZoomPt2)
		return;

	CPoint TL, BR;
	TL.x = min(m_pZoomPt1->x, m_pZoomPt2->x);
	TL.y = min(m_pZoomPt1->y, m_pZoomPt2->y);
	BR.x = max(m_pZoomPt1->x, m_pZoomPt2->x);
	BR.y = max(m_pZoomPt1->y, m_pZoomPt2->y);

	TL.x /= m_FrameScale;
	TL.y /= m_FrameScale;
	BR.x /= m_FrameScale;
	BR.y /= m_FrameScale;

	m_AbsoluteTL.x += TL.x;
	m_AbsoluteTL.y += TL.y;
	
	if (m_pIplToDraw)
		cvReleaseImage(&m_pIplToDraw);
	m_pIplToDraw = NULL;

	int minWidth = 0;
	int maxWidth = m_pIplZoomed->width-1;
	int minHeight = 0;
	int maxHeight = m_pIplZoomed->height-1;
	
	int leftOffset = 0;
	int rightOffset = 0;
	int topOffset = 0;
	int bottomOffset = 0;

	m_CurrentDispArea.left = (int)(_max(TL.x, minWidth))+rightOffset;
	m_CurrentDispArea.right = (int)(_min(BR.x, maxWidth))+leftOffset;
	m_CurrentDispArea.top = (int)(_max(TL.y, minHeight))+bottomOffset;
	m_CurrentDispArea.bottom = (int)(_min(BR.y, maxHeight))+topOffset;
	
	if (m_CurrentDispArea.left >= m_CurrentDispArea.right || m_CurrentDispArea.top >= m_CurrentDispArea.bottom)
	{
		ResetZoom();		
		return;
	}

	m_ZoomPer = ceil(max(m_pIplOrig->width,m_pIplOrig->height)/(double)max(m_CurrentDispArea.Width(),m_CurrentDispArea.Height()) );

	CvRect ROI;
	ROI.width = m_CurrentDispArea.Width();
	ROI.height = m_CurrentDispArea.Height();;
	ROI.x = m_CurrentDispArea.left;
	ROI.y = m_CurrentDispArea.top;

	cvSetImageROI(m_pIplZoomed, ROI);
	IplImage* pIplNextZoom = cvCreateImage(cvSize(ROI.width,ROI.height),IPL_DEPTH_8U,3);
	cvCopyImage(m_pIplZoomed, pIplNextZoom);
	cvResetImageROI(m_pIplZoomed);

	cvReleaseImage(&m_pIplZoomed);
	m_pIplZoomed = pIplNextZoom;

	FitImageToClient(m_pIplZoomed);

	m_DissolveCounter = 250;
	SetTimer(TIMER_DISSOLVE_TEXT,20,NULL);

	delete m_pZoomPt1;
	m_pZoomPt1 = NULL;

	delete m_pZoomPt2;
	m_pZoomPt2 = NULL;
}

CvPoint CPreviewWnd::ScalePtToPicture(CvPoint pt)
{
	pt.x -= m_AligmentROI.x;
	pt.y -= m_AligmentROI.y;

	pt.x /= m_FrameScale;
	pt.y /= m_FrameScale;

	pt.x += m_AbsoluteTL.x;
	pt.y += m_AbsoluteTL.y;

	return pt;
}

CvPoint CPreviewWnd::ScalePtToClient(CvPoint pt)
{
	pt.x -= m_AbsoluteTL.x;
	pt.y -= m_AbsoluteTL.y;

	pt.x *= m_FrameScale;
	pt.y *= m_FrameScale;

	pt.x += m_AligmentROI.x;
	pt.y += m_AligmentROI.y;

	return pt;
}

CvPoint2D32f CPreviewWnd::ScalePtToPicture(CvPoint2D32f pt)
{
	CvPoint tmpPt;
	tmpPt.x = pt.x;
	tmpPt.y = pt.y;
	tmpPt = ScalePtToPicture(tmpPt);
	pt.x = tmpPt.x;
	pt.y = tmpPt.y;
	return pt;
}

CvPoint2D32f CPreviewWnd::ScalePtToClient(CvPoint2D32f pt)
{
	CvPoint tmpPt;
	tmpPt.x = pt.x;
	tmpPt.y = pt.y;
	tmpPt = ScalePtToClient(tmpPt);
	pt.x = tmpPt.x;
	pt.y = tmpPt.y;
	return pt;
}

