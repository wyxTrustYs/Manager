#pragma once
#include "afxcmn.h"


// ModuleDialog 对话框

class ModuleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ModuleDialog)

public:
	ModuleDialog(int Pid,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModuleDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Module };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ListModule;
	int nPID;
	virtual BOOL OnInitDialog();
};
