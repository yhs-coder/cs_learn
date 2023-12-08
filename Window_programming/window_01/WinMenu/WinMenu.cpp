#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include "resource.h"

HANDLE g_hOutput = 0; // ���ձ�׼������
HINSTANCE g_hInstance = 0;

// ��ʽ������������WM_CREATE��Ϣ������SetMenu�������ò˵�
void OnCreate(HWND hWnd)
{
	HMENU hMenu = LoadMenu(g_hInstance, (char*)IDR_MENU1);
	SetMenu(hWnd, hMenu);
}


void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam)) {
	case ID_NEW:
		MessageBox(hWnd, "�½������", "Infor", MB_OK);
		break;
	case ID_QUIT:
		MessageBox(hWnd, "�˳������", "Infor", MB_OK);
		break;
	case ID_ABOUT:
		MessageBox(hWnd, "���ڱ����", "Infor", MB_OK);
		break;
	}
}

void OnContextMenu(HWND hWnd, LPARAM lParam)
{
	HMENU hMain = LoadMenu(g_hInstance, (char*)IDR_MENU1);
	// ��ȡ����˵�����һ���Ӳ˵���1��ʾ�ڶ���
	//HMENU hPopup = GetSubMenu(hMain, 0);
	HMENU hPopup = GetSubMenu(hMain, 1);
	TrackPopupMenu(hPopup, TPM_LEFTALIGN | TPM_TOPALIGN, LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL);
}


// 2. ���ڴ��������Զ��壬������Ϣ��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
		// �������Ҽ���Ϣ�������洦���Ҽ��˵�
	case WM_CONTEXTMENU:
		OnContextMenu(hWnd, lParam);
		break;
		// ����˵������WM_COMMAND��Ϣ
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_CREATE:
		OnCreate(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); // ����ʹGetMessage��������0,�˳���Ϣѭ������������
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam); // ��������Ϣ��Ĭ�ϴ���
}


// 1.����WinMain��ں���
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPerIns, LPSTR IpCmdLine, int nCmdShow) {

	g_hInstance = hIns;
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
	// ��ʽһ��ע�ᴰ����ʱ���ò˵�**
	//wc.lpszMenuName = (char*)IDR_MENU1;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);

#if 0
	// ��ʽ���� ��������ʱ���ݲ������ò˵�
	HMENU hMenu = LoadMenu(hIns, (char*)IDR_MENU1);
	const char* pszText = "hello data";
	HWND hWnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, hMenu, hIns, (LPVOID)pszText);
#else
	const char* pszText = "hello data";
	HWND hWnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, (LPVOID)pszText);
#endif

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
