#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "resource.h"

HINSTANCE g_hInstance = 0;

void OnSetCursor(LPARAM lParam)
{
	HCURSOR hCur = LoadCursor(g_hInstance, (char*)IDC_CURSOR2);
	// 在客户窗口区域活动
	if (LOWORD(lParam) == HTCLIENT) {
		// 改变光标
		SetCursor(hCur);
	}
}

void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam)) {
	case ID_NEW:
		// 来自与菜单项
		if (HIWORD(wParam) == 0) {
			MessageBox(hWnd, "新菜单项被点击", "Infor", MB_OK);
		} else if (HIWORD(wParam) == 1) {
			MessageBox(hWnd, "CTRL+N被点击", "Infor", MB_OK);
		}
		break;
	}
}

// 2. 窗口处理函数（自定义，处理消息）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	// 点击菜单项发出的消息
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
	// 鼠标位置发生变化发出的消息
	case WM_SETCURSOR:
		OnSetCursor(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); // 可以使GetMessage函数返回0
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam); // 给各种消息做默认处理
}



// 1.定义WinMain入口函数
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPerIns, LPSTR IpCmdLine, int nCmdShow) {
	g_hInstance = hIns;
	// 3. 注册窗口类 （向系统内核写入数据）
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	// 加载光标
	wc.hCursor = LoadCursor(hIns, (char*)IDC_CURSOR1);
	// 加载图标
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
		MessageBox(NULL, "窗口创建失败！", "错误", MB_ICONERROR);
		return 0;
	}

	// 5.显示窗口 (在显示器中绘制窗口的图像)
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd); // 刷新窗口

	// 加载加速键表
	HACCEL hAccel = LoadAccelerators(hIns, (CHAR*)IDR_ACCELERATOR1);
	// 6. 消息循环
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0)) {

		// 翻译加速键
		if (!TranslateAccelerator(hWnd, hAccel, &nMsg)) {
			TranslateMessage(&nMsg);
			DispatchMessage(&nMsg);	// 将消息交给窗口处理函数处理
		}
	}
	return 0;
}
