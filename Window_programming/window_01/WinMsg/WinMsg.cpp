#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>

/********************************************
	��Ϣѭ������Ϣ����
*********************************************/

// �Զ�����Ϣ
//#define WM_MYMESSAGE 0x400 + 1001
#define WM_MYMESSAGE WM_USER + 1001


HANDLE g_hOutput = 0; // ���ձ�׼������

// ����WM_CREATE��Ϣ
void OnCreate(HWND hWnd, LPARAM lParam)
{
	CREATESTRUCT* pcs = reinterpret_cast<CREATESTRUCT*>(lParam);
	//CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
	
	// ʹ��IParam������ĳ�Ա
	if (pcs != nullptr && pcs->lpCreateParams != nullptr) {
		const char* pszText = reinterpret_cast<const char*>(pcs->lpCreateParams);
		//char* pszText = (char*)pcs->lpCreateParams;
		MessageBox(NULL, pszText, "Info", MB_OK);
	}
	// �����Զ�����Ϣ
	//PostMessage(hWnd, WM_MYMESSAGE, 0, 0);
	SendMessage(hWnd, WM_MYMESSAGE, 0, 0);

	// �����Ӵ���
	CreateWindowEx(0, "EDIT", "Child", WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 0, 200, 200, hWnd, NULL, 0, NULL);
}

// ����WM_SIZE��Ϣ
void OnResize(HWND hWnd, LPARAM lParam)
{
	short nWidth = LOWORD(lParam);
	short nHeight = HIWORD(lParam);

	char szText[256] = { 0 };
	sprintf_s(szText, "WM_SIZE: ��%d, �ߣ�%d\n", nWidth, nHeight);
	// 	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
		// �����dos����̨
	if (g_hOutput != NULL) {
		WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
	}
}

void OnMyMessage(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	char szText[256] = { 0 };
	sprintf(szText, "�Զ�����Ϣ������wParam = %d, lParam = %d\n", wParam, lParam);
	MessageBox(hWnd, szText, "�Զ�����Ϣ", MB_OK);

}

// 2. ���ڴ��������Զ��壬������Ϣ��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	// �����Զ�����Ϣ
	case WM_MYMESSAGE:
		OnMyMessage(hWnd, wParam, lParam);
		break;
	case WM_SIZE:
		OnResize(hWnd, lParam);
		break;
	case WM_CREATE:
		OnCreate(hWnd, lParam);
		break;
	case WM_DESTROY:
		//PostQuitMessage(0); // ����ʹGetMessage��������0��
		// PostQuitMessage�����ڲ�������PostMessage����
		PostMessage(hWnd, WM_QUIT, 0, 0);
		break;
	case WM_SYSCOMMAND:
		// MessageBox(hWnd, "WM_SYSCOMMAND", "��ʾ��", MB_OK);
		// ������ڹرհ�ť
		if (wParam == SC_CLOSE) {
			int nRet = MessageBox(hWnd, "�Ƿ��˳�", "Information", MB_YESNO);
			if (nRet == IDNO) {
				char szText[256] = "����˷�\n";
				WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
				return 0;
			}
		}

		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam); // ��������Ϣ��Ĭ�ϴ���
}

// 1.����WinMain��ں���
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPerIns, LPSTR IpCmdLine, int nCmdShow) {
	AllocConsole(); // ����dos����
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	// 3. ע�ᴰ���� ����ϵͳ�ں�д�����ݣ�
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);

	// 4. ���ڴ洴������ (�ڴ�洢���ڵĸ�������)
	// HWND hWnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
	const char* pszText = "hello data";
	HWND hWnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, (LPVOID)pszText);

	if (hWnd == NULL){
		MessageBox(NULL, "���ڴ���ʧ�ܣ�", "����", MB_ICONERROR);
		return 0;
	}

	// 5.��ʾ���� (����ʾ���л��ƴ��ڵ�ͼ��)
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd); // ˢ�´���

	// 6. ��Ϣѭ�� 
	// ʹ��PeekMessage���������Ż�

	MSG nMsg = { 0 };
	/*
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);	// ����Ϣ�������ڴ���������
	}*/
	while (1) {
		if (PeekMessage(&nMsg, NULL, 0, 0, PM_NOREMOVE)) {
			// ϵͳ�л�ȡ����Ϣ
			if (GetMessage(&nMsg, NULL, 0, 0)) {
				TranslateMessage(&nMsg);
				DispatchMessage(&nMsg);
			} else {
				// �˳�
				return 0;
			}
		}
		else {
			// û��Ϣ�����д���
			// WriteConsole(g_hOutput, "hello", strlen("hello"), NULL, NULL);
		}
	}
	return 0;
}