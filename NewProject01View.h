
// NewProject01View.h : CNewProject01View Ŭ������ �������̽�
//

#pragma once

#include "resource.h"
#include "Resource.h"
#include "NewProject01Doc.h"
#include "cdib.h"
#include "afxwin.h"
#include <iostream>
#include <vector>
#include "Preview.h"

using namespace std;

class CNewProject01View : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CNewProject01View();
	DECLARE_DYNCREATE(CNewProject01View)
public:
	Preview *pre;
	CRect this_rect;
	CPoint p_point;
	CPoint m_point;
	CImage c_image;
	double zoom;
	int m_nMagnify;
	vector<CRect> m_VectorRect;
	vector<CString> m_VectorString;
	double i_wid;
	double i_hei;
	double wid;
	double hei;
	/*
	unsigned char *m_InImg; //bmp ������ �̹��� ���� ����
	unsigned char *m_OutImg; //bmp�̹��� ��¿� �迭
	BITMAPFILEHEADER dibHf; //��Ʈ�� ������� ����ü
	BITMAPINFOHEADER dibHi; //��Ʈ�� ���� ��� ����ü 
	RGBQUAD palRGB[256]; //�ȷ�Ʈ ���� ����ü �迭
	virtual ~CNewProject01Doc(); 
	*/


private:
	HBITMAP hbitmap;
	CNewProject01Doc* pDoc;
	CDC *mp_display_memory;
	CBitmap *mp_bitmap, *mp_old_bitmap;
	CRect m_image_rect;
	CImage Buf_image;
	CString strPathname;
	CFile f;
	CDib rtrt;
	CRect image_rect;
	double x, y;
	CSize image_xy;
	

	HANDLE bmp;
	CBitmap cBitmap;
	BITMAP bmpinfo;

protected:

public:
	enum{ IDD = IDD_NEWPROJECT01_FORM };

// Ư���Դϴ�.
public:

	CNewProject01Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);
	CRect CNewProject01View::Zoom_in_out(int m_nMagnify);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	BITMAPINFO* BmInfo;
	virtual ~CNewProject01View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnImageLoadImage();
	afx_msg void OnUpdateImageLoadimage(CCmdUI *pCmdUI);
	afx_msg void OnImageSaveImage();
	afx_msg void OnDestroy();
	afx_msg void OnStnClickedStaticDisp();
	CStatic m_stDisp;
	CStatic M_stDisp;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // NewProject01View.cpp�� ����� ����
inline CNewProject01Doc* CNewProject01View::GetDocument() const
   { return reinterpret_cast<CNewProject01Doc*>(m_pDocument); }
#endif

