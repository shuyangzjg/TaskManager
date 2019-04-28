// MyDialogEx.cpp : 实现文件
//

#include "stdafx.h"
#include "MyDialogEx.h"
#include "afxdialogex.h"
#include "resource.h"
#include <TlHelp32.h>

// MyDialogEx 对话框

IMPLEMENT_DYNAMIC(MyDialogEx, CDialogEx)

MyDialogEx::MyDialogEx(CWnd* pParent /*=NULL*/)
	: CDialogEx(MyDialogEx::IDD, pParent)
{

}

MyDialogEx::~MyDialogEx()
{
}

void MyDialogEx::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_Static);
	DDX_Control(pDX, IDC_LIST1, m_ListONject);
}

BEGIN_MESSAGE_MAP(MyDialogEx, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &MyDialogEx::OnBnClickedButton2)
	ON_STN_CLICKED(IDC_STATIC1, &MyDialogEx::OnStnClickedStatic1)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &MyDialogEx::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON3, &MyDialogEx::OnBnClickedButton3)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &MyDialogEx::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// MyDialogEx 消息处理程序

BOOL MyDialogEx::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/*------------------------------------------------*/
	// 图片插入
	CBitmap *p = new CBitmap;
	p->LoadBitmapW(IDB_BITMAP1);
	m_Static.SetBitmap((HBITMAP)p->m_hObject);
	/*------------------------------------------------*/

	/*------------------------------------------------*/
	// 获取List风格
	CRect rc;
	DWORD dwOldStyle = m_ListONject.GetExtendedStyle();
	m_ListONject.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	// 设置宽度
	m_ListONject.GetClientRect(rc);
	int nWidth = rc.Width();
	// 先行后列
	m_ListONject.InsertColumn(0, L"Thread Id", 0, nWidth / 2);
	m_ListONject.InsertColumn(1, L"Thread Name", 0, nWidth / 2);
	/*------------------------------------------------*/

	/*------------------------------------------------*/

	/*------------------------------------------------*/


	return TRUE;
}

void MyDialogEx::OnBnClickedButton2()
{
	this->FindAllProcess();
}

void MyDialogEx::OnStnClickedStatic1()
{
}
// 添加遍历进程信息
void MyDialogEx::FindAllProcess()
{
	PROCESSENTRY32 pe = { sizeof(PROCESSENTRY32) };
	// 创建一个快照
	int i = 0;
	TCHAR buf[MAX_PATH] = { 0 };
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (TRUE == Process32First(hSnap, &pe))
	{
		do
		{
			// 添加列ID
			_stprintf_s(buf, MAX_PATH, _T("%d"), pe.th32ProcessID);
			m_ListONject.InsertItem(i, buf);
			m_ListONject.SetItemText(i, 1, (LPCTSTR)pe.szExeFile);
			++i;
		} while (Process32Next(hSnap, &pe));
	}
}

void MyDialogEx::OnBnClickedButton3()
{
	/*	第一种：
		1、获取当前列表中勾选的哪一行，获取进程信息
		2、遍历改进程的线程信息
		3、弹出一个新的List窗口
	*/
	// 获取鼠标点击的哪一行
	int index = m_ListONject.GetSelectionMark();
	// 获取进程Id 赋值给弹出的DialogBox对象
	CString str = m_ListONject.GetItemText(index, 0);
	// str.Format(L"%d", str);
	// _ttoi()
	
	ThreadObject.m_id = _ttoi(str);  // 如何强转？
	//
	this->ThreadObject.DoModal();


	/*	第二种：
		1、双击进程
		2、弹出对话框，然后查看线程
	*/

	/*	第三种：
		1、右击进程（弹出菜单）
		2、菜单查看线程
		3、弹出当前线程资源信息
	*/
}

//void MyDialogEx::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO:  在此添加控件通知处理程序代码
//	*pResult = 0;
//	//str.Format(L"%c", str);
//	//// 赋值给Thread对象
//	//ThreadObject.m_id = str;
//}
