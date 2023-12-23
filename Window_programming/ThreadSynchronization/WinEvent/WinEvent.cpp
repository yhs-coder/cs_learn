#include <windows.h>
#include <iostream>

HANDLE g_hEvent = 0; // �����¼����

// �̸߳����ӡ
DWORD PrintProc(LPVOID lpParam)
{
	while (1) {

		WaitForSingleObject(g_hEvent, INFINITE);
		// ��������¼�ʱ�����ø�λ��ʽΪFALSE������ϵͳĬ��ִ������ResetEvent����
		// ���¼����ó����ź�״̬
	ResetEvent(g_hEvent);
		std::cout << "************" << std::endl;
	}
	return 0;
}

// �̸߳������
DWORD CtrlProc(LPVOID lpParam)
{
	while (1) {
		// ���¼�����Ϊ���ź�״̬
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