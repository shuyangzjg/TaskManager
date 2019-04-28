#pragma once
#include "stdafx.h"
#include "afxwin.h"
#include "resource.h"
#include "afxcmn.h"
#include "My_Chlid_Thread.h"


// MyDialogEx 对话框

class MyDialogEx : public CDialogEx
{
	DECLARE_DYNAMIC(MyDialogEx)

public:
	MyDialogEx(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MyDialogEx();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnStnClickedStatic1();
	CStatic m_Static;
	virtual BOOL OnInitDialog();
//	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_ListONject;
	afx_msg void OnBnClickedButton3();
	// 子窗口对象（Thread）
	My_Chlid_Thread ThreadObject;
private:
	// 遍历进程
	void FindAllProcess();
public:
//	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
