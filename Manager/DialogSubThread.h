#pragma once
#include "afxcmn.h"


// DialogSubThread 对话框

class DialogSubThread : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSubThread)

public:
	DialogSubThread(int PID,CWnd* pParent = NULL);   // 标准构造函数
	
	virtual ~DialogSubThread();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SubThread };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl SubThreadList;
	int mPID;
	virtual BOOL OnInitDialog();
};
