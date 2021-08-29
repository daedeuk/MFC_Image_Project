
// NewProject01View.cpp : CNewProject01View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "NewProject01.h"
#endif

#include "NewProject01Doc.h"
#include "NewProject01View.h"
#include <atlimage.h>

//#include "opencv2/opencv.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define SHIFTPressed() ( 0x8000 ==(GetKeyState(VK_SHIFT) & 0x8000   ))


// CNewProject01View

IMPLEMENT_DYNCREATE(CNewProject01View, CFormView)

BEGIN_MESSAGE_MAP(CNewProject01View, CFormView)
	ON_COMMAND(ID_FILE_OPEN, &CNewProject01View::OnImageLoadImage)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CNewProject01View::OnUpdateImageLoadimage)
	ON_COMMAND(ID_FILE_SAVE, &CNewProject01View::OnImageSaveImage)
	ON_COMMAND(ID_PROCESSING_ERROSION, &CNewProject01View::OnImageErrosion)
	ON_COMMAND(ID_PROCESSING_DILATION, &CNewProject01View::OnImageDilation)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN() 
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CNewProject01View 생성/소멸

CNewProject01View::CNewProject01View()
: CFormView(CNewProject01View::IDD)
{
	m_nMagnify = 1;
	// TODO: 여기에 생성 코드를 추가합니다.}
}

CNewProject01View::~CNewProject01View()
{
}

void CNewProject01View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CNewProject01View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CNewProject01View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

}


// CNewProject01View 진단

#ifdef _DEBUG
void CNewProject01View::AssertValid() const
{
	CFormView::AssertValid();
}

void CNewProject01View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CNewProject01Doc* CNewProject01View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNewProject01Doc)));
	return (CNewProject01Doc*)m_pDocument;
}
#endif //_DEBUG



// CNewProject01View 메시지 처리기
void CNewProject01View::OnImageLoadImage()
{
	CString szFilter = L"Image files (*.bmp, *.jpg) | *.bmp; *.jpg; | All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (dlg.DoModal() == IDOK)
	{
		CString strPathname = dlg.GetPathName();
		pDoc = GetDocument();
		//이미지가 이미 열린 상태에서 새로 열 때, 초기화
		if (!pDoc->m_Image.IsNull())
		{
			pre->movepoint.x = -1;
			pre->movepoint.y = -1;
			inH = pDoc->m_Image.GetHeight();
			inW = pDoc->m_Image.GetWidth();
			free2DImage(inImageR, inH);
			free2DImage(inImageG, inH);
			free2DImage(inImageB, inH);
			free2DImage(outImageR, outH);
			free2DImage(outImageG, outH);
			free2DImage(outImageB, outH);
			m_nMagnify = 1;
			zoom = 1;
			wid, hei, i_wid, i_hei = 0;
			m_point.x = pDoc->m_Image.GetWidth() / 2;
			m_point.y = pDoc->m_Image.GetHeight() / 2;
			pDoc->m_Image.Destroy();
			pre->p_image.Destroy();
			pre->DestroyWindow();
			pre = NULL;

		}
		pre = new Preview;
		pre->Create(IDD_DIALOG1, this);
		pre->movepoint.x = -1;
		pre->movepoint.y = -1;
		pre->p_image.Load(strPathname);
		pre->ShowWindow(SW_SHOW);
		pDoc->m_Image.Load(strPathname);
		inH = pDoc->m_Image.GetHeight();
		inW = pDoc->m_Image.GetWidth();
		//입력 메모리 할당.
		inImageR = malloc2D(inH, inW);
		inImageG = malloc2D(inH, inW);
		inImageB = malloc2D(inH, inW);
		outH = inH;  outW = inW;
		// 출력 메모리 할당.
		outImageR = malloc2D(outH, outW);
		outImageG = malloc2D(outH, outW);
		outImageB = malloc2D(outH, outW);

		Invalidate(true);
	}
}
void CNewProject01View::OnUpdateImageLoadimage(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
}

void CNewProject01View::OnImageSaveImage()
{
	CString szFilter = L"BMP Image (*.bmp) | *.bmp; | All Files(*.*)|*.*||";
	CFileDialog dlg(FALSE, L"bmp", L"*.bmp", OFN_HIDEREADONLY, szFilter);
	if (dlg.DoModal() == IDOK){
		CString SstrPathname = dlg.GetPathName();
		pDoc->m_Image.Save(SstrPathname);
	}
}


void CNewProject01View::OnDraw(CDC* pDC)
{
	CWnd cwnd;
	CNewProject01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	if (!pDoc->m_Image.IsNull())
	{
		CClientDC dc(this);
		pDC = &dc;
		//현재 뷰의 크기를 받아주는 변수 new_rect
		CRect new_rect;
		GetClientRect(&new_rect);

		i_wid = pDoc->m_Image.GetWidth();
		i_hei = pDoc->m_Image.GetHeight();
		//뷰에서 원하는 크기만 받기 위해서 작게 곱해주었습니다.
		wid = 0.4*new_rect.Width();
		hei = 0.4*new_rect.Width();
		
		//이미지의 비율에 따라가도록 설정
		if (i_wid > i_hei)
		{
			hei = wid*(i_hei / i_wid);
		}
		else if (i_hei > i_wid)
		{
			wid = hei*(i_wid / i_hei);
		}
		CRect this_rect(0, 0, wid, hei);
		
		SetStretchBltMode(pDC->m_hDC, HALFTONE);
		if (m_nMagnify == 1)
		{
			m_point.x = i_wid / 2;
			m_point.y = i_hei / 2;
			zoom = 1.2 - 2 * ((double)m_nMagnify / 10);
			double x1 = m_point.x - (i_wid / 2)*zoom+1;
			double y1 = m_point.y - (i_hei / 2)*zoom+1;
			double x2 = m_point.x + (i_wid / 2)*zoom-1;
			double y2 = m_point.y + (i_hei / 2)*zoom-1;
			CRect xxyy(x1, y1, x2, y2);
			pre->R_Rect = xxyy;
			zoom = 1;
			pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2-x1, y2-y1, SRCCOPY);
		}
		else if (m_nMagnify > 1)
		{
			//얼마나 확대할건지 m_nMagnify에 따라서 zoom을 변화시켜주었다.
			for (int i = 0; i < (m_nMagnify-1); i++)
			{
				zoom = zoom * 1 / 2;
			}

			//마우스로 누른 좌표를 기준으로 볼 영역(rect)의 TopLeft(x1,y1) 와 BottomRight(x2,y2)을 설정.
			double x1 = m_point.x - (i_wid / 2)*zoom;
			if (x1 < 0)
			{
				x1 = 1;
			}
			double y1 = m_point.y - (i_hei / 2)*zoom;
			if (y1 < 0)
			{
				y1 = 1;
			}
			double x2 = m_point.x + (i_wid / 2)*zoom;
			if (x2>i_wid)
			{
				x2 = i_wid-1;
			}
			double y2 = m_point.y + (i_hei / 2)*zoom;
			if (y2 > i_hei)
			{
				y2 = i_hei-1;
			}
			//프리뷰에 전달
			CRect xxyy(x1, y1, x2, y2);
			pre->R_Rect = xxyy;
			zoom = 1;
			pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2-x1, y2-y1, SRCCOPY);
		}
		/* 원본보다 더 축소할 때
		else if (m_nMagnify<1)
		{
			
			zoom = 1 - 5*( ((double)m_nMagnify-1) / 10); //1.2 1.4 1.6 1.8 2.0 2.2
			//1.5 2.0 2.5 3.0 3.5
			double x1 = m_point.x - (i_wid / 2)*zoom;
			double y1 = m_point.y - (i_hei / 2)*zoom;
			double x2 = m_point.x + (i_wid / 2)*zoom;
			double y2 = m_point.y + (i_hei / 2)*zoom;

			CRect xxyy(x1, y1, x2, y2);
			pre->R_Rect = xxyy;
			zoom = 1;
			pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2-x1, y2-y1, SRCCOPY);
		}
		*/
		ReleaseDC(&dc);
		ReleaseDC(pDC);
	}
}

	void CNewProject01View::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CNewProject01View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	//뷰에서 이미지가 있는 영역을 눌렀을 때만 처리
	if (point.x < wid&&point.y < hei)
	{
		if (TRUE == SHIFTPressed())
		{
			p_point.x = point.x;
			p_point.y = point.y;


			if (i_wid != 0 && wid != 0)
			{
				//현재 보고 있는 영역의 TopLeft 좌표에서 누른 부분만큼 더하여 이동.
				m_point.x = p_point.x / wid * (pre->R_Rect.Width()) + (pre->R_Rect.TopLeft().x);
				m_point.y = p_point.y / hei*  (pre->R_Rect.Height()) + (pre->R_Rect.TopLeft().y);
				Invalidate(false);
			}
		}
		else
		{
			if (m_nMagnify < 7)
			{
				p_point.x = point.x;
				p_point.y = point.y;
				if (i_wid != 0 && wid != 0)
				{
					m_point.x = p_point.x / wid * (pre->R_Rect.Width()) + (pre->R_Rect.TopLeft().x);
					m_point.y = p_point.y / hei*  (pre->R_Rect.Height()) + (pre->R_Rect.TopLeft().y);
				}
				//배율이 1배일때 이미지의 중앙을 찍도록 초기화
				if (m_nMagnify == 1)
				{
					p_point.x = point.x;
					p_point.y = point.y;
					if (i_wid != 0 && wid != 0)
					{
						m_point.x = p_point.x / wid*(i_wid)*zoom;
						m_point.y = p_point.y / hei*(i_hei)*zoom;
					}
				}
				zoom = 1;
				++m_nMagnify;
			}
		}
	}
	Invalidate(false);
	CFormView::OnLButtonDown(nFlags, point);
}

void CNewProject01View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (point.x < wid&&point.y < hei)
	{
		if (TRUE==SHIFTPressed())
		{
			p_point.x = point.x;
			p_point.y = point.y;
			if (i_wid != 0 && wid != 0)
			{
				if (i_wid != 0 && wid != 0)
				{
					m_point.x =p_point.x / wid * (pre->R_Rect.Width()) + (pre->R_Rect.TopLeft().x);
					m_point.y =p_point.y / hei*  (pre->R_Rect.Height()) + (pre->R_Rect.TopLeft().y);
					Invalidate(false);
				}
			}
		}
		else
		{
			if (m_nMagnify > 1)
			{
				if (m_nMagnify == 2)
				{
					p_point.x = point.x;
					p_point.y = point.y;
					if (i_wid != 0 && wid != 0)
					{
						m_point.x = p_point.x / wid*(i_wid)*zoom;
						m_point.y = p_point.y / hei*(i_hei)*zoom;
					}
				}
				zoom = 1;
				--m_nMagnify;
			}
		}
	}
	Invalidate(false);
	CFormView::OnRButtonDown(nFlags, point);
}

void CNewProject01View::OnImageErrosion()
{
	// TODO: 여기에 구현 코드 추가.r
	/*
	if (inImageR == NULL)
	return;
	*/
	// 기존에 처리한 적이 있으면 일단 메모리 해제
	inH = i_hei;
	inW = i_wid;
	free2DImage(inImageR, inH);
	free2DImage(inImageG, inH);
	free2DImage(inImageB, inH);
	// 입력 메모리 할당.
	inImageR = malloc2D(inH, inW);
	inImageG = malloc2D(inH, inW);
	inImageB = malloc2D(inH, inW);
	int imgBPP = pDoc->m_Image.GetBPP();
	for (int i = 0; i < inH; i++)
	{
		for (int k = 0; k < inW; k++) {
			COLORREF pixel; // 한 점(R,G,B)
			//pixel은 rgb만 사용하기 때문에 3byte.
			memcpy(&pixel, pDoc->m_Image.GetPixelAddress(k, i), imgBPP/8);
			inImageR[i][k] = (unsigned char)GetRValue(pixel);
			inImageG[i][k] = (unsigned char)GetGValue(pixel);
			inImageB[i][k] = (unsigned char)GetBValue(pixel);
		}
	}
	free2DImage(outImageR, outH);
	free2DImage(outImageG, outH);
	free2DImage(outImageB, outH);

	outH = inH;  outW = inW;
	// 출력 메모리 할당.
	outImageR = malloc2D(outH, outW);
	outImageG = malloc2D(outH, outW);
	outImageB = malloc2D(outH, outW);
	unsigned char minR = 255, minG = 255, minB = 255;
	for (int i = 1; i < inH - 1; i++) {
		for (int j = 1; j < inW - 1; j++) {
			minR = 255, minG = 255, minB = 255;
			for (int k = 0; k < 3; k++)
			{
				for (int m = 0; m < 3; m++)
				{
					if (minR > inImageR[i - 1 + k][j - 1 + m]) {
						minR = inImageR[i - 1 + k][j - 1 + m];
					}
					if (minG > inImageG[i - 1 + k][j - 1 + m]) {
						minG = inImageG[i - 1 + k][j - 1 + m];
					}
					if (minB > inImageB[i - 1 + k][j - 1 + m]) {
						minB = inImageB[i - 1 + k][j - 1 + m];
					}
				}
			}
			outImageR[i][j] = minR;
			outImageG[i][j] = minG;
			outImageB[i][j] = minB;
		}
	}
	
		unsigned char R, G, B;
		for (int i = 0; i < outH; i++) {
			for (int k = 0; k < outW; k++) {
				COLORREF pix;
				R = outImageR[i][k];
				G = outImageG[i][k];
				B = outImageB[i][k];
				pix = RGB(R, G, B);
				memcpy(pDoc->m_Image.GetPixelAddress(k, i), &pix, imgBPP/8);
			}
		}
		pre->p_image = pDoc->m_Image;
		Invalidate(false);
}

void CNewProject01View::OnImageDilation()
{
	/*
	// TODO: 여기에 구현 코드 추가.
		return;
	*/
	inH = i_hei;
	inW = i_wid;
	free2DImage(inImageR, inH);
	free2DImage(inImageG, inH);
	free2DImage(inImageB, inH);
	// 중요! 출력 영상 크기 --> 알고리즘에 따름
	// 출력 메모리 할당.
	inImageR = malloc2D(inH, inW);
	inImageG = malloc2D(inH, inW);
	inImageB = malloc2D(inH, inW);
	int imgBPP = pDoc->m_Image.GetBPP();
	for (int i = 0; i < inH; i++)
	{
		for (int k = 0; k < inW; k++) {

			COLORREF pixel; // 한 점(R,G,B)
			memcpy(&pixel, pDoc->m_Image.GetPixelAddress(k, i), imgBPP/8);
			inImageR[i][k] = (unsigned char)GetRValue(pixel);
			inImageG[i][k] = (unsigned char)GetGValue(pixel);
			inImageB[i][k] = (unsigned char)GetBValue(pixel);
		}
	}
	free2DImage(outImageR, outH);
	free2DImage(outImageG, outH);
	free2DImage(outImageB, outH);
	// 중요! 출력 영상 크기 --> 알고리즘에 따름
	outH = inH;  outW = inW;
	// 출력 메모리 할당.
	outImageR = malloc2D(outH, outW);
	outImageG = malloc2D(outH, outW);
	outImageB = malloc2D(outH, outW);
	unsigned char maxR = 0, maxG = 0, maxB = 0;
	for (int i = 1; i < inH - 1; i++) {
		for (int j = 1; j < inW - 1; j++) {
			maxR = 0, maxG = 0, maxB = 0;
			for (int k = 0; k < 3; k++)
			{
				for (int m = 0; m < 3; m++)
				{
					if (maxR < inImageR[i - 1 + k][j - 1 + m]) {
						maxR = inImageR[i - 1 + k][j - 1 + m];
					}
					if (maxG < inImageG[i - 1 + k][j - 1 + m]) {
						maxG = inImageG[i - 1 + k][j - 1 + m];
					}
					if (maxB < inImageB[i - 1 + k][j - 1 + m]) {
						maxB = inImageB[i - 1 + k][j - 1 + m];
					}
				}
			}
			outImageR[i][j] = maxR;
			outImageG[i][j] = maxG;
			outImageB[i][j] = maxB;
		}
	}

	unsigned char R, G, B;
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			R = outImageR[i][k];
			G = outImageG[i][k];
			B = outImageB[i][k];
			COLORREF p;
			p=RGB(R, G, B);
			memcpy(pDoc->m_Image.GetPixelAddress(k, i), &p, imgBPP/8);
		}
	}
	pre->p_image = pDoc->m_Image;
	Invalidate(false);
}

void CNewProject01View::pointmove(CPoint movepoint)
{
	m_point.x = movepoint.x;
	m_point.y = movepoint.y;
	return;
}

unsigned char** CNewProject01View::malloc2D(int h, int w) {
	unsigned char** p;
	p = (unsigned char**)malloc(h * sizeof(unsigned char*));
	for (int i = 0; i < h; i++)
		p[i] = (unsigned char*)malloc(w * sizeof(unsigned char));
	return p;
}


void CNewProject01View::free2DImage(unsigned char** image, int h) {
	if (image == NULL)
		return;
	for (int i = 0; i < h; i++)
		free(image[i]);
	free(image);
	image = NULL;
}