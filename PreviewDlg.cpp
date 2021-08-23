// PreviewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "NewProject01.h"
#include "PreviewDlg.h"
#include "afxdialogex.h"


// CPreviewDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPreviewDlg, CDialog)

CPreviewDlg::CPreviewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPreviewDlg::IDD, pParent)
{

}

CPreviewDlg::~CPreviewDlg()
{
}

void CPreviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPreviewDlg, CDialog)
END_MESSAGE_MAP()


// CPreviewDlg 메시지 처리기입니다.
