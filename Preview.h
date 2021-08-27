#pragma once
#include "resource.h"
#include "stdafx.h"

// Preview ��ȭ �����Դϴ�.

class Preview : public CDialogEx
{
	DECLARE_DYNAMIC(Preview)
private:
	CWnd *mp_parent_wnd;
public:
	void SetParentWindow(CWnd *parm_parent_wnd);
	CPoint movepoint=(-1,-1);
	CPoint pre_point;
	CRect R_Rect;
	CBitmap	m_pBackBmp;
	CDC		m_MemDC;
	CDC		m_cDC;
	CImage p_image;

	double p_wid;
	double p_hei;
	Preview(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Preview();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };
private:

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnOK();
	virtual void OnCancel();
};
