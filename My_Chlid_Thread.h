#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"

// My_Chlid_Thread �Ի���

class My_Chlid_Thread : public CDialogEx
{
	DECLARE_DYNAMIC(My_Chlid_Thread)

public:
	My_Chlid_Thread(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~My_Chlid_Thread();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	CListCtrl My_ListCtrl;
	// ������̵�ID��
	static DWORD m_id;
private:
	// �����߳�
	VOID ListProcessThreads(DWORD dwPID);
};
