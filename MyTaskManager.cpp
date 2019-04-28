#include "MyTaskManager.h"


Mytaskmanager g_WinApp;

Mytaskmanager::Mytaskmanager()
{
}

Mytaskmanager::~Mytaskmanager()
{
}

BOOL Mytaskmanager::InitInstance()
{
	MyDialogEx big;
	m_pMainWnd = &big;
	big.DoModal();
	return 0;
}