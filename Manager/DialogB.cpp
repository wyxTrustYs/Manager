// DialogB.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "DialogB.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CDialogB 对话框

IMPLEMENT_DYNAMIC(CDialogB, CDialogEx)

CDialogB::CDialogB(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGB, pParent)
{

}

CDialogB::~CDialogB()
{
}

void CDialogB::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrlB);

	DDX_Control(pDX, IDC_FlushThread, m_FlushThrea);
}


BEGIN_MESSAGE_MAP(CDialogB, CDialogEx)
	
	ON_BN_CLICKED(IDC_FlushThread, &CDialogB::OnBnClickedFlushthread)
	ON_COMMAND(ID_32783, &CDialogB::On32783)
	ON_COMMAND(ID_32784, &CDialogB::On32784)
	ON_COMMAND(ID_32785, &CDialogB::On32785)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CDialogB::OnRclickList1)
END_MESSAGE_MAP()


// CDialogB 消息处理程序



void CDialogB::OnBnClickedFlushthread()
{

	// TODO: 在此添加控件通知处理程序代码
	m_ListCtrlB.DeleteAllItems();
	HANDLE hThread = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32;
	// 创建快照 ，创建的是当前操作系统中所有线程的快照
	hThread =
		CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	// 设置输入参数，结构的大小
	te32.dwSize = sizeof(THREADENTRY32);
	// 开始获取信息
	if (Thread32First(hThread, &te32) == TRUE)
	{
		int index = 0;

		//3 循环遍历其他线程的信息
		do
		{
			TCHAR temp[20] = { 0 };
			_stprintf_s(temp, 20, L"%d", te32.th32OwnerProcessID);
			m_ListCtrlB.InsertItem(index, temp);

			_stprintf_s(temp, 20, L"%d", te32.th32ThreadID);
			m_ListCtrlB.SetItemText(index, 1, temp);
			_stprintf_s(temp, 20, L"%d", te32.tpBasePri);
			m_ListCtrlB.SetItemText(index, 2, temp);
			++index;
		} while (Thread32Next(hThread, &te32));
	}
	
}


BOOL CDialogB::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ListCtrlB.InsertColumn(0, L"所属进程", 0, 200);
	m_ListCtrlB.InsertColumn(1, L"threadID", 0, 70);
	m_ListCtrlB.InsertColumn(2, L"优先级", 0, 70);


	m_ListCtrlB.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	HANDLE hThread = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32;
	// 创建快照 ，创建的是当前操作系统中所有线程的快照
	hThread =
		CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	// 设置输入参数，结构的大小
	te32.dwSize = sizeof(THREADENTRY32);
	// 开始获取信息
	if (Thread32First(hThread, &te32) == TRUE)
	{
		int index = 0;

		//3 循环遍历其他线程的信息
		do
		{
			TCHAR temp[20] = { 0 };
			_stprintf_s(temp, 20, L"%d", te32.th32OwnerProcessID);
			m_ListCtrlB.InsertItem(index, temp);

			_stprintf_s(temp, 20, L"%d", te32.th32ThreadID);
			m_ListCtrlB.SetItemText(index, 1, temp);
			_stprintf_s(temp, 20, L"%d", te32.tpBasePri);
			m_ListCtrlB.SetItemText(index, 2, temp);
			++index;
		} while (Thread32Next(hThread, &te32));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogB::On32783()
{
	// TODO: 在此添加命令处理程序代码
	int i = m_ListCtrlB.GetSelectionMark();
	int PID = _tstoi(m_ListCtrlB.GetItemText(i, 1));
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, PID);
	SuspendThread(hThread);
	CloseHandle(hThread);
}


void CDialogB::On32784()
{
	// TODO: 在此添加命令处理程序代码
	int i = m_ListCtrlB.GetSelectionMark();
	int PID = _tstoi(m_ListCtrlB.GetItemText(i, 1));
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, PID);
	ResumeThread(hThread);
	CloseHandle(hThread);
}


void CDialogB::On32785()
{
	// TODO: 在此添加命令处理程序代码
	int i = m_ListCtrlB.GetSelectionMark();
	int PID = _tstoi(m_ListCtrlB.GetItemText(i, 1));
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, PID);
	TerminateThread(hThread,-1);
	CloseHandle(hThread);
}


void CDialogB::OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CMenu menu, *pmenu;
	
	menu.LoadMenu(IDR_MENU2);
	pmenu = menu.GetSubMenu(0);
	//定义一个用于确定光标位置的位置 
	CPoint point1;
	//获取当前光标的位置，以便使得菜单可以跟随光标
	GetCursorPos(&point1);
	//在指定位置显示弹出菜单
	pmenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point1.x, point1.y, this);
	*pResult = 0;
}
