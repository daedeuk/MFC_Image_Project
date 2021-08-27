
// NewProject01View.cpp : CNewProject01View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "NewProject01.h"
#endif

#include "NewProject01Doc.h"
#include "NewProject01View.h"
#include <atlimage.h>

//#include "opencv2/opencv.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define SHIFTPressed() ( 0x8000 ==(GetKeyState(VK_SHIFT) & 0x8000   ))


// CNewProject01View

IMPLEMENT_DYNCREATE(CNewProject01View, CFormView)

BEGIN_MESSAGE_MAP(CNewProject01View, CFormView)
	ON_COMMAND(ID_FILE_OPEN, &CNewProject01View::OnImageLoadImage)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CNewProject01View::OnUpdateImageLoadimage)
	ON_COMMAND(ID_FILE_SAVE, &CNewProject01View::OnImageSaveImage)
	ON_COMMAND(ID_PROCESSING_ERROSION, &CNewProject01View::OnImageErrosion)
	ON_WM_DESTROY()
	ON_STN_CLICKED(IDC_STATIC_DISP, &CNewProject01View::OnStnClickedStaticDisp)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CNewProject01View ����/�Ҹ�

CNewProject01View::CNewProject01View()
: CFormView(CNewProject01View::IDD)
{
	m_nMagnify = 1;
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CNewProject01View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CNewProject01View ����

#ifdef _DEBUG
void CNewProject01View::AssertValid() const
{
	CFormView::AssertValid();
}

void CNewProject01View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CNewProject01Doc* CNewProject01View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNewProject01Doc)));
	return (CNewProject01Doc*)m_pDocument;
}
#endif //_DEBUG





// CNewProject01View �޽��� ó����
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

	// p_dest_image, p_src_image�� ���� �Ҵ�� �޸��� ���� �ּҸ� ����ϰ� �־���� 
	// �۾��� ���� �Ŀ� ���� �Ҵ�� �޸��� �ּҸ� ������ �� �ִ�. 
	//unsigned char *p_dest_pos = p_dest_image;
	//unsigned char *p_src_pos = p_src_image;
	CString szFilter = L"Image files (*.bmp, *.jpg) | *.bmp; *.jpg; | All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	//pDoc = GetDocument();
	if (dlg.DoModal() == IDOK)
	{
		CString strPathname = dlg.GetPathName();
		pDoc = GetDocument();
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
		//CT2CA pszString(strPathname);
		//std::string strPath(pszString);
		//image = cv::imread(strPath);
		/*
		CreateBitmapInfo(m_matImage.cols, m_matImage.rows, m_matImage.channels() * 8);
		DrawImage();
		*/
		pre = new Preview;
		pre->Create(IDD_DIALOG1, this);
		pre->p_image.Load(strPathname);
		pre->ShowWindow(SW_SHOW);
		pDoc->m_Image.Create(pre->p_image.GetWidth(), pre->p_image.GetHeight(), 8);
		pDoc->m_Image.Load(strPathname);
		BITMAP image_bmp_info;
		GetObject((HBITMAP)pDoc->m_Image, sizeof(BITMAP), &image_bmp_info);
		image_bmp_info.bmBits;

		//CreateBitmapInfo(pDoc->m_Image.GetWidth(), pDoc->m_Image.GetHeight() , pDoc->m_Image.GetBPP());
		//m_PreviewDlg = new CPreviewDlg();
		//m_PreviewDlg->Create(IDD_DIALOG1, this);
		//m_PreviewDlg->ShowWindow(SW_SHOW);

		//gray scale
		/*
		register int width = pDoc->m_Image.GetWidth();
		register int height = pDoc->m_Image.GetHeight();
		COLORREF rgb;
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				rgb = pDoc->m_Image.GetPixel(x, y);
				//RGB2GRAY(rgb);
				
				//pDoc->m_Image.SetPixel(x, y, rgb);
			}
		}
		*/
		
		
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
	//CString szFilter = L"Image files (*.bmp, *.jpg) | *.bmp; *.jpg; | All Files(*.*)|*.*||";
	CString szFilter = L"BMP Image (*.bmp) | *.bmp; | All Files(*.*)|*.*||";
	CFileDialog dlg(FALSE, L"bmp", L"*.bmp", OFN_HIDEREADONLY, szFilter);
	if (dlg.DoModal() == IDOK){
		CString SstrPathname = dlg.GetPathName();
		/*
		CImage TempSourceImage;
		CImage TempDestImage;
		CRect TempTargetRect=pre->R_Rect;
		CDC *pSourceDC = CDC::FromHandle(pDoc->m_Image.GetDC());
		int BitPerPixel = pSourceDC->GetDeviceCaps(BITSPIXEL);
		TempDestImage.Create(wid, hei, BitPerPixel);
		CDC*pDestDC = CDC::FromHandle(TempDestImage.GetDC());
		if (!pSourceDC || !pDestDC)
		{
			return;
		}
		pDestDC->BitBlt(0, 0, TempTargetRect.Width(), TempTargetRect.Height(), pSourceDC, TempTargetRect.left, TempTargetRect.top, SRCCOPY);
		TempDestImage.ReleaseDC();
		TempSourceImage.ReleaseDC();

		TempDestImage.Save(SstrPathname, ImageFormatBMP);
		*/
		
		//CClientDC h_dc(this);
//HDC h_dc = ::GetWindowDC(NULL);
		CImage tips_image;
		CDC *pSourceDC = CDC::FromHandle(pDoc->m_Image.GetDC());
		int BitPerPixel = pDoc->m_Image.GetBPP();
		//int BitPerPixel = pSourceDC->GetDeviceCaps(BITSPIXEL8;
		ReleaseDC(pSourceDC);
		tips_image.Create(wid, hei, BitPerPixel, 0);
		CDC* pDestDC = CDC::FromHandle(tips_image.GetDC());
		//tips_image.Create(wid, hei, 32, 0);e
		SetStretchBltMode(pDestDC->m_hDC, HALFTONE);
		//SetStretchBltMode(pDestDC->m_hDC, COLORONCOLOR);
		pDestDC->StretchBlt(0, 0, wid, hei, pSourceDC, pre->R_Rect.TopLeft().x, pre->R_Rect.TopLeft().y,
			pre->R_Rect.BottomRight().x - pre->R_Rect.TopLeft().x, pre->R_Rect.BottomRight().y - pre->R_Rect.TopLeft().y,
			SRCCOPY);
		//::BitBlt(tips_image.GetDC(), 0, 0, wid, hei, h_dc, 0, 0, SRCCOPY);
		tips_image.Save(SstrPathname, Gdiplus::ImageFormatBMP);
		//::ReleaseDC(NULL, h_dc);
		pDoc->m_Image.ReleaseDC();
		tips_image.ReleaseDC();
	}
}

unsigned char** malloc2D(int h, int w) {
	unsigned char** p;
	p = (unsigned char**)malloc(h * sizeof(unsigned char*));
	for (int i = 0; i < h; i++)
		p[i] = (unsigned char*)malloc(w * sizeof(unsigned char));
	return p;
}


void free2DImage(unsigned char** image, int h) {
	if (image == NULL)
		return;
	for (int i = 0; i < h; i++)
		free(image[i]);
	free(image);
	image = NULL;
}

void CNewProject01View::OnDraw(CDC* pDC)
{
	CWnd cwnd;
	CNewProject01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	

	
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	if (!pDoc->m_Image.IsNull())
	{
		if (pre->movepoint.x != -1 && pre->movepoint.y != -1)
		{
			m_point.x = pre->movepoint.x;
			m_point.y = pre->movepoint.y;
			pre->movepoint.x = -1;
			pre->movepoint.y = -1;
		}
		/*
		CFile f;
		BITMAPFILEHEADER bmfh;
		DWORD dwFileSize, dwDibSize;
		f.Open((strPathname), CFile::modeRead | CFile::shareDenyWrite, NULL);
		dwFileSize = (DWORD)f.GetLength();
		//��ü ������� BITMAPFILEHEADER�� ���� DIB����� �ȴ�.
		dwDibSize = dwFileSize - sizeof(BITMAPFILEHEADER);
		BYTE *pDib = new BYTE[dwDibSize];

		f.Read(&bmfh, sizeof(BITMAPFILEHEADER));//fileheader ����ü�б�
		f.Read(pDib, dwDibSize); //DIB�б�
		f.Close();

		BITMAPINFOHEADER *pBmh = (BITMAPINFOHEADER*)pDib;
		int nWidth = pBmh->biWidth;
		int nHeight = pBmh->biHeight;
		int nBit = pBmh->biBitCount;
		BYTE *lpBits = NULL;
		//���� ������ ��ġ
		if (nBit > 8)
		{
			lpBits = (BYTE*)pDib + sizeof(BITMAPINFOHEADER);
		}
		else
		{
			lpBits = (BYTE*)pDib + sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)+(1 << nBit);
		}
		// ������ ȭ�鿡 ǥ��
		*/

	
		//::SetDIBitsToDevice(dc.m_hDC, 0, 0, nWidth, nHeight, 0, 0, 0, nHeight, lpBits, (LPBITMAPINFO)pDib, DIB_RGB_COLORS);
		CClientDC dc(this);
		pDC = &dc;
		CRect new_rect;
		GetClientRect(&new_rect);
			i_wid = pDoc->m_Image.GetWidth();
			i_hei = pDoc->m_Image.GetHeight();
			wid = 0.4*new_rect.Width();
			hei = 0.4*new_rect.Width();
			//::StretchDIBits(dc.m_hDC, 0, 0, wid, hei, 0, 0, nWidth, nHeight, lpBits, (LPBITMAPINFO)pDib, DIB_RGB_COLORS, SRCCOPY);
			if (i_wid > i_hei)
			{
				hei = wid*(i_hei / i_wid);
			}
			else if (i_hei > i_wid)
			{
				wid = hei*(i_wid / i_hei);
			}
			/*
			if (((i_wid > i_hei) && ((i_wid / i_hei) > (wid / hei))) || ((i_wid < i_hei) && ((i_wid / i_hei)<(wid / hei))))
			{
				hei = 0.8*(i_hei / i_wid)*wid;
			}
			else if (((i_wid>i_hei) && ((i_wid / i_hei) < (wid / hei))) || ((i_wid<i_hei) && ((i_wid / i_hei)>(wid / hei))))
			{
				wid = 0.8*(i_wid / i_hei)*hei;
			}
			*/
		CRect this_rect(0, 0, wid, hei);

		//Ȯ�� 
		SetStretchBltMode(pDC->m_hDC, HALFTONE);

		//SetStretchBltMode(pDC->m_hDC, COLORONCOLOR);
		if (m_nMagnify == 1)
		{
			/*
			CImage TempSourceImage;
			CImage TempDestImage;
			CRect TempTargetRect = this_rect;

			CDC *pSourceDC = CDC::FromHandle(pDoc->m_Image.GetDC());
			int BitPerPixel = pSourceDC->GetDeviceCaps(BITSPIXEL);
			TempDestImage.Create(temptargetrect)
			*/

			m_point.x = i_wid / 2;
			m_point.y = i_hei / 2;
			zoom = 1.2 - 2 * ((double)m_nMagnify / 10);
			double x1 = m_point.x - (i_wid / 2)*zoom+1;
			double y1 = m_point.y - (i_hei / 2)*zoom+1;
			double x2 = m_point.x + (i_wid / 2)*zoom-1;
			double y2 = m_point.y + (i_hei / 2)*zoom-1;
			//m_image1.Draw(dc, 0, 0);
			CRect xxyy(x1, y1, x2, y2);
			pre->R_Rect = xxyy;
			zoom = 1;
			//pDoc->m_Image.Draw(pDC->m_hDC, 1, 1, wid-1, hei-1, x1, y1, x2, y2);
			//pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0,wid, hei, x1, y1, x2, y2, SRCCOPY);
			
			
			
			//StretchDIBits(pDC->m_hDC, 0, 0, wid, hei, 0,0,image.cols, image.rows, image.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
			//StretchDIBits(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2-x1, y2-y1, pDoc->m_Image.GetPixelAddress(0,0), m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
			
			pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2-x1, y2-y1, SRCCOPY);





			//CT2CA pszSTring(strPathname);
			//std::string strPath(pszSTring);
			//cv::Mat image = cv::imread(strPath);
			//std::string s((LPCTSTR)strPathname);
			//cv::Mat image = cv::imread(std::string s((LPCTSTR)strPathname);
			//OnImageResize();


			/*
			if (!tips_image.IsNull())
			{
				tips_image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, 0, 0, wid, hei, SRCCOPY);
			}
			*/

		}
		else if (m_nMagnify > 1)
		{
			/*
			if (m_nMagnify<11)
			{
				zoom = 1.1 - 2*((double)m_nMagnify / 10); //1.0 0.9 0.8 ~~ 0.1����
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
				x1 = 1;
			}
			double y1 = m_point.y - (i_hei / 2)*zoom;
			if (y1 < 0)
			{
				//double y3 = y1;
				//y2 = y2 - y1;
				y1 = 1;
			}
			double x2 = m_point.x + (i_wid / 2)*zoom;
			if (x2>i_wid)
			{
				x2 = i_wid-1;
				//double x3 = i_wid*zoom;
				//x1 = x1 - (x2 - x3);
				//x2 = x3;
			}
			double y2 = m_point.y + (i_hei / 2)*zoom;
			if (y2 > i_hei)
			{
				y2 = i_hei-1;
			}
		
			//pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, m_point.x - (i_wid/2)*zoom, m_point.y - (i_hei/2)*zoom, m_point.x + (i_wid/2)*zoom, m_point.y + (i_hei/2)*zoom,SRCCOPY);
		
			//pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2, y2, SRCCOPY);
			//pDoc->m_Image.Draw(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2, y2);

			//pDoc->m_Image.Draw(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2, y2);
			CRect xxyy(x1, y1, x2, y2);
			pre->R_Rect = xxyy;
			zoom = 1;
			//pDoc->m_Image.Draw(pDC->m_hDC, 1, 1, wid - 1, hei - 1, x1, y1, x2, y2);

			/*
			temp_image.Create(x2 - x1, y2 - y1, pDoc->m_Image.GetBPP(), 0);
			POINT start_pos = { x1, y1 }, end_pos = { x2, y2 };
			//DrawClipImage(temp_image.GetDC(), &c_image, start_pos, end_pos, 1, 0, 0);
			temp_image.ReleaseDC();
			*/

			//StretchDIBits(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2 - x1, y2 - y1, pDoc->m_Image.GetPixelAddress(0, 0), m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
			//StretchDIBits(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2 - x1, y2 - y1, image.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
			pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2-x1, y2-y1, SRCCOPY);
		
		}
		else if (m_nMagnify<1)
		{
			
			zoom = 1 - 5*( ((double)m_nMagnify-1) / 10); //1.2 1.4 1.6 1.8 2.0 2.2
			//1.5 2.0 2.5 3.0 3.5
			double x1 = m_point.x - (i_wid / 2)*zoom;
			double y1 = m_point.y - (i_hei / 2)*zoom;
			double x2 = m_point.x + (i_wid / 2)*zoom;
			double y2 = m_point.y + (i_hei / 2)*zoom;
			
			//pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2, y2, SRCCOPY);
			//pDoc->m_Image.Draw(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2, y2);
			CRect xxyy(x1, y1, x2, y2);
			pre->R_Rect = xxyy;
			zoom = 1;
			//pDoc->m_Image.Draw(pDC->m_hDC, 1, 1, wid - 1, hei - 1, x1, y1, x2, y2);

			//StretchDIBits(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2 - x1, y2 - y1, pDoc->m_Image.GetPixelAddress(0, 0), m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
			//StretchDIBits(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2 - x1, y2 - y1, image.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
			pDoc->m_Image.StretchBlt(pDC->m_hDC, 0, 0, wid, hei, x1, y1, x2-x1, y2-y1, SRCCOPY);
			
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CNewProject01View::OnStnClickedStaticDisp()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}



void CNewProject01View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (point.x < wid&&point.y < hei)
	{
		if (TRUE == SHIFTPressed())
		{
			//m_VectorRect.push_back(CRect(point.x, point.y, 0, 0));
			p_point.x = point.x;
			p_point.y = point.y;

			if (i_wid != 0 && wid != 0)
			{
				m_point.x = p_point.x / wid * (pre->R_Rect.Width()) + (pre->R_Rect.TopLeft().x);
				m_point.y = p_point.y / hei*  (pre->R_Rect.Height()) + (pre->R_Rect.TopLeft().y);
				Invalidate(false);
				/*
				if (point.x < wid / 2)
				{
					m_point.x = m_point.x -(p_point.x / wid*(pre->R_Rect.Width()));
					if (m_point.x< 0)
					{
						m_point.x = 0;
					}
					Invalidate(false);
				}
				else
				{
					m_point.x = m_point.x + p_point.x / wid*(pre->R_Rect.Width());
					if (m_point.x + (pre->R_Rect.Width() / 2)>i_wid)
					{
						m_point.x = i_wid - pre->R_Rect.Width() / 2;
					}
					Invalidate(false);
				}
				if (point.y < hei / 2)
				{
					m_point.y = m_point.y -(p_point.y / hei*(pre->R_Rect.Height()));
					if (m_point.y< 0)
					{
						m_point.y= 0;
					}
					Invalidate(false);
				}
				else
				{
					m_point.y = m_point.y + p_point.y / hei*(pre->R_Rect.Height());
					if (m_point.y + (pre->R_Rect.Height() / 2)>i_hei)
					{
						m_point.y = i_hei - pre->R_Rect.Height() / 2;
					}
					Invalidate(false);
				}
				*/
			}
		}
		else
		{
			p_point.x = point.x;
			p_point.y = point.y;

			if (i_wid != 0 && wid != 0)
			{
				m_point.x = p_point.x / wid * (pre->R_Rect.Width()) + (pre->R_Rect.TopLeft().x);
				m_point.y = p_point.y / hei*  (pre->R_Rect.Height()) + (pre->R_Rect.TopLeft().y);
			}
			if (m_nMagnify == 0 || m_nMagnify == 1)
			{
				//m_VectorRect.push_back(CRect(point.x, point.y, 0, 0));
					p_point.x = point.x;
					p_point.y = point.y;
					if (i_wid != 0 && wid != 0)
					{
						m_point.x = p_point.x / wid*(i_wid)*zoom;
						m_point.y = p_point.y / hei*(i_hei)*zoom;
					}
			}
			/*
			else if (m_nMagnify > 1)
			{
				for (int i = 0; i < m_nMagnify; i++)
				{
					//x0 y0 x1 y1 ����
				//	if (m_point.x)
				}
			}
			*/
			if (m_nMagnify < 7)
			{
				zoom = 1;
				++m_nMagnify;
			}
//			Preview::OnLButtonDown(nFlags, point);
		}
	}
	Invalidate(false);
	CFormView::OnLButtonDown(nFlags, point);
}


void CNewProject01View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (point.x < wid&&point.y < hei)
	{
		if (TRUE==SHIFTPressed())
		{
			//m_VectorRect.push_back(CRect(point.x, point.y, 0, 0));
			p_point.x = point.x;
			p_point.y = point.y;
			if (i_wid != 0 && wid != 0)
			{
				if (i_wid != 0 && wid != 0)
				{
					m_point.x =p_point.x / wid * (pre->R_Rect.Width()) + (pre->R_Rect.TopLeft().x);
					m_point.y =p_point.y / hei*  (pre->R_Rect.Height()) + (pre->R_Rect.TopLeft().y);
					Invalidate(false);
				}
			}
		}
		else
		{
			if (m_nMagnify==0 ||m_nMagnify == 1)
			{
				//m_VectorRect.push_back(CRect(point.x, point.y, 0, 0));
				p_point.x = point.x;
				p_point.y = point.y;
				if (i_wid != 0 && wid != 0)
				{
					m_point.x = p_point.x / wid*(i_wid)*zoom;
					m_point.y = p_point.y / hei*(i_hei)*zoom;
				}
			}
			/*
			else if (m_nMagnify < 1)
			{
				//m_point.x = pDoc->m_Image.GetWidth() / 2;
				//m_point.y = pDoc->m_Image.GetHeight() / 2;
			}
			*/
			if (m_nMagnify>1)
			{
				zoom = 1;
				--m_nMagnify;
			}
		}
	}
	Invalidate(false);
	CFormView::OnRButtonDown(nFlags, point);
}

void CNewProject01View::OnImageErrosion()
{
	// TODO: ���⿡ ���� �ڵ� �߰�.r
	/*
	if (inImageR == NULL)
	return;
	*/
	// ������ ó���� ���� ������ �ϴ� �޸� ����
	inH = i_hei;
	inW = i_wid;
	free2DImage(inImageR, inH);
	free2DImage(inImageG, inH);
	free2DImage(inImageB, inH);
	// �߿�! ��� ���� ũ�� --> �˰��� ����
	// ��� �޸� �Ҵ�.
	inImageR = malloc2D(inH, inW);
	inImageG = malloc2D(inH, inW);
	inImageB = malloc2D(inH, inW);
	COLORREF pixel; // �� ��(R,G,B)
	for (int i = 0; i < inH; i++)
	{
		for (int k = 0; k < inW; k++) {
			pixel = pDoc->m_Image.GetPixel(k, i);
			inImageR[i][k] = (unsigned char)GetRValue(pixel);
			inImageG[i][k] = (unsigned char)GetGValue(pixel);
			inImageB[i][k] = (unsigned char)GetBValue(pixel);
		}
	}
	free2DImage(outImageR, outH);
	free2DImage(outImageG, outH);
	free2DImage(outImageB, outH);
	// �߿�! ��� ���� ũ�� --> �˰��� ����
	outH = inH;  outW = inW;
	// ��� �޸� �Ҵ�.
	outImageR = malloc2D(outH, outW);
	outImageG = malloc2D(outH, outW);
	outImageB = malloc2D(outH, outW);
	temp_image.Create(i_wid, i_hei, 8);
	int mask[3][3] = { { -1, -1, -1 },
	{ -1, 8, -1 },
	{ -1, -1, -1 }
	};
	unsigned char minR = 255, minG = 255, minB = 255;
	for (int i = 1; i < inH - 1; i++) {
		for (int j = 1; j < inW - 1; j++) {
			minR = 255, minG = 255, minB = 255;
			for (int k = 0; k < 3; k++)
			{
				for (int m = 0; m < 3; m++)
				{
					if (minR > inImageR[i - 1 + k][j - 1 + m]) {
						minR = inImageR[i - 1 + k][j - 1 + m];
					}
					if (minG > inImageG[i - 1 + k][j - 1 + m]) {
						minG = inImageG[i - 1 + k][j - 1 + m];
					}
					if (minB > inImageB[i - 1 + k][j - 1 + m]) {
						minB = inImageB[i - 1 + k][j - 1 + m];
					}
				}
			}
			outImageR[i][j] = minR;
			outImageG[i][j] = minG;
			outImageB[i][j] = minB;
		}
	}
	
		int i, k;
		unsigned char R, G, B;
		for (i = 0; i < outH; i++) {
			for (k = 0; k < outW; k++) {
				R = outImageR[i][k];

				G = outImageG[i][k];
				B = outImageB[i][k];

				//pDoc->m_Image.SetPixel(k, i, RGB(R, G, B));
				temp_image.SetPixel(k, i, RGB(R, R, R));
			}
		}
		pDoc->m_Image = temp_image;
	

		pre->p_image = temp_image;
		Invalidate(false);
}

void CNewProject01View::OnImageResize()
{
	//CClientDC h_dc(this);
	//HDC h_dc = ::GetWindowDC(NULL);
	CImage resize_image;
	CDC *pSourceDC = CDC::FromHandle(pDoc->m_Image.GetDC());
	int BitPerPixel = pSourceDC->GetDeviceCaps(BITSPIXEL);
	ReleaseDC(pSourceDC);
	//int cx = ::GetSystemMetrics(SM_CXSCREEN);
	//int cy = ::GetSystemMetrics(SM_CYSCREEN);
	//int color_depth = ::GetDeviceCaps(h_dc, BITSPIXEL);
	//tips_image.Create(wid, hei, color_depth, 0);
	tips_image.Create(wid, hei, BitPerPixel, 0);
	//tips_image.Create(wid, hei, 32, 0);
	//::BitBlt(tips_image.GetDC(), 0, 0, wid, hei, h_dc, 0, 0, SRCCOPY);
	//tips_image.Save(SstrPathname, ImageFormatBMP);
	//::ReleaseDC(NULL, h_dc);
	tips_image.ReleaseDC();
	Invalidate(false);
}

/*
void CNewProject01View::RGB2GRAY(COLORREF& rgb)
{
	unsigned char grayColor = ((GetRValue(rgb)*0.3) + (GetRValue(rgb)*0.59) + (GetBValue(rgb)*0.11));
	rgb = RGB(grayColor, grayColor, grayColor);

}
*/


void CNewProject01View::CreateBitmapInfo(int w, int h, int bpp)
{
	if (m_pBitmapInfo != NULL)
	{
		delete m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}

	if (bpp == 8)
		m_pBitmapInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO)+255 * sizeof(RGBQUAD)];
	else // 24 or 32bit
		m_pBitmapInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO)];

	m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo->bmiHeader.biPlanes = 1;
	m_pBitmapInfo->bmiHeader.biBitCount = bpp;
	m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	m_pBitmapInfo->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo->bmiHeader.biClrImportant = 0;

	if (bpp == 8)
	{
		for (int i = 0; i < 256; i++)
		{
			m_pBitmapInfo->bmiColors[i].rgbBlue = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbGreen = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbRed = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbReserved = 0;
		}
	}

	m_pBitmapInfo->bmiHeader.biWidth = w;
	m_pBitmapInfo->bmiHeader.biHeight = -h;
}


/*
void TWAPI_CopyBitmap(CImage *ap_image, HBITMAP ah_bitmap)
{
	BITMAP bmp_info;

	// ah_bitmap ��Ʈ���� �Ӽ� ������ ��´�.
	GetObject(ah_bitmap, sizeof(BITMAP), &bmp_info);
	// ah_bitmap�� ��, ���� �׸��� ���� ���� ��ġ�� ��Ʈ���� �����Ѵ�.
	ap_image->Create(bmp_info.bmWidth, bmp_info.bmHeight, bmp_info.bmBitsPixel);

	// �� �׷��� ��ġ�� ȣȯ�Ǵ� 'Memory DC'�� �����Ѵ�.
	HDC h_dc = CreateCompatibleDC(NULL);
	// ������ DC�� h_src_bmp�� �����Ѵ�.
	SelectObject(h_dc, ah_bitmap);
	// h_src_bmp�� '��Ʈ ����'�� dest_image ��ü�� ����˴ϴ�.
	BitBlt(ap_image->GetDC(), 0, 0, bmp_info.bmWidth, bmp_info.bmHeight, h_dc, 0, 0,
		SRCCOPY);

	ap_image->ReleaseDC();  // '��Ʈ ����'�� ����ϱ� ���� ������ DC ����
	DeleteDC(h_dc);             // '��Ʈ ����'�� ����ϱ� ���� ������ DC ����

*/

void CNewProject01View::pointmove(CPoint movepoint)
{
	m_point.x = movepoint.x;
	m_point.y = movepoint.y;
	return;
}
