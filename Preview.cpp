// Preview.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "NewProject01.h"
#include "Preview.h"
#include "afxdialogex.h"
#include <atlimage.h>


// Preview 대화 상자입니다.

IMPLEMENT_DYNAMIC(Preview, CDialogEx)

Preview::Preview(CWnd* pParent /*=NULL*/)
	: CDialogEx(Preview::IDD, pParent)
{

}

Preview::~Preview()
{
}

void Preview::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Preview, CDialogEx)
//	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Preview 메시지 처리기입니다.


//int Preview::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//	CClientDC cdc(this);
//	CDC *ppdc;
//	ppdc = &cdc;
//	m_MemDC.CreateCompatibleDC(&cdc);
//	m_cDC.CreateCompatibleDC(&cdc);
//	//CBitmap p_bitmap = CBitmap::FromHandle(p_image);
//	//!m_pBackBmp.LoadBitmapW(p_bitmap);
//
//	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
//
//	return 0;
//}


void Preview::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC *pdc = &dc;

	CRect p_rect;
	dc.GetClipBox(p_rect);
	p_wid = p_rect.Width();
	p_hei = p_rect.Height();
	double i_wid = p_image.GetWidth();
	double i_hei = p_image.GetHeight();
	if (!p_image.IsNull())
	{
		SetStretchBltMode(pdc->m_hDC, HALFTONE);
		//p_image.Draw(pdc->m_hDC, 0, 0, p_wid, p_hei, 0, 0, i_wid, i_hei, SRCCOPY);
		//p_image.Draw(pdc->m_hDC, 0, 0, p_wid, p_hei, 0, 0, i_wid, i_hei);
		p_image.StretchBlt(pdc->m_hDC, 0, 0, p_wid, p_hei, 0, 0, i_wid, i_hei, SRCCOPY);
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}
