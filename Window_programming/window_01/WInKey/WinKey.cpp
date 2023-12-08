#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
HANDLE g_hOutput = 0; // 接收标准输出句柄

void OnKeyDown(HWND hWnd, WPARAM wParam)
{
	char szText[256] = { 0 };
	sprintf(szText, "WM_KEYDOWN：键码值 = %d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnKeyUp(HWND hWnd, WPARAM wParam)
{
	char szText[256] = { 0 };
	sprintf(szText, "WM_KEYUP：键码值 = %d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnSysKeyDown(HWND hWnd, WPARAM wParam)
{
	char szText[256] = { 0 };
	sprintf(szText, "WM_SYSKEYDOWN：键码值 = %d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnChar(HWND hWnd, WPARAM wParam)
{
	char szText[256] = { 0 };
	sprintf(szText, "WM_CHAR：键码值 = %d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

// 2. 窗口处理函数（自定义，处理消息）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	case WM_CHAR:
		OnChar(hWnd, wParam);
		break;
		// 系统按键按下，如alt,ctrl
	case WM_SYSKEYDOWN:
		OnSysKeyDown(hWnd, wParam);
		break;
		// 按键按下
	case WM_KEYDOWN:
		OnKeyDown(hWnd, wParam);
		break;
		// 按键放开
	case WM_KEYUP:
		OnKeyUp(hWnd, wParam);
		break;
	case WM_LBUTTONDOWN:
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); // 可以使GetMessage函数返回0？
		break;
	case WM_SYSCOMMAND:
		// MessageBox(hWnd, "WM_SYSCOMMAND", "提示框", MB_OK);
		// 点击窗口关闭按钮
		if (wParam == SC_CLOSE) {
			int nRet = MessageBox(hWnd, "是否退出", "Information", MB_YESNO);
			if (nRet == IDNO) {
				char szText[256] = "点击了否\n";
				WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
				return 0;
			}
		}
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam); // 给各种消息做默认处理
}


// 1.定义WinMain入口函数
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPerIns, LPSTR IpCmdLine, int nCmdShow) {
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
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);

	const char* pszText = "hello data";
	HWND hWnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, (LPVOID)pszText);

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
