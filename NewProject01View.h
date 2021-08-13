
// NewProject01View.h : CNewProject01View Ŭ������ �������̽�
//

#pragma once

#include "resource.h"
#include "Resource.h"
#include "NewProject01Doc.h"
#include "cdib.h"
#include "afxwin.h"


class CNewProject01View : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CNewProject01View();
	DECLARE_DYNCREATE(CNewProject01View)
public:
	CImage c_image;
	
	/*
	unsigned char *m_InImg; //bmp ������ �̹��� ���� ����
	unsigned char *m_OutImg; //bmp�̹��� ��¿� �迭
	BITMAPFILEHEADER dibHf; //��Ʈ�� ������� ����ü
	BITMAPINFOHEADER dibHi; //��Ʈ�� ���� ��� ����ü 
	RGBQUAD palRGB[256]; //�ȷ�Ʈ ���� ����ü �迭
	virtual ~CNewProject01Doc(); 
	*/


private:
	CDC *mp_display_memory;
	CBitmap *mp_bitmap, *mp_old_bitmap;
	CRect m_image_rect;
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
	virtual void OnDraw(CDC* pDC);

public:
	enum{ IDD = IDD_NEWPROJECT01_FORM };

// Ư���Դϴ�.
public:
	CNewProject01Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
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
	afx_msg void OnDestroy();
	afx_msg void OnStnClickedStaticDisp();
	CStatic m_stDisp;
	CStatic M_stDisp;
};

#ifndef _DEBUG  // NewProject01View.cpp�� ����� ����
inline CNewProject01Doc* CNewProject01View::GetDocument() const
   { return reinterpret_cast<CNewProject01Doc*>(m_pDocument); }
#endif

