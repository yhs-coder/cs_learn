#include <windows.h>
#include <iostream>
using std::cout;
using std::endl;

// 两个子线程共享的是dos窗口，即临界资源是dos窗口

HANDLE g_hMutex = 0;	// 接收互斥句柄

DWORD CALLBACK ThreadProc(LPVOID lpParam)
{
	char* pzText = (char*)lpParam;
	while (1) {
		/*cout << pzText << endl;
		Sleep(1000);*/

		// 等候互斥句柄有信号
		Wait

	}
	return 0;
}

DWORD CALLBACK ThreadProc2(LPVOID lpParam)
{
	char* pzText = (char*)lpParam;
	while (1) {
		/*cout << pzText << endl;
		Sleep(1000);*/
		WaitForSingleObject(g_hMutex, INFINITE);
		for (int i = 0; i < strlen(pzText); i++) {
			cout << pzText[i];
			Sleep(125);
		}
		cout << endl;
		ReleaseMutex(g_hMutex);
	}
	return 0;
}

int main()
{
	g_hMutex = CreateMutex(NULL, FALSE, NULL);	// 当前互斥句柄不属于任何线程，表示当前互斥句柄有信号
	const char* pzText = "********";
	DWORD threadId = 0;
	HANDLE hThread1 = CreateThread(nullptr, 1, ThreadProc, (LPVOID)pzText, 0, &threadId);

	const char* pzText2 = "--------";
	DWORD threadId2 = 0;
	HANDLE hThread2 = CreateThread(nullptr, 1, ThreadProc2, (LPVOID)pzText2, 0, &threadId2);

	getchar();
	CloseHandle(g_hMutex);	// 关闭互斥句柄
	return 0;
}