#include <windows.h>
#include <iostream>
using namespace std;
/*
	�ؼ�����Σ��������û�̬�ռ䣬ʹ�øû��Ʊ�֤�߳���������ͬһ��Դ
*/

CRITICAL_SECTION g_cs;
int tickets = 1000;

DWORD CALLBACK SellTicketsA(LPVOID lpParam)
{
	while (1) {
		EnterCriticalSection(&g_cs);	// ����ؼ�����Σ���ȡ�˸��ٽ������������Ȩ�������߳�ֻ�ܵȴ����߳��˳��ٽ�������ȡ����Ȩ�ſɷ���
		if (tickets > 0) {
			tickets--;
			cout << "A window remain tickets: " << tickets << endl;
			LeaveCriticalSection(&g_cs);	// �˳��ؼ������
		} else {
			LeaveCriticalSection(&g_cs);	// �˳��ؼ������
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
			LeaveCriticalSection(&g_cs);	// �˳��ؼ������
		}
		else {
			LeaveCriticalSection(&g_cs);	// �˳��ؼ������
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
	InitializeCriticalSection(&g_cs);	// ��ʼ���ؼ������
	Sleep(30000);
	DeleteCriticalSection(&g_cs);		// ɾ���ؼ������
	system("pause");
	CloseHandle(hThreadA);
	CloseHandle(hThreadB);
	return 0;
}
