
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNewProject01View

IMPLEMENT_DYNCREATE(CNewProject01View, CFormView)

BEGIN_MESSAGE_MAP(CNewProject01View, CFormView)
	ON_COMMAND(ID_FILE_OPEN, &CNewProject01View::OnImageLoadImage)
	ON_WM_DESTROY()
	ON_STN_CLICKED(IDC_STATIC_DISP, &CNewProject01View::OnStnClickedStaticDisp)
END_MESSAGE_MAP()

// CNewProject01View ����/�Ҹ�

CNewProject01View::CNewProject01View()
: CFormView(CNewProject01View::IDD)
{
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
	HWND hWnd = m_stDisp.GetSafeHwnd();
	HDC hdc = ::GetDC(hWnd);

	///c_image.Create(512, 512, 32);
	//unsigned char *p_src_image = new unsigned char[512 * 512];
	//unsigned char *p_dest_image = new unsigned char[512 * 512 * 4];

	// p_dest_image, p_src_image�� ���� �Ҵ�� �޸��� ���� �ּҸ� ����ϰ� �־���� 
	// �۾��� ���� �Ŀ� ���� �Ҵ�� �޸��� �ּҸ� ������ �� �ִ�. 
	//unsigned char *p_dest_pos = p_dest_image;
	//unsigned char *p_src_pos = p_src_image;

	CString szFilter = L"Image files (*.bmp, *.jpg) | *.bmp; *.jpg; | All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	CString strPathname;
	CFile f;
	//CDib rtrt();
	
	if (dlg.DoModal() == IDOK)
	{
		strPathname = dlg.GetPathName();
		HRESULT hr=c_image.Load(strPathname);
		if (SUCCEEDED(hr))
		{
			image_rect;
			::GetWindowRect(hWnd, &image_rect);
			::SetStretchBltMode(hdc, HALFTONE);
			c_image.Draw(hdc, 0, 0, image_rect.Width(), image_rect.Height(), 0, 0, c_image.GetWidth(), c_image.GetHeight());
		}
		//c_image.Draw(dc, 0, 0);
		//ReleaseDC(*hWnd);
		//c_image.Load(strPathname);
		//x = c_image.GetWidth();
		//y = c_image.GetHeight();
		CSize image_xy(x, y);
		if (f.Open(strPathname, CFile::modeRead))
		{
			CArchive ar(&f, CArchive::load);
			//bmp = LoadImage(NULL, strPathname, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			//mp_bitmap->Attach(bmp);
			//mp_bitmap->GetBitmap(&bmpinfo);
		}
	}
}

void CNewProject01View::OnDraw(CDC* pDC)
{

	#define WIDTHBYTES(bits)	(((bits)+31)/32*4);        //�̹��� ���� ����Ʈ ���̴� 4����Ʈ�� ���
	//BmInfo;
	int height;
	int width;
	int rwsize;

	CNewProject01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	if (pDoc->m_InImg == NULL)
	return;

	 /*
	//24��Ʈ ��Ʈ�� ������ �������
	if (pDoc->dibHi.biBitCount == 24){
		height = pDoc->dibHi.biHeight;
		width = pDoc->dibHi.biWidth;
		rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount*pDoc->dibHi.biWidth);
		BmInfo->bmiHeader = pDoc->dibHi;
		SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, width, height, 0, 0, 0, height, pDoc->m_InImg, BmInfo, DIB_RGB_COLORS);
	}
	else	//8��Ʈ �÷��� ���
	{
		int index;
		rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount*pDoc->dibHi.biWidth);
		//�ȷ�Ʈ�� �о���̸� �ݺ����
		for (int i = 0; i<pDoc->dibHi.biHeight; i++)
		for (int j = 0; j < pDoc->dibHi.biWidth; j++){
			index = pDoc->m_InImg[i*rwsize + j];
			BYTE R = pDoc->palRGB[index].rgbRed;
			BYTE G = pDoc->palRGB[index].rgbGreen;
			BYTE B = pDoc->palRGB[index].rgbBlue;
			//pDC->SetPixel(j,i,RGB(R,G,B));
			//���� �������
			pDC->SetPixel(j, pDoc->dibHi.biHeight - i - 1, RGB(R, G, B));
		}
	}
	 */
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
	
}

void CNewProject01View::OnDestroy()
{
	CFormView::OnDestroy();
	mp_bitmap->DeleteObject();
	mp_display_memory->DeleteDC();

	delete mp_bitmap;
	delete mp_display_memory;
	delete bmp;
	

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CNewProject01View::OnStnClickedStaticDisp()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
