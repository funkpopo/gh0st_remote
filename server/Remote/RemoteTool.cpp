
// RemoteTool.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "RemoteTool.h"
#include "RemoteToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// dump相关
#include <io.h>
#include <direct.h>
#include <DbgHelp.h>
#pragma comment(lib, "Dbghelp.lib")


long WINAPI whenbuged(_EXCEPTION_POINTERS *excp)
{
	// 获取dump文件夹，若不存在，则创建之
	char dump[_MAX_PATH], *p = dump;
	GetModuleFileNameA(NULL, dump, _MAX_PATH);
	while (*p) ++p;
	while ('\\' != *p) --p;
	strcpy(p + 1, "dump");
	if (_access(dump, 0) == -1)
		_mkdir(dump);
	char curTime[64];// 当前dump文件
	time_t TIME(time(0));
	strftime(curTime, 64, "\\YAMA_%Y-%m-%d %H%M%S.dmp", localtime(&TIME));
	strcat(dump, curTime);
	HANDLE hFile = ::CreateFileA(dump, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, NULL);
	if(INVALID_HANDLE_VALUE != hFile)
	{
		MINIDUMP_EXCEPTION_INFORMATION einfo = {::GetCurrentThreadId(), excp, FALSE};
		::MiniDumpWriteDump(::GetCurrentProcess(), ::GetCurrentProcessId(),
			hFile, MiniDumpWithFullMemory, &einfo, NULL, NULL);
		::CloseHandle(hFile);
	}

	return EXCEPTION_EXECUTE_HANDLER;
}

BEGIN_MESSAGE_MAP(CMyRemoteApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMyRemoteApp 构造
CMyRemoteApp::CMyRemoteApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	m_Mutex = NULL;
}


// 唯一的一个 CMyRemoteApp 对象
CMyRemoteApp theApp;


// CMyRemoteApp 初始化
BOOL CMyRemoteApp::InitInstance()
{
	m_Mutex = CreateMutex(NULL, FALSE, "YAMA.EXE");
	if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		CloseHandle(m_Mutex);
		m_Mutex = NULL;
		return FALSE;
	}

	SetUnhandledExceptionFilter(&whenbuged);

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	SetRegistryKey(_T("Remoter"));

	CMyRemoteDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}


int CMyRemoteApp::ExitInstance()
{
	if (m_Mutex)
	{
		CloseHandle(m_Mutex);
		m_Mutex = NULL;
	}

	return CWinApp::ExitInstance();
}
