// DialogA.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "DialogA.h"
#include "afxdialogex.h"
#include "DialogSubThread.h"
#include "DialogHeap.h"
#include "ModuleDialog.h"
#include <TlHelp32.h>


// CDialogA 对话框

IMPLEMENT_DYNAMIC(CDialogA, CDialogEx)

CDialogA::CDialogA(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGA, pParent)
{

}

CDialogA::~CDialogA()
{
}

void CDialogA::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST2, m_ListCtrl);
	DDX_Control(pDX, IDC_LIST2, m_ListCtrlA);

	DDX_Control(pDX, FlushProcess, Flush);
}


BEGIN_MESSAGE_MAP(CDialogA, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &CDialogA::OnRclickList2)
	ON_COMMAND(ID_32781, &CDialogA::On32781)
//	ON_BN_CLICKED(IDC_BUTTON2, &CDialogA::OnBnClickedButton2)
	ON_COMMAND(ID_32782, &CDialogA::On32782)
	ON_BN_CLICKED(FlushProcess, &CDialogA::OnBnClickedFlushprocess)
	ON_COMMAND(ID_32786, &CDialogA::On32786)
	ON_COMMAND(ID_32787, &CDialogA::On32787)
END_MESSAGE_MAP()


// CDialogA 消息处理程序


BOOL CDialogA::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化

	m_ListCtrlA.InsertColumn(0, L"进程名", 0, 200);
	m_ListCtrlA.InsertColumn(1, L"pID", 0, 70);
	m_ListCtrlA.InsertColumn(2, L"优先级", 0, 70);
	m_ListCtrlA.InsertColumn(3, L"线程数", 0, 70);
	
	m_ListCtrlA.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	PROCESSENTRY32 pe = { sizeof(PROCESSENTRY32) };
	//1 创建一个快照
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	//2 找到第一个进程的信息
	if (Process32First(hSnap, &pe) == TRUE)
	{
		int index = 0;
	
		//3 循环遍历其他进程的信息
		do
		{
			TCHAR temp[20] = { 0 };
			
			m_ListCtrlA.InsertItem(index, pe.szExeFile);
			_stprintf_s(temp, 20, L"%d", pe.th32ProcessID);
			m_ListCtrlA.SetItemText(index, 1, temp);

			_stprintf_s(temp, 20, L"%d", pe.pcPriClassBase);
			m_ListCtrlA.SetItemText(index, 2, temp);
			_stprintf_s(temp, 20, L"%d", pe.cntThreads);
			m_ListCtrlA.SetItemText(index, 3, temp);
			++index;
		} while (Process32Next(hSnap, &pe));
	}
//	EnumWindows(&EnumWindowProc, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogA::OnRclickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CMenu menu, *pmenu;
	int i = m_ListCtrlA.GetSelectionMark();
	menu.LoadMenu(IDR_MENU1);
	pmenu = menu.GetSubMenu(0);
	//定义一个用于确定光标位置的位置 
	CPoint point1;
	//获取当前光标的位置，以便使得菜单可以跟随光标
	GetCursorPos(&point1);
	//在指定位置显示弹出菜单
	pmenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point1.x, point1.y, this);
	*pResult = 0;
	//ListId = m_ListCtrlA.Get
}


void CDialogA::On32781()
{
	// TODO: 在此添加命令处理程序代码
	int i = m_ListCtrlA.GetSelectionMark();
	int PID = _tstoi(m_ListCtrlA.GetItemText(i, 1));
	HANDLE hProcess = OpenProcess(
		PROCESS_ALL_ACCESS,  //要申请的一个权限
		FALSE,               //句柄是否可继承
		PID                 //进程ID
	);
	//2 结束进程
	TerminateProcess(hProcess, 0);

}



void CDialogA::OnBnClickedFlushprocess()
{
	m_ListCtrlA.DeleteAllItems();
	PROCESSENTRY32 pe = { sizeof(PROCESSENTRY32) };
	//1 创建一个快照
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	//2 找到第一个进程的信息
	if (Process32First(hSnap, &pe) == TRUE)
	{
		int index = 0;

		//3 循环遍历其他进程的信息
		do
		{
			TCHAR temp[20] = { 0 };

			m_ListCtrlA.InsertItem(index, pe.szExeFile);
			_stprintf_s(temp, 20, L"%d", pe.th32ProcessID);
			m_ListCtrlA.SetItemText(index, 1, temp);

			_stprintf_s(temp, 20, L"%d", pe.pcPriClassBase);
			m_ListCtrlA.SetItemText(index, 2, temp);
			_stprintf_s(temp, 20, L"%d", pe.cntThreads);
			m_ListCtrlA.SetItemText(index, 3, temp);
			++index;
		} while (Process32Next(hSnap, &pe));
	}
}


void CDialogA::On32782()
{
	// TODO: 在此添加命令处理程序代码
	int i = m_ListCtrlA.GetSelectionMark();
	int PID = _tstoi(m_ListCtrlA.GetItemText(i, 1));
	DialogSubThread* newDialog = new DialogSubThread(PID);
	newDialog->DoModal();
	delete newDialog;
}




void CDialogA::On32786()
{
	// TODO: 在此添加命令处理程序代码
	
	int i = m_ListCtrlA.GetSelectionMark();
	int PID = _tstoi(m_ListCtrlA.GetItemText(i, 1));
	ModuleDialog* md = new ModuleDialog(PID);
	md->DoModal();
	delete md;
}

//获取堆信息
void CDialogA::On32787()
{
	// TODO: 在此添加命令处理程序代码
	int i = m_ListCtrlA.GetSelectionMark();
	int PID = _tstoi(m_ListCtrlA.GetItemText(i, 1));
	CDialogHeap* heap = new CDialogHeap(PID);
	
	heap->DoModal();
	delete heap;
}
