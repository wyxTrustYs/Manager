// ModuleDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "ModuleDialog.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// ModuleDialog 对话框

IMPLEMENT_DYNAMIC(ModuleDialog, CDialogEx)

ModuleDialog::ModuleDialog(int Pid,CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Module, pParent)
{
	this->nPID = Pid;
}

ModuleDialog::~ModuleDialog()
{
}

void ModuleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTModle, ListModule);
}


BEGIN_MESSAGE_MAP(ModuleDialog, CDialogEx)
END_MESSAGE_MAP()


// ModuleDialog 消息处理程序


BOOL ModuleDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ListModule.InsertColumn(0, L"所属进程", 0, 200);
	ListModule.InsertColumn(1, L"所用模块", 0, 300);

	ListModule.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32 = { sizeof(MODULEENTRY32) };
	// 1. 创建一个模块相关的快照句柄
	hModuleSnap = CreateToolhelp32Snapshot(
		TH32CS_SNAPMODULE,  // 指定快照的类型
		nPID);            // 指定进程
	if (hModuleSnap == INVALID_HANDLE_VALUE)
		return false;
	// 2. 通过模块快照句柄获取第一个模块信息
	if (!Module32First(hModuleSnap, &me32)) {
		CloseHandle(hModuleSnap);
		return false;
	}
	// 3. 循环获取模块信息
	int index = 0;

	//3 循环遍历其他模块的信息
	do
	{
		TCHAR temp[20] = { 0 };

		_stprintf_s(temp, 20, L"%d", me32.th32ProcessID);
		ListModule.InsertItem(index, temp);

		//_stprintf_s(temp, 20, L"%d", me32.szExePath);
		ListModule.SetItemText(index, 1, me32.szExePath);
		
		++index;
	} while (Module32Next(hModuleSnap, &me32));
	// 4. 关闭句柄并退出函数
	CloseHandle(hModuleSnap);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
