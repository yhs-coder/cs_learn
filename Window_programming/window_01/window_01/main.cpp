#include <windows.h>
#include <stdio.h>
// #include <iostream>
/*
	创建一个窗口程序

*/

HANDLE g_hOutput = 0; // 接收标准输出句柄

// 处理WM_CREATE消息
void OnCreate(HWND hWnd, LPARAM lParam)
{
	CREATESTRUCT* pcs = reinterpret_cast<CREATESTRUCT*>(lParam);
	//CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
	// 使用IParam参数里的成员
	if (pcs != nullptr && pcs->lpCreateParams != nullptr) {
		const char* pszText = reinterpret_cast<const char*>(pcs->lpCreateParams);
		//char* pszText = (char*)pcs->lpCreateParams;
		MessageBox(NULL, pszText, "Info", MB_OK);
	}

	// 创建子窗口
	 CreateWindowEx(0, "EDIT", "Child", WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 0, 200, 200, hWnd, NULL, 0, NULL);
}

// 处理WM_SIZE信息
void OnResize(HWND hWnd, LPARAM lParam)
{
	short nWidth = LOWORD(lParam);
	short nHeight = HIWORD(lParam);
	
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_SIZE: 宽：%d, 高：%d\n", nWidth, nHeight);
// 	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
	// 输出到dos控制台
	if (g_hOutput != NULL) {
		WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
	}
}

// 2. 窗口处理函数（自定义，处理消息）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	case WM_SIZE:
		OnResize(hWnd, lParam);
		break;
	case WM_CREATE:
		OnCreate(hWnd, lParam);
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
	//if (RegisterClass(&wc) == 0);	// 将以上所有赋值全部写入操作系统
	//{
	//	MessageBox(NULL, "窗口注册失败！", "错误", MB_ICONERROR);
	//	return 0;
	//}


	// 4. 在内存创建窗口 (内存存储窗口的各种数据)
	// HWND hWnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
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
	MSG nMsg = {0};
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);	// 将消息交给窗口处理函数处理
	}
	return 0;
}



#if 0
int WINAPI WinMain(
	HINSTANCE hIns,
	HINSTANCE hPreIns,
	LPSTR IpCmdLine,
	int nCmdShow)
{
	MessageBox(NULL, (LPCSTR)"hello world", (LPCSTR)"Information", MB_YESNOCANCEL | MB_ICONERROR);
	return 0;
}
#endif


 

