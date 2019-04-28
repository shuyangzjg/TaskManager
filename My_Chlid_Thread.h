#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"

// My_Chlid_Thread 对话框

class My_Chlid_Thread : public CDialogEx
{
	DECLARE_DYNAMIC(My_Chlid_Thread)

public:
	My_Chlid_Thread(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~My_Chlid_Thread();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	CListCtrl My_ListCtrl;
	// 保存进程的ID号
	static DWORD m_id;
private:
	// 遍历线程
	VOID ListProcessThreads(DWORD dwPID);
};
