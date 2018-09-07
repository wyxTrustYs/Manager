#pragma once


// CMyTabCtrl

class CMyTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTabCtrl)

public:
	CMyTabCtrl();
	virtual ~CMyTabCtrl();
	void InsertTab(DWORD dwCount,...);		//插入选项卡
	void AddDig(DWORD dwCount, ...);			//增加对话框
	void SetSelAndShow(int Sel);	//设置当前选中的对话框并显示
	CDialogEx* m_pDlg[20];	//选项卡中存储的对话框数组
	DWORD m_dwCount;		//当前选项卡对话框消息
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


