#pragma once
#include "IOCPServer.h"
#include "afxwin.h"

// CTalkDlg �Ի���

class CTalkDlg : public CDialog
{
	DECLARE_DYNAMIC(CTalkDlg)

public:
	CTalkDlg(CWnd* Parent, IOCPServer* IOCPServer=NULL, CONTEXT_OBJECT *ContextObject=NULL);   // ��׼���캯��
	virtual ~CTalkDlg();

	// �Ի�������
	enum { IDD = IDD_DIALOG_TALK };
	CONTEXT_OBJECT* m_ContextObject;
	IOCPServer*     m_iocpServer;
	HICON m_hIcon;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditTalk;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonTalk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
};