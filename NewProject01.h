
// NewProject01.h : NewProject01 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CNewProject01App:
// �� Ŭ������ ������ ���ؼ��� NewProject01.cpp�� �����Ͻʽÿ�.
//

class CNewProject01App : public CWinApp
{
public:
	CNewProject01App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CNewProject01App theApp;
