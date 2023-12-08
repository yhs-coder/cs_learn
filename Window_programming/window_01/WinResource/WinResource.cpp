#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "resource.h"

HINSTANCE g_hInstance = 0;

void OnSetCursor(LPARAM lParam)
{
	HCURSOR hCur = LoadCursor(g_hInstance, (char*)IDC_CURSOR2);
	// �ڿͻ���������
	if (LOWORD(lParam) == HTCLIENT) {
		// �ı���
		SetCursor(hCur);
	}
}

void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam)) {
	case ID_NEW:
		// ������˵���
		if (HIWORD(wParam) == 0) {
			MessageBox(hWnd, "�²˵�����", "Infor", MB_OK);
		} else if (HIWORD(wParam) == 1) {
			MessageBox(hWnd, "CTRL+N�����", "Infor", MB_OK);
		}
		break;
	}
}

// 2. ���ڴ��������Զ��壬������Ϣ��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	// ����˵��������Ϣ
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
	// ���λ�÷����仯��������Ϣ
	case WM_SETCURSOR:
		OnSetCursor(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); // ����ʹGetMessage��������0
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam); // ��������Ϣ��Ĭ�ϴ���
}



// 1.����WinMain��ں���
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPerIns, LPSTR IpCmdLine, int nCmdShow) {
	g_hInstance = hIns;
	// 3. ע�ᴰ���� ����ϵͳ�ں�д�����ݣ�
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	// ���ع��
	wc.hCursor = LoadCursor(hIns, (char*)IDC_CURSOR1);
	// ����ͼ��
	wc.hIcon = LoadIcon(hIns, (char*)IDI_ICON1);
	wc.hInstance = hIns;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";
	wc.lpszMenuName = (CHAR*)IDR_MENU1;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);

	char szText[256] = { 0 };
	LoadString(hIns, IDS_WND, szText, 256);
	const char* pszText = "hello data";
	HWND hWnd = CreateWindow("Main", szText, WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, (LPVOID)pszText);

	if (hWnd == NULL) {
		MessageBox(NULL, "���ڴ���ʧ�ܣ�", "����", MB_ICONERROR);
		return 0;
	}

	// 5.��ʾ���� (����ʾ���л��ƴ��ڵ�ͼ��)
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd); // ˢ�´���

	// ���ؼ��ټ���
	HACCEL hAccel = LoadAccelerators(hIns, (CHAR*)IDR_ACCELERATOR1);
	// 6. ��Ϣѭ��
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0)) {

		// ������ټ�
		if (!TranslateAccelerator(hWnd, hAccel, &nMsg)) {
			TranslateMessage(&nMsg);
			DispatchMessage(&nMsg);	// ����Ϣ�������ڴ���������
		}
	}
	return 0;
}
