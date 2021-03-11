// ShellDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RemoteTool.h"
#include "ShellDlg.h"
#include "afxdialogex.h"


// CShellDlg 对话框

IMPLEMENT_DYNAMIC(CShellDlg, CDialog)

CShellDlg::CShellDlg(CWnd* pParent, IOCPServer* IOCPServer, CONTEXT_OBJECT *ContextObject)
	: CDialog(CShellDlg::IDD, pParent)
{
	m_iocpServer	= IOCPServer;
	m_ContextObject		= ContextObject;

	m_hIcon			= LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_SHELL)); 
}

CShellDlg::~CShellDlg()
{
}

void CShellDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT, m_Edit);
}


BEGIN_MESSAGE_MAP(CShellDlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CShellDlg 消息处理程序


BOOL CShellDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_nCurSel = 0;
	m_nReceiveLength = 0;
	SetIcon(m_hIcon,FALSE);

	CString str;
	sockaddr_in  ClientAddr;
	memset(&ClientAddr, 0, sizeof(ClientAddr));
	int ClientAddrLen = sizeof(ClientAddr);
	BOOL bResult = getpeername(m_ContextObject->sClientSocket, (SOCKADDR*)&ClientAddr, &ClientAddrLen);

	str.Format("%s - 远程终端", bResult != INVALID_SOCKET ? inet_ntoa(ClientAddr.sin_addr) : "");
	SetWindowText(str);

	BYTE bToken = COMMAND_NEXT;
	m_iocpServer->OnClientPreSending(m_ContextObject, &bToken, sizeof(BYTE));  

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


VOID CShellDlg::OnReceiveComplete()
{
	if (m_ContextObject==NULL)
	{
		return;
	}

	AddKeyBoardData();
	m_nReceiveLength = m_Edit.GetWindowTextLength();
}


VOID CShellDlg::AddKeyBoardData(void)
{
	m_ContextObject->InDeCompressedBuffer.WriteBuffer((LPBYTE)"", 1); 
	CString strResult = (char*)m_ContextObject->InDeCompressedBuffer.GetBuffer(0);
	strResult.Replace("\n", "\r\n");
	int	iLength = m_Edit.GetWindowTextLength();
	m_Edit.SetSel(iLength, iLength);
	m_Edit.ReplaceSel(strResult);   
	m_nCurSel = m_Edit.GetWindowTextLength();
}

void CShellDlg::OnClose()
{
#if CLOSE_DELETE_DLG
	m_ContextObject->v1 = 0;
#endif
	CancelIo((HANDLE)m_ContextObject->sClientSocket);
	closesocket(m_ContextObject->sClientSocket);

	CDialog::OnClose();
#if CLOSE_DELETE_DLG
	delete this;
#endif
}


BOOL CShellDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_DELETE)
			return true;
		if (pMsg->wParam == VK_RETURN && pMsg->hwnd == m_Edit.m_hWnd)
		{
			//得到窗口的数据大小
			int	iLength = m_Edit.GetWindowTextLength();
			CString str;
			//得到窗口的字符数据
			m_Edit.GetWindowText(str);
			//加入换行符
			str += "\r\n";
			LPBYTE pSrc = (LPBYTE)str.GetBuffer(0) + m_nCurSel;
#ifdef _DEBUG
			OutputDebugStringA("[Shell]=> ");
			OutputDebugStringA((char*)pSrc);
#endif
			int length = str.GetLength() - m_nCurSel;
			m_iocpServer->OnClientPreSending(m_ContextObject, pSrc, length);
			m_nCurSel = m_Edit.GetWindowTextLength();
			if (0 == strcmp((char*)pSrc, "exit\r\n"))
			{
				ShowWindow(SW_HIDE);
			}
		}
		if (pMsg->wParam == VK_BACK && pMsg->hwnd == m_Edit.m_hWnd)
		{
			if (m_Edit.GetWindowTextLength() <= m_nReceiveLength)  
				return true;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


HBRUSH CShellDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if ((pWnd->GetDlgCtrlID() == IDC_EDIT) && (nCtlColor == CTLCOLOR_EDIT))
	{
		COLORREF clr = RGB(255, 255, 255);
		pDC->SetTextColor(clr);   //设置白色的文本
		clr = RGB(0,0,0);
		pDC->SetBkColor(clr);     //设置黑色的背景
		return CreateSolidBrush(clr);  //作为约定，返回背景色对应的刷子句柄
	}
	else
	{
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	return hbr;
}
