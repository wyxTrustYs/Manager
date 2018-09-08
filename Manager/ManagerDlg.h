
// ManagerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "MyTabCtrl.h"
#include "afxwin.h"


// CManagerDlg 对话框
class CManagerDlg : public CDialogEx
{
// 构造
public:
	CManagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANAGER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CStatusBar m_status;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CTabCtrl m_TabCtrl;
	CMyTabCtrl m_TabCtrl;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
