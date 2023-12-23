#include <windows.h>
#include <iostream>
HANDLE g_hSema = 0; // 接收信号量句柄

DWORD CALLBACK TestProc(LPVOID lpParam)
{
	while (1) {
		WaitForSingleObject(g_hSema, INFINITE);
		std::cout << "****************" << std::endl;
	}
	
}

int main()
{
	g_hSema = CreateSemaphore(NULL, 5, 10, NULL);
	DWORD nID = 0;
	HANDLE hThread = CreateThread(NULL,0, TestProc, NULL,0,&nID);
	getchar();
	ReleaseSemaphore(g_hSema, 8, NULL);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(g_hSema);
	return 0;
}