// DialogSubThread.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "DialogSubThread.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// DialogSubThread 对话框

IMPLEMENT_DYNAMIC(DialogSubThread, CDialogEx)

DialogSubThread::DialogSubThread(int PID,CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SubThread, pParent)
{
	this->mPID = PID;
}

DialogSubThread::~DialogSubThread()
{
}

void DialogSubThread::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTSubThread, SubThreadList);
}

BEGIN_MESSAGE_MAP(DialogSubThread, CDialogEx)
END_MESSAGE_MAP()


// DialogSubThread 消息处理程序


BOOL DialogSubThread::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化

	SubThreadList.InsertColumn(0, L"所属进程", 0, 200);
	SubThreadList.InsertColumn(1, L"threadID", 0, 70);
	SubThreadList.InsertColumn(2, L"优先级", 0, 70);


	SubThreadList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);


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
			if (te32.th32OwnerProcessID != mPID)
				continue;
			TCHAR temp[20] = { 0 };
			
			_stprintf_s(temp, 20, L"%d", te32.th32OwnerProcessID);
			SubThreadList.InsertItem(index, temp);

			_stprintf_s(temp, 20, L"%d", te32.th32ThreadID);
			SubThreadList.SetItemText(index, 1, temp);
			_stprintf_s(temp, 20, L"%d", te32.tpBasePri);
			SubThreadList.SetItemText(index, 2, temp);
			++index;
		} while (Thread32Next(hThread, &te32));
	}



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
