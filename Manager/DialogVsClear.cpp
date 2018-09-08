// DialogVsClear.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "DialogVsClear.h"
#include "afxdialogex.h"


// CDialogVsClear 对话框

IMPLEMENT_DYNAMIC(CDialogVsClear, CDialogEx)

CDialogVsClear::CDialogVsClear(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VSCLEAR, pParent), CountSize(), DestSize(), FileCount(0), DestCount(0), DeleteCount(0)
	, ExtendString(_T(".obj\\.tlog\\.lastbuildstate\\.idb\\.pdb\\.pch\\.res\\.ilk\\.exe\\.sdf\\.ipch\\.log\\.db\\.suo\\"))
{

}

CDialogVsClear::~CDialogVsClear()
{
}

void CDialogVsClear::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PATH, CListPath);

	DDX_Control(pDX, IDC_WAITDEL, CWaitDel);
	DDX_Control(pDX, IDC_DEL, CDel);

	DDX_Text(pDX, IDC_TYPE, ExtendString);
}




BEGIN_MESSAGE_MAP(CDialogVsClear, CDialogEx)
	//	ON_WM_QUERYDRAGICON()
	//	ON_WM_PAINT()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_DELETE, &CDialogVsClear::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_RESET, &CDialogVsClear::OnBnClickedReset)
	ON_BN_CLICKED(IDC_CHECK, &CDialogVsClear::OnBnClickedCheck)
END_MESSAGE_MAP()


// CDialogVsClear 消息处理程序


BOOL CDialogVsClear::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CListPath.InsertColumn(0, L"文件路径", 0, 400);
	CWaitDel.InsertColumn(0, L"待删除的文件列表", 0, 400);
	CDel.InsertColumn(0, L"已删除的文件列表", 0, 400);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}





void CDialogVsClear::OnDropFiles(HDROP hDropInfo)
{
	CDialogEx::OnDropFiles(hDropInfo);
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);

	// 2. 循环获取每一个文件
	for (int i = 0; i < DropCount; i++)
	{
		WCHAR wcStr[MAX_PATH];
		// 3. 获得拖曳的第i个文件的文件名  
		// DragQueryFile(hDropInfo, -1, NULL, 0);
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);

		// 4. 如果这是一个文件夹，则加入到列表中
		if (GetFileAttributes(wcStr) & FILE_ATTRIBUTE_DIRECTORY)
		{
			// 5. 如果该路径不存在于列表中
			if (find(PathStrings.begin(), PathStrings.end(), wcStr) == PathStrings.end())
			{
				// 6. 添加到保存路径的容器和列表中
				PathStrings.push_back(wcStr);
				CListPath.InsertItem(0, wcStr);
			}
		}
	}

	// 7.拖放结束后,释放内存  
	DragFinish(hDropInfo);

	CDialogEx::OnDropFiles(hDropInfo);
}




void CDialogVsClear::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	DeleteCount = 0;

	// 1. 遍历所有的要删除的文件路径
	for (auto File : DelStrings)
	{
		// 2. 判断是否删除成功
		if (DeleteFile(File))
		{
			++DeleteCount;
			CDel.InsertItem(0, File);
		}
	}

	// 3. 提示删除信息
	CString Msg;
	Msg.Format(L"需删除文件 %d 个\n已删除文件 %d 个",
		DestCount, DeleteCount);
	MessageBox(Msg);
}


void CDialogVsClear::OnBnClickedReset()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	MessageBox(L"文件名更新成功!");
}


void CDialogVsClear::OnBnClickedCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	// 0. 清空所有信息
	CWaitDel.DeleteAllItems();
	DelStrings.clear();
	FileCount = DestCount = 0;
	CountSize.QuadPart = DestSize.QuadPart = 0;

	// 1. 删除路径中的所有文件
	for (auto Path : PathStrings)
		FindFile(Path);

	// for
	// for each
	// for (auto xxx =xx.end)
	// for (auto a: xxx)

	// 2. 获取遍历到的大小信息
	CString Msg;
	Msg.Format(L"所有文件个数: %-3d 大小: %.2lfMB\n"
		"可删文件个数: %-3d 大小: %.2lfMB",
		FileCount, CountSize.QuadPart / 1024.0 / 1024.0,
		DestCount, DestSize.QuadPart / 1024.0 / 1024.0);

	// 3. 输出信息
	MessageBox(Msg);
}

void CDialogVsClear::FindFile(CString Path)
{
	// 1. 尝试查找第一个文件
	WIN32_FIND_DATA FileInfo = { 0 };
	HANDLE File = FindFirstFile(Path + "\\*", &FileInfo);

	// 2. 遍历文件夹的所有文件
	if (File != INVALID_HANDLE_VALUE)
	{
		do {
			// 3.1 如果是文件夹就递归
			if (FileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// 3.1.1 排除两个文件夹
				if (CString(".") != FileInfo.cFileName && CString("..") != FileInfo.cFileName)
					FindFile(Path + CString("\\") + FileInfo.cFileName);
			}
			// 3.2 如果是文件
			else
			{
				// 3.2.0 累加文件大小和个数
				++FileCount;
				CountSize.QuadPart += FileInfo.nFileSizeLow;

				// 3.2.1 判断后缀名
				if (-1 != ExtendString.Find(PathFindExtension(FileInfo.cFileName)))
				{
					++DestCount;
					DestSize.QuadPart += FileInfo.nFileSizeLow;
					CWaitDel.InsertItem(0, Path + CString("\\") + FileInfo.cFileName);
					DelStrings.push_back(Path + CString("\\") + FileInfo.cFileName);
				}
			}
		} while (FindNextFile(File, &FileInfo));
	}
}