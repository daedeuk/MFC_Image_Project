
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

#include "Preview.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNewProject01View

IMPLEMENT_DYNCREATE(CNewProject01View, CFormView)

BEGIN_MESSAGE_MAP(CNewProject01View, CFormView)
	ON_COMMAND(ID_FILE_OPEN, &CNewProject01View::OnImageLoadImage)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CNewProject01View::OnUpdateImageLoadimage)
	//ON_COMMAND(ID_FILE_SAVE, &CnewProject01View::OnImageSaveImage)
	ON_WM_DESTROY()
	ON_STN_CLICKED(IDC_STATIC_DISP, &CNewProject01View::OnStnClickedStaticDisp)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CNewProject01View 생성/소멸

CNewProject01View::CNewProject01View()
: CFormView(CNewProject01View::IDD)
{
	m_nMagnify = 1;
	// TODO: 여기에 생성 코드를 추가합니다.

	BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO)+256 * sizeof(RGBQUAD));
	for (int i = 0; i < 256; i++)
	{
		BmInfo->bmiColors[i].rgbRed = BmInfo->bmiColors[i].rgbGreen = BmInfo->bmiColors[i].rgbReserved = 0;
	}
}

CNewProject01View::~CNewProject01View()
{
	if(BmInfo) delete BmInfo;
}

void CNewProject01View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_DISP, m_stDisp);
	DDX_Control(pDX, IDC_MY_PICTURE, M_stDisp);
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
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

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
	//CWnd *p_wnd = GetDlgItem(ID_FILE_OPEN);
	//CDC *cdc = GetDC();
	//CClientDC dc(this);
	
	/*
	HWND hWnd = m_stDisp.GetSafeHwnd();
	HDC hdc = ::GetDC(hWnd);
	*/

	/*
	HBITMAP h_bitmap = (HBITMAP)GetCurrentObject(hdc, OBJ_BITMAP);
	BITMAP bmp_info;
	GetObject(h_bitmap, sizeof(BITMAP), &bmp_info);
	*/
	///c_image.Create(512, 512, 32);
	//unsigned char *p_src_image = new unsigned char[512 * 512];
	//unsigned char *p_dest_image = new unsigned char[512 * 512 * 4];

	// p_dest_image, p_src_image는 동적 할당된 메모리의 시작 주소를 기억하고 있어야지 
	// 작업이 끝난 후에 동적 할당된 메모리의 주소를 해제할 수 있다. 
	//unsigned char *p_dest_pos = p_dest_image;
	//unsigned char *p_src_pos = p_src_image;
	CString szFilter = L"Image files (*.bmp, *.jpg) | *.bmp; *.jpg; | All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	//pDoc = GetDocument();
	if (dlg.DoModal() == IDOK)
	{
		CString strPathname = dlg.GetPathName();
		pDoc = GetDocument();
		CFile f;
		//HRESULT hr = c_image.Load(strPathname);
		if (!pDoc->m_Image.IsNull())
		{
			m_nMagnify = 1;
			zoom = 1;
			wid, hei, i_wid, i_hei = 0;
			m_point.x = pDoc->m_Image.GetWidth() / 2;
			m_point.y = pDoc->m_Image.GetHeight() / 2;
			pDoc->m_Image.Destroy();
			
			//m_PreviewDlg->DestroyWindow();
			//m_PreviewDlg = NULL;

			pre->p_image.Destroy();
			pre->DestroyWindow();
			pre = NULL;
		}
		pDoc->m_Image.Load(strPathname);
		//m_PreviewDlg = new CPreviewDlg();
		//m_PreviewDlg->Create(IDD_DIALOG1, this);
		//m_PreviewDlg->ShowWindow(SW_SHOW);
		
		pre = new Preview;
		pre->Create(IDD_DIALOG1, this);
		pre->p_image.Load(strPathname);
		pre->ShowWindow(SW_SHOW);
		
		
		//c_image.Load(strPathname);
		//::ReleaseDC(hWnd, hdc);
		Invalidate(true);
	}
}
void CNewProject01View::OnUpdateImageLoadimage(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
}
//CString format
// 0 : image/bmp	// 1 : image/jpeg	// 2 : image/gif	// 3 : image/tiff	// 4 : image/png

void CNewProject01View::OnImageSaveImage()
{

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
		CRect new_rect;
		GetClientRect(&new_rect);
		//dc.GetClipBox(&new_rect);

			i_wid = pDoc->m_Image.GetWidth();
			i_hei = pDoc->m_Image.GetHeight();
			wid = 0.7*new_rect.Width();
			//hei = new_rect.Height();
			//wid = wid*i_wid / (i_wid + i_hei);
			//hei = wid*i_hei / (i_wid + i_hei);
			hei = wid*i_hei/i_wid;

		CRect this_rect(0, 0, wid, hei);

		//확대 
		SetStretchBltMode(pDC->m_hDC, HALFTONE);
		if (m_nMagnify == 1)
		{
			m_point.x = pDoc->m_Image.GetWidth() / 2;
			m_point.y = pDoc->m_Image.GetHeight() / 2;
			zoom = 1.2 - 2 * ((double)m_nMagnify / 10);
			double x1 = m_point.x - (i_wid / 2)*zoom;
			double y1 = m_point.y - (i_hei / 2)*zoom;
			double x2 = m_point.x + (i_wid / 2)*zoom;
			double y2 = m_point.y + (i_hei / 2)*zoom;
			//m_image1.Draw(dc, 0, 0);
			pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2, y2, SRCCOPY);
			CRect xxyy(x1, y1, x2, y2);
			pre->R_Rect = xxyy;
			//pre->ShowWindow(SW_SHOW);
			//pre->OnPaint();
			//pDoc->m_Image.StretchBlt(cdc->m_hDC, 0, 0, pre->p_wid, pre->p_hei, 0,0,i_wid,i_hei,SRCCOPY);
		}
		else if (m_nMagnify > 1)
		{
			/*
			if (m_nMagnify<11)
			{
				zoom = 1.1 - 2*((double)m_nMagnify / 10); //1.0 0.9 0.8 ~~ 0.1까지
			}
			
			else if (11<=m_nMagnify<19)
			{
				zoom = 0.19 - ((double)m_nMagnify / 100);                //0.08 0.07 0.06 0.05 0.04 0.03 0.02 0.01
			}
			else if (20 <= m_nMagnify<29)
			{
				zoom = 0.05 - 2*(double)m_nMagnify / 1000;							//-0.004 -0.0042 -0.0044 0.008 0.00
			}
			*/
			
			for (int i = 0; i < (m_nMagnify-1); i++)
			{
				zoom = zoom * 1 / 2;
			}
			
			double x1 = m_point.x - (i_wid / 2)*zoom;
			if (x1 < 0)
			{
				//double x3 = x1;
				//x2 = x2 - x3;
				x1 = 0;
			}
			double y1 = m_point.y - (i_hei / 2)*zoom;
			if (y1 < 0)
			{
				//double y3 = y1;
				//y2 = y2 - y1;
				y1 = 0;
			}
			double x2 = m_point.x + (i_wid / 2)*zoom;
			if (x2>i_wid)
			{
				x2 = i_wid;
				//double x3 = i_wid*zoom;
				//x1 = x1 - (x2 - x3);
				//x2 = x3;
			}
			double y2 = m_point.y + (i_hei / 2)*zoom;
			if (y2 > i_hei)
			{
				y2 = i_hei;
			}
		
			//pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, m_point.x - (i_wid/2)*zoom, m_point.y - (i_hei/2)*zoom, m_point.x + (i_wid/2)*zoom, m_point.y + (i_hei/2)*zoom,SRCCOPY);
			
			pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2, y2, SRCCOPY);
			CRect xxyy(x1, y1, x2, y2);
			pre->R_Rect = xxyy;
			//pre->ShowWindow(SW_SHOW);
			//pre->OnPaint();
		}
		else if (m_nMagnify<1)
		{
			float zoom = 1 - 5 * ( ((float)m_nMagnify-1) / 10); //1.2 1.4 1.6 1.8 2.0 2.2
			double x1 = m_point.x - (i_wid / 2)*zoom;
			double y1 = m_point.y - (i_hei / 2)*zoom;
			double x2 = m_point.x + (i_wid / 2)*zoom;
			double y2 = m_point.y + (i_hei / 2)*zoom;
			
			pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2, y2, SRCCOPY);
			CRect xxyy(x1, y1, x2, y2);
			pre->R_Rect = xxyy;
			//pre->ShowWindow(SW_SHOW);
			//pre->OnPaint();
		}

		ReleaseDC(&dc);
		ReleaseDC(pDC);
	}
}

	void CNewProject01View::OnDestroy()
{
	CFormView::OnDestroy();
	/*
	mp_bitmap->DeleteObject();
	mp_display_memory->DeleteDC();
	delete mp_bitmap;
	delete mp_display_memory;
	delete bmp;
	*/

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CNewProject01View::OnStnClickedStaticDisp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



void CNewProject01View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/*
	if (nFlags&MK_SHIFT)
	{
		m_VectorRect.push_back(CRect(point.x, point.y, 0, 0));

		p_point.x = point.x;
		p_point.y = point.y;
		if (i_wid != 0 && wid != 0)
		{
			m_point.x = p_point.x / wid*(i_wid)*zoom;
			m_point.y = p_point.y / hei*(i_hei)*zoom;
		}
	}
	else
	{
		if (m_nMagnify < 6)
		{
			++m_nMagnify;
		}
	}
	*/
	if (point.x < wid&&point.y < hei)
	{

		if (nFlags&MK_SHIFT)
		{
			m_VectorRect.push_back(CRect(point.x, point.y, 0, 0));
			p_point.x = point.x;
			p_point.y = point.y;
			if (i_wid != 0 && wid != 0)
			{
				m_point.x = p_point.x / wid*(i_wid)*zoom;
				m_point.y = p_point.y / hei*(i_hei)*zoom;
			}
		}
		else
		{
			if (m_nMagnify==1 )
			{
				m_VectorRect.push_back(CRect(point.x, point.y, 0, 0));
					p_point.x = point.x;
					p_point.y = point.y;
					if (i_wid != 0 && wid != 0)
					{
						m_point.x = p_point.x / wid*(i_wid);
						m_point.y = p_point.y / hei*(i_hei);
					}
			}
			else if (m_nMagnify > 1)
			{
				for (int i = 0; i < m_nMagnify; i++)
				{
					//x0 y0 x1 y1 측정
				//	if (m_point.x)
				}
			}
			++m_nMagnify;
			
//			Preview::OnLButtonDown(nFlags, point);
		}
	}
	Invalidate(false);
	CFormView::OnLButtonDown(nFlags, point);
}


void CNewProject01View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/*
	if (nFlags&MK_SHIFT)
	{
		m_VectorRect.push_back(CRect(point.x, point.y, 0, 0));
		p_point.x = point.x;
		p_point.y = point.y;
		if (i_wid != 0 && wid != 0)
		{
			m_point.x = p_point.x*(i_wid)*zoom / wid;
			m_point.y = p_point.y*(i_hei)*zoom / hei;
		}
	}
	else
	{
		--m_nMagnify;
	}
	*/
	if (point.x < wid&&point.y < hei)
	{
		--m_nMagnify;
		p_point.x = point.x;
		p_point.y = point.y;
		if (i_wid != 0 && wid != 0)
		{
			m_point.x = p_point.x*(i_wid)*zoom / wid;
			m_point.y = p_point.y*(i_hei)*zoom / hei;
		}
	}
	Invalidate(false);
	CFormView::OnRButtonDown(nFlags, point);
}

