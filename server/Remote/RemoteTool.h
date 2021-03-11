
// RemoteTool.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "iniFile.h"

class CMyRemoteApp : public CWinApp
{
public:
	CMyRemoteApp();
	iniFile  m_iniFile;
	HANDLE m_Mutex;
// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CMyRemoteApp theApp;