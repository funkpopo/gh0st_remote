// SettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RemoteTool.h"
#include "SettingDlg.h"
#include "afxdialogex.h"
// CSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialog)

CSettingDlg::CSettingDlg(CWnd* pParent)
	: CDialog(CSettingDlg::IDD, pParent)
	, m_nListenPort(0)
	, m_nMax_Connect(0)
{
}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nListenPort);
	DDX_Text(pDX, IDC_EDIT_MAX, m_nMax_Connect);
	DDX_Control(pDX, IDC_BUTTON_SETTINGAPPLY, m_ApplyButton);
}

BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SETTINGAPPLY, &CSettingDlg::OnBnClickedButtonSettingapply)
	ON_EN_CHANGE(IDC_EDIT_PORT, &CSettingDlg::OnEnChangeEditPort)
	ON_EN_CHANGE(IDC_EDIT_MAX, &CSettingDlg::OnEnChangeEditMax)
END_MESSAGE_MAP()

// CSettingDlg 消息处理程序

BOOL CSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	int nPort = ((CMyRemoteApp*)AfxGetApp())->m_iniFile.GetInt("settings", "ghost");         
	//读取ini 文件中的监听端口
	int nMaxConnection = ((CMyRemoteApp*)AfxGetApp())->m_iniFile.GetInt("settings", "MaxConnection");    

	m_nListenPort = (nPort<=0 || nPort>65535) ? 6543 : nPort;
	m_nMax_Connect  = nMaxConnection<=0 ? 10000 : nMaxConnection;

	UpdateData(FALSE);

	return TRUE; 
}


void CSettingDlg::OnBnClickedButtonSettingapply()
{
	UpdateData(TRUE);
	((CMyRemoteApp *)AfxGetApp())->m_iniFile.SetInt("settings", "ghost", m_nListenPort);      
	//向ini文件中写入值
	((CMyRemoteApp *)AfxGetApp())->m_iniFile.SetInt("settings", "MaxConnection", m_nMax_Connect);

	m_ApplyButton.EnableWindow(FALSE);
	m_ApplyButton.ShowWindow(SW_HIDE);
}


void CSettingDlg::OnEnChangeEditPort()
{
	// Button添加变量
	m_ApplyButton.ShowWindow(SW_NORMAL);
	m_ApplyButton.EnableWindow(TRUE);
}

void CSettingDlg::OnEnChangeEditMax()
{
	HWND hApplyButton = ::GetDlgItem(m_hWnd,IDC_BUTTON_SETTINGAPPLY);

	::ShowWindow(hApplyButton,SW_NORMAL);
	::EnableWindow(hApplyButton,TRUE);
}


void CSettingDlg::OnOK()
{
	OnBnClickedButtonSettingapply();

	CDialog::OnOK();
}
