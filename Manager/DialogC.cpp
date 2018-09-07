// DialogC.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "DialogC.h"
#include "afxdialogex.h"

CListCtrl  CDialogC::WIndowsList = {};
static int index = 0;
// DialogC 对话框

IMPLEMENT_DYNAMIC(CDialogC, CDialogEx)

CDialogC::CDialogC(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WINDOWSDIALOG, pParent)
{

}

CDialogC::~CDialogC()
{
}

void CDialogC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WindowsLIST, WIndowsList);
}



BEGIN_MESSAGE_MAP(CDialogC, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CDialogC::OnBnClickedCancel)
	ON_BN_CLICKED(IDFlushWnd, &CDialogC::OnBnClickedFlushwnd)
END_MESSAGE_MAP()


// DialogC 消息处理程序

BOOL CDialogC::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	TCHAR buff[200];
	::GetWindowText(hwnd, buff, 200);

	if (::IsWindowVisible(hwnd) == TRUE && wcslen(buff) != 0) {
		WIndowsList.InsertItem(index, buff);
		index++;
	}
	return 1;
}


BOOL CDialogC::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	WIndowsList.InsertColumn(0, L"窗口", 0, 600);
	
	WIndowsList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	EnumWindows(&EnumWindowsProc, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogC::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}



void CDialogC::OnBnClickedFlushwnd()
{
	// TODO: 在此添加控件通知处理程序代码
	WIndowsList.DeleteAllItems();
	EnumWindows(&EnumWindowsProc, NULL);
}
