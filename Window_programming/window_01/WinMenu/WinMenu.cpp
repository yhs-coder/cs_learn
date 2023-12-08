#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include "resource.h"

HANDLE g_hOutput = 0; // 接收标准输出句柄
HINSTANCE g_hInstance = 0;

// 方式三：在主窗口WM_CREATE消息中利用SetMenu函数设置菜单
void OnCreate(HWND hWnd)
{
	HMENU hMenu = LoadMenu(g_hInstance, (char*)IDR_MENU1);
	SetMenu(hWnd, hMenu);
}


void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam)) {
	case ID_NEW:
		MessageBox(hWnd, "新建被点击", "Infor", MB_OK);
		break;
	case ID_QUIT:
		MessageBox(hWnd, "退出被点击", "Infor", MB_OK);
		break;
	case ID_ABOUT:
		MessageBox(hWnd, "关于被点击", "Infor", MB_OK);
		break;
	}
}

void OnContextMenu(HWND hWnd, LPARAM lParam)
{
	HMENU hMain = LoadMenu(g_hInstance, (char*)IDR_MENU1);
	// 获取顶层菜单栏第一个子菜单，1表示第二个
	//HMENU hPopup = GetSubMenu(hMain, 0);
	HMENU hPopup = GetSubMenu(hMain, 1);
	TrackPopupMenu(hPopup, TPM_LEFTALIGN | TPM_TOPALIGN, LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL);
}


// 2. 窗口处理函数（自定义，处理消息）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
		// 点击鼠标右键消息，在里面处理右键菜单
	case WM_CONTEXTMENU:
		OnContextMenu(hWnd, lParam);
		break;
		// 点击菜单项产生WM_COMMAND消息
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_CREATE:
		OnCreate(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); // 可以使GetMessage函数返回0,退出消息循环，结束程序
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam); // 给各种消息做默认处理
}


// 1.定义WinMain入口函数
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPerIns, LPSTR IpCmdLine, int nCmdShow) {

	g_hInstance = hIns;
	AllocConsole(); // 增加dos窗口
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	// 3. 注册窗口类 （向系统内核写入数据）
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
	// 方式一：注册窗口类时设置菜单**
	//wc.lpszMenuName = (char*)IDR_MENU1;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);

#if 0
	// 方式二： 创建窗口时传递参数设置菜单
	HMENU hMenu = LoadMenu(hIns, (char*)IDR_MENU1);
	const char* pszText = "hello data";
	HWND hWnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, hMenu, hIns, (LPVOID)pszText);
#else
	const char* pszText = "hello data";
	HWND hWnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, (LPVOID)pszText);
#endif

	if (hWnd == NULL) {
		MessageBox(NULL, "窗口创建失败！", "错误", MB_ICONERROR);
		return 0;
	}

	// 5.显示窗口 (在显示器中绘制窗口的图像)
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd); // 刷新窗口

	// 6. 消息循环
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);	// 将消息交给窗口处理函数处理
	}
	return 0;
}
