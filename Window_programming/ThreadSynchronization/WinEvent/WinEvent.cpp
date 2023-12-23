#include <windows.h>
#include <iostream>

HANDLE g_hEvent = 0; // 接收事件句柄

// 线程负责打印
DWORD PrintProc(LPVOID lpParam)
{
	while (1) {

		WaitForSingleObject(g_hEvent, INFINITE);
		// 如果创建事件时，设置复位方式为FALSE，操作系统默认执行以下ResetEvent操作
		// 将事件设置成无信号状态
	ResetEvent(g_hEvent);
		std::cout << "************" << std::endl;
	}
	return 0;
}

// 线程负责控制
DWORD CtrlProc(LPVOID lpParam)
{
	while (1) {
		// 将事件设置为有信号状态
		SetEvent(g_hEvent);
		Sleep(1000);
	}
	return 0;
}


int  main()
{
	g_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	DWORD nID = 0;
	HANDLE hThread[2]{};
	hThread[0] = CreateThread(NULL, 0, PrintProc, NULL, 0, &nID);
	hThread[1] = CreateThread(NULL, 0, CtrlProc, NULL, 0, &nID);

	WaitForMultipleObjects(2, hThread, 0, INFINITE);
	CloseHandle(g_hEvent);
	return 0;
}