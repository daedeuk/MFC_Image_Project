
// NewProject01View.cpp : CNewProject01View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CNewProject01View ����/�Ҹ�

CNewProject01View::CNewProject01View()
: CFormView(CNewProject01View::IDD)
{
	m_nMagnify = 1;
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.}
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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CNewProject01View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

}


// CNewProject01View ����

#ifdef _DEBUG
void CNewProject01View::AssertValid() const
{
	CFormView::AssertValid();
}

void CNewProject01View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CNewProject01Doc* CNewProject01View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNewProject01Doc)));
	return (CNewProject01Doc*)m_pDocument;
}
#endif //_DEBUG



// CNewProject01View �޽��� ó����
void CNewProject01View::OnImageLoadImage()
{
	CString szFilter = L"Image files (*.bmp, *.jpg) | *.bmp; *.jpg; | All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (dlg.DoModal() == IDOK)
	{
		CString strPathname = dlg.GetPathName();
		pDoc = GetDocument();
		//�̹����� �̹� ���� ���¿��� ���� �� ��, �ʱ�ȭ
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
		//�Է� �޸� �Ҵ�.
		inImageR = malloc2D(inH, inW);
		inImageG = malloc2D(inH, inW);
		inImageB = malloc2D(inH, inW);
		outH = inH;  outW = inW;
		// ��� �޸� �Ҵ�.
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
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	if (!pDoc->m_Image.IsNull())
	{
		CClientDC dc(this);
		pDC = &dc;
		//���� ���� ũ�⸦ �޾��ִ� ���� new_rect
		CRect new_rect;
		GetClientRect(&new_rect);

		i_wid = pDoc->m_Image.GetWidth();
		i_hei = pDoc->m_Image.GetHeight();
		//�信�� ���ϴ� ũ�⸸ �ޱ� ���ؼ� �۰� �����־����ϴ�.
		wid = 0.4*new_rect.Width();
		hei = 0.4*new_rect.Width();
		
		//�̹����� ������ ���󰡵��� ����
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
			//�󸶳� Ȯ���Ұ��� m_nMagnify�� ���� zoom�� ��ȭ�����־���.
			for (int i = 0; i < (m_nMagnify-1); i++)
			{
				zoom = zoom * 1 / 2;
			}

			//���콺�� ���� ��ǥ�� �������� �� ����(rect)�� TopLeft(x1,y1) �� BottomRight(x2,y2)�� ����.
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
			//�����信 ����
			CRect xxyy(x1, y1, x2, y2);
			pre->R_Rect = xxyy;
			zoom = 1;
			pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2-x1, y2-y1, SRCCOPY);
		}
		/* �������� �� ����� ��
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CNewProject01View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	//�信�� �̹����� �ִ� ������ ������ ���� ó��
	if (point.x < wid&&point.y < hei)
	{
		if (TRUE == SHIFTPressed())
		{
			p_point.x = point.x;
			p_point.y = point.y;


			if (i_wid != 0 && wid != 0)
			{
				//���� ���� �ִ� ������ TopLeft ��ǥ���� ���� �κи�ŭ ���Ͽ� �̵�.
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
				//������ 1���϶� �̹����� �߾��� �ﵵ�� �ʱ�ȭ
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ ���� �ڵ� �߰�.r
	/*
	if (inImageR == NULL)
	return;
	*/
	// ������ ó���� ���� ������ �ϴ� �޸� ����
	inH = i_hei;
	inW = i_wid;
	free2DImage(inImageR, inH);
	free2DImage(inImageG, inH);
	free2DImage(inImageB, inH);
	// �Է� �޸� �Ҵ�.
	inImageR = malloc2D(inH, inW);
	inImageG = malloc2D(inH, inW);
	inImageB = malloc2D(inH, inW);
	int imgBPP = pDoc->m_Image.GetBPP();
	for (int i = 0; i < inH; i++)
	{
		for (int k = 0; k < inW; k++) {
			COLORREF pixel; // �� ��(R,G,B)
			//pixel�� rgb�� ����ϱ� ������ 3byte.
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
	// ��� �޸� �Ҵ�.
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
	// TODO: ���⿡ ���� �ڵ� �߰�.
		return;
	*/
	inH = i_hei;
	inW = i_wid;
	free2DImage(inImageR, inH);
	free2DImage(inImageG, inH);
	free2DImage(inImageB, inH);
	// �߿�! ��� ���� ũ�� --> �˰��� ����
	// ��� �޸� �Ҵ�.
	inImageR = malloc2D(inH, inW);
	inImageG = malloc2D(inH, inW);
	inImageB = malloc2D(inH, inW);
	int imgBPP = pDoc->m_Image.GetBPP();
	for (int i = 0; i < inH; i++)
	{
		for (int k = 0; k < inW; k++) {

			COLORREF pixel; // �� ��(R,G,B)
			memcpy(&pixel, pDoc->m_Image.GetPixelAddress(k, i), imgBPP/8);
			inImageR[i][k] = (unsigned char)GetRValue(pixel);
			inImageG[i][k] = (unsigned char)GetGValue(pixel);
			inImageB[i][k] = (unsigned char)GetBValue(pixel);
		}
	}
	free2DImage(outImageR, outH);
	free2DImage(outImageG, outH);
	free2DImage(outImageB, outH);
	// �߿�! ��� ���� ũ�� --> �˰��� ����
	outH = inH;  outW = inW;
	// ��� �޸� �Ҵ�.
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