#include <windows.h>
#include <iostream>
long g_value = 0;

// ����̶߳�ͬһ�����ݽ���ԭ�Ӳ����������������

DWORD CALLBACK TestProc(LPVOID lpParam)
{
	for (int i = 0; i< 10000000; i++) {
		// g_value++;
		// ʹ��ԭ��������
		InterlockedIncrement(&g_value);
	}
	return 0;
}

DWORD CALLBACK TestProc2(LPVOID lpParam)
{
	for (int i = 0; i < 10000000; i++) {
		// g_value++;
		InterlockedIncrement(&g_value);
	}
	return 0;
}

int main()
{
	DWORD nID = 0;
	HANDLE hThread[2]{};
	hThread[0] = CreateThread(NULL, 0, TestProc, NULL, 0, &nID);
	hThread[1] = CreateThread(NULL, 0, TestProc2, NULL, 0, &nID);

	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	std::cout << "g_value = " << g_value << std::endl;
	return 0;
}