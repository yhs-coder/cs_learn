#include <windows.h>
#include <iostream>
using namespace std;
/*
	死锁
*/

CRITICAL_SECTION g_csA;
CRITICAL_SECTION g_csB;
int tickets = 1000;

DWORD CALLBACK SellTicketsA(LPVOID lpParam)
{
	while (1) {
		EnterCriticalSection(&g_csA);	
		cout << "begin A" << endl;
		Sleep(100);	// 此时切换到线程B
		cout << "end A" << endl;
		EnterCriticalSection(&g_csB);

		if (tickets > 0) {
			tickets--;
			cout << "A window remain tickets: " << tickets << endl;
			LeaveCriticalSection(&g_csB);	// 退出关键代码段
			LeaveCriticalSection(&g_csA);	// 退出关键代码段
		}
		else {
			LeaveCriticalSection(&g_csB);	// 退出关键代码段
			LeaveCriticalSection(&g_csA);	// 退出关键代码段
			break;
		}
	}
	return 0;
}

DWORD CALLBACK SellTicketsB(LPVOID lpParam)
{
	while (1) {
		EnterCriticalSection(&g_csB);
		cout << "begin B" << endl;
		Sleep(100);
		cout << "end B" << endl;

		EnterCriticalSection(&g_csA);

		if (tickets > 0) {
			tickets--;
			cout << "B window remain tickets: " << tickets << endl;
			LeaveCriticalSection(&g_csA);	
			LeaveCriticalSection(&g_csB);	
		}
		else {
			LeaveCriticalSection(&g_csA);
			LeaveCriticalSection(&g_csB);
			break;
		}
	}
	return 0;
}


int main()
{
	HANDLE hThreadA, hThreadB;
	hThreadA = CreateThread(NULL, 0, SellTicketsA, NULL, 0, NULL);
	hThreadB = CreateThread(NULL, 0, SellTicketsB, NULL, 0, NULL);
	InitializeCriticalSection(&g_csA);
	InitializeCriticalSection(&g_csB);
	Sleep(30000);
	DeleteCriticalSection(&g_csA);
	DeleteCriticalSection(&g_csB);
	system("pause");
	CloseHandle(hThreadA);
	CloseHandle(hThreadB);
	return 0;
}
