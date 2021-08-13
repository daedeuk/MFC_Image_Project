// cdib.h declaration for Inside Visual C++ CDib class

#ifndef _INSIDE_VISUAL_CPP_CDIB
#define _INSIDE_VISUAL_CPP_CDIB

class CDib : public CObject
{
	DECLARE_SERIAL(CDib)
public:
	LPVOID m_lpvColorTable;
	HBITMAP m_hBitmap;
	LPBYTE m_lpImage;  // starting address of DIB bits
	LPBITMAPINFOHEADER m_lpBMIH; //  buffer containing the BITMAPINFOHEADER
protected:
	enum Alloc {noAlloc, crtAlloc, heapAlloc};
	HGLOBAL m_hGlobal; // For external windows we need to free;
	                   //  could be allocated by this class or allocated externally
	Alloc m_nBmihAlloc;
	Alloc m_nImageAlloc;
	DWORD m_dwSizeImage; // of bits -- not BITMAPINFOHEADER or BITMAPFILEHEADER
	int m_nColorTableEntries;
	
	HANDLE m_hFile;
	HANDLE m_hMap;
	LPVOID m_lpvFile;
	HPALETTE m_hPalette;
public:
	void SetPixel(CPoint pt, int n);
	void ThreasHold(int n);
	void ChangePalette(COLORREF c);
	void GreenPalette();
	void RedPalette();
	void BluePalette();
	void SetImageRect(CRect rect);
	LPBITMAPINFOHEADER GetBMIH();
	int GetColorTableEntries();
	void MakeBitmapPalette();
	BYTE** GetRectPointer();
	LPBYTE GetMemPointer();
	int GetPixel(CPoint point);
	bool InImage(int x, int y);
	int GetPixel(int x, int y);
	int GetHeight();
	int GetWidth();
	CDib();
	CDib(CSize size, int nBitCount);	// builds BITMAPINFOHEADER
	CDib(CSize size, int nBitCount, bool bAllocMem);
	~CDib();
	int GetSizeImage() {return m_dwSizeImage;}
	int GetSizeHeader()
		{return sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries;}
	CSize GetDimension();
	bool AttachMapFile(const char* strPathname, bool bShare = FALSE);
	bool CopyToMapFile(const char* strPathname);
	bool AttachMemory(LPVOID lpvMem, bool bMustDelete = FALSE, HGLOBAL hGlobal = NULL);
	bool Draw(CDC* pDC, CPoint origin, CSize size);  // until we implemnt CreateDibSection
	bool Draw(CDC* pDC, CRect dest, CRect source);  // until we implemnt CreateDibSection
	bool Draw(CDC* pDC, CRect dest, CRect source, DWORD dwRop);
	HBITMAP CreateSection(CDC* pDC = NULL);
	UINT UsePalette(CDC* pDC, bool bBackground = FALSE);
	bool MakePalette();
	bool SetSystemPalette(CDC* pDC);
	bool Compress(CDC* pDC, bool bCompress = TRUE); // FALSE means decompress
	HBITMAP CreateBitmap(CDC* pDC);
	bool Read(CFile* pFile);
	bool ReadSection(CFile* pFile, CDC* pDC = NULL);
	bool Write(CFile* pFile);
	void Serialize(CArchive& ar);
	void Empty();
protected:
	BYTE** m_ppBuff;
	CRect m_rImageRect;
	void DetachMapFile();
	void ComputePaletteSize(int nBitCount);
	void ComputeMetrics();
private:
	bool m_bImageAlloc;
};
#endif // _INSIDE_VISUAL_CPP_CDIB
