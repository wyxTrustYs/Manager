#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDialogB 对话框

class CDialogB : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogB)

public:
	CDialogB(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogB();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrlB;
	CButton m_FlushThrea;
	afx_msg void OnBnClickedFlushthread();
	virtual BOOL OnInitDialog();
	afx_msg void On32783();
	afx_msg void On32784();
	afx_msg void On32785();
	afx_msg void OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
