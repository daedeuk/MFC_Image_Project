// Preview.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "NewProject01.h"
#include "Preview.h"
#include "afxdialogex.h"
#include <atlimage.h>
#include "NewProject01View.h"

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
	ON_WM_LBUTTONDOWN()
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
	GetClientRect(&p_rect);
	//dc.GetClipBox(p_rect);
	p_wid = p_rect.Width();
	p_hei = p_rect.Height();

	double i_wid = p_image.GetWidth();
	double i_hei = p_image.GetHeight();
	if (!p_image.IsNull())
	{
		SetStretchBltMode(pdc->m_hDC, HALFTONE);
		p_image.Draw(pdc->m_hDC, 0, 0, p_wid, p_hei, 0, 0, i_wid, i_hei);
		if (!R_Rect.IsRectNull())
		{
			CBrush brush;
			CPen MyPen(PS_SOLID, 1, RGB(255, 0, 0));
			CPen *oldPen = dc.SelectObject(&MyPen);
			brush.CreateStockObject(NULL_BRUSH);
			CBrush *oldBrush = dc.SelectObject(&brush);

			CPoint TopLeft = R_Rect.TopLeft();
			CPoint BottomRight = R_Rect.BottomRight();
			double R_x1 = TopLeft.x;
			double R_y1 = TopLeft.y;
			double R_x2 = BottomRight.x;
			double R_y2 = BottomRight.y;
			TopLeft.x = TopLeft.x / i_wid*p_wid;
			TopLeft.y = TopLeft.y / i_hei*p_hei;

			BottomRight.x = BottomRight.x / i_wid*p_wid;
			BottomRight.y = BottomRight.y / i_hei*p_hei;
			//dc.MoveTo(TopLeft);
			//dc.LineTo(BottomRight);
			dc.Rectangle(TopLeft.x, TopLeft.y, BottomRight.x, BottomRight.y);
			dc.SelectObject(oldBrush);
			//pen.DeleteObject();
			if (movepoint.x > -1)
			{
				((CNewProject01View *)GetParent())->CNewProject01View::pointmove(movepoint);
				movepoint.x = -1, movepoint.y = -1;
				((CNewProject01View *)GetParent())->Invalidate(false);
			}
			else if (movepoint.x = -1)
			{
				//((CNewProject01View *)GetParent())->Invalidate(false);
			}
		}
	}
	//ReleaseDC(NULL);
	ReleaseDC(&dc);
	ReleaseDC(pdc);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
}


void Preview::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (point.x >= 0 && point.x < p_wid&&point.y >= 0 && point.y < p_hei)
	{
		pre_point.x = point.x;
		pre_point.y = point.y;
		if (!p_image.IsNull())
		{
			movepoint.x = pre_point.x / p_wid*(((CNewProject01View *)GetParent())->i_wid);
			movepoint.y = pre_point.y / p_hei*(((CNewProject01View *)GetParent())->i_hei);
			//OnPaint();
		}
	}
	Invalidate(false);


	CDialogEx::OnLButtonDown(nFlags, point);

}

void Preview::SetParentWindow(CWnd *parm_parent_wnd)
{
	mp_parent_wnd = parm_parent_wnd;
}


void Preview::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CDialogEx::OnOK();
	//if (mp_parent_wnd != NULL) mp_parent_wnd->PostMessage(SC_CLOSE);
	//mp_parent_wnd->PostMessage(SC_CLOSE);
}


void Preview::OnCancel()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CDialogEx::OnCancel();
	//if (mp_parent_wnd != NULL) mp_parent_wnd->PostMessage(LM_CLOSE_DLG_MESSAGE);
	
	//if (mp_parent_wnd != NULL) mp_parent_wnd->PostMessage(SC_CLOSE);
	//mp_parent_wnd->PostMessage(SC_CLOSE);
}
