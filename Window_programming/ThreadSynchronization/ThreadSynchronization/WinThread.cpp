#include <windows.h>
#include <iostream>
using std::cout;
using std::endl;

DWORD CALLBACK ThreadProc(LPVOID lpParam)
{
	cout << "ThreadProc: threadId:" << GetCurrentThreadId() << endl;
	char* pzText = (char*)lpParam;
	while (1) {
		cout << pzText << endl;
		Sleep(1000);
	}
	return 0;
}

DWORD CALLBACK ThreadProc2(LPVOID lpParam)
{
	cout << "ThreadProc: threadId2:" << GetCurrentThreadId() << endl;
	char* pzText = (char*)lpParam;
	while (1) {
		cout << pzText << endl;
		Sleep(1000);
	}
	return 0;
}

int main() 
{
	const char* pzText = "********";
	DWORD threadId = 0;
	HANDLE hThread1 = CreateThread(nullptr, 1, ThreadProc, (LPVOID)pzText, 0, &threadId);
	cout << "threadId:" << threadId << endl;

	// WaitForSingleObject(hThread1, INFINITE);	// 等候线程1句柄有信号
	const char* pzText2 = "--------";
	DWORD threadId2 = 0;
	HANDLE hThread2 = CreateThread(nullptr, 1, ThreadProc2, (LPVOID)pzText2, CREATE_SUSPENDED, &threadId2);
	cout << "threadId2:" << threadId2 << endl;


	getchar();
	// SuspendThread(hThread1);	// 线程1挂起
	ResumeThread(hThread2);		// 线程2唤醒
	getchar();
	TerminateThread(hThread1,1); // 结束指定的线程1
	getchar();

	return 0;
}