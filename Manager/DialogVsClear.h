#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <vector>


// CDialogVsClear 对话框

class CDialogVsClear : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogVsClear)

public:
	CDialogVsClear(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogVsClear();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VSCLEAR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void FindFile(CString Path);
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl CListPath;
	CListCtrl CWaitDel;
	CListCtrl CDel;
	std::vector<CString> PathStrings;// 保存路径的容器
	LARGE_INTEGER CountSize;	// 文件总大小
	LARGE_INTEGER DestSize;		// 可删除文件的大小
	std::vector<CString> DelStrings;	// 要删除的文件
	CString ExtendString;
	INT FileCount, DestCount;	// 总文件数量和可删文件数量
	INT DeleteCount;			// 已删除的文件个数
	virtual BOOL OnInitDialog();
//	afx_msg HCURSOR OnQueryDragIcon();
//	afx_msg void OnPaint();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedCheck();
};
