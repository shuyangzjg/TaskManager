#pragma once // 编译指示 一次
#ifndef _PRAGMA_H_
#define _PRAGMA_H_
#include <afxwin.h>
#include "MyDialogEx.h"

class Mytaskmanager : public CWinApp
{
public:
	Mytaskmanager();
	~Mytaskmanager();
private:
	virtual BOOL InitInstance() override;
};

#endif