
// RemoteTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "iniFile.h"

class CMyRemoteApp : public CWinApp
{
public:
	CMyRemoteApp();
	iniFile  m_iniFile;
	HANDLE m_Mutex;
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CMyRemoteApp theApp;