#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
HANDLE g_hOutput = 0; // ���ձ�׼������

void OnKeyDown(HWND hWnd, WPARAM wParam)
{
	char szText[256] = { 0 };
	sprintf(szText, "WM_KEYDOWN������ֵ = %d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnKeyUp(HWND hWnd, WPARAM wParam)
{
	char szText[256] = { 0 };
	sprintf(szText, "WM_KEYUP������ֵ = %d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnSysKeyDown(HWND hWnd, WPARAM wParam)
{
	char szText[256] = { 0 };
	sprintf(szText, "WM_SYSKEYDOWN������ֵ = %d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnChar(HWND hWnd, WPARAM wParam)
{
	char szText[256] = { 0 };
	sprintf(szText, "WM_CHAR������ֵ = %d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

// 2. ���ڴ��������Զ��壬������Ϣ��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	case WM_CHAR:
		OnChar(hWnd, wParam);
		break;
		// ϵͳ�������£���alt,ctrl
	case WM_SYSKEYDOWN:
		OnSysKeyDown(hWnd, wParam);
		break;
		// ��������
	case WM_KEYDOWN:
		OnKeyDown(hWnd, wParam);
		break;
		// �����ſ�
	case WM_KEYUP:
		OnKeyUp(hWnd, wParam);
		break;
	case WM_LBUTTONDOWN:
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); // ����ʹGetMessage��������0��
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

	const char* pszText = "hello data";
	HWND hWnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, (LPVOID)pszText);

	if (hWnd == NULL) {
		MessageBox(NULL, "���ڴ���ʧ�ܣ�", "����", MB_ICONERROR);
		return 0;
	}

	// 5.��ʾ���� (����ʾ���л��ƴ��ڵ�ͼ��)
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd); // ˢ�´���

	// 6. ��Ϣѭ��
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);	// ����Ϣ�������ڴ���������
	}
	return 0;
}
