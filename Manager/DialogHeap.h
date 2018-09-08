#pragma once
#include "afxcmn.h"


// CDialogHeap 对话框

class CDialogHeap : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogHeap)

public:
	CDialogHeap(int PID,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogHeap();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGHEAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl CListHeap;
	DWORD nPID;
	virtual BOOL OnInitDialog();
};
