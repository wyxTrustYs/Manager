// DialogHeap.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "DialogHeap.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CDialogHeap 对话框

IMPLEMENT_DYNAMIC(CDialogHeap, CDialogEx)

CDialogHeap::CDialogHeap(int PID, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGHEAP, pParent)
{
	this->nPID = (DWORD)PID;
}

CDialogHeap::~CDialogHeap()
{
}

void CDialogHeap::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTHEAP, CListHeap);
}


BEGIN_MESSAGE_MAP(CDialogHeap, CDialogEx)
END_MESSAGE_MAP()


// CDialogHeap 消息处理程序


BOOL CDialogHeap::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CListHeap.InsertColumn(0, L"堆ID", 0, 300);
	CListHeap.InsertColumn(1, L"所占空间", 0, 300);
	CListHeap.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	HEAPLIST32 hl;
	TCHAR buff[100] = { 0 };
	TCHAR SHeapID[20] = { 0 };
	TCHAR HeapSpace[20] = { 0 };
	//	DWORD tmpid = GetCurrentProcessId();
	HANDLE hHeapSnap = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, nPID);

	hl.dwSize = sizeof(HEAPLIST32);

	if (hHeapSnap == INVALID_HANDLE_VALUE)
	{
		//_stprintf_s(buff, 200, L"CreateToolhelp32Snapshot failed (%d)", GetLastError());
		MessageBox(L"CreateToolhelp32Snapshot failed", 0, 0);
		EndDialog(0);
		return FALSE;
	}

	if (Heap32ListFirst(hHeapSnap, &hl))
	{
		int index = 0;
		do
		{
			HEAPENTRY32 he;
			ZeroMemory(&he, sizeof(HEAPENTRY32));
			he.dwSize = sizeof(HEAPENTRY32);

			if (Heap32First(&he, nPID, hl.th32HeapID))
			{
// 				do
// 				{
					_stprintf_s(SHeapID, 20, L"%d", hl.th32HeapID);
					CListHeap.InsertItem(index, SHeapID);
					_stprintf_s(HeapSpace, 20, L"%d KB", he.dwBlockSize);
					CListHeap.SetItemText(index, 1, HeapSpace);
					he.dwSize = sizeof(HEAPENTRY32);
				/*} while (Heap32Next(&he));*/
			}
			hl.dwSize = sizeof(HEAPLIST32);
		} while (Heap32ListNext(hHeapSnap, &hl));
	}
	else
	{
		printf((char*)buff, "Cannot list first heap (%d)", GetLastError());
		MessageBox(buff, L"ERROR", 0);
	}

	CloseHandle(hHeapSnap);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
