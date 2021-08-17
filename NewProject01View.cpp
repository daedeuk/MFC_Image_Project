
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
			pDoc->m_Image.Destroy();
		}
		pDoc->m_Image.Load(strPathname);
		//c_image.Load(strPathname);
		zoom = 1;
		m_nMagnify = 1;
		m_point.x = pDoc->m_Image.GetWidth()/2;
		m_point.y = pDoc->m_Image.GetHeight()/2;
		//::ReleaseDC(hWnd, hdc);
		Invalidate(true);
		/*
		if (SUCCEEDED(hr))
			{
				::GetWindowRect(hWnd, &image_rect);
				::SetStretchBltMode(hdc, HALFTONE);
				::ReleaseDC(hWnd, hdc);
				Invalidate(false); 
				//ReleaseDC();
				//c_image.Draw(hdc, 0, 0, image_rect.Width(), image_rect.Height(), 0, 0, c_image.GetWidth(), c_image.GetHeight());
			}
		*/
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

	CNewProject01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	if (!pDoc->m_Image.IsNull())
	{
		CClientDC dc(this);
		pDC = &dc;
		CRect this_rect;
		dc.GetClipBox(&this_rect);
		double i_wid = pDoc->m_Image.GetWidth();
		double i_hei = pDoc->m_Image.GetHeight();
		SetStretchBltMode(pDC->m_hDC, HALFTONE);

		if (m_nMagnify >= 1)
		{
			//float zoom = (10 - 3*(float)m_nMagnify) / 10;

			double wid = this_rect.Width();
			double hei = this_rect.Height();
			p_point.x = m_point.x*wid / i_wid;
			p_point.y = m_point.y*hei / i_hei;
			m_point.x = m_point.x*i_wid / wid;
			m_point.y = m_point.y*i_hei / hei;
			//CRect new_rect(p_point.x - this_rect.Width()*m_nMagnify/2, p_point.y - this_rect.Height()*m_nMagnify/2, p_point.x + this_rect.Width()*m_nMagnify / 2, p_point.y + this_rect.Height()*m_nMagnify / 2);
			
			//double zoom_x = new_rect.Width();
			//double zoom_y = new_rect.Height();

			//double zoom_x = pDoc->m_Image.GetWidth()*m_nMagnify;
			//double zoom_y = pDoc->m_Image.GetHeight()*m_nMagnify;


			//pDoc->m_Image.Draw(pDC->m_hDC, 0, 0, xxx, yyy, 0, 0, pDoc->m_Image.GetWidth(), pDoc->m_Image.GetHeight());
			//pDoc->m_Image.Draw(pDC->m_hDC, 0, 0, xxx, yyy, 0, 0, xx, yy);
			//pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, xxx*m_nMagnify, yyy*m_nMagnify, SRCCOPY);
			//pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, xxx, yyy, SRCCOPY);
			//pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, 0, 0,zoom_x, zoom_y, SRCCOPY);
			
			pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid,hei, 0, 0, i_wid, i_hei,SRCCOPY);
			//zoom = 1;
			//pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, m_point.x - (i_wid)/2* zoom, m_point.y - (i_hei)/2 *zoom, m_point.x + (i_wid)/2*zoom, m_point.y + (i_hei)/2*zoom, SRCCOPY);
			
		}
		else
		{
			float zoom = (10 + 3*(float)m_nMagnify) / 10;
			double wid = this_rect.Width();
			double hei = this_rect.Height();
			p_point.x = m_point.x*wid / i_wid;
			p_point.y = m_point.y*hei / i_hei;

			m_point.x = m_point.x*i_wid / wid;
			m_point.y = m_point.y*i_hei / hei;
			//CRect new_rect(p_point.x -i_wid/(2-m_nMagnify) / 2, p_point.y - i_hei/(2-m_nMagnify) / 2, p_point.x + i_wid/(2-m_nMagnify) / 2, p_point.y + i_hei/(2-m_nMagnify) / 2);
			
			//double zoom_xx = new_rect.Width();
			//double zoom_yy = new_rect.Height();
			//double zoom_xx = pDoc->m_Image.GetWidth()/(2-m_nMagnify);
			//double zoom_yy = pDoc->m_Image.GetHeight()/(2-m_nMagnify);
			//double xxx = wid*xx / (xx + yy);
			//double yyy = wid*yy / (xx + yy);
			/*
			m_point.x = m_point.x*xx / (xx + yy);
			m_point.y = m_point.y*yy / (xx + yy);
			*/

			//pDoc->m_Image.Draw(pDC->m_hDC, 0, 0, xxx, yyy, 0, 0, pDoc->m_Image.GetWidth(), pDoc->m_Image.GetHeight());
			//pDoc->m_Image.Draw(pDC->m_hDC, 0, 0, xxx, yyy, 0, 0, xx, yy);
			//pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, xxx*m_nMagnify, yyy*m_nMagnify, SRCCOPY);
			//pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, xxx, yyy, SRCCOPY);
			//pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, 0, 0, zoom_xx, zoom_yy, SRCCOPY);
			//pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, m_point.x - (i_wid) / 2 * (2 - m_nMagnify), m_point.y - i_hei*(2 - m_nMagnify) / 2, m_point.x + (i_wid) / 2 * (2 - m_nMagnify), m_point.y + i_hei*(2 - m_nMagnify) / 2, SRCCOPY);
			pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, 0, 0, i_wid, i_hei,SRCCOPY);
			//zoom = 1;
			//pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, m_point.x -(i_wid)/ 2 * zoom, m_point.y - (i_hei) / 2 * zoom, m_point.x + (i_wid) / 2 * zoom, m_point.y + (i_hei) / 2 * zoom, SRCCOPY);
		}
		//pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, this_rect.Width(), this_rect.Height(), SRCCOPY);
		//DeleteObject(pDoc->m_Image);
		ReleaseDC(&dc);
		ReleaseDC(pDC);
	}
	/*
	mp_display_memory = new CDC();
	mp_bitmap = new CBitmap();
	GetClientRect(m_image_rect);

	//*mp_bitmap = cBitmap;
	CClientDC dc(this);
	mp_display_memory->CreateCompatibleDC(pDC);
	//mp_display_memory->CreateCompatibleDC(&dc);

	mp_bitmap->CreateCompatibleBitmap(pDC, m_image_rect.Width(), m_image_rect.Height());
	mp_old_bitmap = mp_display_memory->SelectObject(mp_bitmap);
	mp_display_memory->Rectangle(0, 0, m_image_rect.Width(), m_image_rect.Height());
	mp_display_memory->SelectObject(mp_old_bitmap);

	mp_old_bitmap = mp_display_memory->SelectObject(mp_bitmap);
	mp_display_memory->Rectangle(0, 0, 250, 250);
	dc.BitBlt(0, 0, m_image_rect.Width(), m_image_rect.Height(), mp_display_memory, 0, 0, SRCCOPY);
	mp_display_memory->SelectObject(mp_old_bitmap);
	*/
}

	void CNewProject01View::OnDestroy()
{
	CFormView::OnDestroy();
	mp_bitmap->DeleteObject();
	mp_display_memory->DeleteDC();\
	delete mp_bitmap;
	delete mp_display_memory;
	delete bmp;
	

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CNewProject01View::OnStnClickedStaticDisp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



void CNewProject01View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	++m_nMagnify;
	zoom = zoom /2;
	m_VectorRect.push_back(CRect(point.x,point.y,0,0));
	m_point.x = point.x;
	m_point.y= point.y;
	Invalidate(true);
	CFormView::OnLButtonDown(nFlags, point);
}


void CNewProject01View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	--m_nMagnify;
	zoom = zoom * 2;
	m_VectorRect.push_back(CRect(point.x, point.y, 0, 0));
	m_point.x = point.x;
	m_point.y = point.y;
	Invalidate(true);
	CFormView::OnRButtonDown(nFlags, point);
}