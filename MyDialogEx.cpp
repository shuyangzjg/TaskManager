// MyDialogEx.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyDialogEx.h"
#include "afxdialogex.h"
#include "resource.h"
#include <TlHelp32.h>

// MyDialogEx �Ի���

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


// MyDialogEx ��Ϣ�������

BOOL MyDialogEx::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/*------------------------------------------------*/
	// ͼƬ����
	CBitmap *p = new CBitmap;
	p->LoadBitmapW(IDB_BITMAP1);
	m_Static.SetBitmap((HBITMAP)p->m_hObject);
	/*------------------------------------------------*/

	/*------------------------------------------------*/
	// ��ȡList���
	CRect rc;
	DWORD dwOldStyle = m_ListONject.GetExtendedStyle();
	m_ListONject.SetExtendedStyle(dwOldStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	// ���ÿ��
	m_ListONject.GetClientRect(rc);
	int nWidth = rc.Width();
	// ���к���
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
// ��ӱ���������Ϣ
void MyDialogEx::FindAllProcess()
{
	PROCESSENTRY32 pe = { sizeof(PROCESSENTRY32) };
	// ����һ������
	int i = 0;
	TCHAR buf[MAX_PATH] = { 0 };
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (TRUE == Process32First(hSnap, &pe))
	{
		do
		{
			// �����ID
			_stprintf_s(buf, MAX_PATH, _T("%d"), pe.th32ProcessID);
			m_ListONject.InsertItem(i, buf);
			m_ListONject.SetItemText(i, 1, (LPCTSTR)pe.szExeFile);
			++i;
		} while (Process32Next(hSnap, &pe));
	}
}

void MyDialogEx::OnBnClickedButton3()
{
	/*	��һ�֣�
		1����ȡ��ǰ�б��й�ѡ����һ�У���ȡ������Ϣ
		2�������Ľ��̵��߳���Ϣ
		3������һ���µ�List����
	*/
	// ��ȡ���������һ��
	int index = m_ListONject.GetSelectionMark();
	// ��ȡ����Id ��ֵ��������DialogBox����
	CString str = m_ListONject.GetItemText(index, 0);
	// str.Format(L"%d", str);
	// _ttoi()
	
	ThreadObject.m_id = _ttoi(str);  // ���ǿת��
	//
	this->ThreadObject.DoModal();


	/*	�ڶ��֣�
		1��˫������
		2�������Ի���Ȼ��鿴�߳�
	*/

	/*	�����֣�
		1���һ����̣������˵���
		2���˵��鿴�߳�
		3��������ǰ�߳���Դ��Ϣ
	*/
}

//void MyDialogEx::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//	//str.Format(L"%c", str);
//	//// ��ֵ��Thread����
//	//ThreadObject.m_id = str;
//}
