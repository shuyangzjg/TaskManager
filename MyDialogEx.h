#pragma once
#include "stdafx.h"
#include "afxwin.h"
#include "resource.h"
#include "afxcmn.h"
#include "My_Chlid_Thread.h"


// MyDialogEx �Ի���

class MyDialogEx : public CDialogEx
{
	DECLARE_DYNAMIC(MyDialogEx)

public:
	MyDialogEx(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MyDialogEx();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnStnClickedStatic1();
	CStatic m_Static;
	virtual BOOL OnInitDialog();
//	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_ListONject;
	afx_msg void OnBnClickedButton3();
	// �Ӵ��ڶ���Thread��
	My_Chlid_Thread ThreadObject;
private:
	// ��������
	void FindAllProcess();
public:
//	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
