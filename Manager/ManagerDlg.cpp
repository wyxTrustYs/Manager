
// ManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "ManagerDlg.h"
#include "afxdialogex.h"
#include "DialogA.h"
#include "DialogB.h"
#include "DialogC.h"
#include "DialogVsClear.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// DWORD WINAPI CPUThreadProc(LPVOID lpThreadParameter) {
// 	WaitForSingleObject(lpThreadParameter, 3000);
// 	return 0;
// }
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnPaint();
//	afx_msg HCURSOR OnQueryDragIcon();
//	afx_msg void OnDropFiles(HDROP hDropInfo);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_PAINT()
//	ON_WM_QUERYDRAGICON()
//	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CManagerDlg 对话框



CManagerDlg::CManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MANAGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);

}

BEGIN_MESSAGE_MAP(CManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_WM_TIMER()
END_MESSAGE_MAP()

double FILETIME2Double(const _FILETIME& filetime) {
	return double(filetime.dwHighDateTime*4.294967296e9) + double(filetime.dwLowDateTime);
}

int GetCpuUsage() {
	_FILETIME idleTime, kernelTime, userTime;
	GetSystemTimes(&idleTime, &kernelTime, &userTime);
	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	WaitForSingleObject(hEvent, 100);
	//CreateThread(NULL, NULL, CPUThreadProc, hEvent, NULL, NULL);
	_FILETIME newIdleTime, newkernelTime, newuserTime;
	GetSystemTimes(&newIdleTime, &newkernelTime, &newuserTime);
	double dOldIdleTime = FILETIME2Double(idleTime);
	double dNewIdleTime = FILETIME2Double(newIdleTime);
	double dOldKernelTime = FILETIME2Double(kernelTime);
	double dNewKernelTime = FILETIME2Double(newkernelTime);
	double dOldUsertime = FILETIME2Double(userTime);
	double dNewUserTime = FILETIME2Double(newuserTime);
	return int(100.0 - (dNewIdleTime - dOldIdleTime) / (dNewKernelTime - dOldKernelTime + dNewUserTime - dOldUsertime)*100.0);
}

// CManagerDlg 消息处理程序

BOOL CManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetTimer(1, 5000, NULL);

	CDialogEx* m_Dlg[4];
	m_Dlg[0] = new CDialogA();
	m_Dlg[1] = new CDialogB();
	m_Dlg[2] = new CDialogC();
	m_Dlg[3] = new CDialogVsClear();
	m_TabCtrl.InsertTab(4,L"进程信息",L"线程信息",L"窗口信息",L"VS清理工具");
	m_TabCtrl.AddDig(4, IDD_DIALOGA, m_Dlg[0], IDD_DIALOGB, m_Dlg[1], IDD_WINDOWSDIALOG,m_Dlg[2], IDD_VSCLEAR,m_Dlg[3]);
	m_TabCtrl.SetSelAndShow(0);

	UINT buf[3] = { 1, 2, 3 };
	m_status.Create(this);
	m_status.SetIndicators(buf, 3);
	m_status.SetPaneInfo(0, 1, 0, 100);
	m_status.SetPaneInfo(1, 2, 0, 100);
	m_status.SetPaneInfo(2, 3, 0, 100);
	MEMORYSTATUS memStatus;
	GlobalMemoryStatus(&memStatus);
	DWORD occupancy_rate;
	occupancy_rate = memStatus.dwMemoryLoad;
	TCHAR MeBuff[100] = { 0 };
	TCHAR CpuTime[100] = { 0 };
	
	_stprintf_s(MeBuff, 100, L"内存使用率：%d", occupancy_rate);
	m_status.SetPaneText(0, MeBuff);
//	m_status.SetPaneText(1, L"你好");
	
	_stprintf_s(CpuTime, 100, L"CPU使用率：%d", GetCpuUsage());
	m_status.SetPaneText(2, CpuTime);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CManagerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MEMORYSTATUS memStatus;
	GlobalMemoryStatus(&memStatus);
	DWORD occupancy_rate;
	occupancy_rate = memStatus.dwMemoryLoad;
	TCHAR MeBuff[100] = { 0 };
	TCHAR CpuTime[100] = { 0 };

	_stprintf_s(MeBuff, 100, L"内存使用率：%d", occupancy_rate);
	m_status.SetPaneText(0, MeBuff);
	//	m_status.SetPaneText(1, L"你好");

	_stprintf_s(CpuTime, 100, L"CPU使用率：%d", GetCpuUsage());
	m_status.SetPaneText(2, CpuTime);
	CDialogEx::OnTimer(nIDEvent);
}


//void CAboutDlg::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//					   // TODO: 在此处添加消息处理程序代码
//					   // 不为绘图消息调用 CDialogEx::OnPaint()
//}


//HCURSOR CAboutDlg::OnQueryDragIcon()
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	return CDialogEx::OnQueryDragIcon();
//}


//void CAboutDlg::OnDropFiles(HDROP hDropInfo)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnDropFiles(hDropInfo);
//}
