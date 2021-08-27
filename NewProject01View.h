
// NewProject01View.h : CNewProject01View 클래스의 인터페이스
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
#include <gdiplus.h>
//using namespace Gdiplus;
//#pragma comment (lib,"gdiplus.lib")

#include <opencv2/core/core.hpp>

#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/highgui/highgui.hpp>


//using namespace std;

class CNewProject01View : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CNewProject01View();
	DECLARE_DYNCREATE(CNewProject01View)
public:
	unsigned char** CNewProject01View::malloc2D(int h, int w);
	void CNewProject01View::free2DImage(unsigned char** image, int h);

	BITMAPINFO *m_pBitmapInfo;
	void CNewProject01View::PointColor(CImage *image, int x, int y, COLORREF c, int m_nBitDepth);
	COLORREF CNewProject01View::GetPointColor(CImage *image, int x, int y);
	void CreateBitmapInfo(int w, int h, int bpp);
	HBITMAP m_hbitmap;
	void TWAPI_CopyBitmap(CImage *ap_image, HBITMAP ah_bitmap);
	void DrawImage();
	void CNewProject01View::OnImageResize();
	void CNewProject01View::RGB2GRAY(COLORREF& rgb);
	void CNewProject01View::pointmove(CPoint movepoint);
	unsigned char** inImageR = NULL;
	unsigned char** inImageG = NULL;
	unsigned char** inImageB = NULL;
	unsigned char** outImageR = NULL;
	unsigned char** outImageG = NULL;
	unsigned char** outImageB = NULL;
	int inH = 0;
	int inW = 0;
	int outH = 0;
	int outW = 0;
	Preview *pre;
	CRect this_rect;
	CPoint p_point;
	CPoint m_point;
	CImage tips_image;
	CImage c_image;
	CImage m_image1;
	CImage d_image;
	CImage temp_image;
	CImage ero_image;
	double zoom;
	int m_nMagnify;
	//vector<CRect> m_VectorRect;
	//vector<CString> m_VectorString;
	double i_wid;
	double i_hei;
	double wid;
	double hei;
	double x1, x2, y1, y2;
	/*
	unsigned char *m_InImg; //bmp 파일의 이미지 내용 저장
	unsigned char *m_OutImg; //bmp이미지 출력용 배열
	BITMAPFILEHEADER dibHf; //비트맵 파일헤드 구조체
	BITMAPINFOHEADER dibHi; //비트맵 영상 헤드 구조체 
	RGBQUAD palRGB[256]; //팔레트 정보 구조체 배열
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

// 특성입니다.
public:

	CNewProject01Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	void DrawClipImage(HDC ah_dc, CImage *ap_image, POINT a_clip_start_pos, POINT a_clip_end_pos,
		int a_use_fixed_pos = 0, int a_fixed_x = 0, int a_fixed_y = 0);
	// ah_dc : 이미지를 출력할 DC의 핸들, ap_image : 부분 이미지를 사용할 CImage 객체의 주소
	// a_clip_start_pos : 원본 이미지에서 부분 이미지가 시작될 좌표, a_clip_end_pos : 원본 이미지에서 부분 이미지가 끝날 좌표
	// a_use_fixed_pos 값이 1이면 부분 이미지를 출력할때 특정 위치(a_fixed_x, a_fixed_y)를 지정, 0이면 사용 안함

	virtual void OnDraw(CDC* pDC);
	CRect CNewProject01View::Zoom_in_out(int m_nMagnify);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	BITMAPINFO* BmInfo;
	virtual ~CNewProject01View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnImageLoadImage();
	afx_msg void OnUpdateImageLoadimage(CCmdUI *pCmdUI);
	afx_msg void OnImageSaveImage();
	afx_msg void OnImageErrosion();
	afx_msg void OnDestroy();
	afx_msg void OnStnClickedStaticDisp();
	CStatic m_stDisp;
	CStatic M_stDisp;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickederrosion();
	afx_msg void OnBnClickedDilation();
};

#ifndef _DEBUG  // NewProject01View.cpp의 디버그 버전
inline CNewProject01Doc* CNewProject01View::GetDocument() const
   { return reinterpret_cast<CNewProject01Doc*>(m_pDocument); }
#endif

