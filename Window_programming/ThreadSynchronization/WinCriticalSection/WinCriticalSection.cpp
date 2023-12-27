#include <windows.h>
#include <iostream>
using namespace std;
/*
	关键代码段：运行在用户态空间，使用该机制保证线程正常访问同一资源
*/

CRITICAL_SECTION g_cs;
int tickets = 1000;

DWORD CALLBACK SellTicketsA(LPVOID lpParam)
{
	while (1) {
		EnterCriticalSection(&g_cs);	// 进入关键代码段，获取了该临界区对象的所有权，其他线程只能等待该线程退出临界区，获取访问权才可访问
		if (tickets > 0) {
			tickets--;
			cout << "A window remain tickets: " << tickets << endl;
			LeaveCriticalSection(&g_cs);	// 退出关键代码段
		} else {
			LeaveCriticalSection(&g_cs);	// 退出关键代码段
			break;
		}	
	}
	return 0;
}

DWORD CALLBACK SellTicketsB(LPVOID lpParam)
{
	while (1) {
		EnterCriticalSection(&g_cs);	
		if (tickets > 0) {
			tickets--;
			cout << "B window remain tickets: " << tickets << endl;
			LeaveCriticalSection(&g_cs);	// 退出关键代码段
		}
		else {
			LeaveCriticalSection(&g_cs);	// 退出关键代码段
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
	InitializeCriticalSection(&g_cs);	// 初始化关键代码段
	Sleep(30000);
	DeleteCriticalSection(&g_cs);		// 删除关键代码段
	system("pause");
	CloseHandle(hThreadA);
	CloseHandle(hThreadB);
	return 0;
}
