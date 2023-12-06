#include <windows.h>

/*
	1. 使用系统窗口类
	2. 创建子窗口
*/

/*************************************
	使用系统窗口类
*************************************/

#if 0
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPerIns, LPSTR IpCmdLine, int nCmdShow) {
	

	// 使用系统窗口类
	// HWND hWnd = CreateWindow("Button", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);	
	HWND hWnd = CreateWindowEx(0,"Button", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);

	// 显示窗口 (在显示器中绘制窗口的图像)
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd); // 刷新窗口

	// 消息循环
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);	// 将消息交给窗口处理函数处理
	}
	return 0;
}
#endif

/*************************************
	创建子窗口
*************************************/

// 窗口处理函数（自定义，处理消息）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM IParam) {

	switch (msgID) {
	case WM_DESTROY:
		PostQuitMessage(0); // 可以时GetMessage函数返回0？
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, IParam); 
}

int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPerIns, LPSTR IpCmdLine, int nCmdShow) {

	// 父窗口
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
	RegisterClass(&wc);	// 将以上所有赋值全部写入操作系统
	// 创建父窗口
	HWND hWnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);

	// 注册子窗口类
	wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = DefWindowProc; // 微软提供的函数，可以给所有的消息做默认处理
	wc.lpszClassName = "Child";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);	// 将以上所有赋值全部写入操作系统

	// 创建子窗口
	HWND hChild1 = CreateWindowEx(0, "Child", "c1", WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, 0, 0, 200, 200, hWnd, NULL, hIns, NULL);

	// 创建子窗口
	HWND hChild2 = CreateWindowEx(0, "Child", "c2", WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, 200, 0, 200, 200, hWnd, NULL, hIns, NULL);

	// 显示窗口 (在显示器中绘制窗口的图像)
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd); // 刷新窗口

	// 消息循环
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);	// 将消息交给窗口处理函数处理
	}
	return 0;
}