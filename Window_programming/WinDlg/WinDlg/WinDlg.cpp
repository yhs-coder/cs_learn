#include <windows.h>
#include <iostream>
#include "resource.h"

HINSTANCE g_hInstance = 0;

//typedef INT_PTR(CALLBACK* DLGPROC)(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID) {
	case WM_INITDIALOG:
		MessageBox(hwndDlg, "WM_INITDIALOG", "Infor", MB_OK);
		break;
	case WM_CREATE:
		MessageBox(hwndDlg, "WM_CREATE", "Infor", MB_OK);
		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE) {
			// 销毁模式对话框
			EndDialog(hwndDlg, 100);
		}
		break;
	}
	return FALSE;	// 将消息交给真正的对话框窗口处理函数的后续代码，来进行处理
}

void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam)) {
	case ID_MODEL:
		int nRet = DialogBox(g_hInstance, (char*)IDD_DIALOG1, hWnd, DlgProc);
		if (nRet == 100) {
			MessageBox(hWnd, "successful", "Infor", MB_OK);
		}
		break;
	}
} 


// 2. 窗口处理函数（自定义，处理消息）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); // 可以使GetMessage函数返回0
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam); // 给各种消息做默认处理
}


int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPerIns, LPSTR IpCmdLine, int nCmdShow)
{
	g_hInstance = hIns;
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";
	wc.lpszMenuName = (char*)IDR_MENU1;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);
	HWND hWnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd); // 刷新窗口
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);	// 将消息交给窗口处理函数处理
	}
	return 0;
}





