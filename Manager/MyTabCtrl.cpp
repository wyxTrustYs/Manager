// MyTabCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "MyTabCtrl.h"


// CMyTabCtrl

IMPLEMENT_DYNAMIC(CMyTabCtrl, CTabCtrl)

CMyTabCtrl::CMyTabCtrl()
{

}

CMyTabCtrl::~CMyTabCtrl()
{
}

void CMyTabCtrl::InsertTab(DWORD dwCount,...)
{
	va_list argptr;
	va_start(argptr, dwCount);
	for (DWORD i = 0; i < dwCount; i++) {
		TCHAR* pStrTabName = va_arg(argptr, TCHAR*);
		InsertItem(i, pStrTabName);
	}
	va_end(argptr);
	m_dwCount = dwCount;

}

void CMyTabCtrl::AddDig(DWORD dwCount, ...)
{
	va_list argptr;
	va_start(argptr, dwCount);
	for (DWORD i = 0; i < dwCount; i++) {
		UINT uId = va_arg(argptr, UINT);
		m_pDlg[i] = va_arg(argptr, CDialogEx*);
		m_pDlg[i]->Create(uId, this);
	}
	va_end(argptr);
}

void CMyTabCtrl::SetSelAndShow(int Sel)
{
	CRect rect;
	GetClientRect(rect);
	rect.DeflateRect(1, 22, 3, 3);
	this->SetCurSel(Sel);
	m_pDlg[Sel]->ShowWindow(SW_SHOW);
	m_pDlg[Sel]->MoveWindow(rect);
}


BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CMyTabCtrl::OnTcnSelchange)
END_MESSAGE_MAP()



// CMyTabCtrl 消息处理程序




void CMyTabCtrl::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CRect rect;
	GetClientRect(rect);
	rect.DeflateRect(1, 22, 3, 3);
	DWORD dwSel = this->GetCurSel();
	for (DWORD i = 0; i < m_dwCount; i++) {
		if (dwSel == i) {
			m_pDlg[i]->ShowWindow(SW_SHOW);
			m_pDlg[i]->MoveWindow(rect);
		}
		else
		{
			m_pDlg[i]->ShowWindow(SW_HIDE);
		}
	}
	*pResult = 0;
}
