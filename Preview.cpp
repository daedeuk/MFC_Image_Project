// Preview.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "NewProject01.h"
#include "Preview.h"
#include "afxdialogex.h"
#include <atlimage.h>


// Preview ��ȭ �����Դϴ�.

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


// Preview �޽��� ó�����Դϴ�.


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
//	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
}
