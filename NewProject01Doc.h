
// NewProject01Doc.h : CNewProject01Doc Ŭ������ �������̽�
//


#pragma once


class CNewProject01Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CNewProject01Doc();
	DECLARE_DYNCREATE(CNewProject01Doc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	unsigned char *m_InImg; //bmp ������ �̹��� ���� ����
	unsigned char *m_OutImg; //bmp�̹��� ��¿� �迭
	BITMAPFILEHEADER dibHf; //��Ʈ�� ������� ����ü
	BITMAPINFOHEADER dibHi; //��Ʈ�� ���� ��� ����ü 
	RGBQUAD palRGB[256]; //�ȷ�Ʈ ���� ����ü �迭

	virtual ~CNewProject01Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};