
// NewProject01Doc.cpp : CNewProject01Doc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "NewProject01.h"
#endif

#include "NewProject01Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define WIDTHBYTES(bits)	(((bits)+31)/32*4)
// CNewProject01Doc

IMPLEMENT_DYNCREATE(CNewProject01Doc, CDocument)

BEGIN_MESSAGE_MAP(CNewProject01Doc, CDocument)
END_MESSAGE_MAP()


// CNewProject01Doc ����/�Ҹ�

CNewProject01Doc::CNewProject01Doc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CNewProject01Doc::~CNewProject01Doc()
{
}

BOOL CNewProject01Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}
BOOL CNewProject01Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	//CFile���� ó��
	CFile hFile; //������ �о���̸� �� Ŭ���� �������� ����

	int height; //�̹����� ���̸� ������ ����
	int width; //�̹����� ���α��̸� ������ ����

	hFile.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);//���Ͽ���
	hFile.Read(&dibHf, sizeof(BITMAPFILEHEADER)); //dibHf�� ���� ����� �о���δ�.
	//�� ������ BMP�������� �˻�
	if (dibHf.bfType != 0x4D42)
	{
		AfxMessageBox(L"Not BMP file!!");
		return FALSE;
	}
	hFile.Read(&dibHi,sizeof(BITMAPINFOHEADER));
	if (dibHi.biBitCount != 8 && dibHi.biBitCount != 24)
	{
		AfxMessageBox(L"Gray/True Color Possible!!");
		return FALSE;
	}
	if (dibHi.biBitCount == 8) //8��Ʈ�� ��� �ȷ�Ʈ�� ������ �־�� �Ѵ�. �� 256���� ���̹Ƿ� �� ���̸�ŭ �о���δ�
	hFile.Read(palRGB, sizeof(RGBQUAD)* 256);

	//�޸� �Ҵ�
	int ImgSize;
	if (dibHi.biBitCount == 8)
	{
		ImgSize = hFile.GetLength() - sizeof(BITMAPFILEHEADER)-sizeof(BITMAPINFOHEADER)-256 * sizeof(RGBQUAD);
	}
	//�̹����� ũ��� ���� �� ���̿���, �� ���� �ȷ�Ʈ�� ����� �����Ѵ�.
	else if (dibHi.biBitCount == 24) //�÷�����
	{
		ImgSize = hFile.GetLength() - sizeof(BITMAPFILEHEADER)-sizeof(BITMAPINFOHEADER);
	}
	m_InImg = new unsigned char[ImgSize];
	m_OutImg = new unsigned char[ImgSize];
	hFile.Read(m_InImg, ImgSize);
	hFile.Close();

	height = dibHi.biHeight;
	width = dibHi.biWidth;
	return TRUE;
}

BOOL CNewProject01Doc::OnSaveDocument(LPCTSTR lpszPathName)

{

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CFile hFile;
	if (!hFile.Open(lpszPathName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
		return FALSE;
	//��������

	hFile.Write(&dibHf, sizeof(BITMAPFILEHEADER));
	hFile.Write(&dibHi, sizeof(BITMAPINFOHEADER));

	if (dibHi.biBitCount == 8)
		hFile.Write(palRGB, sizeof(RGBQUAD)* 256);

	hFile.Write(m_InImg, dibHi.biSizeImage);
	hFile.Close();

	return TRUE;

}

// CNewProject01Doc serialization

void CNewProject01Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CNewProject01Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CNewProject01Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CNewProject01Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CNewProject01Doc ����

#ifdef _DEBUG
void CNewProject01Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNewProject01Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CNewProject01Doc ���
