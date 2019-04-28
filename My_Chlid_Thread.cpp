// My_Chlid_Thread.cpp : 实现文件
//

#include "stdafx.h"
#include "My_Chlid_Thread.h"
#include "afxdialogex.h"
#include <TlHelp32.h>

DWORD My_Chlid_Thread::m_id = 0;

// My_Chlid_Thread 对话框

IMPLEMENT_DYNAMIC(My_Chlid_Thread, CDialogEx)

My_Chlid_Thread::My_Chlid_Thread(CWnd* pParent /*=NULL*/)
	: CDialogEx(My_Chlid_Thread::IDD, pParent)
{

}

My_Chlid_Thread::~My_Chlid_Thread()
{
}

void My_Chlid_Thread::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, My_ListCtrl);
}

BEGIN_MESSAGE_MAP(My_Chlid_Thread, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &My_Chlid_Thread::OnLvnItemchangedList2)
END_MESSAGE_MAP()

// My_Chlid_Thread 消息处理程序


void My_Chlid_Thread::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
}

BOOL My_Chlid_Thread::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	/*--------------------------------------------------*/
	// 获取List风格
	DWORD dwOldStyle = My_ListCtrl.GetExtendedStyle();
	My_ListCtrl.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	// 初始化ListCotrol
	CRect rc;
	My_ListCtrl.GetClientRect(rc);
	int nWidth = rc.Width();
	My_ListCtrl.InsertColumn(0, L"Thread ID", 0, nWidth / 3);
	My_ListCtrl.InsertColumn(1, L"Thread priority", 0, nWidth / 3);
	My_ListCtrl.InsertColumn(2, L"Process ID", 0, nWidth / 3);
	// 添加列表信息
	ListProcessThreads(m_id);
	/*--------------------------------------------------*/
	return TRUE;  
}

VOID My_Chlid_Thread::ListProcessThreads(DWORD dwPID)
{
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32;
	TCHAR buf[MAX_PATH] = { 0 };
	// 创建快照
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return;
	// 设置输入参数，结构体大小
	te32.dwSize = sizeof(THREADENTRY32);
	// 开始获取信息
	if (!Thread32First(hThreadSnap, &te32))
	{
		// 关闭句柄
		CloseHandle(hThreadSnap);
		return;
	}
	int i = 0;
	do{
		if (te32.th32OwnerProcessID == dwPID)
		{
			_stprintf_s(buf, MAX_PATH, TEXT("%d"), te32.th32ThreadID);
			My_ListCtrl.InsertItem(i, buf);
			buf[0] = 0;
			if (te32.tpBasePri <= 5)
				My_ListCtrl.SetItemText(i, 1, L"idle(最低)");
			else if (te32.tpBasePri <= 10)
				My_ListCtrl.SetItemText(i, 1, L"below normal(低于标准)");
			else if (te32.tpBasePri <= 15)
				My_ListCtrl.SetItemText(i, 1, L"normal(标准)");
			else if (te32.tpBasePri <= 25)
				My_ListCtrl.SetItemText(i, 1, L"above normal(高于标准)");
			else if (te32.tpBasePri <= 30)
				My_ListCtrl.SetItemText(i, 1, L"high(高)");
			else if (te32.tpBasePri == 31)
				My_ListCtrl.SetItemText(i, 1, L"real-time(实时)");
			buf[0] = 0;
			_stprintf_s(buf, MAX_PATH, L"%d", te32.th32OwnerProcessID);
			My_ListCtrl.SetItemText(i, 2, buf);
			++i;
		}
	} while (Thread32Next(hThreadSnap, &te32));
	CloseHandle(hThreadSnap);
}
