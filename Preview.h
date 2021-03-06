#pragma once
#include "resource.h"
#include "stdafx.h"

// Preview 대화 상자입니다.

class Preview : public CDialogEx
{
	DECLARE_DYNAMIC(Preview)
private:
	CWnd *mp_parent_wnd;
public:
	void SetParentWindow(CWnd *parm_parent_wnd);
	CPoint movepoint;
	CPoint pre_point;
	CRect R_Rect;

	CImage p_image;

	double p_wid;
	double p_hei;
	Preview(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Preview();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };
private:

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnOK();
	virtual void OnCancel();
};
