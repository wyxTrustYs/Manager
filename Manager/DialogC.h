#pragma once
#include "afxcmn.h"


// DialogC 对话框

class CDialogC : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogC)

public:
	CDialogC(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogC();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINDOWSDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	static BOOL CALLBACK EnumWindowsProc(
		_In_ HWND hwnd,
		_In_ LPARAM lParam
	);

	DECLARE_MESSAGE_MAP()
public:
	static CListCtrl WIndowsList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedFlushwnd();
};
